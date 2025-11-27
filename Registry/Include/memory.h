#ifndef _MEMMORY_H
#define _MEMMORY_H

#include <Compiler.h>

typedef struct _POOL_MEMORY_TRACKS{
    ListHeader Peers;
    bool AddressInUse; //used for fixed pools
    uint64_t Address;
    size_t MemorySize; //used if not fixed
}POOL_MEMORY_TRACKS, * PPOOL_MEMORY_TRACKS;

#define string LOU_STRING

typedef struct _LMPOOL_DIRECTORY{
    ListHeader          List;
    bool                FixedSizePool;
    string              Tag;
    uint64_t            LastOut;
    uint64_t            Location;
    uint64_t            VLocation;
    uint64_t            PoolSize;
    uint64_t            ObjectSize;
    uint64_t            Flags;
    uint64_t*           FreeList;
    uint64_t            FreeListTop;       
    POOL_MEMORY_TRACKS  MemoryTracks;
}LMPOOL_DIRECTORY, * PLMPOOL_DIRECTORY, * POOL;

#define LouKeMallocType(x,y) SafeMalloc(sizeof(x))
#define LouKeMalloc(x,y) SafeMalloc(x)
#define LouKeMallocArray(x, y, z) SafeMalloc(sizeof(x) * y)
#define LouKeFree(x) free(x)
#define LouKeMallocEx(x,y,z) SafeMalloc(x)

#define KILOBYTE_PAGE 4096ULL
#define MEGABYTE_PAGE (2 * 1024 * 1024ULL)
#define KILOBYTE (1 * 1024ULL)

#define PRESENT_PAGE           0b1
#define WRITEABLE_PAGE        0b10

#define USER_PAGE           (1 << 2)

#define WRITE_THROUGH_PAGE  0b1000
#define CACHE_DISABLED_PAGE 0b10000
#define UNCACHEABLE_PAGE    0b10000

#define PAGE_PRESENT        (1 << 0)
#define PAGE_WRITE          (1 << 1)
#define PAGE_USER           (1 << 2)
#define PAGE_PWT            (1 << 3)
#define PAGE_PCD            (1 << 4)
#define END_PAGE            (1 << 4)

#define KERNEL_GENERIC_MEMORY   WRITEABLE_PAGE | PRESENT_PAGE
#define KERNEL_DMA_MEMORY       UNCACHEABLE_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
#define USER_GENERIC_MEMORY     USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
#define USER_DMA_MEMORY         USER_PAGE | WRITEABLE_PAGE |PRESENT_PAGE
#define USER_RO_DMA_MEMORY      UNCACHEABLE_PAGE | USER_PAGE | PRESENT_PAGE
#define USER_RO_GENERIC_MEMORY  USER_PAGE | PRESENT_PAGE

#include <stdalign.h>
#define GET_ALIGNMENT(x) (alignof(x))

static inline
bool RangeInterferes(
    uint64_t AddressForCheck, 
    uint64_t SizeOfCheck,
    uint64_t AddressOfBlock, 
    uint64_t SizeOfBlock
) {   
    uint64_t Start = AddressOfBlock;
    uint64_t End = AddressOfBlock + SizeOfBlock;
    if (
        ((AddressForCheck >= Start) && (AddressForCheck < End)) ||
        (((AddressForCheck + SizeOfCheck) >= Start) && ((AddressForCheck + SizeOfCheck) < End)) ||
        ((AddressForCheck <= Start) && ((AddressForCheck + SizeOfCheck) >= End))
    ) {
        return true;
    }
    return false;
}

static inline size_t GetAlignmentBySize(size_t Size){
    if(Size <= 2)    return 2;
    if(Size <= 4)    return 4;
    if(Size <= 8)    return 8;
    if(Size <= 16)   return 16;
    if(Size <= 32)   return 32;
    if(Size <= 64)   return 64;
    if(Size <= 128)  return 128;
    if(Size <= 256)  return 256;
    if(Size <= 512)  return 512;
    if(Size <= 1024) return 1024;
    if(Size <= 2048) return 2048;
    return 4096;
}

POOL LouKeCreateGenericPool(
    uint64_t VLocation,
    uint64_t Location,
    uint64_t size,
    uint64_t Flags
);


void* LouKeGenricAllocateDmaPool(
    POOL Pool,
    size_t size,
    size_t* Offset
);

void* LouKeGenericPoolGetPhyAddress(
    POOL Pool,
    void* Address
);

void* LouKeMallocFromDynamicPoolEx(POOL Pool, size_t AllocationSize, size_t Alignment);


#endif