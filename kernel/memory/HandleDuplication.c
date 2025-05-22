#include <LouAPI.h>

uint64_t GetAllocationBlockSize(uint64_t Address);

void* LouKeForkToUserModeSection(uint64_t OriginalLocation){
    uint64_t AllocationSize = GetAllocationBlockSize(OriginalLocation);    
    LouKeMalloc((uint64_t)&AllocationSize, USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
    //Allocation Size Now Has the allocated Buffer
    if(!AllocationSize){
        return 0x00;
    }
    memcpy((void*)OriginalLocation, (void*)AllocationSize, GetAllocationBlockSize(OriginalLocation));
    return (void*)AllocationSize;
}