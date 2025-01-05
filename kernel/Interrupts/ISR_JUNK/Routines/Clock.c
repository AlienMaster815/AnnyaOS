
#include <LouAPI.h>
int LouPrintPanic(char* format, ...);

void UpdateThreadManager(uint64_t Rsp);

bool GetAPICStatus();

void ChangeBasePointer(uint64_t NewBase){

}
void ChangerStackPointer(uint64_t BasePointer){

}

void local_apic_send_eoi();


void Clock(uint64_t Rsp) {
	UpdateThreadManager(Rsp);
	return;// Rsp;
}