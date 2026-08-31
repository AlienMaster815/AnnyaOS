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

    MutexUnlock(AtaPort->ChannelLock);
        
    while(!LouKeGetAtomicBoolean(&Identify->CommandDone)){
        sleep(10);
    }

    if(Identify->CommandStatus != STATUS_SUCCESS){
        LouKeFree(Identify->PioDataIn);
        return;
    }
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



            LouPrint("YAY!!! Command Completed Successfully\n", Identify->CommandStatus);
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