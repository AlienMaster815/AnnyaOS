//Copyright GPL-2 Tyler Grenier (2026)
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