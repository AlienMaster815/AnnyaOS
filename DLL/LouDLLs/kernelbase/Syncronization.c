#include "kernelbase.h"

KERNELBASE_API
NTSTATUS InitializeCriticalSectionEx(
    PMSVC_CRITICAL_SECTION CriticalSection, 
    uint32_t SpinCounter, 
    uint32_t Flags
){
    
    NTSTATUS Result = RtlInitializeCriticalSectionEx(
        CriticalSection,
        SpinCounter,
        Flags
    );
 
}