#include "BootVid.h"

static PTTF_OBJECT TerminalFont = 0x00;
static int CurrentX = 0;
static int CurrentY = 0;
extern UINT32* Canvas;
extern INT32 Width;
extern INT32 Height;


#define TERMINAL_INCX(bWidth)   (bWidth + 2)
#define TERMINAL_INCY           (18)
#define TERMINAL_INCX_SPC       (12)

static void BootVidScrollTerminal(){
    for(SIZE y = TERMINAL_INCY; y < Height; y++){
        memcpy(&Canvas[((y - TERMINAL_INCY) * Width)], &Canvas[(y * Width)], Width * sizeof(UINT32));
    }
}

void BootVidRegisterBootFont(
    PTTF_OBJECT TtfObject
){
    TerminalFont = TtfObject;
}

static void BootVidEndofData(){
    BootRenderSyncScreen();
}


static int BootVidPrintAsciiCharecter(CHAR AsciiCharecter){

    if((AsciiCharecter == '\n') || ((CurrentX + (TERMINAL_INCX_SPC * 2)) > Width)){
        if((CurrentY + (TERMINAL_INCY * 2)) <= Height){
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
        CurrentX += TERMINAL_INCX_SPC;
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

void
BootVidDeInitializeTerminalDriver(){
    LouKeUnRegisterEcsDriver(&BootVidEcsDriver);
    BootRenderSetScreenColorEx(SET_RGB(0, 192, 192));
    BootRenderSyncScreen();
    TtfDeInitializeFile(TerminalFont);
    LouKeFree(Canvas);
}