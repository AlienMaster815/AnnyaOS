#include "ProcessPrivate.h"

LOUDDK_API_ENTRY
semaphore_t* LouKeCreateSemaphore(int initial, int limit){
    semaphore_t* NewSemaphore = (semaphore_t*)LouKeMallocType(semaphore_t, KERNEL_GENERIC_MEMORY);
    SemaphoreInitialize(NewSemaphore, initial, limit);
    return NewSemaphore;
}

UNUSED 
static void SaveContext(CPUContext* TMContext, CPUContext* ProgramContext){

    ProgramContext->rax = TMContext->rax;
    ProgramContext->rbx = TMContext->rbx;
    ProgramContext->rcx = TMContext->rcx;
    ProgramContext->rdx = TMContext->rdx;

    ProgramContext->rbp = TMContext->rbp;
    ProgramContext->rsi = TMContext->rsi;
    ProgramContext->rdi = TMContext->rdi;
    ProgramContext->r8 = TMContext->r8;

    ProgramContext->r9 = TMContext->r9;
    ProgramContext->r10 = TMContext->r10;
    ProgramContext->r11 = TMContext->r11;
    ProgramContext->r12 = TMContext->r12;

    ProgramContext->r13 = TMContext->r13;
    ProgramContext->r14 = TMContext->r14;
    ProgramContext->r15 = TMContext->r15;
    ProgramContext->rip = TMContext->rip;

    ProgramContext->cs = TMContext->cs;
    ProgramContext->rflags = TMContext->rflags;
    ProgramContext->rsp = TMContext->rsp;
    ProgramContext->ss = TMContext->ss;

}

UNUSED
static void RestoreContext(CPUContext* TMContext, CPUContext* ProgramContext){

    TMContext->rax = ProgramContext->rax;
    TMContext->rbx = ProgramContext->rbx;
    TMContext->rcx = ProgramContext->rcx;
    TMContext->rdx = ProgramContext->rdx;

    TMContext->rbp = ProgramContext->rbp;
    TMContext->rsi = ProgramContext->rsi; 
    TMContext->rdi = ProgramContext->rdi;
    TMContext->r8 = ProgramContext->r8;

    TMContext->r9 = ProgramContext->r9;
    TMContext->r10 = ProgramContext->r10;
    TMContext->r11 = ProgramContext->r11;
    TMContext->r12 = ProgramContext->r12;

    TMContext->r13 = ProgramContext->r13;
    TMContext->r14 = ProgramContext->r14;
    TMContext->r15 = ProgramContext->r15;
    TMContext->rip = ProgramContext->rip;

    TMContext->cs = ProgramContext->cs;
    TMContext->rflags = ProgramContext->rflags;
    TMContext->rsp = ProgramContext->rsp;
    TMContext->ss = ProgramContext->ss;

}



void LouKeSwitchToTask(
    UINT64                  CpuCurrentState,
    PGENERIC_THREAD_DATA    ThreadFrom,
    PGENERIC_THREAD_DATA    ThreadTo,
    BOOL                    StoreData
){
    //LouPrint("Switching From:%h To:%h\n", ThreadFrom, ThreadTo);

    if(StoreData){
        SaveContext((CPUContext*)(uint8_t*)CpuCurrentState, (CPUContext*)(uint8_t*)LouKeCastToUnalignedPointer((void*)&ThreadFrom->SavedState));
        ThreadFrom->State = THREAD_READY;
        SaveEverything(&ThreadFrom->ContextStorage);
    }
        
    ThreadTo->State = THREAD_RUNNING;
    RestoreEverything(&ThreadTo->ContextStorage);
    SetPEB((UINT64)ThreadTo->Peb);
    SetTEB((UINT64)&ThreadTo->Teb);
    RestoreContext((CPUContext*)(uint8_t*)CpuCurrentState, (CPUContext*)(uint8_t*)LouKeCastToUnalignedPointer((void*)&ThreadTo->SavedState));

}


