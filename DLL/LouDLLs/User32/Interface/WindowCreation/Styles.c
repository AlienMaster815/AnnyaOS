#include "WinCreation.h"

__declspec(dllimport)
void LouDrsdDrawLine32(
    PDRSD_CLIP Clip, 
    UINT32 X1, UINT32 Y1,
    UINT32 X2, UINT32 Y2, 
    UINT32 Color
);

__declspec(dllimport)
void LouDrsdPutPixel32(
    PDRSD_CLIP Clip,
    UINT32 X, UINT32 Y,
    UINT32 Color
);

extern PDRSD_CLIP* XButtonClips; 
//0,0, SCREEN_WIDTH, SCREEN_HEIGHT,

static void AwmDraw3dBorderRelative(
    PDRSD_CLIP  WindowClip,
    UINT32      RightBevel,
    UINT32      LeftBevel,
    UINT32      TopBevel,
    UINT32      BottomBevel,
    BOOL        Inwards
){

    //Draw Top
    LouDrsdDrawLine32(
        WindowClip,
        LeftBevel, TopBevel, (WindowClip->Width - 1) - RightBevel, TopBevel,
        Inwards == false ? DRSD_CORE_TRANSLATE_COLOR(255, 255, 255, 255) : DRSD_CORE_TRANSLATE_COLOR(0, 0, 0, 255)
    );

    //Draw Left
    LouDrsdDrawLine32(
        WindowClip,
        LeftBevel, TopBevel, LeftBevel, (WindowClip->Height - 1) - BottomBevel,
        Inwards == false ? DRSD_CORE_TRANSLATE_COLOR(255, 255, 255, 255) : DRSD_CORE_TRANSLATE_COLOR(0, 0, 0, 255)
    );

    //Draw Right
    LouDrsdDrawLine32(
        WindowClip,
        (WindowClip->Width - 1) - RightBevel, TopBevel, (WindowClip->Width - 1) - RightBevel, (WindowClip->Height - 1) - BottomBevel,
        Inwards == false ? DRSD_CORE_TRANSLATE_COLOR(0, 0, 0, 255) :  DRSD_CORE_TRANSLATE_COLOR(255, 255, 255, 255)
    );
    //Draw Right
    LouDrsdDrawLine32(
        WindowClip,
        (WindowClip->Width - 1) - RightBevel, TopBevel, (WindowClip->Width - 1) - RightBevel, (WindowClip->Height - 1) - BottomBevel,
        Inwards == false ? DRSD_CORE_TRANSLATE_COLOR(0, 0, 0, 255) :  DRSD_CORE_TRANSLATE_COLOR(255, 255, 255, 255)
    );    
    
    //Draw Bottom
    LouDrsdDrawLine32(
        WindowClip,
        LeftBevel, (WindowClip->Height - 1) - BottomBevel, (WindowClip->Width - 1) - RightBevel, (WindowClip->Height - 1) - BottomBevel,
        Inwards == false ? DRSD_CORE_TRANSLATE_COLOR(0, 0, 0, 255) :  DRSD_CORE_TRANSLATE_COLOR(255, 255, 255, 255)
    );

}

static void AwmDrawBorderRelative(
    PDRSD_CLIP  WindowClip,
    UINT32      RightBevel,
    UINT32      LeftBevel,
    UINT32      TopBevel,
    UINT32      BottomBevel,
    UINT8       R,
    UINT8       G, 
    UINT8       B,
    UINT8       A
){

    UINT32 Color = DRSD_CORE_TRANSLATE_COLOR(R, G, B, A);
    //Draw Top
    LouDrsdDrawLine32(
        WindowClip,
        LeftBevel, TopBevel, (WindowClip->Width - 1) - RightBevel, TopBevel,
        Color
    );

    //Draw Left
    LouDrsdDrawLine32(
        WindowClip,
        LeftBevel, TopBevel, LeftBevel, (WindowClip->Height - 1) - BottomBevel,
        Color
    );

    //Draw Right
    LouDrsdDrawLine32(
        WindowClip,
        (WindowClip->Width - 1) - RightBevel, TopBevel, (WindowClip->Width - 1) - RightBevel, (WindowClip->Height - 1) - BottomBevel,
        Color
    );
    //Draw Right
    LouDrsdDrawLine32(
        WindowClip,
        (WindowClip->Width - 1) - RightBevel, TopBevel, (WindowClip->Width - 1) - RightBevel, (WindowClip->Height - 1) - BottomBevel,
        Color
    );    
    
    //Draw Bottom
    LouDrsdDrawLine32(
        WindowClip,
        LeftBevel, (WindowClip->Height - 1) - BottomBevel, (WindowClip->Width - 1) - RightBevel, (WindowClip->Height - 1) - BottomBevel,
        Color
    );

}

