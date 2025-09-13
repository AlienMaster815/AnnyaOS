#ifndef _ANNYA_GDI32_H
#define _ANNYA_GDI32_H

typedef float FLOAT;
typedef wchar_t WCHAR;

typedef UINT32 COLORREF, * PCOLORREF, * LPCOLORREF;

#define CALLBACK __stdcall

typedef struct _ABCFLOAT{
    FLOAT   AbcfA;
    FLOAT   AbcfB;
    FLOAT   AbcfC;
}ABCFLOAT, * PABCFLOAT, * LPABCFLOAT;

#define FONTMAPPER_MAX 10

typedef struct _KERNINGPAIR{
    WORD    First;
    WORD    Second;
    INT32   KernAmount; 
}KERNINGPAIR, * PKERNINGPAIR, * LPKERNINGPAIR;

typedef struct PIXEL_FORMAT_DESCRIPTOR{
    WORD    Size;
    WORD    Version;
    DWORD   Flags;
    BYTE    PixelType;
    BYTE    ColorBits;
    BYTE    RedBits;
    BYTE    RedShift;
    BYTE    GreenBits;
    BYTE    GreenShift;
    BYTE    BlueBits;
    BYTE    BlueShift;
    BYTE    AlphaBits;
    BYTE    AlphaShift;
    BYTE    AccumBits;
    BYTE    AccumRedBits;
    BYTE    AccumRedShift;
    BYTE    AccumGreenBits;
    BYTE    AccumGreenShift;
    BYTE    AccumBlueBits;
    BYTE    AccumBlueShift;
    BYTE    AccumAlphaBits;
    BYTE    AccumAlphaShift;
    BYTE    DepthBits;
    BYTE    StenciBits;
    BYTE    AuxilleryBuffers;
    BYTE    LayerType;
    BYTE    Reserved;
    DWORD   LayerMask;
    DWORD   VisableMask;
    DWORD   DamageMask;
}PIXEL_FORMAT_DESCRIPTOR, * PPIXEL_FORMAT_DESCRIPTOR, * LPPIXEL_FORMAT_DESCRIPTOR;

#define PFD_TYPE_RGBA       0
#define PFD_TYPE_COLORINDEX 1

#define PFD_MAIN_PLANE      0
#define PFD_OVERLAY_PLANE   1
#define PFD_UNDERLAY_PLANE  (-1)

#define PFD_DOUBLE_BUFFER                   (1ULL)
#define PFD_STEREO                          (1ULL << 1)
#define PFD_DRAW_TO_WINDOW                  (1ULL << 2)
#define PFD_DRAW_TO_BITMAP                  (1ULL << 3)
#define PFD_SUPPORT_GDI                     (1ULL << 4)
#define PFD_SUPPORT_OPENGL                  (1ULL << 5)
#define PFD_GENERIC_FORMAT                  (1ULL << 6)
#define PFD_NEED_PALLETE                    (1ULL << 7)
#define PFD_NEED_SYSTEM_PALLETE             (1ULL << 8)
#define PFD_SWAP_EXCHANGE                   (1ULL << 9)
#define PFD_SWAP_COPY                       (1ULL << 10)
#define PFD_SWAP_LAYER_BUFFERS              (1ULL << 11)
#define PFD_GENERIC_ACCELERATED             (1ULL << 12)
#define PFD_SUPPORT_COMPOSITION             (1ULL << 15)

#define PFD_DEPTH_DONT_CARE                 (1ULL << 29)
#define PFD_DEPTH_DOUBLE_BUFFER_DONT_CARE   (1ULL << 30)
#define PFD_STEREO_DONT_CARE                (1ULL << 31)

typedef int16_t INT16, SHORT;

typedef struct _COLOR_ADJUSTMENT{
    WORD        Size;
    WORD        Flags;
    WORD        IluminantIndex;
    WORD        RedGamma;
    WORD        GreenGamma;
    WORD        BlueGamma;
    WORD        ReferenceBlack;
    WORD        ReferenceWhite;
    SHORT       Contrast;
    SHORT       Colorfullness;
    SHORT       RedGreenTint;
}COLOR_ADJUSTMENT, * PCOLOR_ADJUSTMENT, * LPCOLOR_ADJUSTMENT;

