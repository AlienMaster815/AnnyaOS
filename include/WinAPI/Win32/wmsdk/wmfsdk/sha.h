/*---------------------------------------
//
//  File :: Sha.h
//
//  Lousine Kernel Sha Library
//
//  Copyright (C) Tyler Grenier 2025
//  
----------------------------------------*/

#ifndef RSA32_API 
#define RSA32_API __stdcall
#endif

#ifndef _LOUSINE_KERNEL_SHA_H
#define _LOUSINE_KERNEL_SHA_H

#ifdef __cplusplus
extern "C" {
#endif

#define A_SHA_DIGEST_LENGTH 160/sizeof(uint8_t)

typedef struct _A_SHA_CONTEXT{
    uint32_t    FinishFlag;
    uint8_t     HashValue[A_SHA_DIGEST_LENGTH];
    uint32_t    State[5];
    uint32_t    Count[2]; //msb first
    uint8_t     InputBuffer[64];
}A_SHA_CONTEXT, * PA_SHA_CONTEXT;



#ifdef _USER_MODE_CODE_
#ifdef _LOUDLL_
void RSA32_API A_SHAInit(A_SHA_CONTEXT* ShaContext);
uintptr_t RSA32_API A_SHAUpdate(A_SHA_CONTEXT* ShaContext, uint8_t* InputBuffer, size_t InputLength);
void RSA32_API A_SHAFinal(A_SHA_CONTEXT* ShaContext, uint8_t InputBuffer[A_SHA_DIGEST_LENGTH]);
#else
__declspec(dllimport) void RSA32_API A_SHAInit(A_SHA_CONTEXT* ShaContext);
__declspec(dllimport) uintptr_t RSA32_API A_SHAUpdate(A_SHA_CONTEXT* ShaContext, uint8_t* InputBuffer, size_t InputLength);
__declspec(dllimport) void RSA32_API A_SHAFinal(A_SHA_CONTEXT* ShaContext, uint8_t InputBuffer[A_SHA_DIGEST_LENGTH]);
#endif
#else //KERNEL_CODE
void RSA32_API A_SHAInit(A_SHA_CONTEXT* ShaContext);
uintptr_t RSA32_API A_SHAUpdate(A_SHA_CONTEXT* ShaContext, uint8_t* InputBuffer, size_t InputLength);
void RSA32_API A_SHAFinal(A_SHA_CONTEXT* ShaContext, uint8_t InputBuffer[A_SHA_DIGEST_LENGTH]);
#endif //KERNEL_CODE

#ifdef __cplusplus
}
#endif
#endif //LOUSINE_KERNEL_SHA_H