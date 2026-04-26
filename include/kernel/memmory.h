#ifndef _MEMMORY_H
#define _MEMMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>
#include <cstdlib.h>
#include <bootloader/grub/multiboot.h>
#include <stdalign.h>
#include <kernel/threads.h>
#include <string.h>
#include <kernel/loustatus.h>
#include <Modulation.h>

KERNEL_EXPORT 
void
LouKeVmmFreeVmBuffer(
    PVOID Address
);

KERNEL_EXPORT 
PVOID 
LouKeAllocateVmmBuffer64Ex2(
    UINT32  ProcessID,
    SIZE    Size,
    SIZE    Alignment,
    BOOLEAN Zero,
    BOOLEAN Shared,
    UINT64  Flags
);

KERNEL_EXPORT 
PVOID 
LouKeAllocateVmmBuffer32Ex2(
    UINT32  ProcessID,
    SIZE    Size,
    SIZE    Alignment,
    BOOLEAN Zero,
    BOOLEAN Shared,
    UINT64  Flags
);



#define POOL_FLAG_NORMAL            0
#define POOL_FLAG_NO_WRAP_ARROUND   (1 << 0)
#define POOL_FLAG_NO_MEMSET         (1 << 1)

#define POOL_FLAG_LAZY_POOL         (POOL_FLAG_NO_WRAP_ARROUND | POOL_FLAG_NO_MEMSET)

#define HighQuad(v) ((__int128)v >> 64)
#define LowQuad(v) ((__int128)v & 0xFFFFFFFFFFFFFFFF)

#define GetStackVariable(offset) (*(uintptr_t*)((uintptr_t)__builtin_frame_address(0) - (offset)))
#define SetStackVariable(offset, value) (*(uintptr_t*)((uintptr_t)__builtin_frame_address(0) - (offset)) = (uintptr_t)(value))

#define GET_ALIGNMENT(x) (alignof(x))
#define FORCE_ALIGNMENT(alignment) __attribute__((aligned(alignment)))

#define STRIP_OPTIMIZATIONS __attribute__((optimize(0))) 
#define SET_OPTIMIZATION(x) __attribute__((optimize(x)))


#ifndef __always_inline
#define __always_inline __attribute__((__always_inline__)) inline
#endif

#ifndef __cleanup
#define __cleanup(_func) __attribute__((__cleanup__(_func)))
#endif

#define DEFINE_FREE(_name, _type, _free) \
    static __always_inline void __free_##_name(void *p) { \
        _type _T = *(_type *)p; \
        _free; \
    }

#define __free(_name) __cleanup(__free_##_name)

#define KILOBYTE        (1      * 1024ULL)
#define MEGABYTE        (1024   * KILOBYTE)
#define GIGABYTE        (1024   * MEGABYTE)

#define KILOBYTE_PAGE   (4 * KILOBYTE)
#define MEGABYTE_PAGE   (2 * MEGABYTE)

#define PRESENT_PAGE            (1ULL << 0)
#define WRITEABLE_PAGE          (1ULL << 1)
#define USER_PAGE               (1ULL << 2)
#define WRITE_THROUGH_PAGE      (1ULL << 3)
#define UNCACHEABLE_PAGE        (1ULL << 4)

#define PAT_PAGE                (1ULL << 7)

#define NOEXEC_PAGE             (1ULL << 63)

#define KERNEL_GENERIC_MEMORY   WRITEABLE_PAGE | PRESENT_PAGE
#define KERNEL_DMA_MEMORY       UNCACHEABLE_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
#define USER_GENERIC_MEMORY     USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
#define USER_DMA_MEMORY         USER_PAGE | WRITEABLE_PAGE |PRESENT_PAGE
#define USER_RO_DMA_MEMORY      UNCACHEABLE_PAGE | USER_PAGE | PRESENT_PAGE
#define USER_RO_GENERIC_MEMORY  USER_PAGE | PRESENT_PAGE

#define PAGE_TABLE_ALLIGNMENT   KILOBYTE_PAGE
#define PAGE_SIZE               KILOBYTE_PAGE

#define PAGE_FLAGSSPACE 0x1FF

#define KERNEL_WRITEABLE_PAGE_PRESENT 0b10000011
#define KERNEL_WRITEABLE_PAGE_UNCAHEABLE_PRESENT 0b10010011

//power of 2 pages
#define NR_PAGE_ORDERS      11
#define NR_MAX_PAGE_ORDERS  10

typedef uint64_t pde_t; // Page Directory Entry
typedef uint64_t pte_t; // Page Table Entry

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
    mutex_t             PoolLock;
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


static inline bool RangeInterferes(uint64_t AddrA, uint64_t SizeA, uint64_t AddrB, uint64_t SizeB){
    return (AddrA < (AddrB + SizeB)) && (AddrB < (AddrA + SizeA));
}


