#include "../UsbCore.h"

void UsbCoreHcdIoQueueManager(PVOID Params){
    PUSB_HCD_OBJECT HcdObject = (PUSB_HCD_OBJECT)(UINT8*)Params;
    PTHREAD Thread = LouKeGetCurrentThreadHandle();
    BOOLEAN CommandPolled;
    LouKIRQL Irql;
    PUSB_TRANSFER_OBJECT TransferObject;    
    PUSB_TRANSFER_OBJECT TransferObjectSafe;
    BOOLEAN NewHandofEntries;
    while(1){
        LouKeAcquireInterruptLock(&HcdObject->IoQueueLock, &Irql);
        TransferObject = ListItemToTypeOrNull(HcdObject->IoQueueItems.NextHeader, USB_TRANSFER_OBJECT, Peers);
        if(!TransferObject){
            LouKeReleaseInterruptLock(&HcdObject->IoQueueLock, &Irql);
            LouKeBlockThread(Thread);
            continue;
        }
        NewHandofEntries = false;
        AtomicLock(&HcdObject->HandoffLock);
        ForEachListEntrySafe(TransferObject, TransferObjectSafe, &HcdObject->IoQueueItems, Peers){
            LouKeListDeleteItem(&TransferObject->Peers);
            HcdObject->Operations->CommitTransfer(TransferObject);
            LouKeListAddTail(&TransferObject->Peers, &HcdObject->HandoffQueue);
            NewHandofEntries = true;
        }
        AtomicUnlock(&HcdObject->HandoffLock);
        LouKeReleaseInterruptLock(&HcdObject->IoQueueLock, &Irql);
        if(NewHandofEntries){
            LouKeUnblockThread(HcdObject->IoDeQueueManager);
        }
        LouKeYieldExecution();
    }
}


void UsbCoreHcdIoDeQueueManager(PVOID Params){
    PUSB_HCD_OBJECT HcdObject = (PUSB_HCD_OBJECT)(UINT8*)Params;
    PTHREAD Thread = LouKeGetCurrentThreadHandle();
    BOOLEAN CommandPolled;
    PUSB_TRANSFER_OBJECT TransferObject;
    PUSB_TRANSFER_OBJECT TransferObjectSafe;
    LouKIRQL Irql;
    LOUSTATUS CmdStatus;
    while(1){
        LouKeAcquireInterruptLock(&HcdObject->IoDeQueueLock, &Irql);
        if(AtomicLockOrFalse(&HcdObject->HandoffLock)){
            if(HcdObject->HandoffQueue.NextHeader){
                LouKeListAddTail(HcdObject->HandoffQueue.NextHeader, &HcdObject->IoDeQueueItems);
                LouKeListDeleteAll(&HcdObject->HandoffQueue);
            }
            AtomicUnlock(&HcdObject->HandoffLock);
        }       
        TransferObject = ListItemToTypeOrNull(HcdObject->IoDeQueueItems.NextHeader, USB_TRANSFER_OBJECT, Peers);
        if(!TransferObject){
            LouKeReleaseInterruptLock(&HcdObject->IoDeQueueLock, &Irql);
            LouKeBlockThread(Thread);
            continue;
        }
        ForEachListEntrySafe(TransferObject, TransferObjectSafe, &HcdObject->IoDeQueueItems, Peers){
            CmdStatus = HcdObject->Operations->GetTransferStatus(TransferObject);
            if(CmdStatus != STATUS_NO_WORK_DONE){
                LouKeListDeleteItem(&TransferObject->Peers);
                LouKeDmaSignalDmaFence(&TransferObject->Transfer->DmaFence);
            }
        }
        LouKeReleaseInterruptLock(&HcdObject->IoDeQueueLock, &Irql);
        LouKeYieldExecution();
    }
}

void UsbCoreCommitUsbTransferToCommandEngine(
    PUSB_TRANSFER_OBJECT    TransferObject,
    int                     MsTimeout
){
    LouKeSetupDmaTransferFence(TransferObject->Transfer, MsTimeout);
    PUSB_HCD_OBJECT HcdObject = TransferObject->UsbDevice->Hcd;
    LouKIRQL Irql;
    LouKeAcquireInterruptLock(&HcdObject->IoQueueLock, &Irql);
    LouKeListAddTail(&TransferObject->Peers, &HcdObject->IoQueueItems);
    LouKeReleaseInterruptLock(&HcdObject->IoQueueLock, &Irql);
    LouKeUnblockThread(HcdObject->IoQueueManager);
}

LOUSTATUS 
UsbCoreFenceTransferObject(
    PUSB_TRANSFER_OBJECT    TransferObject
){
    return LouKeFenceDmaTransfer(TransferObject->Transfer);
}