
// allocation.c
// Tyler Grenier

//Rat version 2 has been depreciated for rat version 3 in RAT.c 
//at some point all code here should be removed

#include <LouAPI.h>

KERNEL_EXPORT
bool EnforceSystemMemoryMap(
    uint64_t Address, 
    uint64_t size
){
    LouKeRatReserveMemoryRegion((PVOID)Address, size);
    return true;
}

KERNEL_EXPORT void* LouAllocatePhysical32UpEx(size_t BytesToAllocate, uint64_t Alignment) {
   return LouKeRatAllocate32BitPhysicalAddress(BytesToAllocate, Alignment);
}

KERNEL_EXPORT void* LouAllocatePhysical64UpEx(SIZE BytesToAllocate, UINT64 Alignment){
    return LouKeRatAllocate64BitPhysicalAddress(BytesToAllocate, Alignment);
}

void* LouAllocatePhysical64Up(
    SIZE Size
){
    return LouAllocatePhysical64UpEx(Size, GetAlignmentBySize(Size));
}

void* LouAllocatePhysical32Up(
    SIZE Size 
){
    return LouAllocatePhysical32UpEx(Size, GetAlignmentBySize(Size));
}

void* 
LouGeneralAllocateMemoryEx(
    UINT64 Size,
    UINT64 Alignment
){
    void* Result = LouKeRatAllocate64BitPhysicalAddress(Size, Alignment);
    if(!Result){
        return 0x00;
    }
    Result += KSpaceBase;
    memset(Result, 0, Size);
    return Result;
}

void* 
LouGeneralAllocateMemoryEx32(
    UINT64 Size,
    UINT64 Alignment
){
    void* Result = LouKeRatAllocate32BitPhysicalAddress(Size, Alignment);
    if(!Result){
        return 0x00;
    }
    Result += KSpaceBase;
    memset(Result, 0, Size);
    return Result;
}


void* LouGeneralAllocateMemory(UINT64 Size){
    return LouGeneralAllocateMemoryEx(Size, GetAlignmentBySize(Size));
}

void* LouGeneralAllocateMemory32(UINT64 Size){
    return LouGeneralAllocateMemoryEx32(Size, GetAlignmentBySize(Size));
}

void LouGeneralFreeMemory(void* Address){
    if(!Address){
        LouPrint("LouGeneralFreeMemory():Address NULL\n");
        while(1);
    }
    UINT64 Tmp = (UINT64)Address;
    Tmp -= KSpaceBase;
    LouKeRatFreeAddress((UINTPTR)Tmp);
}

KERNEL_EXPORT void LouFree(PVOID Addr) {
    LouKeRatFreeAddress((UINTPTR)Addr);
}

KERNEL_EXPORT
void* LouVMallocEx(size_t BytesToAllocate, uint64_t Alignment){
    return (PVOID)LouKeRatAllocateVirtualAddress(BytesToAllocate, Alignment);
}


KERNEL_EXPORT
void* LouVMalloc(size_t BytesToAllocate){
    return LouVMallocEx(BytesToAllocate, GetAlignmentBySize(BytesToAllocate));
}

bool CheckAndReserveVAddress(
    UINTPTR     VAddress,
    SIZE        size
){
    SIZE TotalSize = ROUND_UP64(size, KILOBYTE_PAGE);
    if(!LouKeRatIsAddressFree((PVOID)VAddress, TotalSize)){
        return false;
    }
    LouKeRatReserveMemoryRegion((PVOID)VAddress, TotalSize);
    return true;
}