#include "Gdi.h"

KERNEL_ENTRY NTSTATUS GdiSubsystemEntry(){

    LouPrint("Hello From GdiSubsystemEntry\n");

    return STATUS_SUCCESS;
}