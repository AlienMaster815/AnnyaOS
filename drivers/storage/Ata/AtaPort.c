#include "AtaCore.h"

typedef struct _ATA_PORT_LIST_ENTRY{
    ListHeader              Peers;
    PATA_PORT_DEVICE_OBJECT PortDevice;
}ATA_PORT_LIST_ENTRY, * PATA_PORT_LIST_ENTRY;

static mutex_t      PortListLock = {0};
static ListHeader   PortList = {0};

static LOUSTATUS AtaCoreAllocatePortListEntry(PATA_PORT_DEVICE_OBJECT PortDevice){
    PATA_PORT_LIST_ENTRY NewEntry = LouKeMallocType(ATA_PORT_LIST_ENTRY, KERNEL_GENERIC_MEMORY);
    if(!NewEntry){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    NewEntry->PortDevice = PortDevice;
    MutexLock(&PortListLock);
    LouKeListAddTail(&NewEntry->Peers , &PortList);
    MutexUnlock(&PortListLock);
    return STATUS_SUCCESS;
}

static void AtaCoreFreePortListEntry(PATA_PORT_DEVICE_OBJECT PortDevice){
    PATA_PORT_LIST_ENTRY TmpEntry = 0x00, SafeEntry = 0x00, WantedEntry = 0x00;
    MutexLock(&PortListLock);
    ForEachListEntrySafe(TmpEntry, SafeEntry, &PortList, Peers){
        if(TmpEntry->PortDevice == PortDevice){
            WantedEntry = TmpEntry;
            break;
        }
    }
    if(WantedEntry){
        LouKeListDeleteItem(&WantedEntry->Peers);
    }
    MutexUnlock(&PortListLock);
    if(WantedEntry){
        LouKeFree(WantedEntry);
    }
}

DRIVER_EXPORT void AtaCoreFreeAtaPortsFromHost(PATA_HOST_DEVICE_OBJECT HostDevice){
    PATA_PORT_DEVICE_OBJECT Ports = HostDevice->PortDevices;
    SIZE PortCount = HostDevice->PortCount;
    HostDevice->PortCount = 0;
    HostDevice->PortDevices = 0x00;
    if(!Ports){
        return;
    }
    if(Ports->PortPrivateData){
        LouKeFree(Ports->PortPrivateData);
    }
    if(HostDevice->ChannelLocks){
        LouKeFree(HostDevice->ChannelLocks);
    }
    LouKeFree(Ports);
}

DRIVER_EXPORT LOUSTATUS AtaCoreAllocatePortsForHost(
    PATA_HOST_DEVICE_OBJECT HostDevice,
    SIZE                    PortCount,
    SIZE                    PrivateDataSize,
    SIZE                    PrivateDataAlignment
){
    HostDevice->PortDevices = LouKeMallocArray(ATA_PORT_DEVICE_OBJECT, PortCount, KERNEL_GENERIC_MEMORY);
    if(!HostDevice->PortDevices){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    HostDevice->PortCount = PortCount;
    HostDevice->ChannelLocks = LouKeMallocArray(mutex_t, PortCount, KERNEL_GENERIC_MEMORY);
    if(!HostDevice->ChannelLocks){
        AtaCoreFreeAtaPortsFromHost(HostDevice);
        return STATUS_INSUFFICIENT_RESOURCES;
    }


    if(PrivateDataSize){
        HostDevice->PortDevices->PortPrivateData = LouKeMallocEx(ROUND_UP64(PrivateDataSize, PrivateDataAlignment) * PortCount, PrivateDataAlignment, KERNEL_GENERIC_MEMORY);
        if(!HostDevice->PortDevices->PortPrivateData){
            AtaCoreFreeAtaPortsFromHost(HostDevice);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        for(SIZE i = 0 ; i < PortCount; i++){
            HostDevice->PortDevices[i].PortPrivateData = (PVOID)(UINT8*)((UINT64)(UINT8*)HostDevice->PortDevices->PortPrivateData + (ROUND_UP64(PrivateDataSize, PrivateDataAlignment) * i));
            HostDevice->PortDevices[i].ChannelLock = &HostDevice->ChannelLocks[i];
            HostDevice->PortDevices[i].HostDevice = HostDevice;
        }
    }
    return STATUS_SUCCESS;
}

void AtaCoreSendIdentifyCommand(PATA_PORT_DEVICE_OBJECT AtaPort, PATA_COMMAND_PACKET Identify, UINT8 Dev, BOOLEAN PacketDev){
    PATA_HOST_DEVICE_OBJECT HostDevice = AtaPort->HostDevice;    
    
    MutexLock(AtaPort->ChannelLock);

    memset(Identify, 0, sizeof(ATA_COMMAND_PACKET));

    LOUSTATUS Status;
    Identify->CommandFlags = ATA_COMMAND_PACKET_FLAGS_TRAN_CMD | ATA_COMMAND_PACKET_FLAGS_POLL; 
    LouKeSetAtomicBoolean(&Identify->CommandDone, 0);
    Identify->PioDataIn = LouKeMallocEx(256 * sizeof(UINT16), GET_ALIGNMENT(UINT16), KERNEL_GENERIC_MEMORY);
    Identify->PioSize = 512;
    if(PacketDev){
        AtaCoreEncodeIdentifyPacketDeviceCommand((PATA_COMMAND_IDENTIFY_PACKET_DEVICE_STRUCTURE)&Identify->Packet, Dev);
    }else{
        AtaCoreEncodeIdentifyDeviceCommand((PATA_COMMAND_IDENTIFY_DEVICE_STRUCTURE)&Identify->Packet, Dev);
    }
    if(AtaPort->Operations->AtaPortDevicePrepCommand){
        Status = AtaPort->Operations->AtaPortDevicePrepCommand(AtaPort, Identify);
        if(Status != STATUS_SUCCESS){
            Identify->CommandStatus = STATUS_IO_DEVICE_ERROR;
            LouKeSetAtomicBoolean(&Identify->CommandDone, 1);
        }
    }

    LouKeListAddTail(&Identify->QueuedCommands, &AtaPort->QueuedCommands);

    LouKeUnblockThread(LouKeGetThreadIdentificationFromThreadHandle(AtaPort->CommandWorkerThread));

    MutexUnlock(AtaPort->ChannelLock);
        
    while(!LouKeGetAtomicBoolean(&Identify->CommandDone)){
        sleep(10);
    }

    if(Identify->CommandStatus != STATUS_SUCCESS){
        LouKeFree(Identify->PioDataIn);
        return;
    }
}

void AtaCoreParsePacketDeviceInformation(
    PATA_COMMAND_PACKET         Identify, 
    PATA_ENDPOINT_DEVICE_OBJECT EndpointDevice
){
    UINT16 TmpInfo = *(UINT16*)Identify->PioDataIn;
    UINT64 CapChecksum;
    UINT8  FieldMask = 0;
    EndpointDevice->DeviceCap = 0;
    EndpointDevice->DeviceCap |= TmpInfo & (1 << 15) ? ATA_ENDPOINT_DEVCAP_ATAPI : 0;
    EndpointDevice->DeviceCap |= TmpInfo & (1 << 7) ? ATA_ENDPOINT_DEVCAP_REMOVEABLE : 0;
    EndpointDevice->DeviceCap |= TmpInfo & (1 << 7) ? ATA_ENDPOINT_DEVCAP_REMOVEABLE : 0;
    EndpointDevice->PacketSize = (TmpInfo & 1) ? 16 : 12;

    TmpInfo = ((UINT16*)Identify->PioDataIn)[49];

    EndpointDevice->DeviceCap |= (TmpInfo & (1 << 8)) ? ATA_ENDPOINT_DEVCAP_DMA_SUPPORT : 0;
    EndpointDevice->DeviceCap |= (TmpInfo & (1 << 9)) ? ATA_ENDPOINT_DEVCAP_LBA_SUPPORT : 0;
    EndpointDevice->DeviceCap |= (TmpInfo & (1 << 10)) ? ATA_ENDPOINT_DEVCAP_IORDY_DISABLED : 0;
    EndpointDevice->DeviceCap |= (TmpInfo & (1 << 11)) ? ATA_ENDPOINT_DEVCAP_OVERLAP_SUPPORT : 0;
    EndpointDevice->DeviceCap |= (TmpInfo & (1 << 13)) ? ATA_ENDPOINT_DEVCAP_OVERLAP_SUPPORT : 0;
    EndpointDevice->DeviceCap |= (TmpInfo & (1 << 14)) ? ATA_ENDPOINT_DEVCAP_QUEUE_SUPPORT : 0;
    EndpointDevice->DeviceCap |= (TmpInfo & (1 << 15)) ? ATA_ENDPOINT_DEVCAP_INTERLEAVE_DMA : 0;

    FieldMask = ((UINT16*)Identify->PioDataIn)[53] & 0x07;

    TmpInfo = ((UINT16*)Identify->PioDataIn)[63];
    int i;
    for(i = 2; i >= 0; i--){
        if(TmpInfo & (1 << i)){
            EndpointDevice->MaxMDmaSupport = i;
            break;
        }
    }

    for(i = 2; i >= 0; i--){
        if(TmpInfo & (1 << (i + 8))){
            EndpointDevice->MDmaSelected = i;
            break;
        }
    }

    EndpointDevice->PioModesSupported = ((UINT16*)Identify->PioDataIn)[64] & 0xFF;

    EndpointDevice->MaxQueueDepth = (((UINT16*)Identify->PioDataIn)[75] & 0xFF) + 1;

    //CapChecksum = ((UINT16*)Identify->PioDataIn)[80];
    //if((CapChecksum != 0x00) && (CapChecksum != 0xFFFF)){
    //TODO: Read the most recent spec and implement features
    //}

    CapChecksum = ((UINT64)((UINT16*)Identify->PioDataIn)[82] << 16) | (UINT64)((UINT16*)Identify->PioDataIn)[83];
    if((CapChecksum != 0x00) && (CapChecksum != 0xFFFFFFFF)){
        TmpInfo = ((UINT16*)Identify->PioDataIn)[82];
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 0)) ? ATA_ENDPOINT_DEVCAP_SMART_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 1)) ? ATA_ENDPOINT_DEVCAP_SECURITY_MODE_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 2)) ? ATA_ENDPOINT_DEVCAP_REMOVEABLE_MEDIA_FEATURE : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 3)) ? ATA_ENDPOINT_DEVCAP_PM_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 4)) ? ATA_ENDPOINT_DEVCAP_PACKET_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 5)) ? ATA_ENDPOINT_DEVCAP_WRITE_CACHE_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 6)) ? ATA_ENDPOINT_DEVCAP_LOOK_AHEAD_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 7)) ? ATA_ENDPOINT_DEVCAP_RELEASE_INTERRUPT_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 8)) ? ATA_ENDPOINT_DEVCAP_SERVICE_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 9)) ? ATA_ENDPOINT_DEVCAP_DEVICE_RESET_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 10)) ? ATA_ENDPOINT_DEVCAP_HPAFS_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 12)) ? ATA_ENDPOINT_DEVCAP_WRITEBUFF_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 13)) ? ATA_ENDPOINT_DEVCAP_READBUFF_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 14)) ? ATA_ENDPOINT_DEVCAP_NOP_SUPPORT : 0;
        
        TmpInfo = ((UINT16*)Identify->PioDataIn)[83];
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 0)) ? ATA_ENDPOINT_DEVCAP_DOWNLOAD_MICROCODE_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 4)) ? ATA_ENDPOINT_DEVCAP_REMOVEABLE_MEDIA_STAT_FEAT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 5)) ? ATA_ENDPOINT_DEVCAP_POWER_UP_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 6)) ? ATA_ENDPOINT_DEVCAP_SETFEAT_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 8)) ? ATA_ENDPOINT_DEVCAP_SETMAX_SECURITY_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 11)) ? ATA_ENDPOINT_DEVCAP_DEVCONF_OVERLAY_SUPPORT : 0;
        EndpointDevice->DeviceCap |= (TmpInfo & (1 << 12)) ? ATA_ENDPOINT_DEVCAP_FLUSH_CACHE_SUPPORT : 0;

        
    }
    CapChecksum = ((UINT64)((UINT16*)Identify->PioDataIn)[85] << 24) | ((UINT64)((UINT16*)Identify->PioDataIn)[86] << 16) | (UINT64)((UINT16*)Identify->PioDataIn)[87];
    if((CapChecksum != 0x00) && (CapChecksum != 0x0000FFFFFFFFFFFF)){
        TmpInfo = ((UINT16*)Identify->PioDataIn)[85];

        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 0)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_SMART_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 1)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_SECURITY_MODE_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 2)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_REMOVEABLE_MEDIA_FEATURE);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 3)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_PM_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 4)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_PACKET_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 5)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_WRITE_CACHE_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 6)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_LOOK_AHEAD_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 7)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_RELEASE_INTERRUPT_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 8)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_SERVICE_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 9)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_DEVICE_RESET_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 10)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_HPAFS_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 12)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_WRITEBUFF_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 13)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_READBUFF_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 14)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_NOP_SUPPORT);
    
        TmpInfo = ((UINT16*)Identify->PioDataIn)[86];
    
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 0)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_DOWNLOAD_MICROCODE_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 4)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_REMOVEABLE_MEDIA_STAT_FEAT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 5)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_POWER_UP_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 6)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_SETFEAT_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 8)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_SETMAX_SECURITY_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 11)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_DEVCONF_OVERLAY_SUPPORT);
        EndpointDevice->DeviceCap &= (TmpInfo & (1 << 12)) ? UINT64_MAX : ~(ATA_ENDPOINT_DEVCAP_FLUSH_CACHE_SUPPORT);

        TmpInfo = ((UINT16*)Identify->PioDataIn)[87];
        for(i = 5; i >= 0; i--){
            if(TmpInfo & (1 << i)){
                EndpointDevice->MaxMDmaSupport = i;
                break;
            }
        }

        for(i = 5; i >= 0; i--){
            if(TmpInfo & (1 << (i + 8))){
                EndpointDevice->MDmaSelected = i;
                break;
            }
        }

    }


    for(SIZE i = 0; i < 10; i++){
        EndpointDevice->SerialNumber[i * 2] = (char)(((((UINT16*)Identify->PioDataIn)[i + 10]) >> 8) & 0xFF);
        EndpointDevice->SerialNumber[(i * 2) + 1] = (char)((((UINT16*)Identify->PioDataIn)[i + 10]) & 0xFF);
    }
    
    for(SIZE i = 0; i < 4; i++){
        EndpointDevice->FirmwareVersion[i * 2] = (char)(((((UINT16*)Identify->PioDataIn)[i + 23]) >> 8) & 0xFF);
        EndpointDevice->FirmwareVersion[(i * 2) + 1] = (char)((((UINT16*)Identify->PioDataIn)[i + 23]) & 0xFF);
    }

    for(SIZE i = 0; i < 20; i++){
        EndpointDevice->ModelNumber[i * 2] = (char)(((((UINT16*)Identify->PioDataIn)[i + 27]) >> 8) & 0xFF);
        EndpointDevice->ModelNumber[(i * 2) + 1] =  (char)((((UINT16*)Identify->PioDataIn)[i + 27]) & 0xFF);
    }

    //LouPrint("SERIAL:%s\n", EndpointDevice->SerialNumber);
    //LouPrint("FIRMWARE:%s\n", EndpointDevice->FirmwareVersion);    
    //LouPrint("MODEL:%s\n", EndpointDevice->ModelNumber);    
    
    LouKeFree(Identify->PioDataIn);

}

