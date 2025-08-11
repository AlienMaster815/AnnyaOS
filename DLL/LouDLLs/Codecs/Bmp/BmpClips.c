#include "Bmp.h"

CODECS_API
void 
AnnyaPaintClipWithBmp(
    HANDLE  Bitmap,
    HANDLE  Cliph,
    size_t  X, size_t  Y,
    size_t  ScalingX,
    size_t  ScalingY
){

    PCODECS_TYPE_QUERY Type = (PCODECS_TYPE_QUERY)Bitmap;
    PBITMAP_HANDLE Bmp = (PBITMAP_HANDLE)Type->HandleInformation.ImageHandleData.PrivateDataHandle;
    PDRSD_CLIP Clip = (PDRSD_CLIP)Cliph;
    uint8_t* PixelData = (uint8_t*)Bmp->UnpackedData;   
    const uint8_t* Anchor = PixelData;
    uint16_t Height = Bmp->Height;
    uint16_t Width = Bmp->Width;
    uint16_t Bpp = (Bmp->Bpp / 8);
    if((Clip->Width < Width) || (Clip->Height < Height) || (Bpp < 3)){
        return;
    }
    uint32_t TmpData = 0x00;
    for(uint64_t yz = 0; yz < Height; yz++){
        for(uint64_t xz = 0; xz < Width; xz++){  
            PixelData = (uint8_t*)&Anchor[(((Height - 1) - yz) * Width + ((Width - 1) - xz)) * 4];
            TmpData = PixelData[0];
            TmpData |= (PixelData[1] << 8);
            TmpData |= (PixelData[2] << 16);
            TmpData |= (PixelData[3] << 24);
            for(size_t Ys = 0 ; Ys < ScalingY; Ys++){
                for(size_t Xs = 0 ; Xs < ScalingX; Xs++){ 
                    Clip->WindowBuffer[(X+(xz*ScalingX)+Xs) + ((Y+(yz*ScalingY)+Ys) * Clip->Width)] = TmpData;
                }
            }
        }
    }
}