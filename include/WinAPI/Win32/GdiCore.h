#ifndef GDI_CORE_H
#define GDI_CORE_H

#ifndef _USER_MODE_CODE_

    #ifndef __cplusplus
    #include <LouAPI.h>
    #else
    #include <LouDDK.h>
    extern "C" {
    #endif

#else

    #include <Annya.h>

    #ifdef __cplusplus
    extern "C" {
    #endif

#endif

typedef float FLOAT, * PFLOAT;

typedef struct _ABC{
    INTEGER     AbcA;
    UINT        AbcB;
    INTEGER     AbcC;
}ABC, * PABC, * LPABC, * NPABC;

typedef struct _ABC_FLOAT{
    FLOAT   AbcfA;
    FLOAT   AbcfB;
    FLOAT   AbcfC;
}ABC_FLOAT, ABCFLOAT, * PABC_FLOAT, 
    *PABCFLOAT, * NPABCFLOAT, * LPABCFLOAT; 

#define MM_MAX_AXES_NAMELEN 16
#define MM_MAX_NUMAXES      16

typedef struct _AXIS_INFO_A{
    LONG    AxMinValue;
    LONG    AxMaxValue;
    BYTE    AxAxisName[MM_MAX_AXES_NAMELEN];
}AXIS_INFO_A, * PAXIS_INFO_A, 
    AXISINFOA, * PAXISINFOA, *LPAXISINFOA;

typedef struct _AXIS_INFO_W{
    LONG    AxMinValue;
    LONG    AxMaxValue;
    WCHAR   AxAxisName[MM_MAX_AXES_NAMELEN];
}AXIS_INFO_W, * PAXIS_INFO_W, 
    AXISINFOW, * PAXISINFOW, *LPAXISINFOW;

typedef struct _AXES_LIST_A{
    DWORD           AxlReserved;
    DWORD           AxlNumAxes;
    AXIS_INFO_A     AxlAxisInfo[MM_MAX_NUMAXES];
}AXES_LIST_A, * PAXES_LIST_A,
    AXESLISTA, * PAXESLISTA, * LPAXESLISTA;

typedef struct _AXES_LIST_W{
    DWORD           AxlReserved;
    DWORD           AxlNumAxes;
    AXIS_INFO_W     AxlAxisInfo[MM_MAX_NUMAXES];
}AXES_LIST_W, * PAXES_LIST_W,
    AXESLISTW, * PAXESLISTW, * LPAXESLISTW;

typedef struct _BITMAP{
    LONG        Type;
    LONG        Width;
    LONG        Height;
    LONG        WidthBytes;
    WORD        Planes;
    WORD        BitsPixel;
    PVOID       Bits;      
}BITMAP, * PBITMAP, * NPBITMAP, * LPBITMAP;

typedef struct _BITMAP_CORE_HEADER{
    DWORD       Size;
    WORD        Width;
    WORD        Height;
    WORD        Planes;
    WORD        BitCount;
}BITMAP_CORE_HEADER, * PBITMAP_CORE_HEADER,
    BITMAPCOREHEADER, *  PBITMAPCOREHEADER, * LPBITMAPCOREHEADER;

typedef struct _RGB_TRIPLE{
    BYTE    Blue;
    BYTE    Green;
    BYTE    Red;
}RGB_TRIPLE, * PRGB_TRIPLE,
    RGBTRIPLE, * PRGBTRIPLE, 
    * LPRGBTRIPLE, * NPRGBTRIPLE;

typedef struct _BITMAP_CORE_INFO{
    BITMAP_CORE_HEADER  Header;
    RGB_TRIPLE          Colors[1];
}BITMAP_CORE_INFO, * PBITMAP_CORE_INFO,
    BITMAPCOREINFO, * PBITMAP_CORE_INFO, * LPBITMAP_CORE_INFO;


#define BITMAP_FILE_HEADER_TYPE "BM"

typedef struct _BITMAP_FILE_HEADER{
    WORD    Type;
    DWORD   Size;
    WORD    Reserved1;
    WORD    Reserved2;
    DWORD   OffBits;
}BITMAP_FILE_HEADER, * PBITMAP_FILE_HEADER,
    BITMAPFILEHEADER, * PBITMAPFILEHEADER, * LPBITMAPFILEHEADER;



#ifdef __cplusplus
}
#endif
#endif