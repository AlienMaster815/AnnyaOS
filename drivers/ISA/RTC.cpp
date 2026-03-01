#include <LouDDK.h>

LOUAPI
void UnSetInterruptFlags();
LOUAPI
void SetInterruptFlags();

void LouKeBcdToBinary(uint8_t* bcd_value){
    *bcd_value = (*bcd_value / 16 * 10) + (*bcd_value % 16);
}

static mutex_t RtcTex;

LOUAPI
void read_rtc() {
    MutexLock(&RtcTex);
    UNUSED uint8_t second, minute, hour, day, month, year;

    outb(0x70, 0x0A);
    while (inb(0x71) & 0x80) {
        sleep(5);  // Sleep for a short duration (e.g., 1 ms)
    }
    
    outb(0x70, 0x00);  // Seconds
    second = inb(0x71);
    outb(0x70, 0x02);  // Minutes
    minute = inb(0x71);
    outb(0x70, 0x04);  // Hours
    hour = inb(0x71);
    outb(0x70, 0x07);  // Day
    day = inb(0x71);
    outb(0x70, 0x08);  // Month
    month = inb(0x71);
    outb(0x70, 0x09);  // Year
    year = inb(0x71);

    // Optionally convert BCD to binary
    LouKeBcdToBinary(&second);
    LouKeBcdToBinary(&minute);
    LouKeBcdToBinary(&hour);
    LouKeBcdToBinary(&day);
    LouKeBcdToBinary(&month);
    LouKeBcdToBinary(&year);

    //LouPrint("Time:%d:%d\n", hour, minute);
    MutexUnlock(&RtcTex);
}
