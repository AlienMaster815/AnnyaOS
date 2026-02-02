#include "PIIX.h"

static LOUSINE_PCI_DEVICE_TABLE PiixPciDeviceTable[] = {
    //PATA Devices
    {.VendorID = 0x8086, .DeviceID = 0x7010 , .BoardID = PIIX_CONTROLLER_ID_PATA_MWDMA, .SimpleEntry = true},
    //{.VendorID = 0x8086, .DeviceID = 0x7111 , .SubVendorID = 0x15AD, .SubDeviceID = 0x1976, .BoardID = PIIX_CONTROLLER_ID_VMWARE, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7111 , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {0},
};

void UnloadDriver(PDRIVER_OBJECT Driver){

}

LOUSTATUS PiixInitializePiix3Xceleration(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);
LOUSTATUS PiixInitializePiix4Xceleration(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);

LOUDDK_API_ENTRY
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, struct _DEVICE_OBJECT* PlatformDevice){
    LouPrint("PIIX.SYS:AddDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    LOUSTATUS Status;

    Status = InitializeGenericAtaDevice(PDEV);

    uint8_t DeviceID = PlatformDevice->DeviceID;
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = LouKeDeviceManagerGetAtaDevice(PDEV);

    if(!AtaHost){
        LouPrint("PIIX.SYS:Error Controller Not In Ata Manager\n");
        return STATUS_NO_SUCH_DEVICE;
    }

    Status = LouKeHalEnablePciDevice(PDEV);
    if(Status != STATUS_SUCCESS){
        return (NTSTATUS)Status;
    }

    if(PiixPciDeviceTable[DeviceID].BoardID == PIIX_CONTROLLER_ID_PATA_MWDMA){
        Status = PiixInitializePiix3Xceleration(AtaHost);
    }else if(PiixPciDeviceTable[DeviceID].BoardID == PIIX_CONTROLLER_ID_PATA_33){
        Status = PiixInitializePiix4Xceleration(AtaHost);
        while(1);
    }else {
        Status = STATUS_NO_SUCH_DEVICE;
    }

    if(Status != STATUS_SUCCESS){
        LouPrint("PIIX.SYS:Error Unable To Initialize Acceleration\n");
        return Status;
    }

    LouPrint("PIIX.SYS:AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){

    LouPrint("PIIX.SYS:DriverEntry()\n");
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

    LouPrint("PIIX.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}