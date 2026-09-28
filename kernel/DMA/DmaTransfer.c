#include <LouAPI.h>

//TODO LouKeCreateDmaTransfer

uint64_t read_tsc();
uint64_t GetTscMaster();

PLOUSINE_DMA_TRANSFER LouKeCreateDmaTransfer(PLOUSINE_DMA_DEVICE DmaDevice, SIZE AllocationSize, SIZE LowestAlignment){
    if(!DmaDevice){
        return 0x00;
    }
    else if(DmaDevice->DmaDeviceFlags & LOUSINE_DMA_DEVICE_FLAGS_USING_PRIVATE_DMA_ALLOCATOR){
        //TODO: Add PrivateDmaTransfers
        return 0x00;
    }
    LONG i = 0; 
    PLOUSINE_DMA_TRANSFER NewTransfer = LouKeMallocType(LOUSINE_DMA_TRANSFER, KERNEL_GENERIC_MEMORY);
    if(!NewTransfer){
        return 0x00;
    }
    if(AllocationSize > DmaDevice->AllocatorData.DmaThreshold){
        SIZE SgCount = (ROUND_UP64(AllocationSize, DmaDevice->AllocatorData.DmaThreshold) / DmaDevice->AllocatorData.DmaThreshold);
        NewTransfer->ScatteredTransfer = (PLOUSINE_SCATTER_DMA_TRANSFER)LouKeMallocEx(GetStructureSize(LOUSINE_SCATTER_DMA_TRANSFER, Transfers, SgCount), GET_ALIGNMENT(LOUSINE_SCATTER_DMA_TRANSFER), KERNEL_GENERIC_MEMORY);
        if(!NewTransfer->ScatteredTransfer){
            LouKeFree(NewTransfer);
            return 0x00;
        }
        NewTransfer->ScatteredTransfer->TransferCount = SgCount;
        NewTransfer->Type = LOUSINE_DMA_TRANSFER_TYPE_SCATTERED;

        for(; i < SgCount; i++){
            NewTransfer->ScatteredTransfer->Transfers[i].DmaSize = MIN(AllocationSize, DmaDevice->AllocatorData.DmaThreshold);
            SIZE Alignment = (NewTransfer->ScatteredTransfer->Transfers[i].DmaSize == DmaDevice->AllocatorData.DmaThreshold) ? DmaDevice->AllocatorData.DmaThreshold : LowestAlignment;
            NewTransfer->ScatteredTransfer->Transfers[i].DmaAddress = (UINTPTR)(UINT8*)LouKeDmaDeviceAllocateDmaMemory(DmaDevice, NewTransfer->ScatteredTransfer->Transfers[i].DmaSize, Alignment);
            if(!NewTransfer->ScatteredTransfer->Transfers[i].DmaAddress){
                goto _DMA_ALLOCATION_ERROR;
            }
            AllocationSize -= NewTransfer->ScatteredTransfer->Transfers[i].DmaSize;
        }
    }else{
        NewTransfer->Type = LOUSINE_DMA_TRANSFER_TYPE_STANDARD;
        NewTransfer->StandardTransfer.DmaAddress = (UINTPTR)(UINT8*)LouKeDmaDeviceAllocateDmaMemory(DmaDevice, AllocationSize, LowestAlignment); 
        if(!NewTransfer->StandardTransfer.DmaAddress){
            LouKeFree(NewTransfer);   
            return 0x00;
        }
        NewTransfer->StandardTransfer.DmaSize = AllocationSize;
    }
    NewTransfer->DmaDevice = DmaDevice;
    NewTransfer->DmaDone = 0;
    return NewTransfer;

_DMA_ALLOCATION_ERROR:
    while(i > 0){
        i--;
        LouKeDmaDeviceFreeDmaMemory(DmaDevice, (PVOID)(UINT8*)NewTransfer->ScatteredTransfer->Transfers[i].DmaAddress);
    }
    LouKeFree(NewTransfer->ScatteredTransfer);
    LouKeFree(NewTransfer);
    return 0x00;
}

KERNEL_EXPORT void LouKeDestroyDmaTransfer(PLOUSINE_DMA_TRANSFER Transfer){
    PLOUSINE_DMA_DEVICE DmaDevice = Transfer->DmaDevice;
    LONG i = 0; 
    switch(Transfer->Type){
        case LOUSINE_DMA_TRANSFER_TYPE_SCATTERED:{
            i = Transfer->ScatteredTransfer->TransferCount;
            while(i > 0){
                i--;
                LouKeDmaDeviceFreeDmaMemory(DmaDevice, (PVOID)(UINT8*)Transfer->ScatteredTransfer->Transfers[i].DmaAddress);
            }
            LouKeFree(Transfer->ScatteredTransfer);
            //fallthrought
        }
        default:
            LouKeFree(Transfer);
            break;
    }
}

