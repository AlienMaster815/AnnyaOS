#include "limine.h"
#include "loader.h"
#include "cstdlib.h"
#include "cstdint.h"

struct rsdp_v1 {
    char signature[8];      // Must be "RSD PTR "
    uint8_t checksum;
    char oem_id[6];
    uint8_t revision;     
    uint32_t rsdt_address;
} __attribute__((packed));


LIMINE_REQUEST struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST_ID,
    .revision = 0
};

LIMINE_REQUEST struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST_ID,
    .revision = 0
};

LIMINE_REQUEST struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0
};

LIMINE_REQUEST struct limine_paging_mode_request paging_request = {
    .id = LIMINE_PAGING_MODE_REQUEST_ID,
    .revision = 0,
    .mode = LIMINE_PAGING_MODE_X86_64_4LVL, 
};

LIMINE_REQUEST struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0,
};

LIMINE_REQUEST struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST_ID,
    .revision = 0,
};

LIMINE_REQUEST struct limine_efi_system_table_request efi_system_table_request = {
    .id = LIMINE_EFI_SYSTEM_TABLE_REQUEST_ID,
    .revision = 0,
};

LIMINE_REQUEST struct limine_tsc_frequency_request tsc_frequency_request = {
    .id = LIMINE_TSC_FREQUENCY_REQUEST_ID,
    .revision = 0,
};

static PLOADER_RAT_MBR_CHUNK RatMbrTable = 0x00;

static BOOLEAN AllocationLocationOk(UINTPTR Location, SIZE Size){
    return ((Location >= (64 * KILOBYTE)) && ((Location + Size) < (GIGABYTE)));
}


void CalculateTableMarks(
    UINT64 VirtualAddressess,
    UINT64* L4Entry,
    UINT64* L3Entry,
    UINT64* L2Entry,
    UINT64* L1Entry
){
    *L4Entry = (VirtualAddressess >> 39) & 0x1FF;
    *L3Entry = (VirtualAddressess >> 30) & 0x1FF;
    *L2Entry = (VirtualAddressess >> 21) & 0x1FF;
    *L1Entry = (VirtualAddressess >> 12) & 0x1FF;
}

UINT64 GetCr3() { 
    UINT64 cr3_value; 
    __asm__ volatile ("mov %%cr3, %0" : "=r" (cr3_value)); 
    return cr3_value; 
} 

UINT64 GetPageBase() { 
    return GetCr3() & 0x000FFFFFFFFFF000ULL; 
}

UINTPTR LimineGetVirtualAddress(UINTPTR Address){
    if(!hhdm_request.response){
        return 0x00;
    }
    return (hhdm_request.response->offset + Address);
}

UINTPTR LimineGetHhdmPhysicalAddress(UINTPTR Address){
    if(!hhdm_request.response){
        return 0x00;
    }
    return (Address - hhdm_request.response->offset);
}


UINTPTR LimineGetPhysicalAddress(UINTPTR Address) {
    if(!hhdm_request.response){
        return 0x00;
    }

    UINT64 VirtualAddress = (UINT64)Address;
    UINT64 L4, L3, L2, L1;
    
    CalculateTableMarks(VirtualAddress, &L4, &L3, &L2, &L1);

    UINT64* Pml4 = (UINT64*)LimineGetVirtualAddress((UINTPTR)GetPageBase());
    UINT64 Pml4Entry = Pml4[L4];
    if(!(Pml4Entry & 0b1))return 0x00;

    UINT64* PageDirectoryTable = (UINT64*)LimineGetVirtualAddress((UINTPTR)(Pml4Entry & 0x000FFFFFFFFFF000ULL));
    UINT64 PageDirectoryTableEntry = PageDirectoryTable[L3];
    if(!(PageDirectoryTableEntry & 0b1))return 0x00;

    if(PageDirectoryTableEntry & (1<< 7)){
        UINT64 PhysicalBase = PageDirectoryTableEntry & 0x000FFFFFFFFFF000ULL;
        UINT64 PageOffset = VirtualAddress & 0x3FFFFFFFULL;
        return (UINTPTR)(PhysicalBase + PageOffset);
    }

    UINT64* PageDirectory = (UINT64*)LimineGetVirtualAddress((UINTPTR)(PageDirectoryTableEntry & 0x000FFFFFFFFFF000ULL));
    UINT64 PageDirectoryEntry = PageDirectory[L2];
    if(!(PageDirectoryEntry & 0b1))return 0x00;

    if(PageDirectoryEntry & (1 << 7)){
        UINT64 PhysicalBase = PageDirectoryEntry & 0x000FFFFFFFFFF000ULL;
        UINT64 PageOffset = VirtualAddress & 0x1FFFFFULL;
        return (UINTPTR)(PhysicalBase + PageOffset);
    }

    UINT64* PageTable = (UINT64*)LimineGetVirtualAddress((UINTPTR)(PageDirectoryEntry & 0x000FFFFFFFFFF000ULL));
    UINT64 PageTableEntry = PageTable[L1];
    if(!(PageTableEntry & 0b1))return 0x00;

    UINT64 PhysicalBase = PageTableEntry & 0x000FFFFFFFFFF000ULL;
    UINT64 PageOffset = VirtualAddress & 0xFFFULL;
    return (UINTPTR)(PhysicalBase + PageOffset);
}

