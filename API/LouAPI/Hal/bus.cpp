//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <Hal.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeHalQueryBusSlots(
    PBUS_HANDLER 
    BusHandler, 
    ULONG Index, 
    PULONG Data, 
    PULONG Remaining
){
    LouPrint("LouKeHalQueryBusSlots()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
PBUS_HANDLER 
LouKeHalHandlerForBus(
    INTERFACE_TYPE InterfaceType,
    ULONG BusNumber
){
    LouPrint("LouKeHalHandlerForBus()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
void 
LouKeHalReferenceBusHandler(
    PBUS_HANDLER BusHandler
){
    LouPrint("LouKeHalReferenceBusHandler()\n");
    while(1);
}