#define CA_NEGATIVE     1
#define CA_LOG_FILTER   2

#define ILLUMINANT_DEVICE_DEFAULT   0
#define ILLUMINANT_A                1
#define ILLUMINANT_B                2
#define ILLUMINANT_C                3
#define ILLUMINANT_D50              4
#define ILLUMINANT_D55              5
#define ILLUMINANT_D65              6
#define ILLUMINANT_D75              7
#define ILLUMINANT_F2               8
#define ILLUMINANT_MAX_INDEX        ILLUMINANT_F2

#define ILLUMINANT_TUNGSTEN         ILLUMINANT_A
#define ILLUMINANT_DAYLIGHT         ILLUMINANT_C
#define ILLUMINANT_FLOURSCENT       ILLUMINANT_F2
#define ILLUMINANT_NTSC             ILLUMINANT_C

#define RGB_GAMMA_MIN               ((WORD)2500)
#define RGB_GAMMA_MAX               ((WORD)65000)

#define REFERENCE_WHITE_MIN         ((WORD)6000)
#define REFERENCE_WHITE_MAX         ((WORD)10000)
#define REFERENCE_BLACK_MIN         ((WORD)0)
#define REFERENCE_BLACK_MAX         ((WORD)4000)

#define COLOR_ADJ_MIN               ((SHORT)-100)
#define COLOR_ADJ_MAX               ((SHORT)100)

typedef long FXPT16DOT16, * PFXPT16DOT16, * LPFXPT16DOT16;
typedef long FXPT2DOT30, * PFXPT2DOT30, * LPFXPT2DOT30; 
typedef long LCSCSTYPE;
typedef long LCSGAMUTMATCH;

#define LCS_sRGB                        0x73524742
#define LCS_WINDOWS_COLOR_SPACE         0x57696E20

#define LCS_CALIBRATED_RGB              0x00000000L
#define LCS_DEVICE_RGB                  0x00000001L
#define LCS_DEVICE_CMYK                 0x00000002L

#define LCS_GM_BUISINESS                0x00000001L
#define LCS_GM_GRAPHICS                 0x00000002L
#define LCS_GM_IMAGES                   0x00000003L

#define CM_OUT_OF_GAMUT                 255
#define CM_IN_GAMUT                     0

typedef struct _CIEXYZ{
    PFXPT2DOT30     CieXyzX;
    PFXPT2DOT30     CieXyzY;
    PFXPT2DOT30     CieXyzZ;
}CIEXYZ, * PCIEXYZ, * LPCIEXYZ;

typedef struct _CIEXYZTRIPPLE{
    CIEXYZ          CieXyzR;
    CIEXYZ          CieXyzG;
    CIEXYZ          CieXyzB;
}CIEXYZTRIPPLE, * PCIEXYZTRIPPLE, * LPCIEXYZTRIPPLE;

typedef struct _LOGCOLORSPACEA{
    DWORD           Signature;
    DWORD           Version;
    DWORD           Size;
    LCSCSTYPE       CsType;
    LCSGAMUTMATCH   Intent;
    CIEXYZTRIPPLE   Endpoints;
    DWORD           GammaR;
    DWORD           GammaG;
    DWORD           GammaB;
    CHAR            FileName[256];
}LOGCOLORSPACEA, * PLOGCOLORSPACEA, * LPLOGCOLORSPACEA;

typedef struct _LOGCOLORSPACEW{
    DWORD           Signature;
    DWORD           Version;
    DWORD           Size;
    LCSCSTYPE       CsType;
    LCSGAMUTMATCH   Intent;
    CIEXYZTRIPPLE   Endpoints;
    DWORD           GammaR;
    DWORD           GammaG;
    DWORD           GammaB;
    WCHAR            FileName[256];
}LOGCOLORSPACEW, * PLOGCOLORSPACEW, * LPLOGCOLORSPACEW;

