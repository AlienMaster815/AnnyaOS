#ifndef _EVENTS_H
#define _EVENTD_H

#ifndef __cplusplus
#include <LouAPI.h>
#else 
#include <LouDDK.h>
extern "C"{
#endif


typedef struct _KERNEL_EVENT_OBJECT{
    BOOL        Completed;
    mutex_t     Lock;
    SIZE        TimeOut;
    SIZE        ThreadID;
}KERNEL_EVENT_OBJECT, * PKERNEL_EVENT_OBJECT;

static inline void LouKeInitializeEventTimeOut(
    PKERNEL_EVENT_OBJECT    Event,
    size_t                  TimeOut
){
    Event->TimeOut = TimeOut;
}

#ifndef _KERNEL_MODULE_

LOUSTATUS LouKeWaitForEvent(PKERNEL_EVENT_OBJECT Event);
void      LouKeSignalEvent(PKERNEL_EVENT_OBJECT Event);

#else

KERNEL_EXPORT LOUSTATUS LouKeWaitForEvent(PKERNEL_EVENT_OBJECT Event);
KERNEL_EXPORT void      LouKeSignalEvent(PKERNEL_EVENT_OBJECT Event);

#endif
#ifdef __cplusplus
}
#endif
#endif