#include <Hal.h>

KERNEL_EXPORT 
PDMA_ADAPTER 
LouKeHalGetDmaAdapter(
    PVOID Context, 
    PDEVICE_DESCRIPTION DeviceDescription, 
    PULONG MapRegisterCount
){
    LouPrint("LouKeHalGetDmaAdapter()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeAllocateCommonBufferVector(
    PDMA_ADAPTER                DmaAdapter,
    PHYSICAL_ADDRESS            LowAdderss,
    PHYSICAL_ADDRESS            HighAddress,
    MEMORY_CACHING_TYPE         CachingType,
    NODE_REQUIREMENT            IdealNode,
    ULONG                       Flags,
    ULONG                       ElementCount,
    ULONGLONG                   ElementSize,
    PDMA_COMMON_BUFFER_VECTOR   VectorOut
){
    LouPrint("LouKeAllocateCommonBufferVector()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
PVOID 
LouKeAllocateCommonBuffer(
    PDMA_ADAPTER DmaAdapter, 
    ULONG Length, 
    PPHYSICAL_ADDRESS LogicalAddress, 
    BOOLEAN CacheEnabled
){
    LouPrint("LouKeAllocateCommonBuffer()\n");
    while(1);
    return 0x00;
}

KERNEL_EXPORT 
void 
LouKeGetCommonBufferFromVectorByIndex(
    PDMA_COMMON_BUFFER_VECTOR   Vector,
    ULONG                       Index,
    PVOID*                      VAddress,
    PPHYSICAL_ADDRESS           LogicalAddress  
){
    LouPrint("LouKeGetCommonBufferFromVectorByIndex()\n");
    while(1);
}