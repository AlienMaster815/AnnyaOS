#include "../BootVid.h"

extern UINT32* Canvas;
extern INT32 Width;
extern INT32 Height;

void 
BootVidPlaceBitmap(
    PBOOTVID_BITMAP Bitmap,
    int             x,
    int             y
){
    int bHeight = Bitmap->Height;
    int bWidth = Bitmap->Width;
    UINT32* bMap = Bitmap->Map;
    for(int i = 0 ; i < bHeight; i++){
        memcpy(&Canvas[x + ((i + y) * Width)], &bMap[i * bWidth], bWidth * sizeof(UINT32));
    }
}