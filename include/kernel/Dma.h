#ifndef _LOU_DMA_API
#define _LOU_DMA_API

#define LOUSINE_DMA_DEVICE_FLAGS_USING_PRIVATE_DMA_ALLOCATOR    (1 << 0)
#define LOUSINE_DMA_DEVICE_FLAGS_SCATTER_DMA_SUPPORTED          (1 << 1)

struct _LOUSINE_DMA_DEVICE;

typedef struct _LOUSINE_SCATTER_DMA_TRANSFER{
    SIZE        TransferCount;
    struct{
        UINTPTR DmaAddress;
        SIZE    DmaSize;
    }           Transfers[];
}LOUSINE_SCATTER_DMA_TRANSFER, * PLOUSINE_SCATTER_DMA_TRANSFER;

typedef enum{
    LOUSINE_DMA_TRANSFER_TYPE_STANDARD = 0,
    LOUSINE_DMA_TRANSFER_TYPE_SCATTERED,
}LOUSINE_DMA_TRANSFER_TYPE;

typedef struct _LOUSINE_DMA_FENCE{
    atomic_t            Wait;
    ATOMIC_BOOLEAN      Poll;    
    KERNEL_EVENT_OBJECT DoneEvent;
}LOUSINE_DMA_FENCE, * PLOUSINE_DMA_FENCE;

typedef struct _LOUSINE_DMA_TRANSFER{
    struct _LOUSINE_DMA_DEVICE*         DmaDevice;
    ATOMIC_BOOLEAN                      DmaDone;
    PVOID                               PrivateData;
    LOUSINE_DMA_FENCE                   DmaFence;
    LOUSINE_DMA_TRANSFER_TYPE           Type;
    union{
        struct{
            UINTPTR                     DmaAddress; 
            SIZE                        DmaSize;
        }                               StandardTransfer;
        PLOUSINE_SCATTER_DMA_TRANSFER   ScatteredTransfer;
    };
}LOUSINE_DMA_TRANSFER, * PLOUSINE_DMA_TRANSFER;

typedef struct _LOUSINE_DMA_DEVICE{
    ULONG           DmaDeviceFlags;
    SIZE            MaxScatterCount;
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


KERNEL_EXPORT void LouKeDmaSignalDmaFence(PLOUSINE_DMA_FENCE Fence);
KERNEL_EXPORT LOUSTATUS LouKeFenceDmaTransfer(PLOUSINE_DMA_TRANSFER Transfer);
KERNEL_EXPORT LOUSTATUS LouKeSetupDmaTransferFence(PLOUSINE_DMA_TRANSFER Transfer, int Wait, bool Poll);
KERNEL_EXPORT void LouKeDestroyDmaTransfer(PLOUSINE_DMA_TRANSFER Transfer);
KERNEL_EXPORT PLOUSINE_DMA_TRANSFER LouKeCreateDmaTransfer(PLOUSINE_DMA_DEVICE DmaDevice, SIZE AllocationSize, SIZE LowestAlignment);

#ifdef __cplusplus
}
#endif
#endif