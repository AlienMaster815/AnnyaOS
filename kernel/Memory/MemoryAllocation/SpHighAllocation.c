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

static ListHeader               SpKernelMemorySpaces[TOTAL_MEMORY_SPACES] = {0};
static mutex_t                  SpKernelMemorySpacesLocks[TOTAL_MEMORY_SPACES] = {0};
const  PAGE_ALLOCATOR_FUNCTION  SpKernelMemorySpacesPageAllocators[TOTAL_MEMORY_SPACES] = {LouKeMallocPage, LouKeMallocPagePhy32, (PAGE_ALLOCATOR_FUNCTION)LouKeMallocPageVirt32, (PAGE_ALLOCATOR_FUNCTION)LouKeMallocPageVirt64};

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
LouKeSpMallocFromTrackers(
    SIZE    Size, 
    SIZE    Alignment, 
    UINT64  PageFlags, 
    UINT8   MemorySpace
){
    if(MemorySpace >= TOTAL_MEMORY_SPACES){
        return 0x00;
    }

    mutex_t*                    Lock = &SpKernelMemorySpacesLocks[MemorySpace];
    ListHeader*                 Track = &SpKernelMemorySpaces[MemorySpace];
    PVOID                       Result = 0x00;
    PKMALLOC_PAGE_TRACK         TmpPageTrack = 0x00;
    uint64_t                    RoundUpSize = ROUND_UP64(Size, KILOBYTE_PAGE);
    PAGE_ALLOCATOR_FUNCTION     PageAllocator = SpKernelMemorySpacesPageAllocators[MemorySpace];
    PAGE_ALLOCATOR_FUNCTION_EX  PageAllocatorEx = MemorySpace > 1 ? (PAGE_ALLOCATOR_FUNCTION_EX)SpKernelMemorySpacesPageAllocators[MemorySpace] : 0x00;
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

    Result = PageAllocatorEx ? PageAllocatorEx(KILOBYTE_PAGE, RoundUpSize / KILOBYTE_PAGE, PageFlags, true) : PageAllocator(KILOBYTE_PAGE , RoundUpSize / KILOBYTE_PAGE, PageFlags);

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
LouKeSpGetAllocationSizeFromTrackers(
    PVOID Address,
    UINT8 MemorySpace
){
    if(MemorySpace >= TOTAL_MEMORY_SPACES){
        return 0x00;
    }

    mutex_t*                    Lock = &SpKernelMemorySpacesLocks[MemorySpace];
    ListHeader*                 Track = &SpKernelMemorySpaces[MemorySpace];
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
LouKeSpReallocFromTrackers(
    PVOID   Address,
    SIZE    Size,   
    SIZE    Alignment,
    UINT64  Flags,
    UINT8   MemorySpace
){

    if(MemorySpace >= TOTAL_MEMORY_SPACES){
        return 0x00;
    }

    mutex_t*                    Lock = &SpKernelMemorySpacesLocks[MemorySpace];
    ListHeader*                 Track = &SpKernelMemorySpaces[MemorySpace];
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
                            LouKeFreePage(TmpPageTrack->PageAddress);
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
                        Result = LouKeSpMallocFromTrackers(
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
                            LouKeFreePage(TmpPageTrack->PageAddress);
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

void LouKeSpFreeFromTrackers(
    PVOID   Address,
    UINT8   MemorySpace
){
    LouKeSpReallocFromTrackers(
        Address,
        0,
        0,
        0,
        MemorySpace
    );
}

KERNEL_EXPORT
void* 
LouKeSpMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){  
    return LouKeSpMallocFromTrackers(
        AllocationSize,
        Alignment,
        AllocationFlags,
        HIGH_MEMORY_SPACE
    );
}

KERNEL_EXPORT
void* 
LouKeSpMallocExVirt32(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){  
    return LouKeSpMallocFromTrackers(
        AllocationSize,
        Alignment,
        AllocationFlags,
        LOW_VM_SPACE
    );
}

KERNEL_EXPORT
void* LouKeSpMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeSpMallocEx(
        AllocationSize,
        GetAlignmentBySize(AllocationSize),
        AllocationFlags
    );
}

KERNEL_EXPORT
void* LouKeSpMallocVirt32(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeSpMallocExVirt32(
        AllocationSize,
        GetAlignmentBySize(AllocationSize),
        AllocationFlags
    );
}

KERNEL_EXPORT
void* LouKeSpMallocExPhy32(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){
    return LouKeSpMallocFromTrackers(
        AllocationSize,
        Alignment,
        AllocationFlags,
        LOW_DMA_SPACE
    );
}


KERNEL_EXPORT void* LouKeSpMallocPhy32(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeSpMallocExPhy32(
        AllocationSize,
        GetAlignmentBySize(AllocationSize),
        AllocationFlags
    );
}

KERNEL_EXPORT
void LouKeSpFree(void* Address){
    LouKeSpFreeFromTrackers(
        Address,
        HIGH_MEMORY_SPACE
    );
}

KERNEL_EXPORT
void LouKeSpFreeVirt32(void* Address){
    LouKeSpFreeFromTrackers(
        Address,
        LOW_VM_SPACE  
    );
}

KERNEL_EXPORT
void LouKeSpFreePhy32(void* Address){
    LouKeSpFreeFromTrackers(
        Address,
        LOW_DMA_SPACE  
    );
}

KERNEL_EXPORT
SIZE LouKeSpGetAllocationSize(PVOID Address){
    SIZE Result = 0x00;
    for(UINT8 i = 0 ; i < TOTAL_MEMORY_SPACES; i++){
        Result = LouKeSpGetAllocationSizeFromTrackers(Address, i);
        if(Result){
            return Result;
        }
    }
    return 0x00;
}

KERNEL_EXPORT
void* LouKeSpReallocEx(
    void*       Address, 
    size_t      Alignment, 
    size_t      NewSize,
    uint64_t    PageFlags
){
    return LouKeSpReallocFromTrackers(
        Address,
        NewSize,
        Alignment,
        PageFlags,
        HIGH_MEMORY_SPACE
    );
}

KERNEL_EXPORT
void* LouKeSpRealloc(
    void*       Address, 
    size_t      NewSize,
    uint64_t    PageFlags
){
    return LouKeSpReallocEx(
        Address,
        GetAlignmentBySize(NewSize),
        NewSize,
        PageFlags
    );
}

KERNEL_EXPORT
void* LouKeSpReallocExPhy32(
    void* Address, 
    size_t Alignment, 
    size_t NewSize,
    UINT64 PageFlags
){
    return LouKeSpReallocFromTrackers(
        Address,
        NewSize,
        Alignment,
        PageFlags,
        LOW_DMA_SPACE
    );
}

KERNEL_EXPORT
void* LouKeSpReallocPhy32(
    void* Address, 
    size_t NewSize,
    UINT64 PageFlags
){
    return LouKeSpReallocExPhy32(
        Address,
        GetAlignmentBySize(NewSize),
        NewSize,
        PageFlags
    );
}
