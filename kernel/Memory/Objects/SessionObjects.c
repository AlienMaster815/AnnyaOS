#include "ObjectManager.h"

static SESSION_OBJECT_CHAIN SessionsList = {0};
static mutex_t SessionsLock = {0};

static PVOID AllocateSessionHandle(){
    PSESSION_OBJECT_CHAIN Tmp = &SessionsList;
    MutexLock(&SessionsLock);

    while(Tmp->Peers.NextHeader){
        Tmp = (PSESSION_OBJECT_CHAIN)Tmp->Peers.NextHeader; 
    }
    Tmp->Peers.NextHeader = (PListHeader)AllocateSessionTracker();
    MutexUnlock(&SessionsLock);
    return (PVOID)Tmp->Peers.NextHeader;
}

LOUSTATUS LouKeAllocateSesionHandle(
    PHANDLE OutHandle,
    PVOID   HandleData
){

    PSESSION_OBJECT_CHAIN NewHandle = (PSESSION_OBJECT_CHAIN)AllocateSessionHandle();

    NewHandle->SessionHandle.HandleTie = HandleData;
    NewHandle->SessionHandle.HandleID = 0;

    if(OutHandle){
        *OutHandle = (HANDLE)NewHandle->SessionHandle.HandleID;
    }

    return STATUS_SUCCESS;
}