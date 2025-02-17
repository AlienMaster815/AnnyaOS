#include <LouAPI.h>

uint64_t OpenWindows = 0;

typedef struct _OPEN_WINDOW_LIST{
    ListHeader Neighbors;
    PWINDHANDLE WindowHandle;
}OPEN_WINDOW_LIST, * POPEN_WINDOW_LIST;

OPEN_WINDOW_LIST MasterWindowList;

static spinlock_t WindowHandleLock;

static inline PWINDHANDLE CreateWindowHandle(){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&WindowHandleLock, &Irql);
    POPEN_WINDOW_LIST TmpList = &MasterWindowList;
    for(uint64_t i = 0 ; i < OpenWindows; i++){
        if(TmpList->Neighbors.NextHeader){
            TmpList = (POPEN_WINDOW_LIST)TmpList->Neighbors.NextHeader;
        }
    }
    OpenWindows++;

    TmpList->Neighbors.NextHeader = (PListHeader)LouMalloc(sizeof(OPEN_WINDOW_LIST));
    TmpList = (POPEN_WINDOW_LIST)TmpList->Neighbors.NextHeader;
    TmpList->WindowHandle = LouKeMalloc(sizeof(WINDHANDLE), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
    LouKeReleaseSpinLock(&WindowHandleLock, &Irql);
    
    return TmpList->WindowHandle;
}

static inline void DestroyWindowHandle(
    PWINDHANDLE WindowToDestroy
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&WindowHandleLock, &Irql);
    POPEN_WINDOW_LIST TmpList = &MasterWindowList;
    for(uint64_t i = 0 ; i < OpenWindows; i++){
        TmpList = (POPEN_WINDOW_LIST)TmpList->Neighbors.NextHeader;
        if(TmpList->WindowHandle == WindowToDestroy){
            POPEN_WINDOW_LIST TmpList2 = &MasterWindowList;
            for(uint64_t j = 0 ; j < i; j++){
                TmpList2 = (POPEN_WINDOW_LIST)TmpList->Neighbors.NextHeader;
            }
            TmpList2->Neighbors.NextHeader = TmpList->Neighbors.NextHeader;  
            OpenWindows--;
            LouFree((RAMADD)TmpList->WindowHandle);
            LouKeReleaseSpinLock(&WindowHandleLock, &Irql);
            return;
       }
    }
    LouKeReleaseSpinLock(&WindowHandleLock, &Irql);
}

void LouKeDrsdHandleWindowUpdate(
    PWINDHANDLE WindowHandles,
    uint16_t x,
    uint16_t y,
    uint16_t Width,
    uint16_t Height
);

void LouKeDrsdDrawDesktopBackground(
    FILE* ImageFile,
    uint16_t DrsdFileType
);

PWINDHANDLE 
GetWindowHandleByNumber(
    uint16_t HandleNumber
){
    POPEN_WINDOW_LIST TmpHandle = &MasterWindowList;

    for(uint64_t i = 0 ; i < OpenWindows; i++){
        TmpHandle = (POPEN_WINDOW_LIST)TmpHandle->Neighbors.NextHeader;
        if(i == (uint64_t)HandleNumber){
            return TmpHandle->WindowHandle;
        }
    }

    return 0x00;
}

uint16_t GetAmmountOfOpenWindows(){
    return OpenWindows;
}

void print_clear();
void VgaPutCharecterRgb(char Character, PWINDHANDLE Handle, uint8_t r, uint8_t g, uint8_t b);

void DrawRectangle(
    uint16_t x, 
    uint16_t y, 
    uint16_t width, 
    uint16_t height,
    uint8_t r,
    uint8_t g,
    uint8_t b
    ){
    for(uint16_t yz = y; yz <= y+height; yz++){
        for(uint16_t xz = x;xz <= x+width; xz++){
            LouKeDrsdPutPixelMirrored(xz,yz,r,g,b);
        }
    }
}

