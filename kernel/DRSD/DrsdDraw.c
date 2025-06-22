#include <LouAPI.h>

static FILE*    BackgroundFile     = 0x00;
static uint16_t BackgroundFileType = 0x00;
void LouKeDrsdCorePutPixel(int64_t X, int64_t Y, uint8_t R, uint8_t G, uint8_t B, uint8_t A);
void* GetFrameBufferAddress(
    int64_t x, int64_t y
);
;

PWINDHANDLE 
GetWindowHandleByNumber(
    uint16_t HandleNumber
);

uint16_t GetAmmountOfOpenWindows();


void LouKeDsrdFBDEVFrameBufferMemMov(
    PFRAME_BUFFER_HANDLE FrameHandle, 
    PWINDHANDLE WindowOfCopy,
    uint64_t xDest, 
    uint64_t yDest,
    COLOR_MAP Background
){
    uint16_t Width =  FrameHandle->width;
    uint16_t Height = FrameHandle->height;
    uint16_t StartX = FrameHandle->x;
    uint16_t StartY = FrameHandle->y;
    uint8_t BytesPerPixel = 4;

    for (uint16_t y = 0; y < Height; y++) {
        for(uint16_t x = 0 ; x < Width; x++){
            void* dest = GetFrameBufferAddress(xDest + x, yDest + y);
            void* src = GetFrameBufferAddress(StartX + x, StartY + y);
        
            if (BytesPerPixel == 4) {
                *(uint8_t*)(dest) = *(uint8_t*)(src);
                *(uint8_t*)(dest+1) = *(uint8_t*)(src+1);
                *(uint8_t*)(dest+2) = *(uint8_t*)(src+2);
                *(uint8_t*)(dest+3) = *(uint8_t*)(src+3);
                
                *(uint8_t*)(src)   = Background.b;
                *(uint8_t*)(src+1) = Background.g;
                *(uint8_t*)(src+2) = Background.r;
                *(uint8_t*)(src+3) = 0;

            } else if (BytesPerPixel == 3) {
                *(uint8_t*)(dest) = *(uint8_t*)(src);
                *(uint8_t*)(dest+1) = *(uint8_t*)(src+1);
                *(uint8_t*)(dest+2) = *(uint8_t*)(src+2);

                *(uint8_t*)(src)   = Background.b;
                *(uint8_t*)(src+1) = Background.g;
                *(uint8_t*)(src+2) = Background.r;
            }

        }
    }

}

void LouKeDsrdMirrorFrameBufferMemMov(
    PFRAME_BUFFER_HANDLE FrameHandle, 
    PWINDHANDLE WindowOfCopy,
    uint64_t xDest, 
    uint64_t yDest,
    COLOR_MAP BackGround
){
    LouKeDsrdFBDEVFrameBufferMemMov(
        FrameHandle,
        WindowOfCopy,
        xDest,
        yDest,
        BackGround
    );
}
   

static inline
bool DoesPixelOverlap(
    int64_t x, 
    int64_t y, 
    uint32_t width, 
    uint32_t height, 
    int64_t PixelX,
    int64_t PixelY
){
    return(
        (PixelX >= x) && 
        (PixelX <= (x + width)) && 
        (PixelY >= y) && 
        (PixelY <= (y + height)));
}

//static spinlock_t FPWSLock;
 
static inline
void FillPixelsWithStepping(
    int64_t x, int64_t y, 
    uint8_t r, uint8_t g, uint8_t b,
    uint16_t XStepping, uint16_t YStepping
){  

    int64_t X = x * XStepping;
    int64_t Y = y * YStepping;

    uint8_t WindowCount = GetAmmountOfOpenWindows();
    for(uint16_t x2 = 0; x2 < XStepping; x2++){
        for(uint16_t y2 = 0; y2 < YStepping; y2++){
            bool PixelOverlap = false;
            for(uint8_t i = 0 ; i < WindowCount; i++){
                PWINDHANDLE WindowHandle = GetWindowHandleByNumber(i);
                if(DoesPixelOverlap(
                    WindowHandle->CurrentX,
                    WindowHandle->CurrentY,
                    WindowHandle->CurrentWidth,
                    WindowHandle->CurrentHeight,
                    X + x2,
                    (GetScreenBufferHeight() - 1) - (Y + y2)
                ))PixelOverlap = true;
            }
            if(!PixelOverlap){
                LouKeDrsdCorePutPixel(
                    X + x2,                                
                    (GetScreenBufferHeight() - 1) - (Y + y2), 
                    r, g, b, 0                                     
                );    
            }
        }
    }
}

