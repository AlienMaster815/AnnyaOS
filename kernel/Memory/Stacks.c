#define _STACK_INTERNALS_
#include <LouAPI.h>

static ListHeader   StackObjectList = {0};
static mutex_t      StackObjectLock = {0}; 
typedef PVOID PVMM_ALLOCATION_TRACKER;

LOUSTATUS
LouKeVmmCommitPageAddressEx(
    PVOID                   Address, 
    PVMM_ALLOCATION_TRACKER In,
    SIZE                    Commits,
    UINT32                  ProcessID,
    BOOLEAN                 Force
);

BOOLEAN
LouKeVmmAddressCausePageFault(
    PVOID Address, 
    PVMM_ALLOCATION_TRACKER* Out
);

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
    SIZE    CommitSize,
    BOOLEAN HighMem,
    UINT64  PageFlags
){
    PLOUSINE_STACK NewStack = AllocateNewStackObject();
    NewStack->Stack = HighMem ? LouKeAllocateVmmBuffer64Ex2(ProcessID, VSize, 16, false, false, PageFlags) : LouKeAllocateVmmBuffer32Ex2(ProcessID, VSize, 16, false, false, PageFlags);
    PVMM_ALLOCATION_TRACKER StackTracker;
    LouKeVmmAddressCausePageFault(NewStack->Stack, &StackTracker);
    
    UINT64 CommitBase = ROUND_DOWN64(((UINT64)NewStack->Stack + VSize) - CommitSize, MEGABYTE_PAGE);
    CommitSize = ROUND_UP64(CommitSize, MEGABYTE_PAGE);


    LouKeVmmCommitPageAddressEx((PVOID)CommitBase, StackTracker, CommitSize / MEGABYTE_PAGE, ProcessID, true);

    return NewStack->Stack;
}