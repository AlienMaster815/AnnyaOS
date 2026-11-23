#include "../UsbCore.h"

void UsbCoreHcdIoQueueManager(PVOID Params){
    PTHREAD Thread = LouKeGetCurrentThreadHandle();
    PUSB_HCD_OBJECT HcdObject = (PUSB_HCD_OBJECT)(UINT8*)Params;
    BOOLEAN CommandPolled;
    PUSB_TRANSFER_OBJECT TransferObject;    
    PUSB_TRANSFER_OBJECT TransferObjectSafe;
    BOOLEAN NewHandofEntries;
    while(1){
        MutexLock(&HcdObject->IoQueueLock);
        TransferObject = ListItemToTypeOrNull(HcdObject->IoQueueItems.NextHeader, USB_TRANSFER_OBJECT, Peers);
        if(!TransferObject){
            MutexUnlock(&HcdObject->IoQueueLock);
            LouKeBlockThread(Thread);
            continue;
        }
        NewHandofEntries = false;
        MutexLock(&HcdObject->HandoffLock);
        ForEachListEntrySafe(TransferObject, TransferObjectSafe, &HcdObject->IoQueueItems, Peers){
            HcdObject->Operations->CommitTransfer(TransferObject);
            LouKeListDeleteItem(&TransferObject->Peers);
            LouKeListAddTail(&TransferObject->Peers, &HcdObject->HandoffQueue);
            NewHandofEntries = true;
        }
        MutexUnlock(&HcdObject->HandoffLock);
        MutexUnlock(&HcdObject->IoQueueLock);
        if(NewHandofEntries){
            LouKeUnblockThread(HcdObject->IoDeQueueManager);
        }
    }
}


void UsbCoreHcdIoDeQueueManager(PVOID Params){
    PTHREAD Thread = LouKeGetCurrentThreadHandle();
    PUSB_HCD_OBJECT HcdObject = (PUSB_HCD_OBJECT)(UINT8*)Params;
    BOOLEAN CommandPolled;
    PUSB_TRANSFER_OBJECT TransferObject;
    PUSB_TRANSFER_OBJECT TransferObjectSafe;
    LOUSTATUS CmdStatus;
    while(1){
        MutexLock(&HcdObject->HandoffLock);
        if(HcdObject->HandoffQueue.NextHeader){
            LouKeListAddTail(HcdObject->HandoffQueue.NextHeader, &HcdObject->IoDeQueueItems);
            LouKeListDeleteAll(&HcdObject->HandoffQueue);
        }
        MutexUnlock(&HcdObject->HandoffLock);
            
        MutexLock(&HcdObject->IoDeQueueLock);
        TransferObject = ListItemToTypeOrNull(HcdObject->IoDeQueueItems.NextHeader, USB_TRANSFER_OBJECT, Peers);
        if(!TransferObject){
            MutexUnlock(&HcdObject->IoDeQueueLock);
            LouKeBlockThread(Thread);
            continue;
        }
        ForEachListEntrySafe(TransferObject, TransferObjectSafe, &HcdObject->IoDeQueueItems, Peers){
            CmdStatus = HcdObject->Operations->GetTransferStatus(TransferObject);
            if(CmdStatus != STATUS_NO_WORK_DONE){
                LouKeListDeleteItem(&TransferObject->Peers);
                LouKeDmaSignalDmaFence(&TransferObject->Transfer->DmaFence);
                if(HcdObject->Operations->CleanupTransfer){
                    LOUSTATUS CleanupStatus = HcdObject->Operations->CleanupTransfer(TransferObject);
                    if(CleanupStatus != STATUS_SUCCESS){
                        LouPrint("UsbCoreHcdIoDeQueueManager():HERE\n");
                        while(1);
                    }
                }
            }
        }
        MutexUnlock(&HcdObject->IoDeQueueLock);
    }
}

void UsbCoreCommitUsbTransferToCommandEngine(
    PUSB_TRANSFER_OBJECT    TransferObject,
    int                     MsTimeout
){

    LouKeSetupDmaTransferFence(TransferObject->Transfer, MsTimeout);
    PUSB_HCD_OBJECT HcdObject = TransferObject->UsbDevice->Hcd;
    LouKIRQL Irql;
    if(HcdObject->Operations->PrepTransfer){
        HcdObject->Operations->PrepTransfer(TransferObject);
    }
    MutexLock(&HcdObject->IoQueueLock);
    LouKeListAddTail(&TransferObject->Peers, &HcdObject->IoQueueItems);
    MutexUnlock(&HcdObject->IoQueueLock);
    LouKeUnblockThread(HcdObject->IoQueueManager);
}

LOUSTATUS 
UsbCoreFenceTransferObject(
    PUSB_TRANSFER_OBJECT    TransferObject
){
    PUSB_HCD_OBJECT HcdObject = TransferObject->UsbDevice->Hcd;
    return LouKeFenceDmaTransfer(TransferObject->Transfer);
}