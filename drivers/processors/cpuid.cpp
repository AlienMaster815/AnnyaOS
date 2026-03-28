//Copyright GPL-2 Tyler Grenier (2024 - 2026)
#include "Processors.h"

bool CPU::CPUID::IsFeatureSupported(FEATURE Feature){
       
    unsigned int eax, ebx, ecx, edx;

    cpuid(1, &eax, &ebx, &ecx, &edx);

    if(Feature == FPU){
        // Check if FPU (bit 0 of EDX) is present
        return edx & 0x1;
    }
    else if(Feature == SMP){
        // Check if SMP (bit 9 of EDX) is supported
        return edx & (1 << 9);
    }
    else if(Feature == MMX){
        // Check if MMX (bit 23 of EDX) is supported
        return edx & (1 << 23);
    }
    else if(Feature == SSE1){
        // Check if SSE (bit 25 of EDX) is supported
        return edx & (1 << 25);
    }
    else if(Feature == SSE2){
        // Check if SSE2 (bit 26 of EDX) is supported
        return edx & (1 << 26);
    }
    else if(Feature == SSE3){
        // Check if SSE3 (bit 0 of ECX) is supported
        return ecx & 0x1;
    }
    else if(Feature == SSE4A){
        // Execute extended CPUID leaf 0x80000001
        cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

        // Check if SSE4a (bit 6 of ECX) is supported
        return ecx & (1 << 6);
    }
    else if(Feature == SSE42){
        return ecx & 0x1;
    }
    else if(Feature == HYPERTHREAD){
        // Check if Hyper-Threading (bit 28 of EDX) is supported
        return edx & (1 << 28);
    }
    else if(Feature == X2APIC){
        if(edx & (1 << 21))return true;
        else return false;
    }
    else if(Feature == XAPIC){
        if(edx & (1 << 9))return true;
        else return false;
    }
    else if(Feature == APIC){
        if((edx & (1 << 9)) || (edx & (1 << 21)))return false;
        else return true;
    } 

    return false;

}

