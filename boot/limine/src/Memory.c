#include "limine.h"
#include "loader.h"
#include "cstdlib.h"
#include "cstdint.h"

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

static BOOLEAN AllocationLocationOk(UINTPTR Location, SIZE Size){
    return ((Location >= (64 * KILOBYTE)) && ((Location + Size) < (12 * MEGABYTE)));
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

UINT64* GetPageBase() {
    return (UINT64*)(GetCr3() & 0x000FFFFFFFFFF000ULL);
}


PVOID LimineGetVirtualAddress(PVOID Address){
    if(!hhdm_request.response){
        return 0x00;
    }
    return (PVOID)((UINTPTR)hhdm_request.response->offset + (UINTPTR)Address);
}

PVOID LimineGetPhysicalAddress(PVOID Address) {
    if(!hhdm_request.response){
        return 0x00;
    }

    UINT64 VirtualAddress = (UINT64)Address;
    UINT64 L4, L3, L2, L1;
    
    CalculateTableMarks(VirtualAddress, &L4, &L3, &L2, &L1);

    UINT64* Pml4 = (UINT64*)LimineGetVirtualAddress((PVOID)GetPageBase());
    UINT64 Pml4Entry = Pml4[L4];
    if(!(Pml4Entry & 0b1))return 0x00;

    UINT64* PageDirectoryTable = (UINT64*)LimineGetVirtualAddress((PVOID)(Pml4Entry & 0x000FFFFFFFFFF000ULL));
    UINT64 PageDirectoryTableEntry = PageDirectoryTable[L3];
    if(!(PageDirectoryTableEntry & 0b1))return 0x00;

    if(PageDirectoryTableEntry & (1<< 7)){
        UINT64 PhysicalBase = PageDirectoryTableEntry & 0x000FFFFFFFFFF000ULL;
        UINT64 PageOffset = VirtualAddress & 0x3FFFFFFFULL;
        return (PVOID)(PhysicalBase + PageOffset);
    }

    UINT64* PageDirectory = (UINT64*)LimineGetVirtualAddress((PVOID)(PageDirectoryTableEntry & 0x000FFFFFFFFFF000ULL));
    UINT64 PageDirectoryEntry = PageDirectory[L2];
    if(!(PageDirectoryEntry & 0b1))return 0x00;

    if(PageDirectoryEntry & (1 << 7)){
        UINT64 PhysicalBase = PageDirectoryEntry & 0x000FFFFFFFFFF000ULL;
        UINT64 PageOffset = VirtualAddress & 0x1FFFFFULL;
        return (PVOID)(PhysicalBase + PageOffset);
    }

    UINT64* PageTable = (UINT64*)LimineGetVirtualAddress((PVOID)(PageDirectoryEntry & 0x000FFFFFFFFFF000ULL));
    UINT64 PageTableEntry = PageTable[L1];
    if(!(PageTableEntry & 0b1))return 0x00;

    UINT64 PhysicalBase = PageTableEntry & 0x000FFFFFFFFFF000ULL;
    UINT64 PageOffset = VirtualAddress & 0xFFFULL;
    return (PVOID)(PhysicalBase + PageOffset);
}

PLOADER_RAT_MBR_CHUNK LoaderSetUpRatMbr(){
    if(!memmap_request.response || !module_request.response){
        return 0x00;
    }
    SIZE MapCount = memmap_request.response->entry_count;
    SIZE AllocationSizeNeeded = GetStructureSize(LOADER_RAT_MBR_CHUNK, Entries, MapCount);
    PLOADER_RAT_MBR_CHUNK Result = 0x00;

    for(SIZE i = 0; i < MapCount; i++){
        if(memmap_request.response->entries[i]->type == LIMINE_MEMMAP_USABLE){
            if((memmap_request.response->entries[i]->length > AllocationSizeNeeded) && (AllocationLocationOk(memmap_request.response->entries[i]->base, AllocationSizeNeeded))){
                memmap_request.response->entries[i]->length -= AllocationSizeNeeded;
                Result = (PLOADER_RAT_MBR_CHUNK)memmap_request.response->entries[i]->base;
                memmap_request.response->entries[i]->base += AllocationSizeNeeded;
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
        Result->Entries[i].Tracker.Base = memmap_request.response->entries[i]->base;;
        Result->Entries[i].Tracker.Length = memmap_request.response->entries[i]->length;
    }

    return Result;
}

BOOLEAN LoaderInitializeLoaderInformation(PLOADER_INFORMATION Info){

    if(
        (framebuffer_request.response == 0x00) ||
        (framebuffer_request.response->framebuffer_count < 1)
    ){
        return false;
    }

    SIZE Offset;
    SIZE MapCount = memmap_request.response->entry_count;
    SIZE AllocationSizeNeeded =  sizeof(LOADER_FB_MEMORY_MAP) * framebuffer_request.response->framebuffer_count;
    PVOID Result = 0x00;
    for(SIZE i = 0; i < MapCount; i++){
        if(memmap_request.response->entries[i]->type == LIMINE_MEMMAP_USABLE){
            if((memmap_request.response->entries[i]->length > AllocationSizeNeeded) && (AllocationLocationOk(memmap_request.response->entries[i]->base, AllocationSizeNeeded))){
                Result = (PVOID)ROUND_UP64(memmap_request.response->entries[i]->base, GET_ALIGNMENT(LOADER_FB_MEMORY_MAP));
                Offset = (UINTPTR)Result - memmap_request.response->entries[i]->base;
                memmap_request.response->entries[i]->base += (AllocationSizeNeeded + Offset);
                memmap_request.response->entries[i]->length -= (AllocationSizeNeeded + Offset);
                break;
            }
        }
    }

    if(!Result){
        return false;
    }

    memset(Result, 0, AllocationSizeNeeded);

    Info->FrameBufferCount = framebuffer_request.response->framebuffer_count;
    Info->FrameBuffers = (PLOADER_FB_MEMORY_MAP)Result;
    for(SIZE i = 0 ; i < Info->FrameBufferCount; i++){
        Info->FrameBuffers[i].Attributes = LOADER_FRAMEBUFFER_MEMORY;
        Info->FrameBuffers[i].Tracker.Base = (UINTPTR)LimineGetPhysicalAddress(framebuffer_request.response->framebuffers[i]->address);
        Info->FrameBuffers[i].Tracker.Width = framebuffer_request.response->framebuffers[i]->width;
        Info->FrameBuffers[i].Tracker.Height = framebuffer_request.response->framebuffers[i]->height;
        Info->FrameBuffers[i].Tracker.Pitch = framebuffer_request.response->framebuffers[i]->pitch;
        Info->FrameBuffers[i].Tracker.Bpp = framebuffer_request.response->framebuffers[i]->bpp;
        SIZE x, y, pitch;
        pitch = Info->FrameBuffers[i].Tracker.Pitch;
        volatile UINT32* Fb = framebuffer_request.response->framebuffers[i]->address;
        for(y = 0; y < Info->FrameBuffers[i].Tracker.Height; y++){
            for(x = 0; x < Info->FrameBuffers[i].Tracker.Width; x++){
                Fb[(y * (pitch / sizeof(UINT32))) + x] = 0x00C0C0;
            }
        }
    }
    
    Info->LoadedModulesCount = module_request.response->module_count;
    AllocationSizeNeeded = sizeof(LOADER_MEMORY_MAP) * Info->LoadedModulesCount;
    Result = 0x00;

    for(SIZE i = 0; i < MapCount; i++){
        if(memmap_request.response->entries[i]->type == LIMINE_MEMMAP_USABLE){
            if((memmap_request.response->entries[i]->length > AllocationSizeNeeded) && (AllocationLocationOk(memmap_request.response->entries[i]->base, AllocationSizeNeeded))){
                Result = (PVOID)ROUND_UP64(memmap_request.response->entries[i]->base, GET_ALIGNMENT(LOADER_MEMORY_MAP));
                Offset = (UINTPTR)Result - memmap_request.response->entries[i]->base;
                memmap_request.response->entries[i]->base += (AllocationSizeNeeded + Offset);
                memmap_request.response->entries[i]->length -= (AllocationSizeNeeded + Offset);
            }
        }
    }
    if(!Result){
        return false;
    }

    memset(Result, 0, AllocationSizeNeeded);

    Info->LoadedModules = (PLOADER_MEMORY_MAP)Result;
    for(SIZE i = 0 ; i < Info->LoadedModulesCount; i++){
        Info->LoadedModules[i].Attributes = LOADER_MODULE_MEMORY;
        Info->LoadedModules[i].Tracker.Base = (UINT64)module_request.response->modules[i]->address;
        Info->LoadedModules[i].Tracker.Length = module_request.response->modules[i]->size;
    }
 
    Info->LouLoadCoff.Tracker.Base = Info->LoadedModules[0].Tracker.Base;
    Info->LouLoadCoff.Tracker.Length = Info->LoadedModules[0].Tracker.Length;

    Info->LouLoadCoff.Tracker.Base = Info->LoadedModules[1].Tracker.Base;
    Info->LouLoadCoff.Tracker.Length = Info->LoadedModules[1].Tracker.Length;

    if(efi_system_table_request.response){
        Info->EfiSystemTable = efi_system_table_request.response->address;
    }

    if(tsc_frequency_request.response){
        Info->TscCount = tsc_frequency_request.response->frequency;
    }

    return true;
}