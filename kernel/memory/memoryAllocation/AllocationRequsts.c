#include <LouAPI.h>

typedef struct _SECTION_TRACKER{
    ListHeader      Peers;
    UINTPTR         SectionAddress;
    SIZE            VirtualSize;
}SECTION_TRACKER, * PSECTION_TRACKER;

bool CheckAndReserveVAddress(
    UINTPTR     VAddress,
    UINTPTR     size
);

LOUSTATUS 
LouKeRequestVirtualAddressAllocation(
    UINTPTR     Address,
    SIZE        size,
    PVOID*      Phy
){  
    if(!size){
        return STATUS_INVALID_PARAMETER;
    }
    if(!CheckAndReserveVAddress(Address, size)){
        return STATUS_UNSUCCESSFUL;
    }

    size_t Tmp;
    size_t i = 0;
    while(i < size){
        RequestPhysicalAddress(Address + i, (UINT64*)Phy);
        if(*Phy || (!LouKeIsPageUnMapped((UINTPTR)*Phy))){
            LouUnMapAddress(Address + i, 0x00, &Tmp, 0x00);
            i += Tmp;
        }else{
            i += KILOBYTE_PAGE;
        }
    }
    
    return STATUS_SUCCESS;
}