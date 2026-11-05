#include "Xhci.h"

static LOUSINE_DMA_DEVICE Xhci32BitBusMasterTransferDevice = {
    .DmaDeviceFlags = LOUSINE_DMA_DEVICE_FLAGS_SCATTER_DMA_SUPPORTED,
    .MaxScatterCount = 8320,
    .AllocatorData = {
        .DmaLimit = 32,
        .DmaThreshold = 64 * KILOBYTE,
    },
};

static LOUSINE_DMA_DEVICE Xhci32BitBusMasterPageSizeDevice = {
    .DmaDeviceFlags = LOUSINE_DMA_DEVICE_FLAGS_SCATTER_DMA_SUPPORTED,
    .MaxScatterCount = 8320,
    .AllocatorData = {
        .DmaLimit = 32,
        .DmaThreshold = 0x00,
    },
};

static LOUSINE_DMA_DEVICE Xhci64BitBusMasterTransferDevice = {
    .DmaDeviceFlags = LOUSINE_DMA_DEVICE_FLAGS_SCATTER_DMA_SUPPORTED,
    .MaxScatterCount = 8320,
    .AllocatorData = {
        .DmaLimit = 64,
        .DmaThreshold = 64 * KILOBYTE,
    },
};

static LOUSINE_DMA_DEVICE Xhci64BitBusMasterPageSizeDevice = {
    .DmaDeviceFlags = LOUSINE_DMA_DEVICE_FLAGS_SCATTER_DMA_SUPPORTED,
    .MaxScatterCount = 8320,
    .AllocatorData = {
        .DmaLimit = 64,
        .DmaThreshold = 0x00,
    },
};



LOUSTATUS XhciInitializeMemoryManagement(
    PXHCI_DEVICE            Device
){
    if(!Device){
        return STATUS_INVALID_PARAMETER;
    }
    if(Device->Capabilities.Dma64Supported){
        memcpy(&Device->PageSizeDmaDevice, &Xhci64BitBusMasterPageSizeDevice, sizeof(LOUSINE_DMA_DEVICE));
        memcpy(&Device->TransferDmaDevice, &Xhci64BitBusMasterTransferDevice, sizeof(LOUSINE_DMA_DEVICE));
        Device->UnrestrictedDmaAllocatorFunctions.UnrestrictedDmaAllocatorAlloc = LouKeMallocEx;
        Device->UnrestrictedDmaAllocatorFunctions.UnrestrictedDmaAllocatorFree = LouKeFree;
    }else{
        memcpy(&Device->PageSizeDmaDevice, &Xhci32BitBusMasterPageSizeDevice, sizeof(LOUSINE_DMA_DEVICE));
        memcpy(&Device->TransferDmaDevice, &Xhci32BitBusMasterTransferDevice, sizeof(LOUSINE_DMA_DEVICE));
        Device->UnrestrictedDmaAllocatorFunctions.UnrestrictedDmaAllocatorAlloc = LouKeMallocExPhy32;
        Device->UnrestrictedDmaAllocatorFunctions.UnrestrictedDmaAllocatorFree = LouKeFreePhy32;
    }
    Device->PageSizeDmaDevice.AllocatorData.DmaThreshold = Device->Capabilities.PageSize;
    if(!Device->PageSizeDmaDevice.AllocatorData.DmaThreshold){
        LouPrint("XHCI.SYS:Unable To Get Page Size - Check Register Pointer\n");
        return STATUS_IO_DEVICE_ERROR;
    }
    return STATUS_SUCCESS;
}

static LOUSTATUS AllocateDmaMemoryFromDevice(
    PLOUSINE_DMA_DEVICE DmaDevice,
    SIZE                AllocationSize,
    SIZE                Alignment,
    PVOID*              Out
){  
    if(
        (!DmaDevice) || (!AllocationSize) ||
        (!Alignment) || (!Out)
    ){
        return STATUS_INVALID_PARAMETER;
    }
    PVOID Tmp = LouKeDmaDeviceAllocateDmaMemory(DmaDevice, AllocationSize, Alignment);
    if(!Tmp){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *Out = Tmp;
    return STATUS_SUCCESS;
}

static LOUSTATUS FreeDmaMemoryFromDevice(
    PLOUSINE_DMA_DEVICE DmaDevice,
    PVOID               Address
){
    if((!DmaDevice) || (!Address)){
        return STATUS_INVALID_PARAMETER;
    }
    LouKeDmaDeviceFreeDmaMemory(DmaDevice, Address);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciAllocateUnrestrictedDmaMemory(
    PXHCI_DEVICE    XhciDevice,
    SIZE            AllocationSize,
    SIZE            Alignment,
    PVOID*          Out
){
    if(
        (!XhciDevice) || (!AllocationSize) || 
        (!Alignment) || (!Out) 
    ){
        return STATUS_INVALID_PARAMETER;
    }
    PVOID Tmp = XhciDevice->UnrestrictedDmaAllocatorFunctions.UnrestrictedDmaAllocatorAlloc(AllocationSize, Alignment, KERNEL_DMA_MEMORY);
    if(!Tmp){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *Out = Tmp;
    return STATUS_SUCCESS;
}

LOUSTATUS XhciFreeUnrestrictedDmaMemory(
    PXHCI_DEVICE    XhciDevice,
    PVOID           Address
){
    if((!XhciDevice) || (!Address)){
        return STATUS_INVALID_PARAMETER;
    }
    XhciDevice->UnrestrictedDmaAllocatorFunctions.UnrestrictedDmaAllocatorFree(Address);
    return STATUS_SUCCESS;
}

LOUSTATUS XhciAllocateTransferDmaMemory(
    PXHCI_DEVICE    XhciDevice,
    SIZE            AllocationSize,
    SIZE            AllocationAlignment,
    PVOID*          Out
){
    if(!XhciDevice){
        return STATUS_INVALID_PARAMETER;
    }
    return AllocateDmaMemoryFromDevice(
        &XhciDevice->TransferDmaDevice,
        AllocationSize,
        AllocationAlignment,
        Out
    );
}

LOUSTATUS XhciFreeTransferDmaMemory(
    PXHCI_DEVICE    XhciDevice,
    PVOID           Address
){
    if(!XhciDevice){
        return STATUS_INVALID_PARAMETER;
    }
    return FreeDmaMemoryFromDevice(
        &XhciDevice->TransferDmaDevice,
        Address
    );
}
LOUSTATUS XhciAllocatePageSizeDmaMemory(
    PXHCI_DEVICE    XhciDevice,
    SIZE            AllocationSize,
    SIZE            AllocationAlignment,
    PVOID*          Out
){
    if(!XhciDevice){
        return STATUS_INVALID_PARAMETER;
    }
    return AllocateDmaMemoryFromDevice(
        &XhciDevice->PageSizeDmaDevice,
        AllocationSize,
        AllocationAlignment,
        Out
    );
}

LOUSTATUS XhciFreePageSizeDmaMemory(
    PXHCI_DEVICE    XhciDevice,
    PVOID           Address
){
    if(!XhciDevice){
        return STATUS_INVALID_PARAMETER;
    }
    return FreeDmaMemoryFromDevice(
        &XhciDevice->PageSizeDmaDevice,
        Address
    );
}

UINT64 XhciGetDmaAddress(
    PVOID Address
){
    UINT64 Result;
    RequestPhysicalAddress((UINT64)Address, &Result);
    return Result;
}


