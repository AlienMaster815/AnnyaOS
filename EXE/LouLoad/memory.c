#include <LouLoad.h>
#include <LoaderPrivate.h>

extern LOUSINE_LOADER_INFO KernelLoaderInfo;

void 
memset(
    void*   pDestination, 
    int     v,
    size_t  Count
){
    UINT8* Destination = (UINT8*)pDestination;
    for(size_t i = 0 ; i < Count; i++){
        Destination[Count] = (UINT8)v;
    }
}


//memcmp from ACPICA see /AnnyaOS/kernel/Firmware/ACPICA/utilities/utclib.c
int
memcmp (
    void                    *VBuffer1,
    void                    *VBuffer2,
    UINT64                  Count)
{
    char                    *Buffer1 = (char *) VBuffer1;
    char                    *Buffer2 = (char *) VBuffer2;


    for ( ; Count-- && (*Buffer1 == *Buffer2); Buffer1++, Buffer2++)
    {
    }

    return ((Count == 0xFFFFFFFFFFFFFFFF) ? 0 : ((unsigned char) *Buffer1 -
        (unsigned char) *Buffer2));
}

static void LoaderMapKernelMemory(UINT64 PAddress, UINT64 VAddress, UINT64 Flags){

}

static void LoaderMapKernelMemoryBlock(UINT64 PAddress, UINT64 VAddress, UINT64 Size, UINT64 Flags){
    for(size_t i = 0; i < Size; i += (2 * MEGABYTE)){
        LoaderMapKernelMemory(PAddress + i, VAddress + i, Flags);
    }   
}

static void MapKernelSpace(){
    struct master_multiboot_mmap_entry* mmap = (struct master_multiboot_mmap_entry*)(UINT8*)KernelLoaderInfo.RatPartition.RamMap;
    UINT16  EntryCount = (mmap->tag.size - sizeof(struct master_multiboot_mmap_entry)) / mmap->entry_size;
    struct multiboot_mmap_entry* MapEntry;
    for(UINT16 i = 0 ; i < EntryCount; i++){
        MapEntry = MapIndexToEntry(mmap, i);
        if(MapEntry->type == 1){
            LoaderMapKernelMemoryBlock(
                ROUND_DOWN64(MapEntry->addr, 4096), 
                ROUND_DOWN64(KernelLoaderInfo.KernelVm.KernelVmBase + MapEntry->addr, 4096), 
                ROUND_UP64(MapEntry->len, 4096), 
                0b011
            );
        }
    }
}


void LoaderCreateKernelSpace(){

    UNUSED UINT64 KSpaceBase = ROUND_UP64(GetRamSize(), 512 * GIGABYTE);
    UINT64 KSpaceLimit = ROUND_UP64(GetRamSize(), 4096);
    UINT64 Frames;
    Frames =  (KSpaceLimit / (512 * GIGABYTE)) ? ( KSpaceLimit / (512 * GIGABYTE)) : 1;
    Frames += ((KSpaceLimit / GIGABYTE) ? (KSpaceLimit / GIGABYTE) : 1);
    Frames += (KSpaceLimit / (2 * MEGABYTE)) ? (KSpaceLimit / (2 * MEGABYTE)) : 1;

    void* KSpaceManager = LoaderAllocateMemoryEx(
        Frames * 4096, 4096
    );

    UINT64 Rem = KSpaceLimit;
    UINT64 L4 = Rem / (512ULL * GIGABYTE);
    Rem = Rem % (512ULL * GIGABYTE);
    UINT64 L3 = Rem / (1ULL * GIGABYTE);
    Rem = Rem % (1ULL * GIGABYTE);
    UINT64 L2 = Rem / (2ULL * MEGABYTE);
    Rem = Rem % (2ULL * MEGABYTE);

    KernelLoaderInfo.KernelVm.KernelVmBase = KSpaceBase;
    KernelLoaderInfo.KernelVm.KernelVmLimit = KSpaceLimit;
    KernelLoaderInfo.KernelVm.LargePageClusters = (UINT64)KSpaceManager;
    KernelLoaderInfo.KernelVm.KernelPml4 = L4;
    KernelLoaderInfo.KernelVm.KernelPml3 = L3;
    KernelLoaderInfo.KernelVm.KernelPml2 = L2;

    MapKernelSpace();

}