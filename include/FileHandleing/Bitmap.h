#ifndef _BITMAP_H_
#define _BITMAP_H_

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#ifndef _USER_MODE_CODE_
#include <LouAPI.h>
#else 
typedef void* FILE;
#endif
#endif

#pragma pack(push, 1)
typedef struct _BITMAP_FILE_HEADER{
    uint16_t BFType;
    uint32_t BFSize;
    uint16_t BFReserved1;
    uint16_t BFReserved2;
    uint32_t BFOffBits;
}BITMAP_FILE_HEADER, * PBITMAP_FILE_HEADER;

typedef struct _BITMAP_INFORMATION_HEADER{
    uint32_t BISize;
    int32_t  BIWidth;
    int32_t  BIHeight;
    uint16_t BIPlanes;
    uint16_t BIBpp;
    uint32_t BICompression;
    uint32_t BISizeImage;
    int32_t  BIXPelsPerMeter;
    int32_t  BIYPelsPerMeter;
    uint32_t BIClrUsed;
    uint32_t BIImpClrUsed;
}BITMAP_INFORMATION_HEADER, * PBITMAP_INFORMATION_HEADER;
#pragma pack(pop)

typedef struct _BITMAP_HANDLE{
    uint8_t* UnpackedData;
    uint64_t FileEnd;
    uint16_t Height;
    uint16_t Width;
    uint16_t Bpp;
    FILE* FileHandle;
}BITMAP_HANDLE, * PBITMAP_HANDLE;


PBITMAP_HANDLE LouKeOpenBitmapImage(string FilePath);
void LouKeDrsdDrawBitMap(PBITMAP_HANDLE BitmapHandle, int64_t x, int64_t y);

#include "png.h"


#ifdef __cplusplus
}
#endif

#endif