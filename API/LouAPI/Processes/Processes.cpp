//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "ProcessPrivate.h"

static ListHeader MasterProcessList = {0};
static spinlock_t ProcessListLock = {0};
static KERNEL_REFERENCE TotalProcesses = {0};
static XARRAY ProcessThreadIDXa = {};

LOUAPI void DeAllocateSaveContext(uint64_t Context);
void DeallocateThreadHandle(PGENERIC_THREAD_DATA Thread);
LOUAPI PCFI_OBJECT LouKeLookupHandleToCfiObject(HANDLE LookupHandle, BOOL AOA64);

void LouKeTsmDestroyThreadHandle(
    PGENERIC_THREAD_DATA Thread
){
    LouKeFree(Thread->AfinityBitmap);
    if(Thread->StackBase > GetKSpaceBase()){
        LouKeFree((PVOID)Thread->StackBase);
    }else{
        LouKeVmmFreeVmBuffer((PVOID)Thread->StackBase, false); 
    }
    DeAllocateSaveContext(Thread->ContextStorage);
    DeAllocateSaveContext(Thread->InterruptStorage);
    LouKeXaFreeUint32(&ProcessThreadIDXa, Thread->ThreadID);
    DeallocateThreadHandle(Thread);
}


LOUAPI UINT64 GetCr3();

UINT32 AllocateThreadID(){
    UINT32 NewID = 1;
    LouKeXarrayAllocateUint32(&ProcessThreadIDXa, &NewID, 0x00, 0, KERNEL_GENERIC_MEMORY);
    return NewID;
}

LOUAPI
SIZE LouKePmGetProcessCount(){
    return LouKeGetReferenceCount(&TotalProcesses);
}

LOUAPI
uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);


static PGENERIC_PROCESS_DATA CreateProcessObject(string ProcessName){    
    LouKIRQL Irql; 
    PGENERIC_PROCESS_DATA NewProcessObject = LouKeMallocType(GENERIC_PROCESS_DATA , KERNEL_GENERIC_MEMORY);
    NewProcessObject->ProcessName = LouKeMallocArray(CHAR, strlen(ProcessName) + 1, USER_GENERIC_MEMORY);
    strncpy(NewProcessObject->ProcessName, ProcessName, strlen(ProcessName));

    LouKeAcquireSpinLock(&ProcessListLock, &Irql);
    LouKeListAddTail(&NewProcessObject->Peers, &MasterProcessList);
    LouKeAcquireReference(&TotalProcesses);
    LouKeReleaseSpinLock(&ProcessListLock, &Irql);

    return NewProcessObject;
}

UNUSED static void DestroyProcessObject(
    PGENERIC_PROCESS_DATA ProcessObject
){    
    LouKIRQL                Irql;
    LouKeAcquireSpinLock(&ProcessListLock, &Irql);
    LouKeListDeleteItem(&ProcessObject->Peers);
    LouKeReleaseSpinLock(&ProcessListLock, &Irql);
    LouKeFree(ProcessObject->ProcessName);
    LouKeFree(ProcessObject);
    LouKeXaFreeUint32(&ProcessThreadIDXa, ProcessObject->ProcessID);
}

static UINT32 AllocateProcessID(){
    UINT32 NewID = 0;
    LouKeXarrayAllocateUint32(&ProcessThreadIDXa, &NewID, 0x00, 0, KERNEL_GENERIC_MEMORY);
    return NewID;
}
void LouKeInitProceSchedTail(PGENERIC_PROCESS_DATA Process, size_t Proc);

LOUAPI
LOUSTATUS LouKeSectionInitNewProcess(
    PHPROCESS    Process,
    HANDLE      Section
);

LOUAPI
LOUSTATUS 
LouKeSectionGetEntryList(
    PGENERIC_PROCESS_DATA   Process,
    HANDLE                  Section,
    UINT64**                OutList
);

