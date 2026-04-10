#include "../BootVid.h"

LOUSTATUS
BootVidBitmapPutPixelEx(
    PBOOTVID_BITMAP Bitmap,
    int             x,
    int             y,
    UINT32          Color
){
    if((x >= Bitmap->Width || y >= Bitmap->Height)){
        return STATUS_INVALID_PARAMETER;
    }
    Bitmap->Map[x + (y * Bitmap->Width)] = Color;
    return STATUS_SUCCESS;
}

LOUSTATUS
BootVidBitmapPutPixel(
    PBOOTVID_BITMAP Bitmap,
    int             x,
    int             y,
    UINT8           R,
    UINT8           G,
    UINT8           B
){
    return BootVidBitmapPutPixelEx(
        Bitmap,
        x,y,
        SET_RGB(R,G,B)
    );  
}