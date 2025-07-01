#include "Bmp.h"

CODECS_API 
HANDLE 
AnnyaOpenBmpA(
    string FileName
){
    FILE* NewBmp = LouOpenFileA(FileName);

    PBITMAP_HANDLE MapHandle = 0x00;
    PBITMAP_FILE_HEADER BitmapFile = (PBITMAP_FILE_HEADER)NewBmp;
    PBITMAP_INFORMATION_HEADER BIH = (PBITMAP_INFORMATION_HEADER)((uint64_t)NewBmp + sizeof(BITMAP_FILE_HEADER));
    
    LouPrint("File Size:%h\n", BitmapFile->BFSize);
    LouPrint("Pixel Data Offset:%h\n", BitmapFile->BFOffBits);

    LouPrint("BMP Width:%d\n",  BIH->BIWidth);
    LouPrint("BMP Height:%d\n", BIH->BIHeight);
    LouPrint("BMP BPP:%d\n",    BIH->BIBpp);

    uint8_t* PixelData = (uint8_t*)((uint64_t)NewBmp + (uint64_t)BitmapFile->BFOffBits);

    MapHandle = LouGlobalUserMallocType(BITMAP_HANDLE);

    MapHandle->Width = BIH->BIWidth;
    MapHandle->Height = BIH->BIHeight;
    MapHandle->Bpp = BIH->BIBpp;
    MapHandle->UnpackedData = (void*)PixelData;
    MapHandle->FileHandle = NewBmp;
    MapHandle->FileEnd = (uint64_t)NewBmp + (uint64_t)BitmapFile->BFSize;
    
    return AnnyaCodecsCreateHandle(IMAGE_HANDLE, BMP, MapHandle);
}