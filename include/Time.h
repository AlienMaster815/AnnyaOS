#ifndef TIME_H
#define TIME_H
#ifdef __cplusplus
extern "C" {
#endif


#include <Modulation.h>
#include <cstdint.h>
#include <cstdio.h>

typedef struct _TIME_T{
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
    uint16_t MilliSeconds;
}TIME_T, * PTIME_T;

#define PTIME_SEED T->MilliSeconds + (T->Second * 60) + (T->Minute * (60 * 60))
#define  TIME_SEED T.MilliSeconds + (T.Second * 60) + (T.Minute * (60 * 60))

#ifndef _USER_MODE_CODE_
uint64_t GetCurrentTimeInMilliseconds();
KERNEL_EXPORT void sleep(uint64_t Time);
void sleepEx(uint8_t Interval, uint64_t Time);
void LouKeThreadSleep(size_t Ms);
uint64_t GetTscFromNowMilliseconds(uint64_t ms);
bool LouKeDidTimeoutExpire(PTIME_T Timeout);
bool LouKeIsTimeoutNull(PTIME_T Timeout);
void LouKeGetRtcData(TIME_T* pTime);
void LouKeGetFutureTime(
    PTIME_T TimeStruct,
    size_t Ms
);
void LouKeGetTime(
    PTIME_T TimeStruct
);
#endif
#ifdef __cplusplus
}
#endif
#endif