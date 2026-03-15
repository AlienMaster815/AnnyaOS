#include <LouDDK.h>

KERNEL_EXPORT
void 
LouKeExpandStackCallout(//export as NTOSKRNL.EXE:ExpandStackCallout
	PVOID Parameter
){
    LouPrint("LouKeExpandStackCallout()\n");
    while(1);
}