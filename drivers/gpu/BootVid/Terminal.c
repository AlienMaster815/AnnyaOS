#include "BootVid.h"

static PTTF_OBJECT TerminalFont = 0x00;
static int CurrentX = 0;
static int CurrentY = 0;
extern UINT32* Canvas;
extern INT32 Width;
extern INT32 Height;

#define TERMINAL_INCX(bWidth)   (bWidth + 2)
#define TERMINAL_INCY(bHeight)  (bHeight + 2)

void BootVidRegisterBootFont(
    PTTF_OBJECT TtfObject
){
    TerminalFont = TtfObject;
}

static void BootVidEndofData(){
    BootRenderSyncScreen();
}


static int BootVidPrintAsciiCharecter(CHAR AsciiCharecter){
    if(!TerminalFont->AsciiGlyphData[(SIZE)AsciiCharecter]){
        return 0x00; 
    }
    PBOOTVID_BITMAP Bitmap = (PBOOTVID_BITMAP)TerminalFont->AsciiGlyphData[(SIZE)AsciiCharecter]->Bitmap;
    if(!Bitmap){
        return 0x00;
    }
    if((CurrentX + TERMINAL_INCX(Bitmap->Width)) >= Width){
        return 0x00;
    //    while(1);
    }

    BootVidPlaceBitmap(Bitmap, CurrentX, CurrentY);
    
    CurrentX += TERMINAL_INCX(Bitmap->Width);
    
    return 0x00;
}
    
static int BootVidPrintUnicodeCharecter(UINT32 Charecter){

    return 0x00;
}


static LOUSINE_ECS_DRIVER BootVidEcsDriver = {
    .DriverName = "BOOTVIS-ECS",
    .ModuleName = "BOOTVID.SYS",
    .EcsOperations = {
        .PrintAsciiCharecter = BootVidPrintAsciiCharecter,
        .PrintUnicodeCharecter = BootVidPrintUnicodeCharecter,
        .EndofData = BootVidEndofData,
    },
};

LOUSTATUS 
BootVidInitializeTerminalDriver(){
    LOUSTATUS Status;
    


    Status = LouKeRegisterEcsDriver(&BootVidEcsDriver);

    return Status;
}