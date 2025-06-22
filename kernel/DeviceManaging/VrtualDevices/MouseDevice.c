#include <LouAPI.h>

void LouKeDrsdUnDrawMouse(
    uint16_t x, uint16_t y
);

static int32_t MouseXCursor = 0;
static int32_t MouseYCursor = 0;

static int32_t LastMouseXCursor = 0;
static int32_t LastMouseYCursor = 0;

UNUSED static const uint16_t Cursour[19] = {
    0b100000000000000,
    0b110000000000000,
    0b111000000000000,
    0b111100000000000,
    0b111110000000000,
    0b111111000000000,
    0b111111100000000,
    0b111111110000000,
    0b111111111000000,
    0b111111111100000,
    0b111111111110000,
    0b111111111111000,
    0b111011110000000,
    0b110011110000000,
    0b100001111000000,
    0b000001111000000,
    0b000000111100000,
    0b000000111100000,
    0b000000011000000,
};

UNUSED static const uint16_t CursourRim[19] = {
    0b100000000000000,
    0b110000000000000,
    0b101000000000000,
    0b100100000000000,
    0b100010000000000,
    0b100001000000000,
    0b100000100000000,
    0b100000010000000,
    0b100000001000000,
    0b100000000100000,
    0b100000000010000,
    0b100100011111000,
    0b101010010000000,
    0b110010010000000,
    0b100001001000000,
    0b000001001000000,
    0b000000100100000,
    0b000000100100000,
    0b000000011000000,
};

static uint32_t MouseTmpData[12 * 19];

static inline void DrawMouse(uint16_t x, uint16_t y){
    PDrsdVRamObject FBDEV = LouKeDeviceManagerGetFBDEV(0);
    for(uint8_t yz = 0 ; yz < 19; yz++){
        uint16_t XData = Cursour[yz];
        uint16_t X2Data = CursourRim[yz];
        for(uint8_t xz = 0 ; xz < 12; xz++){
            if(((x + xz) < GetScreenBufferWidth()) && ((y + yz) < GetScreenBufferHeight())){
                MouseTmpData[xz + yz * 12] = *(uint32_t*)(GetFrameBufferAddress(FBDEV, x + xz,y + yz));
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
    for(uint8_t yz = 0 ; yz < 19; yz++){
        for(uint8_t xz = 0 ; xz < 12; xz++){
            if(((x + xz) < GetScreenBufferWidth()) && ((y + yz) < GetScreenBufferHeight())){
                *(uint32_t*)(GetFrameBufferAddress(FBDEV, x + xz,y + yz)) = MouseTmpData[xz + yz * 12]; 
            }
        }
    }
}

static bool FirstDraw = true;

void LouKeMouseMoveEventUpdate(int32_t X, int32_t Y){
    
    MouseXCursor += X;

    if(MouseXCursor < 0){
        //MouseXCursor = 0;
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

}


void LouKeMouseClickEventUpdate(bool Right, bool Left){

}

void MouseDrawWork(uint64_t NullDataDontUse){
    if(!FirstDraw){
        UnDrawMouse(LastMouseXCursor, LastMouseYCursor);    
    }else{
        FirstDraw = false;
    }
    LastMouseXCursor = MouseXCursor;
    LastMouseYCursor = MouseYCursor;
    DrawMouse(MouseXCursor, MouseYCursor);
    LouKeDrsdSyncScreens();
}

void LouKeInitializeMouseManagemet(){
 
    LouKeInitializeIntervalWork(
        MouseDrawWork,
        0x00,
        16
    );
    LouPrint("Here\n");
}