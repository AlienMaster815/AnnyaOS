#include "Pci.h"

static BOOLEAN PciDebugOn = false;

void PciHalPciDbgPrint(char* format, ...){
    if(PciDebugOn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}


LOUSTATUS PciEntry(){
    HANDLE PciDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\PCI_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(PciDebugKey, &DbgValue);
    PciDebugOn = DbgValue ? true : false;
    
    return STATUS_SUCCESS;
}