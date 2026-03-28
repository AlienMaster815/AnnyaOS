//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <Hal.h>


KERNEL_EXPORT 
LOUSTATUS 
LouKeHalGetInterruptTranslator(
    INTERFACE_TYPE ParrentInterfaceType, 
    ULONG ParrentBussNumber, 
    INTERFACE_TYPE BridgeInterfaceType, 
    USHORT Size, 
    USHORT VendorsDictionary, 
    PTRANSLATOR_INTERFACE Translator, 
    PULONG BridgeBusNumber
){
    LouPrint("LouKeHalGetInterruptTranslator()\n");
    while(1);
    return STATUS_SUCCESS;
}
