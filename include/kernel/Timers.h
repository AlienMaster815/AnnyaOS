#ifndef TIMERS_H
#define TIMERS_H

#ifdef __cplusplus

#else

#ifdef __x86_64__

typedef uint64_t    COUNTER;

void RunTimerClockMS(uint64_t TimerInMS);
void RunTimerClockS(uint64_t TimerInS);
void RunTimerClockS(uint64_t TimerInS);
void RunTimerClockHs(uint64_t TimerHS);

#endif

#endif

#endif
