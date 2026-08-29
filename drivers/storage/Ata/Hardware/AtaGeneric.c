#include "AtaIdeGeneric.h"

#define ATA_BOARD_ID_ISA_DEVICE_NO_DMA      0
#define ATA_BOARD_ID_NATIVE_DEVICE_NO_DMA   1
#define ATA_BOARD_ID_ISA_DEVICE_HAS_DMA     2
#define ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA  3

LOUSTATUS AtaGenericPortDevicePrepCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){

    LouPrint("AtaGenericPortDevicePrepCommand()\n");
    while(1);
    return STATUS_SUCCESS;
}
    
LOUSTATUS AtaGenericPortDeviceIssueCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){

    LouPrint("AtaGenericPortDeviceIssueCommand()\n");
    while(1);
    return STATUS_SUCCESS;
}
    
LOUSTATUS AtaGenericPortDeviceCleanupCommand(PATA_PORT_DEVICE_OBJECT PortDevice, PATA_COMMAND_PACKET CommandPacket){

    LouPrint("AtaGenericPortDeviceCleanupCommand()\n");
    while(1);
    return STATUS_SUCCESS;
}

static ATA_PORT_OPERATIONS PortOperations = {
    .AtaPortDevicePrepCommand = AtaGenericPortDevicePrepCommand,
    .AtaPortDeviceIssueCommand = AtaGenericPortDeviceIssueCommand,
    .AtaPortDeviceCleanupCommand = AtaGenericPortDeviceCleanupCommand,
//    .AtaPortDeviceReset = AtaGenericPortDeviceReset,
//    .AtaPortDeviceStart = AtaGenericPortDeviceStart,
//    .AtaPortDeviceStop = AtaGenericPortDeviceStop,
//    .AtaPortDeviceWake = AtaGenericPortDeviceWake,
//    .AtaPortDeviceSleep = AtaGenericPortDeviceSleep,
//    .AtaPortDevicePowerUp = AtaGenericPortDevicePowerUp,
//    .AtaPortDevicePowerDown = AtaGenericPortDevicePowerDown,
};

static ATA_HOST_OPERATIONS AtaOperations = {
//    .AtaHostDeviceReset = AtaGenericHostDeviceReset,
//    .AtaHostDeviceStart = AtaGenericHostDeviceStart,
//    .AtaHostDeviceStop = AtaGenericHostDeviceStop,
//    .AtaHostDeviceWake = AtaGenericHostDeviceWake,
//    .AtaHostDeviceSleep = AtaGenericHostDeviceSleep,
//    .AtaHostDevicePowerUp = AtaGenericHostDevicePowerUp,
//    .AtaHostDevicePowerDown = AtaGenericHostDevicePowerDown,
};

static LOUSINE_PCI_DEVICE_TABLE AtaDevices[] = {
    //Generic ATA devices
    //NO DMA Devs
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x00, .BoardID = ATA_BOARD_ID_ISA_DEVICE_NO_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x05, .BoardID = ATA_BOARD_ID_NATIVE_DEVICE_NO_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x0A, .BoardID = ATA_BOARD_ID_ISA_DEVICE_NO_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x0F, .BoardID = ATA_BOARD_ID_NATIVE_DEVICE_NO_DMA, .GenericEntry = true},
    //DMA Devs
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x80, .BoardID = ATA_BOARD_ID_ISA_DEVICE_HAS_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x85, .BoardID = ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x8A, .BoardID = ATA_BOARD_ID_ISA_DEVICE_HAS_DMA, .GenericEntry = true},
    {.BaseClass = 0x01, .SubClass = 0x01, .ProgIf = 0x8F, .BoardID = ATA_BOARD_ID_NATIVE_DEVICE_HAS_DMA, .GenericEntry = true},
};

LOUSTATUS AddAtaDevice(
    PDRIVER_OBJECT DriverObject,
    struct _DEVICE_OBJECT* Device
){
    LouPrint("ATA.SYS:AddAtaDevice()\n");
  
    PPCI_DEVICE_OBJECT PDEV = PciHalGetPciDeviceObjectFromLdmDeviceObject(Device);
    SIZE BoardID = AtaDevices[PDEV->DeviceID].BoardID;

    LouPrint("ATA.SYS:BoardID:%d\n", (UINT64)BoardID);


    
    LouPrint("ATA.SYS:AddAtaDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS; //Status;
}


VOID AtaUnloadDriver(
    PDRIVER_OBJECT DriverObject
){
    LouPrint("ATA.SYS:AtaUnloadDriver()\n");
    //this is a dummy function due to the module
    //being built in there is nothing to unload
    LouPrint("ATA.SYS:AtaUnloadDriver() RETURN\n");
}

LOUAPI
LOUSTATUS 
DriverEntry(
    PDRIVER_OBJECT  DriverObject, 
    PUNICODE_STRING RegistryEntry
){
    LouPrint("ATA.SYS:DriverEntry()\n");

    //tell the System where are key Nt driver functions are
    DriverObject->DriverUnload = AtaUnloadDriver;
    DriverObject->DriverExtension->AddDevice = AddAtaDevice;

    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, AtaDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("ATA.SYS:DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }
    
    LouPrint("ATA.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}