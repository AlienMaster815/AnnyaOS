#include "ntdll.h"

#pragma pack(push, 1)
static uint8_t ShaInitializationBuffer[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 0xF0, 0xE1, 0xD2, 0xC3};
#pragma pack(pop)


static 
int64_t 
SHATransform(int32_t* ShaDestinationHandle, int32_t* ShaSourceHandle){

    return 0;
}



NTDLL_API
int64_t A_SHAFinal(

){
    LouPrint("A_SHAFinal()\n");
    while(1);
    return 0;
}

NTDLL_API
void A_SHAInit(void* ShaHandle){
    __builtin_memcpy((void*)((uintptr_t)ShaHandle + 0x40), (void*)ShaInitializationBuffer, 0x14);
    *(uint8_t*)((uintptr_t)ShaHandle + 0x54) = 0;
}

NTDLL_API
int64_t A_SHAUpdate(
    int32_t* ShaDestinationHandle,
    int32_t* ShaSourceHandle,
    int32_t  ShaChecksum
){
    int32_t Alpha = ShaDestinationHandle[0x16], Bravo = ShaChecksum, Result = Alpha + Bravo, Romeo15 = Alpha & 0x3F;  
    int32_t* DeltaI;

    ShaDestinationHandle[0x16] = Result;

    if(Result < ShaChecksum){
        ShaDestinationHandle[0x15] += 1;
    }

    if(Romeo15 != 0){
        int32_t Santa = Romeo15 + ShaChecksum;
        if(Santa >= 0x40){
            __builtin_memcpy((void*)(uintptr_t)Romeo15 + (uintptr_t)ShaDestinationHandle, (void*)ShaSourceHandle, (U64)(0x40 - Romeo15));
            DeltaI = (int32_t*)(U64)DeltaI + (U64)(0x40 - Romeo15);
            Bravo = Santa - 0x40;
            Result = SHATransform(&ShaDestinationHandle[0x10], ShaDestinationHandle);
            Romeo15 = 0; 
        }
    }

    if(Bravo >= 0x40){
        U64 Index2 = ((U64)Bravo >> 6);
        U64 Index1 = 0;
    
        do {
            Result = SHATransform(&ShaDestinationHandle[0x10], DeltaI);
            DeltaI = &DeltaI[0x10];
            Bravo -= 0x40;
            Index1 = Index2;
            Index2 -= 1; 
        }while(Index1 != 1);
    }

    if(Bravo == 0){
        return Result;
    }

    return (uintptr_t)__builtin_memcpy((void*)(uintptr_t)((uintptr_t)Romeo15 + (uintptr_t)ShaDestinationHandle), (void*)(uintptr_t)DeltaI, (U64)Bravo);
}