static void AwmFillRectangleRelative(
    PDRSD_CLIP  WindowClip,
    UINT32      RightBevel,
    UINT32      LeftBevel,
    UINT32      TopBevel,
    UINT32      BottomBevel,
    UINT8       R,
    UINT8       G, 
    UINT8       B,
    UINT8       A
){
    UINT32 Color = DRSD_CORE_TRANSLATE_COLOR(R, G, B, A);

    UINT32 OriginX = LeftBevel;
    UINT32 OriginY = TopBevel;
    UINT32 Height = WindowClip->Height - BottomBevel;
    UINT32 Width = WindowClip->Width - RightBevel;

    for(UINT32 Y = OriginY; Y < Height; Y++){
        for(UINT32 X = OriginX; X < Width; X++){
            LouDrsdPutPixel32(WindowClip, X, Y, Color);
        }
    }
}

static void AwmFillRectangleDimentional(
    PDRSD_CLIP  WindowClip,
    UINT32 OriginX,
    UINT32 OriginY,
    UINT32 Width,
    UINT32 Height,
    UINT8 R,
    UINT8 G,
    UINT8 B,
    UINT8 A
){
    UINT32 Color = DRSD_CORE_TRANSLATE_COLOR(R, G, B, A);
    for(UINT32 Y = OriginY; Y < (OriginY + Height); Y++){
        for(UINT32 X = OriginX; X < (OriginX + Width); X++){
            LouDrsdPutPixel32(WindowClip, X, Y, Color);
        }
    }
}

void AwmDrawOverlappedWindow(
    PWINDOW_HANDLE WindowHandle
){
    size_t PlaneCount = WindowHandle->PlaneCount;
    for(size_t i = 0 ; i < PlaneCount; i++){
        //Draw 3d border
        AwmDraw3dBorderRelative(WindowHandle->MainWindow[i], 0, 0, 0, 0, false);
        if(WindowHandle->ExtendedWindowStyle & WS_EX_CLIENTEDGE){
            AwmDraw3dBorderRelative(WindowHandle->MainWindow[i], 11, 10, 47, 10, true);
        }else{
            AwmDrawBorderRelative(WindowHandle->MainWindow[i], 11, 10, 47, 10, 0, 0 , 0, 255);
        }
        AwmFillRectangleRelative(WindowHandle->MainWindow[i], 12, 11, 48, 11, 255, 255 , 255, 255);
        AwmFillRectangleDimentional(WindowHandle->MainWindow[i], 3, 3,  (WindowHandle->MainWindow[i]->Width - 5), 23, 0, 0 , 255, 255);
        //AwmFillRectangleDimentional(WindowHandle->MainWindow[i], (WindowHandle->MainWindow[i]->Width - (6 + 18)), 6,  18, 18, 192, 192 , 192, 255);
        LouDrsdClipToClip(WindowHandle->MainWindow[i], XButtonClips[i], (WindowHandle->MainWindow[i]->Width - (6 + 18)), 6);
        if(WindowHandle->WindowName){
            //PDRSD_CLIP WindowTitle = CreateClipFromString(WindowHandle->WindowName, AnnyaGetFont("C:/ANNYA/MJSSR.OTF"), 16, 16 ,WindowHandle->MainWindow[i], 6, 6);
    
        }
    }
}

void AwmInitializeWindowStyle(
    PWINDOW_HANDLE  Window,
    DWORD           ExStyle, 
    DWORD           Style
){
    AwmDrawOverlappedWindow(Window);


}