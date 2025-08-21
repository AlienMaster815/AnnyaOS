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

//static spinlock_t* TrampolineLock;
//static LouKIRQL* PreTrampolineIrql;


void LouKeLoadLousineBootTrampoline(string FilePath){
    //LouPrint("FilePath:%s\n", FilePath);
    //UNUSED FILE* TrampolineFile = fopen(FilePath, KERNEL_GENERIC_MEMORY);
    //LouKeMapContinuousMemoryBlock(0x7000, 0x7000, 0x2000, KERNEL_DMA_MEMORY);
    //memset((PVOID)0x7000, 0, 0x2000);
    //memcpy((PVOID)0x8000, (PVOID)TrampolineFile, fsize(TrampolineFile));
    //INTEGER CurrentCpu = GetCpuTrackMemberFromID(get_processor_id());
    
    //TrampolineLock = (spinlock_t*)0x7000;
    //PreTrampolineIrql = (LouKIRQL*)(ROUND_UP64(0x7000 + sizeof(spinlock_t), GET_ALIGNMENT(spinlock_t)));
    //for(INTEGER i = 0 ; i < GetNPROC(); i++){
    //    if(i == CurrentCpu){
    //        continue;
    //    }
    //    LouKeAcquireSpinLock(TrampolineLock, PreTrampolineIrql);

    //    LouKeSendProcessorWakeupSignal(i);

    //}

}