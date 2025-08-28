#include <LouDDK.h>
#include <usb.h>

PUSB_HOST_CONTROLLER_DEVICE
LouKeAllocateUsbHostControllerDevice(
    const USB_HOST_CONTROLLER_DRIVER*   Driver,
    PPCI_DEVICE_OBJECT                  PDEV
){
    size_t DeviceDataSize = ROUND_UP64(sizeof(USB_HOST_CONTROLLER_DEVICE), sizeof(uint64_t)) + Driver->HcdPrivateSize;
    PUSB_HOST_CONTROLLER_DEVICE NewDevice = (PUSB_HOST_CONTROLLER_DEVICE)LouKeMallocEx(DeviceDataSize, GET_ALIGNMENT(USB_HOST_CONTROLLER_DEVICE), KERNEL_GENERIC_MEMORY);
    NewDevice->PrivateData = (PVOID)((UINT64)NewDevice + ROUND_UP64(sizeof(USB_HOST_CONTROLLER_DEVICE), sizeof(uint64_t)));
    NewDevice->PDEV = PDEV;
    return NewDevice;
}