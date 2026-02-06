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
    LPWSTR  AcTokRegEntry,
    PVOID   HandleData
){

    if(!AcTokRegEntry){
        LouPrint("LouKeAllocateSesionHandle() (!AcTokRegEntry)\n");
        while(1);
    }
    PVOID AccessToken = 0x00;
    LOUSTATUS Status = LouKeOpenStoredAccessToken(&AccessToken, AcTokRegEntry);
    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeAllocateSesionHandle()\n");
        LouPrint("Unable To Open Stored Access Token\n");
        return Status;
    }


    PSESSION_OBJECT_CHAIN NewHandle = (PSESSION_OBJECT_CHAIN)AllocateSessionHandle();

    NewHandle->SessionHandle.HandleTie = HandleData;
    NewHandle->SessionHandle.HandleID = 0;
    NewHandle->SessionHandle.ClassTag = SESSION_OBJECT_CLASS_TAG;

    NewHandle->SessionHandle.Peers.NextHeader = (PListHeader)&NewHandle->AccessTokenHandle;
    NewHandle->AccessTokenHandle.HandleTie = 0;
    NewHandle->AccessTokenHandle.HandleID = 1;
    NewHandle->AccessTokenHandle.ClassTag = ACCESS_TOKEN_OBJECT_CLASS_TAG;

    if(OutHandle){
        *OutHandle = (HANDLE)NewHandle->SessionHandle.HandleID;
    }

    return STATUS_SUCCESS;
}