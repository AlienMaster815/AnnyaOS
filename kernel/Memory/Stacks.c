#define _STACK_INTERNALS_
#include <LouAPI.h>

UNUSED static LOUSINE_STACK    StackObjectList = {0};
UNUSED static mutex_t          StackObjectLock = {0}; 

static PLOUSINE_STACK AllocateNewStackObject(){
    PLOUSINE_STACK TmpStack = &StackObjectList;
    MutexLock(&StackObjectLock);
    while(TmpStack->Peers.NextHeader){
        TmpStack = (PLOUSINE_STACK)TmpStack->Peers.NextHeader;
    }
    TmpStack->Peers.NextHeader = (PListHeader)LouKeMallocType(LOUSINE_STACK, KERNEL_GENERIC_MEMORY);
    TmpStack = (PLOUSINE_STACK)TmpStack->Peers.NextHeader;
    MutexUnlock(&StackObjectLock);
    return TmpStack;
}

UNUSED static void FreeStackObject(PLOUSINE_STACK StackObject){
    PLOUSINE_STACK TmpStack = &StackObjectList;
    PLOUSINE_STACK Follower;
    MutexLock(&StackObjectLock);
    while(TmpStack->Peers.NextHeader){
        Follower = TmpStack;
        TmpStack = (PLOUSINE_STACK)TmpStack->Peers.NextHeader;
        if(TmpStack == StackObject){
            Follower->Peers.NextHeader = TmpStack->Peers.NextHeader;
            LouKeFree(StackObject);
            break;
        }
    }
    MutexUnlock(&StackObjectLock);
}

PLOUSINE_STACK 
LouKeCreateStack(
    SIZE VSize,
    SIZE CommitSize,
    UINT64 PageFlags
){
    //LouVMalloc(VSize, );
    PLOUSINE_STACK NewStack = AllocateNewStackObject();


    return NewStack;
}