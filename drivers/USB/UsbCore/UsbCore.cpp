//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "UsbCore.h"

KERNEL_ENTRY LOUSTATUS UsbCoreSubsystemEntry(){

    //LouPrint("UsbCoreSubsystemEntry()\n");

    LouKeCreateFastObjectClass("USB_TRANSFER_OBJECT", 64, sizeof(USB_TRANSFER_OBJECT), GET_ALIGNMENT(USB_TRANSFER_OBJECT), 0, KERNEL_GENERIC_MEMORY);
    
    //while(1);
    return STATUS_SUCCESS;
}

