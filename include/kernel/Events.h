#ifndef _EVENTS_H
#define _EVENTS_H

#ifdef __cplusplus
extern "C"{
#endif


typedef struct _KERNEL_EVENT_OBJECT{
    BOOL                Completed;
    mutex_t             Lock;
    SIZE                TimeOut;
    SIZE                ThreadID;
}KERNEL_EVENT_OBJECT, * PKERNEL_EVENT_OBJECT;

static inline void LouKeInitializeEventTimeOut(
    PKERNEL_EVENT_OBJECT    Event,
    size_t                  TimeOut
){
    Event->TimeOut = TimeOut;
}

#ifndef _USER_MODE_CODE_

KERNEL_EXPORT LOUSTATUS LouKeWaitForEvent(PKERNEL_EVENT_OBJECT Event);
KERNEL_EXPORT void      LouKeSignalEvent(PKERNEL_EVENT_OBJECT Event);

#endif

#ifdef __cplusplus
}
#endif
#endif