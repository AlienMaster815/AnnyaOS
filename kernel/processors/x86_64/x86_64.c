#include <LouAPI.h>

// MSR register for TSC frequency
#define MSR_PLATFORM_INFO 0xCE
#define MSR_TSC 0x10

//Returns Speed In GHZ
long double GetProcessorSpeed() {
    uint64_t tsc_freq = LouKeReadMsr(MSR_TSC);

    // Convert to GHz
    return (long double)tsc_freq / 1e9;
}

uint32_t GetProcessorBusSpeed() {
    uint64_t platform_info = LouKeReadMsr(MSR_PLATFORM_INFO);
    uint32_t bus_freq = (platform_info >> 8) & 0xFF; // Extract bus frequency in MHz

    return bus_freq;
}

uint32_t NPROC = 0;

KERNEL_EXPORT uint32_t GetNPROC() {
    return NPROC ? NPROC : 1;
}

KERNEL_EXPORT void UpgradeNPROC(){
    NPROC++;
}

KERNEL_EXPORT void DowngradeNPROC(){
    NPROC--;
}

extern void init_fpu();



uint64_t GetGdtAsmTailCall(){
    return 0x00;
}

uint64_t GetIdtAsmTailCall(){
    return 0x00;
}

KERNEL_EXPORT UINT32 LouKeGetCurrentCpuPhysicalId(){
    unsigned int Eax, Ebx, Ecx, Edx;
    cpuid(1, &Eax, &Ebx, &Ecx, &Edx);
    BOOLEAN X2ApicSupported = (Ecx & (1 << 21)) ? true : false;
    if(X2ApicSupported){
        cpuid(0x0B, &Eax, &Ebx, &Ecx, &Edx);
        return Edx;
    }
    return (Ebx >> 24) & 0xFF;
}

//0x178BFBFF

