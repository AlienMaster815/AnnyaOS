#include "ntdll.h"

void* GetProcessHeap();

extern uint64_t NtGetPeb();
extern uint64_t NtGetTeb();

uint16_t NtGetProcessorCount();

void* RtlAllocateHeapEx(
    PVOID       HeapHandle, //using actual heap
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize,
    size_t      Alignment
);

uint64_t GetCurrentOwningThread(){
    uint64_t ThreadId[2] = {0};
    while(!ThreadId[0]){
        LouCALL(LOUGETTHREADID, (uint64_t)&ThreadId[0], 0);
    }
    return ThreadId[1];
}


HANDLE ULongToHandle(uint64_t OwningThread){
    return (HANDLE)OwningThread;
}

NTDLL_API 
bool 
RtlTryEnterCriticalSection(
    PRTL_CRITICAL_SECTION CriticalSection
){

    if(InterlockedCompareExchange(&CriticalSection->LockCount, 0 , -1) == -1){
        CriticalSection->OwningThread = ULongToHandle(GetCurrentOwningThread());
        CriticalSection->RecursionCount  =   1;
        return true;
    }
    else if((uint64_t)CriticalSection->OwningThread == GetCurrentOwningThread()){
        InterlockedIncrement(&CriticalSection->LockCount);
        CriticalSection->RecursionCount++;
        return true;
    }
    return false;
}

NTDLL_API
NTSTATUS 
RtlEnterCriticalSection(
    PRTL_CRITICAL_SECTION CriticalSection
){

    if(CriticalSection->SpinCount){
        uint64_t Count = 0;

        if(RtlTryEnterCriticalSection(CriticalSection))return 0;//STATUS_SUCCESS
        for(Count = *CriticalSection->SpinCount; Count > 0; Count--){
            if(CriticalSection->LockCount > 0){
                break;
            }
            if(CriticalSection->LockCount == -1){
                if(InterlockedCompareExchange(&CriticalSection->LockCount, 0 , -1) == -1){
                    CriticalSection->OwningThread = ULongToHandle(GetCurrentOwningThread());
                    CriticalSection->RecursionCount = 1;
                    return STATUS_SUCCESS;
                }
            }
            LouYeildExecution();
        }

    }
    CriticalSection->OwningThread = ULongToHandle(GetCurrentOwningThread());
    CriticalSection->RecursionCount = 1;
    return STATUS_SUCCESS;
}


NTDLL_API
NTSTATUS 
RtlInitializeCriticalSectionEx(
    PRTL_CRITICAL_SECTION CriticalSection,
    uint32_t SpinCount,
    uint32_t Flags
){

    if(!CriticalSection->SpinCount){
        return STATUS_UNSUCCESSFUL;
    }

    if(Flags & RTL_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION_DYNAMIC_SPIN){
        //TODO:allocate static pool for debug information
        LouPrint("Critical Section:%h :: SpinCount:%d :: Flags:%h\n", CriticalSection, SpinCount, Flags);
    }

    if(Flags & RTL_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFORMATION){
        LouPrint("Forcing Debug on critical section\n");
        CriticalSection->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)RtlAllocateHeapEx(GetProcessHeap(), 0, sizeof(RTL_CRITICAL_SECTION_DEBUG_DATA), GET_ALIGNMENT(RTL_CRITICAL_SECTION_DEBUG_DATA));
        if(CriticalSection->DebugInfo){
            CriticalSection->DebugInfo->Type = 0;
            CriticalSection->DebugInfo->CreatorBackTraceIndex;
            CriticalSection->DebugInfo->CriticalSection = CriticalSection;
            CriticalSection->DebugInfo->ProcessLocksList.Blink = (PLIST_ENTRY)&CriticalSection->DebugInfo->ProcessLocksList;
            CriticalSection->DebugInfo->ProcessLocksList.Flink = (PLIST_ENTRY)&CriticalSection->DebugInfo->ProcessLocksList;
            CriticalSection->DebugInfo->EntryCount = 0;
            CriticalSection->DebugInfo->ContentionCount = 0;
        }
    }else{
        CriticalSection->DebugInfo = 0x00;
    }

    CriticalSection->LockCount              = -1;
    CriticalSection->RecursionCount         = 0;
    CriticalSection->OwningThread           = 0;
    CriticalSection->LockSemaphore          = 0;
    
    if(NtGetProcessorCount() <= 1){
        *CriticalSection->SpinCount = 0;    
    }
    *CriticalSection->SpinCount = SpinCount & ~(0x80000000);
    return STATUS_SUCCESS;
}


NTDLL_API 
NTSTATUS 
RtlLeaveCriticalSection(PRTL_CRITICAL_SECTION CriticalSection) {

    if(--CriticalSection->RecursionCount){
        if(CriticalSection->RecursionCount > 0){
            InterlockedDecrement(&CriticalSection->LockCount);
        }else{
            LouPrint("Error:Lock Not Aquired:%h\n", CriticalSection);
            while(1);
        }
    }else{
        CriticalSection->OwningThread = 0;
        if(InterlockedDecrement(&CriticalSection->LockCount) >= 0){

            LouPrint("Someone Is Waiting\n");
            while(1);
        }
    }
    return STATUS_SUCCESS;
}