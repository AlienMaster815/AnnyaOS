#ifndef GDI_CORE_H
#define GDI_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef float FLOAT, * PFLOAT;

typedef struct _ABC{
    INTEGER     AbcA;
    UINT        AbcB;
    INTEGER     AbcC;
}ABC, * PABC;

typedef struct _ABC_FLOAT{
    FLOAT   AbcfA;
    FLOAT   AbcfB;
    FLOAT   AbcfC;
}ABC_FLOAT, ABCFLOAT, * PABC_FLOAT; 

#define MM_MAX_AXES_NAMELEN 16
#define MM_MAX_NUMAXES      16

typedef struct _AXIS_INFOA{
    LONG    AxMinValue;
    LONG    AxMaxValue;
    BYTE    AxAxisName[MM_MAX_AXES_NAMELEN];
}AXIS_INFOA, * PAXIS_INFOA;

typedef struct _AXIS_INFOW{
    LONG    AxMinValue;
    LONG    AxMaxValue;
    WCHAR   AxAxisName[MM_MAX_AXES_NAMELEN];
}AXIS_INFOW, * PAXIS_INFOW;

typedef struct _AXES_LISTA{
    DWORD           AxlReserved;
    DWORD           AxlNumAxes;
    AXIS_INFOA      AxlAxisInfo[MM_MAX_NUMAXES];
}AXES_LISTA, * PAXES_LISTA;

typedef struct _AXES_LISTW{
    DWORD           AxlReserved;
    DWORD           AxlNumAxes;
    AXIS_INFOW      AxlAxisInfo[MM_MAX_NUMAXES];
}AXES_LISTW, * PAXES_LISTW;

typedef struct _BITMAP{
    LONG        Type;
    LONG        Width;
    LONG        Height;
    LONG        WidthBytes;
    WORD        Planes;
    WORD        BitsPixel;
    PVOID       Bits;      
}BITMAP, * PBITMAP;

typedef struct _BITMAP_CORE_HEADER{
    DWORD       Size;
    WORD        Width;
    WORD        Height;
    WORD        Planes;
    WORD        BitCount;
}BITMAP_CORE_HEADER, * PBITMAP_CORE_HEADER;

typedef struct _RGB_TRIPLE{
    BYTE    Blue;
    BYTE    Green;
    BYTE    Red;
}RGB_TRIPLE, * PRGB_TRIPLE;

typedef struct _BITMAP_CORE_INFO{
    BITMAP_CORE_HEADER  Header;
    RGB_TRIPLE          Colors[1];
}BITMAP_CORE_INFO, * PBITMAP_CORE_INFO;


#define BITMAP_FILE_HEADER_TYPE "BM"

typedef struct _BITMAP_FILE_HEADER{
    WORD    Type;
    DWORD   Size;
    WORD    Reserved1;
    WORD    Reserved2;
    DWORD   OffBits;
}BITMAP_FILE_HEADER, * PBITMAP_FILE_HEADER;

typedef struct _RGB_QUAD{
    BYTE    Blue;
    BYTE    Green;
    BYTE    Red;
    BYTE    Reserved;
}RGB_QUAD, * PRGB_QUAD;

typedef struct _BITMAP_INFO_HEADER{
    DWORD       Size;
    LONG        Width;
    LONG        Height;
    WORD        Planes;
    WORD        BitCount;
    DWORD       Compression;
    DWORD       SizeImage;
    LONG        XPelsPerMeter;
    LONG        YPelsPErMeter;
    DWORD       ClrUsed;
    DWORD       ClrImportant;
}BITMAP_INFO_HEADER, * PBITMAP_INFO_HEADER;

typedef struct _BITMAP_INFO{
    BITMAP_INFO_HEADER      Header;
    RGB_QUAD                Colors[1];
}BITMAP_INFO, * PBITMAP_INFO;

typedef LONG FXPT2DOT30;

typedef struct _CIE_XYZ{
    FXPT2DOT30  X;
    FXPT2DOT30  Y;
    FXPT2DOT30  Z;
}CIE_XYZ, * PCIE_XYZ;

//this is represented as ICEXYZTRIPLE in the winapi reference
//manual tag i dont know if that is a type but for concistency
//im changing it to CIEXYZTRIPLE for the tag
typedef struct _CIE_XYZ_TRIPLE{
    CIE_XYZ     Red;
    CIE_XYZ     Green;
    CIE_XYZ     Blue;
}CIE_XYZ_TRIPLE, * PCIE_XYZ_TRIPLE;

