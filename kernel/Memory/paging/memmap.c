#include <LouAPI.h>
#include "PageDefinitions.h"
#include <stdint.h>

static spinlock_t PageTableLock = {0};

//LouKe PFN Architecture

static uint64_t SafePage = 0x00;

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

void InitializeSafePage(){
    SafePage = (uint64_t)LouAllocatePhysical64UpEx(MEGABYTE_PAGE, MEGABYTE_PAGE);
}

bool LouKeIsPageUnMapped(UINTPTR PhysicalAddress){
    return (SafePage == PhysicalAddress);
}

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


void LouUnMapAddress(uint64_t VAddress, uint64_t* PAddress, uint64_t* UnmapedLength, uint64_t* PageFlags){


    while(1);
    VAddress &= ~(KILOBYTE_PAGE - 1);

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
    
    //TODO Change To UINT64*
    UNUSED PML* PML4 = (PML*)GetPageBase();

    uint64_t* PML3Directory = (uint64_t*)(PML4->PML4.entries[L4Entry] & ~(FLAGSSPACE));
    if(!PML3Directory){
        return;
    }
    uint64_t* PML2Directory = (uint64_t*)(PML3Directory[L3Entry] & ~(FLAGSSPACE));
    if(!PML2Directory){
        return;
    }
    if(PML2Directory[L2Entry] & (1 << 7)){
        if((PML2Directory[L2Entry] & ~(FLAGSSPACE)) == SafePage){
            return;
        }
        if(PAddress){
            *PAddress = PML2Directory[L2Entry] & ~(FLAGSSPACE);
        }
        if(UnmapedLength){
            *UnmapedLength = MEGABYTE_PAGE;
        }
        if(PageFlags){
            *PageFlags = PML2Directory[L2Entry] & (FLAGSSPACE);
        }
        PML2Directory[L2Entry] = GetPageValue(SafePage, (1 << 7));

    }else{
        uint64_t* PML1Directory = (uint64_t*)(PML2Directory[L2Entry] & ~(FLAGSSPACE));
        if((PML1Directory[L1Entry] & ~(FLAGSSPACE)) == SafePage){
            return;
        }
        if(PAddress){
            *PAddress = PML1Directory[L1Entry] & ~(FLAGSSPACE);
        }
        if(UnmapedLength){
            *UnmapedLength = KILOBYTE_PAGE;
        }
        if(PageFlags){
            *PageFlags = PML1Directory[L1Entry] & (FLAGSSPACE);
        }

        PML1Directory[L1Entry] = GetPageValue(SafePage, 0);
        CacheFlush(&PML1Directory[L1Entry]);

        if(PageFrameL2SanityCheck(PML2Directory[L2Entry])){
            PML2Directory[L2Entry] = GetPageValue(SafePage, 1 << 7);
            LouFree((RAMADD)PML1Directory);
        }

    }
    CacheFlush(&PML2Directory[L2Entry]);
    CacheFlush(&PML3Directory[L3Entry]);
    CacheFlush(&PML4->PML4.entries[L4Entry]);
    
    PageFlush(VAddress);
    ReloadCR3();
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


bool LouMapAddress(uint64_t PAddress, uint64_t VAddress, uint64_t FLAGS, uint64_t PageSize) {

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
    UINT64* TmpPageBase = GetPageBase();
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

uint64_t* LouKeVirtualAddresToPageValue(
    uint64_t VAddress
){

    while(1);
    // Calculate the entries for each page level
    /*uint64_t L4Entry = 0;
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
    PML* PML4 = GetPageBase();
    if(!PML4)return 0x00;
    uint64_t* LBase = (uint64_t*)&PML4->PML4.entries[0];
    if(!LBase)return 0x00;
    uint64_t TMP = LBase[L4Entry];
    TMP  &= ~(KILOBYTE_PAGE);   
    LBase = (uint64_t*)TMP;
    if(!LBase)return 0x00;
    TMP = LBase[L3Entry];
    TMP &= ~(KILOBYTE_PAGE);
    LBase = (uint64_t*)TMP;
    if(!LBase)return 0x00;
    if(IsMegabytePage(&LBase[L2Entry])){
        return &LBase[L2Entry];
    }
    TMP = LBase[L2Entry];
    TMP &= ~(KILOBYTE_PAGE);
    LBase = (uint64_t*)TMP;
    if(!LBase)return 0x00;*/
    return 0x00; //&LBase[L1Entry];
}

uint64_t LouKeGetOffsetInPage(
    uint64_t VAddress
){
    while(1);
// Calculate the entries for each page level
    /*uint64_t L4Entry = 0;
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
    //TODO: Change to UINT64*
    PML* PML4 = (PML*)GetPageBase();
    if(!PML4)return 0x00;
    uint64_t* LBase = (uint64_t*)&PML4->PML4.entries[0];
    if(!LBase)return 0x00;
    uint64_t TMP = LBase[L4Entry];
    TMP  &= ~(KILOBYTE_PAGE);   
    LBase = (uint64_t*)TMP;
    if(!LBase)return 0x00;
    TMP = LBase[L3Entry];
    TMP &= ~(KILOBYTE_PAGE);
    LBase = (uint64_t*)TMP;
    if(!LBase)return 0x00;
    uint64_t PageBase;
    if(IsMegabytePage(&LBase[L2Entry])){
        PageBase = VAddress & ~(MEGABYTE_PAGE);
    }else {
        PageBase = VAddress & ~(KILOBYTE_PAGE);
    }

    if(!PageBase)return 0x00;//sanity check*/
    return 0x00;//VAddress - PageBase;
}

uint64_t LouKePageToPhysicalAddres(uint64_t* Page){
    uint64_t ResultAddress = *Page;
    ResultAddress &= ~(KILOBYTE_PAGE);
    return  ResultAddress;
}

//this is a messy function but its required for 
//the type of page directory system i have set up
//Sory -Tyler Grenier
uint64_t ScanPageEntries(uint64_t* SearchingPage, bool MegabytPage){
    while(1);
    /*UNUSED uint64_t L4, L3, L2, L1,Page4V,Page3V,Page2V, Page1V, Result;

    PML* PML4 = GetPageBase();
    UNUSED const uint64_t* Page4 = &PML4->PML4.entries[0];
    UNUSED uint64_t* Page3;
    UNUSED uint64_t* Page2;
    UNUSED uint64_t* Page1;
    
    if(MegabytPage){
        for(L4 = 0;L4 < 512; L4++){
            //Get L4 Value
            Page4V = Page4[L4];
            //cut the botom bits off
            Page4V &= ~(PAGE_TABLE_ALIGNMENT);
            //Get Page3 Addres
            if(!Page4V)continue;
            Page3 = (uint64_t*)Page4V;
            for(L3 = 0;L3 < 512; L3++){   
                //Get L3 Value
                Page3V = Page3[L3];
                //Cut the bottom bits off
                Page3V &= ~(PAGE_TABLE_ALIGNMENT);  
                //get Page 2
                if(!Page3V)continue;
                Page2 = (uint64_t*)Page3V;
                for(L2 = 0;L2 < 512; L2++){
                    //page 2 value for megabyte pages will be the 
                    //actual pointer to the page
                    Page2V = (uint64_t)&Page2[L2];
                    Page2V &= ~(PAGE_TABLE_ALIGNMENT);
                    if(!Page2V)continue;
                    if(Page2V == (uint64_t)SearchingPage){
                        //Add the sum of the Virtual Address
                        Result = L4 * (512ULL * GIGABYTE);
                        Result += L3 * (GIGABYTE);
                        Result += L2 * MEGABYTE_PAGE;
                        //return the virtual Address
                        return Result; 
                    }
                } 
            }
        }
    }else{
        for(L4 = 0;L4 < 512; L4++){
            //Get L4 Value
            Page4V = Page4[L4];
            //cut the botom bits off
            Page4V &= ~(PAGE_TABLE_ALIGNMENT);
            //Get Page3 Addres
            if(!Page4V)continue;
            Page3 = (uint64_t*)Page4V;
            for(L3 = 0;L3 < 512; L3++){   
                //Get L3 Value
                Page3V = Page3[L3];
                //Cut the bottom bits off
                Page3V &= ~(PAGE_TABLE_ALIGNMENT);  
                //get Page 2
                if(!Page3V)continue;
                Page2 = (uint64_t*)Page3V;
                for(L2 = 0;L2 < 512; L2++){
                    //Get L2 Value
                    Page2V = Page2[L2];
                    //Cut the bottom bits off
                    Page2V &= ~(PAGE_TABLE_ALIGNMENT);
                    //get page 1
                    if(!Page2V)continue;
                    Page1 = (uint64_t*)Page2V;
                    for(L1 = 0 ; L1 < 512 ; L1++){
                        //Page 1 Value will be the pointer 
                        //to the page one value
                        Page1V = (uint64_t)&Page1[L1];
                        Page1V &= ~(PAGE_TABLE_ALIGNMENT);
                        if(!Page1V)continue;
                        if(Page1V == (uint64_t)SearchingPage){
                            //Add the sum of the Virtual Address
                            Result = L4 * (512ULL * GIGABYTE);
                            Result += L3 * (GIGABYTE);
                            Result += L2 * MEGABYTE_PAGE;
                            Result += L1 * KILOBYTE_PAGE;
                            //return the virtual Address
                            return Result;
                        }
                    }
                }
            }
        }
    }*/
    return 0;
} 

uint64_t LouKeGetPageAddress(uint64_t* Page){
    return ScanPageEntries(Page, IsMegabytePage(Page));
}
