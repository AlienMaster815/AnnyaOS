#include <LouAPI.h>

static uint32_t NumberOfAtaDevices = 0x00;

typedef struct _ATA_DEVICE_MANAGER_DATA{
    uint32_t RegisteredDeviceNumber;
    bool IsUsingDma;
}ATA_DEVICE_MANAGER_DATA, * PATA_DEVICE_MANAGER_DATA;

LOUSTATUS LouRegisterStorageDevice(
    PDEVICE_DIRECTORY_TABLE Table
);


bool read(void *Vport, uint32_t startl, uint32_t starth, uint32_t count, uint16_t *buf, uint8_t Command);

bool InitializeAtaDevice(

) {
    return false;
}

LOUSTATUS LouRegisterAtaDeviceToInformationTable(
    PDEVICE_DIRECTORY_TABLE Table,
    P_PCI_DEVICE_OBJECT PDEV, 
    SYSTEM_DEVICE_IDENTIFIER Sdi,
    string LRE, //optional
    void* KeyData, //optional
    void* DevicePrivateData
){
    LOUSTATUS Status = STATUS_SUCCESS;
    LouPrint("Registering ATA Device\n");


    
    NumberOfAtaDevices++;
    return Status;
}
