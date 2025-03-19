#include "ntdll.h"

NTDLL_API
NTSTATUS RtlInitializeCriticalSectionEx(
    PMSVC_CRITICAL_SECTION CriticalSection,
    uint32_t SpinCount,
    uint32_t Flags
){
    if(Flags & MSVC_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION_DYNAMIC_SPIN){
        //TODO:allocate static pool for debug information
        LouPrint("Critical Section:%h :: SpinCount:%d :: Flags:%h\n", CriticalSection, SpinCount, Flags);
    }

    

    return STATUS_SUCCESS;
}