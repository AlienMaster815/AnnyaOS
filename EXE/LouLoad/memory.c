#include <LouLoad.h>

void 
memset(
    void* pDestination, 
    size_t Count
){
    UINT8* Destination = (UINT8*)pDestination;
    for(size_t i = 0 ; i < Count; i++){
        Destination[Count] = 0;
    }
}

int 
memcmp(
    void*   pSource1,
    void*   pSource2,
    size_t  Count
){
    UINT8* Source1 = (UINT8*)pSource1;
    UINT8* Source2 = (UINT8*)pSource2;
    size_t i = 0;
    for(; i < Count && Source1[i] == Source2[i]; i++);
    return Source1[i] - Source2[i];
}

