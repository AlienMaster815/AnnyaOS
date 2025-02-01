#include <LouDDK.h>
#include "AhciMod.h"

SECTIONED_CODE(".Ahci.Code")
LOUSTATUS AhciP5wdhHardReset(PLOUSINE_KERNEL_DEVICE_ATA_PORT AhciPort){
    LouPrint("AhciP5wdhHardReset");
    while(1);
    return STATUS_SUCCESS;
}