#include <LouAPI.h>

void LouQWorkDemon(PVOID WorkQueue);

LOUSTATUS LouKeInitializeDefaultDemons(){
    LouPrint("LouKeInitializeDefaultDemons()\n");

    LouKeCreateDemon(
        LouQWorkDemon,
        0x00,
        16 * KILOBYTE
    );


    LouPrint("LouKeInitializeDefaultDemons() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}