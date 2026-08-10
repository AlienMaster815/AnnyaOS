#define _KERNEL_MODULE_
#include <LouDDK.h>


UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedPciDevices[] = {
    {.VendorID = 0x1000, .DeviceID = 0x0030, .SimpleEntry = true},
    {0},
};

LOUAPI 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("LSI_SCSI.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("LSI_SCSI.SYS::UnloadDriver() STATUS_SUCCESS\n");
}


LOUSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    struct _DEVICE_OBJECT* PlatformDevice
){
    LouPrint("LSI_SCSI.SYS::AddDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PciHalGetPciDeviceObjectFromLdmDeviceObject(PlatformDevice);
    uint8_t DeviceID = PDEV->DeviceID;

    //LouPrint("Pci Device ID:%d\n", DeviceID);

    LouPrint("PCI-SCSI VendorID:%h\n", PciHalGetVendorId(PDEV));
    LouPrint("PCI-SCSI DeviceID:%h\n", PciHalGetDeviceId(PDEV));



    LouPrint("LSI_SCSI.SYS::AddDevice() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("LSI_SCSI.SYS::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;

    LOUSTATUS Status = PciHalRegisterLousinePciDeviceTable(DriverObject, SupportedPciDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("LSI_SCSI.SYS::DriverEntry():ERROR Unable To Register Pci Device Table\n");
    }

    LouPrint("LSI_SCSI.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

