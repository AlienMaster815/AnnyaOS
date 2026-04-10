#include "../BootVid.h"



LOUSTATUS 
BootVidCreateBitmap(
    PBOOTVID_BITMAP*    Bitmap,
    int                 Width,
    int                 Height
){
    if((!Bitmap) || (!Width) || (!Height)){
        return STATUS_INVALID_PARAMETER;
    }

    *Bitmap = LouKeMallocType(BOOTVID_BITMAP, KERNEL_GENERIC_MEMORY);
    if(!(*Bitmap)){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    (*Bitmap)->Map = LouKeMallocArray(UINT32, Width * Height, KERNEL_GENERIC_MEMORY);
    if(!((*Bitmap)->Map)){
        LouKeFree(*Bitmap);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    (*Bitmap)->Width = Width;
    (*Bitmap)->Height = Height;

    return STATUS_SUCCESS;
}

void 
BootVidDestroyBitmap(
    PBOOTVID_BITMAP Bitmap
){
    LouKeFree(Bitmap->Map);
    LouKeFree(Bitmap);
}

void 
BootVidTrimBitmap(
    PBOOTVID_BITMAP Bitmap,
    UINT32          Background
){
    int MaxX = -1;
    int MaxY = -1;

    for(size_t i = 0; i < Bitmap->Height; i++){
        for(size_t j = 0 ; j < Bitmap->Width; j++){
            if(Bitmap->Map[j + (i * Bitmap->Width)] != Background){
                if ((int)j > MaxX) MaxX = (int)j;
                if ((int)i > MaxY) MaxY = (int)i;
            }
        }
    }

    if (MaxX == -1 || MaxY == -1) return;

    int NewWidth = MaxX + 1;
    int NewHeight = MaxY + 1;

    UINT32* bMap = LouKeMallocArray(UINT32, NewWidth * NewHeight, KERNEL_GENERIC_MEMORY);
    if (!bMap) return;
    for(int i = 0 ; i < NewHeight; i++){
        memcpy(&bMap[i * NewWidth], &Bitmap->Map[i * Bitmap->Width], NewWidth * sizeof(UINT32));
    }
    LouKeFree(Bitmap->Map);
    Bitmap->Map = bMap;
    Bitmap->Width = NewWidth;
    Bitmap->Height = NewHeight;
}
