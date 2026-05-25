#define _IPC_INTERNALS
#include <LouAPI.h>

typedef struct _LOU_IPC_MESSAGE{
    ListHeader          Peers;
    BOOLEAN             MessageCompleted;
    UINT64              MessageID;
    PVOID               DataIn;
    SIZE                DataInSize;
}LOU_IPC_MESSAGE, * PLOU_IPC_MESSAGE;

typedef struct _LOU_IPC_MANAGER{
    HPROCESS            Process;
    spinlock_t          Lock;
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
    PVOID               DataIn,
    SIZE                DataInSize
){
    if(!OutMessage){
        return STATUS_INVALID_PARAMETER;
    }
    PLOU_IPC_MESSAGE NewMessage = *OutMessage;
    if(!NewMessage){
        NewMessage = LouKeMallocType(LOU_IPC_MESSAGE, USER_GENERIC_MEMORY);
    }
    NewMessage->MessageID = MessageID;
    if(DataIn && DataInSize){
        NewMessage->DataIn = LouKeMalloc(DataInSize, USER_GENERIC_MEMORY);
        memcpy(NewMessage->DataIn, DataIn, DataInSize);
    }else if(DataIn){
        NewMessage->DataIn = DataIn; 
    }
    NewMessage->DataInSize = DataInSize;
    *OutMessage = NewMessage;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeIpcSendIpcEx(
    PLOU_IPC_MANAGER    Manager,
    PLOU_IPC_MESSAGE    Message
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&Manager->Lock, &Irql);
    LouKeListAddTail(&Message->Peers, &Manager->Messages);
    LouKeReleaseSpinLock(&Manager->Lock, &Irql);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeIpcSendIpc(
    LPWSTR              ProcessName,
    PLOU_IPC_MESSAGE    Message
){
    

    return STATUS_SUCCESS; //LouKeIpcSendIpcEx(ProcessManager, Message);
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
    LouKIRQL Irql;
    while(!ListItemToTypeOrNull(Manager->Messages.NextHeader, LOU_IPC_MESSAGE, Peers)){
        if(!WaitForMessage){
            return STATUS_UNSUCCESSFUL;
        }
        LouKeYeildExecution();
    }   
    LouKeAcquireSpinLock(&Manager->Lock, &Irql);
    *OutMessage = ListItemToTypeOrNull(Manager->Messages.NextHeader, LOU_IPC_MESSAGE, Peers);
    LouKeListDeleteItem(Manager->Messages.NextHeader);
    LouKeReleaseSpinLock(&Manager->Lock, &Irql);
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
LOUSTATUS
LouKeIpcDestroyMessage(
    PLOU_IPC_MESSAGE Message
){
    if(!Message){
        return STATUS_INVALID_PARAMETER;
    }
    if(Message->DataIn && Message->DataInSize){
        LouKeFree(Message->DataIn);
    }
    LouKeFree(Message);
    return STATUS_SUCCESS;
}