#define DC_FEILDS               1
#define DC_PAPERS               2
#define DC_PAPER_SIZE           3
#define DC_MIN_EXTENT           4
#define DC_MAX_EXTENT           5
#define DC_BINS                 6
#define DC_DUPLEX               7
#define DC_SIZE                 8
#define DC_EXTRA                9
#define DC_VERSION              10
#define DC_DRIVER               11
#define DC_BIN_NAMES            12
#define DC_ENUM_RESOLUTIONS     13
#define DC_FILE_DEPENDENCIES    14
#define DC_TRUE_TYPE            15
#define DC_PAPER_NAMES          16
#define DC_ORIENTATION          17
#define DC_COPIES               18
#define DC_BIN_ADJUST           19
#define DC_EMF_COMPLIANT        20
#define DC_DATA_TYPE_PRODUCED   21
#define DC_COLLATE              22
#define DC_MANUFACTURER         23
#define DC_MODEL                24
#define DC_PERSONALITY          25
#define DC_PRINT_RATE           26
#define DC_PRINT_RATE_UNIT      27
#define DC_PRINTER_MEM          28
#define DC_MEDIA_READY          29
#define DC_STAPLE               30
#define DC_PRINT_RATME_PPM      31
#define DC_COLOR_DEVICE         32
#define DC_NUP                  33
#define DC_MEDIA_TYPE_NAMES     34
#define DC_MEDIA_TYPES          35

#define DCTT_BITMAP             0x00000001L
#define DCTT_DOWNLOAD           0x00000002L
#define DCTT_SUBDEV             0x00000004L
#define DCTT_DOWNLOAD_OUTLINE   0x00000008L

#define DCBA_FACE_UPNOTE        0x0000
#define DCBA_FACE_UPCENTER      0x0001
#define DCBA_FACE_UPLEFT        0x0002
#define DCBA_FACE_UPRIGHT       0x0003
#define DCBA_FACE_DOWNNONE      0x0100
#define DCBA_FACE_DOWNCENTER    0x0101
#define DCBA_FACE_DOWNLEFT      0x0102
#define DCBA_FACE_DOWNRIGHT     0x0103

#define PRINT_RATE_UNIT_PPL     1     
#define PRINT_RATE_UNIT_CPS     2
#define PRINT_RATE_UNIT_LPM     3
#define PRINT_RATE_UNIT_IPM     4

#define QDI_SET_DI_BITS     1
#define QDI_GET_DI_BITS     2
#define QDI_DIB_TO_SCREEN   4
#define QDI_STRETCH_DIB     5

#define NEWFRAME            1
#define ABORTDOC            2
#define NEXTBAND            3
#define SETCOLORTABLE       4
#define GETCOLORTABLE       5
#define FLUSHOUTPUT         6
#define DRAFTMODE           7
#define QUERYESCSUPPORT     8
#define SETABORTPROC        9
#define STARTDOC            10
#define ENDDOC              11
#define GETPHYSPAGESIZE     12
#define GETPRINTINGOFFSET   13
#define GETSCALINGFACTOR    14
#define MFCOMMENT           15
#define GETPENWIDTH         16
#define SETCOPYCOUNT        17
#define SELECTPAPERSOURCE   18
#define DEVICEDATA          19
#define GETTECHNOLGY        20
#define GETTECHNOLOGY       GETTECHNOLGY
#define SETLINECAP          21
#define SETLINEJOIN         22
#define SETMITERLIMIT       23
#define BANDINFO            24
#define DRAWPATTERNRECT     25
#define GETVECTOROPENSIZE   26
#define GETVECTORBRUSHSIZE  27
#define ENABLEDUPLEX        28
#define GETSETPAPERBINS     29
#define GETSETPRINTORIENT   30
#define ENUMPAPERBINS       31
#define SETDIBSCALING       32
#define EPSPRINTING         33
#define ENUMPAPERMETRICS    34
#define GETSETPAPERMETRICS  35
#define POSTSCRIPT_DATA     37
#define POSTSCRIPT_IGNORE   38
#define MOUSETRAILS         39
#define GETDEVICEUNITS      42

