#include "../BootVid.h"

void 
BootVidPlaceBitmap(
    PBOOTVID_BITMAP     Bitmap,
    int                 x,
    int                 y,
    PFB_BOOT_RENDERER   Renderer
){
    int bHeight = Bitmap->Height;
    int bWidth = Bitmap->Width;
    UINT32* bMap = Bitmap->Map;
    for(int i = 0 ; i < bHeight; i++){
        memcpy(&Renderer->Canvas[x + ((i + y) * (Renderer->Pitch / 4))], &bMap[i * bWidth], bWidth * sizeof(UINT32));
    }
}