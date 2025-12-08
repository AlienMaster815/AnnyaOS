#include <LouAPI.h>

//later were going to add thread checks for other modes

//PML* GetPageBase();

uint64_t* LouKeVirtualAddresToPageValue(
    uint64_t VAddress
);

void CalculateTableMarks(
    uint64_t VAddress, 
    uint64_t* L4Entry,
    uint64_t* L3Entry,
    uint64_t* L2Entry,
    uint64_t* L1Entry
);

PML* GetPageBase();
bool IsMegabytePage(uint64_t* PageAddress);

LOUSTATUS RequestPhysicalAddress(
    uint64_t VAddress,
    uint64_t* PAddress
){
    
    // Calculate the entries for each page level
    uint64_t L4Entry = 0;
    uint64_t L3Entry = 0;
    uint64_t L2Entry = 0;
    uint64_t L1Entry = 0;
    uint64_t AlteredVAddress;
    uint64_t AddressToPageOffset;
    CalculateTableMarks(
        VAddress,
        &L4Entry,
        &L3Entry,
        &L2Entry,
        &L1Entry
    );
    //LouPrint("VAddress:%h\n",VAddress);
    //LouPrint("L4Entry:%h\n", L4Entry);
    //LouPrint("L3Entry:%h\n", L3Entry);
    //LouPrint("L2Entry:%h\n", L2Entry);
    //LouPrint("L1Entry:%h\n", L1Entry);  

    PML* PML4 = (PML*)((UINT64)GetPageBase() + GetKSpaceBase());

    uint64_t* Tmp = &PML4->PML4.entries[0];
    Tmp = (uint64_t*)(Tmp[L4Entry] & ~(PAGE_TABLE_ALLIGNMENT - 1));
    if(!Tmp){return STATUS_UNSUCCESSFUL;}
    Tmp = (uint64_t*)(Tmp[L3Entry] & ~(PAGE_TABLE_ALLIGNMENT - 1));
    if(!Tmp){return STATUS_UNSUCCESSFUL;}

    if(IsMegabytePage(&Tmp[L2Entry])){
        AlteredVAddress = VAddress & ~(MEGABYTE_PAGE - 1);
        AddressToPageOffset = VAddress - AlteredVAddress;
        *PAddress = Tmp[L2Entry] & ~((1ULL << 21) - 1);
        *PAddress += AddressToPageOffset;
        return STATUS_SUCCESS;
    }

    Tmp = (uint64_t*)(Tmp[L2Entry] & ~(PAGE_TABLE_ALLIGNMENT - 1));
    if(!Tmp){return STATUS_UNSUCCESSFUL;}

    AlteredVAddress = VAddress & ~(KILOBYTE_PAGE - 1);
    AddressToPageOffset = VAddress - AlteredVAddress;
    *PAddress = Tmp[L1Entry] & ~(PAGE_TABLE_ALLIGNMENT - 1);
    *PAddress += AddressToPageOffset;

    return STATUS_SUCCESS;
}