LOUAPI
LOUSTATUS LouKePmCreateProcessEx(
    PKHANDLE                        HandleOut,                       
    string                          ProcessName,
    HPROCESS                        ParentProcess,  
    UINT8                           Priority,                 
    HANDLE                          Section,
    HANDLE                          AccessToken,
    PLOUSINE_CREATE_PROCESS_PARAMS  Params 
){
    LOUSTATUS Status;
    LouPrint("LouKePmCreateProcessEx()\n");
    size_t Processors = GetNPROC();

    if(!ProcessName){
        return STATUS_INVALID_PARAMETER;
    }
    PGENERIC_PROCESS_DATA NewProcessObject = CreateProcessObject(ProcessName);
    if(HandleOut){
        *HandleOut = NewProcessObject; 
    }


    Status = LouKeRegisterObjectToObjectManager(
        NewProcessObject,
        sizeof(PGENERIC_PROCESS_DATA),
        ProcessName,
        0,
        0x00
    );
    if(Status != STATUS_SUCCESS){
        DestroyProcessObject(NewProcessObject);
        return Status;
    }

    NewProcessObject->ParentProcess = (PGENERIC_PROCESS_DATA)ParentProcess;
    NewProcessObject->ProcessPriority = Priority;
    NewProcessObject->ProcessSection = Section;
    NewProcessObject->ProcessAccessToken = AccessToken;
    NewProcessObject->ProcessID = AllocateProcessID();
    LouPrint("Creating Process:%s With ID:%d\n", ProcessName, NewProcessObject->ProcessID);
    if(Params){
        //TODO::
        LouPrint("LouKePmCreateProcessEx()::TODO\n");
        while(1){

        }
    }else{
        
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
        LouKeGetTime(&NewProcessObject->BlockTimeout);
        NewProcessObject->ProcessState = PROCESS_BLOCKED;   
    }

    if(strcmp(ProcessName, KERNEL_PROCESS_NAME)){
        NewProcessObject->PMLTree = LouKeVmmCreatePmlTable(); 
    }else {
        NewProcessObject->PMLTree = (GetCr3() + GetKSpaceBase());
    }

    if(Section){
        Status = LouKeSectionInitNewProcess(
            (PHPROCESS)NewProcessObject, 
            Section
        );

        if(Status != STATUS_SUCCESS){
            LouPrint("ERROR Unable To Initialize Process For Serction\n");
            return Status;
        }
    }

    if(Params){

    }else{
        for(size_t i = 0 ; i < Processors; i++){
            LouKeInitProceSchedTail(NewProcessObject, i);
        }
    }

    if(Section){
        HANDLE  ThreadOut;
    

        struct ProcessLoaderParameters{
            mutex_t                 Lock;
            UINT64*                 ModEntrys;
            SIZE                    StackReserve;
            SIZE                    StackCommit;
            SIZE                    HeapReserve;
            SIZE                    HeapCommit;
            UINT16                  Subsystem;
        };

        struct ProcessLoaderParameters* Tmp = LouKeMallocType(struct ProcessLoaderParameters, USER_GENERIC_MEMORY);

        Status = LouKeSectionGetEntryList(NewProcessObject, Section, &Tmp->ModEntrys);
        //HPROCESS    Process,
        //PVOID       Entry,
        //PVOID       Params,
        //UINT8       Priority
        if(Status != STATUS_SUCCESS){
            return Status;
        }

        MutexLock(&Tmp->Lock);

        PCOFF_PRIVATE_DATA CfiData = (PCOFF_PRIVATE_DATA)((PSECTION_OBJECT)Section)->SectionPrivateData; 
        PCFI_OBJECT TmpCfiObject;
        UINT64* DependList = CfiData->CfiObject.ModDependencies;
        for(size_t i = 0 ; i < *DependList; i++){
            TmpCfiObject = LouKeLookupHandleToCfiObject((HANDLE)DependList[i + 1], CfiData->CfiObject.AOA64);
            TmpCfiObject->CoffCommitSection(TmpCfiObject, NewProcessObject->PMLTree);
        }
        
        Tmp->StackReserve = CfiData->CfiObject.StackReserve;
        Tmp->StackCommit = CfiData->CfiObject.StackCommit;
        Tmp->HeapReserve = CfiData->CfiObject.HeapReserve;
        Tmp->HeapCommit = CfiData->CfiObject.HeapCommit;

        LouKePsmCreateThreadForProcess(
            &ThreadOut,
            (HPROCESS)NewProcessObject,
            (PVOID)LouKeLinkerGetAddress("LOUDLL.DLL", "LouProcessInitThread"),
            Tmp,
            Tmp->StackReserve,
            Tmp->StackCommit,
            31
        );

        MutexSynchronize(&Tmp->Lock);
        LouKeFree(Tmp->ModEntrys);
        LouKeFree(Tmp);

    }

    LouPrint("LouKePmCreateProcessEx() STATUS_SUCCESS\n");
    
    return STATUS_SUCCESS;
}

LOUSTATUS LouKePsmGetProcessData(
    string   ProcessName,
    PKHANDLE OutHandle
){
    if((!ProcessName) || (!OutHandle)){
        return STATUS_INVALID_PARAMETER;
    }
    LouKIRQL Irql;
    PGENERIC_PROCESS_DATA TmpHandle;
    LouKeAcquireSpinLock(&ProcessListLock, &Irql);
    ForEachListEntry(TmpHandle, &MasterProcessList, Peers){
        ForEachIf(!strcmp(TmpHandle->ProcessName, ProcessName)){
            *OutHandle = (HANDLE)TmpHandle;
            LouKeReleaseSpinLock(&ProcessListLock, &Irql);
            return STATUS_SUCCESS;
        }
    }
    LouKeReleaseSpinLock(&ProcessListLock, &Irql);
    *OutHandle = 0x00;
    return STATUS_NO_SUCH_FILE;
}

