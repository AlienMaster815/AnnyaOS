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

void CheckWinCallTable(int64_t Call, uint64_t Data);
void CheckLouCallTables(int64_t Call, uint64_t Data);
spinlock_t* LouKeGetInterruptGlobalLock();
void RestoreEverything(uint64_t* ContextHandle);
void SaveEverything(uint64_t* ContextHandle);

void SYSCALLS(uint64_t Call, uint64_t Data, uint64_t SystemEmulation, uint64_t StackPointer){
    uint64_t* Status = (uint64_t*)Data;
    if(SpinlockIsLocked(LouKeGetInterruptGlobalLock())){
        *Status = 0;
        return;
    }
    //Status Success the Call went 
    //througt to be handled
    *Status = 1;
    uint64_t RegisterHandle;
    SaveEverything(&RegisterHandle);
    if(!SystemEmulation){
        CheckLouCallTables(Call, Data);
    }else if(SystemEmulation == LOUCALL_WIN64_EMU){
        CheckWinCallTable(Call, Data);
    }
    RestoreEverything(&RegisterHandle);

}