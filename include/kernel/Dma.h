#ifndef _LOU_DMA_API
#define _LOU_DMA_API

#ifdef __cplusplus
extern "C" {
#endif



KERNEL_EXPORT PVOID LouKeDmaAllocateGenericDmaMemory(UINT64 DataSize, UINT64 Alignment, UINT64 Threshold);
KERNEL_EXPORT PVOID LouKeDmaAllocateGenericDmaMemory32(UINT64 DataSize, UINT64 Alignment, UINT64 Threshold);

#ifdef __cplusplus
}
#endif
#endif