#include "BootVid.h"

static PTTF_OBJECT TerminalFont = 0x00;
static int CurrentX = 0;
static int CurrentY = 0;
extern UINT32* Canvas;
extern INT32 Width;
extern INT32 Height;


static void BootVidScrollTerminal(){
    for(SIZE y = TERMINAL_INCY; y < Height; y++){
        memcpy(&Canvas[((y - TERMINAL_INCY) * Width)], &Canvas[(y * Width)], Width * sizeof(UINT32));
    }
    BootVidScrollTracking();
}

void BootVidRegisterBootFont(
    PTTF_OBJECT TtfObject
){
    TerminalFont = TtfObject;
}

static void BootVidEndofData(){
    BootVidModifyTracking(CurrentY, CurrentX);
    BootVidSyncScreenWithTracking();
}


static int BootVidPrintAsciiCharecter(CHAR AsciiCharecter){
    if((AsciiCharecter == '\n') || ((CurrentX + (TerminalFont->AvgWidth * 3)) >= Width)){
        if((CurrentY + (TERMINAL_INCY * 3)) <= Height){
            CurrentY += TERMINAL_INCY;
            CurrentX = 0;
            if((AsciiCharecter == '\n') || (AsciiCharecter == ' ')){
                return 0x00;
            }
        }else{
            BootVidScrollTerminal();
            CurrentX = 0;
            if((AsciiCharecter == '\n') || (AsciiCharecter == ' ')){
                return 0x00;
            }
        }
    }

    if(AsciiCharecter == ' '){
        CurrentX += TerminalFont->AvgWidth;
        return 0x00;
    }

    if(!TerminalFont->AsciiGlyphData[(SIZE)AsciiCharecter]){
        return 0x00; 
    }
    PBOOTVID_BITMAP Bitmap = (PBOOTVID_BITMAP)TerminalFont->AsciiGlyphData[(SIZE)AsciiCharecter]->Bitmap;
    if(!Bitmap){
        return 0x00;
    }

    BootVidPlaceBitmap(Bitmap, CurrentX, CurrentY);
    
    CurrentX += TerminalFont->AvgWidth;

    BootVidModifyTracking(CurrentY, CurrentX);

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
    
    BootVidInitializeArtifactTracking();

    Status = LouKeRegisterEcsDriver(&BootVidEcsDriver);

    return Status;
}

void
BootVidDeInitializeTerminalDriver(){
    LouKeUnRegisterEcsDriver(&BootVidEcsDriver);
    BootRenderSetScreenColorEx(SET_RGB(0, 0, 0));
    BootRenderSyncScreen();
    TtfDeInitializeFile(TerminalFont);
    LouPrint("BOOTVID.SYS:Freeing Canvas Buffer\n");
    LouKeFree((PVOID)Canvas);
    LouPrint("BOOTVID.SYS:Done Freeing Canvas Buffer\n");
}