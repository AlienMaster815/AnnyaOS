#include <LouAPI.h>

LOUSTATUS InitHPET();
uint64_t calibrate_tsc();

void SetTSCFrequency(uint64_t Frequency);
uint64_t GetTscMaster();
void SetTSC();

static inline uint64_t read_tsc(void) {
    uint32_t lo, hi;
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}



LOUSTATUS SetUpTimers() {
	LOUSTATUS Status = LOUSTATUS_GOOD;

	//Start With the Most Reliable And Work From There

	//if (LOUSTATUS_GOOD != InitHPET()) {
		//if no hpet use tsc
		//LouPrint("HPET Not Found Using TSC\n");
		
		uint64_t TSC_Ticks = 0;
		while(TSC_Ticks == 0){
		TSC_Ticks = calibrate_tsc();
		}
		LouPrint("TSC Ticks Are:%d\n",TSC_Ticks);

		SetTSCFrequency(TSC_Ticks);
		SetTSC();
	//}

	

	return Status;
}

uint64_t GetCurrentTimeInMilliseconds() {
    uint64_t current_tsc = read_tsc();
    uint64_t tsc_frequency = GetTscMaster();
    uint64_t timemilliseconds = (current_tsc * 1000) / tsc_frequency;
    return timemilliseconds;
}

uint64_t GetTscFromNowMilliseconds(uint64_t ms){
    uint64_t now = read_tsc();
    uint64_t tsc_frequency = GetTscMaster();
    uint64_t delta = (tsc_frequency * ms) / 1000;
    return now + delta;
}


int is_leap_year(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}


void LouKeGetTime(
    PTIME_T TimeStruct
){
    if (TimeStruct == NULL) {
        return; // Handle null pointer case
    }

    uint64_t TimeMS = GetCurrentTimeInMilliseconds();

    // Extract milliseconds
    TimeStruct->MilliSeconds = TimeMS % 1000;
    TimeMS /= 1000; // Convert to seconds

    // Calculate seconds, minutes, and hours
    TimeStruct->Second = TimeMS % 60;
    TimeMS /= 60; // Convert to minutes
    TimeStruct->Minute = TimeMS % 60;
    TimeMS /= 60; // Convert to hours
    TimeStruct->Hour = TimeMS % 24;
    TimeMS /= 24; // Convert to days

    // Calculate year, month, and day
    // Unix epoch time starts on January 1, 1970
    int days_since_epoch = (int)TimeMS;
    int year = 1970;

    // Calculate the year
    while (1) {
        int daysyear = is_leap_year(year) ? 366 : 365;
        if (days_since_epoch >= daysyear) {
            days_since_epoch -= daysyear;
            year++;
        } else {
            break;
        }
    }

    // Calculate the month and day
    int month = 0;
    int daysmonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysmonth_leap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dayscurrent_month = 0;
    while (1) {
        dayscurrent_month = is_leap_year(year) ? daysmonth_leap[month] : daysmonth[month];
        if (days_since_epoch >= dayscurrent_month) {
            days_since_epoch -= dayscurrent_month;
            month++;
        } else {
            break;
        }
    }

    TimeStruct->Month = month;
    TimeStruct->Day = dayscurrent_month;
}

void LouKeGetFutureTime(
    PTIME_T TimeStruct,
    size_t Ms
){
    if (TimeStruct == NULL) {
        return; // Handle null pointer case
    }

    uint64_t TimeMS = GetCurrentTimeInMilliseconds() + Ms;

    // Extract milliseconds
    TimeStruct->MilliSeconds = TimeMS % 1000;
    TimeMS /= 1000; // Convert to seconds

    // Calculate seconds, minutes, and hours
    TimeStruct->Second = TimeMS % 60;
    TimeMS /= 60; // Convert to minutes
    TimeStruct->Minute = TimeMS % 60;
    TimeMS /= 60; // Convert to hours
    TimeStruct->Hour = TimeMS % 24;
    TimeMS /= 24; // Convert to days

    // Calculate year, month, and day
    // Unix epoch time starts on January 1, 1970
    int days_since_epoch = (int)TimeMS;
    int year = 1970;

    // Calculate the year
    while (1) {
        int daysyear = is_leap_year(year) ? 366 : 365;
        if (days_since_epoch >= daysyear) {
            days_since_epoch -= daysyear;
            year++;
        } else {
            break;
        }
    }

    // Calculate the month and day
    int month = 0;
    int daysmonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysmonth_leap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dayscurrent_month = 0;
    while (1) {
        dayscurrent_month = is_leap_year(year) ? daysmonth_leap[month] : daysmonth[month];
        if (days_since_epoch >= dayscurrent_month) {
            days_since_epoch -= dayscurrent_month;
            month++;
        } else {
            break;
        }
    }

    TimeStruct->Month = month;
    TimeStruct->Day = dayscurrent_month;
}


bool LouKeDidTimeoutExpire(PTIME_T Timeout){
    TIME_T CurrentTime = {0}; 
    LouKeGetTime(&CurrentTime);

    return(
        (CurrentTime.Month >= Timeout->Month) && 
        (CurrentTime.Day >= Timeout->Day) && 
        (CurrentTime.Hour >= Timeout->Hour) && 
        (CurrentTime.Minute >= Timeout->Minute) && 
        (CurrentTime.Second >= Timeout->Second) &&
        (CurrentTime.MilliSeconds >= Timeout->MilliSeconds)
    );
}

bool LouKeIsTimeoutNull(PTIME_T Timeout){
    return(
        (0 == Timeout->Month) && 
        (0 == Timeout->Day) && 
        (0 == Timeout->Hour) && 
        (0 == Timeout->Minute) && 
        (0 == Timeout->Second) &&
        (0 == Timeout->MilliSeconds)
    );
}


uint8_t LouKeGetCurrentTimeMinute(){

    return 15;
}

uint64_t GetCurrentTimeIn100ns() {
    uint64_t current_tsc = read_tsc();
    uint64_t tsc_frequency = GetTscMaster(); // in Hz (ticks per second)
    return (current_tsc * 10000000ULL) / tsc_frequency;
}
