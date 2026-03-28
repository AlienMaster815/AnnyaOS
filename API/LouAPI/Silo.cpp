//Copyright GPL-2 Tyler Grenier (2026)
#include <LouDDK.h>

KERNEL_EXPORT
void 
SiloContextCleanupCallback(
   PVOID SiloContext
){
    LouPrint("SiloContextCleanupCallback()\n");
    while(1);
}

KERNEL_EXPORT
void 
SiloMonitorTerminateCallback(
   PESILO Silo
){
    LouPrint("SiloMonitorTerminateCallback()\n");
    while(1);
}