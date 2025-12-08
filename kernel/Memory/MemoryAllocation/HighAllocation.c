#include <LouAPI.h>

extern uint64_t X86_64DivisionBug(uint64_t , uint64_t );
extern uint64_t X86_64MemoryReferenceBug64Read(uint64_t, uint64_t);
extern uint64_t X86_64MemoryReferenceBug64Write(uint64_t, uint64_t , uint64_t);

//typedef struct _KMALLOC_VMEM_TRACK{
//    uint64_t    Next;
//    uint64_t    Address;
//    uint64_t    size;
//}KMALLOC_VMEM_TRACK, * PKMALLOC_VMEM_TRACK;

#define KMALLOC_VMEM_TRACK_SIZE 24

//typedef struct _KMALLOC_PAGE_TRACK{
//    uint64_t                        Next;
//    uint64_t                        Flags;
//    uint64_t                        PageAddress;
//    uint64_t                        PageSize;
//    uint64_t                        TrackCount;
//    PKMALLOC_VMEM_TRACK             VMemTracks; 
//}KMALLOC_PAGE_TRACK, * PKMALLOC_PAGE_TRACK;

#define KMALLOC_PAGE_TRACK_SIZE 48

static uint64_t   KeMallocPageTracks = 0;
static uint64_t   KeMallocPageTracksPhy = 0;
static uint64_t   KaMallocPageTracks32 = 0;
static mutex_t    GenMallocLock = {0};
static mutex_t    GenMallocLock32 = {0};
static mutex_t    GenMallocPhyLock = {0};

//static KMALLOC_PAGE_TRACK   TB3 = {0};
//static size_t               KeMallocPageTracksPhyCount = 0;

#define VMEM_TRACK_DEREFERENCE_READ_NEXT(x) (X86_64MemoryReferenceBug64Read((x), 0))
#define VMEM_TRACK_DEREFERENCE_WRITE_NEXT(x, y) (X86_64MemoryReferenceBug64Write((x), 0, (y)))
#define VMEM_TRACK_DEREFERENCE_READ_ADDRESS(x) (X86_64MemoryReferenceBug64Read((x), 1))
#define VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(x, y) (X86_64MemoryReferenceBug64Write((x), 1, (y)))
#define VMEM_TRACK_DEREFERENCE_READ_SIZE(x) (X86_64MemoryReferenceBug64Read((x), 2))
#define VMEM_TRACK_DEREFERENCE_WRITE_SIZE(x, y) (X86_64MemoryReferenceBug64Write((x), 2, (y)))

#define PAGE_TRACK_DEREFERENCE_READ_NEXT(x) (X86_64MemoryReferenceBug64Read((x), 0))
#define PAGE_TRACK_DEREFERENCE_WRITE_NEXT(x, y) (X86_64MemoryReferenceBug64Write((x), 0, (y)))
#define PAGE_TRACK_DEREFERENCE_READ_FLAGS(x) (X86_64MemoryReferenceBug64Read((x),1))
#define PAGE_TRACK_DEREFERENCE_WRITE_FLAGS(x, y)(X86_64MemoryReferenceBug64Write((x),1, (y)))
#define PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(x) (X86_64MemoryReferenceBug64Read((x), 2))
#define PAGE_TRACK_DEREFERENCE_WRITE_PAGE_ADDRESS(x, y) (X86_64MemoryReferenceBug64Write((x), 2, (y)))
#define PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(x) (X86_64MemoryReferenceBug64Read((x), 3))
#define PAGE_TRACK_DEREFERENCE_WRITE_PAGE_SIZE(x, y) (X86_64MemoryReferenceBug64Write((x), 3, (y)))
#define PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(x) (X86_64MemoryReferenceBug64Read((x), 4))
#define PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(x, y) (X86_64MemoryReferenceBug64Write((x), 4, (y)))
#define PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(x) (X86_64MemoryReferenceBug64Read((x), 5))
#define PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(x, y) (X86_64MemoryReferenceBug64Write((x), 5, (y)))

static inline void ZeroMem(uint64_t Address, uint64_t Size){
    for(size_t i = 0 ; i < Size; i++){
        ((uint8_t*)Address)[i] = 0;
    }
}

