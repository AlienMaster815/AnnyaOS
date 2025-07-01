#include <LouAPI.h>

void LouKeDrsdCorePutPixel(int64_t X, int64_t Y, uint8_t R, uint8_t G, uint8_t B, uint8_t A);


static spinlock_t BitMapDrawLock;

void LouKeDrsdDrawBitMap(PBITMAP_HANDLE BitmapHandle, int64_t x, int64_t y){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&BitMapDrawLock, &Irql);
    uint8_t* PixelData = (uint8_t*)BitmapHandle->UnpackedData;
    uint8_t* Anchor = PixelData;
    uint16_t Height = BitmapHandle->Height;
    uint16_t Width = BitmapHandle->Width;
    //uint16_t Bpp = BitmapHandle->Bpp;
    // Rendering for top-left origin framebuffer
    for(uint64_t yz = 0; yz < Height; yz++){
        for(uint64_t xz = 0; xz < Width; xz++){    
            PixelData = &Anchor[(y * Width + x) * 4];
            UNUSED uint8_t b = PixelData[0];
            UNUSED uint8_t g = PixelData[1];
            UNUSED uint8_t r = PixelData[2];
            //LouKeDrsdCorePutPixel(x + xz, y + yz, r, g, b, 0);                 
        }
    }
    //LouKeDrsdSyncScreens();
    LouKeReleaseSpinLock(&BitMapDrawLock, &Irql);
}