PLOADER_RAT_MBR_CHUNK LoaderSetUpRatMbr(PLOADER_INFORMATION Info){
    if(!memmap_request.response || !module_request.response){
        return 0x00;
    }
    SIZE MapCount = memmap_request.response->entry_count;
    SIZE AllocationSizeNeeded = ROUND_UP64(GetStructureSize(LOADER_RAT_MBR_CHUNK, Entries, MapCount), GET_ALIGNMENT(LOADER_RAT_MBR_CHUNK));
    PLOADER_RAT_MBR_CHUNK Result = 0x00;

    for(SIZE i = 0; i < MapCount; i++){
        if((memmap_request.response->entries[i]->base + memmap_request.response->entries[i]->length) > Info->MachineSize){
            Info->MachineSize = memmap_request.response->entries[i]->base + memmap_request.response->entries[i]->length;
        }
        if(
            (memmap_request.response->entries[i]->type == LOADER_USABLE_MEMORY) &&
            (memmap_request.response->entries[i]->base + memmap_request.response->entries[i]->length) > Info->RamSize
        ){
            Info->RamSize = memmap_request.response->entries[i]->base + memmap_request.response->entries[i]->length;
        }
    }

    for(SIZE i = 0; i < MapCount; i++){
        if(memmap_request.response->entries[i]->type == LIMINE_MEMMAP_USABLE){
            UINT64 Base = ROUND_UP64(memmap_request.response->entries[i]->base,  GET_ALIGNMENT(LOADER_RAT_MBR_CHUNK));
            UINT64 Offset = Base - memmap_request.response->entries[i]->base;

            if( 
                ((memmap_request.response->entries[i]->base + memmap_request.response->entries[i]->length) > (Base + AllocationSizeNeeded)) && 
                (AllocationLocationOk(Base, AllocationSizeNeeded))
            ){
                Result = (PLOADER_RAT_MBR_CHUNK)(UINTPTR)(Base);
                memmap_request.response->entries[i]->length -= (Offset + AllocationSizeNeeded);
                memmap_request.response->entries[i]->base = ((UINTPTR)Result + AllocationSizeNeeded); 
                break;
            }
        }
    }
    if(!Result){
        return 0x00;
    }

    memset(Result, 0, AllocationSizeNeeded);

    Result->Count = MapCount;

    for(SIZE i = 0 ; i < MapCount; i++){
        Result->Entries[i].Attributes = (LOADER_MEMORY_MAP_ATTRIBUTE)memmap_request.response->entries[i]->type;
        Result->Entries[i].Tracker.Base = memmap_request.response->entries[i]->base;
        Result->Entries[i].Tracker.Length = memmap_request.response->entries[i]->length;
    }
    RatMbrTable = Result;
    return Result;
}

