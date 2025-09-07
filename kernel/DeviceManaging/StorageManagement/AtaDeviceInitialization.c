#include <LouAPI.h>

typedef struct _ATA_HOST_DEVICE_LIST{
    ListHeader                      Neighbors;
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHostDevices;
}ATA_HOST_DEVICE_LIST, * PATA_HOST_DEVICE_LIST;

static size_t                   AtaHostDeviceCount = 0;
static ATA_HOST_DEVICE_LIST     AtaHostDeviceList;

LOUSTATUS LouRegisterStorageDevice(
    PDEVICE_DIRECTORY_TABLE Table
);

LOUSTATUS LouKeAtaSendAtaIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort,
    void* IdBuffer
);
 
LOUSTATUS LouKeAtaSendAtapiIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT  AtapiPort,
    void*                           IdBuffer
);

uint8_t LouKeAtaGetDeviceType(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtapiPort);

LOUSTATUS LouKeAtaSendAtaIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort,
    void* IdBuffer
);

LOUSTATUS DeviceManagerInitializeAtaPortDevice(PDEVICE_DIRECTORY_TABLE PortTable){
    UNUSED PLOUSINE_KERNEL_DEVICE_ATA_PORT PortToInitialize = PortTable->KeyData;
    LOUSTATUS Status = STATUS_SUCCESS;

    if(!PortToInitialize->DeviceAttached){
        PortToInitialize->PortFunctioning = false;
        return STATUS_SUCCESS;
    }
    
    void* AtaIdBuffer;
    if(PortToInitialize->PortScsiDevice){
        PortToInitialize->PortFunctioning = true;
        return STATUS_SUCCESS;
    }else{
        AtaIdBuffer = LouKeMalloc(512, USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
        Status = LouKeAtaSendAtaIdentifyCommand(
            PortToInitialize,
            AtaIdBuffer
        );
        LouKeFree(AtaIdBuffer);
        if(Status != STATUS_SUCCESS){
            PortToInitialize->PortFunctioning = false;
            return Status;
        }
        else{
            PortToInitialize->PortFunctioning = true;
        }
    }

    LouPrint("Initialization Of ATA Port Successfull\n");
    return STATUS_SUCCESS;
}

LOUSTATUS DeviceManagerInitializeAtaHostDevice(PDEVICE_DIRECTORY_TABLE DeviceDirectoryTable){
    LouPrint("Lousine Kernel Device Manager Initializing ATA Host Device\n");
    
    PATA_HOST_DEVICE_LIST TmpHostList = &AtaHostDeviceList;

    //Run Through the Host List And Allocate A Host For The Next Time This Function Used
    for(size_t i = 0 ; i <= AtaHostDeviceCount; i++){
        if(TmpHostList->Neighbors.NextHeader){
            TmpHostList = (PATA_HOST_DEVICE_LIST)TmpHostList->Neighbors.NextHeader;
        }else {
            TmpHostList->Neighbors.NextHeader = (PListHeader)LouKeMallocType(ATA_HOST_DEVICE_LIST, KERNEL_GENERIC_MEMORY);
        }
    }
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)DeviceDirectoryTable->KeyData;
    TmpHostList->AtaHostDevices = AtaHost;
    

    for(uint8_t i = 0 ; i < AtaHost->PortCount; i++){
        LouPrint("Registering Ata Port To Device Manager\n");
        PDEVICE_DIRECTORY_TABLE PortTable = (PDEVICE_DIRECTORY_TABLE)LouKeMallocType(DEVICE_DIRECTORY_TABLE, KERNEL_GENERIC_MEMORY);
        *PortTable = *DeviceDirectoryTable;
        PortTable->KeyData = &AtaHost->Ports[i];
        PortTable->DevicePrivateData = &AtaHost->Ports[i];
        if(DeviceManagerInitializeAtaPortDevice(PortTable) != STATUS_SUCCESS){
            LouKeFree(PortTable);
            continue;
        }
        LouRegisterStorageDevice(PortTable);
    }
    return STATUS_SUCCESS;
}