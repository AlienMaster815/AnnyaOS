#include <LouAPI.h>

#include <stdint.h>

#ifndef _TIME_T_
#define _TIME_T_
typedef struct _TIME_T {
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
    uint16_t MilliSeconds;
} TIME_T, *PTIME_T;
#endif

static inline uint8_t ReadRtcRegister(uint8_t reg) {
    outb(0x70, reg);    // Select RTC register
    return inb(0x71);   // Read its value
}

uint8_t BcdToBinary(uint8_t value) {
    return ((value >> 4) * 10) + (value & 0x0F);
}

void LouKeGetRtcData(TIME_T* pTime) {
    if (!pTime) return;  // Null check

    do {
        outb(0x70, 0x0A);
    } while (ReadRtcRegister(0x0A) & 0x80);

    pTime->Second = ReadRtcRegister(0x00);
    pTime->Minute = ReadRtcRegister(0x02);
    pTime->Hour   = ReadRtcRegister(0x04);
    pTime->Day    = ReadRtcRegister(0x07);
    pTime->Month  = ReadRtcRegister(0x08);

    pTime->MilliSeconds = 0;

    if (!(ReadRtcRegister(0x0B) & 0x04)) {
        pTime->Second = BcdToBinary(pTime->Second);
        pTime->Minute = BcdToBinary(pTime->Minute);
        pTime->Hour   = BcdToBinary(pTime->Hour);
        pTime->Day    = BcdToBinary(pTime->Day);
        pTime->Month  = BcdToBinary(pTime->Month);
    }    
}