#include "awm.h"

LOUSTATUS AnnyaAwmProcessStartup(HANDLE Peb){

    int x = 0, y = 0, Width = 0, Height = 0;

    LOUSTATUS Status = DrsdGetCurrentScreenArea(
        &x, &y,
        &Width, &Height 
    );

    LouPrint("Hello Annya OS Window Manager\n");

    /*LouPrint("X     :%d\n", x);
    LouPrint("Y     :%d\n", y);
    LouPrint("Width :%d\n", Width);
    LouPrint("Height:%d\n", Height);

    for(SIZE Tx = 0; Tx < Width; Tx++){
        for(SIZE Ty = 0; Ty < Height; Ty++){
            DrsdPutPixelEx(Tx + x, Ty + y, SET_RGB(255, 255,255));
        }
    }

    DrsdSyncScreens();*/

    while(1);
    return STATUS_SUCCESS;
}