//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#define _KERNEL_MODULE_
#ifndef _USB_CORE_INTERNALS_
#define _USB_CORE_INTERNALS_

//TODO: Check ACPI _PLD table for the port numbers for XHCI transfers

#include <LouDDK.h>
#include <usb.h>

void UsbCoreCommitUsbTransferToCommandEngine(PUSB_TRANSFER_OBJECT TransferObject, int MsTimeout);
LOUSTATUS UsbCoreFenceTransferObject(PUSB_TRANSFER_OBJECT TransferObject);

LOUSTATUS UsbCoreAllocateUsbControlTransfer(PUSB_TRANSFER_OBJECT* OutTransfer, PUSB_DEVICE_OBJECT Device, PUSB_PIPE_OBJECT Pipe, ULONG TransferFlags, SIZE DataSize, SIZE DataAlignment);
LOUSTATUS UsbCoreFreeUsbControlTransfer(PUSB_TRANSFER_OBJECT Transfer);

LOUSTATUS _UsbCoreDeviceRequestSetAddressStart(PUSB_TRANSFER_OBJECT* OutObject, PUSB_DEVICE_OBJECT UsbDevice, UINT8 Address);
LOUSTATUS _UsbCoreDeviceRequestSetAddressEnd(PUSB_TRANSFER_OBJECT TransferObject);

LOUSTATUS UsbCoreCreateDefaultControlPipe(PUSB_DEVICE_OBJECT UsbDevice);

#endif