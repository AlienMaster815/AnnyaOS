#include <LouDDK.h>

KERNEL_EXPORT
void 
LouKeExpandStackCallout(//export as NTOSKRNL.EXE:ExpandStackCallout
	PVOID Parameter
){
    LouPrint("LouKeExpandStackCallout()\n");
    while(1);
}


KERNEL_EXPORT 
LOUSTATUS 
LouKeAllocateVirtualMemoryExCallback(
    HANDLE                  CallbackContext, 
    HANDLE                  ProcessHandle, 
    PVOID*                  BaseAddress, 
    PSIZE_T                 RegionSize, 
    ULONG                   AllocationType, 
    ULONG                   PageProtection, 
    PMEM_EXTENDED_PARAMETER ExtendedParameters, 
    ULONG                   ExtendedParameterCount
){
    LouPrint("LouKeAllocateVirtualMemoryExCallback()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
BOOLEAN 
LouKeCcCanIWrite(
    PFILE_OBJECT    FileObject, 
    ULONG           BytesToWrite, 
    BOOLEAN         Wait, 
    UCHAR           Retrying
){
    LouPrint("LouKeCcCanIWrite()\n");
    while(1);
    return false;
}
