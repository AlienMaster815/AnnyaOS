#include "awm.h"


LOUSTATUS AnnyaAwmProcessStartup(HANDLE Peb){

    int x = 0, y = 0, Width = 0, Height = 0;

    LOUSTATUS Status = DrsdGetCurrentScreenArea(
        &x, &y,
        &Width, &Height 
    );

    LouPrint("Hello AnnyaOS Window Manager\n");

    LouPrint("X:%h\n", x);
    LouPrint("Y:%h\n", y);
    LouPrint("Width:%h\n", Width);
    LouPrint("Height:%h\n", Height);

    while(1);
    return STATUS_SUCCESS;
}