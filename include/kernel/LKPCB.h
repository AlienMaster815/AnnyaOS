#ifndef _LKPCB_H
#define _LKPCB_H

#include <cstdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t LouKIRQL;

typedef struct _LOUSINE_KERNEL_APIC_DATA{
    UINTPTR     ApicBase;
    BOOL        TscDeadlineSuport;
    BOOL        TscDeadlineEnabled;
    UINT64      CurrentTsc;
    SIZE        DefaultMsTicks;
    SIZE        CurrentTimerTicks;
}LOUSINE_KERNEL_APIC_DATA, * PLOUSINE_KERNEL_APIC_DATA;

typedef struct _LKPCB{
    UINT64                      Schedualer;
    UINT8                       ProcID;
    LOUSINE_KERNEL_APIC_DATA    ApicData;
}LKPCB, * PLKPCB;

#ifndef _USER_MODE_CODE_
LouKIRQL LouKeGetIrql();
uint64_t GetGSBase();
UINT64 GetLKPCB();
#endif

#ifdef __cplusplus
}
#endif
#endif