void Draw2DBorder(
    uint16_t x, 
    uint16_t y, 
    uint16_t width, 
    uint16_t height, 
    uint8_t r,
    uint8_t g,
    uint8_t b
    ){
        plot_Line(x,y,x,y+height,r,g,b);
        plot_Line(x,y,x+width,y,r,g,b);
        plot_Line(x+width,y,x+width,y+height,r,g,b);
        plot_Line(x,y+height,x+width,y+height,r,g,b);
}

void Draw3DBorder(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint16_t rf,
    uint16_t gf,
    uint16_t bf,
    uint16_t rb,
    uint16_t gb,
    uint16_t bb
){
        plot_Line(x,y,x,y+height,rf,gf,bf);
        plot_Line(x,y,x+width,y,rf,gf,bf);
        plot_Line(x+width,y,x+width,y+height,rb,gb,bb);
        plot_Line(x,y+height,x+width,y+height,rb,gb,bb);
}

static inline
void DrawWindowTitle(
    PWINDHANDLE WindowHandle
){
    WINDHANDLE Title;
    
    Title.Charecteristics.Dimentions.x = WindowHandle->CurrentX - 3;
    Title.Charecteristics.Dimentions.y = WindowHandle->CurrentY + 5;
    Title.Charecteristics.Dimentions.height = (17 * 2);
    Title.Charecteristics.Dimentions.width = WindowHandle->CurrentWidth - 6;
    Title.Cursor.x = 0;
    Title.Cursor.y = 0;
    VgaPutCharecterRgb(' ', &Title , 255, 255, 255);//prints a null for a memory bug

    for(uint8_t i = 0; i < strlen(WindowHandle->WindowName); i++){
        VgaPutCharecterRgb(WindowHandle->WindowName[i], &Title , 255, 255, 255);
        if((Title.Cursor.x + 17) > (Title.Charecteristics.Dimentions.width/2)){
            break;
        }
    }

}

bool DrawWindow(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    PWINDHANDLE WindHandle
);