static inline
bool RangeDoesNotInterfere(
    uint64_t AddressForCheck, 
    uint64_t SizeOfCheck,
    uint64_t AddressOfBlock, 
    uint64_t SizeOfBlock
) {   
    return (RangeInterferes(AddressForCheck, SizeOfCheck, AddressOfBlock, SizeOfBlock) == false);
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


#ifndef _USER_MODE_CODE_
#define LouKeMallocArray(type, count, tag) (type*)LouKeMallocEx(sizeof(type) * (count) , GET_ALIGNMENT(type), (tag))
#define LouKeMallocType(Type, Tag) (Type*)LouKeMallocEx(sizeof(Type), GET_ALIGNMENT(Type), Tag)

void LouKeFreePhysical(void* AddressToFree);
void LouFree(PVOID Addr);
void* LouAllocatePhysical32UpEx(size_t BytesToAllocate, size_t Aligned);
void* LouAllocatePhysical64UpEx(size_t BytesToAllocate, uint64_t Alignment);
uint64_t GetStackBackset(uint64_t Offset);

void Write16BitValueToAddress(uint64_t Address, uint16_t Value);
uint16_t Get16BitValueFromAddress(uint64_t Address);
void Write8BitValueToAddress(uint64_t Address, uint8_t Value);
uint8_t Get8BitValueFromAddress(uint64_t Address);
void Write32BitValueFromAddress(uint64_t Address, uint32_t Value);
uint32_t Get32BitValueFromAddress(uint64_t Address);
void Write64BitValueToAddress(uint64_t Address, uint64_t Value);
uint64_t Get64BitValueFromAddress(uint64_t Address);

KERNEL_EXPORT
void LouKeFreePage(void* PageAddress);

void LouKeFreePage32(void* PageAddress);
bool LouMapAddress(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize);
bool LouMapAddress32(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize);
bool LouMapAddressEx(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize, UINT64* Pml4);
bool LouMapAddressEx32(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize, UINT64* Pml4);
void LouUnMapAddress(uint64_t VAddress, uint64_t* PAddress, uint64_t* UnmapedLength, uint64_t* PageFlags);
uint64_t GetPageOfFaultValue(uint64_t VAddress);
extern uint64_t GetPageValue(uint64_t PAddress, uint64_t FLAGS);

KERNEL_EXPORT
uint64_t LouKeGetRamSize();

void* LouGeneralAllocateMemoryEx(UINT64 Size,UINT64 Alignment);
void* LouGeneralAllocateMemoryEx32(UINT64 Size,UINT64 Alignment);
void* LouGeneralAllocateMemory(UINT64 Size);
void* LouGeneralAllocateMemory32(UINT64 Size);
void  LouGeneralFreeMemory(void* Address);
bool LouCreateMemoryPool(uint64_t* MemoryAddressVirtual,uint64_t* RequestedMemoryAddressPhysical,uint64_t PoolSizeNeeded,uint64_t AlignmentNeeded, uint64_t PageAttributes);
void LouFreeAlignedMemory(uint8_t* alignedAddr, size_t size);

KERNEL_EXPORT
bool EnforceSystemMemoryMap(
    uint64_t Address, 
    uint64_t size
);

KERNEL_EXPORT void* LouKeMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
);
KERNEL_EXPORT void* LouKeMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);

KERNEL_EXPORT void LouKeFree(void* AddressToFree);

KERNEL_EXPORT void* LouKeMallocPhy32(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
);
void* LouKeMallocExPhy32(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);

void MapIoMemory(
    uint64_t Address,
    uint64_t MapSize
);

KERNEL_EXPORT
LOUSTATUS LouKeCreateDeviceSection(
    void*   PBase,
    void*   VBase,
    size_t    Size,
    uint64_t  PageFlags
);

ULONG LouPageFlagsToNtPageFlags(UINT64 PageFlags, BOOL PageFault, BOOL NxExists);
UINT64 NtPageFlagsToLouPageFlags(ULONG PageFlags, BOOL PageFault, BOOL NxExists);

KERNEL_EXPORT void* memset(void* dest, int value, size_t count);

void MapIoMemory(
    uint64_t Address,
    uint64_t MapSize
);


void LouKeMapDeviceMemoryBlock(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS
);

KERNEL_EXPORT
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

void LouKeMapContinuousMemoryBlockEx(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS,
    UINT64*  Pml4
);

void LouKeMapContinuousMemoryBlockKB(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS
);

void LouKeMapContinuousMemoryBlock32(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS
);

void LouKeMapContinuousMemoryBlockEx32(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS,
    UINT64*  Pml4
);

