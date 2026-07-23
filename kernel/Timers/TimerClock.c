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

uint64_t GetTscMaster();
uint64_t read_tsc(void);

void RunTimerClockMS(uint64_t TimerInMS){
    UINT64 CurrentTSC = read_tsc();
    UINT64 TscFrequency = GetTscMaster() / 1000;
    UINT64 Expiration = CurrentTSC + (TimerInMS * TscFrequency);
    while(read_tsc() <= Expiration);
}

void RunTimerClockS(uint64_t TimerInS){
    RunTimerClockMS(TimerInS * 1000);
}