#define GETEXTENDEDTEXTMETRICS      256
#define GETEXTENTTABLE              257
#define GETPAIRKERNTABLE            258
#define GETTRACKKERNTABLE           259
#define EXTTEXTOUT                  512
#define GETFACENAME                 513
#define DOWNLOAD_FACE               514
#define ENABLERELATIVEWIDTHS        768
#define ENABLEPAIRKERNING           769
#define SETKERNTRACK                770
#define SETALLJUSTVALUES            771
#define SETCHARSET                  772

#define STRETCHBLT                  2048
#define GETSETSCREENPARAMS          3072
#define QUERYDIBSUPPORT             4096
#define CLIP_TO_PATH                4097
#define END_PATH                    4098
#define EXT_DEVICE_CAPS             4099
#define RESTORE_CTM                 4100
#define SAVE_CTM                    4101
#define SET_ARC_DIRECTION           4102
#define SET_BACKGROUND_COLOR        4103
#define SET_POLY_MODE               4104
#define SET_SCREEN_ANGLE            4105
#define SET_SPREAD                  4106
#define TRANSFORM_CTM               4107
#define SET_CLIP_BOX                4108
#define SET_BOUNDS                  4109
#define SET_MIRROR_MODE             4110
#define OPENCHANNEL                 4110
#define DOWNLOAD_HEADER             4111
#define CLOSECHANNEL                4112
#define POSTSCRIPT_PASSTHROUGH      4115
#define ENCAPSULATE_POSTSCRIPT      4116
#define POSTSCRIPT_IDENTIFY         4117
#define POSTSCRIPT_INJECTION        4118
#define CHECKJPEGFORMAT             4119
#define CHECKPNGFORMAT              4120
#define GET_PS_FEATURESETTING       4121
#define GDIPLUS_TS_QUERYVER         4122
#define GDIPLUS_TS_RECORD           4123

#define PSIDENT_GDICENTRIC  0
#define PSIDENT_PSCENTRIC   1

#define QDI_SETDIBITS       1
#define QDI_GETDIBITS       2
#define QDI_DIBTOSCREEN     4
#define QDI_STRETCHDIB      8

#define SP_NOTEREPORTED     0x4000
#define SP_ERROR            (-1)
#define SP_APPABORT         (-2)
#define SP_USERABORT        (-3)
#define SP_OUTOFDISK        (-4)
#define SP_OUTOFMEMORY      (-5)

#define PR_JOBSTATUS 0

#define R2_BLOCK        1
#define R2_NOTMERGEPEN  2
#define R2_MASKNOTPEN   3
#define R2_NOTCOPYPEN   4
#define R2_MASKPENNOT   5
#define R2_NOT          6
#define R2_XORPEN       7
#define R2_NOTMASKPEN   8
#define R2_MASKPEN      9
#define R2_NOTXORPEN    10
#define R2_NOP          11
#define R2_MERGENOTPEN  12
#define R2_COPYPEN      13
#define R2_MERGEPENNOT  14
#define R2_MERGEPEN     15
#define R2_WHITE        16
#define R2_LAST         16

#define MAKEROP4(Fore, Back)     (DWORD)((((Back) << 8) & (0xFF000000)) | (Fore))

#define SRCCOPY     0x00CC0020
#define SRCPAINT    0x00EE0086
#define SRCAND      0x008800C6
#define SRCINVERT   0x00660046
#define SRCERASE    0x00440328
#define NOTSRCCOPY  0x00330008
#define NOTSRCERASE 0x001100A6
#define MERGECOPY   0x00C000CA
#define MERGEPAINT  0x00BB0226
#define PATCOPY     0x00F00021
#define PATPAINT    0x00FB0A09
#define PATINVERT   0x005A0049
#define DSTINVERT   0x00550009
#define BLACKNESS   0x00000042
#define WHITENESS   0x00FF0062

#define BLACKONWHITE        1
#define WHITEONBLACK        2
#define COLORONCOLOR        3
#define HALFTONE            4
#define MAXSTRETCHBLTMODE   4

#define STRETCH_ANDSCANS    BLACKONWHITE
#define STRETCH_ORSCANS     WHITEONBLACK
#define STRETCH_DELETESCANS COLORONCOLOR
#define STRETCH_HALFTONE    HALFTONE

