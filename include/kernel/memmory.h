#ifndef _MEMMORY_H
#define _MEMMORY_H

#define LouKeMallocArray(type, count, tag) \
    (type*)LouKeMallocEx((ROUND_UP64(sizeof(type), GET_ALIGNMENT(type))) * (count) , GET_ALIGNMENT(type), (tag))
#define LouKeMallocType(Type, Tag) (Type*)LouKeMallocEx(sizeof(Type), GET_ALIGNMENT(Type), Tag)


// Tyler Grenier 9/21/23 9:38 PM
// added Section 1:1 RAM ADDRESS

#include <stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <bootloader/grub/multiboot.h>
#include <SharedTypes.h>
#include <stdalign.h>

#define GET_ALIGNMENT(x) (alignof(x))
#define FORCE_ALIGNMENT(alignment) __attribute__((aligned(alignment)))

#define STRIP_OPTIMIZATIONS __attribute__((optimize(0))) 
#define SET_OPTIMIZATION(x) __attribute__((optimize(x)))

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

typedef __int128 int128_t;

#pragma GCC diagnostic pop

#define KILOBYTE_PAGE 4096ULL
#define MEGABYTE_PAGE (2 * 1024 * 1024ULL)
#define KILOBYTE (1 * 1024ULL)

#define PRESENT_PAGE           0b1
#define WRITEABLE_PAGE        0b10

#define USER_PAGE           (1 << 2)

#define WRITE_THROUGH_PAGE  0b1000
#define CACHE_DISABLED_PAGE 0b10000
#define UNCACHEABLE_PAGE    0b10000

#define PAGE_PAT         (1ULL << 7)  // PAT bit
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
 

#ifndef __cplusplus
// Section 1:1 RAM ADDRESS
#define MAXMEM 0xFFFFFFFFFFFFFFFFULL
#define RAMADD unsigned char*
#define RAMADDDATA unsigned char *
#define BLOCK 4096
#define SIZE unsigned long long

// Constants for gigabyte and megabyte sizes
#define GIGABYTE (1ULL << 30)  // 1 GB in bytes
#define MEGABYTE (1ULL << 20)  // 1 MB in bytes
#define KILOBYTE (1 * 1024ULL)

#define PAGE_TABLE_ALLIGNMENT 4096
#define PAGE_SIZE 4096

#define FLAGSSPACE 0x1FF

#include <LouAPI.h>

#ifndef _KERNEL_MODULE_
extern void Write16BitValueToAddress(uint64_t Address, uint16_t Value);
extern uint16_t Get16BitValueFromAddress(uint64_t Address);
extern void Write8BitValueToAddress(uint64_t Address, uint8_t Value);
extern uint8_t Get8BitValueFromAddress(uint64_t Address);
extern void Write32BitValueFromAddress(uint64_t Address, uint32_t Value);
extern uint32_t Get32BitValueFromAddress(uint64_t Address);
extern void Write64BitValueToAddress(uint64_t Address, uint64_t Value);
extern uint64_t Get64BitValueFromAddress(uint64_t Address);


void LouKeFreePhysical(void* AddressToFree);


void LouFree(RAMADD Addr);
void* LouMalloc(size_t BytesToAllocate);
void* LouMallocEx(size_t BytesToAllocate, size_t Aligned);
uint64_t GetStackBackset(uint64_t Offset);
#endif


#include <stdint.h>

#define MachineMemoryBase 0 


//Paging Stub
#ifndef _KERNEL_MODULE_
typedef struct  __attribute__((packed, aligned(4096))) _PageTable {
    uint64_t entries[512];
} PageTable;

typedef struct __attribute__((packed, aligned(4096))) _PML {
    PageTable PML4;
    PageTable PML3;
    PageTable PML2;
    PageTable PML1;
}PML;
#endif

