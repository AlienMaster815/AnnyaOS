#include "LsiLogic.h"
 

static LOUSTATUS Lsi53c1030ScsiDeviceResetHcd(PSCSI_HOST_DEVICE_OBJECT Hcd){


    return STATUS_SUCCESS;
}

static LOUSTATUS Lsi53c1030ScsiDevicePowerOnHcd(PSCSI_HOST_DEVICE_OBJECT Hcd){

    return STATUS_SUCCESS;
}

static LOUSTATUS Lsi53c1030ScsiDevicePowerOffHcd(PSCSI_HOST_DEVICE_OBJECT Hcd){

    return STATUS_NOT_SUPPORTED;
}

static LOUSTATUS Lsi53c1030ScsiDeviceSendScsiCommand(
    PSCSI_PORT_DEVICE_OBJECT    ScsiPortDevice, 
    PSCSI_COMMAND_PACKET        ScsiCommandPacket
){



    return STATUS_NOT_SUPPORTED;
}

static LOUSTATUS Lsi53c1030ScsiDevicePrepScsiCommand(
    PSCSI_PORT_DEVICE_OBJECT    ScsiPortDevice, 
    PSCSI_COMMAND_PACKET        ScsiCommandPacket
){



    return STATUS_NOT_SUPPORTED;
}

static SCSI_HOST_DEVICE_CALLBACKS Lsi53c1030DriverCallbacks = {
    .ScsiDeviceResetHcd = Lsi53c1030ScsiDeviceResetHcd,
    .ScsiDevicePowerOnHcd = Lsi53c1030ScsiDevicePowerOnHcd,
    .ScsiDevicePowerOffHcd = Lsi53c1030ScsiDevicePowerOffHcd,
    .ScsiDeviceSendScsiCommand = Lsi53c1030ScsiDeviceSendScsiCommand,
    .ScsiDevicePrepScsiCommand = Lsi53c1030ScsiDevicePrepScsiCommand,
};

static SCSI_HOST_DEVICE_DRIVER_OBJECT Lsi53c1030DriverObject = {
    .DriverName = "LSI53C1030 Scsi Host Adapter Driver",
    .Callbacks = &Lsi53c1030DriverCallbacks,
};
 
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
    PDEVICE_OBJECT PlatformDevice
){
    LouPrint("LSI_SCSI.SYS::AddDevice()\n");
    PSCSI_HOST_DEVICE_OBJECT ScsiDevice;
    PPCI_DEVICE_OBJECT PDEV = PciHalGetPciDeviceObjectFromLdmDeviceObject(PlatformDevice);
    uint8_t DeviceID = PDEV->DeviceID;

    //LouPrint("Pci Device ID:%d\n", DeviceID);

    LouPrint("PCI-SCSI VendorID:%h\n", PciHalGetVendorId(PDEV));
    LouPrint("PCI-SCSI DeviceID:%h\n", PciHalGetDeviceId(PDEV));

    LOUSTATUS Status = ScsiCoreCreateScsiHostDeviceObject(
        &Lsi53c1030DriverObject,
        PlatformDevice,
        &ScsiDevice
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("LSI_SCSI.SYS::AddDevice():Unable To Create Scsi Device Object\n");
        goto _ERROR_OUT;
    }

    LouPrint("LSI_SCSI.SYS::AddDevice() STATUS_SUCCESS\n");
    while(1);
    _ERROR_OUT:
    LouPrint("LSI_SCSI.SYS::AddDevice() ERROR\n");
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

    LOUSTATUS Status = ScsiCoreRegisterScsiHostDeviceDriver(
        &Lsi53c1030DriverObject,
        0, 0
    );    
    if(Status != STATUS_SUCCESS){
        LouPrint("LSI_SCSI.SYS::DriverEntry:ERROR Unable To Register Scsi Host Driver\n");
        goto _OUT_ERROR;
    }

    Status = PciHalRegisterLousinePciDeviceTable(DriverObject, SupportedPciDevices);
    if(Status != STATUS_SUCCESS){
        LouPrint("LSI_SCSI.SYS::DriverEntry():ERROR Unable To Register Pci Device Table\n");
        goto _OUT_ERROR;
    }

    LouPrint("LSI_SCSI.SYS::DriverEntry() STATUS_SUCCESS\n");
    _OUT_ERROR:
    return Status;
}

