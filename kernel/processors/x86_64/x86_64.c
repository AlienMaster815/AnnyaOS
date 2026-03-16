#include <LouAPI.h>

// MSR register for TSC frequency
#define MSR_PLATFORM_INFO 0xCE
#define MSR_TSC 0x10

//Returns Speed In GHZ
long double GetProcessorSpeed() {
    uint64_t tsc_freq = read_msr(MSR_TSC);

    // Convert to GHz
    return (long double)tsc_freq / 1e9;
}

uint32_t GetProcessorBusSpeed() {
    uint64_t platform_info = read_msr(MSR_PLATFORM_INFO);
    uint32_t bus_freq = (platform_info >> 8) & 0xFF; // Extract bus frequency in MHz

    return bus_freq;
}

uint16_t NPROC = 0;

uint16_t GetNPROC() {
    return NPROC ? NPROC : 1;
}

void UpgradeNPROC(){
    NPROC++;
}

void DowngradeNPROC(){
    NPROC--;
}

extern void init_fpu();



uint64_t GetGdtAsmTailCall(){
    return 0x00;
}

uint64_t GetIdtAsmTailCall(){
    return 0x00;
}



//0x178BFBFF