KERNEL_EXPORT LOUSTATUS LouKeSetupDmaTransferFence(PLOUSINE_DMA_TRANSFER Transfer, int Wait, bool Poll){
    if(!Transfer){
        return STATUS_INVALID_PARAMETER;
    }
    MutexLock(&Transfer->DmaFence.DmaFenceFence);
    MutexLock(&Transfer->DmaFence.DmaFence);
    Transfer->DmaFence.Wait = Wait;
    Transfer->DmaFence.Poll = Poll;
    if(!Poll){
        Transfer->DmaFence.Thread = LouKeGetCurrentThreadHandle();
    }
    return STATUS_SUCCESS;
}

void _LouKeDmaSignalDmaFence(PLOUSINE_DMA_FENCE Fence){
    MutexSynchronizeNoBlocking(&Fence->DmaFence); //yeild till the fence is ready
    PLOUSINE_DMA_TRANSFER Transfer = CONTAINER_OF(Fence, LOUSINE_DMA_TRANSFER, DmaFence);
    Transfer->DmaDone = true;
    if(Fence->Thread){
        LouKeUnblockThread(Fence->Thread);
    }
}



LOUSTATUS _LouKeDmaSignalDmaFenceDelayedWork(PVOID Data){
    _LouKeDmaSignalDmaFence((PLOUSINE_DMA_FENCE)Data);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
void 
LouKeDmaSignalDmaFence(
    PLOUSINE_DMA_FENCE Fence
){
    DELAYED_FUNCTION Work ={
        .DelayedFunction = _LouKeDmaSignalDmaFenceDelayedWork,
        .WorkData = (PVOID)Fence,
    };
    LouKeQueueInterruptWork(Work);
}

KERNEL_EXPORT LOUSTATUS LouKeFenceDmaTransfer(PLOUSINE_DMA_TRANSFER Transfer){
    BOOLEAN Poll = Transfer->DmaFence.Poll;
    SIZE    CurrentTSC;
    SIZE    TscFrequency;
    SIZE    Expiration;
    SIZE    Wait = (SIZE)Transfer->DmaFence.Wait;
    BOOLEAN TransferDone;
    if(Poll){
        MutexUnlock(&Transfer->DmaFence.DmaFence);
        CurrentTSC = read_tsc();
        TscFrequency = GetTscMaster() / 1000;
        Expiration = CurrentTSC + (Wait * TscFrequency);
        while(CurrentTSC <= Expiration){
            CurrentTSC = read_tsc();
            TransferDone = Transfer->DmaDone;
            if(TransferDone){
                return STATUS_SUCCESS;
            }
        }
        return STATUS_TIMEOUT;
    }
    LouKIRQL Irql;
    LouKeRaiseIrql(HIGH_LEVEL, &Irql);
    if(Wait){
        LouKeThreadSleepNoYield((SIZE)Wait);
    }else{
        LouKeBlockThreadNoYield(Transfer->DmaFence.Thread);
    }
    MutexUnlock(&Transfer->DmaFence.DmaFence);
    LouKeLowerIrql(Irql);
    TransferDone = Transfer->DmaDone;
    if(!TransferDone){
        LouKeYieldExecution();
    }
    return TransferDone ? STATUS_SUCCESS : STATUS_TIMEOUT;
}

KERNEL_EXPORT LOUSTATUS LouKeFinishDmaTransferFence(PLOUSINE_DMA_TRANSFER Transfer){
    if(!Transfer){
        return STATUS_INVALID_PARAMETER;
    }
    MutexUnlock(&Transfer->DmaFence.DmaFenceFence);
    return STATUS_SUCCESS;
}



KERNEL_EXPORT PVOID LouKeDmaTransferGetOffsetVa(PLOUSINE_DMA_TRANSFER Transfer, SIZE ByteOffset, SIZE* RemainingInSegment){
    if(!Transfer){
        return 0x00;
    }
    switch(Transfer->Type){
        case LOUSINE_DMA_TRANSFER_TYPE_STANDARD:{
            if(Transfer->StandardTransfer.DmaSize < ByteOffset){
                return 0x00;
            }   
            if(RemainingInSegment){
                *RemainingInSegment = Transfer->StandardTransfer.DmaSize - ByteOffset;
            }
            return (PVOID)((UINT8*)Transfer->StandardTransfer.DmaAddress + ByteOffset);
        }
        case LOUSINE_DMA_TRANSFER_TYPE_SCATTERED:
            break;
        default:
            return 0x00;
    }    
    SIZE SgCount = Transfer->ScatteredTransfer->TransferCount;
    SIZE TmpOffset = 0;
    SIZE CurrentOffset;
    for(SIZE i = 0; i < SgCount; i++){
        if((TmpOffset + Transfer->ScatteredTransfer->Transfers[i].DmaSize) < ByteOffset){
            TmpOffset += Transfer->ScatteredTransfer->Transfers[i].DmaSize;
            continue;
        }
        CurrentOffset = (ByteOffset - TmpOffset);
        if(RemainingInSegment){
            *RemainingInSegment = Transfer->ScatteredTransfer->Transfers[i].DmaSize - CurrentOffset;
        }
        return (PVOID)((UINT8*)Transfer->ScatteredTransfer->Transfers[i].DmaAddress + CurrentOffset);
    }
    return 0x00;
}   