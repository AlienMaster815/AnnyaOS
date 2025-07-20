#include "ntdll.h"

extern uint64_t NtGetPeb();
extern uint64_t NtGetTeb();

void* RtlAllocateHeapEx(
    PVOID       HeapHandle,
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize,
    size_t      Alignment
){

    switch(HeapAllocationFlags){
        case 0:
            return LouGenericAllocateHeapEx(HeapHandle, HeapSize, Alignment);
        default:
            LouPrint("Allocation Failed Unrecognized Flags:%h\n", HeapAllocationFlags);
            LouTrashAndDumpProcess();
    }
}

void* RtlAllocateHeap(
    PVOID       HeapHandle,
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize
){
    return RtlAllocateHeapEx(HeapHandle, HeapAllocationFlags, HeapSize, GetAlignmentBySize(HeapSize));
}

NTDLL_API
void* GetProcessHeap(){
    PWIN_PEB Peb = (PWIN_PEB)(uint8_t*)NtGetPeb();
    return (void*)(uint8_t*)Peb->ProcessHeap;
}

//used for Dlls that have a dedicated Version of GetProcessHeap
NTDLL_API 
void* AnnyaNtGetProcessHeap(){
    return GetProcessHeap(); 
}

NTDLL_API
uint16_t NtGetProcessorCount(){
    PWIN_PEB Peb = (PWIN_PEB)(uint8_t*)NtGetPeb();
    return Peb->NumberOfProcessors;
}