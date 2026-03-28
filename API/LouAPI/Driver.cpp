//Copyright GPL-2 Tyler Grenier (2026)
#include <LouDDK.h>

KERNEL_EXPORT 
void 
LouKeDriverReinitialize( //export as NTOSKRNL.EXE:DriverReinitialize
    PDRIVER_OBJECT DriverObject, 
    PVOID Context, 
    ULONG Count
){
    LouPrint("LouKeDriverReinitialize()\n");
    while(1);
}
