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

void AtaCoreProbePortForDevice(PATA_PORT_DEVICE_OBJECT AtaPort){
    PATA_HOST_DEVICE_OBJECT HostDevice = AtaPort->HostDevice;
    MutexLock(AtaPort->ChannelLock);
    PATA_COMMAND_PACKET Identify = LouKeMallocType(ATA_COMMAND_PACKET, KERNEL_GENERIC_MEMORY);
    LOUSTATUS Status;
    Identify->CommandFlags = ATA_COMMAND_PACKET_FLAGS_TRAN_CMD | ATA_COMMAND_PACKET_FLAGS_POLL; 
    LouKeSetAtomicBoolean(&Identify->CommandDone, 0);
    Identify->PioDataIn = LouKeMallocEx(256 * sizeof(UINT16), GET_ALIGNMENT(UINT16), KERNEL_GENERIC_MEMORY);
    AtaCoreEncodeIdentifyDeviceCommand((PATA_COMMAND_IDENTIFY_DEVICE_STRUCTURE)&Identify->Packet, 0);

    if(AtaPort->Operations->AtaPortDevicePrepCommand){
        Status = AtaPort->Operations->AtaPortDevicePrepCommand(AtaPort, Identify);
    }

    LouKeListAddTail(&Identify->FifoChain, &AtaPort->CommandList);

    MutexUnlock(AtaPort->ChannelLock);

    while(!LouKeGetAtomicBoolean(&Identify->CommandDone)){
        sleep(10);
    }

    LouPrint("YAY!!! Command Completed\n");
    while(1);
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