bool DrawWindowEx(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    PWINDHANDLE WindHandle,
    bool SkipInnerWindow
){
    if((width < 50) || (height < 50)){
        return false;
    }

    //later on we will check for somthing behind it to draw back for now though
    UNUSED uint16_t oldX = WindHandle->CurrentX;
    UNUSED uint16_t oldY = WindHandle->CurrentY;
    UNUSED uint16_t oldWidth = WindHandle->CurrentWidth;
    UNUSED uint16_t oldHeight = WindHandle->CurrentHeight;

    UNUSED uint16_t ScreenWidth = GetScreenBufferWidth();
    UNUSED uint16_t ScreenHeight = GetScreenBufferWidth();
    

    WindHandle->CurrentX = x;
    WindHandle->CurrentY = y;
    WindHandle->CurrentWidth = width;
    WindHandle->CurrentHeight = height;

    WindHandle->Charecteristics.Dimentions.x = x+6;
    WindHandle->Charecteristics.Dimentions.y = y+2+33+1;

    WindHandle->Charecteristics.Dimentions.width =  width - 7;
    WindHandle->Charecteristics.Dimentions.height = height - (2+33+1+1);

    if(!SkipInnerWindow){

        if(
            (WindHandle->WindowDataColor.r != WindHandle->ForgroundColor.r) &&
            (WindHandle->WindowDataColor.g != WindHandle->ForgroundColor.g) &&
            (WindHandle->WindowDataColor.b != WindHandle->ForgroundColor.b)
        ){
            for(uint16_t Buffx = 0 ; Buffx < GetScreenBufferWidth(); Buffx++){
                for(uint16_t Buffy = 0 ; Buffy < GetScreenBufferHeight(); Buffy++){
                    uint8_t* FOO = (uint8_t*)&WindHandle->InnerWindowData[Buffx + GetScreenBufferWidth() * Buffy];
                    if(
                        (FOO[0] == WindHandle->WindowDataColor.b) &&
                        (FOO[1] == WindHandle->WindowDataColor.g) &&
                        (FOO[2] == WindHandle->WindowDataColor.r) 
                    ){
                        uint8_t* FOO = (uint8_t*)&WindHandle->InnerWindowData[Buffx + GetScreenBufferWidth() * Buffy];
                        FOO[0] = WindHandle->ForgroundColor.b;
                        FOO[1] = WindHandle->ForgroundColor.g;
                        FOO[2] = WindHandle->ForgroundColor.r;
                    }
                }
            }
        }

        
        for(
            uint16_t Buffx = 0; 
            Buffx < WindHandle->Charecteristics.Dimentions.width;
            Buffx++
        ){
            for(
                uint16_t Buffy = 0;
                Buffy < WindHandle->Charecteristics.Dimentions.height;
                Buffy++
            ){
                uint8_t* FOO = (uint8_t*)&WindHandle->InnerWindowData[Buffx + GetScreenBufferWidth() * Buffy];
                LouKeDrsdPutPixelMirrored(
                    WindHandle->Charecteristics.Dimentions.x + Buffx,
                    WindHandle->Charecteristics.Dimentions.y + Buffy,
                    FOO[2],FOO[1], FOO[0]
                );  
            }
        }
        
        if(
            (WindHandle->WindowDataColor.r != WindHandle->ForgroundColor.r) &&
            (WindHandle->WindowDataColor.g != WindHandle->ForgroundColor.g) &&
            (WindHandle->WindowDataColor.b != WindHandle->ForgroundColor.b)
        ){
            WindHandle->WindowDataColor.r = WindHandle->ForgroundColor.r;
            WindHandle->WindowDataColor.g = WindHandle->ForgroundColor.g;
            WindHandle->WindowDataColor.b = WindHandle->ForgroundColor.b;
        }

    }

    //left Front Higlight
    plot_Line(
        x,y,
        x,y+height,
        WindHandle->ForwardHighLite.r,
        WindHandle->ForwardHighLite.g,
        WindHandle->ForwardHighLite.b
    );
    //top Front Higlight
    plot_Line(
        x,y,
        x+width,y,
        WindHandle->ForwardHighLite.r,
        WindHandle->ForwardHighLite.g,
        WindHandle->ForwardHighLite.b
    );
    //right AftHiglight
    plot_Line(
        x+width,y,
        x+width,y+height,
        WindHandle->AftHighLight.r,
        WindHandle->AftHighLight.g,
        WindHandle->AftHighLight.b
    );
    //bottom AftHiglight
    plot_Line(
        x,y+height,
        x+width,y+height,
        WindHandle->AftHighLight.r,
        WindHandle->AftHighLight.g,
        WindHandle->AftHighLight.b
    );
    //top Border
    plot_Line(
        x+1,y+1, 
        x+width-1, y+1, 
        WindHandle->BorderFront.r,
        WindHandle->BorderFront.g,
        WindHandle->BorderFront.b
    );
    //Left Border
    plot_Line(
        x+1,y+2, 
        x+1, y+height-1, 
        WindHandle->BorderFront.r,
        WindHandle->BorderFront.g,
        WindHandle->BorderFront.b
    );
    //bottom Border
    plot_Line(
        x+1,y+height-1,
        x+width-1,y+height-1, 
        WindHandle->BorderBack.r,
        WindHandle->BorderBack.g,
        WindHandle->BorderBack.b
    );
    //right Border
    plot_Line(
        x+width-1,y+1,
        x+width-1,y+height-1, 
        WindHandle->BorderBack.r,
        WindHandle->BorderBack.g,
        WindHandle->BorderBack.b
    );
    //Right Background
    DrawRectangle(
        x+width-4,y+2,
        2,height-3,
        WindHandle->BackgroundColor.r,
        WindHandle->BackgroundColor.g,
        WindHandle->BackgroundColor.b
    );
    //Left Background
    DrawRectangle(
        x+2,y+2,
        2,height-3,
        WindHandle->BackgroundColor.r,
        WindHandle->BackgroundColor.g,
        WindHandle->BackgroundColor.b
    );
    //bottom BackGround
    DrawRectangle(
        x+2,y+height-3,
        width-3,2,
        WindHandle->BackgroundColor.r,
        WindHandle->BackgroundColor.g,
        WindHandle->BackgroundColor.b
    );

    //Top BackGround
    DrawRectangle(
        x+2,y+2,
        width-3,33,
        WindHandle->BackgroundColor.r,
        WindHandle->BackgroundColor.g,
        WindHandle->BackgroundColor.b
    );

    DrawRectangle(x+3,y+3,width-6,12,0,0,128);
    
    //plot_Line(x+5,y+2+27,x+width-5,y+2+27,64,64,64);
    Draw2DBorder(
        x+5,y+2+33,
        (width-9), (height-2-37),         
        WindHandle->AftHighLight.r,
        WindHandle->AftHighLight.g,
        WindHandle->AftHighLight.b
    );

    DrawRectangle(
        x+width-14,y+4,
        10,10,        
        WindHandle->BackgroundColor.r,
        WindHandle->BackgroundColor.g,
        WindHandle->BackgroundColor.b
    );
    
    Draw3DBorder(
        x+width-14,y+4,
        10,10,
        WindHandle->ForwardHighLite.r,
        WindHandle->ForwardHighLite.g,
        WindHandle->ForwardHighLite.b,
        WindHandle->AftHighLight.r,
        WindHandle->AftHighLight.g,
        WindHandle->AftHighLight.b
    );

    plot_Line(
        x+width-14+1,y+4+1,
        x+width-14+10-2,y+4+10-2,
        0,0,0
    );
    plot_Line(
        x+width-14+1,y+4+10-2,
        x+width-14+10-2,y+4+1,
        0,0,0
    );

    DrawRectangle(
        x+width-28,y+4,
        10,10,        
        WindHandle->BackgroundColor.r,
        WindHandle->BackgroundColor.g,
        WindHandle->BackgroundColor.b
    );

    DrawRectangle(
        x+width-42,y+4,
        10,10,        
        WindHandle->BackgroundColor.r,
        WindHandle->BackgroundColor.g,
        WindHandle->BackgroundColor.b
    );

    Draw3DBorder(
        x+width-42,y+4,10,10,  
        WindHandle->ForwardHighLite.r,
        WindHandle->ForwardHighLite.g,
        WindHandle->ForwardHighLite.b,      
        WindHandle->AftHighLight.r,
        WindHandle->AftHighLight.g,
        WindHandle->AftHighLight.b
    );

    DrawRectangle(        
        x+width-40,y+10,
        6,2,        
        WindHandle->AftHighLight.r,
        WindHandle->AftHighLight.g,
        WindHandle->AftHighLight.b
        );

    Draw3DBorder(
        x+width-28,y+4,
        10,10,
        WindHandle->ForwardHighLite.r,
        WindHandle->ForwardHighLite.g,
        WindHandle->ForwardHighLite.b,
        WindHandle->AftHighLight.r,
        WindHandle->AftHighLight.g,
        WindHandle->AftHighLight.b
    );

    Draw2DBorder(
        x+width-26,y+6,6,6,        
        WindHandle->AftHighLight.r,
        WindHandle->AftHighLight.g,
        WindHandle->AftHighLight.b
    );

    DrawWindowTitle(
        WindHandle
    );
  

    return true;
}

