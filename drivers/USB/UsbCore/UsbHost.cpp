//Copyright GPL-2 Tyler Grenier (2025 - 2026)

#include "UsbCore.h"

LOUSTATUS UsbCoreCreateHcdObject(
    PPCI_DEVICE_OBJECT  PDEV,
    ULONG               Flags,
    PVOID               PrivateData,
    PUSB_HCD_OPERATIONS Operations
){
    PUSB_HCD_OBJECT NewHcdObject;
    LOUSTATUS Status;
    if(!Operations){
        return STATUS_INVALID_PARAMETER;
    }
    NewHcdObject = LouKeMallocType(USB_HCD_OBJECT, KERNEL_GENERIC_MEMORY);
    if(!NewHcdObject){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    NewHcdObject->PDEV = PDEV;
    NewHcdObject->HcdFlags = Flags;
    NewHcdObject->HcdPrivateData = PrivateData;
    NewHcdObject->Operations = Operations;

    if(Operations->ResetHcdDevice){
        Status = Operations->ResetHcdDevice(NewHcdObject);
        if(Status != STATUS_SUCCESS){
            LouKeFree(NewHcdObject);
            return Status;
        }
    }

    if(Operations->StartHcdDevice){
        Status = Operations->StartHcdDevice(NewHcdObject);
        if(Status != STATUS_SUCCESS){
            LouKeFree(NewHcdObject);
            return Status;
        }
    }
    return STATUS_SUCCESS;
}


/*
#include "UsbCore.h"


//USB_HOST_DEVICE

DRIVER_EXPORT
LOUSTATUS LouKeUsbAddHcd(
    PUSB_HOST_DEVICE    HostDevice
){  
    LouPrint("LouKeUsbAddHcd()\n");

    if(HostDevice->Operations.UsbHcdStopHostController){
        LouPrint("Stopping Usb Host Controller\n");
        HostDevice->Operations.UsbHcdStopHostController(HostDevice);
    }

    if(HostDevice->Operations.UsbHcdResetHostController){
        LouPrint("Resetting Usb Host Controller\n");
        HostDevice->Operations.UsbHcdResetHostController(HostDevice);
    }    

    if(HostDevice->Operations.UsbHcdStartHostController){
        LouPrint("Starting Usb Host Controller\n");
        HostDevice->Operations.UsbHcdStartHostController(HostDevice);
    }

    if(HostDevice->Operations.UsbHcdProbeRootHub){
        LouPrint("Probing Usb Controller Root Hub\n");
        HostDevice->Operations.UsbHcdProbeRootHub(HostDevice);
    }

    LouPrint("LouKeUsbAddHcd() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
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
*/