void LouKeMapContinuousMemoryBlockKB32(
    uint64_t PAddress, 
    uint64_t VAddress,
    uint64_t size, 
    uint64_t FLAGS
);


void LouKeUnMapContinuousMemoryBlock(
    uint64_t VAddress,
    uint64_t size
);

KERNEL_EXPORT void* LouKeMallocPage(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags);

typedef void (*KERNEL_REMAP_EMPTY_CALLBACK)(PVOID);

LOUSTATUS
LouKeVmmCreatePageReserveVm(
    PVOID   PageAddress, 
    SIZE    PageSize,  
    SIZE    PageCount,
    BOOLEAN SetPhysUser,
    BOOLEAN SetVirtUser
);

LOUSTATUS
LouKeVmmCreatePageReserveVm64(
    PVOID   PageAddress, 
    SIZE    PageSize,  
    SIZE    PageCount,
    BOOLEAN SetPhysUser,
    BOOLEAN SetVirtUser
);

LOUSTATUS
LouKeVmmCreatePageReserveVm32(
    PVOID   PageAddress, 
    SIZE    PageSize,  
    SIZE    PageCount,
    BOOLEAN SetPhysUser,
    BOOLEAN SetVirtUser
);

LOUSTATUS
LouKeVmmGetVPageReserveVm(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
);

LOUSTATUS
LouKeVmmGetPPageReserveVm(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
);

LOUSTATUS
LouKeVmmGetVPageReserveVm64(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
);

LOUSTATUS 
LouKeVmmGetPPageReserveVm64(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
);

LOUSTATUS
LouKeVmmGetVPageReserveVm32(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
);

LOUSTATUS 
LouKeVmmGetPPageReserveVm32(
    SIZE    PageSize,
    SIZE    PageCount,
    PVOID*  Out
);

LOUSTATUS 
LouKeVmmPutVPageReserveAddressVm(
    PVOID                       PAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
);


LOUSTATUS 
LouKeVmmPutPPageReserveAddressVm(
    PVOID                       PAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
);


LOUSTATUS 
LouKeVmmPutVPageReserveAddressVm64(
    PVOID                       PAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
);

LOUSTATUS 
LouKeVmmPutPPageReserveAddressVm64(
    PVOID                       PAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
);

LOUSTATUS 
LouKeVmmPutVPageReserveAddressVm32(
    PVOID                       VAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
);

LOUSTATUS 
LouKeVmmPutPPageReserveAddressVm32(
    PVOID                       PAddress,
    KERNEL_REMAP_EMPTY_CALLBACK Callback
);

void* LouKeMallocPageEx(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres);
void* LouKeMallocPageExVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres, BOOLEAN CreateDevSection);
void* LouKeMallocPageVirt32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection);
void* LouKeMallocPageExVirt64(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres, BOOLEAN CreateDevSection);
void* LouKeMallocPageVirt64(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, BOOLEAN CreateDevSection);
void* LouKeMallocPageExPhy32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags, uint64_t PhysicalAddres);
KERNEL_EXPORT void* LouKeMallocPagePhy32(uint64_t PageSize, uint64_t PageCount, uint64_t PageFlags);
uint64_t LouKeVMemmoryGetSize(uint64_t VAddress);
void* LouKeMallocExVirt32(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
);
void* LouKeMallocVirt32(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
);
size_t LouKeGetAllocationSize(PVOID Addrress);

KERNEL_EXPORT LOUSTATUS RequestPhysicalAddressEx(
    uint64_t  VAddress,
    uint64_t* PAddress,
    uint64_t  Pml4Base 
);

KERNEL_EXPORT LOUSTATUS RequestPhysicalAddress(
    uint64_t VAddress,
    uint64_t* PAddress
);

LOUSTATUS 
LouKeMemSetVmSpace(
    UINT32 ProcessID, 
    PVOID Addres, 
    int v, 
    SIZE Count
);

PLMPOOL_DIRECTORY LouKeMapPool(
    uint64_t LocationOfPool,
    uint64_t LocationOf,
    uint64_t PoolSize,
    uint64_t ObjectSize,
    string Tag,
    uint64_t Flags
);

void LouKeDestroyFixedPool(PLMPOOL_DIRECTORY Pool);

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

void* LouKeGenericAllocateFixedDmaPool(
    POOL Pool,
    size_t* Offset
);

void LouKeFreeFromFixedPool(
    PLMPOOL_DIRECTORY Pool, 
    void* Object
);

void* LouKeRealloc(void* Address, size_t NewSide, uint64_t PageFlags);

void LouKeFreeFromPool(PLMPOOL_DIRECTORY Pool, void* Address, uint64_t size);

void LouKeDestroyDynamicPool(
    POOL Pool
);


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

void LouKeFreePhy32(void*);

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

#endif
#ifdef __cplusplus
}
#endif
#endif