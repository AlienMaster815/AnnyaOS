#include "MSVCRT.h"

static MSVC_LOCK_TABLE_ENTRY MsvcLockTable[MSVC_TOTAL_LOCKS] = {0};

#define MsvCrtSetInitializationStatus(TableMember, Status) MsvcLockTable[(TableMember)].LockInitialized = ((bool)(Status))
#define IS_MSVC_LOCK_INITIALIZED(TableMember) MsvcLockTable[TableMember].LockInitialized == true

static inline void MsvcInitializeLock(int LockNumber){
    InitializeCriticalSectionEx(&MsvcLockTable[LockNumber].CriticalSection, 0, 0x10000000);
    MsvCrtSetInitializationStatus(LockNumber, true);
}

static inline void MsvcUninitializeLock(int LockNumber){
    DeleteCriticalSection(&MsvcLockTable[LockNumber].CriticalSection);
    MsvCrtSetInitializationStatus(LockNumber, false);
}

void MsvcInitializeLockSystem(){
    
    for(uint8_t i = 0; i < MSVC_TOTAL_LOCKS; i++){
        MsvCrtSetInitializationStatus(i, false);
    }

    MsvcInitializeLock(MSVC_LOCK_LOCK_TABLE);
    
}

MSVCRT_API 
void _lock(int LockNumber){
    if(!IS_MSVC_LOCK_INITIALIZED(LockNumber)){
        _lock(MSVC_LOCK_LOCK_TABLE);
        if(!IS_MSVC_LOCK_INITIALIZED(LockNumber)){
            LouPrint("Initializing Lock(%d)\n", LockNumber);
            MsvcInitializeLock(LockNumber);
        }
    }
    EnterCriticalSection(&MsvcLockTable[LockNumber].CriticalSection);
}

MSVCRT_API
void _unlock(int LockNumber){
    LeaveCriticalSection(&MsvcLockTable[LockNumber].CriticalSection);
}
