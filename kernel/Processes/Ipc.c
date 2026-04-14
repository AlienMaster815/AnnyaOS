#include <LouAPI.h>

typedef LOUSTATUS (*LOU_IPC_CALLBACK)(UINT64 MessageID, PVOID DataIn, POVID* DataOut);

typedef struct _LOU_IPC_MESSAGE{
    ListHeader          Peers;
    LOU_IPC_CALLBACK    Callback;
    UINT64              MessageID;
    PVOID               DataIn;
    PVOID*              DataOut;
}LOU_IPC_MESSAGE, * PLOU_IPC_MESSAGE;

typedef struct _LOU_IPC_MANAGER{
    HPROCESS    Process;
    spinlock_t  Lock;
    ListHeader  Messages;
}LOU_IPC_MANAGER, * PLOU_IPC_MANAGER;

KERNEL_EXPORT
LOUSTATUS
LouKeIpcCreateIpcMessage(
    PLOU_IPC_MESSAGE*   NewMessage,
    LOU_IPC_CALLBACK    Callback,
    UINT64              MessageID,
    PVOID               DataIn,
    PVOID*              DataOut
){
    if(!NewMessage){
        return STATUS_INVALID_PARAMETER;
    }
    PLOU_IPC_MESSAGE NewMessage = *NewMessage;
    if(!NewMessage){
        NewMessage = LouKeMallocType(LOU_IPC_MESSAGE, USER_GENERIC_MEMORY);
    }

    NewMessage->Callback = Callback;
    NewMessage->MessageID = MessageID;
    NewMessage->DataIn = DataIn;
    NewMessage->DataOut = DataOut;

    *NewMessage = NewMessage;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS 
LouKeIpcSendIpc(
    PLOU_IPC_MANAGER    Manager
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
LouKeIpcGetIpc(
    PLOU_IPC_MANAGER    Manager,
    PLOU_IPC_MESSAGE*   OutMessage,
    BOOLEAN             WaitForMessage
){
    if((!Manager) || (!OutMessage)){
        return STATUS_INVALID_PARAMETER;
    }
    LouKIRQL Irql;
    while(!ListItemToTypeOrNull(Manager->Messages.NextHeader)){
        if(!WaitForMessage){
            return STATUS_UNSUCCESSFUL;
        }
        LouKeYeildExecution();
    }   
    LouKeAcquireSpinLock(&Manager->Lock, &Irql);
    *OutMessage = ListItemToTypeOrNull(Manager->Messages.NextHeader);
    LouKeListDeleteItem(Manager->Messages.NextHeader);
    LouKeReleaseSpinLock(&Manager->Lock, &Irql);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS
LouKeIpcDestroyMessage(
    PLOU_IPC_MESSAGE Message
){
    if(!Message){
        return STATUS_INVALID_PARAMETER;
    }
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&Manager->Lock, &Irql);
    LouKeListDeleteItem(&Message->Peers);
    LouKeFree(Message);
    LouKeReleasSpinLock(&Manager->Lock, &Irql);
    return STATUS_SUCCESS;
}