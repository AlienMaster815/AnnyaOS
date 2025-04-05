#include "ehci.h"
#include <Hal.h>

uint64_t LouKeGetLdmModuleDeviceID(PPCI_COMMON_CONFIG Config, PLOUSINE_PCI_DEVICE_TABLE DeviceTable);

#define INTEL_QUARK_X1000   ((((PPCI_COMMON_CONFIG)PDEV->CommonConfig)->VendorID == PCI_VENDOR_ID_INTEL) && (((PPCI_COMMON_CONFIG)PDEV->CommonConfig)->DeviceID == 0x0939))

void EhciInterruptHandler(uint64_t HcdHandle){

    LouPrint("Hello EHCI Interrupt World\n");
    while(1);
}

//Ehci Setup
LOUSTATUS EhciReset(PUSB_HOST_CONTROLER_DEVICE Hcd){

    return STATUS_SUCCESS;
}

//Ehci run
LOUSTATUS EhciStart(PUSB_HOST_CONTROLER_DEVICE Hcd){

    return STATUS_SUCCESS;
}

//Ehci Stop
void EhciHaltHcdExecution(PUSB_HOST_CONTROLER_DEVICE Hcd){

}

//ehci Shutdown
void EhciShutdownHcd(PUSB_HOST_CONTROLER_DEVICE Hcd){

}

LOUSTATUS EhciHcdQueueUrb(PUSB_HOST_CONTROLER_DEVICE Hcd, PURB Urn, uint64_t MemoryFlags){

    return STATUS_SUCCESS;
}

LOUSTATUS EhciHcdUnQueue(PUSB_HOST_CONTROLER_DEVICE Hcd, PURB Urb, LOUSTATUS* Status){

    return STATUS_SUCCESS;
}


UNUSED static USB_HOST_CONTROLER_DRIVER EhciHostDriver = {
    .DeviceDescription = "EHCI PCI HOST",
    .ProductDescriptor = "EHCI Host Controller",
    .HcdPrivateSize = sizeof(EHCI_HOST_CONTROLLER_DRIVER),
    .InterruptHandler = EhciInterruptHandler,
    .DriverFlags = HCD_MEMORY | HCD_DMA | HCD_USB2_0 | HCD_BH,
    .ResetHcd = EhciReset,
    .StartHcd = EhciStart,
    .HaltHcdExecution = EhciHaltHcdExecution,
};

UNUSED static LOUSINE_PCI_DEVICE_TABLE EhciBypassTable[] = {
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x0811, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0x0829, .SimpleEntry = true},
    {.VendorID = PCI_VENDOR_ID_INTEL, .DeviceID = 0xE006, .SimpleEntry = true},
    {0},
};


static bool IsBypassedDevice(P_PCI_DEVICE_OBJECT PDEV){
    uint64_t Id = LouKeGetLdmModuleDeviceID((PPCI_COMMON_CONFIG)PDEV->CommonConfig, EhciBypassTable);
    if(Id >= 3) return false;
    return true;
}

LOUSTATUS LoUSBDeInitializeHostController(P_PCI_DEVICE_OBJECT PDEV, PUSB_HOST_CONTROLER_DRIVER HostDriver);
LOUSTATUS LoUSBInitializeHostController(P_PCI_DEVICE_OBJECT PDEV, PUSB_HOST_CONTROLER_DRIVER HostDriver);

//static void RestEhciDriverData(){
//    LouPrint("Resetting EHCI Driver Data\n");



//    LouPrint("Done Resseting EHCI Driver Data\n");
//}




void InitializeEhciDevice(P_PCI_DEVICE_OBJECT PDEV){
    LouPrint("Initializing EHCI Device\n");
    //we first need to know if this LoUSB subse will drive the chip
    if(IsBypassedDevice(PDEV)){
        return;
    }

    if(!NT_SUCCESS(LoUSBInitializeHostController(PDEV, &EhciHostDriver))){
        LoUSBDeInitializeHostController(PDEV, &EhciHostDriver);
    }

    LouPrint("Initializing EHCI Device STATUS_SUCCES\n");
    while(1);
}