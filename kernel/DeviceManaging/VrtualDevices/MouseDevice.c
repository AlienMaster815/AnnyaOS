#include <LouAPI.h>

void LouKeDrsdUnDrawMouse(
    uint16_t x, uint16_t y
);

static int32_t MouseXCursor = 0;
static int32_t MouseYCursor = 0;

UNUSED static const uint16_t Cursour[11] = {
    0b110000000000000,
    0b111000000000000,
    0b111100000000000,
    0b111110000000000,
    0b111111000000000,
    0b111111100000000,
    0b111111110000000,
    0b1111111111000000,
    0b000011100010000,
    0b000011100000000,
    0b000001110000000,
};

UNUSED static const uint16_t CursourRim[11] = {
    0b110000000000000,
    0b101000000000000,
    0b100100000000000,
    0b100010000000000,
    0b100001000000000,
    0b100000100000000,
    0b100001110000000,
    0b111101001000000,
    0b000010100000000,
    0b000010100000000,
    0b000001110000000,
};

static uint32_t MouseTmpData[8 * 11];

static inline void DrawMouse(uint16_t x, uint16_t y){
    PDrsdVRamObject FBDEV = LouKeDeviceManagerGetFBDEV(0);

    for(uint8_t yz = 0 ; yz < 11; yz++){
        uint16_t XData = Cursour[yz];
        uint16_t X2Data = CursourRim[yz];
        for(uint8_t xz = 0 ; xz < 8; xz++){
            if(((x + xz) < GetScreenBufferWidth()) && ((y + yz) < GetScreenBufferHeight())){
                MouseTmpData[xz + yz * 8] = *(uint32_t*)(GetFrameBufferAddress(FBDEV, x + xz,y + yz));
                if(XData & (1 << (15 - xz))){
                    LouKeDrsdPutPixelMirrored(x + xz, y + yz, 255,255,255);
                }
                if(X2Data & (1 << (15 - xz))){
                    LouKeDrsdPutPixelMirrored(x + xz, y + yz, 0,0,0);
                }
            }
        }
    }
}

static inline void UnDrawMouse(uint16_t x, uint16_t y){
    PDrsdVRamObject FBDEV = LouKeDeviceManagerGetFBDEV(0);
    for(uint8_t yz = 0 ; yz < 11; yz++){
        for(uint8_t xz = 0 ; xz < 8; xz++){
            if(((x + xz) < GetScreenBufferWidth()) && ((y + yz) < GetScreenBufferHeight())){
                *(uint32_t*)(GetFrameBufferAddress(FBDEV, x + xz,y + yz)) = MouseTmpData[xz + yz * 8]; 
            }
        }
    }
}

static bool FirstDraw = true;

void LouKeMouseMoveEventUpdate(int32_t X, int32_t Y){

    if(!FirstDraw){
        UnDrawMouse(MouseXCursor, MouseYCursor);    
    }else{
        FirstDraw = false;
    }

    MouseXCursor += X;

    if(MouseXCursor < 0){
        MouseXCursor = 0;
    }
    if(MouseXCursor >= GetScreenBufferWidth()){
        MouseXCursor = (GetScreenBufferWidth() - 1);
    }

    MouseYCursor += Y;

    if(MouseYCursor < 0){
        MouseYCursor = 0;
    }
    if(MouseYCursor >= GetScreenBufferHeight()){
        MouseYCursor = (GetScreenBufferHeight() - 1);
    }

    DrawMouse(MouseXCursor, MouseYCursor);
    //LouPrint("MouseX:%d :: MouseY:%d\n", MouseXCursor, MouseYCursor);
}


void LouKeMouseClickEventUpdate(bool Right, bool Left){

    

}