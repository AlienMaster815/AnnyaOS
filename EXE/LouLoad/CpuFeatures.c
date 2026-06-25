#include "LouLoadPrivate.h"

uint64_t read_msr(uint32_t msr_id) {
    uint32_t low, high;
    __asm__ __volatile__("rdmsr"
                         : "=a"(low), "=d"(high)
                         : "c"(msr_id));
    return ((uint64_t)high << 32) | low;
}

void write_msr(uint32_t msr, uint64_t value) {
    uint32_t low = (uint32_t)(value & 0xFFFFFFFF);
    uint32_t high = (uint32_t)(value >> 32);
    __asm__ __volatile__("wrmsr"
                         :
                         : "c"(msr), "a"(low), "d"(high));
}

void cpuid(unsigned int code, unsigned int* eax, unsigned int* ebx, unsigned int* ecx, unsigned int* edx) {
    asm volatile("cpuid"
        : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
        : "a" (code));
}

void cpuid_subleaf(unsigned int leaf, unsigned int subleaf, 
                                 unsigned int *eax, unsigned int *ebx, 
                                 unsigned int *ecx, unsigned int *edx){
    __asm__ __volatile__(
        "cpuid"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
        : "a"(leaf), "c"(subleaf)
    );
}

static BOOLEAN IsGiganticPagesSupported(){
    unsigned int Eax = 0, Ebx = 0, Ecx = 0, Edx = 0;

    cpuid(0x80000000, &Eax, &Ebx, &Ecx, &Edx);
    if(Eax < 0x80000001){
        return false;
    }

    cpuid(0x80000001, &Eax, &Ebx, &Ecx, &Edx);

    return Edx & (1 << 26) ? true : false;
}

static BOOLEAN IsNxSupported(){
    unsigned int Eax = 0, Ebx = 0, Ecx = 0, Edx = 0;

    cpuid(0x80000000, &Eax, &Ebx, &Ecx, &Edx);
    if(Eax < 0x80000001){
        return false;
    }

    cpuid(0x80000001, &Eax, &Ebx, &Ecx, &Edx);

    return Edx & (1 << 11) ? true : false;
}

void LoaderGetCpuFeatures(PLOADER_INFORMATION Info){

    Info->LoaderCpuFeatures = 0;
    Info->LoaderCpuFeatures |= IsGiganticPagesSupported() ? LOADER_CPU_FEATURES_GB_PAGES : 0;
    Info->LoaderCpuFeatures |= IsNxSupported() ? LOADER_CPU_FEATURES_NX : 0; 


    if(Info->LoaderCpuFeatures & LOADER_CPU_FEATURES_NX){
        uint64_t MsrData = read_msr(0xC0000080);
        MsrData |= (1ULL << 11);
        write_msr(0xC0000080, MsrData);
    }

}