void* 
LouKeMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){  
    MutexLock(&GenMallocLock);


    uint64_t RoundUpSize = ROUND_UP64(AllocationSize, MEGABYTE_PAGE);
    if(!KeMallocPageTracks){
        KeMallocPageTracks = (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_PAGE_TRACK_SIZE , 8);
    }
    uint64_t TmpPageTrackBase = KeMallocPageTracks;
    uint64_t TmpVMemTrackBase = 0x00;
    uint64_t Base = 0x00;
    uint64_t Limit = 0x00;
    uint64_t TrackCount = 0;
    bool FoundAddress;
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(PAGE_TRACK_DEREFERENCE_READ_FLAGS(TmpPageTrackBase) == AllocationFlags){
            Base = PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase);
            Limit = Base + PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase);
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            while((Base + AllocationSize) <= Limit){
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                FoundAddress = true;
                while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                    if(RangeInterferes(
                        Base, 
                        AllocationSize,
                        VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase),
                        VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase)
                    )){
                        FoundAddress = false;
                        break;
                    }
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                }

                if(FoundAddress){
                    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8));
                    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, Base);
                    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
                    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount + 1);
                    MutexUnlock(&GenMallocLock);
                    ZeroMem(Base, AllocationSize);
                    return (void*)Base;
                }
                Base += ROUND_UP64(VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase), Alignment);
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }

    PAGE_TRACK_DEREFERENCE_WRITE_NEXT(TmpPageTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_PAGE_TRACK_SIZE, 8));
    PAGE_TRACK_DEREFERENCE_WRITE_FLAGS(TmpPageTrackBase, AllocationFlags);
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_ADDRESS(TmpPageTrackBase, (uint64_t)LouKeMallocPage(MEGABYTE_PAGE, RoundUpSize / MEGABYTE_PAGE, AllocationFlags));
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_SIZE(TmpPageTrackBase, RoundUpSize);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, 1);
    TmpVMemTrackBase = (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, TmpVMemTrackBase);
    
    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8));
    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase));
    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
    MutexUnlock(&GenMallocLock);
    ZeroMem(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase), AllocationSize);

    return (void*)VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase);
}

void* 
LouKeMallocExVirt32(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){  
    MutexLock(&GenMallocLock32);
    uint64_t RoundUpSize = ROUND_UP64(AllocationSize, MEGABYTE_PAGE);
    if(!KaMallocPageTracks32){
        KaMallocPageTracks32 = (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_PAGE_TRACK_SIZE , 8);
    }
    uint64_t TmpPageTrackBase = KaMallocPageTracks32;
    uint64_t TmpVMemTrackBase = 0x00;
    uint64_t Base = 0x00;
    uint64_t Limit = 0x00;
    uint64_t TrackCount = 0;
    bool FoundAddress;
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(PAGE_TRACK_DEREFERENCE_READ_FLAGS(TmpPageTrackBase) == AllocationFlags){
            Base = PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase);
            Limit = Base + PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase);
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            while((Base + AllocationSize) <= Limit){
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                FoundAddress = true;
                while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                    if(RangeInterferes(
                        Base, 
                        AllocationSize,
                        VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase),
                        VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase)
                    )){
                        FoundAddress = false;
                        break;
                    }
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                }

                if(FoundAddress){
                    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8));
                    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, Base);
                    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
                    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount + 1);
                    MutexUnlock(&GenMallocLock32);
                    ZeroMem(Base, AllocationSize);
                    return (void*)Base;
                }
                Base += ROUND_UP64(VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase), Alignment);
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }

    PAGE_TRACK_DEREFERENCE_WRITE_NEXT(TmpPageTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_PAGE_TRACK_SIZE, 8));
    PAGE_TRACK_DEREFERENCE_WRITE_FLAGS(TmpPageTrackBase, AllocationFlags);
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_ADDRESS(TmpPageTrackBase, (uint64_t)LouKeMallocPageVirt32(MEGABYTE_PAGE, RoundUpSize / MEGABYTE_PAGE, AllocationFlags));
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_SIZE(TmpPageTrackBase, RoundUpSize);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, 1);
    TmpVMemTrackBase = (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, TmpVMemTrackBase);
    
    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8));
    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase));
    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
    MutexUnlock(&GenMallocLock32);
    ZeroMem(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase), AllocationSize);
    return (void*)VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase);
}

void* LouKeMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocEx(AllocationSize, GetAlignmentBySize(AllocationSize), AllocationFlags);
}

