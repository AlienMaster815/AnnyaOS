#include <LouDDK.h>
#include "AhciMod.h"

LOUSTATUS AhciVt8251HardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AhciVt8251HardReset");
    while(1);
    return STATUS_SUCCESS;
}