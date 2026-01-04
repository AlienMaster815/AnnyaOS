#include <LouAPI.h>

UNUSED static uint8_t vendor = 0;
UNUSED static uint8_t Processor = 0;
UNUSED static uint8_t CoreVersion = 0;
UNUSED static uint64_t CoreGeneration = 0;
UNUSED static double Speed = 0.0;

uint8_t GetCPUVendor() {
    return vendor;
}

uint8_t GetProcessor(){
    return Processor;
}

uint8_t GetCPUCoreVersion() {
    return CoreVersion;
}

uint64_t GetCPUCoreGeneration() {
    return CoreGeneration;
}

string GetVenString(){
    
    unsigned int eax, ebx, ecx, edx;
    string brand = LouGeneralAllocateMemoryEx(49, 1); // Enough space for the 48-character brand string + null terminator

    LouPrint("Detecting CPU\n");

    // Initial CPUID call
    cpuid(1, &eax, &ebx, &ecx, &edx);

    UNUSED unsigned int family = (eax >> 8) & 0xF;
    UNUSED unsigned int model = (eax >> 4) & 0xF;
    UNUSED unsigned int stepping = eax & 0xF;

    //LouPrint("Family: %d\nModel: %d\nStepping: %d\n", family, model, stepping);

    // Check highest function supported
    cpuid(0x80000000, &eax, &ebx, &ecx, &edx);

    if (eax >= 0x80000004) {
        // Retrieve and assemble the processor brand string
        unsigned int* brand_part = (unsigned int*)brand;
        for (unsigned int i = 0; i < 3; ++i) {
            cpuid(0x80000002 + i, &eax, &ebx, &ecx, &edx);
            brand_part[i * 4 + 0] = eax;
            brand_part[i * 4 + 1] = ebx;
            brand_part[i * 4 + 2] = ecx;
            brand_part[i * 4 + 3] = edx;
        }
        brand[48] = '\0'; // Ensure null-termination

        // Print the full brand string
        LouPrint("Processor Brand: %s\n", brand);
    }




    string VenCheck = brand;
    CPUFullString = VenCheck;
    return CPUFullString;
}


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

extern void enable_sse();

void InitializeFloatPointUnit(){
    enable_sse();
}

uint64_t GetGdtAsmTailCall(){
    return 0x00;
}

uint64_t GetIdtAsmTailCall(){
    return 0x00;
}



//0x178BFBFF

