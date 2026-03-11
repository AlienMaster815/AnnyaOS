#include <Hal.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeHalStartMirroring(){
    LouPrint("LouKeHalStartMirroring()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeHalEndMirroring(
    ULONG Pass
){
    LouPrint("LouKeHalEndMirroring()\n");
    while(1);
    return STATUS_SUCCESS;
}
