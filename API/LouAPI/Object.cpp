#include <LouDDK.h>

KERNEL_EXPORT
LOUSTATUS 
LouKeExUuidCreate( //export as NTOSKRNL.EXE:ExUuidCreate
	UUID* Uuid
){
    LouPrint("LouKeExUuidCreate()\n");
    while(1);
    return STATUS_SUCCESS;
}