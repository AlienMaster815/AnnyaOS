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

typedef struct PACKED _LKSEB{
    UINT64          KernelApEntry;
    UINT64          KernelPml4;
    UINT64          Gdt32[3];
    UINT64          Gdt64[7];
    UINT16          GDTP32[3];
    UINT16          BootStack;
    UINT32          Reserved1;
    UINT32          LKSEBEX;
    UINT32          StackPointer;
    UINT32          Reserved2;
    UINT16          GDTP64[5];
}LKSEB, * PLKSEB;

typedef struct PACKED _LKSEBEX{
    UINT64 Pml4[512];
    UINT64 Pml3Low[512];
    UINT64 Pml2Low[512];
    UINT64 Pml3High[512];
    UINT64 Pml2High[512];
}LKSEBEX, * PLKSEBEX;


#ifndef _USER_MODE_CODE_
LouKIRQL LouKeGetIrql();
uint64_t GetGSBase();
UINT64 GetLKPCB();
#endif

#ifdef __cplusplus
}
#endif
#endif