static spinlock_t LouKeDrsdDrawDesktopBackgroundLock;

void LouKeDrsdDrawDesktopBackground(
    FILE* ImageFile,
    uint16_t DrsdFileType
){

    LouKIRQL Irql;

    LouKeAcquireSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);

    if(BackgroundFile != ImageFile){
        BackgroundFile = ImageFile;
    }
    if(BackgroundFileType != DrsdFileType){
        BackgroundFileType = DrsdFileType;
    }

    if(DrsdFileType == 0){
        //Bitmap Type
        PBITMAP_HANDLE BitHandle = (PBITMAP_HANDLE)ImageFile;

            // Ensure the handle is valid
        if (!BitHandle || !BitHandle->UnpackedData) {
            LouPrint("Invalid bitmap handle or unpacked data.\n");
            LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
            return;
        }

        uint8_t* PixelData = (uint8_t*)BitHandle->UnpackedData;
        uint8_t* Anchor = PixelData;
        int64_t Height = BitHandle->Height;
        int64_t Width = BitHandle->Width;
        uint16_t Bpp = BitHandle->Bpp;

        if((!GetScreenBufferWidth()) || (!Width) || (!GetScreenBufferHeight()) || (!Height)){
            LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
            return;
        }

        int64_t XStepping = (GetScreenBufferWidth() / Width);
        int64_t YStepping = (GetScreenBufferHeight() / Height);

        //LouPrint("XStepping:%d\n", XStepping);
        //LouPrint("YStepping:%d\n", YStepping);

        //uint16_t CenterX = XStepping * Width;
        //uint16_t CenterY = YStepping * Height;

        //while(1);
        // Validate supported bit depth
        if (Bpp != 32) {
            LouPrint("Unsupported bitmap bit depth: %d\n", Bpp);
            LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
            return;
        }

        if((Width == GetScreenBufferWidth()) && (Height == GetScreenBufferHeight())) {
            // Rendering for top-left origin framebuffer
            for(uint64_t y = 0; y < Height; y++){
                for(uint64_t x = 0; x < Width; x++){    
                    PixelData = &Anchor[(y * Width + x) * 4];
                    uint8_t b = PixelData[0];
                    uint8_t g = PixelData[1];
                    uint8_t r = PixelData[2];
                    FillPixelsWithStepping(x, y, r, g, b, XStepping, YStepping);                 
                }
            }
        }
    }
    //Other file types
    LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
    LouKeDrsdSyncScreens();
}