typedef struct _BITMAP_V4_HEADER{
    DWORD           V4Size;
    LONG            V4Width;
    LONG            V4Height;
    WORD            V4Planes;
    WORD            V4BitCount;
    DWORD           V4V4Compression;
    DWORD           V4SizeImage;
    LONG            V4XPelsPerMeter;
    LONG            V4YPelsPerMeter;
    DWORD           V4ClrUsed;
    DWORD           V4ClrImportant;
    DWORD           V4RedMask;
    DWORD           V4GreenMask;
    DWORD           V4BlueMask;
    DWORD           V4AlphaMask;
    DWORD           V4CsType;
    CIE_XYZ_TRIPLE  V4Endpoints;
    DWORD           V4GammaRed;
    DWORD           V4GammaGreen;
    DWORD           V4GammaBlue;
}BITMAP_V4_HEADER, * PBITMAP_V4_HEADER;

typedef struct _BITMAP_V5_HEADER{
    DWORD           V5Size;
    LONG            V5Width;
    LONG            V5Height;
    WORD            V5Planes;
    WORD            V5BitCount;
    DWORD           V5Compresion;
    DWORD           V5SizeImage;
    LONG            V5C5XpelsPerMeter;
    LONG            V5C5YpelsPerMeter;
    DWORD           V5ClrUsed;
    DWORD           V5ClrImportant;
    DWORD           V5RedMask;
    DWORD           V5GreenMask;
    DWORD           V5BlueMask;
    DWORD           V5AlphaMask;
    DWORD           V5CsType;
    CIE_XYZ_TRIPLE  V5Endpoints;
    DWORD           V5GammaRed;
    DWORD           V5GammaGreen;
    DWORD           V5GammaBlue;
    DWORD           V5Intent;
    DWORD           V5ProfileData;
    DWORD           V5ProfileSize;
    DWORD           V5Reserved;
}BITMAP_V5_HEADER, * PBITMAP_V5_HEADER;

typedef struct _BLEND_FUNCTION{
    BYTE        BlendOp;
    BYTE        BlendFlags;
    BYTE        SourceConstantAlpha;
    BYTE        AlphaFormat;
}BLEND_FUNCTION, * PBLEND_FUNCTION;

typedef struct _COLOR_ADJUSTMENT{
    WORD        Size;
    WORD        Flags;
    WORD        IlluminentIndex;
    WORD        RedGamma;
    WORD        GreenGamma;
    WORD        BlueGamma;
    WORD        ReferenceBlack;
    WORD        ReferenceWhite;
    SHORT       Contrast;
    SHORT       Brightness;
    SHORT       Colorfulness;
    SHORT       GreenTint;
}COLOR_ADJUSTMENT, * PCOLOR_ADJUSTMENT;

typedef struct _DESIGN_VECTOR{
    DWORD   Reserved;
    DWORD   NumAxes;
    LONG    Values[MM_MAX_NUMAXES];
}DESIGN_VECTOR, * PDESIGN_VECTOR;

typedef struct _DIB_SECTION{
    BITMAP                  Bitmap;
    BITMAP_INFO_HEADER      InfoHeader;
    DWORD                   Bitfields[3];
    HANDLE                  Section;
    DWORD                   Offset;
}DIB_SECTION, * PDIB_SECTION;   

typedef struct _DISPLAY_DEVICEA{
    DWORD       StructSize;
    CHAR        DeviceName[32];
    CHAR        DeviceString[128];
    DWORD       StateFlags;
    CHAR        DeviceID[128];
    CHAR        DeviceKey[128];
}DISPLAY_DEVICEA, * PDISPLAY_DEVICEA;

typedef struct _DISPLAY_DEVICEW{
    DWORD       StructSize;
    WCHAR       DeviceName[32];
    WCHAR       DeviceString[128];
    DWORD       StateFlags;
    WCHAR       DeviceID[128];
    WCHAR       DeviceKey[128];
}DISPLAY_DEVICEW, * PDISPLAY_DEVICEW;

//DRAW_TEXT_PARAMS

#ifdef __cplusplus
}
#endif
#endif