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


//memcmp from ACPICA see /AnnyaOS/kernel/Firmware/ACPICA/utilities/utclib.c
int
memcmp (
    void                    *VBuffer1,
    void                    *VBuffer2,
    UINT64                  Count)
{
    char                    *Buffer1 = (char *) VBuffer1;
    char                    *Buffer2 = (char *) VBuffer2;


    for ( ; Count-- && (*Buffer1 == *Buffer2); Buffer1++, Buffer2++)
    {
    }

    return ((Count == 0xFFFFFFFFFFFFFFFF) ? 0 : ((unsigned char) *Buffer1 -
        (unsigned char) *Buffer2));
}

