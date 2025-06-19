#include "DrsdCore.h"

static DRSD_MODE_SET_CONTEXT ModeSetManagerContextList;
static mutex_t ModeSetManagerLock;

PDRSD_MODE_SET_CONTEXT DrsdInitializeModeContext(PDRSD_DEVICE Device){
    MutexLock(&Device->ModeConfiguration.ConfigLock);
    MutexLockEx(&ModeSetManagerLock, true);
    
    PDRSD_MODE_SET_CONTEXT TmpContextList = &ModeSetManagerContextList;

    while(TmpContextList->Peers.NextHeader){
        TmpContextList = (PDRSD_MODE_SET_CONTEXT)TmpContextList->Peers.NextHeader;
    }

    TmpContextList->Peers.NextHeader = (PListHeader)LouKeMallocType(DRSD_MODE_SET_CONTEXT, KERNEL_GENERIC_MEMORY);
    TmpContextList = (PDRSD_MODE_SET_CONTEXT)TmpContextList->Peers.NextHeader;

    TmpContextList->Device = Device;
    MutexUnlock(&ModeSetManagerLock);
    return TmpContextList;
}

//returns true if device is being used
void DrsdModeSetLockContext(PDRSD_MODE_SET_CONTEXT Context){
    MutexLockEx(&ModeSetManagerLock, true);
    MutexLockEx(&Context->ModeSetLock, false);
    MutexUnlock(&ModeSetManagerLock);

}

void DrsdModeSetWarnIfLocked(PDRSD_DEVICE Device){
    MutexLockEx(&ModeSetManagerLock, true);
    if(MutexIsLocked(&Device->ModeConfiguration.ConnectionMutex)){
        LouPrint("WARNING:DrsdModeSetWarnIfLocked() CONFIG IS LOCKED\n");
    }    
    MutexUnlock(&ModeSetManagerLock);
}

void DrsdModeSetUnlockContext(PDRSD_MODE_SET_CONTEXT Setex){
    MutexLockEx(&ModeSetManagerLock, true);
    MutexUnlock(&Setex->ModeSetLock);
    MutexUnlock(&ModeSetManagerLock);
}

void DrsdModeSetDestroyModeContext(PDRSD_DEVICE Device, PDRSD_MODE_SET_CONTEXT Setex){
    MutexLockEx(&ModeSetManagerLock, true);
    PDRSD_MODE_SET_CONTEXT TmpContextList = &ModeSetManagerContextList;
    while(TmpContextList->Peers.NextHeader){
        if((uintptr_t)TmpContextList->Peers.NextHeader == (uintptr_t)Setex){
            TmpContextList->Peers.NextHeader = ((PDRSD_MODE_SET_CONTEXT)TmpContextList->Peers.NextHeader)->Peers.NextHeader;
            LouKeFree(Setex);
            break;
        }
        TmpContextList = (PDRSD_MODE_SET_CONTEXT)TmpContextList->Peers.NextHeader;
    }
    MutexUnlock(&ModeSetManagerLock);
    MutexUnlock(&Device->ModeConfiguration.ConfigLock);
}