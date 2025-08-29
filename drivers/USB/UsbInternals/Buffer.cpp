#include <LouDDK.h>
#include <Hal.h>
#include <usb.h>
#include "Hcd.h"

LOUSTATUS
LouKeCreateHcdBuffer(
    PUSB_HOST_CONTROLLER_DEVICE Hcd
){
    
    if((Hcd->HcdLocalMemory) || (!(Hcd->HcdDriver->DriverFlags & HCD_DMA))){
        return STATUS_SUCCESS;
    }

    Hcd->HcdLocalMemory = LouKeCreateDynamicPool(
        64 * KILOBYTE,
        64 * KILOBYTE,
        "USB Hcd Pool",
        0,
        KERNEL_DMA_MEMORY
    );

    return STATUS_SUCCESS;
}