#ifndef _KERNEL_MODULE_
void LouKeFreePage(void* PageAddress);
void LouKeFreePage32(void* PageAddress);
bool LouMapAddress(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize);
void LouUnMapAddress(uint64_t VAddress, uint64_t* PAddress, uint64_t* UnmapedLength, uint64_t* PageFlags);
uint64_t GetPageOfFaultValue(uint64_t VAddress);
extern uint64_t GetPageValue(uint64_t PAddress, uint64_t FLAGS);
uint64_t GetRamSize();

bool LouCreateMemoryPool(uint64_t* MemoryAddressVirtual,uint64_t* RequestedMemoryAddressPhysical,uint64_t PoolSizeNeeded,uint64_t AlignmentNeeded, uint64_t PageAttributes);
void LouFreeAlignedMemory(uint8_t* alignedAddr, size_t size);
void* LouMallocAlligned(size_t size, uint64_t allignment);
bool EnforceSystemMemoryMap(
    uint64_t Address, 
    uint64_t size
);
void* LouKeMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
);
void* LouKeMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);

void LouKeFree(void* AddressToFree);

void* LouKeMallocPhysical(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
);
void* Ex(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);

void MapIoMemory(
    uint64_t Address,
    uint64_t MapSize
);
#endif
//Directory Entry FLAGS

//2mb Entry
#define KERNEL_PAGE_WRITE_PRESENT 0b10000011
#define KERNEL_PAGE_WRITE_UNCAHEABLE_PRESENT 0b10010011


typedef uint64_t pde_t; // Page Directory Entry
typedef uint64_t pte_t; // Page Table Entry

//endof Paging Stubs

#ifndef _KERNEL_MODULE_
void* memset(void* dest, int value, size_t count);

void* align_memory(void* ptr, size_t alignment);
#endif

// Initialize a page table
#else
#include <LouDDK.h>

#ifndef _KERNEL_MODULE_
KERNEL_IMPORT void MapIoMemory(
    uint64_t Address,
    uint64_t MapSize
);
#endif

#define GIGABYTE 0x40000000ULL
#define MEGABYTE 0x100000ULL
#define KILOBYTE (1 * 1024ULL)

#define KERNEL_PAGE_WRITE_PRESENT 0b10000011
#define KERNEL_PAGE_WRITE_UNCAHEABLE_PRESENT 0b10010011


#ifndef _KERNEL_MODULE_
KERNEL_IMPORT bool LouMapAddress(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize);
KERNEL_IMPORT void remove_padding(const void* struct_ptr, size_t struct_size, uint8_t* buffer);
KERNEL_IMPORT void LouFree(uint8_t* Addr);
KERNEL_IMPORT void* LouMalloc(size_t BytesToAllocate);
KERNEL_IMPORT LOUSTATUS LouKeMapIO(uint64_t PADDRESS, uint64_t MemoryBuffer, uint64_t FLAGS);
KERNEL_IMPORT bool LouMapAddressEx(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize);
KERNEL_IMPORT void* LouMallocEx(size_t BytesToAllocate, size_t Aligned);
KERNEL_IMPORT void* memset(void* dest, int value, size_t count);
KERNEL_IMPORT void* LouMallocAlligned(size_t size, uint64_t allignment);
KERNEL_IMPORT bool LouCreateMemoryPool(uint64_t* MemoryAddressVirtual,uint64_t* RequestedMemoryAddressPhysical, uint64_t PoolSizeNeeded,uint64_t AlignmentNeeded, uint64_t PageAttributes);
KERNEL_IMPORT void LouFreeAlignedMemory(uint8_t* alignedAddr, size_t size);
KERNEL_IMPORT bool LouUnMapAddress(uint64_t VAddress, uint64_t PageSize);
KERNEL_IMPORT bool EnforceSystemMemoryMap(
    uint64_t Address, 
    uint64_t size
);
KERNEL_IMPORT void* LouKeMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
);
KERNEL_IMPORT void* LouKeMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);
KERNEL_IMPORT void LouKeFree(void* AddressToFree);
KERNEL_IMPORT void LouUserFree(uint64_t DataP);
KERNEL_IMPORT void LouKeUserFree(void* AddressToFree);
KERNEL_IMPORT void LouKeFreePhysical(void* AddressToFree);
KERNEL_IMPORT void* LouKeMallocPhysical(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
);
KERNEL_IMPORT void* LouKeMallocPhysicalEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);
#else 
KERNEL_EXPORT void* LouMalloc(size_t BytesToAllocate);
KERNEL_EXPORT void* LouMallocEx(size_t BytesToAllocate, size_t Aligned);
KERNEL_EXPORT void* memset(void* dest, int value, size_t count);

