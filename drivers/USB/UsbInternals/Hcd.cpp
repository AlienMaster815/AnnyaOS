#include <LouDDK.h>
#include <usb.h>
#include <Hal.h>
#include "Hcd.h"

static PIDENTIFICATION_RANGE UsbIdRange = 0x00;

static void LouKeInitializeUsbBus(PUSB_BUS UsbBus){
    memset(&UsbBus->DeviceMap, 0, sizeof(UsbBus->DeviceMap));
    UsbBus->NextDeviceNumber = 1;
    UsbBus->RootHub = 0x00;
    UsbBus->BusNumber = -1;
    UsbBus->BandwithAllocated = 0;
    UsbBus->BandwithInterrupts = 0;
    UsbBus->BandwithIsoc = 0;
}

PUSB_HOST_CONTROLLER_DEVICE
LouKeCreateUsbHostControllerDeviceEx(
    const USB_HOST_CONTROLLER_DRIVER*   Driver,
    PPCI_DEVICE_OBJECT                  SystemDevice,
    PPCI_DEVICE_OBJECT                  Device,
    PUSB_HOST_CONTROLLER_DEVICE         PrimaryHcd
){

    SIZE DeviceObjectSize =  ROUND_UP64(sizeof(USB_HOST_CONTROLLER_DEVICE), GET_ALIGNMENT(UINT64));
    PUSB_HOST_CONTROLLER_DEVICE Hcd = (PUSB_HOST_CONTROLLER_DEVICE)LouKeMallocEx(DeviceObjectSize + Driver->HcdPrivateSize , GET_ALIGNMENT(USB_HOST_CONTROLLER_DEVICE), KERNEL_GENERIC_MEMORY);
    Hcd->PrivateData = (PVOID)((UINTPTR)Hcd + (UINTPTR)DeviceObjectSize);
    if(!PrimaryHcd){
        Hcd->Address0Mutex = LouKeMallocType(mutex_t, KERNEL_GENERIC_MEMORY);
        Hcd->BandwithMutex = LouKeMallocType(mutex_t, KERNEL_GENERIC_MEMORY);
        Device->DevicePrivateData = (UINTPTR)Hcd;
    }else{
        Hcd->PrimaryHcd = PrimaryHcd;
        Hcd->Address0Mutex = PrimaryHcd->Address0Mutex;
        Hcd->BandwithMutex = PrimaryHcd->BandwithMutex;
        Hcd->PrimaryHcd = PrimaryHcd;
        Hcd->SharedHcd = PrimaryHcd;
        PrimaryHcd->SharedHcd = Hcd;
        Device->DevicePrivateData = (UINTPTR)Hcd; 
    }
    
    LouKeInitializeUsbBus(&Hcd->UsbSelf);
    Hcd->UsbSelf.ControllerDevice = Device;
    Hcd->UsbSelf.SystemDevice = SystemDevice;
    Hcd->UsbSelf.BusName = Driver->DeviceDescription;

    Hcd->HcdDriver = (PUSB_HOST_CONTROLLER_DRIVER)Driver;
    Hcd->RoothubSpeed  = Driver->DriverFlags & HCD_MASK;
    Hcd->ProductDescriptor = (Driver->ProductDescriptor) ? Driver->ProductDescriptor : (string)"USB Host Controller";
    return Hcd;
}

PUSB_HOST_CONTROLLER_DEVICE
LouKeCreateUsbHostControllerDevice(
    const USB_HOST_CONTROLLER_DRIVER*   Driver,
    PPCI_DEVICE_OBJECT                  PDEV
){
    return LouKeCreateUsbHostControllerDeviceEx(Driver, PDEV, PDEV, 0x00);
}

static UINT8 UsbDeviceDefaultAuthority = USB_DEVICE_AUTHORITY_ALL;

static 
LOUSTATUS
LouKeUsbRegisterBus(
    PUSB_BUS Bus
){
    INTEGER BusNumber;
    if(!UsbIdRange){
        UsbIdRange = LouKeCreateIdentificationRange(0, 256);
    }
    BusNumber = LouKeAcquireIdFromRange(UsbIdRange, (PVOID)Bus);
    
    if(BusNumber == (INTEGER)-1){
        LouPrint("USB ERROR: Unable To Acquire ID For Bus:%h\n", Bus);
        return STATUS_UNSUCCESSFUL;
    }

    LouPrint("Bus:%h Is Now Tied To ID:%d\n", Bus, BusNumber);
    Bus->BusNumber = BusNumber;

    //MABYE_TODO: add notifier

    return STATUS_SUCCESS;
}

LOUSTATUS 
LouKeUsbAddHcd(
    PUSB_HOST_CONTROLLER_DEVICE Hcd,
    UINT8                       Irq
){
    LOUSTATUS Status = STATUS_SUCCESS;
    UNUSED PUSB_DEVICE RhDev;
    UNUSED PUSB_HOST_CONTROLLER_DEVICE SharedHcd;
    UNUSED INTEGER SkipPhyLayerInit;
    UNUSED BOOL IsPrimaryHcd = !Hcd->PrimaryHcd;

    Hcd->DevicePolicy = UsbDeviceDefaultAuthority;
    if(Hcd->DevicePolicy == USB_DEVICE_AUTHORITY_WIRED){
        Hcd->DevicePolicy = USB_DEVICE_AUTHORITY_ALL;
    }

    Hcd->Flags |= 1;            //HW ACCESSABLE
    Hcd->Flags |= (1 << 7);     //INTERFACE AUTHORIZED
    
    Status = LouKeCreateHcdBuffer(Hcd);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = LouKeUsbRegisterBus(&Hcd->UsbSelf);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    RhDev = LouKeAllocateUsbDevice(0x00, &Hcd->UsbSelf, 0);
    LouPrint("RootHub Device:%h\n", RhDev);    

    return Status;
}

PUSB_HOST_CONTROLLER_DEVICE LouKeUsbGetHcd(PUSB_HOST_CONTROLLER_DEVICE Hcd){
    if(Hcd){
        LouKeAcquireReference(&Hcd->KRef);
    }
    return Hcd;
}

void LouKeUsbPutHcd(PUSB_HOST_CONTROLLER_DEVICE Hcd){
    if(Hcd){
        LouKeReleaseReferece(&Hcd->KRef);
    }
}