#ifndef TIME_H
#define TIME_H
#ifdef __x86_64__
#ifdef __cplusplus

#define MilliSec 1
#define Sec 2

#include <LouDDK.h>



#ifndef _KERNEL_MODULE_
LOUDDK_API_ENTRY uint64_t GetCurrentTimeInMilliseconds();
KERNEL_EXPORT void sleep(uint64_t Time);
LOUDDK_API_ENTRY void sleepEx(uint8_t Interval, uint64_t Time);
LOUDDK_API_ENTRY LOUSTATUS 
LouKeWaitForUlongRegisterCondition(
    PULONG  Mmio, 
    size_t  MsWait,
    ULONG   Mask, 
    ULONG   Value
);
LOUDDK_API_ENTRY void LouKeThreadSleep(size_t Ms);
LOUDDK_API_ENTRY uint64_t GetTscFromNowMilliseconds(uint64_t ms);
#else 
#endif
#else





#define MilliSec 1
#define Sec 2
#ifndef _KERNEL_MODULE_
uint64_t GetCurrentTimeInMilliseconds();
KERNEL_EXPORT void sleep(uint64_t Time);
void sleepEx(uint8_t Interval, uint64_t Time);
void LouKeThreadSleep(size_t Ms);
uint64_t GetTscFromNowMilliseconds(uint64_t ms);
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
void LouKeGetFutureTime(
    PTIME_T TimeStruct,
    size_t Ms
);
#endif
#define PTIME_SEED T->MilliSeconds + (T->Second * 60) + (T->Minute * (60 * 60))
#define  TIME_SEED T.MilliSeconds + (T.Second * 60) + (T.Minute * (60 * 60))

#ifdef __cplusplus
}
#endif
