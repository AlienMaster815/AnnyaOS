#include <LouAPI.h>

//for reduced overhead pages are 2mb
typedef struct _MEMORY_CHUNK{
    ListHeader TrackLink;
    uint64_t PAddress;
    uint64_t VAddress;
    uint8_t NumPages;
}MEMORY_CHUNK, * PMEMORY_CHUNK;

typedef struct _USER_MODE_VMEM_TRACK{
    ListHeader TrackLink;
    uint64_t PAddress;
    uint64_t VAddress;
    uint64_t size;
}USER_MODE_VMEM_TRACK, * PUSER_MODE_VMEM_TRACK;

static USER_MODE_VMEM_TRACK MasterTrack;
static MEMORY_CHUNK MasterChunk;

static uint64_t AllocationTracks = 0;
static uint64_t ChunkTrack = 0;

uint64_t LouKeMallocFromMap(
    uint64_t BytesNeeded,
    uint64_t MapStart,
    uint64_t MapEnd,
    uint64_t MappedTrack,
    PUSER_MODE_VMEM_TRACK MappedAddresses
);

static spinlock_t UserMallocLock;

void LouUserMalloc(uint64_t DataP){
    LouKIRQL LouIrql;
    LouKeAcquireSpinLock(&UserMallocLock, &LouIrql);

    uint64_t* Data = (uint64_t*)DataP;

    if(ChunkTrack == 0){
        if(*Data < MEGABYTE_PAGE){
            MasterChunk.PAddress = (uint64_t)LouMalloc(MEGABYTE_PAGE);
            MasterChunk.VAddress = (uint64_t)LouVMalloc(MEGABYTE_PAGE);
            MasterChunk.NumPages = 1;
            LouKeMapContinuousMemoryBlock(MasterChunk.PAddress, MasterChunk.VAddress, MEGABYTE_PAGE, PAGE_USER | PAGE_PRESENT | WRITEABLE_PAGE);
            ChunkTrack++;
        }else{
            uint8_t NeededPages = ROUND_UP64(*Data, MEGABYTE_PAGE);
            MasterChunk.PAddress = (uint64_t)LouMalloc(MEGABYTE_PAGE * NeededPages);
            MasterChunk.VAddress = (uint64_t)LouVMalloc(MEGABYTE_PAGE * NeededPages);
            MasterChunk.NumPages = NeededPages;
            LouKeMapContinuousMemoryBlock(MasterChunk.PAddress, MasterChunk.VAddress, MEGABYTE_PAGE * NeededPages, PAGE_USER | PAGE_PRESENT | WRITEABLE_PAGE);
            ChunkTrack++;
        }
    }

    PMEMORY_CHUNK TmpChunk = (PMEMORY_CHUNK)&MasterChunk;

    uint64_t Pointer = 0x00;
    while(!Pointer){
        Pointer = LouKeMallocFromMap(
            *Data, MasterChunk.VAddress,
            TmpChunk->VAddress + ((2 * MEGABYTE_PAGE) * TmpChunk->NumPages),
            AllocationTracks,
            &MasterTrack
        );
        if(TmpChunk->TrackLink.NextHeader){
            TmpChunk = (PMEMORY_CHUNK)TmpChunk->TrackLink.NextHeader;
        }else{
            TmpChunk->TrackLink.NextHeader = LouMalloc(sizeof(MEMORY_CHUNK));
            TmpChunk = (PMEMORY_CHUNK)TmpChunk->TrackLink.NextHeader;
            if(*Data < MEGABYTE_PAGE){
                TmpChunk->PAddress = (uint64_t)LouMalloc(MEGABYTE_PAGE);
                TmpChunk->VAddress = (uint64_t)LouVMalloc(MEGABYTE_PAGE);
                TmpChunk->NumPages = 1;
                LouKeMapContinuousMemoryBlock(TmpChunk->PAddress, TmpChunk->VAddress, MEGABYTE_PAGE, PAGE_USER | PAGE_PRESENT | WRITEABLE_PAGE);
                ChunkTrack++;
            }else{
                uint8_t NeededPages = ROUND_UP64(*Data, MEGABYTE_PAGE);
                TmpChunk->PAddress = (uint64_t)LouMalloc(MEGABYTE_PAGE * NeededPages);
                TmpChunk->VAddress = (uint64_t)LouVMalloc(MEGABYTE_PAGE * NeededPages);
                TmpChunk->NumPages = NeededPages;
                LouKeMapContinuousMemoryBlock(TmpChunk->PAddress, TmpChunk->VAddress, MEGABYTE_PAGE * NeededPages, PAGE_USER | PAGE_PRESENT | WRITEABLE_PAGE);
                ChunkTrack++;
            }
        }
    }

    AllocationTracks++;

    *Data = Pointer;
    LouKeReleaseSpinLock(&UserMallocLock, &LouIrql);
    return;//Endof SYSTEMCALL
}

void LouUserFree(uint64_t DataP){
    LouKIRQL LouIrql;
    LouKeAcquireSpinLock(&UserMallocLock, &LouIrql);
    uint64_t Data = *(uint64_t*)DataP;

    PMEMORY_CHUNK TmpChunk = &MasterChunk;

    for(uint64_t i = 0; i < ChunkTrack; i++){
        if((TmpChunk->VAddress <= Data) && (TmpChunk->VAddress + (TmpChunk->NumPages * MEGABYTE_PAGE) >= Data)){
            //found the VAddress Chunk;
            break;
        } 
        TmpChunk = (PMEMORY_CHUNK)TmpChunk->TrackLink.NextHeader;
    }

    

    while(1);
    LouKeReleaseSpinLock(&UserMallocLock, &LouIrql);
    return;//Endof SYSTEMCALL
}

void LouKeUserFree(void* AddressToFree){
    uint64_t Data = (uint64_t)AddressToFree;
    LouUserFree((uint64_t)&Data);
    return;
}

void* LouKeUserMalloc(size_t NumberOfBytes){
    uint64_t Foo = NumberOfBytes;
    LouUserMalloc((uint64_t)&Foo);
    return (void*)Foo;
}