#include "ntdll.h"

/*---------------------------------------
//
//  Module Lousine Kernel NT DLL 
//
//  BELL Layer For The Lousine KULA Arch
//
//  File :: Sha.c
//
//  Lousine Kernel Sha Library
//
//  Copyright (C) Tyler Grenier 2025
//  
//  Work In Progrss LOL
----------------------------------------*/

static 
uintptr_t 
SHATransform(
    uint32_t* State, 
    uint32_t* InputBuffer
){

    return 0x00;
}

NTDLL_API
void 
RSA32_API 
A_SHAInit(
    A_SHA_CONTEXT* ShaContext
){
    if(!ShaContext){
        return;
    }
    *(uint64_t*)((uint8_t*)ShaContext + 0x50) = 0;
    uint32_t* Tmp = (uint32_t*)((uint8_t*)ShaContext + 0x40);
    Tmp[0] = 0x67452301;
    Tmp[1] = 0xefcdab89;
    Tmp[2] = 0x98badcfe;
    Tmp[3] = 0x10325476;
    Tmp[4] = 0xc3d2e1f0;
}

NTDLL_API
uintptr_t 
RSA32_API 
A_SHAUpdate(
    A_SHA_CONTEXT* ShaContext, 
    uint8_t* InputBuffer, 
    size_t InputLength
){
    if(!ShaContext){
        return 0x00;
    }
    register uint32_t    HashOffsetX16R = ((uint32_t*)ShaContext)[0x16];
    register uint32_t    InputLengthR = InputLength;
    register uint32_t*   InputBufferR = (uint32_t*)InputBuffer;
    uint32_t             Result = HashOffsetX16R + InputLength;
    register uint32_t    Checksum = HashOffsetX16R & 0x3F;
    ((uint32_t*)ShaContext)[0x16] = Result;

    if(Result < InputLength){
        ((uint32_t*)ShaContext)[0x15] += 1;
    }
    if(Checksum){
        register uint32_t Index = Checksum + InputLength;
        if(Index >= 0x40){
            __builtin_memcpy((void*)(Index + (uintptr_t)ShaContext), (void*)InputBuffer, (size_t)(0x40 - Checksum));
            InputBufferR = (uint32_t*)(uint8_t*)((uintptr_t)InputBufferR + (uintptr_t)(0x40 - Checksum)); 
            InputLengthR = Index - 0x40;
            Result = SHATransform(&ShaContext->State[1], InputBufferR); 
            Index = 0;
        }
    }
    if(InputLengthR >= 0x40){
        size_t i1 = (size_t)InputLengthR;
        size_t i2;
        do{
            Result = SHATransform(&ShaContext->State[1], InputBufferR);
            InputBufferR = &InputBufferR[0x10];
            InputLengthR -= 0x40;
            i1 = i2;
            i2 -= 1;
        }while (i1 != 12);
    }
    if(!InputLengthR){
        return Result;
    }
    return (uintptr_t)__builtin_memcpy((void*)((uintptr_t)Checksum + (uintptr_t)ShaContext), InputBufferR, InputLengthR);
}

NTDLL_API
void 
RSA32_API 
A_SHAFinal(
    A_SHA_CONTEXT* ShaContext, 
    uint8_t InputBuffer[A_SHA_DIGEST_LENGTH]
){
    //register uint32_t    HashOffsetX16R = ((uint32_t*)ShaContext)[0x16];
    //register uint32_t    CheckSum = (0x40 * 2) - (HashOffsetX16R & 0x3F);
    //if((0x40 - (CheckSum & 0x3F)) > 8){
    //    Checksum = (0x40 - (CheckSum & 0x3F));
    //}
    //register TmpChecksum = Checksum;



}

