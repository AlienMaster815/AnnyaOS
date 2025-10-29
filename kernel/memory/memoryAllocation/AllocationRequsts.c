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
    SIZE        size
){  
    if(!size){
        return STATUS_INVALID_PARAMETER;
    }
    if(!CheckAndReserveVAddress(Address, size)){
        return STATUS_UNSUCCESSFUL;
    }
    LouKeUnMapContinuousMemoryBlock(Address, size);
    return STATUS_SUCCESS;
}