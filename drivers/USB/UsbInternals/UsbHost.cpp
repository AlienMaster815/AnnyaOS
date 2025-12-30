#include <LouDDK.h>
#include <usb.h>

//USB_HOST_DEVICE

LOUDDK_API_ENTRY
LOUSTATUS LouKeUsbAddHcd(
    PUSB_HOST_DEVICE    HostDevice
){  
    LouPrint("LouKeUsbAddHcd()\n");

    if(HostDevice->Operations.UsbHcdStopHostController){
        HostDevice->Operations.UsbHcdStopHostController(HostDevice);
    }

    if(HostDevice->Operations.UsbHcdResetHostController){
        LouPrint("Reseting Usb Host Controller\n");
        HostDevice->Operations.UsbHcdResetHostController(HostDevice);
    }    

    if(HostDevice->Operations.UsbHcdStartHostController){
        HostDevice->Operations.UsbHcdStartHostController(HostDevice);
    }

    if(HostDevice->Operations.UsbHcdProbeRootHub){
        LouPrint("Probing Usb Controller Root Hub\n");
        HostDevice->Operations.UsbHcdProbeRootHub(HostDevice);
    }

    LouPrint("LouKeUsbAddHcd() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeUsbAddDeviceToHcd(
    PUSB_HOST_DEVICE        HostDevice,
    PUSB_FUNCTION_DEVICE    ParrentFunction,
    PUSB_FUNCTION_DEVICE    DeviceDescription
){
    LouPrint("LouKeUsbAddDeviceToHcd()\n");
    if((!HostDevice) || (!DeviceDescription)){
        LouPrint("LouKeUsbAddDeviceToHcd() EINVAL\n");
        return STATUS_INVALID_PARAMETER;
    }
    else if(!ParrentFunction){ //use root be default
        ParrentFunction = &HostDevice->RootHub.FunctionDevice;
    }
    MutexLock(&HostDevice->RootHubMutex);

    if(!ParrentFunction->Children){
        ParrentFunction->Children = LouKeMallocType(USB_TOPOLOGY_TREE, KERNEL_GENERIC_MEMORY);
    }

    PUSB_TOPOLOGY_TREE Topology = ParrentFunction->Children;

    while(Topology->FLink){
        Topology = Topology->FLink;
    }

    Topology->FLink = LouKeMallocType(USB_TOPOLOGY_TREE, KERNEL_GENERIC_MEMORY);
    
    ((PUSB_TOPOLOGY_TREE)Topology->FLink)->BLink = Topology;
    Topology = Topology->FLink;

    Topology->ULink = CONTAINER_OF(ParrentFunction, USB_TOPOLOGY_TREE, FunctionDevice);    

    Topology->HostIdentifier = HostDevice;

    Topology->FunctionDevice = *DeviceDescription;

    if(Topology->FunctionDevice.Operations.UsbInitializeFunctionDevice){
        Topology->FunctionDevice.Operations.UsbInitializeFunctionDevice(&Topology->FunctionDevice);
    }

    MutexUnlock(&HostDevice->RootHubMutex);
    LouPrint("LouKeUsbAddDeviceToHcd() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}