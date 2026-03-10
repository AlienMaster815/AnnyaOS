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