#define RGB(r,g,b)          ((COLORREF)((BYTE)(r) | ((BYTE)g << 8) | ((BYTE)b << 16)))
#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
#define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (WORD)(i)))
#define GetRValue(rgb)      ((BYTE)rgb & 0xFF)
#define GetGValue(rgb)      ((BYTE)(rgb >> 8))
#define GetBValue(rgb)      ((BYTE)(rgb >> 16))

#define GetKValue(cmyk)     ((BYTE)cmyk & 0xFF)
#define GetYValue(cmyk)     ((BYTE)(cmyk >> 8))
#define GetMValue(cmyk)     ((BYTE)(cymk >> 16))
#define GetCValue(cmyk)     ((BYTE)(cymk >> 24))

#define CMYK(c,m,y,k)       ((COLORREF)((((BYTE)(k)|((WORD)((BYTE)(y))  <<    8))|(((DWORD)(BYTE)(m)) <<   16))|(((DWORD)(BYTE)(c))   <<  24)))

typedef int (CALLBACK *ICMENUMPROCA)(LPSTR FileName, LPARAM Param);
typedef int (CALLBACK *ICMENUMPROCW)(LPWSTR FileName, LPARAM Param);

#define ICM_OFF     1
#define ICM_ON      2
#define ICM_QUERY   3

#define DCB_RESET       0x0001
#define DCB_ACCUMULATE  0x0002
#define DCB_DIRTY       DCB_ACCUMULATE
#define DCB_SET         (DCB_RESET | DCB_ACCUMULATE)
#define DCB_ENABLE      0x0004
#define DCV_DISABLE     0x0008

typedef struct _PELARRAY{
    LONG XCount;
    LONG YCount;
    LONG XExt;
    LONG YExt;
    BYTE Rgbs;
}PELARRAY, * PPELARRAY, * LPPELARRAY;

typedef struct _BITMAP{
    int     Type;
    int     Width;
    int     Height;
    int     WidthBytes;
    WORD    Planes;
    WORD    PixelBits;
    LPVOID  Data;
}BITMAP, * PBITMAP, * LPBITMAP;

typedef struct _BITMAP_CORE_HEADER{
    DWORD   Size;
    WORD    Width;
    WORD    Height;
    WORD    Planes;
    WORD    BitCount;
    
}BITMAP_CORE_HEADER, * PBITMAP_CORE_HEADER, 
    BITMAPCOREHEADER, *PBITMAPCOREHEADER, * LPBITMAPCOREHEADER;

typedef struct _RGB_TRIPLE{
    BYTE Blue;
    BYTE Green;
    BYTE Red;
}RGB_TRIPLE, PRGB_TRIPLE,
    RGBTRIPLE, *PRGBTRIPLE, *LPRGBTRIPLE; 

typedef struct _BITMAP_CORE_INFO{
    BITMAP_CORE_HEADER  Header;
    RGB_TRIPLE          Colors[1];
}BITMAP_CORE_INFO, *PBITMAP_CORE_INFO, 
    BITMAPCOREINFO, * PBITMAPCOREINFO, * LPBITMAPCOREINFO;

typedef struct _RGB_QUAD{
    BYTE Blue;
    BYTE Green;
    BYTE Red;
    BYTE Reserved;
}RGB_QUAD, * PRGB_QUAD,
    RGBQUAD, * PRGBQUAD, * LPRGBQUAD;

typedef struct _BITMAP_INFO_HEADER{
    DWORD   Size;
    LONG    Width;
    LONG    Height;
    WORD    Planes;
    WORD    BitCount;
    DWORD   Compression;
    DWORD   ImageSize;
    LONG    XPixelsPerMeter;
    LONG    YPixelsPerMeter;
    DWORD   ClrUsed;
    DWORD   ClrImportant;
}BITMAP_INFO_HEADER, * PBITMAP_INFO_HEADER,
    BITMAPINFOHEADER, * PBITMAPINFOHEADER, * LPBITMAPINFOHEADER;



typedef struct _BITMAP_INFO{
    BITMAP_INFO_HEADER  Header;
    RGB_QUAD            Colors[1];
}BITMAP_INFO, * PBITMAP_INFO,
    BITMAPINFO,* PBITMAPINFO, * LPBITMAPINFO; 



