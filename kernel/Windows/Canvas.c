#include <LouAPI.h>


void LouChangeCanvasBufferColor(
    PWINDHANDLE WindHandle,
    uint8_t r,
    uint8_t g,
    uint8_t b
){
    DrawRectangle(
        WindHandle->CurrentX, 
        WindHandle->CurrentY, 
        WindHandle->CurrentWidth, 
        WindHandle->CurrentHeight,
        r,g,b
    );
}


PWINDHANDLE LouCreateCanvasBuffer(
    uint16_t x, uint16_t y,
    uint16_t width, uint16_t height,
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
){
    PWINDHANDLE WindHandle = LouKeMalloc(sizeof(WINDHANDLE), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);

    WindHandle->CurrentX = x;
    WindHandle->CurrentY = y;
    WindHandle->CurrentWidth = width;
    WindHandle->CurrentHeight = height;

    WindHandle->ParentWindow = ParentWindow;
    WindHandle->Charecteristics.Type = Charecteristics->Type;
    WindHandle->Charecteristics.Dimentions = Charecteristics->Dimentions;
    WindHandle->Charecteristics.WindowName = Charecteristics->WindowName;

    return WindHandle;
}