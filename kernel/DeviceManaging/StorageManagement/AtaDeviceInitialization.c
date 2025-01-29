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

LOUSTATUS DeviceManagerInitializeAtaPortDevice(PDEVICE_DIRECTORY_TABLE PortTable){
    UNUSED PLOUSINE_KERNEL_DEVICE_ATA_PORT PortToInitialize = PortTable->KeyData;
    LOUSTATUS Status = STATUS_SUCCESS;
    if(!PortToInitialize->Operations){
        LouPrint("ERROR: Port Has No Or Invalid Operations\n");
        return STATUS_UNSUCCESSFUL;
    }
    if(!PortToInitialize->Operations->IssueCommand){
        LouPrint("ERROR: Port Does Not Have A Issue Command\n");
        return STATUS_UNSUCCESSFUL;
    }

    void* IdBuffer = LouKeMalloc(512, WRITEABLE_PAGE | PRESENT_PAGE | UNCACHEABLE_PAGE);

    if(PortToInitialize->PortScsiDevice){
       Status = LouKeAtaSendAtapiIdentifyCommand(PortToInitialize, IdBuffer);
    }

    LouPrint("Initialization Of ATA Port Successfull\n");

    while(1);
    return Status;
}

LOUSTATUS DeviceManagerInitializeAtaHostDevice(PDEVICE_DIRECTORY_TABLE DeviceDirectoryTable){
    LouPrint("Lousine Kernel Device Manager Initializing ATA Host Device\n");

    PATA_HOST_DEVICE_LIST TmpHostList = &AtaHostDeviceList;

    //Run Through the Host List And Allocate A Host For The Next Time This Function Used
    for(size_t i = 0 ; i <= AtaHostDeviceCount; i++){
        if(TmpHostList->Neighbors.NextHeader){
            TmpHostList = (PATA_HOST_DEVICE_LIST)TmpHostList->Neighbors.NextHeader;
        }else {
            TmpHostList->Neighbors.NextHeader = (PListHeader)LouMalloc(sizeof(ATA_HOST_DEVICE_LIST));
        }
    }
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)DeviceDirectoryTable->KeyData;
    TmpHostList->AtaHostDevices = AtaHost;
    
    LOUSTATUS Result = STATUS_SUCCESS;

    for(uint8_t i = 0 ; i < AtaHost->PortCount; i++){
        LouPrint("Registering Ata Port To Device Manager\n");
        PDEVICE_DIRECTORY_TABLE PortTable = (PDEVICE_DIRECTORY_TABLE)LouMalloc(sizeof(DEVICE_DIRECTORY_TABLE));
        *PortTable = *DeviceDirectoryTable;
        PortTable->KeyData = &AtaHost->Ports[i];
        PortTable->DevicePrivateData = &AtaHost->Ports[i];
        //Result = DeviceManagerInitializeAtaPortDevice(PortTable);
        //if(Result != STATUS_SUCCESS){
        //    return Result;
        //}
        Result = LouRegisterStorageDevice(PortTable);
        if(Result != STATUS_SUCCESS){
            return Result;
        }
    }

    return Result;
}