typedef struct _LOGBRUSH32{
    unsigned int    Style;
    COLORREF        Color;
    ULONG           Hatch;
}LOGBRUSH32, * PLOGBRUSH32;

typedef struct _LOGBRUSH{
    unsigned int    Style;
    COLORREF        Color;
    UINTPTR         Hatch;
}LOGBRUSH, * PLOGBRUSH;

typedef struct _BRUSH{
    //logbrush 32 can encapsulate the 64 bit 
    //version as long as we do le to cpu later
    LOGBRUSH        LogBrush; 
}BRUSH, * HBRUSH;

typedef struct _BLEND_FUNCTION{
    BYTE    BlendOperation;
    BYTE    BlendFlags;
    BYTE    SourceConstantAlpha;
    BYTE    AlphaFormat;
}BLEND_FUNCTION, * PBLEND_FUNCTION,
    BLENDFUNCTION, * PBLENDFUNCTION, * LPBLENDFUNCTION;


#define BS_DIBPATTERN       
#define BS_DIBPATTERN8X8    8
#define BS_DIBPATTERNPT     6
#define BS_HATCHED          2
#define BS_HOLLOW           1
#define BS_NULL             1
#define BS_PATTERN          3
#define BS_PATTERN8X8       7
#define BS_SOLID            0
#define BS_MONOPATTERN      9

#define HS_HROIZONTAL       0
#define HS_VERTICAL         1
#define HS_FDIAGONAL        2
#define HS_BDIAGONAL        3 
#define HS_CROSS            4
#define HS_DIAGCROSS        5
#define HS_API_MAX          12

#define MM_MAX_NUMAXES          16
#define MM_MAX_AXES_NAMELEN     MM_MAX_NUMAXES

typedef struct _AXISINFOA{
    LONG        MinValue;
    LONG        MaxValue;
    WCHAR       AxisName[MM_MAX_AXES_NAMELEN];
}AXISINFOA, * PAXISINFOA, * LPAXISINFOA;

typedef struct _AXISINFOW{
    LONG        MinValue;
    LONG        MaxValue;
    BYTE        AxisName[MM_MAX_AXES_NAMELEN];
}AXISINFOW, * PAXISINFOW, * LPAXISINFOW;

typedef struct _AXESLISTA{
    DWORD       Reserved;
    DWORD       AxesCount;
    AXISINFOA   AxisInfo[MM_MAX_NUMAXES];
}AXESLISTA, * PAXESLISTA, * LPAXESLISTA;

typedef struct _AXESLISTW{
    DWORD       Reserved;
    DWORD       AxesCount;
    AXISINFOW   AxisInfo[MM_MAX_NUMAXES];
}AXESLISTW, * PAXESLISTW, * LPAXESLISTW;

typedef HANDLE HDC;
typedef HANDLE HENHMETAFILE;
typedef HANDLE HMETAFILE;
typedef HANDLE HRGN;

typedef struct _XFORM{
    FLOAT Em11;
    FLOAT Em12;
    FLOAT Em21;
    FLOAT Em22;
    FLOAT Dx;
    FLOAT Dy;
}XFORM, * PXFORM, * LPXFORM;

typedef HANDLE HBITMAP;

#define CCHDEVICENAME   16
#define CCHFORMNAME     16

typedef HANDLE HGLOBAL;

