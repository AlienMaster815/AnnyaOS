#include <LouAPI.h>

void RunTimerClockMS(uint64_t TimerInMS);

bool GetAPICStatus();


bool HPET = false;

void SetHPET(bool Set) {
	HPET = Set;
}
bool SleepHPET(uint64_t Milliseconds) {
	return true;
}

bool PIT = false;
void SetPIT(bool Set) {
	HPET = Set;
}
bool SleepPIT(uint64_t Milliseconds) {
	return true;
}

void busy_wait_TSC(uint32_t milliseconds);

bool TSC = false;
void SetTSC() {
	TSC = true;
}
bool SleepTSC(uint64_t Milliseconds) {
	busy_wait_TSC(Milliseconds);
	return true;
}

void sleep(uint64_t Time) {
	if (HPET) {
		SleepHPET(Time);
	}
	else if (PIT) {
		SleepPIT(Time);
	}
	else if (TSC) {
		busy_wait_TSC(Time);
	}
	else if (GetAPICStatus()) {

	}
	else {
		RunTimerClockMS(Time);
	}
}
void sleepEx(uint8_t Interval, uint64_t Time) {

}