void AtaCoreProbePortForDevice(PATA_PORT_DEVICE_OBJECT AtaPort){

    PATA_COMMAND_PACKET Identify = LouKeMallocType(ATA_COMMAND_PACKET, KERNEL_GENERIC_MEMORY);
    SIZE Channels = AtaPort->HostDevice->HostFlags & ATA_HOST_FLAGS_DUAL_CHANNEL ? 2 : 1; 
    for(SIZE i = 0; i < Channels; i++){
        BOOLEAN PacketDevice = false;
                
        AtaCoreSendIdentifyCommand(AtaPort, Identify, i, false);
            
        if((Identify->Packet.Status & (1 << 5)) && (Identify->Packet.Error == 0x04)){
            PacketDevice = true;
            AtaCoreSendIdentifyCommand(AtaPort, Identify, i, true);
        }else if(Identify->Packet.Status & (1 << 5)){
            continue;
        }else if(Identify->Packet.Status & 0x01){
            PacketDevice = true;
            AtaCoreSendIdentifyCommand(AtaPort, Identify, i, true);
        }else if(Identify->CommandStatus == STATUS_TIMEOUT){
            continue;
        }

        if(Identify->CommandStatus == STATUS_SUCCESS){
            PATA_ENDPOINT_DEVICE_OBJECT NewEndpoint = LouKeMallocType(ATA_ENDPOINT_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
            NewEndpoint->Port = AtaPort;
            NewEndpoint->ChannelDev = i;

            if(PacketDevice){
                AtaCoreParsePacketDeviceInformation(Identify, NewEndpoint);
            }else{
                //TODO: finish the normal ATA Devices
                LouKeFree(Identify->PioDataIn);
            }

            LouPrint("YAY!!! Command Completed Successfully\n", Identify->CommandStatus);
            while(1);
        }
    }
    LouPrint("Done Scanning Port\n");
}

LOUSTATUS AtaCoreRegisterAtaPorts(PATA_HOST_DEVICE_OBJECT HostDevice){
    SIZE i;
    PATA_PORT_DEVICE_OBJECT TmpPort;
    LOUSTATUS Status;
    ForEachAtaPort(HostDevice, TmpPort, i){
        Status = AtaCoreAllocatePortListEntry(TmpPort);
        if(Status != STATUS_SUCCESS){
            goto _ERROR_CREATING_LIST;
        }
    }

    ForEachAtaPort(HostDevice, TmpPort, i){
        if(TmpPort->Operations->AtaPortDeviceReset){
            Status = TmpPort->Operations->AtaPortDeviceReset(TmpPort);
            if(Status != STATUS_SUCCESS){
                continue;
            }
        }
        if(TmpPort->Operations->AtaPortDeviceStart){
            Status = TmpPort->Operations->AtaPortDeviceStart(TmpPort);
            if(Status != STATUS_SUCCESS){
                continue;
            }
        }
        
        AtaCoreProbePortForDevice(TmpPort);
    }

    LouPrint("ATACORE.SYS:AtaCoreRegisterAtaPorts()\n");
    while(1);
    return STATUS_SUCCESS;

_ERROR_CREATING_LIST:
    ForEachAtaPort(HostDevice, TmpPort, i){
        AtaCoreFreePortListEntry(TmpPort);
    }
    return Status;
}