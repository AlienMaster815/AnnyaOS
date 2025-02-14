#include <LouAPI.h>

static FILE*    BackgroundFile     = 0x00;
static uint16_t BackgroundFileType = 0x00;

PDrsdVRamObject LouKeDeviceManagerGetFBDEV(uint8_t Gpu);

PWINDHANDLE 
GetWindowHandleByNumber(
    uint16_t HandleNumber
);

uint16_t GetAmmountOfOpenWindows();

void LouKeDrsdResetScreen(uint8_t Gpu){
    PDrsdVRamObject FBDEV = LouKeDeviceManagerGetFBDEV(Gpu);
    uint16_t ScreenWidth = FBDEV->FrameBuffer.Width;
    uint16_t ScreenHeight = FBDEV->FrameBuffer.Height;

    if(FBDEV->FrameWorkReference->RgbPutPixel != 0x00){
        for(uint16_t x = 0; x < ScreenWidth; x++){
            for(uint16_t y = 0; y < ScreenHeight; y++){
                FBDEV->FrameWorkReference->RgbPutPixel(FBDEV, x, y, 0, 192, 192, 0);
           }   
        }
    }
}

void LouKeDrsdResetFBDEV(uint64_t* FBDEV){
    uint64_t NumFBDEV = (uint64_t)LouKeDeviceManagerGetGpuCount();
    if(*FBDEV > NumFBDEV){
        *FBDEV = STATUS_NO_SUCH_DEVICE;
    }
    LouKeDrsdResetScreen((uint8_t)*FBDEV);
    *FBDEV = STATUS_SUCCESS;
}

void LouKeDrsdPciResetScreen(P_PCI_DEVICE_OBJECT PDEV){
    uint8_t GpuCount = LouKeDeviceManagerGetGpuCount();
    PDrsdVRamObject FBDEV;
    for(uint8_t i = 0 ; i < GpuCount; i++){
        FBDEV = LouKeDeviceManagerGetFBDEV(i);
        if(FBDEV->DeviceObject == (void*)PDEV)break;
    }
    uint16_t ScreenWidth = FBDEV->FrameBuffer.Width;
    uint16_t ScreenHeight = FBDEV->FrameBuffer.Height;

    if(FBDEV->FrameWorkReference->RgbPutPixel != 0x00){
        for(uint16_t x = 0; x < ScreenWidth; x++){
            for(uint16_t y = 0; y < ScreenHeight; y++){
                FBDEV->FrameWorkReference->RgbPutPixel(FBDEV, x, y, 0, 192, 192, 0);
           }   
        }
    }
    if(FBDEV->FrameWorkReference->BlitCopy){
        FBDEV->FrameWorkReference->BlitCopy((void*)FBDEV->FrameBuffer.FramebufferBase, (void*)FBDEV->FrameBuffer.SecondaryFrameBufferBase, FBDEV->FrameBuffer.FramebufferSize);
    }
}


void LouKeDrsdPutPixelMirroredEx(
    uint16_t x, uint16_t y, 
    uint8_t r, uint8_t g, uint8_t b, uint8_t a
){
    uint8_t GpuCount = LouKeDeviceManagerGetGpuCount();
    PDrsdVRamObject FBDEV;
    for(uint8_t i = 0 ; i < GpuCount; i++){
        FBDEV = LouKeDeviceManagerGetFBDEV(i);
        uint16_t ScreenWidth = FBDEV->FrameBuffer.Width;
        uint16_t ScreenHeight = FBDEV->FrameBuffer.Height;
        if((x > ScreenWidth) || (y > ScreenHeight)){
            return;
        }
        FBDEV->FrameWorkReference->RgbPutPixel(FBDEV, x, y, r, g, b, a);
    }
}

void LouKeDrsdPutPixelMirrored(
    uint16_t x, uint16_t y, 
    uint8_t r, uint8_t g, uint8_t b
){
    LouKeDrsdPutPixelMirroredEx(
        x, y,
        r,g,b,0
    );
}

void LouKeDrsdSyncScreens(){
    uint8_t GpuCount = LouKeDeviceManagerGetGpuCount();
    PDrsdVRamObject FBDEV;
    for(uint8_t i = 0 ; i < GpuCount; i++){
        FBDEV = LouKeDeviceManagerGetFBDEV(i);
        if(FBDEV->FrameWorkReference->BlitCopy){
            FBDEV->FrameWorkReference->BlitCopy((void*)FBDEV->FrameBuffer.FramebufferBase, (void*)FBDEV->FrameBuffer.SecondaryFrameBufferBase, FBDEV->FrameBuffer.FramebufferSize);
        }
    }
}

