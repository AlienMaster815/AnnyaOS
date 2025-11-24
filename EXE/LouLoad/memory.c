#include <LouLoad.h>
#include <LoaderPrivate.h>

extern LOUSINE_LOADER_INFO KernelLoaderInfo;
extern UINT64 GetPageValue();
extern UINT64 GetCr3Address();
extern void SetCr3(UINT64 Value);

static void CalculateTableMarks(
    uint64_t VAddress,
    uint64_t* L4Entry,
    uint64_t* L3Entry,
    uint64_t* L2Entry,
    uint64_t* L1Entry
){
    *L4Entry = (VAddress >> 39) & 0x1FF;
    *L3Entry = (VAddress >> 30) & 0x1FF;
    *L2Entry = (VAddress >> 21) & 0x1FF;
    *L1Entry = (VAddress >> 12) & 0x1FF;
}

static inline void CacheFlush(void* addr) {
    asm volatile ("clflush (%0)" :: "r"(addr) : "memory");
    asm volatile ("mfence");
}

static inline void PageFlush(uint64_t addr) {
    asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
    asm("mfence");
}


static inline void ReloadCR3() {
    uint64_t cr3;
    asm volatile ("mov %%cr3, %0" : "=r"(cr3));
    asm volatile ("mov %0, %%cr3" :: "r"(cr3));
}

void 
memzero(
    void*   pDestination, 
    size_t  Count
){
    for(size_t i = 0 ; i < Count; i++){
        ((UINT8*)pDestination)[i] = 0;
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

void memcpy(
    void* pDestination, 
    void* pSource, 
    size_t Count
){
    UINT8* Destination = pDestination;
    UINT8* Source = pSource;
    for(size_t i = 0 ; i < Count; i++){
        Destination[i] = Source[i];
    }
}

static void GetTableBases(
    UINT64  L4, 
    UINT64  L3, 
    UINT64* L3Base,
    UINT64* L2Base
){
    UINT64 TL3Base = 512; // L3 Semment starts at 512th quadword
    UINT64 TL2Base = (KernelLoaderInfo.KernelVm.KernelPml4 * 512) + 512; //L2 segment starts after the allocates L3 segment

    TL3Base += (512 * L4); //segmentation is 512 quads per L4
    TL2Base += ((512 * 512) * L3); //segmentations i 512 quads for 512 entries per L3
    *L3Base = TL3Base;
    *L2Base = TL2Base;
}

static void LoaderMapKernelMemory(UINT64 PAddress, UINT64 VAddress, UINT64 Flags){
    UINT64* ClusterBase = (UINT64*)(UINT8*)KernelLoaderInfo.KernelVm.LargePageClusters;

    UINT64 L4, L3, L2, L1;
    CalculateTableMarks(
        VAddress, 
        &L4, 
        &L3, 
        &L2, 
        &L1
    );

    UINT64 L3Base; 
    UINT64 L2Base;
    
    GetTableBases(
        L4, 
        L3, 
        &L3Base, 
        &L2Base
    ); 

    ClusterBase[L2Base + L2]    = GetPageValue(PAddress, (1 << 7) | Flags);
    ClusterBase[L3Base + L3]    = GetPageValue(&ClusterBase[L2Base], 0b111);
    ClusterBase[L4]             = GetPageValue(&ClusterBase[L3Base], 0b111);

    PageFlush(VAddress);
    ReloadCR3();
}


void LoaderMapKernelMemoryBlock(UINT64 PAddress, UINT64 VAddress, UINT64 Size, UINT64 Flags){
    for(size_t i = 0; i < Size; i += (2 * MEGABYTE)){
        LoaderMapKernelMemory(PAddress + i, VAddress + i, Flags);
    }   
}

static void MapKernelSpace(){
    LoaderMapKernelMemoryBlock(
        0, 
        GetKSpaceBase(), 
        ROUND_UP64(GetRamSize(), 2 * MEGABYTE), 
        0b011
    );
        
}

void LoaderCreateKernelSpace(){

    UNUSED UINT64 KSpaceBase = KERNEL_SPACE_DEFAULT_BASE;
    UINT64 KSpaceLimit = ROUND_UP64(GetRamSize(), 4096);
    UINT64 Frames = 1; //PML4
    UINT64 L4, L3, L2, L1;

    CalculateTableMarks(
        KSpaceLimit,
        &L4,
        &L3,
        &L2,
        &L1
    );

    SetKSpaceBase(KSpaceBase);
    //KernelLoaderInfo.KernelVm.KernelVmBase = KSpaceBase;
    KernelLoaderInfo.KernelVm.KernelVmLimit = KSpaceLimit;
    KernelLoaderInfo.KernelVm.KernelPml4 = (UINT8)L4 + 1;
    KernelLoaderInfo.KernelVm.KernelPml3 = (UINT8)L3 + 1;
    KernelLoaderInfo.KernelVm.KernelPml2 = (UINT8)L2 + 1;

    Frames += KernelLoaderInfo.KernelVm.KernelPml4;
    Frames += (KernelLoaderInfo.KernelVm.KernelPml3 * 512); //L2s
    void* KSpaceManager = LoaderAllocateMemoryEx(
        Frames * 4096, 4096
    );
    EnforceLoaderMemoryMap((UINT64)KSpaceManager + GetKSpaceBase(), Frames * 4096);

    KernelLoaderInfo.KernelVm.LargePageClusters = (UINT64)KSpaceManager;

    UINT64* Pml4 = (UINT64*)GetCr3Address();
    *(UINT64*)(KSpaceManager) = Pml4[0];
    SetCr3((UINT64)KSpaceManager);

    MapKernelSpace();

    
}

