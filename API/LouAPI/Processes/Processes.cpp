#include "ProcessPrivate.h"

static GENERIC_PROCESS_DATA MasterProcessList = {0};
static mutex_t ProcessListLock = {0};

static PGENERIC_PROCESS_DATA CreateProcessObject(string ProcessName){

    PGENERIC_PROCESS_DATA TmpProcessObject = &MasterProcessList;
    MutexLock(&ProcessListLock);
    while(TmpProcessObject->Peers.NextHeader){
        TmpProcessObject = (PGENERIC_PROCESS_DATA)TmpProcessObject->Peers.NextHeader;
    }
    TmpProcessObject->Peers.NextHeader = (PListHeader)LouKeMallocType(GENERIC_PROCESS_DATA, KERNEL_GENERIC_MEMORY);
    TmpProcessObject = (PGENERIC_PROCESS_DATA)TmpProcessObject->Peers.NextHeader;
    TmpProcessObject->ProcessName = LouKeMallocArray(CHAR, strlen(ProcessName) + 1, KERNEL_GENERIC_MEMORY);
    strncpy(TmpProcessObject->ProcessName, ProcessName, strlen(ProcessName));
    MutexUnlock(&ProcessListLock);
    return TmpProcessObject;
}

UNUSED static void DestroyProcessObject(
    PGENERIC_PROCESS_DATA ProcessObject
){
    PGENERIC_PROCESS_DATA TmpProcessObject = &MasterProcessList;
    MutexLock(&ProcessListLock);
    while(TmpProcessObject->Peers.NextHeader){
        if((PGENERIC_PROCESS_DATA)TmpProcessObject->Peers.NextHeader == ProcessObject){
            TmpProcessObject->Peers.NextHeader = ((PGENERIC_PROCESS_DATA)TmpProcessObject->Peers.NextHeader)->Peers.NextHeader;
            LouKeFree(ProcessObject->ProcessName);
            LouKeFree(ProcessObject);
            MutexUnlock(&ProcessListLock);
            return;
        }
        TmpProcessObject = (PGENERIC_PROCESS_DATA)TmpProcessObject->Peers.NextHeader;
    }
    MutexUnlock(&ProcessListLock);
}

static UINT16 AllocateProcessID(){
    UINT16 Result = 1;
    BOOL FoundID = false;
    while(!FoundID){
        FoundID = true;
        PGENERIC_PROCESS_DATA TmpProcessHandle = &MasterProcessList;
        while(TmpProcessHandle->Peers.NextHeader){
            TmpProcessHandle = (PGENERIC_PROCESS_DATA)TmpProcessHandle->Peers.NextHeader;
            if(Result == TmpProcessHandle->ProcessID){
                Result++;
                FoundID = false;
                break;
            }
        }
    }
    return Result;
}

LOUSTATUS LouKePmCreateProcessEx(
    PHPROCESS                       HandleOut,                       
    string                          ProcessName,
    PHPROCESS                       ParentProcess,  
    UINT8                           Priority,                 
    HANDLE                          Section,
    PLOUSINE_CREATE_PROCESS_PARAMS  Params 
){
    LouPrint("LouKePmCreateProcessEx()\n");

    if(!ProcessName){
        return STATUS_INVALID_PARAMETER;
    }
    PGENERIC_PROCESS_DATA NewProcessObject = CreateProcessObject(ProcessName);
    if(HandleOut){
        *HandleOut = NewProcessObject; 
    }
    
    NewProcessObject->ParentProcess = (PGENERIC_PROCESS_DATA)ParentProcess;
    NewProcessObject->ProcessPriority = Priority;
    NewProcessObject->ProcessSection = Section;

    if(Params){
        //TODO::
        LouPrint("LouKePmCreateProcessEx()::TODO\n");
        while(1){

        }
    }else{
        size_t Processors = GetNPROC();
        NewProcessObject->ThreadObjects = LouKeMallocArray(THREAD_SCHEDUAL_MANAGER, Processors , KERNEL_GENERIC_MEMORY);
        PTHREAD_SCHEDUAL_MANAGER Tsm = NewProcessObject->ThreadObjects;
        for(size_t i = 0 ; i < Processors; i++){
            Tsm[i].TsmInitializeSchedualerObject(
                i,
                NewProcessObject,
                THREAD_PRIORITY_RINGS,
                THREAD_DEFAULT_DISTRIBUTER_INCREMENTER
            );
        }
        NewProcessObject->TotalMsSlice = 100;   
    }

    NewProcessObject->ProcessID = AllocateProcessID();
    NewProcessObject->PMLTree = LouKeVmmCreatePmlTable(); 

    LouPrint("LouKePmCreateProcessEx() STATUS_SUCCESS\n");
    
    return STATUS_SUCCESS;
}

LOUSTATUS LouKePsmGetProcessHandle(
    string  ProcessName,
    PHANDLE OutHandle
){
    if((!ProcessName) || (!OutHandle)){
        return STATUS_INVALID_PARAMETER;
    }

    PGENERIC_PROCESS_DATA TmpHandle = &MasterProcessList;
    while(TmpHandle->Peers.NextHeader){
        TmpHandle = (PGENERIC_PROCESS_DATA)TmpHandle->Peers.NextHeader;
        if(!strcmp(TmpHandle->ProcessName, ProcessName)){
            *OutHandle = (HANDLE)TmpHandle;
            return STATUS_SUCCESS;
        }
    }
    *OutHandle = 0x00;
    return STATUS_NO_SUCH_FILE;
}