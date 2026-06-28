#include "LouLoadPrivate.h"

typedef struct PACKED _LongModeGdt{
    uint64_t                           NULLSEG;
    uint64_t                           KCODE;
    uint64_t                           KDATA;
    uint64_t                           UCODE;
    uint64_t                           UDATA;
    uint64_t                           KPCR;
    uint64_t                           TSSLo;
    uint64_t                           TSSHi;
}LongModeGdt, * PLongModeGdt;

typedef struct PACKED _GDTREntry{
    uint16_t Length;
    uint64_t Base;
}GDTREntry, * PGDTREntry;

extern void InstallGDT(uint64_t GDT);
extern void SetCr3(uint64_t Value);

static volatile FORCE_ALIGNMENT(16) LongModeGdt GDT = {0}; 

static PLOADER_RAT_MBR_CHUNK RatMbrTable = 0x00;

BOOLEAN LoaderInitializeMemoryManager(PLOADER_INFORMATION Info){

    RatMbrTable = Info->RatMbr;

    return true;
}

static BOOLEAN AllocationLocationOk(UINTPTR Location, SIZE Size){
    return ((Location >= (64 * KILOBYTE)) && ((Location + Size) < (GIGABYTE)));
}

void CalculateTableMarks(
    UINT64  VirtualAddressess,
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

UINT64 GetCr3(){
    UINT64 cr3_value;
    __asm__ volatile ("mov %%cr3, %0" : "=r" (cr3_value));
    return cr3_value;
}

UINT64* GetPageBase(){
    return (UINT64*)(GetCr3() & 0x000FFFFFFFFFF000ULL);
}


static inline bool RangeInterferes(uint64_t AddrA, uint64_t SizeA, uint64_t AddrB, uint64_t SizeB){
    return !( (AddrA + SizeA <= AddrB) || (AddrB + SizeB <= AddrA));
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

void LouKeRatFreeAddress(UINTPTR Address){
    PRAT_TRACKER Mbr = &RatMbrTable->Mbr[0];
    SIZE MbrChunksAllocated = RatMbrTable->MbrChunksAllocated;
    PRAT_TRACKER MbrChunkIndex = 0x00;
    SIZE MbrChunkAllocations = 0;
    for(SIZE i = 0; i < MbrChunksAllocated; i++){
        if(Mbr[i].Base == (UINT64)Address){
            Mbr[i].Base = 0;
            Mbr[i].Length = 0;
            return;
        }
        MbrChunkIndex = (PRAT_TRACKER)Mbr[i].Base;
        MbrChunkAllocations = RatMbrTable->ChunkAllocatorIndexor[i];
        for(SIZE j = 0; j < MbrChunkAllocations; j++){
            if(MbrChunkIndex[j].Base == (UINT64)Address){
                MbrChunkIndex[j].Base = 0;
                MbrChunkIndex[j].Length = 0;
                return;
            }
        }
    }
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


BOOLEAN LouKeRatForEachRatEntry(RAT_ENTRY_HANDLER Handler, PVOID Context, LOADER_MEMORY_MAP_ATTRIBUTE Attributes){
    SIZE Count = RatMbrTable->Count;
    BOOLEAN Result;
    for(SIZE i = 0; i < Count; i++){
        if((Attributes == LOADER_ANY_ATTRIBUTE_MEMORY) || (RatMbrTable->Entries[i].Attributes == Attributes)){
            Result = Handler(Context, &RatMbrTable->Entries[i].Tracker);
            if(!Result){
                return Result;
            }
        }
    }
    return true;
}


typedef struct _REP_GET_ALLOCATION_CTX{
    UINTPTR     Base;
    SIZE        Length;
    SIZE        Alignment;
}REP_GET_ALLOCATION_CTX, * PREP_GET_ALLOCATION_CTX;

static BOOLEAN GetFirstFreeAddress(PVOID Context, PRAT_TRACKER Tracker){
    if((Tracker->Base + Tracker->Length) <= UINT16_MAX){
        return false;
    }
    PVOID Result = (PVOID)MAX(Tracker->Base, 0xFFFF);
    PREP_GET_ALLOCATION_CTX AllocContext = (PREP_GET_ALLOCATION_CTX)Context;
    Result = (PVOID)ROUND_UP64((UINTPTR)Result, AllocContext->Alignment);

    while(((UINTPTR)Result + AllocContext->Length) <= (UINTPTR)(Tracker->Base + Tracker->Length)){
        UINTPTR NextHint = 0x00;
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


static BOOLEAN GetFirstFreeAddressUnder1Gig(PVOID Context, PRAT_TRACKER Tracker){
    if(Tracker->Base > GIGABYTE){
        return false;
    }
    PREP_GET_ALLOCATION_CTX AllocContext = (PREP_GET_ALLOCATION_CTX)Context;
    PVOID Result = (PVOID)Tracker->Base;
    Result = (PVOID)ROUND_UP64((UINTPTR)Result, AllocContext->Alignment);

    while(((UINTPTR)((UINTPTR)Result + AllocContext->Length) <= (UINTPTR)(Tracker->Base + Tracker->Length)) && (AllocationLocationOk((UINT64)Result, AllocContext->Length))){
        UINTPTR NextHint = 0x00;
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



PVOID LouKeRatAllocatePhysicalAddress(SIZE Size, SIZE Alignment){
    PRAT_TRACKER NewTracker = LouKeRatGetNextFreeAllocationTracker();
    if(!NewTracker){
        return 0x00;
    }
    REP_GET_ALLOCATION_CTX Context = {.Base = 0, .Length = Size, .Alignment = Alignment};
    BOOLEAN Successfull = LouKeRatForEachRatEntryTillTrue(GetFirstFreeAddress, (PVOID)&Context, LOADER_USABLE_MEMORY);
    if(!Successfull){
        return 0x00;
    }
    NewTracker->Base = Context.Base;
    NewTracker->Length = Context.Length;
    return (PVOID)Context.Base;
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


void SetGDTSegmentEntry(
    uint8_t* GDTEntry,
    uint32_t Base, 
    uint32_t Limit,
    uint8_t Access, 
    uint8_t Flags
){
    GDTEntry[0] =  Limit        & 0xFF;
    GDTEntry[1] = (Limit >> 8)  & 0xFF;
    GDTEntry[6] = (Limit >> 16) & 0x0F;

    GDTEntry[2] =  Base        & 0xFF;
    GDTEntry[3] = (Base >> 8)  & 0xFF;
    GDTEntry[4] = (Base >> 16) & 0xFF;
    GDTEntry[7] = (Base >> 24) & 0xFF;

    GDTEntry[5] = Access;
    GDTEntry[6] |= Flags << 4;
}

static void InitializeGdt(){
    SetGDTSegmentEntry(
            (uint8_t*)&GDT.KCODE,
            0,
            0xFFFFF,                                              
            0x9A,
            0xA
        );

    SetGDTSegmentEntry(
            (uint8_t*)&GDT.KDATA,
            0,
            0xFFFFF,
            0x92,
            0xC
        );
    SetGDTSegmentEntry(
            (uint8_t*)&GDT.UCODE,
            0,
            0xFFFFF,
            0xFA,
            0xA
        );
    SetGDTSegmentEntry(
            (uint8_t*)&GDT.UDATA,
            0,
            0xFFFFF,
            0xF2,
            0xC
        );

    GDTREntry Gdtr;
    Gdtr.Length = sizeof(LongModeGdt) - 1;
    Gdtr.Base   = (uint64_t)&GDT;

    InstallGDT((uint64_t)&Gdtr);
}

static BOOLEAN LoaderMapMemory(UINTPTR PhysicalAddress, UINTPTR VirtualAddress, UINT64 Size){



    UINT64 L4Entry = 0, L3Entry = 0, L2Entry = 0, L1Entry = 0;

    CalculateTableMarks(
        VirtualAddress,
        &L4Entry,
        &L3Entry, 
        &L2Entry, 
        &L1Entry 
    );

    UINT64 Tmp = 0x00;
    UINT64* L4Table = (UINT64*)GetPageBase();
    UINT64* L3Table = 0x00;
    UINT64* L2Table = 0x00;
    UINT64* L1Table = 0x00;

    Tmp = (L4Table[L4Entry] & ~(KILOBYTE_PAGE - 1));
    if(!Tmp){
        L4Table[L4Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111; 
        Tmp = (L4Table[L4Entry] & ~(KILOBYTE_PAGE - 1));
    }
    L3Table = (UINT64*)Tmp;
    Tmp = L3Table[L3Entry];

    //Gigabyte Logic
    if(((((!Tmp) || (Tmp & (1 << 7))) && (Size == GIGABYTE)))){
        L3Table[L3Entry] = PhysicalAddress | 0b11 | (1 << 7);
        return true;           
    }else if((Tmp) && (Size == GIGABYTE)){
        L2Table = (UINT64*)(Tmp & ~(KILOBYTE_PAGE - 1));
        for(SIZE i = 0 ; i < 512; i++){
            if(!(L2Table[i] & (1 << 7))){
                LouKeRatFreeAddress((UINT64)L2Table[i] & ~(KILOBYTE_PAGE - 1));
            }
        }
        LouKeRatFreeAddress(Tmp & ~(KILOBYTE_PAGE - 1));
        L3Table[L3Entry] = PhysicalAddress | 0b11 | (1 << 7);
        return true;
    }

    //megabyte logic
    if((!Tmp) && (Size == MEGABYTE_PAGE)){
        L3Table[L3Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111;
        Tmp = L3Table[L3Entry] & ~(KILOBYTE_PAGE - 1);
        L2Table = (UINT64*)Tmp; 
        L2Table[L2Entry] = PhysicalAddress | 0b11 | (1 << 7);
        return true;  
    }
    else if((Tmp & (1 << 7)) && (Size == MEGABYTE_PAGE)){
        L3Table[L3Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111;
        L2Table = (UINT64*)(L3Table[L3Entry] & ~(KILOBYTE_PAGE - 1)); 
        UINT64 TmpFlags = Tmp & ((1 << 13) - 1);
        Tmp &= ~(KILOBYTE_PAGE - 1);
        for(SIZE i = 0 ; i < 512; i++){
            L2Table[i] = (Tmp + (i * MEGABYTE_PAGE)) | TmpFlags;
        }
        L2Table[L2Entry] = PhysicalAddress | 0b11 | (1 << 7);
        return true;
    }else if((Tmp) && (Size == MEGABYTE_PAGE)){
        L2Table = (UINT64*)(Tmp & ~(KILOBYTE_PAGE - 1));
        if(!(L2Table[L2Entry] & (1 << 7))){
            LouKeRatFreeAddress(L2Table[L2Entry] & ~(KILOBYTE_PAGE - 1));
        }
        L2Table[L2Entry] = PhysicalAddress | 0b11 | (1 << 7);
        return true;
    }

    //kilobyte logic
    if((!Tmp) && (Size == KILOBYTE_PAGE)){
        L3Table[L3Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111;
        Tmp = L3Table[L3Entry] & ~(KILOBYTE_PAGE - 1);
        L2Table = (UINT64*)Tmp; 
        L2Table[L2Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111;
        Tmp = L2Table[L2Entry] & ~(KILOBYTE_PAGE - 1);
        L1Table = (UINT64*)Tmp;
        L1Table[L1Entry] = PhysicalAddress | 0b11;
        return true;
    }else if((Tmp & (1 << 7)) && (Size == KILOBYTE_PAGE)){
        if(RangeInterferes(VirtualAddress, 1, VirtualAddress, Size)){
            while(1);
        }
        L3Table[L3Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111;
        L2Table = (UINT64*)(L3Table[L3Entry] & ~(KILOBYTE_PAGE - 1)); 
        UINT64 TmpFlags = Tmp & ((1 << 13) - 1);
        TmpFlags &= ~(1 << 7);
        Tmp &= ~(KILOBYTE_PAGE - 1);
        for(SIZE i = 0 ; i < 512; i++){
            L2Table[i] = (Tmp + (i * MEGABYTE_PAGE)) | TmpFlags | (1 << 7);
        }
        L2Table[L2Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111;
        L1Table = (UINT64*)(L2Table[L2Entry] & ~(KILOBYTE_PAGE - 1)); 
        for(SIZE i = 0 ; i < 512; i++){
            L1Table[i] = (Tmp + (L2Entry * MEGABYTE_PAGE) + (i * KILOBYTE_PAGE)) | TmpFlags;
        }
        L1Table[L1Entry] = PhysicalAddress | 0b11;
        return true;
    }else if((Tmp) && (Size == KILOBYTE_PAGE)){\
        L2Table = (UINT64*)(Tmp & ~(KILOBYTE_PAGE - 1));
        if(L2Table[L2Entry] & (1 << 7)){
            Tmp = L2Table[L2Entry] & ~(KILOBYTE_PAGE - 1);
            UINT64 TmpFlags = L2Table[L2Entry] & ((1 << 13) - 1);
            TmpFlags &= ~(1 << 7);
            L2Table[L2Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111;
            L1Table = (UINT64*)(L2Table[L2Entry] & ~(KILOBYTE_PAGE - 1));
            for(SIZE i = 0; i < 512; i++){
                L1Table[i] = (Tmp + (i * KILOBYTE_PAGE)) | TmpFlags;
            }
        }else if(!L2Table[L2Entry]){
            L2Table[L2Entry] = (UINT64)LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE) | 0b111;
        }
        L1Table = (UINT64*)(L2Table[L2Entry] & ~(KILOBYTE_PAGE - 1));
        L1Table[L1Entry] = PhysicalAddress | 0b11;
        return true;
    }

    return false;
}

static BOOLEAN LoaderMapContinuiousMemoryBlock(
    UINTPTR             PhysicalAddress, 
    UINTPTR             VirtualAddress, 
    SIZE                Size, 
    PLOADER_INFORMATION Info
){
    if(
        //at least one page alignment
        ((PhysicalAddress & ~(KILOBYTE_PAGE - 1)) != PhysicalAddress) ||
        ((VirtualAddress & ~(KILOBYTE_PAGE - 1)) != VirtualAddress) ||
        //at least 1 page size and size aligned to at least a kilobyte page
        (((Size & ~(KILOBYTE_PAGE - 1)) == 0) || ((Size & ~(KILOBYTE_PAGE - 1)) != Size))
    ){
        return false;
    }

    BOOLEAN Status = false;
    BOOLEAN GigPageSupport = Info->LoaderCpuFeatures & LOADER_CPU_FEATURES_GB_PAGES ? true : false;
    SIZE i = 0;

    while(i < Size){
        if(
            ((Size - i) >= GIGABYTE) &&
            (((PhysicalAddress + i) & ~(GIGABYTE - 1)) == (PhysicalAddress + i)) &&
            (((VirtualAddress + i) & ~(GIGABYTE - 1)) == (VirtualAddress + i)) && 
            (GigPageSupport)
        ){
            Status = LoaderMapMemory(PhysicalAddress + i, VirtualAddress + i, GIGABYTE);
            if(!Status){
                return Status;
            }
            i += GIGABYTE;
        }
        else if(
            ((Size - i) >= MEGABYTE_PAGE) && 
            (((PhysicalAddress + i) & ~(MEGABYTE_PAGE - 1)) == (PhysicalAddress + i)) && 
            (((VirtualAddress + i) & ~(MEGABYTE_PAGE - 1)) == (VirtualAddress + i))
        ){
            Status = LoaderMapMemory(PhysicalAddress + i, VirtualAddress + i, MEGABYTE_PAGE);
            if(!Status){
                return Status;
            }
            i += MEGABYTE_PAGE;
        }else{
            Status = LoaderMapMemory(PhysicalAddress + i, VirtualAddress + i, KILOBYTE_PAGE);
            if(!Status){
                return Status;
            }
            i += KILOBYTE_PAGE;
        }
    }
    return Status;
}

static BOOLEAN MapKernelSpaceAddresses(PVOID Context, PRAT_TRACKER Tracker){
    UINT64 BasePage = Tracker->Base & ~(KILOBYTE_PAGE - 1);
    UINT64 PageLength = Tracker->Length;
    PageLength += Tracker->Base - BasePage;
    PageLength = ROUND_UP64(PageLength, KILOBYTE_PAGE);
    return LoaderMapContinuiousMemoryBlock(BasePage, BasePage + KSpaceBase, PageLength, (PLOADER_INFORMATION)Context);
}

static BOOLEAN MapAllFreeKernelSpaceAddresses(PLOADER_INFORMATION Info){
    BOOLEAN Tmp = LouKeRatForEachRatEntry(MapKernelSpaceAddresses, (PVOID)Info, LOADER_USABLE_MEMORY);
    if(!Tmp){
        return false;
    }
    Tmp = LouKeRatForEachRatEntry(MapKernelSpaceAddresses, (PVOID)Info, LOADER_ACPI_RECLAIM_MEMORY);
    if(!Tmp){
        return false;
    }
    Tmp = LouKeRatForEachRatEntry(MapKernelSpaceAddresses, (PVOID)Info, LOADER_ACPI_NVS_MEMORY);
    if(!Tmp){
        return false;
    }
    Tmp = LouKeRatForEachRatEntry(MapKernelSpaceAddresses, (PVOID)Info, LOADER_RECLAIMABLE_MEMORY);
    if(!Tmp){
        return false;
    }
    return true;
}

static volatile FORCE_ALIGNMENT(KILOBYTE_PAGE) UINT64 Pml3[512];
static volatile FORCE_ALIGNMENT(KILOBYTE_PAGE) UINT64 Pml2[512];


BOOLEAN LoaderInitializeKernelSpace(PLOADER_INFORMATION Info){
    
    InitializeGdt();

    UINT64* Pml4 = LoaderAllocateSpace(KILOBYTE_PAGE, KILOBYTE_PAGE);
    Pml3[0] = (UINT64)&Pml2[0] | 0b111;
    for(SIZE i = 0; i < 512; i++){
        Pml2[i] = (i * (2 * MEGABYTE)) | 0b11 | (1 << 7);
    }

    Pml4[0] = (UINT64)&Pml3[0] | 0b111;

    SetCr3((UINT64)&Pml4[0]);

    UINT64 MbrPage = (UINT64)RatMbrTable & ~(KILOBYTE_PAGE - 1);
    UINT64 MbrSize = GetStructureSize(LOADER_RAT_MBR_CHUNK, Entries, RatMbrTable->Count);
    MbrSize += ((UINT64)RatMbrTable - MbrPage);
    MbrSize = ROUND_UP64(MbrSize , KILOBYTE_PAGE);

    if(!LoaderMapContinuiousMemoryBlock(MbrPage, MbrPage + KSpaceBase, MbrSize, Info)){
        return false;
    }
    
    if(!MapAllFreeKernelSpaceAddresses(Info)){
        return false;
    }

    LouKeMemoryBarrier();

    LouKeReloadCR3(); //just reload for the loader for sanity

    Info->LoadedModules = (PLOADER_MEMORY_MAP)((UINT64)Info->LoadedModules + KSpaceBase);
    Info->FrameBuffers = (PLOADER_FB_MEMORY_MAP)((UINT64)Info->FrameBuffers + KSpaceBase);
    Info->RatMbr = (PLOADER_RAT_MBR_CHUNK)((UINT64)Info->RatMbr + KSpaceBase);

    UINT64 TmpPageBase;
    UINT64 TmpPageLength;

    for(SIZE i = 0 ; i < Info->LoadedModulesCount; i++){
        TmpPageBase = ((UINT64)Info->LoadedModules[i].Tracker.Base & ~(KILOBYTE_PAGE - 1));
        TmpPageLength = ((UINT64)Info->LoadedModules[i].Tracker.Length);
        TmpPageLength += (UINT64)Info->LoadedModules[i].Tracker.Base - TmpPageBase;
        TmpPageLength = ROUND_UP64(TmpPageLength, KILOBYTE_PAGE);
        if(!LoaderMapContinuiousMemoryBlock(TmpPageBase, TmpPageBase + KSpaceBase, TmpPageLength, Info)){
            return false;
        }
        Info->LoadedModules[i].Tracker.Base += KSpaceBase;
    }

    LouKeMemoryBarrier();

    LouKeReloadCR3(); //just reload for the loader for sanity

    
    //NOTE: BOOTVID.SYS will handle framebuffers after the 
    //      kernel initializes cpu specific features such as
    //      Write Combined memory access 
    return true;
}