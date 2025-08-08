#include "8237A.h"


LOUDDK_API_ENTRY
NTSTATUS 
DriverEntry(
    PDRIVER_OBJECT DrvObj,
    PUNICODE_STRING RegistryEntry
){
    LouPrint("8237A.SYS:DriverEntry()\n");
    


    LouPrint("8237A.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}