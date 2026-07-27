#include "awm.h"

LOUSTATUS AnnyaAwmProcessStartup(HANDLE Peb){

    int x = 0, y = 0, Width = 0, Height = 0;

    LOUSTATUS Status = InternalDrsdGetCurrentScreenArea(
        &x, &y,
        &Width, &Height 
    );

    LouPrint("Hello Annya OS Window Manager\n");

    LouPrint("X     :%d\n", x);
    LouPrint("Y     :%d\n", y);
    LouPrint("Width :%d\n", Width);
    LouPrint("Height:%d\n", Height);

    HANDLE BackgroundFbContext = InternalDrsdCreateFbContext(
        x, y,
        Width, Height,
        4
    );

    //for(SIZE Tx = 0; Tx < Width; Tx++){
    //    for(SIZE Ty = 0; Ty < Height; Ty++){
    //        InternalDrsdPutPixelEx(Tx + x, Ty + y, SET_RGB(0, 0xC0, 0xC0));
    //    }
    //}

    InternalDrsdFillColorEx(
        BackgroundFbContext,
        0,0,0,0,
        SET_RGB(0, 0xC0, 0xC0)
    );


    InternalDrsdDeployContext(
        BackgroundFbContext
    );
    
    while(1);
    return STATUS_SUCCESS;
}