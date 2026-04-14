#include <LouAPI.h>

typedef struct _KMALLOC_VMEM_TRACK{
    ListHeader  Peers;
    PVOID       Address;
    SIZE        Size;
}KMALLOC_VMEM_TRACK, * PKMALLOC_VMEM_TRACK;

typedef struct _KMALLOC_PAGE_TRACK{
    ListHeader                      Peers;
    PVOID                           PageAddress;
    SIZE                            PageSize;
    UINT64                          Flags;
    ListHeader                      VMemTracks; 
}KMALLOC_PAGE_TRACK, * PKMALLOC_PAGE_TRACK;

typedef PVOID (*PAGE_ALLOCATOR_FUNCTION)(SIZE Size, SIZE Count, UINT64 PageFlags);
typedef PVOID (*PAGE_ALLOCATOR_FUNCTION_EX)(SIZE Size, SIZE Count, UINT64 PageFlags, BOOLEAN CreateDevSection);

#define HIGH_MEMORY_SPACE           0
#define LOW_DMA_SPACE               1
#define LOW_VM_SPACE                2
#define HIGH_VM_SPACE               3
#define TOTAL_MEMORY_SPACES         4

static ListHeader               KernelMemorySpaces[TOTAL_MEMORY_SPACES] = {0};
static mutex_t                  KernelMemorySpacesLocks[TOTAL_MEMORY_SPACES] = {0};
const  PAGE_ALLOCATOR_FUNCTION  KernelMemorySpacesPageAllocators[TOTAL_MEMORY_SPACES] = {LouKeMallocPage, LouKeMallocPagePhy32, (PAGE_ALLOCATOR_FUNCTION)LouKeMallocPageVirt32, (PAGE_ALLOCATOR_FUNCTION)LouKeMallocPageVirt64};

static 
BOOLEAN
LouKeTrackAllocationFits(
    PKMALLOC_PAGE_TRACK PageTrack,
    UINT64              Address,
    UINT64              Size,
    PVOID*              NextHint    
){  
    PKMALLOC_VMEM_TRACK TmpVMemTrack;
    ForEachListEntry(TmpVMemTrack, &PageTrack->VMemTracks, Peers){
        if(RangeInterferes(
            (UINT64)TmpVMemTrack->Address, TmpVMemTrack->Size,
            Address, Size
        )){
            if(NextHint){
                *NextHint = (PVOID)((UINTPTR)Address + (UINTPTR)TmpVMemTrack->Size);
            }
            return false;
        }
    }    
    return true;
}

PVOID 
LouKeMallocFromTrackers(
    SIZE    Size, 
    SIZE    Alignment, 
    UINT64  PageFlags, 
    UINT8   MemorySpace
){
    if(MemorySpace >= TOTAL_MEMORY_SPACES){
        return 0x00;
    }

    mutex_t*                    Lock = &KernelMemorySpacesLocks[MemorySpace];
    ListHeader*                 Track = &KernelMemorySpaces[MemorySpace];
    PVOID                       Result = 0x00;
    PKMALLOC_PAGE_TRACK         TmpPageTrack = 0x00;
    uint64_t                    RoundUpSize = ROUND_UP64(Size, MAX(MEGABYTE_PAGE, ROUND_UP64(Alignment, MEGABYTE_PAGE)));
    PAGE_ALLOCATOR_FUNCTION     PageAllocator = KernelMemorySpacesPageAllocators[MemorySpace];
    PAGE_ALLOCATOR_FUNCTION_EX  PageAllocatorEx = MemorySpace > 1 ? (PAGE_ALLOCATOR_FUNCTION_EX)KernelMemorySpacesPageAllocators[MemorySpace] : 0x00;
    PKMALLOC_VMEM_TRACK         TmpVMemTrack;
    
    MutexLock(Lock);
    ForEachListEntry(TmpPageTrack, Track, Peers){
        ForEachIf((TmpPageTrack->Flags == PageFlags) && (TmpPageTrack->PageSize >= Size)){
            Result = (PVOID)ROUND_UP64((UINT64)TmpPageTrack->PageAddress, Alignment);
            while(((UINTPTR)Result + Size) <= ((UINT64)TmpPageTrack->PageAddress + TmpPageTrack->PageSize)){
                if(LouKeTrackAllocationFits(TmpPageTrack, (UINT64)Result, Size, &Result)){
                    goto _DONE;
                }
                Result = (PVOID)ROUND_UP64((UINT64)Result, Alignment);
            }
        }
    }

    TmpPageTrack = (PKMALLOC_PAGE_TRACK)LouGeneralAllocateMemoryEx(sizeof(KMALLOC_PAGE_TRACK), GET_ALIGNMENT(KMALLOC_PAGE_TRACK));
    Result = PageAllocatorEx ? PageAllocatorEx(MEGABYTE_PAGE, RoundUpSize / MEGABYTE_PAGE, PageFlags, true) : PageAllocator(MEGABYTE_PAGE , RoundUpSize / MEGABYTE_PAGE, PageFlags);
    TmpPageTrack->PageSize = RoundUpSize;
    TmpPageTrack->Flags = PageFlags;
    TmpPageTrack->PageAddress = Result;
    LouKeListAddTail(&TmpPageTrack->Peers, Track);

    _DONE:
    TmpVMemTrack = (PKMALLOC_VMEM_TRACK)LouGeneralAllocateMemoryEx(sizeof(KMALLOC_VMEM_TRACK), GET_ALIGNMENT(KMALLOC_VMEM_TRACK));
    TmpVMemTrack->Address = Result;
    TmpVMemTrack->Size = Size;
    LouKeListAddTail(&TmpVMemTrack->Peers, &TmpPageTrack->VMemTracks);

    MutexUnlock(Lock);
    memset(Result, 0, Size);
    return Result;
}