void LouKeDsrdFBDEVFrameBufferMemMov(
    uint8_t Gpu,
    PFRAME_BUFFER_HANDLE FrameHandle, 
    PWINDHANDLE WindowOfCopy,
    uint64_t xDest, 
    uint64_t yDest,
    COLOR_MAP Background
){
    PDrsdVRamObject FBDEV = LouKeDeviceManagerGetFBDEV(Gpu);
    uint16_t Width =  FrameHandle->width;
    uint16_t Height = FrameHandle->height;
    uint16_t StartX = FrameHandle->x;
    uint16_t StartY = FrameHandle->y;
    uint8_t BytesPerPixel = FBDEV->FrameBuffer.Bpp / 8;

    for (uint16_t y = 0; y < Height; y++) {
        for(uint16_t x = 0 ; x < Width; x++){
            void* dest = GetFrameBufferAddress(FBDEV ,xDest + x, yDest + y);
            void* src = GetFrameBufferAddress(FBDEV, StartX + x, StartY + y);
        
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

    if(FBDEV->FrameWorkReference->BlitCopy){
        FBDEV->FrameWorkReference->BlitCopy((void*)FBDEV->FrameBuffer.FramebufferBase, (void*)FBDEV->FrameBuffer.SecondaryFrameBufferBase, FBDEV->FrameBuffer.FramebufferSize);
    }

}

void LouKeDsrdMirrorFrameBufferMemMov(
    PFRAME_BUFFER_HANDLE FrameHandle, 
    PWINDHANDLE WindowOfCopy,
    uint64_t xDest, 
    uint64_t yDest,
    COLOR_MAP BackGround
    ){
    uint8_t GpuCount = LouKeDeviceManagerGetGpuCount();

    for (uint8_t i = 0 ; i < GpuCount; i++){
        LouKeDsrdFBDEVFrameBufferMemMov(
            i,
            FrameHandle,
            WindowOfCopy,
            xDest,
            yDest,
            BackGround
        );
    }
   
}

static inline
bool DoesPixelOverlap(
    uint16_t x, 
    uint16_t y, 
    uint16_t width, 
    uint16_t height, 
    uint16_t PixelX,
    uint16_t PixelY
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
    uint16_t x, uint16_t y, 
    uint8_t r, uint8_t g, uint8_t b,
    uint16_t XStepping, uint16_t YStepping
){  

    uint16_t X = x * XStepping;
    uint16_t Y = y * YStepping;

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
                LouKeDrsdPutPixelMirrored(
                    X + x2,                                
                    (GetScreenBufferHeight() - 1) - (Y + y2), 
                    r, g, b                                     
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
        uint16_t Height = BitHandle->Height;
        uint16_t Width = BitHandle->Width;
        uint16_t Bpp = BitHandle->Bpp;

        if((!GetScreenBufferWidth()) || (!Width) || (!GetScreenBufferHeight()) || (!Height)){
            LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
            return;
        }

        uint16_t XStepping = (GetScreenBufferWidth() / Width);
        uint16_t YStepping = (GetScreenBufferHeight() / Height);

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
    //Other file types
    LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
}



void LouKeDrsdHandleWindowUpdate(
    PWINDHANDLE WindowHandle,
    uint16_t NewX,
    uint16_t NewY,
    uint16_t NewWidth,
    uint16_t NewHeight
){

    if(WindowHandle == 0x00){
        uint16_t CurrentX = NewX;
        uint16_t CurrentY = NewY;
        uint16_t CurrentHeight = NewHeight;
        uint16_t CurrentWidth = NewWidth;

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
                uint16_t Height = BitHandle->Height;
                uint16_t Width = BitHandle->Width;
                uint16_t Bpp = BitHandle->Bpp;

                if((!GetScreenBufferWidth()) || (!Width) || (!GetScreenBufferHeight()) || (!Height)){
                    LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                    //LouKeDrsdSyncScreens();
                    return;
                }

                uint16_t XStepping = (GetScreenBufferWidth() / Width);
                uint16_t YStepping = (GetScreenBufferHeight() / Height);

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
            
            for(uint16_t x = CurrentX; x <= (CurrentX + CurrentWidth); x++){
                for(uint16_t y = 0 ; y <= (CurrentY + CurrentHeight); y++){
                    LouKeDrsdPutPixelMirrored(x, y,0, 192, 192);
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

    uint16_t CurrentX = WindowHandle->CurrentX;
    uint16_t CurrentY = WindowHandle->CurrentY;
    uint16_t CurrentHeight = WindowHandle->CurrentHeight;
    uint16_t CurrentWidth = WindowHandle->CurrentWidth;

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
            uint16_t Height = BitHandle->Height;
            uint16_t Width = BitHandle->Width;
            uint16_t Bpp = BitHandle->Bpp;

            if((!GetScreenBufferWidth()) || (!Width) || (!GetScreenBufferHeight()) || (!Height)){
                LouKeReleaseSpinLock(&LouKeDrsdDrawDesktopBackgroundLock, &Irql);
                //LouKeDrsdSyncScreens();
                return;
            }

            uint16_t XStepping = (GetScreenBufferWidth() / Width);
            uint16_t YStepping = (GetScreenBufferHeight() / Height);

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
        
        for(uint16_t x = CurrentX; x <= (CurrentX + CurrentWidth); x++){
            for(uint16_t y = 0 ; y <= (CurrentY + CurrentHeight); y++){
                if(!DoesPixelOverlap(
                    NewX, NewY,
                    NewWidth, NewHeight,
                    x, y
                )){
                    LouKeDrsdPutPixelMirrored(x, y,0, 192, 192);
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
