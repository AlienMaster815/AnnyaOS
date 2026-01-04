#ifndef _FPU_H
#define _FPU_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

typedef struct _FXSAVE_64_CONTEXT{
    UINT16      FloatControl;
    UINT16      FloatStatus;
    UINT8       FloatTag;
    UINT8       Reserved1;
    UINT16      FloadOpcode;
    UINT64      FloatIp;
    UINT64      FloatDp;
    UINT32      Mxcr;
    UINT32      MxcrMask;
}FXSAVE_64_CONTEXT, * PFXSAVE_64_CONTEXT;

#ifdef __cplusplus
}
#endif
#endif