#ifndef _HDMI_INFO_H
#define _HDMI_INFO_H

#include "Picture.h"
#include "Sound.h"

typedef enum _HDMI_INFOFRAME_TYPE{
    HDMI_INFOFRAME_TYPE_VENDOR = 0x81,
    HDMI_INFOFRAME_TYPE_AVI = 0x82,
    HDMI_INFOFRAME_TYPE_SPD = 0x83,
    HDMI_INFOFRAME_TYPE_AUDIO = 0x84,
    HDMI_INFOFRAME_TYPE_DRSD = 0x87,
}HDMI_INFOFRAME_TYPE, * PHDMI_INFOFRAME_TYPE;

typedef enum _HDMI_3D_STRUCTURE{
    HDMI_3D_STRUCTURE_INVALID = -1,
    HDMI_3D_STRUCTURE_FRAME_PACKING = 0,
    HDMI_3D_STRUCTURE_FIELD_ALTERNATIVE,
    HDMI_3D_STRUCTURE_LINE_ALTERNATIVE,
    HDMI_3D_STRUCTURE_SIDE_BY_SIDE_FULL,
    HDMI_3D_STRUCTURE_L_DEPTH,
    HDMI_3D_STRUCTURE_L_DEPTH_GFX_GFX_DEPTH,
    HDMI_3D_STRUCTURE_TOP_AND_BOTTOM,
    HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF = 8,
}HDMI_3D_STRUCTURE, * PHDMI_3D_STRUCTURE;

typedef enum _HDMI_CONTENT_TYPE{
    HDMI_CONTENT_TYPE_GRAPHICS = 0,
    HDMI_CONTENT_TYPE_PHOTO,
    HDMI_CONTENT_TYPE_CINEMA,
    HDMI_CONTENT_TYPE_GAME,
}HDMI_CONTENT_TYPE, * PHDMI_CONTENT_TYPE;

typedef enum _HDMI_METADATA_TYPE{
    HDMI_METADATA_TYPE_1 = 0,
}HDMI_METADATA_TYPE, * PHDMI_METADATA_TYPE;

typedef enum _HDMI_EOTF{
    HDMI_EOTF_TRADITIONAL_GAMMA_SDR = 0,
    HDMI_EOTF_TRADITIONAL_GAMMA_HDR,
    HDMI_EOTF_SMPTE_ST2084,
    HDMI_EOTF_BT_2100_HLG,
}HDMI_EOTF, * PHDMI_EOTF;   

typedef enum _HDMI_SPD_SDI{
    HDMI_SPD_SDI_UNKOWN = 0,
    HDMI_SPD_SDI_DSTB,
    HDMI_SPD_SDI_DVDP,
    HDMI_SPD_SDI_DVHS,
    HDMI_SPD_SDI_HDDVR,
    HDMI_SPD_SDI_DVC,
    HDMI_SPD_SDI_DSC,
    HDMI_SPD_SDI_VCD,
    HDMI_SPD_SDI_GAME,
    HDMI_SPD_SDI_PC,
    HDMI_SPD_SDI_BD,
    HDMI_SPD_SDI_SACD,
    HDMI_SPD_SDI_HDDVD,
    HDMI_SPD_SDI_PMP,
}HDMI_SPD_SDI, * PHDMI_SPD_SDI;

typedef struct _HDMI_ANY_INFOFRAME{
    HDMI_INFOFRAME_TYPE     Type;
    UINT8                   Version;
    UINT8                   Length;
}HDMI_ANY_INFOFRAME, * PHDMI_ANY_INFOFRAME;

typedef struct _HDMI_VENDOR_INFOFRAME{
    HDMI_INFOFRAME_TYPE     Type;
    UINT8                   Version;
    UINT8                   Length;
    UINT                    Oui;
    UINT8                   Vic;
    HDMI_3D_STRUCTURE       S3dStructure;
    UINT                    S3dExtData;
}HDMI_VENDOR_INFOFRAME, * PHDMI_VENDOR_INFOFRAME;

typedef union _HDMI_ANY_VENDOR_INFOFRAME{
    struct{
        HDMI_INFOFRAME_TYPE Type;
        UINT8               Version;
        UINT8               Length;
    }                       Any;
    HDMI_VENDOR_INFOFRAME   Hdmi;
}HDMI_ANY_VENDOR_INFOFRAME, * PHDMI_ANY_VENDOR_INFOFRAME;

typedef struct _HDMI_AVI_INFOFRAME{
    HDMI_INFOFRAME_TYPE         Type;
    UINT8                       Version;
    UINT8                       Length;
    BOOLEAN                     Itc;
    uint8_t                     PixelRepeat;
    HDMI_COLOR_SPACE            ColorSpace;
    HDMI_SCAN_MODE              ScanMode;
    HDMI_COLORIMETRY            Colorimetry;
    HDMI_PICTURE_ASPECT         PictureAspect;
    HDMI_ACTIVE_ASPECT          ActiveAspect;
    HDMI_EXTENDED_COLORTIMETRY  ExtendedColoimetry;
    HDMI_QUANTIZATION_RANGE     QuantizationRange;
    HDMI_NUPS                   Nups;
    UINT8                       VideoCode;
    HDMI_YCC_QUANTIZATION_RANGE YccQuantizationRange;
    HDMI_CONTENT_TYPE           ContentType;
    UINT16                      TopBar;
    UINT16                      BottomBar;
    UINT16                      LeftBar;
    UINT16                      RightBar;
}HDMI_AVI_INFOFRAME, * PHDMI_AVI_INFOFRAME;

typedef struct _HDMI_DRSD_INFOFRAME{
    HDMI_INFOFRAME_TYPE     Type;
    UINT8                   Version;
    UINT8                   Length;
    HDMI_EOTF               Etof;
    HDMI_METADATA_TYPE      MetaDataType;
    struct{
        UINT16              X;
        UINT16              Y;
    }                       DisplayPrimaries[3];
    struct{
        UINT16              X;
        UINT16              Y;
    }                       WhitePoint[3];
    UINT16                  MaxDisplayMasteringLum;
    UINT16                  MinDisplayMasteringLum;
    UINT16                  MaxCll;
    UINT16                  MaxFall;
}HDMI_DRSD_INFOFRAME, * PHDMI_DRSD_INFOFRAME;

typedef struct _HDMI_SPD_INFOFRAME{
    HDMI_INFOFRAME_TYPE     Type;
    UINT8                   Version;
    UINT8                   Length;
    CHAR                    Vendor[8];
    CHAR                    Product[16];
    HDMI_SPD_SDI            Sdi;
}HDMI_SPD_INFOFRAME, * PHDMI_SPD_INFOFRAME;

typedef union _HDMI_INFOFRAME{
    HDMI_ANY_INFOFRAME          Any;
    HDMI_AVI_INFOFRAME          Avi;
    HDMI_SPD_INFOFRAME          Spd;
    HDMI_ANY_VENDOR_INFOFRAME   Vendor;
    HDMI_AUDIO_INFO_FRAME       Audio;
    HDMI_DRSD_INFOFRAME         Drsd;
}HDMI_INFOFRAME, * PHDMI_INFOFRAME;

#endif