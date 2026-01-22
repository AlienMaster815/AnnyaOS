#include <LouAPI.h>

static size_t NumberOfStorageDevice = 0x00;

typedef struct _STORAGE_DEVICE_MANAGER_DATA{
    ListHeader                  Neighbors;
    PDEVICE_DIRECTORY_TABLE     Table;
}STORAGE_DEVICE_MANAGER_DATA, * PSTORAGE_DEVICE_MANAGER_DATA;

static STORAGE_DEVICE_MANAGER_DATA StorageDevices = {0};

static spinlock_t StorgaeDeviceManagerLock = {0};

LOUSTATUS LouRegisterStorageDevice(
    PDEVICE_DIRECTORY_TABLE Table
){
    LouPrint("Registering Storage Device\n");
    PSTORAGE_DEVICE_MANAGER_DATA TmpStorageDrivers = &StorageDevices;
    LouKIRQL Irql;
    PListHeader NewTrack = (PListHeader)LouKeMallocType(STORAGE_DEVICE_MANAGER_DATA, KERNEL_GENERIC_MEMORY);;
    LouKeAcquireSpinLock(&StorgaeDeviceManagerLock, &Irql);
    while(TmpStorageDrivers->Neighbors.NextHeader){
        TmpStorageDrivers = (PSTORAGE_DEVICE_MANAGER_DATA)TmpStorageDrivers->Neighbors.NextHeader;
    }
    TmpStorageDrivers->Neighbors.NextHeader = NewTrack;
    TmpStorageDrivers = (PSTORAGE_DEVICE_MANAGER_DATA)TmpStorageDrivers->Neighbors.NextHeader;

    TmpStorageDrivers->Table = Table;
    NumberOfStorageDevice++;
    LouKeReleaseSpinLock(&StorgaeDeviceManagerLock, &Irql);
    return STATUS_SUCCESS;
}

SYSTEM_DEVICE_IDENTIFIER LouKeGetStorageDeviceSystemIdentifier(uint8_t DriveNumber){
    PSTORAGE_DEVICE_MANAGER_DATA TmpStorageDrivers = (PSTORAGE_DEVICE_MANAGER_DATA)StorageDevices.Neighbors.NextHeader;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&StorgaeDeviceManagerLock, &Irql);
    for(size_t i = 0 ; i < DriveNumber; i++){
        TmpStorageDrivers = (PSTORAGE_DEVICE_MANAGER_DATA)TmpStorageDrivers->Neighbors.NextHeader;
    }
    LouKeReleaseSpinLock(&StorgaeDeviceManagerLock, &Irql);
    return TmpStorageDrivers->Table->Sdi;
}

PLOUSINE_KERNEL_DEVICE_ATA_PORT LouKeGetAtaStoragePortObject(uint8_t DriveNumber){
    PSTORAGE_DEVICE_MANAGER_DATA TmpStorageDrivers = (PSTORAGE_DEVICE_MANAGER_DATA)StorageDevices.Neighbors.NextHeader;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&StorgaeDeviceManagerLock, &Irql);
    for(size_t i = 0 ; i < DriveNumber; i++){
        TmpStorageDrivers = (PSTORAGE_DEVICE_MANAGER_DATA)TmpStorageDrivers->Neighbors.NextHeader;
    }
    LouKeReleaseSpinLock(&StorgaeDeviceManagerLock, &Irql);
    return TmpStorageDrivers->Table->DevicePrivateData;
}

uint8_t LouKeGetNumberOfStorageDevices(){
    return NumberOfStorageDevice;
}