SIZE
LouKeGetAllocationSizeFromTrackers(
    PVOID Address,
    UINT8 MemorySpace
){
    if(MemorySpace >= TOTAL_MEMORY_SPACES){
        return 0x00;
    }

    mutex_t*                    Lock = &KernelMemorySpacesLocks[MemorySpace];
    ListHeader*                 Track = &KernelMemorySpaces[MemorySpace];
    PKMALLOC_PAGE_TRACK         TmpPageTrack = 0x00;
    PKMALLOC_VMEM_TRACK         TmpVMemTrack;
    SIZE                        Result = 0x00;
    MutexLock(Lock);
    ForEachListEntry(TmpPageTrack, Track, Peers){
        ForEachIf(RangeInterferes((UINT64)Address, 1, (UINT64)TmpPageTrack->PageAddress, TmpPageTrack->PageSize)){
            ForEachListEntry(TmpVMemTrack, &TmpPageTrack->VMemTracks, Peers){
                if(RangeInterferes(
                    (UINT64)TmpVMemTrack->Address, TmpVMemTrack->Size,
                    (UINT64)Address, 1
                )){
                    Result = TmpVMemTrack->Size;
                    goto _DONE;
                }   
            }
        }
    }
    _DONE:
    MutexUnlock(Lock);
    return Result;
}

PVOID 
LouKeReallocFromTrackers(
    PVOID   Address,
    SIZE    Size,   
    SIZE    Alignment,
    UINT64  Flags,
    UINT8   MemorySpace
){

    if(MemorySpace >= TOTAL_MEMORY_SPACES){
        return 0x00;
    }

    mutex_t*                    Lock = &KernelMemorySpacesLocks[MemorySpace];
    ListHeader*                 Track = &KernelMemorySpaces[MemorySpace];
    PVOID                       Result = 0x00;
    PKMALLOC_PAGE_TRACK         TmpPageTrack = 0x00;
    PKMALLOC_VMEM_TRACK         TmpVMemTrack;

    MutexLock(Lock);
    ForEachListEntry(TmpPageTrack, Track, Peers){
        ForEachIf(RangeInterferes((UINT64)Address, 1, (UINT64)TmpPageTrack->PageAddress, TmpPageTrack->PageSize)){
            ForEachListEntry(TmpVMemTrack, &TmpPageTrack->VMemTracks, Peers){
                if(RangeInterferes(
                    (UINT64)TmpVMemTrack->Address, TmpVMemTrack->Size,
                    (UINT64)Address, 1
                )){
                    BOOLEAN Realocate = false;
                    if(!Size){
                        LouKeListDeleteItem(&TmpVMemTrack->Peers);
                        LouGeneralFreeMemory(TmpVMemTrack);
                        if(LouKeListIsEmpty(&TmpPageTrack->VMemTracks)){
                            LouKeListDeleteItem(&TmpPageTrack->Peers);
                            LouGeneralFreeMemory(TmpPageTrack);
                        }
                    }else{
                        if(LouKeTrackAllocationFits(TmpPageTrack, (UINT64)TmpVMemTrack->Address, Size, 0x00) && (TmpPageTrack->Flags == Flags)){
                            TmpVMemTrack->Size = Size;
                            Result = TmpVMemTrack->Address;
                        }else{
                            Realocate = true;                            
                        }
                    }
                    MutexUnlock(Lock);
                    if(Realocate){
                        Result = LouKeMallocFromTrackers(
                            Size,   
                            Alignment,
                            Flags,
                            MemorySpace
                        );
                        memcpy(Result, TmpVMemTrack->Address, TmpVMemTrack->Size);
                        LouKeListDeleteItem(&TmpVMemTrack->Peers);
                        LouGeneralFreeMemory(TmpVMemTrack);
                        if(LouKeListIsEmpty(&TmpPageTrack->VMemTracks)){
                            LouKeListDeleteItem(&TmpPageTrack->Peers);
                            LouGeneralFreeMemory(TmpPageTrack);
                        }
                    }
                    return Result;
                }
            }
        }
    }
    MutexUnlock(Lock);
    LouPrint("LouKeReallocFromTrackers():%h\n", Address);
    while(1);
    return 0x00;
}