#endif
#endif

#ifdef __cplusplus
KERNEL_IMPORT{
#endif

#define LouClamp_t(type, val, min, max) ({           \
    type __val = (val);                              \
    type __min = (min);                              \
    type __max = (max);                              \
    __val < __min ? __min : __val > __max ? __max : __val; \
})

typedef struct _POOL_MEMORY_TRACKS{
    ListHeader Peers;
    bool AddressInUse; //used for fixed pools
    uint64_t Address;
    size_t MemorySize; //used if not fixed
}POOL_MEMORY_TRACKS, * PPOOL_MEMORY_TRACKS;

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

typedef struct _BO{
    ListHeader Header;
    size_t size;
    uintptr_t CpuDmaAddress;
    uintptr_t VRamTranslatedAddress;
    uint64_t Flags;
    int ReferenceCount;
    bool BufferIsInVRam;
}BO, *PBO;

#ifndef _KERNEL_MODULE_

void LouKeMapDeviceMemoryBlock(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS
);

POOL LouKeCreateGenericPool(
    uint64_t VLocation,
    uint64_t Location,
    uint64_t Size,
    uint64_t Flags
);

void* MallocVariacHeap(size_t InitialSize);
void FreeVariacHeap(
void* VariacPointerToFree, 
size_t HeapSize
);
void* IncreaseVariacHeap(
    void* LocationOfCurrentHeap,
    size_t SizeOfNewHeap,
    size_t SizeOfCurrentHeap
);
void* TrimVariacHeap(
    void* LocationOfCurrentHeap,
    void* TRIMStartLocation,
    size_t SizeToTrim,
    size_t SizeOfCurrentHeap
);

uint64_t GetKernelLoadedAddress();
void SetKernelLoadedAddress(uint64_t Address);

void LouKeMallocVMmIO(
    uint64_t PAddress,
    uint64_t size,
    uint64_t FLAGS
);

uint64_t LouKeVMemmorySearchPhysicalSpace(
    uint64_t VAddress
);

uint64_t LouKeVMemmorySearchVirtualSpace(
    uint64_t PAddress
);

uint64_t SearchForMappedAddressSize(uint64_t Address);
void* LouKeAllocateUncachedVMemory(uint64_t NumberOfBytes);
void* LouKeAllocateUncachedVMemoryEx(
    uint64_t NumberOfBytes,
    uint64_t Alignment
);

void* LouVMallocEx(size_t BytesToAllocate, uint64_t Alignment);
void* LouVMalloc(size_t BytesToAllocate);

void LouKeMapContinuousMemoryBlock(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS
);

void LouKeUnMapContinuousMemoryBlock(
    uint64_t VAddress,
    uint64_t size
);


void* LouKeMallocPage(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags);
void* LouKeMallocPageEx(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres);
void* LouKeMallocPageEx32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres);
void* LouKeMallocPage32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags);

uint64_t LouKeVMemmoryGetSize(uint64_t VAddress);

LOUSTATUS RequestPhysicalAddress(
    uint64_t VAddress,
    uint64_t* PAddress
);

