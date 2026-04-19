#define _STACK_INTERNALS_
#include <LouAPI.h>

static ListHeader   StackObjectList = {0};
static mutex_t      StackObjectLock = {0}; 

static PLOUSINE_STACK AllocateNewStackObject(){
    PLOUSINE_STACK NewStack = LouKeMallocType(LOUSINE_STACK, KERNEL_GENERIC_MEMORY);
    MutexLock(&StackObjectLock);
    LouKeListAddTail(&NewStack->Peers, &StackObjectList);
    MutexUnlock(&StackObjectLock);
    return NewStack;
}

UNUSED static void FreeStackObject(PLOUSINE_STACK StackObject){
    MutexLock(&StackObjectLock);
    LouKeListDeleteItem(&StackObject->Peers);
    MutexUnlock(&StackObjectLock);
    LouKeFree(StackObject);
}

PVOID 
LouKeCreateStack(
    UINT32  ProcessID,
    SIZE    VSize,
    BOOLEAN HighMem,
    UINT64  PageFlags
){
    PLOUSINE_STACK NewStack = AllocateNewStackObject();
    NewStack->Stack = HighMem ? LouKeAllocateVmmBuffer64Ex2(ProcessID, VSize, 16, false, false, PageFlags) : LouKeAllocateVmmBuffer32Ex2(ProcessID, VSize, 16, false, false, PageFlags);


    return NewStack->Stack;
}