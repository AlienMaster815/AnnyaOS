#ifndef _CLOCKS_H
#define _CLOCKS_H
#ifdef __cplusplus
extern "C" {
#endif

#define TIMERCLOCK_1000HZ 1000
#define TIMERCLOCK_500HZ 500
#define TIMERCLOCK_1HZ 1

#include <cstdint.h>

#ifndef _USER_MODE_CODE_
void ChangeTimerClock(uint64_t SPEED);
#endif

#ifdef __cplusplus
}
#endif
#endif
