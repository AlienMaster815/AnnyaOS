#include <LouAPI.h>



KERNEL_EXPORT 
PVOID 
LouKeDmaDeviceAllocateDmaMemory(
    PLOUSINE_DMA_DEVICE DmaDevice,
    SIZE                Size,
    SIZE                Alignment
){
    if(DmaDevice->DmaDeviceFlags & LOUSINE_DMA_DEVICE_FLAGS_USING_PRIVATE_DMA_ALLOCATOR){
        return DmaDevice->AllocatorFunctions.ExternalAllocator(DmaDevice, Size, Alignment);
    }
    return LouKeDmaAllocateGenericDmaMemory(
        Size,
        Alignment,
        DmaDevice->AllocatorData.DmaLimit,
        DmaDevice->AllocatorData.DmaThreshold
    );
}

KERNEL_EXPORT 
void 
LouKeDmaDeviceFreeDmaMemory(
    PLOUSINE_DMA_DEVICE DmaDevice,
    PVOID               Data
){
    if(DmaDevice->DmaDeviceFlags & LOUSINE_DMA_DEVICE_FLAGS_USING_PRIVATE_DMA_ALLOCATOR){
        DmaDevice->AllocatorFunctions.ExternalDeAllocator(DmaDevice, Data);
    }
    LouKeDmaFreeGenericDmaMemory(
        Data,
        DmaDevice->AllocatorData.DmaLimit,
        DmaDevice->AllocatorData.DmaThreshold
    );
}