BOOLEAN LoaderInitializeLoaderInformation(PLOADER_INFORMATION Info){

    if(
        (framebuffer_request.response == 0x00) ||
        (framebuffer_request.response->framebuffer_count < 1)
    ){
        return false;
    }

    SIZE AllocationSizeNeeded =  ROUND_UP64(sizeof(LOADER_FB_MEMORY_MAP), GET_ALIGNMENT(LOADER_FB_MEMORY_MAP)) * framebuffer_request.response->framebuffer_count;
    PVOID Result = LoaderAllocateSpace(AllocationSizeNeeded, GET_ALIGNMENT(LOADER_FB_MEMORY_MAP));
    if(!Result){
        return false;
    }

    Info->FrameBufferCount = framebuffer_request.response->framebuffer_count;
    Info->FrameBuffers = (PLOADER_FB_MEMORY_MAP)Result;
    for(SIZE i = 0 ; i < Info->FrameBufferCount; i++){
        Info->FrameBuffers[i].Attributes = LOADER_FRAMEBUFFER_MEMORY;
        Info->FrameBuffers[i].Tracker.Base = (UINTPTR)LimineGetHhdmPhysicalAddress((UINTPTR)framebuffer_request.response->framebuffers[i]->address);
        Info->FrameBuffers[i].Tracker.Width = framebuffer_request.response->framebuffers[i]->width;
        Info->FrameBuffers[i].Tracker.Height = framebuffer_request.response->framebuffers[i]->height;
        Info->FrameBuffers[i].Tracker.Pitch = framebuffer_request.response->framebuffers[i]->pitch;
        Info->FrameBuffers[i].Tracker.Bpp = framebuffer_request.response->framebuffers[i]->bpp;
        SIZE x, y, pitch;
        pitch = Info->FrameBuffers[i].Tracker.Pitch;
        volatile UINT32* Fb = framebuffer_request.response->framebuffers[i]->address;
        for(y = 0; y < Info->FrameBuffers[i].Tracker.Height; y++){
            for(x = 0; x < Info->FrameBuffers[i].Tracker.Width; x++){
                Fb[(y * (pitch / sizeof(UINT32))) + x] = 0x00;//0x00C0C0;
            }
        }
    }
    
    Info->LoadedModulesCount = module_request.response->module_count;
    AllocationSizeNeeded = ROUND_UP64(sizeof(LOADER_MEMORY_MAP), GET_ALIGNMENT(LOADER_MEMORY_MAP)) * Info->LoadedModulesCount;
    Result = LoaderAllocateSpace(AllocationSizeNeeded, GET_ALIGNMENT(LOADER_MEMORY_MAP));
    if(!Result){
        return false;
    }

    Info->LoadedModules = (PLOADER_MEMORY_MAP)Result;
    for(SIZE i = 0 ; i < Info->LoadedModulesCount; i++){
        Info->LoadedModules[i].Attributes = LOADER_MODULE_MEMORY;
        Info->LoadedModules[i].Tracker.Base = (UINT64)module_request.response->modules[i]->address;
        Info->LoadedModules[i].Tracker.Length = module_request.response->modules[i]->size;
    }

    if(efi_system_table_request.response){
        if((UINTPTR)efi_system_table_request.response->address > KSpaceBase){
            Info->EfiSystemTable = (KHANDLE)LimineGetHhdmPhysicalAddress((UINTPTR)efi_system_table_request.response->address);
        }
        else {
            Info->EfiSystemTable = (KHANDLE)(UINTPTR)efi_system_table_request.response->address;
        }
    }
    if(tsc_frequency_request.response){
        Info->TscCount = tsc_frequency_request.response->frequency;
    }

    if(rsdp_request.response){
        struct rsdp_v1* Rsdp = (struct rsdp_v1*)rsdp_request.response->address;
        Info->RsdpPointer = (UINT64)LimineGetHhdmPhysicalAddress((UINTPTR)Rsdp);
        if(Rsdp->revision){
            Info->RsdpVersion = Rsdp->revision;
        }
    }


    return true;
}

static inline bool RangeInterferes(uint64_t AddrA, uint64_t SizeA, uint64_t AddrB, uint64_t SizeB){
    return !( (AddrA + SizeA <= AddrB) || (AddrB + SizeB <= AddrA));
}

