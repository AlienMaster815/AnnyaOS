//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <Hal.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeHalInitPowerManagement(
    PVOID Info
){
    LouPrint("LouKeHalInitPowerManagement()\n");
    while(1);
    return STATUS_SUCCESS;
}
