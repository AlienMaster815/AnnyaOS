#include "BootVid.h"

static PTTF_OBJECT TerminalFont = 0x00;

void BootVidRegisterBootFont(
    PTTF_OBJECT TtfObject
){
    TerminalFont = TtfObject;
}

static int BootVidPrintAsciiCharecter(CHAR AsciiCharecter){
    //BootVidPlaceBitmap((PBOOTVID_BITMAP)TerminalFont->AsciiGlyphData['A']->Bitmap, 0, 0);

    

}
    
static int BootVidPrintUnicodeCharecter(UINT32 Charecter){

}

static void BootVidEndofData(){
    BootRenderSyncScreen();
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