void LouKeFreeFromTrackers(
    PVOID   Address,
    UINT8   MemorySpace
){
    LouKeReallocFromTrackers(
        Address,
        0,
        0,
        0,
        MemorySpace
    );
}

KERNEL_EXPORT
void* 
LouKeMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){  
    return LouKeMallocFromTrackers(
        AllocationSize,
        Alignment,
        AllocationFlags,
        HIGH_MEMORY_SPACE
    );
}

KERNEL_EXPORT
void* 
LouKeMallocExVirt32(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){  
    return LouKeMallocFromTrackers(
        AllocationSize,
        Alignment,
        AllocationFlags,
        LOW_VM_SPACE
    );
}

KERNEL_EXPORT
void* LouKeMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocEx(
        AllocationSize,
        GetAlignmentBySize(AllocationSize),
        AllocationFlags
    );
}

KERNEL_EXPORT
void* LouKeMallocVirt32(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocExVirt32(
        AllocationSize,
        GetAlignmentBySize(AllocationSize),
        AllocationFlags
    );
}

KERNEL_EXPORT
void* LouKeMallocExPhy32(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){
    return LouKeMallocFromTrackers(
        AllocationSize,
        Alignment,
        AllocationFlags,
        LOW_DMA_SPACE
    );
}


KERNEL_EXPORT void* LouKeMallocPhy32(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocExPhy32(
        AllocationSize,
        GetAlignmentBySize(AllocationSize),
        AllocationFlags
    );
}

KERNEL_EXPORT
void LouKeFree(void* Address){
    LouKeFreeFromTrackers(
        Address,
        HIGH_MEMORY_SPACE
    );
}

KERNEL_EXPORT
void LouKeFreeVirt32(void* Address){
    LouKeFreeFromTrackers(
        Address,
        LOW_VM_SPACE  
    );
}

KERNEL_EXPORT
void LouKeFreePhy32(void* Address){
    LouKeFreeFromTrackers(
        Address,
        LOW_DMA_SPACE  
    );
}

KERNEL_EXPORT
SIZE LouKeGetAllocationSize(PVOID Address){
    SIZE Result = 0x00;
    for(UINT8 i = 0 ; i < TOTAL_MEMORY_SPACES; i++){
        Result = LouKeGetAllocationSizeFromTrackers(Address, i);
        if(Result){
            return Result;
        }
    }
    return 0x00;
}

KERNEL_EXPORT
void* LouKeReallocEx(
    void*       Address, 
    size_t      Alignment, 
    size_t      NewSize,
    uint64_t    PageFlags
){
    return LouKeReallocFromTrackers(
        Address,
        NewSize,
        Alignment,
        PageFlags,
        HIGH_MEMORY_SPACE
    );
}

KERNEL_EXPORT
void* LouKeRealloc(
    void*       Address, 
    size_t      NewSize,
    uint64_t    PageFlags
){
    return LouKeReallocEx(
        Address,
        GetAlignmentBySize(NewSize),
        NewSize,
        PageFlags
    );
}

KERNEL_EXPORT
void* LouKeReallocExPhy32(
    void* Address, 
    size_t Alignment, 
    size_t NewSize,
    UINT64 PageFlags
){
    return LouKeReallocFromTrackers(
        Address,
        NewSize,
        Alignment,
        PageFlags,
        LOW_DMA_SPACE
    );
}

KERNEL_EXPORT
void* LouKeReallocPhy32(
    void* Address, 
    size_t NewSize,
    UINT64 PageFlags
){
    return LouKeReallocExPhy32(
        Address,
        GetAlignmentBySize(NewSize),
        NewSize,
        PageFlags
    );
}
