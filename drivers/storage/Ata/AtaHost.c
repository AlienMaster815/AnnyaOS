#include "AtaCore.h"

typedef struct _ATA_HOST_LIST_ENTRY{
    ListHeader              Peers;
    PATA_HOST_DEVICE_OBJECT HostDevice;
}ATA_HOST_LIST_ENTRY, * PATA_HOST_LIST_ENTRY;

static mutex_t      HostListLock = {0};
static ListHeader   HostList = {0};


static LOUSTATUS AtaCoreAllocateHostListEntry(PATA_HOST_DEVICE_OBJECT HostDevice){
    PATA_HOST_LIST_ENTRY NewEntry = LouKeMallocType(ATA_HOST_LIST_ENTRY, KERNEL_GENERIC_MEMORY);
    if(!NewEntry){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    NewEntry->HostDevice = HostDevice;
    MutexLock(&HostListLock);
    LouKeListAddTail(&NewEntry->Peers , &HostList);
    MutexUnlock(&HostListLock);
    return STATUS_SUCCESS;
}

static void AtaCoreFreeHostListEntry(PATA_HOST_DEVICE_OBJECT HostDevice){
    PATA_HOST_LIST_ENTRY TmpEntry = 0x00, SafeEntry = 0x00, WantedEntry = 0x00;
    MutexLock(&HostListLock);
    ForEachListEntrySafe(TmpEntry, SafeEntry, &HostList, Peers){
        if(TmpEntry->HostDevice == HostDevice){
            WantedEntry = TmpEntry;
            break;
        }
    }
    if(WantedEntry){
        LouKeListDeleteItem(&WantedEntry->Peers);
    }
    MutexUnlock(&HostListLock);
    if(WantedEntry){
        LouKeFree(WantedEntry);
    }
}

DRIVER_EXPORT void AtaCoreFreeHostDevice(PATA_HOST_DEVICE_OBJECT HostDevice){
    if(!HostDevice){
        return;
    }
    if(HostDevice->HostPrivateData){
        LouKeFree(HostDevice->HostPrivateData);
    }
    LouKeFree(HostDevice);
}

DRIVER_EXPORT LOUSTATUS AtaCoreAllocateHostDevice(
    PATA_HOST_DEVICE_OBJECT*    HostDeviceOut,
    SIZE                        PrivateDataSize,
    SIZE                        PrivateDataAlignment
){
    PATA_HOST_DEVICE_OBJECT NewDeviceObject = LouKeMallocType(ATA_HOST_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
    if(!NewDeviceObject){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    if(PrivateDataSize){
        PVOID PrivateData = LouKeMallocEx(PrivateDataSize, PrivateDataAlignment, KERNEL_GENERIC_MEMORY);
        if(!PrivateData){
            AtaCoreFreeHostDevice(NewDeviceObject);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        NewDeviceObject->HostPrivateData = PrivateData;
    }
    return STATUS_SUCCESS;
}



DRIVER_EXPORT LOUSTATUS AtaCoreRegisterAtaHostDevice(PATA_HOST_DEVICE_OBJECT NewHostDevice){
    LOUSTATUS Status = AtaCoreAllocateHostListEntry(NewHostDevice);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if(NewHostDevice->Operations->AtaHostDeviceReset){
        Status = NewHostDevice->Operations->AtaHostDeviceReset(NewHostDevice);
        if(Status != STATUS_SUCCESS){
            goto _REGISTER_ERROR_REMOVE_ENTRY;
        }
    }

    if(NewHostDevice->Operations->AtaHostDeviceStart){
        Status = NewHostDevice->Operations->AtaHostDeviceStart(NewHostDevice);
        if(Status != STATUS_SUCCESS){
            goto _REGISTER_ERROR_REMOVE_ENTRY;
        }
    }

    NewHostDevice->PortIoManager = LouKeMallocArray(PTHREAD, NewHostDevice->PortCount, KERNEL_GENERIC_MEMORY);
    for(SIZE i = 0; i < NewHostDevice->PortCount; i++){
        NewHostDevice->PortIoManager[i] = LouKeCreateDemon(
            AtaCorePortIoQueueManager,
            &NewHostDevice->PortDevices[i],
            8 * KILOBYTE,
            31
        );
    }

    Status = AtaCoreRegisterAtaPorts(NewHostDevice);
    if(Status != STATUS_SUCCESS){
        goto _REGISTER_ERROR_STOP_CONTROLLER; 
    }
    return STATUS_SUCCESS;

_REGISTER_ERROR_STOP_CONTROLLER:
    if(NewHostDevice->Operations->AtaHostDeviceStop){
        NewHostDevice->Operations->AtaHostDeviceStop(NewHostDevice);
    }
_REGISTER_ERROR_REMOVE_ENTRY:
    AtaCoreFreeHostListEntry(NewHostDevice);
    return Status;
}