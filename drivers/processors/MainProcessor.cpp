#include <LouDDK.h>
#include <NtAPI.h>

#include "Processors.h"



KERNEL_IMPORT void InitializeFloatPointUnit();

LOUDDK_API_ENTRY void SMPInit();

LOUSTATUS EnableAdvancedBspFeatures(CPU::FEATURE Feature){
    LOUSTATUS Status = LOUSTATUS_GOOD;

    LouPrint("Enableing Advanced Processor Features For Bootstrap Processor\n");

    CPU::CPUID cpu;

        //Initialize FPU
        if(Feature == CPU::FPU){
            if(cpu.IsFeatureSupported(CPU::FPU)){
                LouPrint("Setting Up FPU\n");
                InitializeFloatPointUnit();
                // Perform a simple floating-point addition
                float value1 = 10.5;
                float value2 = 5.5;
                float result = value1 + value2;
                if(result == 16)LouPrint("FPU Set Up\n");
            }
        }

    cpu.~CPUID();

    //while(1);
    return Status;
}