void* LouKeMallocVirt32(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocExVirt32(AllocationSize, GetAlignmentBySize(AllocationSize), AllocationFlags);
}

void* LouKeMallocExPhy32(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){
    MutexLock(&GenMallocPhyLock);
    uint64_t RoundUpSize = ROUND_UP64(AllocationSize, MEGABYTE_PAGE);
    if(!KeMallocPageTracksPhy){
        KeMallocPageTracksPhy = (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_PAGE_TRACK_SIZE , 8);
    }
    uint64_t TmpPageTrackBase = KeMallocPageTracksPhy;
    uint64_t TmpVMemTrackBase = 0x00;
    uint64_t Base = 0x00;
    uint64_t Limit = 0x00;
    uint64_t TrackCount = 0;
    bool FoundAddress;
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(PAGE_TRACK_DEREFERENCE_READ_FLAGS(TmpPageTrackBase) == AllocationFlags){
            Base = PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase);
            Limit = Base + PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase);
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            while((Base + AllocationSize) <= Limit){
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                FoundAddress = true;
                while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                    if(RangeInterferes(
                        Base, 
                        AllocationSize,
                        VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase),
                        VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase)
                    )){
                        FoundAddress = false;
                        break;
                    }
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                }

                if(FoundAddress){
                    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8));
                    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, Base);
                    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
                    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount + 1);
                    MutexUnlock(&GenMallocPhyLock);
                    ZeroMem(Base, AllocationSize);
                    return (void*)Base;
                }
                Base += Alignment;
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }

    PAGE_TRACK_DEREFERENCE_WRITE_NEXT(TmpPageTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_PAGE_TRACK_SIZE, 8));
    PAGE_TRACK_DEREFERENCE_WRITE_FLAGS(TmpPageTrackBase, AllocationFlags);
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_ADDRESS(TmpPageTrackBase, (uint64_t)LouKeMallocPagePhy32(MEGABYTE_PAGE, RoundUpSize / MEGABYTE_PAGE, AllocationFlags));
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_SIZE(TmpPageTrackBase, RoundUpSize);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, 1);
    TmpVMemTrackBase = (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, TmpVMemTrackBase);
    
    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouGeneralAllocateMemoryEx(KMALLOC_VMEM_TRACK_SIZE, 8));
    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase));
    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
    MutexUnlock(&GenMallocPhyLock);
    ZeroMem(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase), AllocationSize);
    return (void*)VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase);
}


void* LouKeMallocPhy32(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocExPhy32(AllocationSize, GetAlignmentBySize(AllocationSize), AllocationFlags);
}

void LouKeFree(void* Address){
    if(!Address){
        return;
    }
    MutexLock(&GenMallocLock);
    uint64_t TmpPageTrackBase = KeMallocPageTracks;
    uint64_t TmpPageTrackLast = KeMallocPageTracks;
    uint64_t TmpVMemTrackBase;
    uint64_t TmpVMemTrackLast;
    uint64_t TrackCount = 0;
    
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(RangeInterferes(
            (uint64_t)Address, 
            1,
            PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase),
            PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase)
        )){
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            if((!(TrackCount - 1)) && (VMEM_TRACK_DEREFERENCE_READ_ADDRESS(PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase)) == (uint64_t)Address)){
                if(KeMallocPageTracks == TmpPageTrackBase){
                    MutexUnlock(&GenMallocLock);
                    return;
                }
                PAGE_TRACK_DEREFERENCE_WRITE_NEXT(TmpPageTrackLast, PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase));
                LouKeFreePage((PVOID)PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase));
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                TmpVMemTrackLast = TmpVMemTrackBase;
                while(TmpVMemTrackBase){
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                    LouGeneralFreeMemory((void*)TmpVMemTrackLast);
                    TmpVMemTrackLast = TmpVMemTrackBase;
                }
                LouGeneralFreeMemory((void*)TmpPageTrackBase);
                MutexUnlock(&GenMallocLock);
                return;
            }else{
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                TmpVMemTrackLast = TmpVMemTrackBase;
                while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                    if(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase) == (uint64_t)Address){
                        if(TmpVMemTrackBase == TmpVMemTrackLast){
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                            LouGeneralFreeMemory((void*)TmpVMemTrackBase);
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                            MutexUnlock(&GenMallocLock);
                            return;
                        }else{
                            VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackLast, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                            LouGeneralFreeMemory((void*)TmpVMemTrackBase);
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                            MutexUnlock(&GenMallocLock);
                            return;
                        }
                    }
                    TmpVMemTrackLast = TmpVMemTrackBase;
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                }
            }
        }
        TmpPageTrackLast = TmpPageTrackBase;
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }
    MutexUnlock(&GenMallocLock);
}

