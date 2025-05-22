#define _KERNEL_MODULE_
#define _WPP_H

#include <LouDDK.h>

static uint64_t pfnWppGetVersion = 0;
static uint64_t pfnWppTraceMessage = 0;
static uint64_t pfnWppQueryTraceInformation = 0;

LOUDDK_API_ENTRY
uint64_t 
WppLoadTracingSupport(){
    pfnWppGetVersion = LouKeLinkerGetAddress(
        "ntoskrnl.exe",
        "PsGetVersion"
    );
    if(!pfnWppGetVersion){
        LouPrint("pfnWppGetVersion Is Null\n");
        return 0x00;
    }
    pfnWppTraceMessage = LouKeLinkerGetAddress(
        "ntoskrnl.exe",
        "WmiTraceMessage"
    );
    if(!pfnWppTraceMessage){
        LouPrint("pfnWppTraceMessage Is Null\n");
        return 0x00;
    }
    pfnWppQueryTraceInformation = LouKeLinkerGetAddress(
        "ntoskrnl.exe",
        "WmiQueryTraceInformation"
    );
    if(!pfnWppQueryTraceInformation){
        LouPrint("pfnWppQueryTraceInformation Is Null\n");
        return 0x00;
    }
    return pfnWppGetVersion;
}

