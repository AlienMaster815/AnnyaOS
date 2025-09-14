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

uint64_t GetCurrentThreadID(){
    uint64_t ThreadId[2] = {0};
    while(!ThreadId[0]){
        LouCALL(LOUGETTHREADID, (uint64_t)&ThreadId[0], 0);
    }
    return ThreadId[1];
}

long InterlockedIncrement(long* LockHandle){
    *LockHandle = (*LockHandle + 1);
    return *LockHandle;
}

long InterlockedDecrement(long* LockHandle){
    *LockHandle = (*LockHandle - 1);
    return *LockHandle;
}

uint32_t InterlockedCompareExchange(
    long* LockHandle, 
    uint32_t Reserved, 
    uint32_t Result
){
    

    LouPrint("InterlockedCompareExchange()\n"); 
    while(1);
    return 0;
}

HANDLE ULongToHandle(uint64_t ThreadID){
    return (HANDLE)ThreadID;
}

NTDLL_API 
bool 
RtlTryEnterCriticalSection(
    PMSVC_CRITICAL_SECTION CriticalSection
){

    if(InterlockedCompareExchange(&CriticalSection->LockCount, 0 , -1) == -1){
        CriticalSection->ThreadWithPossesion = ULongToHandle(GetCurrentThreadID());
        CriticalSection->RecusionCount  =   1;
        return true;
    }
    else if((uint64_t)CriticalSection->ThreadWithPossesion == GetCurrentThreadID()){
        InterlockedIncrement(&CriticalSection->LockCount);
        CriticalSection->RecusionCount++;
        return true;
    }
    return false;
}

NTDLL_API
NTSTATUS 
RtlEnterCriticalSection(
    PMSVC_CRITICAL_SECTION CriticalSection
){

    if(CriticalSection->SpinCount){
        uint64_t Count = 0;

        if(RtlTryEnterCriticalSection(CriticalSection))return 0;//STATUS_SUCCESS
        for(Count = CriticalSection->SpinCount; Count > 0; Count--){
            if(CriticalSection->LockCount > 0){
                break;
            }
            if(CriticalSection->LockCount == -1){
                if(InterlockedCompareExchange(&CriticalSection->LockCount, 0 , -1) == -1){
                    CriticalSection->ThreadWithPossesion = ULongToHandle(GetCurrentThreadID());
                    CriticalSection->RecusionCount = 1;
                    return STATUS_SUCCESS;
                }
            }
            LouYeildExecution();
        }

    }
    CriticalSection->ThreadWithPossesion = ULongToHandle(GetCurrentThreadID());
    CriticalSection->RecusionCount = 1;
    return STATUS_SUCCESS;
}


NTDLL_API
NTSTATUS 
RtlInitializeCriticalSectionEx(
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
        if(CriticalSection->DebuggingInfo){
            CriticalSection->DebuggingInfo->SectionType = 0;
            CriticalSection->DebuggingInfo->CBTI;
            CriticalSection->DebuggingInfo->MsvcCriticalSection = CriticalSection;
            CriticalSection->DebuggingInfo->ProcessLockList.LastHeader = (PListHeader)&CriticalSection->DebuggingInfo->ProcessLockList;
            CriticalSection->DebuggingInfo->ProcessLockList.NextHeader = (PListHeader)&CriticalSection->DebuggingInfo->ProcessLockList;
            CriticalSection->DebuggingInfo->LockListEntryCount - 0;
            CriticalSection->DebuggingInfo->ContentionCount = 0;
        }
    }else{
        CriticalSection->DebuggingInfo = 0x00;
    }

    CriticalSection->LockCount              = -1;
    CriticalSection->RecusionCount          = 0;
    CriticalSection->ThreadWithPossesion    = 0;
    CriticalSection->Semaphore              = 0;
    
    if(NtGetProcessorCount() <= 1){
        CriticalSection->SpinCount = 0;    
    }
    CriticalSection->SpinCount = SpinCount & ~(0x80000000);

    return STATUS_SUCCESS;
}


NTDLL_API 
NTSTATUS 
RtlLeaveCriticalSection(PMSVC_CRITICAL_SECTION CriticalSection) {

    if(--CriticalSection->RecusionCount){
        if(CriticalSection->RecusionCount > 0){
            InterlockedDecrement(&CriticalSection->LockCount);
        }else{
            LouPrint("Error:Lock Not Aquired:%h\n", CriticalSection);
            while(1);
        }
    }else{
        CriticalSection->ThreadWithPossesion = 0;
        if(InterlockedDecrement(&CriticalSection->LockCount) >= 0){

            LouPrint("Someone Is Waiting\n");
            while(1);
        }
    }
    return STATUS_SUCCESS;
}