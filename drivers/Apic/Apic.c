#define APIC_MAIN
#include "ApicInternals.h"

PPER_PROCESSOR_APIC_DATA PerProcessorApicData = 0x00;

static BOOLEAN ApicDebugOn = false;

void ApicHalDbgPrint(char* format, ...){
    if(ApicDebugOn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}

DRIVER_EXPORT 
LOUSTATUS 
ApicInitializeAdvancedProgramableInterruptController(
    SIZE Cpu
){


    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS 
ApicSubsystemEntry(){
    LouPrint("APICS.SYS:ApicSubsystemEntry()\n");
    
    HANDLE ApicDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\APIC_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(ApicDebugKey, &DbgValue);
    ApicDebugOn = DbgValue ? true : false;


    LouPrint("APICS.SYS:ApicSubsystemEntry():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}