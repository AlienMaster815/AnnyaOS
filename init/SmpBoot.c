#include <LouAPI.h>

static inline uint32_t get_processor_id() {
    uint32_t eax, ebx, ecx, edx;
    eax = 1; // Processor info and feature bits
    __asm__ volatile(
        "cpuid"
        : "=b" (ebx), "=d" (edx), "=c" (ecx)
        : "a" (eax)
    );
    uint32_t processor_id = ebx >> 24;
    return processor_id;
}

INTEGER GetCpuTrackMemberFromID(UINT32 CpuID);
void LouKeSendProcessorWakeupSignal(INTEGER TrackMember);

uint16_t GetNPROC();

static mutex_t* TrampolineLock;
static UINT64* TrampolineStack;
static UINT64* FunctionAddress;
static UINT64* Pml4Address;

extern UINT64 page_table_l4;

void LouKeSmpWakeFunction(){

    MutexUnlock(TrampolineLock);

    while(1){

    }
}


void LouKeLoadLousineBootTrampoline(string FilePath){
    LouPrint("FilePath:%s\n", FilePath);
    UNUSED FILE* TrampolineFile = fopen(FilePath, KERNEL_GENERIC_MEMORY);
    LouKeMapContinuousMemoryBlock(0x7000, 0x7000, 0x2000, KERNEL_DMA_MEMORY);
    memset((PVOID)0x7000, 0, 0x2000);
    memcpy((PVOID)0x8000, (PVOID)TrampolineFile, fsize(TrampolineFile));
    INTEGER CurrentCpu = GetCpuTrackMemberFromID(get_processor_id());

    TrampolineStack = (UINT64*)0x7000;
    FunctionAddress = (UINT64*)0x7008;
    Pml4Address = (UINT64*)0x7010;
    TrampolineLock = (mutex_t*)0x7018;

    *Pml4Address     = (UINT64)&page_table_l4;
    *TrampolineStack = (UINT64)(LouKeMallocPhysicalEx(16 * KILOBYTE, 16, KERNEL_GENERIC_MEMORY) + ((16 * KILOBYTE) - 16)); 
    *FunctionAddress = (UINT64)LouKeSmpWakeFunction; 

    LouKeMemoryBarrier();

    for(INTEGER i = 0 ; i < 2; i++){
        if(i == CurrentCpu){
            continue;
        }
        MutexLock(TrampolineLock);
        LouKeSendProcessorWakeupSignal(i);
    }

    while(1);
}