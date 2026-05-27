#define _IPC_INTERNALS
#include <LouAPI.h>

typedef struct _LOU_IPC_MESSAGE{
    ListHeader          Peers;
    BOOLEAN             MessageCompleted;
    UINT64              MessageID;
    PVOID               Data;
    SIZE                DataSize;
    LOU_IPC_CALLBACK    Callback;
}LOU_IPC_MESSAGE, * PLOU_IPC_MESSAGE;

typedef struct _LOU_IPC_MANAGER{
    HPROCESS            Process;
    mutex_t             Lock;
    ListHeader          Messages;
    LOU_IPC_CALLBACK    Callback;
}LOU_IPC_MANAGER, * PLOU_IPC_MANAGER;

static XARRAY ProcessIpcManagers = {0};

KERNEL_EXPORT 
LOUSTATUS
LouKeCreateIpcManagerForProcess(
    PLOU_IPC_MANAGER*   OutManagerOpt,
    LOU_IPC_CALLBACK    Callback
){

    ULONG ProcessID = LouKeGetProcessIdentification(); 
    if(LouKeXaIsIndexUsed(&ProcessIpcManagers, ProcessID)){
        return STATUS_UNSUCCESSFUL;
    }
    PLOU_IPC_MANAGER NewManager = LouKeMallocType(LOU_IPC_MANAGER, KERNEL_GENERIC_MEMORY);
    if(!NewManager){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    LOUSTATUS Status = LouKeGetCurrentProcessHandle(&NewManager->Process);
    if(Status != STATUS_SUCCESS){
        goto _ERROR_OUT;
    }
    NewManager->Callback = Callback;
    LouKeXaStore(&ProcessIpcManagers, ProcessID, NewManager, KERNEL_GENERIC_MEMORY);
    if(OutManagerOpt){
        *OutManagerOpt = NewManager;
    }
    return STATUS_SUCCESS;
    
_ERROR_OUT:
    LouKeFree(NewManager);
    return Status;
}

KERNEL_EXPORT
LOUSTATUS
LouKeIpcCreateIpcMessage(
    PLOU_IPC_MESSAGE*   OutMessage,
    UINT64              MessageID,
    PVOID               Data,
    SIZE                DataSize
){
    if(!OutMessage){
        return STATUS_INVALID_PARAMETER;
    }
    PLOU_IPC_MESSAGE NewMessage = LouKeMallocType(LOU_IPC_MESSAGE, USER_GENERIC_MEMORY);
    NewMessage->MessageID = MessageID;
    NewMessage->Data = Data; 
    NewMessage->DataSize = DataSize;
    *OutMessage = NewMessage;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeIpcSendIpcEx(
    PLOU_IPC_MANAGER    Manager,
    PLOU_IPC_MESSAGE    Message
){
    MutexLock(&Manager->Lock);
    Message->Callback = Manager->Callback;
    LouKeListAddTail(&Message->Peers, &Manager->Messages);
    MutexUnlock(&Manager->Lock);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeIpcSendIpc(
    LPWSTR              ProcessName,
    PLOU_IPC_MESSAGE    Message
){
    KHANDLE KHandle;
    LOUSTATUS Status = LouKePsmGetProcessDataW(ProcessName, &KHandle);    
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    ULONG ProcessID = LouKeGetHProcessID(KHandle);
    UINT64 Out;
    LouKeXaGet(
        &ProcessIpcManagers,
        ProcessID,
        &Out
    );
    PLOU_IPC_MANAGER ProcessManager = (PLOU_IPC_MANAGER)Out;    
    return LouKeIpcSendIpcEx(ProcessManager, Message);
}

KERNEL_EXPORT
LOUSTATUS
LouKeIpcGetIpcEx(
    PLOU_IPC_MANAGER    Manager,
    PLOU_IPC_MESSAGE*   OutMessage,
    BOOLEAN             WaitForMessage
){
    if((!Manager) || (!OutMessage)){
        return STATUS_INVALID_PARAMETER;
    }
    MutexLock(&Manager->Lock);
    while(!ListItemToTypeOrNull(Manager->Messages.NextHeader, LOU_IPC_MESSAGE, Peers)){
        if(!WaitForMessage){
            *OutMessage = 0x00;
            return STATUS_UNSUCCESSFUL;
        }
        LouKeYeildExecution();
    }   
    *OutMessage = ListItemToTypeOrNull(Manager->Messages.NextHeader, LOU_IPC_MESSAGE, Peers);
    LouKeListDeleteItem(Manager->Messages.NextHeader);
    MutexUnlock(&Manager->Lock);    
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS
LouKeIpcGetIpc(
    PLOU_IPC_MESSAGE*   OutMessage,
    BOOLEAN             WaitForMessage
){
    UINT64 Out;
    LouKeXaGet(
        &ProcessIpcManagers,
        LouKeGetProcessIdentification(),
        &Out
    );

    PLOU_IPC_MANAGER ProcessManager = (PLOU_IPC_MANAGER)Out;    

    return LouKeIpcGetIpcEx(
        ProcessManager,
        OutMessage,
        WaitForMessage
    );
}

KERNEL_EXPORT
void
LouKeIpcDestroyMessage(
    PLOU_IPC_MESSAGE Message
){
    LouKeFree(Message);
}