void LouKeFreeVirt32(void* Address){
    if(!Address){
        return;
    }
    MutexLock(&GenMallocLock32);
    uint64_t TmpPageTrackBase = KaMallocPageTracks32;
    uint64_t TmpPageTrackLast = KaMallocPageTracks32;
    uint64_t TmpVMemTrackBase;
    uint64_t TmpVMemTrackLast;
    uint64_t TrackCount = 0;
    
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(RangeInterferes(
            (uint64_t)Address, 
            1,
            PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase),
            PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase)
        )){
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            if((!(TrackCount - 1)) && (VMEM_TRACK_DEREFERENCE_READ_ADDRESS(PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase)) == (uint64_t)Address)){
                if(KeMallocPageTracks == TmpPageTrackBase){
                    MutexUnlock(&GenMallocLock32);
                    return;
                }
                PAGE_TRACK_DEREFERENCE_WRITE_NEXT(TmpPageTrackLast, PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase));
                LouKeFreePage((PVOID)PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase));
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                TmpVMemTrackLast = TmpVMemTrackBase;
                while(TmpVMemTrackBase){
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                    LouGeneralFreeMemory((void*)TmpVMemTrackLast);
                    TmpVMemTrackLast = TmpVMemTrackBase;
                }
                LouGeneralFreeMemory((void*)TmpPageTrackBase);
                MutexUnlock(&GenMallocLock32);
                return;
            }else{
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                TmpVMemTrackLast = TmpVMemTrackBase;
                while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                    if(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase) == (uint64_t)Address){
                        if(TmpVMemTrackBase == TmpVMemTrackLast){
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                            LouGeneralFreeMemory((void*)TmpVMemTrackBase);
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                            MutexUnlock(&GenMallocLock32);
                            return;
                        }else{
                            VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackLast, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                            LouGeneralFreeMemory((void*)TmpVMemTrackBase);
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                            MutexUnlock(&GenMallocLock32);
                            return;
                        }
                    }
                    TmpVMemTrackLast = TmpVMemTrackBase;
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                }
            }
        }
        TmpPageTrackLast = TmpPageTrackBase;
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }
    MutexUnlock(&GenMallocLock32);
}

void LouKeFreePhys32(void* Address){
    if(!Address){
        return;
    }
    MutexLock(&GenMallocPhyLock);
    uint64_t TmpPageTrackBase = KeMallocPageTracksPhy;
    uint64_t TmpPageTrackLast = KeMallocPageTracksPhy;
    uint64_t TmpVMemTrackBase;
    uint64_t TmpVMemTrackLast;
    uint64_t TrackCount = 0;
    
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(RangeInterferes(
            (uint64_t)Address, 
            1,
            PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase),
            PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase)
        )){
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            if((!(TrackCount - 1)) && (VMEM_TRACK_DEREFERENCE_READ_ADDRESS(PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase)) == (uint64_t)Address)){
                if(KeMallocPageTracks == TmpPageTrackBase){
                    MutexUnlock(&GenMallocPhyLock);
                    return;
                }
                PAGE_TRACK_DEREFERENCE_WRITE_NEXT(TmpPageTrackLast, PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase));
                LouKeFreePage((PVOID)PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase));
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                TmpVMemTrackLast = TmpVMemTrackBase;
                while(TmpVMemTrackBase){
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                    LouGeneralFreeMemory((void*)TmpVMemTrackLast);
                    TmpVMemTrackLast = TmpVMemTrackBase;
                }
                LouGeneralFreeMemory((void*)TmpPageTrackBase);
                MutexUnlock(&GenMallocPhyLock);
                return;
            }else{
                if(KeMallocPageTracks == TmpPageTrackBase){
                    MutexUnlock(&GenMallocPhyLock);
                    return;
                }
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                TmpVMemTrackLast = TmpVMemTrackBase;
                while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                    if(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase) == (uint64_t)Address){
                        if(TmpVMemTrackBase == TmpVMemTrackLast){
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                            LouGeneralFreeMemory((void*)TmpVMemTrackBase);
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                            MutexUnlock(&GenMallocPhyLock);
                            return;
                        }else{
                            VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackLast, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                            LouGeneralFreeMemory((void*)TmpVMemTrackBase);
                            PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                            MutexUnlock(&GenMallocPhyLock);
                            return;
                        }
                    }
                    TmpVMemTrackLast = TmpVMemTrackBase;
                    TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
                }
            }
        }
        TmpPageTrackLast = TmpPageTrackBase;
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }
    MutexUnlock(&GenMallocPhyLock);
}