LOUAPI
uint64_t 
LouKePsmGetProcessPml4(uint32_t ProcessID){
    PGENERIC_PROCESS_DATA TmpHandle;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&ProcessListLock, &Irql);
    ForEachListEntry(TmpHandle, &MasterProcessList, Peers){
        if(ProcessID == TmpHandle->ProcessID){
            LouKeReleaseSpinLock(&ProcessListLock, &Irql);
            return (TmpHandle->PMLTree - GetKSpaceBase());
        }
    }
    LouKeReleaseSpinLock(&ProcessListLock, &Irql);
    return 0x00;
}

LOUAPI
LOUSTATUS LouKePmCreateProcessExCall(
    PHPROCESS                       HandleOut,                       
    string                          ProcessName,
    HPROCESS                        ParentProcess,  
    UINT8                           Priority,                 
    HANDLE                          Section,
    HANDLE                          AccessToken,
    PLOUSINE_CREATE_PROCESS_PARAMS  Params 
){
    HANDLE NewHandle;
    LOUSTATUS Status = LouKePmCreateProcessEx(
        &NewHandle,                       
        ProcessName,
        LouKeGetObjectFromHandle((HANDLE)ParentProcess),  
        Priority,                 
        LouKeGetObjectFromHandle(Section),
        AccessToken,
        Params 
    );
    if(Status != STATUS_SUCCESS){
        NewHandle = 0;
        return Status;
    }

    PLOUSINE_ACCESS_TOKEN CurrentAccessToken;
    HANDLE AccessTokenHandle = LouKePsmGetCurrentProcessAccessToken();
    Status = LouKeZwGetAccessTokenData(&CurrentAccessToken, AccessTokenHandle);
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR:Invalid Parameter To LouKeZwGetAccessTokenData()\n");
        return Status;
    }
    
    if(HandleOut){
        HANDLE UserHandle;
        Status = LouKeAcquireHandleForObject(
            &UserHandle,
            NewHandle, 
            CurrentAccessToken->CurrentAccess
        );
        if(Status != STATUS_SUCCESS){
            return Status;
        }

        *HandleOut = UserHandle;
    }
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS
LouKeGetProcessName(
    KHANDLE                 ProcessHandle,
    PSTRING                 ProcessNameOut 
){
    if(!ProcessHandle || !ProcessNameOut){
        return STATUS_INVALID_PARAMETER;
    }   
    return LouKeRtlInitStringEx(
        ProcessNameOut,
        (PCSTR)((PGENERIC_PROCESS_DATA)ProcessHandle)->ProcessName
    );
}

LOUAPI
LOUSTATUS
LouKeGetProcessNameCall(
    HANDLE  ProcessHandle,
    PSTRING ProcessNameOut
){
    return LouKeGetProcessName(
        LouKeGetObjectFromHandle(ProcessHandle),
        ProcessNameOut
    );
}

LOUAPI 
LOUSTATUS
LouKeGetCurrentProcessHandle(
    PKHANDLE     OutHandle
){
    if(!OutHandle){
        return STATUS_INVALID_PARAMETER;
    }
    *OutHandle = (KHANDLE)LouKeGetCurrentProcessData();
    return (*OutHandle ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL);
}

LOUAPI 
LOUSTATUS
LouKeGetCurrentProcessHandleCall(
    PHANDLE     OutHandle,
    ACCESS_MASK RequestedAccess
){
    LOUSTATUS Status;
    PLOUSINE_ACCESS_TOKEN CurrentAccessToken;
    HANDLE AccessTokenHandle = LouKePsmGetCurrentProcessAccessToken();
    Status = LouKeZwGetAccessTokenData(&CurrentAccessToken, AccessTokenHandle);
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR:Invalid Parameter To LouKeZwGetAccessTokenData()\n");
        return Status;
    }
    KHANDLE ProcessData = 0x00;
    Status = LouKeGetCurrentProcessHandle(&ProcessData);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    Status = LouKeAcquireHandleForObject(
        OutHandle,
        ProcessData, 
        RequestedAccess
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    return STATUS_SUCCESS;
}

LOUAPI
void
LouKePutCurrentProcessHandleCall(
    HANDLE Handle
){
    LouKeReleaseHandleFromObject(Handle, 0x00);
}