PLMPOOL_DIRECTORY LouKeMapPool(
    uint64_t LocationOfPool,
    uint64_t LocationOf,
    uint64_t PoolSize,
    uint64_t ObjectSize,
    string Tag,
    uint64_t Flags
);

PLMPOOL_DIRECTORY LouKeCreateFixedPool(
    uint64_t NumberOfPoolMembers,
    uint64_t ObjectSize,
    uint64_t Alignment,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
);

PLMPOOL_DIRECTORY LouKeCreateDynamicPoolEx(
    size_t PoolSize,
    size_t CachedTracks,
    size_t PagedTypeAlignement,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
);

PLMPOOL_DIRECTORY LouKeMapDynamicDevicePool();

PLMPOOL_DIRECTORY LouKeMapDynamicPool(
    uint64_t    LocationOfPool,
    size_t      PoolSize,
    string      Tag,
    uint64_t    Flags
);

void* LouKeMallocFromDynamicPoolEx(
    POOL Pool, 
    size_t AllocationSize, 
    size_t Alignment
);

void* LouKeMallocFromDynamicPool(
    POOL Pool, 
    size_t AllocationSize
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

void LouKeFreeFromDynamicPool(
    POOL Pool, 
    void* Address
);

PLMPOOL_DIRECTORY LouKeCreateDynamicPool(
    size_t PoolSize,
    size_t PagedTypeAlignement,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
);

void LouKeFreePool(PLMPOOL_DIRECTORY PoolToFree);

void* LouKeMallocFromPool(
    PLMPOOL_DIRECTORY Pool, 
    uint64_t size, 
    uint64_t* Offset
);

void* LouKeMallocFromFixedPool(
    PLMPOOL_DIRECTORY Pool
);

void LouKeFreeFromPool(PLMPOOL_DIRECTORY Pool, void* Address, uint64_t size);

static inline
bool RangeDoesNotInterfere(
    uint64_t AddressForCheck, 
    uint64_t SizeOfCheck,
    uint64_t AddressOfBlock, 
    uint64_t SizeOfBlock
) {   
    uint64_t Start = AddressOfBlock;
    uint64_t End = AddressOfBlock + SizeOfBlock;

    if (
        ((AddressForCheck >= Start) && (AddressForCheck < End)) ||
        (((AddressForCheck + SizeOfCheck) > Start) && ((AddressForCheck + SizeOfCheck) <= End)) ||
        ((AddressForCheck <= Start) && ((AddressForCheck + SizeOfCheck) >= End))
    ) {
        return false;
    }
    return true;
}

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
        (((AddressForCheck + SizeOfCheck) > Start) && ((AddressForCheck + SizeOfCheck) <= End)) ||
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

uint64_t* LouKeVirtualAddresToPageValue(
    uint64_t VAddress
);

uint64_t LouKeGetOffsetInPage(
    uint64_t VAddress
);

uint64_t LouKePageToPhysicalAddres(uint64_t* Page);

typedef struct _LOU_PFN_TABLE_ENTRY{
    ListHeader  Chain;
    uint64_t    VirtualAddress;
    uint64_t    PhysicalAddres;
    bool        LargePage;
    bool        PresentPage;
    uint64_t    Flags;
    uint64_t    PageAddress;
}LOU_PFN_TABLE_ENTRY, * PLOU_PFN_TABLE_ENTRY;

PLOU_PFN_TABLE_ENTRY LouKePageToPFN(
    uint64_t PAddress
);

void* LouKeMemReMap(void* Location, size_t Size, uint64_t Flags);
void  LouKeMemReleaseReMap(void* Address);
uint64_t GetIoMemEnd();

uint64_t GetAllocationBlockBase(uint64_t Address);

#endif
#ifdef __cplusplus
}
#endif

//typedef __uint128_t uint128_t;




#endif
#ifdef _KERNEL_MODULE_

KERNEL_EXPORT void LouFree(uint8_t* Addr);

