//Copyright GPL-2 Tyler Grenier (2025 - 2026)

#include "UsbCore.h"

void UsbCoreHcdIoQueueManager(PVOID Params);
void UsbCoreHcdIoDeQueueManager(PVOID Params);


LOUSTATUS UsbCoreCreateDefaultUsbDeviceObject(PUSB_HCD_OBJECT HostObject);


static ListHeader   UsbHcdList = {0};
static mutex_t      UsbHcdListLock {0};

DRIVER_EXPORT
LOUSTATUS UsbCoreCreateHcdObject(
    PPCI_DEVICE_OBJECT  PDEV,
    ULONG               Flags,
    PVOID               PrivateData,
    PLOUSINE_DMA_DEVICE DmaDevice,
    PUSB_HCD_OPERATIONS Operations
){
    PUSB_HCD_OBJECT NewHcdObject;
    LOUSTATUS Status;
    if((!Operations) || (!DmaDevice)){
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
    NewHcdObject->DeviceAddresses = LouKeCreateIdentificationRange(1, 127);
    memcpy(&NewHcdObject->DmaDevice, DmaDevice, sizeof(LOUSINE_DMA_DEVICE));

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

    NewHcdObject->IoQueueManager = LouKeCreateDemon(
        (PVOID)UsbCoreHcdIoQueueManager,
        (PVOID)NewHcdObject,
        8 * KILOBYTE,
        31
    );
    if(!NewHcdObject->IoQueueManager){
        Operations->StopHcdDevice(NewHcdObject);
        LouKeFree(NewHcdObject);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    NewHcdObject->IoDeQueueManager = LouKeCreateDemon(
        (PVOID)UsbCoreHcdIoDeQueueManager,
        (PVOID)NewHcdObject,
        8 * KILOBYTE,
        31
    );
    if(!NewHcdObject->IoDeQueueManager){
        //TODO: Destroy Queue Demon
        Operations->StopHcdDevice(NewHcdObject);
        LouKeFree(NewHcdObject);
        LouPrint("USBCORE.SYS:UsbCoreCreateHcdObject():HERE\n");
        while(1);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    MutexLock(&UsbHcdListLock);
    LouKeListAddTail(&NewHcdObject->Peers, &UsbHcdList);
    MutexUnlock(&UsbHcdListLock);
    return STATUS_SUCCESS;
}

void UsbCoreCreateRoothubDevice(
    PUSB_HCD_OBJECT HcdObject, 
    SIZE            PortNumber
){
    PUSB_DEVICE_OBJECT NewDevice = LouKeMallocType(USB_DEVICE_OBJECT, KERNEL_GENERIC_MEMORY);
    NewDevice->DeviceAddress = LouKeAcquireIdFromRange(HcdObject->DeviceAddresses, NewDevice);
    if(!NewDevice->DeviceAddress){
        LouKeFree(NewDevice);
        return;
    }
    NewDevice->Uplink = 0x00;
    NewDevice->UplinkPort = PortNumber;
    NewDevice->Hcd = HcdObject;
    LOUSTATUS Status = UsbCoreDeviceRequestSetAddress(&HcdObject->DefaultDevice, NewDevice->DeviceAddress);
    if(Status != STATUS_SUCCESS){
        LouPrint("UsbCoreCreateRoothubDevice():HERE 1\n");
        while(1);
    }
    Status = UsbCoreCreateDefaultPipe(NewDevice);
    if(Status != STATUS_SUCCESS){
        LouPrint("UsbCoreCreateRoothubDevice():HERE 2\n");
        while(1);
    }

}

LOUSTATUS UsbCoreProbeRootHub(PUSB_HCD_OBJECT HcdObject){
    LouPrint("UsbCoreProbeRootHub()\n");
    SIZE RhPortCount = 0;
    LOUSTATUS PortResetStatus;
    if(HcdObject->Operations->GetHcdRhPortCount){
        RhPortCount = HcdObject->Operations->GetHcdRhPortCount(HcdObject);
    }
    if(!RhPortCount){
        RhPortCount = 256;
    }

    for(SIZE i = 0; i < RhPortCount; i++){
        if(!HcdObject->Operations->GetHcdRhPortStatus){
            //LouPrint("");
            continue;
        }

        RHPORT_STATUS RhPortStatus = HcdObject->Operations->GetHcdRhPortStatus(HcdObject, i);

        if(RhPortStatus == RHPORT_STATUS_NO_DEVICE){
            continue;
        }

        if(!HcdObject->Operations->ResetRhPort){
            continue;
        }

        PortResetStatus = HcdObject->Operations->ResetRhPort(HcdObject, i);
        if(PortResetStatus != STATUS_SUCCESS){
            continue;
        }

        UsbCoreCreateRoothubDevice(HcdObject, i);

        LouPrint("UsbCoreProbeRootHub(%d):FOUND_DEVICE\n", i);
        while(1);
    }


    LouPrint("UsbCoreProbeRootHub():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS
UsbCoreInitializeHostManagementAndBootDevices(){
    LouPrint("UsbCoreInitializeHostManagementAndBootDevices()\n");
    
    BOOLEAN HasXhci, HasEhci;

    MutexLock(&UsbHcdListLock);
    
    PUSB_HCD_OBJECT TmpHcd;
    ForEachListEntry(TmpHcd, &UsbHcdList, Peers){
        ForEachIf(USBHCD_FLAGS_GET_VERSION(TmpHcd->HcdFlags) != 3){
            continue;
        }
        HasXhci = true;
        LouPrint("USBCORE.SYS:Initializing Xhci Host Device:%h\n", TmpHcd);

        UsbCoreCreateDefaultUsbDeviceObject(TmpHcd);

        UsbCoreProbeRootHub(TmpHcd);

        //PUSB_ENDPOINT_OBJECT NewEndpoint0 = LouKeMallocType();


        
        //TODO:Create Endpoint 0 enumerate the root hub 
        //Add Check Status For Non Interruptable setups

    }

    MutexUnlock(&UsbHcdListLock);

    LouPrint("UsbCoreInitializeHostManagementAndBootDevices():STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}
