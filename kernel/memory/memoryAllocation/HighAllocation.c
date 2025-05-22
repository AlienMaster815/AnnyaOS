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
static uint64_t   KeMallocPageTracksCount = 0;
static uint64_t   KeMallocPageTracksPhy = 0;
static uint64_t   KeMallocPageTracksPhyCount = 0;

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
    for(;Size > 0 ; Size--){
        *(uint8_t*)(Address + Size) = 0;
    }
}

void* 
LouKeMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){  
    uint64_t RoundUpSize = ROUND_UP64(AllocationSize, MEGABYTE_PAGE);
    if(!KeMallocPageTracks){
        KeMallocPageTracks = (uint64_t)LouMallocEx(KMALLOC_PAGE_TRACK_SIZE , 8);
    }
    uint64_t TmpPageTrackBase = KeMallocPageTracks;
    uint64_t TmpVMemTrackBase = 0x00;
    uint64_t Base = 0x00;
    uint64_t Limit = 0x00;
    uint64_t VmemCheck = 0;
    uint64_t TrackCount = 0;
    bool FoundAddress;
    for(uint64_t i = 0 ; i < KeMallocPageTracksCount; i++){
        if(PAGE_TRACK_DEREFERENCE_READ_FLAGS(TmpPageTrackBase) == AllocationFlags){
            Base = PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase);
            Limit = Base + PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase);
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            while((Base + AllocationSize) <= Limit){
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                FoundAddress = true;
                for(VmemCheck = 0; VmemCheck < TrackCount; VmemCheck++){
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
                    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouMallocEx(KMALLOC_VMEM_TRACK_SIZE, 8));
                    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, Base);
                    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
                    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount + 1);
                    ZeroMem(Base, AllocationSize);
                    return (void*)Base;
                }
                Base += ROUND_UP64(VMEM_TRACK_DEREFERENCE_READ_SIZE(TmpVMemTrackBase), Alignment);
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }

    PAGE_TRACK_DEREFERENCE_WRITE_NEXT(TmpPageTrackBase, (uint64_t)LouMallocEx(KMALLOC_PAGE_TRACK_SIZE, 8));
    PAGE_TRACK_DEREFERENCE_WRITE_FLAGS(TmpPageTrackBase, AllocationFlags);
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_ADDRESS(TmpPageTrackBase, (uint64_t)LouKeMallocPage(MEGABYTE_PAGE, RoundUpSize / MEGABYTE_PAGE, AllocationFlags));
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_SIZE(TmpPageTrackBase, RoundUpSize);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, 1);
    TmpVMemTrackBase = (uint64_t)LouMallocEx(KMALLOC_VMEM_TRACK_SIZE, 8);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, TmpVMemTrackBase);
    
    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouMallocEx(KMALLOC_VMEM_TRACK_SIZE, 8));
    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase));
    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
    KeMallocPageTracksCount++;
    return (void*)VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase);
}

void* LouKeMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocEx(AllocationSize, GetAlignmentBySize(AllocationSize), AllocationFlags);
}

void* LouKeMallocPhysicalEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){
    uint64_t RoundUpSize = ROUND_UP64(AllocationSize, MEGABYTE_PAGE);
    if(!KeMallocPageTracksPhy){
        KeMallocPageTracksPhy = (uint64_t)LouMallocEx(KMALLOC_PAGE_TRACK_SIZE , 8);
    }
    uint64_t TmpPageTrackBase = KeMallocPageTracksPhy;
    uint64_t TmpVMemTrackBase = 0x00;
    uint64_t Base = 0x00;
    uint64_t Limit = 0x00;
    uint64_t VmemCheck = 0;
    uint64_t TrackCount = 0;
    bool FoundAddress;
    for(uint64_t i = 0 ; i < KeMallocPageTracksPhyCount; i++){
        if(PAGE_TRACK_DEREFERENCE_READ_FLAGS(TmpPageTrackBase) == AllocationFlags){
            Base = PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase);
            Limit = Base + PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase);
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            while((Base + AllocationSize) <= Limit){
                TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);
                FoundAddress = true;
                for(VmemCheck = 0; VmemCheck < TrackCount; VmemCheck++){
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
                    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouMallocEx(KMALLOC_VMEM_TRACK_SIZE, 8));
                    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, Base);
                    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
                    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount + 1);
                    ZeroMem(Base, AllocationSize);
                    return (void*)Base;
                }
                Base += Alignment;
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }

    PAGE_TRACK_DEREFERENCE_WRITE_NEXT(TmpPageTrackBase, (uint64_t)LouMallocEx(KMALLOC_PAGE_TRACK_SIZE, 8));
    PAGE_TRACK_DEREFERENCE_WRITE_FLAGS(TmpPageTrackBase, AllocationFlags);
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_ADDRESS(TmpPageTrackBase, (uint64_t)LouKeMallocPage32(MEGABYTE_PAGE, RoundUpSize / MEGABYTE_PAGE, AllocationFlags));
    PAGE_TRACK_DEREFERENCE_WRITE_PAGE_SIZE(TmpPageTrackBase, RoundUpSize);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, 1);
    TmpVMemTrackBase = (uint64_t)LouMallocEx(KMALLOC_VMEM_TRACK_SIZE, 8);
    PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, TmpVMemTrackBase);
    
    VMEM_TRACK_DEREFERENCE_WRITE_NEXT(TmpVMemTrackBase, (uint64_t)LouMallocEx(KMALLOC_VMEM_TRACK_SIZE, 8));
    VMEM_TRACK_DEREFERENCE_WRITE_ADDRESS(TmpVMemTrackBase, PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase));
    VMEM_TRACK_DEREFERENCE_WRITE_SIZE(TmpVMemTrackBase, AllocationSize);
    KeMallocPageTracksPhyCount++;
    return (void*)VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase);
}


