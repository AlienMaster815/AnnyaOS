#ifndef _APIC_H
#define _APIC_H

#ifdef _USER_MODE_CODE_
#include <Annya.h>
#else
#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif
#endif

typedef struct _LOUSINE_KERNEL_APIC_DATA{
    UINTPTR     ApicBase;
    BOOL        TscDeadlineSuport;
    BOOL        TscDeadlineEnabled;
    UINT64      CurrentTsc;
    SIZE        DefaultMsTicks;
    SIZE        CurrentTimerTicks;
}LOUSINE_KERNEL_APIC_DATA, * PLOUSINE_KERNEL_APIC_DATA;


#ifdef __cplusplus
}
#endif
#endif