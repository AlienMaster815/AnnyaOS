#include <LouAPI.h>

typedef struct  __attribute__((packed)) _CPUContext{
    // General-Purpose Registers    
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r8;

    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;

    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;

    uint64_t cs;
    uint64_t fq;
    uint64_t FaultStack;
    uint64_t ss;
} CPUContext;

void CheckLouCallTables(uint64_t Call, uint64_t Data);

spinlock_t* LouKeGetInterruptGlobalLock();


void SYSCALLS(uint64_t Call, uint64_t Data, uint64_t SystemEmulation, uint64_t StackPointer){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(LouKeGetInterruptGlobalLock(), &Irql);


    if(!SystemEmulation){
        CheckLouCallTables(Call, Data);
    }

    LouKeReleaseSpinLock(LouKeGetInterruptGlobalLock(), &Irql);

}