#include <LouAPI.h>

static inline 
uint16_t GetCodeSegment(){
    uint16_t cs;
    asm("mov %%cs, %0" : "=r" (cs));
    return cs;
}

OperatingMode LouKeCheckOperatingMode(){

    uint16_t cs = GetCodeSegment();

    //LouPrint("Cs Is:%h\n", cs);

    if(cs == 0x08){
        LouPrint("Lousine Kernel Is Requesting Somthing\n");
        return Kernel;
    }
    else if(cs == 0x38){
        LouPrint("A Interrupt Event Is Requesting Somthing\n");
        return System;
    }
    else if(cs == 0x18){
        LouPrint("User Mode Is Requesting Somthing\n");
        return User;
    }
    else if((cs == 0x48) || (cs == 0x28)){
        LouPrint("A System Event Is Requesting Somthing\n");
        return System;
    }

    //this will never execute but just god forbid we will get the 
    //antivirus version of the requesting service for safety
    return LousineInternalAntivirus;

}

void LouKeInitializeSecuritySubsystem(){
 
    LouKeCreateFastObjectClass(
        "LOUSINE_ACCESS_TOKEN",
        512,
        sizeof(LOUSINE_ACCESS_TOKEN),
        GET_ALIGNMENT(LOUSINE_ACCESS_TOKEN),
        0,
        KERNEL_GENERIC_MEMORY
    );

}