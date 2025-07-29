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

static void AwmDraw3dBorder(
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

static void AwmDrawBorder(
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
    for(UINT32 Y = OriginY; Y < Height; Y++){
        for(UINT32 X = OriginX; X < Width; X++){
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
        AwmDraw3dBorder(WindowHandle->MainWindow[i], 0, 0, 0, 0, false);
        if(WindowHandle->ExtendedWindowStyle & WS_EX_CLIENTEDGE){
            AwmDraw3dBorder(WindowHandle->MainWindow[i], 9, 8, 32, 8, true);
        }else{
            AwmDrawBorder(WindowHandle->MainWindow[i], 9, 8, 32, 8, 0, 0 , 0, 255);
        }
        AwmFillRectangleRelative(WindowHandle->MainWindow[i], 10, 9, 33, 9, 255, 255 , 255, 255);
        AwmFillRectangleDimentional(WindowHandle->MainWindow[i], 2, 2,  (WindowHandle->MainWindow[i]->Width - 2), 14, 0, 0 , 255, 255);
    }
}

void AwmInitializeWindowStyle(
    PWINDOW_HANDLE  Window,
    DWORD           ExStyle, 
    DWORD           Style
){
    AwmDrawOverlappedWindow(Window);


}