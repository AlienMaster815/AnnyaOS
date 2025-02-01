#include <LouDDK.h>
#include "AhciMod.h"

SECTIONED_CODE(".Ahci.Code")
LOUSTATUS AhciAvnHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AhciAvnHardReset");
    while(1);
    return STATUS_SUCCESS;
}