#include <LouAPI.h>

//TODO LouKeCreateDmaTransfer

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
    LouKeSetAtomicBoolean(&NewTransfer->DmaDone, 0);
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

void LouKeDestroyDmaTransfer(PLOUSINE_DMA_TRANSFER Transfer){
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
