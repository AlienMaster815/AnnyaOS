#define _KERNEL_MODULE_
#include <LouDDK.h>
#include "AhciMod.h"



LOUSTATUS AhciAvnHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AhciAvnHardReset");
    while(1);
    return STATUS_SUCCESS;
}