SIZE LouKeGetAllocationSize(PVOID Address){
    if(!Address){
        return 0;
    }
    uint64_t TmpPageTrackBase = KeMallocPageTracks;
    uint64_t TmpVMemTrackBase;

    
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(RangeInterferes(
            (uint64_t)Address, 
            1,
            PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase),
            PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase)
        )){
            TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
            while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                if(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase) == (uint64_t)Address){
                    return VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase);
                }
                TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }

    return 0x00;
}

void* LouKeReallocEx(
    void* Address, 
    size_t Alignment, 
    size_t NewSize
){
    if(!Address){
        return 0x00;
    }
    if(!NewSize){
        LouKeFree(Address);
        return 0x00;
    }
    MutexLock(&GenMallocLock);
    uint64_t TmpPageTrackBase = KeMallocPageTracks;
    uint64_t TmpVMemTrackBase;

    
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(RangeInterferes(
            (uint64_t)Address, 
            1,
            PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase),
            PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase)
        )){
            TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
            while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                if(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase) == (uint64_t)Address){
                    bool Relocation = false;
                    uint64_t Flags = PAGE_TRACK_DEREFERENCE_READ_FLAGS(TmpPageTrackBase);
                    size_t AllocationSize = VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase);
                    if(AllocationSize < NewSize){
                        Relocation = true;
                    }else{
                        VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, NewSize);
                    }
                    MutexUnlock(&GenMallocLock);
                    if(Relocation){
                        PVOID Tmp = LouKeMallocEx(NewSize, Alignment, Flags);
                        memcpy(Tmp, Address, AllocationSize);
                        LouKeFree(Address);
                        Address = Tmp;
                    }
                    return Address;
                }
                TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }
    MutexUnlock(&GenMallocLock);
    return 0x00;
}

void* LouKeRealloc(
    void* Address, 
    size_t NewSize
){
    return LouKeReallocEx(
        Address, 
        GetAlignmentBySize(NewSize),
        NewSize        
    );
}

void* LouKeReallocExPhy32(
    void* Address, 
    size_t Alignment, 
    size_t NewSize
){
    if(!Address){
        return 0x00;
    }
    if(!NewSize){
        LouKeFree(Address);
        return 0x00;
    }
    MutexLock(&GenMallocPhyLock);
    uint64_t TmpPageTrackBase = KeMallocPageTracksPhy;
    uint64_t TmpVMemTrackBase;

    
    while(PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase)){
        if(RangeInterferes(
            (uint64_t)Address, 
            1,
            PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase),
            PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase)
        )){
            TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
            while(VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase)){
                if(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase) == (uint64_t)Address){
                    bool Relocation = false;
                    uint64_t Flags = PAGE_TRACK_DEREFERENCE_READ_FLAGS(TmpPageTrackBase);
                    size_t AllocationSize = VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase);
                    if(AllocationSize < NewSize){
                        Relocation = true;
                    }else{
                        VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, NewSize);
                    }
                    MutexUnlock(&GenMallocLock);
                    if(Relocation){
                        PVOID Tmp = LouKeMallocEx(NewSize, Alignment, Flags);
                        memcpy(Tmp, Address, AllocationSize);
                        LouKeFree(Address);
                        Address = Tmp;
                    }
                    return Address;
                }
                TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }
    MutexUnlock(&GenMallocPhyLock);
    return 0x00;
}

void* LouKeReallocPhy32(
    void* Address, 
    size_t NewSize
){
    return LouKeReallocExPhy32(
        Address, 
        GetAlignmentBySize(NewSize),
        NewSize        
    );
}
