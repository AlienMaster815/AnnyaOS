#include <Hal.h>

KERNEL_EXPORT 
PDMA_ADAPTER 
LouKeHalGetDmaAdapter(
    PVOID               Context, 
    PDEVICE_DESCRIPTION DeviceDescription, 
    PULONG              MapRegisterCount
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
    PDMA_ADAPTER        DmaAdapter, 
    ULONG               Length, 
    PPHYSICAL_ADDRESS   LogicalAddress, 
    BOOLEAN             CacheEnabled
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

KERNEL_EXPORT 
void 
LouKeFreeCommonBufferFromVector(
    PDMA_ADAPTER                DmaAdapter,
    PDMA_COMMON_BUFFER_VECTOR   Vector,
    ULONG                       Index
){
    LouPrint("LouKeFreeCommonBufferFromVector()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeFreeCommonBufferVector(
    PDMA_ADAPTER                DmaAdapter, 
    PDMA_COMMON_BUFFER_VECTOR   Vector
){
    LouPrint("LouKeFreeCommonBufferVector()\n");
    while(1);
}

KERNEL_EXPORT 
void 
LouKeFreeCommonBuffer(
    PDMA_ADAPTER        DmaAdapter, 
    ULONG               Length, 
    PHYSICAL_ADDRESS    LogicalAddress, 
    PVOID               VirtualAddress, 
    BOOLEAN             CacheEnabled
){
    LouPrint("LouKeFreeCommonBuffer()\n");
    while(1);
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeFlushAdapterBuffersEx(
    PDMA_ADAPTER    DmaAdapter, 
    PMDL            Mdl, 
    PVOID           Offset, 
    ULONG           Length, 
    BOOLEAN         WriteToDevice
){
    LouPrint("LouKeFlushAdapterBuffersEx()\n");
    while(1);   
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
BOOLEAN 
LouKeFlushAdapterBuffers(
    PDMA_ADAPTER    DmaAdapter, 
    PMDL            Mdl, 
    PVOID           MapRegisterBase, 
    PVOID           CurrentVa, 
    ULONG           Length,
    BOOLEAN         WriteToDevice
){
    LouPrint("LouKeFlushAdapterBuffers()\n");
    while(1);
    return true;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeAllocateAdapterChannelEx(
    struct _DMA_ADAPTER*    DmaAdapter,
    PDEVICE_OBJECT          DeviceObject,
    PVOID                   DmaTransferContext,
    ULONG                   MapRegisterCount,
    ULONG                   Flags,
    PDRIVER_CONTROL         DriverControl,
    PVOID                   Contex,
    PVOID                   MapRegisterBase
){
    LouPrint("LouKeAllocateAdapterChannelEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIommuPasidDeviceCreate(
    PIOMMU_DMA_DEVICE       DmaDevice, 
    PIOMMU_DMA_PASID_DEVICE PasidDeviceOut, 
    PULONG                  AsidOut
){
    LouPrint("LouKeIommuPasidDeviceCreate()\n");
    while(1);
    return STATUS_SUCCESS;
}


KERNEL_EXPORT 
LOUSTATUS 
LouKeIommuPasidDeviceDelete(
    PIOMMU_DMA_PASID_DEVICE PasidDeviceOut
){
    LouPrint("LouKeIommuPasidDeviceDelete()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIommuDomainAttatchPasidDevice(
    PIOMMU_DMA_DOMAIN       Domain, 
    PIOMMU_DMA_PASID_DEVICE PasidDevice
){
    LouPrint("LouKeIommuDomainAttatchPasidDevice()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIommuDomainDetatchPasidDevice(
    PIOMMU_DMA_PASID_DEVICE PasidDevice
){
    LouPrint("LouKeIommuDomainDetatchPasidDevice()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeIommuDeviceQueryInformation(
    PIOMMU_DMA_DEVICE               DmaDevice, 
    ULONG                           Size, 
    PULONG                          BytesWriten, 
    PIOMMU_DMA_DEVICE_INFORMATION   Buffer
){
    LouPrint("LouKeIommuDeviceQueryInformation()\n");
    while(1);
    return STATUS_SUCCESS;
}