KERNEL_EXPORT void LouKeMallocVMmIO(
    uint64_t PAddress,
    uint64_t size,
    uint64_t FLAGS
);

KERNEL_EXPORT uint64_t LouKeVMemmorySearchPhysicalSpace(
    uint64_t VAddress
);

KERNEL_EXPORT uint64_t LouKeVMemmorySearchVirtualSpace(
    uint64_t PAddress
);

KERNEL_EXPORT uint64_t SearchForMappedAddressSize(uint64_t Address);
KERNEL_EXPORT void* LouKeAllocateUncachedVMemory(uint64_t NumberOfBytes);
KERNEL_EXPORT void* LouKeAllocateUncachedVMemoryEx(
    uint64_t NumberOfBytes,
    uint64_t Alignment
);

KERNEL_EXPORT void* LouVMallocEx(size_t BytesToAllocate, uint64_t Alignment);
KERNEL_EXPORT void* LouVMalloc(size_t BytesToAllocate);

KERNEL_EXPORT void LouKeMapContinuousMemoryBlock(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS
);

KERNEL_EXPORT void LouKeUnMapContinuousMemoryBlock(
    uint64_t VAddress,
    uint64_t size
);

KERNEL_EXPORT uint64_t LouKeVMemmoryGetSize(uint64_t VAddress);

KERNEL_EXPORT LOUSTATUS RequestPhysicalAddress(
    uint64_t VAddress,
    uint64_t* PAddress
);

KERNEL_EXPORT PLMPOOL_DIRECTORY LouKeMapPool(
    uint64_t LocationOfPool,
    uint64_t PoolSize,
    uint64_t ObjectSize,
    string Tag,
    uint64_t Flags
);

KERNEL_EXPORT void LouKeFreePool(PLMPOOL_DIRECTORY PoolToFree);

KERNEL_EXPORT void* LouKeMallocFromPool(
    PLMPOOL_DIRECTORY Pool, 
    uint64_t size, 
    uint64_t* Offset
);

KERNEL_EXPORT void* LouKeMallocFromFixedPool(
    PLMPOOL_DIRECTORY Pool
);

KERNEL_EXPORT void LouKeFreeFromPool(PLMPOOL_DIRECTORY Pool, void* Address, uint64_t size);

KERNEL_EXPORT POOL LouKeCreateFixedPool(
    uint64_t NumberOfPoolMembers,
    uint64_t ObjectSize,
    uint64_t Alignment,
    string Tag,
    uint64_t Flags,     //flags for alignment
    uint64_t PageFlags  //flags for Page Directory
);

KERNEL_EXPORT
void* LouKeMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
);

KERNEL_EXPORT
void* LouKeMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);

KERNEL_EXPORT 
PLMPOOL_DIRECTORY LouKeMapDynamicPool(
    uint64_t    LocationOfPool,
    size_t      PoolSize,
    string      Tag,
    uint64_t    Flags
);

KERNEL_EXPORT
void* LouKeMallocFromDynamicPoolEx(
    POOL Pool, 
    size_t AllocationSize, 
    size_t Alignment
);

KERNEL_EXPORT
void* LouKeMallocFromDynamicPool(
    POOL Pool, 
    size_t AllocationSize
);

KERNEL_EXPORT
void LouKeFreeFromDynamicPool(
    POOL Pool, 
    void* Address
);

KERNEL_EXPORT
POOL LouKeCreateGenericPool(
    uint64_t VLocation,
    uint64_t Location,
    uint64_t Size,
    uint64_t Flags
);

KERNEL_EXPORT
void* LouKeGenricAllocateDmaPool(
    POOL Pool,
    size_t size,
    size_t* Offset
);

KERNEL_EXPORT
void* LouKeGenericPoolGetPhyAddress(
    POOL Pool,
    void* Address
);

KERNEL_EXPORT void LouKeFree(void* AddressToFree);

#endif