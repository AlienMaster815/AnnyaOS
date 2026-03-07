#ifndef TIME_H
#define TIME_H
#ifdef __cplusplus
extern "C" {
#endif


#include <Modulation.h>
#include <cstdint.h>
#include <cstdio.h>

typedef struct _FILETIME{
    union{
        struct{
            UINT32      LowDateTime;
            UINT32      HighDateTime;
        };
        UINT64          DateTime;
    };
}FILETIME, * PFILETIME, * LPFILETIME;


typedef struct _TIME_T{
    UINT32      Year;
    UINT8       Month;
    UINT8       Day;
    UINT8       Hour;
    UINT8       Minute;
    UINT8       Second;
    UINT16      MilliSeconds;
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