typedef struct _DEVICE_MODEA{
    BYTE    DeviceName[CCHDEVICENAME];
    WORD    SpecVersion;
    WORD    DriverVersion;
    WORD    Size;
    WORD    DriverExtra;
    DWORD   Fields;
    union{
        struct {
            SHORT Orientation;
            SHORT PaperSize;
            SHORT PaperLength;
            SHORT PaperWidth;
            SHORT Scale;
            SHORT Copies;
            SHORT DefaultSource;
            SHORT PrintQuality;
        };
        struct {
            POINT Position;
            DWORD DisplayOrientation;
            DWORD DispalyFixedOutput;
        };
    };
    SHORT   Color;
    SHORT   Duplex;
    SHORT   YResolution;
    SHORT   TTOption;
    SHORT   Collate;
    BYTE    FormName[CCHFORMNAME];
    WORD    LogPixels;
    DWORD   Bpp;
    DWORD   PelsWidth;
    DWORD   PelsHeight;
    union {
        DWORD   DisplayFlags;
        DWORD   Nup;
    };  
    DWORD   DisplayFrequency;
    DWORD   ICMMethod;
    DWORD   ICMIntent;
    DWORD   MediaType;
    DWORD   DitherType;
    DWORD   Reserved1;
    DWORD   Reserved2;
    DWORD   PanningWidth;
    DWORD   PanningHeight;
}DEVICE_MODEA, * PDEVICE_MODEA,
    DEVICEMODEA, * PDEVICEMODEA, * LPDEVICEMODEA,
        DEVMODEA, * PDEVMODEA, * LPDEVMODEA; 



typedef struct _DEVICE_MODEW{
    WCHAR    DeviceName[CCHDEVICENAME];
    WORD    SpecVersion;
    WORD    DriverVersion;
    WORD    Size;
    WORD    DriverExtra;
    DWORD   Fields;
    union{
        struct {
            SHORT Orientation;
            SHORT PaperSize;
            SHORT PaperLength;
            SHORT PaperWidth;
            SHORT Scale;
            SHORT Copies;
            SHORT DefaultSource;
            SHORT PrintQuality;
        };
        struct {
            POINT Position;
            DWORD DisplayOrientation;
            DWORD DispalyFixedOutput;
        };
    };
    SHORT   Color;
    SHORT   Duplex;
    SHORT   YResolution;
    SHORT   TTOption;
    SHORT   Collate;
    WCHAR   FormName[CCHFORMNAME];
    WORD    LogPixels;
    DWORD   Bpp;
    DWORD   PelsWidth;
    DWORD   PelsHeight;
    union {
        DWORD   DisplayFlags;
        DWORD   Nup;
    };  
    DWORD   DisplayFrequency;
    DWORD   ICMMethod;
    DWORD   ICMIntent;
    DWORD   MediaType;
    DWORD   DitherType;
    DWORD   Reserved1;
    DWORD   Reserved2;
    DWORD   PanningWidth;
    DWORD   PanningHeight;
}DEVICE_MODEW, * PDEVICE_MODEW,
    DEVICEMODEW, * PDEVICEMODEW, * LPDEVICEMODEW,
        DEVMODEW, * PDEVMODEW, * LPDEVMODEW; 

typedef HANDLE HRGN;
typedef HANDLE HFONT;

#define LF_FACESIZE     32
#define LF_FULLFACESIZE 256

typedef struct _LOGFONTA{
    LONG    Height;
    LONG    Width;
    LONG    Escapement;
    LONG    Orientation;
    LONG    Weight;
    BYTE    Italic;
    BYTE    Underline;
    BYTE    StrikeOut;
    BYTE    CharSet;
    BYTE    OutPrecision;
    BYTE    ClipPercision;
    BYTE    Quality;
    BYTE    PitchAndFamily;
    CHAR    FaceName[LF_FACESIZE];
}LOGFONTA, * PLOGFONTA, * LPLOGFONTA, * NPLOGFONTA;

typedef struct _LOGFONTW{
    LONG    Height;
    LONG    Width;
    LONG    Escapement;
    LONG    Orientation;
    LONG    Weight;
    BYTE    Italic;
    BYTE    Underline;
    BYTE    StrikeOut;
    BYTE    CharSet;
    BYTE    OutPrecision;
    BYTE    ClipPercision;
    BYTE    Quality;
    BYTE    PitchAndFamily;
    WCHAR   FaceName[LF_FACESIZE];
}LOGFONTW, * PLOGFONTW, * LPLOGFONTW, * NPLOGFONTW;

typedef struct _ENUMLOGFONTA{
    LOGFONTA    LogFont;
    CHAR        FullName[LF_FULLFACESIZE];
    CHAR        Style[LF_FACESIZE];
}ENUMLOGFONTA, * PENUMLOGFONTA, * LPENUMLOGFONTA, * NPENUMLOGFONTA;

