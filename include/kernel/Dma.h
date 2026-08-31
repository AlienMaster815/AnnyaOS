#ifndef _LOU_DMA_API
#define _LOU_DMA_API

#define LOUSINE_DMA_DEVICE_FLAGS_USING_PRIVATE_DMA_ALLOCATOR    (1 << 0)

struct _LOUSINE_DMA_DEVICE;

typedef struct _LOUSINE_DMA_TRANSFER{
    struct _LOUSINE_DMA_DEVICE* DmaDevice;
    ATOMIC_BOOLEAN              DmaDone;
    PVOID                       PrivateData;
    UINTPTR                     DmaAddress; 
    SIZE                        DmaSize;
}LOUSINE_DMA_TRANSFER, * PLOUSINE_DMA_TRANSFER;

typedef struct _LOUSINE_DMA_DEVICE{
    ULONG           DmaDeviceFlags;
    PVOID           PrivateData;
    union{
        struct{
            ULONG   DmaLimit; 
            ULONG   DmaThreshold;
        }           AllocatorData;
        struct{
            PVOID (*ExternalAllocator)(struct _LOUSINE_DMA_DEVICE* DmaDevice, SIZE Size, SIZE Alignment);
            PVOID (*ExternalDeAllocator)(struct _LOUSINE_DMA_DEVICE* DmaDevice, PVOID Data);
        }           AllocatorFunctions;
    };
}LOUSINE_DMA_DEVICE, * PLOUSINE_DMA_DEVICE;

#ifdef __cplusplus
extern "C" {
#endif

KERNEL_EXPORT PVOID LouKeDmaAllocateGenericDmaMemory(SIZE Size, SIZE Alignment, ULONG Limit, ULONG Threshold);
KERNEL_EXPORT void LouKeDmaFreeGenericDmaMemory(PVOID Data, ULONG Limit, ULONG Threshold);

KERNEL_EXPORT PVOID LouKeDmaDeviceAllocateDmaMemory(PLOUSINE_DMA_DEVICE DmaDevice, SIZE Size, SIZE Alignment);
KERNEL_EXPORT void LouKeDmaDeviceFreeDmaMemory(PLOUSINE_DMA_DEVICE DmaDevice, PVOID Data);

#ifdef __cplusplus
}
#endif
#endif