void LouKeDrsdHandleWindowUpdate(
    PWINDHANDLE WindowHandle,
    int64_t NewX,
    int64_t NewY,
    uint32_t NewWidth,
    uint32_t NewHeight
){

    if(WindowHandle == 0x00){
        int64_t CurrentX = NewX;
        int64_t CurrentY = NewY;
        uint32_t CurrentHeight = NewHeight;
        uint32_t CurrentWidth = NewWidth;

        if(BackgroundFile){

            if(BackgroundFileType == 0){
                LouKIRQL Irql;

                LouKeAcquireSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                //Bitmap Type
                PBITMAP_HANDLE BitHandle = (PBITMAP_HANDLE)BackgroundFile;

                    // Ensure the handle is valid
                if (!BitHandle || !BitHandle->UnpackedData) {
                    LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                    LouKeDrsdSyncScreens();
                    return;
                }

                uint8_t* PixelData = (uint8_t*)BitHandle->UnpackedData;
                uint8_t* Anchor = PixelData;
                uint32_t Height = BitHandle->Height;
                uint32_t Width = BitHandle->Width;
                uint16_t Bpp = BitHandle->Bpp;

                if((!GetScreenBufferWidth()) || (!Width) || (!GetScreenBufferHeight()) || (!Height)){
                    LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                    LouKeDrsdSyncScreens();
                    return;
                }

                int64_t XStepping = (GetScreenBufferWidth() / Width);
                int64_t YStepping = (GetScreenBufferHeight() / Height);

                //LouPrint("XStepping:%d\n", XStepping);
                //LouPrint("YStepping:%d\n", YStepping);

                //uint16_t CenterX = XStepping * Width;
                //uint16_t CenterY = YStepping * Height;

                //while(1);
                // Validate supported bit depth
                if (Bpp != 32) {
                    LouPrint("Unsupported bitmap bit depth: %d\n", Bpp);
                    LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                    LouKeDrsdSyncScreens();
                    return;
                }

                // Rendering for top-left origin framebuffer
                for(uint64_t y = 0; y < Height; y++){
                    for(uint64_t x = 0; x < Width; x++){    
                        PixelData = &Anchor[(y * Width + x) * 4];
                        uint8_t b = PixelData[0];
                        uint8_t g = PixelData[1];
                        uint8_t r = PixelData[2];
                        FillPixelsWithStepping(x, y, r, g, b, XStepping, YStepping);                 
                    }
                }
            LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);

            }
            //Other file types

        }else{
            
            for(int64_t x = CurrentX; x <= (CurrentX + CurrentWidth); x++){
                for(int64_t y = 0 ; y <= (CurrentY + CurrentHeight); y++){
                    LouKeDrsdCorePutPixel(x, y,0, 192, 192, 0);
                }
            }

            
        }
        /*
        uint16_t WindowsToCheck = GetAmmountOfOpenWindows();
        PWINDHANDLE WindowParseHandle;

        for(uint16_t i = 0 ; i < WindowsToCheck; i++){
            WindowParseHandle = GetWindowHandleByNumber(i);
            if (WindowHandle == WindowParseHandle)continue;

            LouUpdateWindow(
                WindowHandle, 
                WindowHandle->CurrentX, 
                WindowHandle->CurrentY, 
                WindowHandle->CurrentWidth, 
                WindowHandle->CurrentHeight
            );

        }
        */
        //LouKeDrsdSyncScreens();
        //return;
    }

    int64_t CurrentX = WindowHandle->CurrentX;
    int64_t CurrentY = WindowHandle->CurrentY;
    uint32_t CurrentHeight = WindowHandle->CurrentHeight;
    uint32_t CurrentWidth = WindowHandle->CurrentWidth;

    if(BackgroundFile){

        if(BackgroundFileType == 0){
            LouKIRQL Irql;

            LouKeAcquireSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
            //Bitmap Type
            PBITMAP_HANDLE BitHandle = (PBITMAP_HANDLE)BackgroundFile;

                // Ensure the handle is valid
            if (!BitHandle || !BitHandle->UnpackedData) {
                LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                //LouKeDrsdSyncScreens();
                return;
            }

            uint8_t* PixelData = (uint8_t*)BitHandle->UnpackedData;
            uint8_t* Anchor = PixelData;
            uint32_t Height = BitHandle->Height;
            uint32_t Width = BitHandle->Width;
            uint16_t Bpp = BitHandle->Bpp;

            if((!GetScreenBufferWidth()) || (!Width) || (!GetScreenBufferHeight()) || (!Height)){
                LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                //LouKeDrsdSyncScreens();
                return;
            }

            int64_t XStepping = (GetScreenBufferWidth() / Width);
            int64_t YStepping = (GetScreenBufferHeight() / Height);

            //LouPrint("XStepping:%d\n", XStepping);
            //LouPrint("YStepping:%d\n", YStepping);

            //uint16_t CenterX = XStepping * Width;
            //uint16_t CenterY = YStepping * Height;

            //while(1);
            // Validate supported bit depth
            if (Bpp != 32) {
                LouPrint("Unsupported bitmap bit depth: %d\n", Bpp);
                LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                //LouKeDrsdSyncScreens();
                return;
            }

            // Rendering for top-left origin framebuffer
            for(uint64_t y = 0; y < Height; y++){
                for(uint64_t x = 0; x < Width; x++){    
                    PixelData = &Anchor[(y * Width + x) * 4];
                    uint8_t b = PixelData[0];
                    uint8_t g = PixelData[1];
                    uint8_t r = PixelData[2];
                    FillPixelsWithStepping(x, y, r, g, b, XStepping, YStepping);                 
                }
            }
        LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);

        }
        //Other file types

    }else{
        
        for(int64_t x = CurrentX; x <= (CurrentX + CurrentWidth); x++){
            for(int64_t y = 0 ; y <= (CurrentY + CurrentHeight); y++){
                if(!DoesPixelOverlap(
                    NewX, NewY,
                    NewWidth, NewHeight,
                    x, y
                )){
                    LouKeDrsdCorePutPixel(x, y,0, 192, 192, 0);
                }
            }
        }
        
    }
    /*
    uint16_t WindowsToCheck = GetAmmountOfOpenWindows();
    PWINDHANDLE WindowParseHandle;

    for(uint16_t i = 0 ; i < WindowsToCheck; i++){
        WindowParseHandle = GetWindowHandleByNumber(i);
        if (WindowHandle == WindowParseHandle)continue;

        LouUpdateWindow(
            WindowHandle, 
            WindowHandle->CurrentX, 
            WindowHandle->CurrentY, 
            WindowHandle->CurrentWidth, 
            WindowHandle->CurrentHeight
        );

    }
    */
    //LouKeDrsdSyncScreens();
}
