#include <LouAPI.h>
#include "PageDefinitions.h"
#include <stdint.h>

static spinlock_t PageTableLock = {0};

//LouKe PFN Architecture

void CacheFlush(void* addr) {
    asm volatile ("clflush (%0)" :: "r"(addr) : "memory");
    asm volatile ("mfence");
}

static inline void ReloadCR3() {
    uint64_t cr3;
    asm volatile ("mov %%cr3, %0" : "=r"(cr3));
    asm volatile ("mov %0, %%cr3" :: "r"(cr3));
}

void CalculateTableMarks(
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

static LOU_PFN_TABLE_ENTRY PfnDatabase = {0};
static size_t PageFrameCount = 0;

void LouKeMallocPageFrameNumber(
    uint64_t Virtual,
    uint64_t Physical,
    bool     LargePage,
    uint64_t Flags,
    uint64_t PageAddress
){
    PLOU_PFN_TABLE_ENTRY CurrentEntry = &PfnDatabase, LastEntry = 0;

    for(size_t i = 0; i < PageFrameCount; i++){
        if(CurrentEntry->Chain.NextHeader){
            LastEntry = CurrentEntry;
            CurrentEntry = (PLOU_PFN_TABLE_ENTRY)CurrentEntry->Chain.NextHeader;
        }else{ //Unlikely
            //TODO:Bluescreen for Data Leak, Memory manager is compromised use panic KCall
            while(1);
        }
    }
    
    CurrentEntry->Chain.LastHeader  = (PListHeader)LastEntry;
    CurrentEntry->VirtualAddress    = Virtual;
    CurrentEntry->PhysicalAddres    = Physical;
    CurrentEntry->LargePage         = LargePage;
    CurrentEntry->PresentPage       = true;
    CurrentEntry->Flags             = Flags;
    CurrentEntry->PageAddress       = PageAddress;
    CurrentEntry->Chain.NextHeader  = (PListHeader)LouGeneralAllocateMemoryEx(sizeof(LOU_PFN_TABLE_ENTRY), GET_ALIGNMENT(LOU_PFN_TABLE_ENTRY));
    PageFrameCount++;
}

static inline bool IsPfnPhysicalCompatible(
    PLOU_PFN_TABLE_ENTRY    Pfn,
    uint64_t                Physical
){
    if(
        (Pfn->PhysicalAddres == Physical) && 
        (Pfn->PresentPage == true) 
    )return  true;
    return false;
}

PLOU_PFN_TABLE_ENTRY LouKePageToPFNIndex(
    uint64_t PAddress,
    PLOU_PFN_TABLE_ENTRY PfnIndex
){
    PLOU_PFN_TABLE_ENTRY CurrentEntry = &PfnDatabase;
    size_t i = 0;
    for(; i < PageFrameCount; i++){
        if(CurrentEntry == PfnIndex){
            break;
        }
        if(CurrentEntry->Chain.NextHeader){
            CurrentEntry = (PLOU_PFN_TABLE_ENTRY)CurrentEntry->Chain.NextHeader;
        }
        else{ //Unlikely
            CurrentEntry = &PfnDatabase;
        }
    }

    for(; i < PageFrameCount; i++){
        if(IsPfnPhysicalCompatible(
            CurrentEntry,
            PAddress
        )){
            return CurrentEntry;
        }
        if(CurrentEntry->Chain.NextHeader){
            CurrentEntry = (PLOU_PFN_TABLE_ENTRY)CurrentEntry->Chain.NextHeader;
        }else if(i == (PageFrameCount - 1)){
            if(&PfnDatabase == PfnIndex){
                return PfnIndex;
            }else{
                CurrentEntry = &PfnDatabase;
                i = 0; 
            }
        }else {
            if((uint64_t)CurrentEntry->Chain.NextHeader == (uint64_t)PfnIndex){
                return PfnIndex;
            }
        }
    }
    return 0x00;
}

PLOU_PFN_TABLE_ENTRY LouKePageToPFN(
    uint64_t PAddress
){
    return  LouKePageToPFNIndex(PAddress, &PfnDatabase);
}

//Endof LouKe PFN Architecture

#define StartMap (10ULL * MEGABYTE)

uint64_t GetCr3() {
    uint64_t cr3_value;
    __asm__ volatile ("mov %%cr3, %0" : "=r" (cr3_value));
    return cr3_value;
}

UINT64* GetPageBase() {
    return (UINT64*)(GetCr3() & 0x000FFFFFFFFFF000ULL);
}

static inline void PageFlush(uint64_t addr) {
    asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
    asm("mfence");
}


bool IsMegabytePage(uint64_t* PageAddress){
    if(*PageAddress & (1 << 7)){
        return true;
    }
    return false;
}


// Utility functions used in LouMapAddress
void InitializePageTable(uint64_t* PageTable) {
    memset((void*)PageTable, 0, sizeof(uint64_t) * 512);
}

void InitializePageTableWithIndex(uint64_t* PageTable, uint64_t StartIndex, uint64_t PageSize) {
    for (uint16_t i = 0; i < 512; i++) {
        PageTable[i] = GetPageValue(StartIndex, 0b111);
        StartIndex += PageSize;
    }
}

#define PAGE_TABLE_ALIGNMENT 4096
#define nullptr 0x00

void CalculateInvalidationEntries(
    uint64_t*   PML4,
    uint64_t    L4Entry,
    uint64_t    L3Entry,
    uint64_t    L2Entry,
    uint64_t    L1Entry,
    uint64_t*   L4Table,
    uint64_t*   L3Table,
    uint64_t*   L2Table,
    uint64_t*   L1Table
){
    *L4Table = (uint64_t)PML4;
    *L3Table = L4Table[L3Entry] & ~(PAGE_TABLE_ALIGNMENT - 1); 
    if(!(*L3Table))return;
    *L2Table = L3Table[L2Entry] & ~(PAGE_TABLE_ALIGNMENT - 1);
    if(!(*L2Table))return;
    *L1Table = L2Table[L1Entry] & ~(PAGE_TABLE_ALIGNMENT - 1); 
}

static inline bool PageFrameL2MbSanityCheck(uint64_t old2){
    return (old2 & (1 << 7));
}

static inline bool PageFrameL2SanityCheck(uint64_t oldL2){
    if(!(oldL2 & (1 << 7)) && (oldL2 & (UINT64_MAX & ~(FLAGSSPACE)))){
        uint64_t* PageCheck = (uint64_t*)(oldL2 & ~(FLAGSSPACE));
        //sanity check all page frames for active pages
        for(size_t i = 0; i < 512; i++){
            if(PageCheck[i] & PRESENT_PAGE){
                //a higher function will check this
                return false;
            } 
        }
    }
    return true;
}

static UINT64* PageDown(UINT64* PageUpperBase, UINT64 UpperIndex){
    UINT64 Base = PageUpperBase[UpperIndex] & ~(FLAGSSPACE);
    if(!Base){
        Base = (UINT64)LouGeneralAllocateMemoryEx(4096, 4096);
        PageUpperBase[UpperIndex] = GetPageValue(Base - GetKSpaceBase(), 0b111);
    }else {
        Base += GetKSpaceBase();
    }

    return (UINT64*)Base;
}

void LouUnMapAddress(uint64_t VAddress, uint64_t* PAddress, uint64_t* UnmapedLength, uint64_t* PageFlags){

    LouKIRQL Irql;
    VAddress &= ~(KILOBYTE_PAGE - 1);

    if(RangeInterferes(VAddress, 1, GetKSpaceBase(), GetRamSize())){
        DEBUG_TRAP
        while(1);
    }

    LouKeAcquireSpinLock(&PageTableLock, &Irql);

    // Calculate the entries for each page level
    uint64_t L4Entry = 0;
    uint64_t L3Entry = 0;
    uint64_t L2Entry = 0;
    uint64_t L1Entry = 0;
    
    CalculateTableMarks(
        VAddress,
        &L4Entry,
        &L3Entry,
        &L2Entry,
        &L1Entry
    );
    
    UINT64* TmpPageBase = GetPageBase();
    UINT64  TmpPageValue;
    TmpPageBase = (UINT64*)((UINT64)TmpPageBase + GetKSpaceBase());
    TmpPageBase = PageDown(TmpPageBase, L4Entry);    
    TmpPageBase = PageDown(TmpPageBase, L3Entry);
    TmpPageValue = TmpPageBase[L2Entry];

    if(TmpPageValue & (1 << 7)){
        if(UnmapedLength){
            *UnmapedLength = MEGABYTE_PAGE;
        }
        if(PageFlags){
            *PageFlags = TmpPageValue & FLAGSSPACE; 
        }
        if(PAddress){
            *PAddress = TmpPageValue & ~(FLAGSSPACE);
        }
        TmpPageValue &= ~(PRESENT_PAGE);
        TmpPageBase[L2Entry] = TmpPageValue;
    }else{
        TmpPageValue &= ~(FLAGSSPACE);
        TmpPageBase = (UINT64*)(UINT8*)(TmpPageValue + GetKSpaceBase());
        TmpPageValue = TmpPageBase[L1Entry];
        if(UnmapedLength){
            *UnmapedLength = KILOBYTE_PAGE;
        }
        if(PageFlags){
            *PageFlags = TmpPageValue & FLAGSSPACE; 
        }
        if(PAddress){
            *PAddress = TmpPageValue & ~(FLAGSSPACE);
        }   
        TmpPageValue &= ~(PRESENT_PAGE);
        TmpPageBase[L1Entry] = TmpPageValue;
    }

    ReloadCR3();
    LouKeReleaseSpinLock(&PageTableLock, &Irql);
}
bool LouMapAddressEx(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize, UINT64* TmpPageBase);

bool LouMapAddress(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize){
    return LouMapAddressEx(PAddress, VAddress, FLAGS, PageSize,  GetPageBase());
}

bool LouMapAddressEx(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize, UINT64* TmpPageBase){

    // Calculate the entries for each page level
    LouKIRQL Irql;
    uint64_t L4Entry = 0;
    uint64_t L3Entry = 0;
    uint64_t L2Entry = 0;
    uint64_t L1Entry = 0;

    CalculateTableMarks(
        VAddress,
        &L4Entry,
        &L3Entry,
        &L2Entry,
        &L1Entry
    );

    if(RangeInterferes(VAddress, 1, GetKSpaceBase(), GetRamSize())){
        DEBUG_TRAP
        while(1);
    }
    LouKeAcquireSpinLock(&PageTableLock, &Irql);
    
    TmpPageBase = (UINT64*)((UINT64)TmpPageBase + GetKSpaceBase());
    TmpPageBase = PageDown(TmpPageBase,L4Entry);    
    TmpPageBase = PageDown(TmpPageBase,L3Entry);
    UINT64* NewPage;

    if(PageSize == MEGABYTE_PAGE){
        if(!(TmpPageBase[L2Entry] & (1 << 7))){
            LouFree((RAMADD)(TmpPageBase[L2Entry] & ~(FLAGSSPACE)));
        }
        TmpPageBase[L2Entry] = GetPageValue(PAddress, FLAGS | (1 << 7));
    }else if(PageSize == KILOBYTE_PAGE){
        if(TmpPageBase[L2Entry] & (1 << 7)){
            NewPage = LouGeneralAllocateMemoryEx(4096, 4096);
            InitializePageTableWithIndex(NewPage, TmpPageBase[L2Entry] & ~(FLAGSSPACE), KILOBYTE_PAGE);
            TmpPageBase[L2Entry] = GetPageValue(((UINT64)NewPage - GetKSpaceBase()), 0b111);
        }else if(!(TmpPageBase[L2Entry] & ~(FLAGSSPACE))){
            NewPage = LouGeneralAllocateMemoryEx(4096, 4096);
            TmpPageBase[L2Entry] = GetPageValue(((UINT64)NewPage - GetKSpaceBase()), 0b111);
        }
        else{
            NewPage = (UINT64*)((UINT64)(TmpPageBase[L2Entry] & ~(FLAGSSPACE)) + GetKSpaceBase()); 
        }
        NewPage[L1Entry] = GetPageValue(PAddress, FLAGS);
    } 
    else {
        LouPrint("Could Not Map Memory\n");
        LouKeReleaseSpinLock(&PageTableLock, &Irql);
        return false;
    }

    PageFlush(VAddress);
    ReloadCR3();
    LouKeReleaseSpinLock(&PageTableLock, &Irql);

    return true;
}


uint64_t GetPageOfFaultValue(uint64_t VAddress) {

    return 0;
}
