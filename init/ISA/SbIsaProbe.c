#include <drivers/SbIsa.h>

void LouKeProbeSbIsa(){
    LouKeSbIsaWriteReset(1);
    sleep(1);
    LouKeSbIsaWriteReset(0);
    UINT8 SbCheck = LouKeSbIsaReadDsp();
    if(SbCheck == SBISA_FOUND_DEVICE){
        LouPrint("Found ISA SoundBlaster 16\n");
        LOUSTATUS (*SbModAddIsa)() = (LOUSTATUS (*)())LouKeLoadDriver("SBMOD.SYS","LouKeAddSbIsaDevice");
        if(SbModAddIsa){
            SbModAddIsa();
        }
    }
    //while(1);
}