/*
-- Tyler Grenier 11/25/23 3:19 PM
-- This File Will Hold the information for interacting with clock
-- interrupts through a timed interface i am going to set this up
-- so that the system can work less and that will save more energy
-- but it will be more work for me because i will have to minipulate
-- clocks in the board to go at certain clock speeds such as clocks
-- at 1000 hz for milliseconds and 1hz for seconds and minipulate the
-- clocks to make this as power efficient as posible
*/

#include <LouAPI.h>

#ifdef __i386__
void WaitForInterrupt();
#endif

void RegisterForClockInterrupt(){
    Mask_All_Programable_Interrupts();
    IRQ_Pic_clear_mask(0);
    IRQ_Pic_clear_mask(1);
}

void RunTimerClockMS(uint64_t TimerInMS){
    uint64_t Time = GetCurrentTimeInMilliseconds() + TimerInMS;
    uint64_t Spin = 0;
    while(Time > Spin){
        Spin = GetCurrentTimeInMilliseconds();
    }
}

void RunTimerClockS(uint64_t TimerInS){
    RunTimerClockMS(TimerInS * 1000);
}
