//Copyright GPL-2 Tyler Grenier (2025 - 2026) 
#include <LouLoad.h> 
#include <LoaderPrivate.h> 

extern LOUSINE_LOADER_INFO KernelLoaderInfo; 
extern UINT64 GetPageValue(UINT64, UINT64); 
extern UINT64 GetCr3Address(); 
extern void SetCr3(UINT64 Value); 

static void CalculateTableMarks( uint64_t VAddress, uint64_t* L4Entry, uint64_t* L3Entry, uint64_t* L2Entry, uint64_t* L1Entry ){ 
    *L4Entry = (VAddress >> 39) & 0x1FF; 
    *L3Entry = (VAddress >> 30) & 0x1FF; 
    *L2Entry = (VAddress >> 21) & 0x1FF; 
    *L1Entry = (VAddress >> 12) & 0x1FF; 
} 

static void CalculateTableCounts(uint64_t KSpaceLimit, uint64_t* Pml3Count, uint64_t* Pml2Count) { 
    uint64_t Total2MBPages = KSpaceLimit / (2 * 1024 * 1024); 
    *Pml2Count = (Total2MBPages + 511) / 512; 
    *Pml3Count = (*Pml2Count + 511) / 512; 
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

void memzero( void* pDestination, size_t Count ){ 
    for(size_t i = 0 ; i < Count; i++){ 
        ((UINT8*)pDestination)[i] = 0; 
    } 
} 

//memcmp from ACPICA see /AnnyaOS/kernel/Firmware/ACPICA/utilities/utclib.c 
int memcmp ( void *VBuffer1, void *VBuffer2, UINT64 Count) { 
    char *Buffer1 = (char *) VBuffer1; 
    char *Buffer2 = (char *) VBuffer2; 
    for ( ; Count-- && (*Buffer1 == *Buffer2); Buffer1++, Buffer2++) { } 
    return ((Count == 0xFFFFFFFFFFFFFFFF) ? 0 : ((unsigned char) *Buffer1 - (unsigned char) *Buffer2)); 
} 

void memcpy( void* pDestination, void* pSource, size_t Count ){ 
    UINT8* Destination = pDestination; 
    UINT8* Source = pSource; 
    for(size_t i = 0 ; i < Count; i++){ 
        Destination[i] = Source[i]; 
    } 
} 

static void GetTableBases(UINT64 L4, UINT64 L3, UINT64* L3Base, UINT64* L2Base ){ 
    UINT64 StartL4, StartL3, StartL2, StartL1;
    CalculateTableMarks(GetKSpaceBase(), &StartL4, &StartL3, &StartL2, &StartL1);

    UINT64 RelativeL4 = L4 - StartL4;
    UINT64 RelativeL3 = (RelativeL4 * 512) + L3 - StartL3;

    UINT64 TotalPml3Entries = (UINT64)KernelLoaderInfo.KernelVm.KernelPml3 * 512; 
    *L3Base = 512 + (RelativeL4 * 512); 
    *L2Base = 512 + TotalPml3Entries + (RelativeL3 * 512); 
} 

static void LoaderMapKernelMemory(UINT64 PAddress, UINT64 VAddress, UINT64 Flags){ 
    UINT64* ClusterBase = (UINT64*)(UINT8*)KernelLoaderInfo.KernelVm.LargePageClusters; 
    UINT64 L4, L3, L2, L1; 
    CalculateTableMarks( VAddress, &L4, &L3, &L2, &L1 ); 

    UINT64 L3Base; 
    UINT64 L2Base; 
    GetTableBases( L4, L3, &L3Base, &L2Base ); 

    ClusterBase[L2Base + L2] = GetPageValue(PAddress, (1 << 7) | Flags); 

    if ((ClusterBase[L3Base + L3] & 1) == 0) {
        ClusterBase[L3Base + L3] = GetPageValue((UINT64)&ClusterBase[L2Base], 0b111); 
    }
    if ((ClusterBase[L4] & 1) == 0) {
        ClusterBase[L4] = GetPageValue((UINT64)&ClusterBase[L3Base], 0b111); 
    }

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
        ROUND_UP64(LouKeGetRamSize(), 2 * MEGABYTE), 
        0b011 
    ); 
} 

void LoaderCreateKernelSpace(){ 
    UNUSED UINT64 KSpaceBase = KERNEL_SPACE_DEFAULT_BASE; 
    UINT64 KSpaceLimit = ROUND_UP64(LouKeGetRamSize(), 2 * MEGABYTE); 
    UINT64 Pml3Count, Pml2Count; 
    CalculateTableCounts(KSpaceLimit, &Pml3Count, &Pml2Count); 
    UINT64 Frames = 1 + Pml3Count + Pml2Count; 
    SetKSpaceBase(KSpaceBase); 
    KernelLoaderInfo.KernelVm.KernelVmLimit = KSpaceLimit; 
    KernelLoaderInfo.KernelVm.KernelPml4 = 1; 
    KernelLoaderInfo.KernelVm.KernelPml3 = (UINT16)Pml3Count; 
    KernelLoaderInfo.KernelVm.KernelPml2 = (UINT16)Pml2Count; 
    void* KSpaceManager = LoaderAllocateMemoryEx(Frames * 4096, 4096); 
    memzero(KSpaceManager, Frames * 4096); 
    EnforceLoaderMemoryMap((UINT64)KSpaceManager + GetKSpaceBase(), Frames * 4096); 
    KernelLoaderInfo.KernelVm.LargePageClusters = (UINT64)KSpaceManager; 
    UINT64* OldPml4 = (UINT64*)GetCr3Address(); 
    UINT64* NewPml4 = (UINT64*)KSpaceManager; 
    
    NewPml4[0] = OldPml4[0]; 
    SetCr3((UINT64)KSpaceManager); 
    MapKernelSpace(); 
}
