#ifndef TIME_H
#define TIME_H
#ifdef __x86_64__
#ifdef __cplusplus

#define MilliSec 1
#define Sec 2

#include <LouDDK.h>



#ifndef _KERNEL_MODULE_
KERNEL_IMPORT uint64_t GetCurrentTimeInMilliseconds();
KERNEL_IMPORT void sleep(uint64_t Time);
KERNEL_IMPORT void sleepEx(uint8_t Interval, uint64_t Time);
KERNEL_IMPORT LOUSTATUS 
LouKeWaitForUlongRegisterCondition(
    PULONG  Mmio, 
    size_t  MsWait,
    ULONG   Mask, 
    ULONG   Value
);
#else 
#endif
#else





#define MilliSec 1
#define Sec 2
#ifndef _KERNEL_MODULE_
uint64_t GetCurrentTimeInMilliseconds();
void sleep(uint64_t Time);
void sleepEx(uint8_t Interval, uint64_t Time);
#endif
#endif
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TIME_T_
#define _TIME_T_
typedef struct _TIME_T{
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
    uint16_t MilliSeconds;
}TIME_T, * PTIME_T;
#endif

#ifndef _KERNEL_MODULE_
void LouKeGetTime(
    PTIME_T TimeStruct
);
bool LouKeDidTimeoutExpire(PTIME_T Timeout);
bool LouKeIsTimeoutNull(PTIME_T Timeout);
void LouKeGetRtcData(TIME_T* pTime);

#endif
#define PTIME_SEED T->MilliSeconds + (T->Second * 60) + (T->Minute * (60 * 60))
#define  TIME_SEED T.MilliSeconds + (T.Second * 60) + (T.Minute * (60 * 60))

#ifdef __cplusplus
}
#endif