BOOLEAN InitializeRatSubsystem(PLOADER_INFORMATION Info){

    RatMbrTable->ChunkSize = Info->RamSize / 100;
    RatMbrTable->ChunkSize /= sizeof(RAT_TRACKER);
    PVOID Result = 0x00;
    UINT64 Base = 0;
    UINT64 Size = 0;
    for(SIZE i = 0 ; i < RatMbrTable->Count; i++){
        Base = ROUND_UP64(RatMbrTable->Entries[i].Tracker.Base,  GET_ALIGNMENT(RAT_TRACKER));
        Size = ROUND_UP64(RatMbrTable->ChunkSize * sizeof(RAT_TRACKER), GET_ALIGNMENT(RAT_TRACKER));
        if(
            (RatMbrTable->Entries[i].Attributes == LOADER_USABLE_MEMORY) &&
            ((RatMbrTable->Entries[i].Tracker.Base + RatMbrTable->Entries[i].Tracker.Length) > (Base + Size)) && 
            (AllocationLocationOk(Base, Size))
        ){
            Result = (PVOID)(UINTPTR)Base; 
            break;
        }
    }
    if(!Result){
        return false;
    }
    RatMbrTable->Mbr[0].Base = (UINTPTR)Result;
    RatMbrTable->Mbr[0].Length = Size;
    RatMbrTable->MbrChunksAllocated = 1;
    memset(Result, 0, Size);
    return true;
}

BOOLEAN LouKeRatIsAddressFreeEx(PVOID Address, SIZE Size, UINTPTR* EndofAllocations){
    if(!Address || !Size){
        return false;
    }
    PRAT_TRACKER Mbr = &RatMbrTable->Mbr[0];
    SIZE MbrChunksAllocated = RatMbrTable->MbrChunksAllocated;
    PRAT_TRACKER MbrChunkIndex = 0x00;
    SIZE MbrChunkAllocations = 0;
    for(SIZE i = 0; i < MbrChunksAllocated; i++){
        if(RangeInterferes(Mbr[i].Base, Mbr[i].Length, (UINT64)Address, Size)){
            if(EndofAllocations){
                *EndofAllocations = (Mbr[i].Base + Mbr[i].Length);  
            }
            return false;
        }
        MbrChunkIndex = (PRAT_TRACKER)Mbr[i].Base;
        MbrChunkAllocations = RatMbrTable->ChunkAllocatorIndexor[i];
        for(SIZE j = 0; j < MbrChunkAllocations; j++){
            if(RangeInterferes(MbrChunkIndex[j].Base, MbrChunkIndex[j].Length, (UINT64)Address, Size)){
                if(EndofAllocations){
                    *EndofAllocations = (MbrChunkIndex[j].Base + MbrChunkIndex[j].Length);  
                }
                return false;
            }
        }
    }
    return true;
}

BOOLEAN LouKeRatIsAddressFree(PVOID Address, SIZE Size){
    return LouKeRatIsAddressFreeEx(Address, Size, 0x00);
}

typedef BOOLEAN (*RAT_ENTRY_HANDLER)(PVOID Context, PRAT_TRACKER Tracker);

BOOLEAN LouKeRatForEachRatEntryTillTrue(RAT_ENTRY_HANDLER Handler, PVOID Context, LOADER_MEMORY_MAP_ATTRIBUTE Attributes){
    SIZE Count = RatMbrTable->Count;
    BOOLEAN Result;
    for(SIZE i = 0; i < Count; i++){
        if((Attributes == LOADER_ANY_ATTRIBUTE_MEMORY) || (RatMbrTable->Entries[i].Attributes == Attributes)){
            Result = Handler(Context, &RatMbrTable->Entries[i].Tracker);
            if(Result){
                return Result;
            }
        }
    }
    return false;
}

typedef struct _REP_GET_ALLOCATION_CTX{
    UINTPTR     Base;
    SIZE        Length;
    SIZE        Alignment;
}REP_GET_ALLOCATION_CTX, * PREP_GET_ALLOCATION_CTX;


