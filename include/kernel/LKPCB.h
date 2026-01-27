#ifndef _LKPCB_H
#define _LKPCB_H

#ifndef _APIC_H
#include <drivers/cpu/Apic.h>
#endif

#ifdef _USER_MODE_CODE_
#include <Annya.h>
#else
#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif    
#endif

#ifndef _LOUKIRQL_
#define _LOUKIRQL_
typedef uint8_t LouKIRQL;
#endif



typedef struct _LKPCB{
    UINT64                      Schedualer;
    UINT8                       ProcID;
    LOUSINE_KERNEL_APIC_DATA    ApicData;
}LKPCB, * PLKPCB;

#ifdef _USER_MODE_CODE_


#else 

LouKIRQL LouKeGetIrql();
uint64_t GetGSBase();
UINT64 GetLKPCB();

#ifdef _KERNEL_MODULE_

#endif
#endif

#ifdef __cplusplus
}
#endif
#endif