void* LouKeMallocPhysical(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocPhysicalEx(AllocationSize, AllocationSize, AllocationFlags);
}

void LouKeFree(void* Address){
    if(!Address){
        return;
    }
    uint64_t TmpPageTrackBase = KeMallocPageTracks;
    uint64_t TmpVMemTrackBase;
    uint64_t VmemCheck = 0;
    uint64_t TrackCount = 0;
    uint64_t Foo = 0;
    for(uint64_t PageCount = 0; PageCount < KeMallocPageTracksCount; PageCount++){
        
        if(RangeInterferes(
            (uint64_t)Address, 
            1,
            PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase),
            PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase)
        )){
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);

            for(VmemCheck = 0 ; VmemCheck < TrackCount; VmemCheck++){

                if(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase) == (uint64_t)Address){
                    if(TmpVMemTrackBase == PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase)){
                        PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                        LouFree((RAMADD)TmpVMemTrackBase);
                        PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                        return;
                    }else{
                        VMEM_TRACK_DEREFERENCE_WRITE_NEXT(Foo, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                        LouFree((RAMADD)TmpVMemTrackBase);
                        PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                        return;
                    }
                }
                Foo = TmpVMemTrackBase;
                TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }
}

void LouKeFreePhysical(void* Address){
    if(!Address){
        return;
    }
    uint64_t TmpPageTrackBase = KeMallocPageTracksPhy;
    uint64_t TmpVMemTrackBase;
    uint64_t VmemCheck = 0;
    uint64_t TrackCount = 0;
    uint64_t Foo = 0;
    for(uint64_t PageCount = 0; PageCount < KeMallocPageTracksPhyCount; PageCount++){
        if(RangeInterferes(
            (uint64_t)Address, 
            1,
            PAGE_TRACK_DEREFERENCE_READ_PAGE_ADDRESS(TmpPageTrackBase),
            PAGE_TRACK_DEREFERENCE_READ_PAGE_SIZE(TmpPageTrackBase)
        )){
            TrackCount = PAGE_TRACK_DEREFERENCE_READ_TRACK_COUNT(TmpPageTrackBase);
            TmpVMemTrackBase = PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase);

            for(VmemCheck = 0 ; VmemCheck < TrackCount; VmemCheck++){

                if(VMEM_TRACK_DEREFERENCE_READ_ADDRESS(TmpVMemTrackBase) == (uint64_t)Address){
                    if(TmpVMemTrackBase == PAGE_TRACK_DEREFERENCE_READ_TRACK_BASE(TmpPageTrackBase)){
                        PAGE_TRACK_DEREFERENCE_WRITE_TRACK_BASE(TmpPageTrackBase, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                        LouFree((RAMADD)TmpVMemTrackBase);
                        PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                        return;
                    }else{
                        VMEM_TRACK_DEREFERENCE_WRITE_NEXT(Foo, VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase));
                        LouFree((RAMADD)TmpVMemTrackBase);
                        PAGE_TRACK_DEREFERENCE_WRITE_TRACK_COUNT(TmpPageTrackBase, TrackCount - 1);
                        return;
                    }
                }
                Foo = TmpVMemTrackBase;
                TmpVMemTrackBase = VMEM_TRACK_DEREFERENCE_READ_NEXT(TmpVMemTrackBase);
            }
        }
        TmpPageTrackBase = PAGE_TRACK_DEREFERENCE_READ_NEXT(TmpPageTrackBase);//get the next value
    }
}