static BOOLEAN GetFirstFreeAddressUnder1Gig(PVOID Context, PRAT_TRACKER Tracker){
    if((Tracker->Base + Tracker->Length) <= UINT16_MAX){
        return false;
    }
    PVOID Result = (PVOID)MAX(Tracker->Base, 0xFFFF);
    if(Tracker->Base > GIGABYTE){
        return false;
    }
    PREP_GET_ALLOCATION_CTX AllocContext = (PREP_GET_ALLOCATION_CTX)Context;
    Result = (PVOID)ROUND_UP64((UINTPTR)Result, AllocContext->Alignment);

    while(((UINTPTR)((UINTPTR)Result + AllocContext->Length) <= (UINTPTR)(Tracker->Base + Tracker->Length)) && (AllocationLocationOk((UINT64)Result, AllocContext->Length))){
        UINTPTR NextHint;
        if(LouKeRatIsAddressFreeEx(Result, AllocContext->Length, &NextHint)){
            AllocContext->Base = (UINTPTR)Result;
            return true;
        }        
        Result = (PVOID)ROUND_UP64((UINTPTR)NextHint, AllocContext->Alignment);   
        if((UINTPTR)Result == NextHint){
            Result = (PVOID)((UINTPTR)Result + AllocContext->Alignment);
        }
    }
    return false;
}

PRAT_TRACKER LouKeRatGetNextFreeAllocationTracker(){
    PRAT_TRACKER Mbr = &RatMbrTable->Mbr[0];
    SIZE MbrChunksAllocated = RatMbrTable->MbrChunksAllocated;
    PRAT_TRACKER MbrChunkIndex = 0x00;
    SIZE MbrChunkAllocations = 0;
    SIZE i;
    //check for fragmentation and defragment
    for(i = 0; i < MbrChunksAllocated; i++){
        MbrChunkIndex = (PRAT_TRACKER)Mbr[i].Base;
        MbrChunkAllocations = RatMbrTable->ChunkAllocatorIndexor[i];
        for(SIZE j = 0; j < MbrChunkAllocations; j++){
            //defragment if posible
            if(!MbrChunkIndex[j].Base){
                return &MbrChunkIndex[j];
            }
        }
    }
    if(MbrChunkAllocations == RatMbrTable->ChunkSize){
        if(MbrChunksAllocated >= 100){
            return 0x00;
        }
        REP_GET_ALLOCATION_CTX Context = {.Base = 0, .Length = RatMbrTable->ChunkSize * sizeof(RAT_TRACKER), .Alignment = GET_ALIGNMENT(RAT_TRACKER)};
        BOOLEAN Successfull = LouKeRatForEachRatEntryTillTrue(GetFirstFreeAddressUnder1Gig, (PVOID)&Context, LOADER_USABLE_MEMORY);
        if(!Successfull){
            return 0x00;
        }
        Mbr[i].Base = Context.Base;
        Mbr[i].Length = RatMbrTable->ChunkSize * sizeof(RAT_TRACKER);
        memset((PVOID)Mbr[i].Base, 0, Mbr[i].Length);
        RatMbrTable->MbrChunksAllocated++;
        MbrChunkIndex = (PRAT_TRACKER)Mbr[i].Base;
        MbrChunkAllocations = RatMbrTable->ChunkAllocatorIndexor[i]; //should be 0
        i++;
    }
    PRAT_TRACKER Result = &MbrChunkIndex[MbrChunkAllocations];
    MbrChunkAllocations++;
    RatMbrTable->ChunkAllocatorIndexor[i - 1] = MbrChunkAllocations;
    return Result;
}



PVOID LoaderAllocateSpace(SIZE Size, SIZE Alignment){
    PRAT_TRACKER NewTracker = LouKeRatGetNextFreeAllocationTracker();
    if(!NewTracker){
        return 0x00;
    }
    REP_GET_ALLOCATION_CTX Context = {.Base = 0, .Length = Size, .Alignment = Alignment};
    BOOLEAN Successfull = LouKeRatForEachRatEntryTillTrue(GetFirstFreeAddressUnder1Gig, (PVOID)&Context, LOADER_USABLE_MEMORY);
    if(!Successfull){
        return 0x00;
    } 
    NewTracker->Base = Context.Base;
    NewTracker->Length = Context.Length;

    memset((PVOID)Context.Base, 0, Context.Length);
    
    return (PVOID)Context.Base;
}