typedef struct _ENUMLOGFONTW{
    LOGFONTW    LogFont;
    WCHAR       FullName[LF_FULLFACESIZE];
    WCHAR       Style[LF_FACESIZE];
}ENUMLOGFONTW, * PENUMLOGFONTW, * LPENUMLOGFONTW, * NPENUMLOGFONTW;

typedef struct _ENUMLOGFONTEXA{
    LOGFONTA    LogFont;
    CHAR        Style[LF_FACESIZE];
    CHAR        Script[LF_FACESIZE];
}ENUMLOGFONTEXA, * PENUMLOGFONTEXA, * LPENUMLOGFONTEXA, * NPENUMLOGFONTEXA;

typedef struct _ENUMLOGFONTEXW{
    LOGFONTA    LogFont;
    CHAR        Style[LF_FACESIZE];
    CHAR        Script[LF_FACESIZE];
}ENUMLOGFONTEXW, * PENUMLOGFONTEXW, * LPENUMLOGFONTEXW, * NPENUMLOGFONTEXW;

typedef struct _DESIGNVECTOR{
    DWORD   Reserved;
    DWORD   NumAxes;
    LONG    Value[MM_MAX_NUMAXES];
}DESIGNVECTOR, * PDESIGNVECTOR, * LPDESIGNVECTOR, * NDESIGNVECTOR;

typedef struct _ENUMLOGFONTEXDVA{
    ENUMLOGFONTEXA  LogFontEx;
    DESIGNVECTOR    DesignVector;
}ENUMLOGFONTEXDVA, * PENUMLOGFONTEXDVA, * LPENUMLOGFONTEXDVA, * NPENUMLOGFONTEXDVA;

typedef struct _ENUMLOGFONTEXDVW{
    ENUMLOGFONTEXW  LogFontEx;
    DESIGNVECTOR    DesignVector;
}ENUMLOGFONTEXDVW, * PENUMLOGFONTEXDVW, * LPENUMLOGFONTEXDVW, * NPENUMLOGFONTEXDVW;

typedef HANDLE HPALETTE;

typedef struct _PALETTEENTRY{
    BYTE    Red;
    BYTE    Green;
    BYTE    Blue;
    BYTE    Flags;
}PALETTEENTRY, * PPALETTEENTRY, * LPPALETTEENTRY, * NPPALETTEENTRY;

typedef struct _LOGPALETTE{
    WORD            Version;
    WORD            NumEntries;
    PALETTEENTRY    PaletteEntry;
}LOGPALETTE, * PLOGPALETTE, * LPLOGPALETTE, * NPLOGPALETTE;

typedef HANDLE HPEN;

typedef struct _LOGPEN{
    UINT32      Style;
    POINT       Width;
    COLORREF    Color;
}LOGPEN, * PLOGPEN, * LPLOGPEN, * NPLOGPEN;

typedef HANDLE HGDIOBJ;

typedef struct _DIBSECTION{
    BITMAP              Ditmap;
    BITMAP_INFO_HEADER  InfoHeader;
    DWORD               BitFields[3];
    HANDLE              Section;
    DWORD               Offset;
}DIBSECTION, * PDIBSECTION;

typedef struct _DISPLAY_DEVICEA{
    DWORD   Buffer;
    CHAR    DeviceName[32];
    CHAR    DeviceString[128];
    DWORD   StateFlags;
    CHAR    DeviceID[128];
    CHAR    DeviceKey[128];
}DISPLAY_DEVICEA, * PDISPLAY_DEVICEA, * LPDISPLAY_DEVICEA;

typedef struct _DISPLAY_DEVICEW{
    DWORD   Buffer;
    WCHAR   DeviceName[32];
    WCHAR   DeviceString[128];
    DWORD   StateFlags;
    WCHAR   DeviceID[128];
    WCHAR   DeviceKey[128];
}DISPLAY_DEVICEW, * PDISPLAY_DEVICEW, * LPDISPLAY_DEVICEW;

typedef struct _EMR{
    
}EMR, * PEMR, * LPEMR, * NPEMR;

#ifndef _GDI32_H

#endif

#endif