bool DrawWindow(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    PWINDHANDLE WindHandle
){
    return DrawWindowEx(x,y,width,height,WindHandle, false);
}

static spinlock_t WindowUpdateLock;


bool LouUpdateWindow(
    uint16_t x, 
    uint16_t y, 
    uint16_t width,
    uint16_t height,
    PWINDHANDLE WindHandle
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&WindowUpdateLock, &Irql);
    
    LouKeDrsdHandleWindowUpdate(
        WindHandle,
        x,y,
        width, height
    );

    if(DrawWindow(
        x, y,
        width, height,
        WindHandle) != true){
        LouKeReleaseSpinLock(&WindowUpdateLock, &Irql);
        return false;
    }
    LouKeReleaseSpinLock(&WindowUpdateLock, &Irql);
    LouKeDrsdSyncScreens();
    return true;
}


static spinlock_t LouUpdtateTextWindowLock;

bool LouUpdateTextWindow(PWINDHANDLE WindowHandle,TEXT_WINDOW_EVENT Update){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&LouUpdtateTextWindowLock, &Irql);    
    const uint16_t Width = WindowHandle->Charecteristics.Dimentions.width;
    const uint16_t Height = WindowHandle->Charecteristics.Dimentions.height;
    const uint16_t StartX = WindowHandle->Charecteristics.Dimentions.x;
    const uint16_t StartY = WindowHandle->Charecteristics.Dimentions.y;
    const uint16_t ScreenWidth = GetScreenBufferWidth();
    const uint16_t ScreenHeight = GetScreenBufferHeight();

    switch (Update){
        case TEXT_WINDOW_BUFFER_OVERFLOW:{
            UNUSED uint8_t r;
            UNUSED uint8_t g;
            UNUSED uint8_t b;
            UNUSED uint8_t a;
            UNUSED uint8_t GpuCount = LouKeDeviceManagerGetGpuCount();
            PDrsdVRamObject FBDEV;
            for(uint8_t i = 0; i < GpuCount; i++){
                FBDEV = LouKeDeviceManagerGetFBDEV(i);        
                for(uint16_t x = 0; x < (Width - 5); x++){
                    for(uint16_t y = 18; y < (Height - 5); y++){         
                        uint32_t* dest = GetFrameBufferAddress(FBDEV ,StartX + x, StartY + y - 18);
                        *dest = WindowHandle->InnerWindowData[x + ScreenWidth * y];
                    }
                }
            }
            for(uint16_t x = 0; x < (Width - 5); x++){
                for(uint16_t y = 18; y < (Height - 5); y++){  
                    WindowHandle->InnerWindowData[x + ScreenWidth * (y - 18)] = WindowHandle->InnerWindowData[x + ScreenWidth * y];
                }
            }
            break;
        }

        case TEXT_WINDOW_RESIZE:{
            UNUSED uint8_t r;
            UNUSED uint8_t g;
            UNUSED uint8_t b;
            UNUSED uint8_t a;
            UNUSED uint8_t GpuCount = LouKeDeviceManagerGetGpuCount();
            PDrsdVRamObject FBDEV;
            for(uint8_t i = 0; i < GpuCount; i++){
                FBDEV = LouKeDeviceManagerGetFBDEV(i);        
                for(uint16_t x = 0; x < (Width - 1); x++){
                    for(uint16_t y = 0; y < (Height - 3); y++){         
                        uint32_t* dest = GetFrameBufferAddress(FBDEV ,StartX + x, StartY + y);
                        *dest = 0 ;//= WindowHandle->InnerWindowData[x + ScreenWidth * y];
                    }
                }
            }

            uint16_t HeightDifference = WindowHandle->Cursor.y - (Height - 64);
            for(uint16_t x = 0; x < (ScreenWidth - 1); x++){
                for(uint16_t y = HeightDifference; y < (ScreenHeight); y++){  
                    WindowHandle->InnerWindowData[x + ScreenWidth * (y - HeightDifference)] = WindowHandle->InnerWindowData[x + ScreenWidth * y];
                }
            }
            

            for(uint8_t i = 0; i < GpuCount; i++){
                FBDEV = LouKeDeviceManagerGetFBDEV(i);        
                for(uint16_t x = 0; x < (Width - 1); x++){
                    for(uint16_t y = 0; y < (Height - 3); y++){         
                        uint32_t* dest = GetFrameBufferAddress(FBDEV ,StartX + x, StartY + y);
                        *dest = WindowHandle->InnerWindowData[x + ScreenWidth * y];
                    }
                }
            }
            WindowHandle->Cursor.y = Height - 64;
        }
    }
    LouKeReleaseSpinLock(&LouUpdtateTextWindowLock, &Irql);    
    
    return true;
}

