
#include "PIIX.h"

static LOUSINE_PCI_DEVICE_TABLE PiixPciDeviceTable[] = {
    //PATA Devices
    {.VendorID = 0x8086, .DeviceID = 0x7010 , .BoardID = PIIX_CONTROLLER_ID_PATA_MWDMA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7111 , .SubVendorID = 0x15AD, .SubDeviceID = 0x1976, .BoardID = PIIX_CONTROLLER_ID_VMWARE, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7111 , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7199 , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7601 , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x84CA , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2421 , .BoardID = ICH_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2411 , .BoardID = ICH_CONTROLLER_ID_PATA_66, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x244A , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x244B , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x248A , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x248B , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24C1 , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24CA , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24CB , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24DB , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x245B , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x25A2 , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x266F , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2850 , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x27DF , .BoardID = ICH_CONTROLLER_ID_PATA_100_NO_MWDMA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x269E , .BoardID = ICH_CONTROLLER_ID_PATA_100_NO_MWDMA, .SimpleEntry = true},
    //SATA Devices
    {.VendorID = 0x8086, .DeviceID = 0x24D1 , .BoardID = ICH5_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24DF , .BoardID = ICH5_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x25A3 , .BoardID = ICH5_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x25B0 , .BoardID = ICH5_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2651 , .BoardID = ICH6_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2652 , .BoardID = ICH6_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x27C0 , .BoardID = ICH6_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2680 , .BoardID = ICH6_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2653 , .BoardID = ICH6M_CONTROLLER_ID_SATA, .SimpleEntry = true}, //simple entry because the maniges already handles the class
    {.VendorID = 0x8086, .DeviceID = 0x27C4 , .BoardID = ICH6M_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2820 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2825 , .BoardID = ICH8_2P_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2828 , .SubVendorID = 0x106B, .SubDeviceID = 0x00A0, .BoardID = ICH8M_APPLE_CONTROLLER_ID_SATA, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2828 , .SubVendorID = 0x106B, .SubDeviceID = 0x00A1, .BoardID = ICH8M_APPLE_CONTROLLER_ID_SATA, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2828 , .SubVendorID = 0x106B, .SubDeviceID = 0x00A3, .BoardID = ICH8M_APPLE_CONTROLLER_ID_SATA, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2828 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2920 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2921 , .BoardID = ICH8_2P_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2926 , .BoardID = ICH8_2P_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2928 , .BoardID = ICH8_2P_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x292E , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x5028 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x3A00 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x3A06 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x3A20 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {0},
};

LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("PIIX::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("PIIX::UnloadDriver() STATUS_SUCCESS\n");
}

LOUDDK_API_ENTRY
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT PlatformDevice){
    LouPrint("AddDevice()\n");
    P_PCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    uint8_t DeviceID = PlatformDevice->DeviceID;
    
    LouPrint("PDEV :%h\n", PDEV);
    LouPrint("DEVID:%d\n", DeviceID);



    LouPrint("AddDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){

    LouPrint("PIIX::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)PiixPciDeviceTable;

    LouPrint("PIIX::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}