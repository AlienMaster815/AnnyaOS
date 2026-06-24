#include "LouLoadPrivate.h"

static void HaltAndCatchFile() {
    for (;;) {
        asm ("hlt");
    }
}


LOUSTATUS LouLoadStartLoader(
    UINT64  LimineData
){


    HaltAndCatchFile();
    return (LOUSTATUS)~0;
}