static spinlock_t WindowCreationLock;

PWINDHANDLE LouCreateWindow(
    const uint16_t x, const uint16_t y,
    const uint16_t width, const uint16_t height, 
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
    ){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&WindowCreationLock, &Irql);
    UNUSED static uint16_t yT;
    UNUSED static uint16_t xT;

    PWINDHANDLE WindHandle = CreateWindowHandle();

    
    WindHandle->ParentWindow = ParentWindow;
    WindHandle->ChildWindows = 0x00; //null until assigned 
    WindHandle->CurrentX = x;
    WindHandle->CurrentY = y;
    WindHandle->CurrentWidth = width;
    WindHandle->CurrentHeight = height;
    WindHandle->ForgroundColor.r = 255;
    WindHandle->ForgroundColor.g = 255;
    WindHandle->ForgroundColor.b = 255;
    WindHandle->BackgroundColor.r = 198;
    WindHandle->BackgroundColor.g = 198;
    WindHandle->BackgroundColor.b = 198;
    WindHandle->BorderFront.r = 198;
    WindHandle->BorderFront.g = 198;
    WindHandle->BorderFront.b = 198;
    WindHandle->BorderBack.r = 192;
    WindHandle->BorderBack.g = 192;
    WindHandle->BorderBack.b = 192;
    WindHandle->ForwardHighLite.r = 255;
    WindHandle->ForwardHighLite.g = 255;
    WindHandle->ForwardHighLite.b = 255;
    WindHandle->AftHighLight.r = 64;
    WindHandle->AftHighLight.g = 64;
    WindHandle->AftHighLight.b = 64;
    WindHandle->NumberOfChildWindows = 0;

    WindHandle->WindowDataColor.r = WindHandle->ForgroundColor.r;
    WindHandle->WindowDataColor.g = WindHandle->ForgroundColor.g;
    WindHandle->WindowDataColor.b = WindHandle->ForgroundColor.b;

    //fill out windows charecteristics
    WindHandle->Charecteristics.Type = Charecteristics->Type;
    WindHandle->Charecteristics.Dimentions.x = x+6;
    WindHandle->Charecteristics.Dimentions.y = y+2+54+1;
    WindHandle->Charecteristics.Dimentions.width = (width - x + 1)- 3;
    WindHandle->Charecteristics.Dimentions.height = height -(y + 24 + 1);

    WindHandle->Cursor.x = 0;
    WindHandle->Cursor.y = 0;

    WindHandle->WindowName = Charecteristics->WindowName;

    WindHandle->InnerWindowData = LouMallocEx(    
        GetScreenBufferHeight() * GetScreenBufferWidth() * 4, 4
    );

    for(
        uintptr_t InnerWindowData = 0; 
        InnerWindowData < (GetScreenBufferHeight() * GetScreenBufferWidth()); 
        InnerWindowData++
    ){
        uint8_t* Data = (uint8_t*)&WindHandle->InnerWindowData[InnerWindowData];
        Data[0] = WindHandle->ForgroundColor.b;
        Data[1] = WindHandle->ForgroundColor.g;
        Data[2] = WindHandle->ForgroundColor.r;
        Data[3] = 0;
    }

    LouUpdateWindow(
        x, y, 
        width, height,
        WindHandle
    );

    LouKeReleaseSpinLock(&WindowCreationLock, &Irql);
    return WindHandle;
}

void LouDestroyWindow(PWINDHANDLE WindowToDestroy){
    LouKeDrsdHandleWindowUpdate(
        0x00,
        WindowToDestroy->CurrentX,
        WindowToDestroy->CurrentY,
        WindowToDestroy->CurrentWidth,
        WindowToDestroy->CurrentHeight
    );
    DestroyWindowHandle(WindowToDestroy);
}