//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "ProcessPrivate.h"

static ListHeader MasterProcessList = {0};
static spinlock_t ProcessListLock = {0};
static KERNEL_REFERENCE TotalProcesses = {0};
static XARRAY ProcessThreadIDXa = {};

LOUAPI void DeAllocateSaveContext(uint64_t Context);
void DeallocateThreadHandle(PGENERIC_THREAD_DATA Thread);

void LouKeTsmDestroyThreadHandle(
    PGENERIC_THREAD_DATA Thread
){
    LouKeFree(Thread->AfinityBitmap);
    if(Thread->StackBase > GetKSpaceBase()){
        LouKeFree((PVOID)Thread->StackBase);
    }else{
        LouKeVmmFreeVmBuffer((PVOID)Thread->StackBase); 
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
    NewProcessObject->ProcessName = LouKeMallocArray(CHAR, strlen(ProcessName) + 1, KERNEL_GENERIC_MEMORY);
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
    HANDLE      Section,
    UINT64**    OutList
);

LOUSTATUS LouKePmCreateProcessEx(
    PHPROCESS                       HandleOut,                       
    string                          ProcessName,
    PHPROCESS                       ParentProcess,  
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
    
    NewProcessObject->ParentProcess = (PGENERIC_PROCESS_DATA)ParentProcess;
    NewProcessObject->ProcessPriority = Priority;
    NewProcessObject->ProcessSection = Section;
    NewProcessObject->ProcessAccessToken = AccessToken;
    NewProcessObject->ProcessID = AllocateProcessID();
    LouPrint("Creating Process With ID:%d\n", NewProcessObject->ProcessID);
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
        };

        struct ProcessLoaderParameters* Tmp = LouKeMallocType(struct ProcessLoaderParameters, USER_GENERIC_MEMORY);

        UINT64* EntryList;
        Status = LouKeSectionGetEntryList(Section, &EntryList);
        //HPROCESS    Process,
        //PVOID       Entry,
        //PVOID       Params,
        //UINT8       Priority
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        MutexLock(&Tmp->Lock);

        Tmp->ModEntrys = EntryList;

        LouKePsmCreateThreadForProcess(
            &ThreadOut,
            (HPROCESS)NewProcessObject,
            (PVOID)LouKeLinkerGetAddress("LOUDLL.DLL", "LouProcessInitThread"),
            Tmp,
            15
        );

        MutexSynchronize(&Tmp->Lock);

        LouKeFree(EntryList);

        LouKeFree(Tmp);
    }

    LouPrint("LouKePmCreateProcessEx() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUSTATUS LouKePsmGetProcessData(
    string  ProcessName,
    PHANDLE OutHandle
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