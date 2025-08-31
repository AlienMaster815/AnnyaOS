#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "Xhci.h"
#include "XhciTrace.h"
#include "XhciPci.h"

UNUSED LOUSINE_PCI_DEVICE_TABLE SupportedXhciPciDevices[] = {
    {.BaseClass = 0x0C, .SubClass = 0x03, .BoardID = 0x00, .GenericEntry = true},
    {0},
};

LOUSTATUS 
XhciRun(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
){

    return STATUS_SUCCESS;
}

void 
XhciStop(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
){

}

void 
XhciShutdown(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
){

}

LOUSTATUS 
XhciQueueUrb(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    PURB                        Urb,
    UINT64                      PageFlags
){

    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciMapUrbDma(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    PURB                        Urb,
    UINT64                      PageFlags
){

    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciUnQueueUrb(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    PURB                        Urb,
    LOUSTATUS*                  Status
){

    return STATUS_SUCCESS;
}

void 
XhciUnmapUrbDma(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    PURB                        Urb
){

}

LOUSTATUS 
XhciMallocDevice(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    PUSB_DEVICE                 UsbDevice
){

    return STATUS_SUCCESS;
}

void 
XhciFreeDevice(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    PUSB_DEVICE                 UsbDevice
){

}

LOUSTATUS 
XhciMallocStreams(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice, 
    PUSB_HOST_ENDPOINT*         Endpoints, 
    uint32_t                    EndpointCount, 
    uint32_t                    StreamCount, 
    uint64_t                    MemoryFlags
){

    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciFreeStreams(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice, 
    PUSB_HOST_ENDPOINT*         Endpoints, 
    uint32_t                    EndpointCount, 
    uint32_t                    StreamCount, 
    uint64_t                    MemoryFlags
){

    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciAddEndpoint(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice, 
    PUSB_HOST_ENDPOINT          Endpoint
){

    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciDropEndpoint(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice, 
    PUSB_HOST_ENDPOINT          Endpoint
){

    return STATUS_SUCCESS;
}

void 
XhciDisableEndpoint(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_HOST_ENDPOINT          Endpoint
){

}

void 
XhciResetEndpoint(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_HOST_ENDPOINT          Endpoint
){

}

LOUSTATUS 
XhciCheckBandwidth(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE UsbDevice
){

    return STATUS_SUCCESS;
}

void 
XhciResetBandwidth(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice, 
    UINT64                      Timeout
){

}

LOUSTATUS 
XhciAddressDevice(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE UsbDevice, 
    uint64_t Timeout
){


        
    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciEnableDevice(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE UsbDevice
){

    return STATUS_SUCCESS;
}

LOUSTATUS
XhciUpdateHubDevice(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE UsbDevice
){

    return STATUS_SUCCESS;
}

LOUSTATUS
XhciResetDevice(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE UsbDevice
){

    return STATUS_SUCCESS;
}

int
XhciRequestFrameNumber(
    PUSB_HOST_CONTROLLER_DEVICE Hcd   
){

    return 0;
}

LOUSTATUS 
XhciHubControl(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    uint16_t RequestType, 
    uint16_t Value, 
    uint16_t Index, 
    string DataString, 
    uint16_t Length
){

    return STATUS_SUCCESS;
}

LOUSTATUS
XhciHubStatusData(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    string DataString
){

    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciResumeBus(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
){

    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciSuspendBus(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
){

    return STATUS_SUCCESS;
}

UINT32 
XhciRequestResumingPorts(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
){

    return 0x00;
}

LOUSTATUS 
XhciUpdateDevice(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice
){

    return STATUS_SUCCESS;
}

LOUSTATUS
XhciSetUsb2LowPowerMode(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice, 
    int                         PowerFlags
){

    return STATUS_SUCCESS;
}

LOUSTATUS
XhciEnableUsb3LowPowerModeTimeout(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice, 
    int                         PowerFlags
){

    return STATUS_SUCCESS;
}

void
XhciCtbComplete(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_HOST_ENDPOINT          Endpoint
){

}

LOUSTATUS 
XhciDisableUsb3LowPowerModeTimeout(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    PUSB_DEVICE                 UsbDevice, 
    int                         Usb3LinkState
){

    return STATUS_SUCCESS;
}

LOUSTATUS 
XhciSearchRawPortID(
    PUSB_HOST_CONTROLLER_DEVICE Hcd, 
    int                         PortID
){

    return STATUS_SUCCESS;
}



UNUSED static const USB_HOST_CONTROLLER_DRIVER HostControllerDriver = {
    .DeviceDescription              = "XHCI.SYS",
    .ProductDescriptor              = "XHCI Host Controller",
    .HcdPrivateSize                 = sizeof(XHCI_HCD),
    //.IntrNumber                   = //populated by initialization
    .DriverFlags                    = HCD_MEMORY | HCD_DMA | HCD_USB3_0 | HCD_SHARED | HCD_BH,
    //.ResetHcd                     = //populated by initialization
    .StartHcd                       = XhciRun,
    .HaltHcdExecution               = XhciStop, 
    .ShutdownHcd                    = XhciShutdown,
    .HcdRequestFrameNumber          = XhciRequestFrameNumber,
    .HcdQueueUrb                    = XhciQueueUrb,
    .HcdUnQueueUrb                  = XhciUnQueueUrb,
    .MapUrbToDma                    = XhciMapUrbDma,
    .UnmapUrbToDma                  = XhciUnmapUrbDma,
    .DisableEndpoint                = XhciDisableEndpoint,
    .ResetEndpoint                  = XhciResetEndpoint,
    .HubStatusData                  = XhciHubStatusData,
    .HubControl                     = XhciHubControl,
    .SuspendBus                     = XhciSuspendBus,
    .ResumeBus                      = XhciResumeBus,
    .RequestResumingPorts           = XhciRequestResumingPorts,
    .CtbComplete                    = XhciCtbComplete,
    .LouKeMallocDevice              = XhciMallocDevice,
    .LouKeFreeDevice                = XhciFreeDevice,
    .LouKeMallocStreams             = XhciMallocStreams,
    .LouKeFreeStreams               = XhciFreeStreams,
    .AddEndpoint                    = XhciAddEndpoint,
    .DropEndpoint                   = XhciDropEndpoint,
    .CheckBandwith                  = XhciCheckBandwidth,
    .ResetBandwith                  = XhciResetBandwidth,
    .AddressDevice                  = XhciAddressDevice,
    .EnableDevice                   = XhciEnableDevice,
    .UpdateHubDevice                = XhciUpdateHubDevice,
    .ResetDevice                    = XhciResetDevice,
    .UpdateDevice                   = XhciUpdateDevice,
    .SetUsb2LowPowerMode            = XhciSetUsb2LowPowerMode,
    .EnableUsb3LowPowerModeTimeout  = XhciEnableUsb3LowPowerModeTimeout,
    .DisableUsb3LowPowerModeTimeout = XhciDisableUsb3LowPowerModeTimeout,
    .SearchRawPortID                = XhciSearchRawPortID,
};





LOUDDK_API_ENTRY 
VOID UnloadDriver(PDRIVER_OBJECT DriverObject){
    LouPrint("XHCI.SYS::UnloadDriver()\n");
    //we have nothing to unload
    LouPrint("XHCI.SYS::UnloadDriver() STATUS_SUCCESS\n");
}


NTSTATUS AddDevice(
    PDRIVER_OBJECT DriverObject, 
    PDEVICE_OBJECT PlatformDevice
){
    LouPrint("XHCI.SYS::AddDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    PPCI_COMMON_CONFIG Config = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    LouPrint("XHCI Bar:%h\n", Config->BarBase[0]);

    LOUSTATUS Status = LouKeUsbHcdPciProbe(PDEV, &HostControllerDriver);
    
    if(Status != STATUS_SUCCESS){
        return (NTSTATUS)Status;
    }

    LouPrint("XHCI.SYS::AddDevice() STATUS_SUCCESS\n");

    while(1);
    return Status;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("XHCI.SYS::DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)SupportedXhciPciDevices;

    LouPrint("XHCI.SYS::DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}