#include <drivers/Dma8237A.h>
#define DMA_16_START (2 * MEGABYTE)
#define DMA_16_END   (16 * MEGABYTE)

static POOL Dma16Pool = 0x00;

PVOID LouKeMallocDma16Ex(
    SIZE AllocationSize, 
    UINT64 Alignment
){
    if(!Dma16Pool){
        //64 < is not allowed to be remapped from identiy so assume identity
        Dma16Pool = LouKeMapDynamicPoolEx(
            DMA_16_START, 
            DMA_16_END - DMA_16_START, 
            6, //6 ISA devices Sound, Net, Ide 1, Ide 2, Flopy 1, Flopy 2  
            "DMA-16 Pool",
            0 //no flags
        );
    }
    return LouKeMallocFromDynamicPoolEx(
        Dma16Pool,
        AllocationSize,
        Alignment
    );
}

PVOID LouKeMallocDma16(
    SIZE AllocationSize
){
    return LouKeMallocDma16Ex(
        AllocationSize,
        GetAlignmentBySize(AllocationSize)
    );
}

void LouKeFreeDma16(
    PVOID Address
){
    LouKeFreeFromDynamicPool(Dma16Pool, Address);
}
