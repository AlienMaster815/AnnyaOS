#include "BootVid.h"

static PTTF_OBJECT TerminalFont = 0x00;
extern PFB_BOOT_RENDERER BootFbRenderers;
extern SIZE gFbCount;

static void BootVidScrollTerminal(PFB_BOOT_RENDERER Renderer){
    for(SIZE y = TERMINAL_INCY; y < Renderer->Height; y++){
        memcpy(&Renderer->Canvas[((y - TERMINAL_INCY) * (Renderer->Pitch / 4))], &Renderer->Canvas[(y * (Renderer->Pitch / 4))], Renderer->Width * sizeof(UINT32));
    }
    BootVidScrollTracking(Renderer);
}

void BootVidRegisterBootFont(
    PTTF_OBJECT TtfObject
){
    TerminalFont = TtfObject;
}

static void BootVidEndofData(){
    for(SIZE i = 0 ; i < gFbCount; i++){
        BootVidModifyTracking(BootFbRenderers[i].CurrentY, BootFbRenderers[i].CurrentX, &BootFbRenderers[i]);
        BootVidSyncScreenWithTracking(&BootFbRenderers[i]);
    }
}


static int BootVidPrintAsciiCharecter(CHAR AsciiCharecter){
    for(SIZE i = 0 ; i < gFbCount; i++){
        if((AsciiCharecter == '\n') || ((BootFbRenderers[i].CurrentX + (TerminalFont->AvgWidth * 3)) >= BootFbRenderers[i].Width)){
            if((BootFbRenderers[i].CurrentY + (TERMINAL_INCY * 3)) <= BootFbRenderers[i].Height){
                BootFbRenderers[i].CurrentY += TERMINAL_INCY;
                BootFbRenderers[i].CurrentX = 0;
                if((AsciiCharecter == '\n') || (AsciiCharecter == ' ')){
                    return 0x00;
                }
            }else{
                BootVidScrollTerminal(&BootFbRenderers[i]);
                BootFbRenderers[i].CurrentX = 0;
                if((AsciiCharecter == '\n') || (AsciiCharecter == ' ')){
                    return 0x00;
                }
            }
        }

        if(AsciiCharecter == ' '){
            BootFbRenderers[i].CurrentX += TerminalFont->AvgWidth;
            return 0x00;
        }

        if(!TerminalFont->AsciiGlyphData[(SIZE)AsciiCharecter]){
            return 0x00; 
        }
        PBOOTVID_BITMAP Bitmap = (PBOOTVID_BITMAP)TerminalFont->AsciiGlyphData[(SIZE)AsciiCharecter]->Bitmap;
        if(!Bitmap){
            return 0x00;
        }

        BootVidPlaceBitmap(Bitmap, BootFbRenderers[i].CurrentX, BootFbRenderers[i].CurrentY, &BootFbRenderers[i]);

        BootFbRenderers[i].CurrentX += TerminalFont->AvgWidth;

        BootVidModifyTracking(BootFbRenderers[i].CurrentY, BootFbRenderers[i].CurrentX, &BootFbRenderers[i]);
    }

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
    for(SIZE i = 0 ; i < gFbCount; i++){
        BootVidInitializeArtifactTracking(&BootFbRenderers[i]);
    }
    
    Status = LouKeRegisterEcsDriver(&BootVidEcsDriver);

    LouPrint("BootVidInitializeTerminalDriver() STATUS_SUCCESS\n");

    return Status;
}

void
BootVidDeInitializeTerminalDriver(){
    LouKeUnRegisterEcsDriver(&BootVidEcsDriver);
    for(SIZE i = 0 ; i < gFbCount; i++){
        BootRenderSetScreenColorEx(SET_RGB(0, 0, 0), &BootFbRenderers[i]);
        BootRenderSyncScreen(&BootFbRenderers[i]);
        LouKeFree((PVOID)BootFbRenderers[i].Canvas);
        LouKeFree((PVOID)BootFbRenderers[i].LineSystem);
    }
    TtfDeInitializeFile(TerminalFont);
    LouPrint("BOOTVID.SYS:Freeing Canvas Buffer\n");
    LouPrint("BOOTVID.SYS:Done Freeing Canvas Buffer\n");
}