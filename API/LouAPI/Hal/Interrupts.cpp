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
