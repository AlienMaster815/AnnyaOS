#include "ntdll.h"

void* GetProcessHeap();

void* RtlAllocateHeapEx(
    PVOID       HeapHandle, //using actual heap
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize,
    size_t      Alignment
);

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

    if(Flags & MSVC_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFORMATION){
        LouPrint("Forcing Debug on critical section\n");
        CriticalSection->DebuggingInfo = (PMSVC_CRITICAL_SECTION_DEBUG_DATA)RtlAllocateHeapEx(GetProcessHeap(), 0, sizeof(MSVC_CRITICAL_SECTION_DEBUG_DATA), GET_ALIGNMENT(MSVC_CRITICAL_SECTION_DEBUG_DATA));

    }else{
        CriticalSection->DebuggingInfo = 0x00;
    }
    
    return STATUS_SUCCESS;
}
