
#ifndef _DRSD_H
#define _DRSD_H


#ifdef __cplusplus
#include <LouDDK.h>
#include <NtAPI.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif

/* Clean-room reimplementation of a DRM-like display subsystem.
 * No Linux kernel code has been copied. Inspired by public concepts only.
*/

#define DRSD_ROTATION_MODE_0 1

#define DRSD_PIXEL_BLEND_PRE_MULTI 1

#define DRSD_MAXIMUM_OBJECT_PROPERTIES 64

struct _DRSD_FRAME_BUFFER;
struct _DRSD_PLANE;
struct _DRSD_CRTC;
struct _DRSD_ENCODER_CALLBACKS;
struct _DRSD_ENCODER_ASSISTED_CALLBACKS;
struct _DRSD_CRTC_STATE;
struct _DRSD_CONNECTOR;
struct _DRSD_PROPERTY;
struct _DRSD_MODE_SET_CONTEXT;

//8 bit color
#define DRSD_COLOR_FORMAT_RGB332    "RGB8"
#define DRSD_COLOR_FORMAT_BGR233    "BGR8"

//16 bit Color
#define DRSD_COLOR_FORMAT_XRGB4444  "XR12"
#define DRSD_COLOR_FORMAT_XBGR4444  "XB12"
#define DRSD_COLOR_FORMAT_RGBX4444  "RX12"
#define DRSD_COLOR_FORMAT_BGRX4444  "XB12"
//Alpha 16 bit color
#define DRSD_COLOR_FORMAT_ARGB4444  "AR12"
#define DRSD_COLOR_FORMAT_ABGR4444  "AB12"
#define DRSD_COLOR_FORMAT_RGBA4444  "RA12"
#define DRSD_COLOR_FORMAT_BGRA4444  "BA12"
//PBD 16 bit color
#define DRSD_COLOR_FORMAT_XRGB1555  "XR15"
#define DRSD_COLOR_FORMAT_XBGR1555  "XB15"
#define DRSD_COLOR_FORMAT_RGBX1555  "RX15"
#define DRSD_COLOR_FORMAT_BGRX1555  "BX15"
#define DRSD_COLOR_FORMAT_RGB565    "RG16"
#define DRSD_COLOR_FORMAT_GRB565    "BG16"

//24 true RGB
#define DRSD_COLOR_FORMAT_RGB888    "RG24"
#define DRSD_COLOR_FORMAT_BBR888    "BG24"

//32 true RGB
#define DRSD_COLOR_FORMAT_XRGB8888  "XR24"
#define DRSD_COLOR_FORMAT_XBGR8888  "XB24"
#define DRSD_COLOR_FORMAT_RGBX8888  "RX24"
#define DRSD_COLOR_FORMAT_BGRX8888  "BX24"
//Alpha True RGB
#define DRSD_COLOR_FORMAT_ARGB8888  "AR24"
#define DRSD_COLOR_FORMAT_ABGR8888  "AB24"
#define DRSD_COLOR_FORMAT_RGBA8888  "RA24"
#define DRSD_COLOR_FORMAT_BGRA8888  "BA24"
//PBD 32 bit True RGB

typedef enum{
    DRSD_CONNECTOR_CONNECTED = 1,
    DRSD_CONNECTOR_DISCONNECTED = 2,
    DRSD_CONNECTOR_UNKOWN = 3,
}DRSD_CONNECTOR_STATUS;

typedef enum{
    DRSD_LINK_GOOD = 0,
    DRSD_LINK_BAD  = 1,
}DRSD_LINK_STATUS;

typedef enum{
    DRSD_MODE_OK = 0,
    DRSD_MODE_HSYNC = 1,
    DRSD_MODE_VSYNC = 2,
    DRSD_MODE_H_ILLEGAL = 3,
    DRSD_MODE_V_ILLEGAL = 4,
    DRSD_MODE_BAD_WIDTH = 5,
    DRSD_MODE_NO_MODE = 6,
    DRSD_MODE_NO_INTERLACE = 7,
    DRSD_MODE_NO_DOUBLE_SCAN = 8,
    DRSD_MODE_NO_VSCAN = 9,
    DRSD_MODE_MEMORY = 10,
    DRSD_MODE_VIRTUAL_X = 17,
    DRSD_MODE_VIRTUAL_Y = 18,
    DRSD_MODE_VIRTUAL_MEMORY = 19,
    DRSD_MODE_NO_CLOCK = 20,
    DRSD_MODE_CLOCK_TOO_HIGH = 21,
    DRSD_MODE_CLOCK_TOO_LOW = 22,
    DRSD_MODE_CLOCK_RANGE_ERROR = 23,
    DRSD_MODE_BAD_HVALUE = 24,
    DRSD_MODE_BAD_VVALUE = 25,
    DRSD_MODE_BAD_VSCAN = 26,
    DRSD_MODE_HSYNC_NARROW = 27,
    DRSD_MODE_HSYNC_WIDE = 28,
    DRSD_MODE_HBLANK_NARROW = 29,
    DRSD_MODE_HBLANK_WIDE = 30,
    DRSD_MODE_VSYNC_NARROW = 31,
    DRSD_MODE_VSYNC_WIDE = 32,
    DRSD_MODE_VBLANK_NARROW = 33,
    DRSD_MODE_VBLANK_WIDE = 34,
    DRSD_MODE_PANEL = 35,
    DRSD_MODE_INTERLACE_WIDTH = 36,
    DRSD_MODE_ONE_WIDTH = 37,
    DRSD_MODE_ONE_HEIGHT = 38,
    DRSD_MODE_ONE_SIZE = 39,
    DRSD_MODE_NO_REDUCED = 40,
    DRSD_MODE_NO_STEREO = 41,
    DRSD_MODE_NO_420 = 41,
    DRSD_MODE_STALE = -3,
    DRSD_MODE_BAD = -2,
    DRSD_MODE_ERROR = -1,
}DRSD_MODE_STATUS;

typedef enum {
    DRSD_FORCE_USPECIFIED = 0,
    DRSD_FORCE_OFF = 1,
    DRSD_FORCE_ON = 2,
    DRSD_FORCE_DIGITAL = 3,
}DRSD_CONNECTOR_FORCE;

#define DRSD_ENCODER_MODE_NONE  0
#define DRSD_ENCODER_MODE_DAC   1
#define DRSD_ENCODER_MODE_TMDS  2
#define DRSD_ENCODER_MODE_LVDS  3
#define DRSD_ENCODER_MODE_TVDAC 4
#define DRSD_ENCODER_MODE_VIRT  5
#define DRSD_ENCODER_MODE_DSI   6
#define DRSD_ENCODER_MODE_DPMST 7
#define DRSD_ENCODER_MODE_DPI   8

#define DRSD_MODE_OBJECT_ID_PLANE 1

typedef struct _DRSD_PROPERTY{
    uintptr_t Foo;
}DRSD_PROPERTY, * PDRSD_PROPERTY;

typedef struct _DRSD_MODE_OBJECT{
    ListHeader                          Peers;
    uint32_t                            Identification;
    uint32_t                            ModeType;
    struct _DRSD_OBJECT_PROPERTIES*     Properties;
    atomic_t                            ReferenceCount;
    void                                (*FreeCb)(int Reference);
}DRSD_MODE_OBJECT, * PDRSD_MODE_OBJECT;

typedef struct _DRSD_OBJECT_PROPERTIES{
    size_t                              CurrentProperties;
    struct _DRSD_PROPERTY_OBJECT*       Properties[DRSD_MAXIMUM_OBJECT_PROPERTIES];
    uint64_t                            Values[DRSD_MAXIMUM_OBJECT_PROPERTIES];
}DRSD_OBJECT_PROPERTIES, * PDRSD_OBJECT_PROPERTIES;

typedef struct _DRSD_PROPERTY_OBJECT{
    ListHeader              Peers;
    DRSD_MODE_OBJECT        BaseMode;
    uint32_t                PropertyFlags;
    string                  Name;
    size_t                  ValueCount;
    uint64_t*               Value;
    struct _DRSD_DEVICE*    Device;
    ListHeader              Enums;
}DRSD_PROPERTY_OBJECT, DRSD_PROPERTY_OBJECT; 

typedef struct _DRSD_FORMAT_INFORMATION{
    uint32_t    Format;
    uint8_t     PlaneDepth;
    union{
        uint8_t Bpp[4];
        uint8_t Bpb[4];
    }ByteData;
    uint8_t     BlockWidth[4];
    uint8_t     BlockHeight[4];
    uint8_t     HorizontalChromaFactor;
    uint8_t     VerticalChromaFactor;
    bool        AlphaChannelPresent;
    bool        IsYUV;
    bool        IsCollorIndexed;
}DRSD_FORMAT_INFORMATION, * PDRSD_FORMAT_INFORMATION;

typedef struct _DRSD_FRAMEBUFFER_CALLBACKS{
    void        (*DestroyFramebuffer)(struct _DRSD_FRAME_BUFFER* FrameBuffer);
    LOUSTATUS   (*CreateHandle)(struct _DRSD_FRAME_BUFFER* FrameBuffer, void* DrsdBuffer, uint32_t* Handle);
    LOUSTATUS   (*DrsdFlushFramebufferSyscall)(struct _DRSD_FRAME_BUFFER* FrameBuffer, void* DrsdBuffer, 
                                                                 uint64_t Flags, uint64_t Color, 
                                                                 void* Clip , uint64_t ClipCount);
    semaphore_t CallbackLock;
}DRSD_FRAMEBUFFER_CALLBACKS, * PDRSD_FRAMEBUFFER_CALLBACKS;

typedef struct _DRSD_GXE_OBJECT{
    semaphore_t                 ObjectLock;
    size_t                      HandleCount;
    struct _DRSD_DEVICE*        Device;
    void*                       Buffers;
    struct _LMPOOL_DIRECTORY*   GxeVmaPool;
    size_t                      GxeSize;
    uint64_t                    Name;
    uintptr_t                   DmaBuffer;
    void*                       DmaPropertiesBuffer;
}DRSD_GXE_OBJECT, * PDRSD_GXE_OBJECT;

typedef struct _DRSD_FRAME_BUFFER{
    ListHeader                              Peers;
    struct _DRSD_DEVICE*                    Device;
    DRSD_MODE_OBJECT                        Base;
    string                                  Comm;
    PDRSD_FORMAT_INFORMATION                FormatInfo;
    PDRSD_FRAMEBUFFER_CALLBACKS             Callbacks;
    uint32_t                                Offset;
    uint64_t                                Modifier;
    uint32_t                                Width;
    uint32_t                                Height;
    int32_t                                 Flags;
    ListHeader                              Buffers;
    PDRSD_GXE_OBJECT                        GxeObjects;
    //following is legacy and here for old linear framebuffers
    uint64_t                                FramebufferBase;
    uint64_t                                SecondaryFrameBufferBase;
    uint64_t                                TrimaryFrameBufferBase;
    uint64_t                                FramebufferSize;
    PDRSD_FORMAT_INFORMATION                Format;
    uint8_t                                 Bpp;
    uint64_t                                Pitch;
    uint8_t                                 FrameBufferType;
}DRSD_FRAME_BUFFER, * PDRSD_FRAME_BUFFER;

#define DDM_HSYNC_FLAGS             (0x03 << 0) //first 0 : 2
#define DDM_FLAG_HSYNC_INACTIVE     (0 << 0)
#define DDM_FLAG_HSYNC_ACTIVE_HIGH  (1 << 0)
#define DDM_FLAG_HSYNC_ACTIVE_LOW   (2 << 0)
#define DDM_VSYNC_FLAGS             (0x03 << 2) //      2 : 4
#define DDM_FLAG_VSYNC_INACTIVE     (0 << 2)
#define DDM_FLAG_VSYNC_ACTIVE_HIGH  (1 << 2)
#define DDM_FLAG_VSYNC_ACTIVE_LOW   (2 << 2)
#define DDM_FLAG_DOUBLE_SCAN        (1 << 4)    //      4 
#define DDM_FLAG_CSYNC              (1 << 5)    //      5
#define DDM_CSYNC_FLAGS             (0x03 << 6) //      6 : 8
#define DDM_FLAG_CSYNC_INACTIVE     (0 << 6)
#define DDM_FLAG_CSYNC_ACTIVE_HIGH  (1 << 6)
#define DDM_FLAG_CSYNC_ACTIVE_LOW   (2 << 6)
#define DDM_FLAG_INTERLACED         (1 << 8)    //      8 
#define DDM_FLAG_HSKEW              (1 << 9)    //      9 
#define DDM_FLAG_BCAST              (1 << 10)   //      10 : Legacy System
#define DDM_FLAG_PIXMUX             (1 << 11)   //      11 : Legacy System
#define DDM_CLOCKED_FLAG            (1 << 12)   //      12 : Boolean
#define DDM_FLAG_DOUBLE_CLOCKED     (1 << 12)   //
#define DDM_FLAG_SINGLE_CLOCKED     (0 << 12)   //
#define DDM3D_FLAG_3D_ENABLED       (1 << 13)   //      13 : Boolean
#define DDM3D_FLAG_FRAME_PACKING    (1 << 14)
#define DDM3D_FLAG_FIELD_ALTERNITIVE (1 << 15)
#define DDM3D_FLAG_LINE_ALTERNITIVE (1 << 16)
#define DDM3D_FLAG_SBS_FULL         (1 << 17)
#define DDM3D_FLAG_3D_L_DEPTH       (1 << 18)
#define DDM3D_FLAG_3D_L_DEPTH_GFX   (1 << 19)
#define DDM3D_FLAG_3D_TB            (1 << 20)
#define DDM3D_FLAG_SBS_HALF         (1 << 21)

typedef enum {
    NONE = 0,
    X4Y3 = 1,
    X16Y9 = 2,
    X64Y27 = 3,
    X256Y135 = 4,
    RESERVED = 5,
}HDMI_ASPECT_RATIO;

#define DRSD_MODE_TYPE_BUILTIN          (1)
#define DRSD_MODE_TYPE_CLOCK_C          (1 << 1)
#define DRSD_MODE_TYPE_CRTC_C           (1 << 2)
#define DRSD_MODE_TYPE_PREFERED         (1 << 3)
#define DRSD_MODE_TYPE_DEFAULT          (1 << 4)
#define DRSD_MODE_TYPE_USER_DEFINED     (1 << 5)
#define DRSD_MODE_TYPE_DRIVER           (1 << 6)
#define DRSD_MODE_TYPE_ALL              (0b1111111)


#define DEFINE_DRSD_MODE(Name, Type, Clock, Hd, Hss, Hse, Ht, Hsk, Vd, Vss, Vse, Vt, Vs, Flags) \
    .ModeName = Name, .ModeStatus = (DRSD_MODE_STATUS)0, .KhzClock = Clock, .HorizontalDisplay = Hd, .HorizontalSyncStart = Hss, \
    .HorizontalSyncEnd = Hse,  .HorizontalTotal = Ht, .HorizontalSkew = Hsk, .VirticalDisplay = Vd, \
    .VirticalSyncStart = Vss, .VirticalSyncEnd = Vse, .VirticalTotal = Vt, .VirticalScan = Vs, .DdmFlags = Flags, .ModeType = Type


typedef struct  _DRSD_DISPLAY_MODE{
    ListHeader              Peers;
    string                  ModeName;
    DRSD_MODE_STATUS        ModeStatus;
    size_t                  KhzClock;
    uint16_t                HorizontalDisplay;
    uint16_t                HorizontalSyncStart;
    uint16_t                HorizontalSyncEnd;
    uint16_t                HorizontalTotal;
    uint16_t                HorizontalSkew;
    uint16_t                VirticalDisplay;
    uint16_t                VirticalSyncStart;
    uint16_t                VirticalSyncEnd;
    uint16_t                VirticalTotal;
    uint16_t                VirticalScan;
    uint32_t                DdmFlags;
    size_t                  CrtcClock;
    uint16_t                CrtcHorizontalDisplay;
    uint16_t                CrtcHorizontalSyncStart;
    uint16_t                CrtcHorizontalSyncEnd;
    uint16_t                CrtcHorizontalTotal;
    uint16_t                CrtcHorizontalSkew;
    uint16_t                CrtcVirticalDisplay;
    uint16_t                CrtcVirticalSyncStart;
    uint16_t                CrtcVirticalSyncEnd;
    uint16_t                CrtcVirticalTotal;
    uint16_t                ModeType;
    bool                    GiveToUser;
    HDMI_ASPECT_RATIO       AspectRatio;
}DRSD_DISPLAY_MODE, * PDRSD_DISPLAY_MODE;

typedef struct _DRSD_CRTC_COMMIT{
    atomic_t        Reference;
}DRSD_CRTC_COMMIT, * PDRSD_CRTC_COMMIT;

typedef struct _DRSD_PLANE_STATE{
    struct _DRSD_FRAME_BUFFER*      FrameBuffer;
    atomic_t                        Fence;
    DRSD_CRTC_COMMIT                Commit;
    struct _DRSD_PROPERTY_BLOB*     Base;
    uint32_t                        Rotation;
    uint32_t                        PixelBlend;
    int32_t                         SourceX;
    int32_t                         SourceY;
    uint32_t                        Height;
    uint32_t                        Width;
    uint32_t*                       Formats;
    size_t                          FormatCount;
    struct _DRSD_CRTC*              Crtc;
    string                          FormatUsed;
}DRSD_PLANE_STATE, * PDRSD_PLANE_STATE;

typedef struct _SHADOW_PLANE_STATE{
    DRSD_PLANE_STATE Base;
}SHADOW_PLANE_STATE, * PSHADOW_PLANE_STATE;

typedef struct _DRSD_PLANE_ASSIST_CALLBACKS{
    LOUSTATUS   (*PrepareFrameBuffer)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* NewState);
    void        (*CleanupFrameBuffer)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* OldState);
    LOUSTATUS   (*StartFrameBufferProcessing)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* NewState);
    void        (*StopFrameBufferProcessing)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* OldState);
    LOUSTATUS   (*AtomicCheck)(struct _DRSD_PLANE* Plane, void* LockHandle);
    void        (*AtomicUpdate)(struct _DRSD_PLANE* Plane, void* LockHandle);
    void        (*AtomicSetState)(struct _DRSD_PLANE* Plane, void* LockHandle, bool Enable);
    LOUSTATUS   (*AtomicAsyncCheck)(struct _DRSD_PLANE* Plane, void* State, bool Flip);
    void        (*AtomicAsyncUpdate)(struct _DRSD_PLANE* Plane, void* LockHandle);
    LOUSTATUS   (*GetCanoutBuffer)(struct _DRSD_PLANE* Plane, void* ScanBuffer);
    void        (*PanicFlush)(struct _DRSD_PLANE* Plane);
}DRSD_PLANE_ASSIST_CALLBACKS, * PDRSD_PLANE_ASSIST_CALLBACKS;

typedef struct _DRSD_PLANE_CALLBACKS{
    LOUSTATUS                   (*UpdatePlane)(struct _DRSD_PLANE* Plane, struct _DRSD_CRTC* Crtc, struct _DRSD_FRAME_BUFFER* FrameBuffer, int CrtcX, int CrtcY, int CrtcWidth, int CrtcHeight, uint32_t SourceX, uint32_t SourceY, uint32_t SourceWidth, uint32_t SourceHeight, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
    LOUSTATUS                   (*DisablePlane)(struct _DRSD_PLANE* Plane, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
    void                        (*DestroyPlane)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* PlaneState);
    void                        (*ResetPlane)(struct _DRSD_PLANE* Plane);
    LOUSTATUS                   (*SetPlaneProperty)(struct _DRSD_PLANE* Plane, void* PropertyBuffer, uint64_t Value);
    struct _DRSD_PLANE_STATE*   (*DuplicatePlaneAtomicState)(struct _DRSD_PLANE* Plane);
    void                        (*DestroyPlaneAtomic)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* PlaneState);
    LOUSTATUS                   (*SetPropertyAtomic)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* PlaneState, void* Property, uint64_t Value);
    LOUSTATUS                   (*GetPropertyAtomic)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* PlaneState, void* Property, uint64_t* Value);
    LOUSTATUS                   (*PlaneLateRegister)(struct _DRSD_PLANE* Planem);
    LOUSTATUS                   (*PlaneEarlyRegister)(struct _DRSD_PLANE* Planem);
    void                        (*PrintPlaneStateAtomic)(struct _DRSD_PLANE_STATE* State);
    bool                        (*ModifierFormatSupported)(struct _DRSD_PLANE* Plane, uint32_t Format, uint64_t Modifier);
    bool                        (*AsyncModifierFormatSupported)(struct _DRSD_PLANE* Plane, uint32_t Format, uint64_t Modifier);
}DRSD_PLANE_CALLBACKS, * PDRSD_PLANE_CALLBACKS;

typedef enum{
    OVERLAY_PLANE = 0,
    PRIMARY_PLANE = 1,
    CURSOR_PLANE  = 2,
}DRSD_PLANE_TYPE;

typedef struct _DRSD_PLANE{
    ListHeader                      Peers;
    struct _DRSD_DEVICE*            Device;
    string                          PlaneName;
    mutex_t                         PlaneLock;
    DRSD_MODE_OBJECT                BaseMode;
    uint32_t*                       FormatTypes;
    size_t                          FormatCount;
    uint32_t*                       Formats;
    bool                            FormatDefault;
    uint64_t*                       Modifiers;
    uint64_t                        ModifierCount;
    bool                            ModifierDefault;
    struct _DRSD_CRTC*              Crtc;
    PDRSD_FRAME_BUFFER              FrameBuffer;
    PDRSD_FRAME_BUFFER              OldBuffer;
    PDRSD_PLANE_CALLBACKS           Callbacks;
    PDRSD_PLANE_ASSIST_CALLBACKS    AssistCallbacks;
    DRSD_OBJECT_PROPERTIES          Properties;
    DRSD_PLANE_TYPE                 PlaneType;
    PDRSD_PLANE_STATE               PlaneState;
    size_t                          ColorEncodingProperty;
    size_t                          ColorRangeProperty;
    size_t                          ZPositionProperty;
    size_t                          HotSpotXProperty;
    size_t                          HotSpotYProperty;
    bool                            PlaneInUse;
    uint64_t                        DrsdPutPixelCase;
    size_t                          AlphaShift;
    size_t                          RedShift;
    size_t                          BlueShift;
    size_t                          GreenShift;
}DRSD_PLANE, * PDRSD_PLANE;

typedef enum{
    DRSD_REGISTERING = 1,
    DRSD_REGISTERED  = 2,
    DRSD_UNREGISTERED= 3,
}DRSD_REGISTRATION_STATE;

typedef enum {
    SUBPIXEL_UNKOWN              = 0,
    SUBPIXEL_HORIZONTAL_RGB      = 1,
    SUBPIXEL_HORIZONTAL_BGR      = 2,
    SUBPIXEL_VERTICAL_RGB        = 3,
    SUBPIXEL_VIRTICAL_BGR        = 4,
    SUBPIXEL_NONE                = 5,
}SUBPIXEL_ORDER;

typedef struct _DRSD_SCRAMBLING{
    bool    ScramblingSupported;
    bool    LowRates;
}DRSD_SCRAMBLING, * PDRSD_SCRAMBLING;

typedef struct _DRSD_SCDC{
    bool                ScdcSupported;
    bool                ReadRequest;
    DRSD_SCRAMBLING     Scrambling;
}DRSD_SCDC, * PDRSD_SCDC;

typedef struct _DRSD_HDMI_DSC_CAPABILITIES{
    bool        V1p2;
    bool        Native420;
    bool        AllBpp;
    bool        BpcSupported;
    uint8_t     MaxSupported;
    uint8_t     MaxSlices;
    int32_t     ClockPerSlices;
    uint8_t     MaxLanes;
    uint8_t     MaxFrlRatePerLane;
    uint8_t     TotalKilobyteChunks;
}DRSD_HDMI_DSC_CAPABILITIES,  * PDRSD_HDMI_DSC_CAPABILITIES;

typedef struct _HDMI_SYNCRONIZATION_INFORMATION{
    uint32_t MetaType;
    struct {
        uint8_t Eotf;
        uint8_t MetaType;
        uint16_t MaximumCll;
        uint16_t MaximumFall;
        uint16_t MinimumCall;
    }HDR861G;
}HDMI_SYNCRONIZATION_INFORMATION, * PHDMI_SYNCRONIZATION_INFORMATION;

typedef struct _DRSD_HDMI_INFORMATION{
    DRSD_SCDC                       Scdc;
    ListHeader                      Y420VdbModes;
    ListHeader                      Y420CmdbModes;
    uint8_t                         Y420DcModes;
    uint8_t                         MaxFrlRatePerLane;
    uint8_t                         MaxLanes;
    DRSD_HDMI_DSC_CAPABILITIES      DscCapabilities;
}DRSD_HDMI_INFORMATION, * PDRSD_HDMI_INFORMATION;

typedef struct _DRSD_MONITOR_RANGE_INFORMATION{
    uint16_t    MinimumVFrequency;
    uint16_t    MaximumVFrequency;
}DRSD_MONITOR_RANGE_INFORMATION, * PDRSD_MONITOR_RANGE_INFORMATION;

typedef struct _DRSD_LUMINANCE_RANGE_INFORMATION{
    uint32_t    MinimumLiminance;
    uint32_t    MaximumLiminance;
}DRSD_LUMINANCE_RANGE_INFORMATION, * PDRSD_LUMINANCE_RANGE_INFORMATION;

typedef struct _DRSD_DISPLAY_INFORMATION{
    uint32_t                            MetricWidth;
    uint32_t                            MetricHeight;
    uint32_t                            BitsPerChannel;
    SUBPIXEL_ORDER                      SubpixelOrder;
    int32_t                             PanelOrientation;
    uint32_t                            ColorFormats;
    uint32_t*                           BusFormats;
    uint32_t                            NumBusFormats;
    uint32_t                            BusFlags;
    int32_t                             MaxTmdsClock;
    bool                                DualDVI;
    bool                                HdmiDevice;
    bool                                AudioConection;
    bool                                HdmiInfoFrameProtocol;
    bool                                QuantizationSelectable;
    uint8_t                             EdidHdmiRgb444DcModes;
    uint8_t                             EdidHdmiYcbcr444DcModes;
    uint8_t                             CEARevision;
    DRSD_HDMI_INFORMATION               HdmiInformation;
    bool                                NDD; //non desktop display HMD
    DRSD_MONITOR_RANGE_INFORMATION      MonitorRangeInfo;
    DRSD_LUMINANCE_RANGE_INFORMATION    LuminanceInformation;
    uint8_t                             MsoStreamCount;
    uint8_t                             MsoPixelOverlap;
    uint32_t                            MaxDscBpp;
    uint8_t*                            Vics;
    size_t                              VicsCount;
    uint32_t                            Quirks;
    uint16_t                            SourcePhysicalAddress;
}DRSD_DISPLAY_INFORMATION , * PDRSD_DISPLAY_INFORMATION;

typedef struct _DRSD_CONNECTOR_STATE{
    struct _DRSD_CONNECTOR*     Connector;
    struct _DRSD_CRTC*          Crtc;
    struct _DRSD_ENCODER*       Encoder;
    DRSD_LINK_STATUS            LinkStatus;
    void*                       AtomicState;
    struct _DRSD_CRTC_COMMIT*   Commit;
    //TODO
}DRSD_CONNECTOR_STATE, * PDRSD_CONNECTOR_STATE;

typedef struct _DRSD_CONNECTOR_CALLBACKS{
    LOUSTATUS                   (*ConnectorSetPowerMode)(struct _DRSD_CONNECTOR* Connector, int Mode);
    void                        (*ResetConnector)(struct _DRSD_CONNECTOR* Connector);
    DRSD_CONNECTOR_STATUS       (*DetectConnector)(struct _DRSD_CONNECTOR* Connector, bool Force);
    void                        (*ForceConnector)(struct _DRSD_CONNECTOR* Connector);
    LOUSTATUS                   (*ConnectorFillModes)(struct _DRSD_CONNECTOR* Connector, uint32_t MaxWidth, uint32_t MaxHeight);
    LOUSTATUS                   (*SetConnectorProperty)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_PROPERTY* Property, uint64_t Value);
    LOUSTATUS                   (*ConnectorLateRegister)(struct _DRSD_CONNECTOR* Connector);
    void                        (*ConnectorEarlyUnregister)(struct _DRSD_CONNECTOR* Connector);
    void                        (*DestroyConnector)(struct _DRSD_CONNECTOR* Connector);
    PDRSD_CONNECTOR_STATE       (*ConnectorAtomicDuplicateState)(struct _DRSD_CONNECTOR* Connector);
    void                        (*ConnectorDestroyStateAtomic)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_CONNECTOR_STATE* State);
    LOUSTATUS                   (*ConnectorSetPropertyAtomic)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_CONNECTOR_STATE* State, struct _DRSD_PROPERTY* Property, uint64_t Value);
    LOUSTATUS                   (*ConnectorGetPropertyAtomic)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_CONNECTOR_STATE* State, struct _DRSD_PROPERTY* Property, uint64_t* Value);
    void                        (*OobHotplugEvent)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_CONNECTOR_STATE* State);
}DRSD_CONNECTOR_CALLBACKS , * PDRSD_CONNECTOR_CALLBACKS;

typedef struct _DRSD_PROPERTY_BLOB{
    ListHeader              Peers;
    struct _DRSD_DEVICE*    Device;
    DRSD_MODE_OBJECT        Base;
    size_t                  Length;
    void*                   Data;
}DRSD_PROPERTY_BLOB, * PDRSD_PROPERTY_BLOB;

typedef struct _DRSD_CONNECTOR_ASSIST_CALLBACKS{
    size_t                  (*ConnectorGetModes)(struct _DRSD_CONNECTOR* Connector);
    DRSD_CONNECTOR_STATUS   (*ConnectorDetectContext)(struct _DRSD_CONNECTOR* Connector, void*  ModeSetAquireContext, bool Force);
    DRSD_CONNECTOR_STATUS   (*ConnectorDetect)(struct _DRSD_CONNECTOR* Connector, bool Force);
    DRSD_MODE_STATUS        (*ConnectorModeValid)(struct _DRSD_CONNECTOR* Connector, PDRSD_DISPLAY_MODE Mode);
    LOUSTATUS               (*ConnectorModeValidContext)(struct _DRSD_CONNECTOR* Connector, PDRSD_DISPLAY_MODE Mode, void* ModeSetAquireContext, DRSD_MODE_STATUS* Status);
    struct _DRSD_ENCODER*   (*ConnectorBestEncoder)(struct _DRSD_CONNECTOR* Connector);
    struct _DRSD_ENCODER*   (*ConnectorBestEncoderAtomic)(struct _DRSD_CONNECTOR* Connector);
    LOUSTATUS               (*ConnectorCheckAtomic)(struct _DRSD_CONNECTOR* Connector, void* AtomicData);
    void                    (*ConnectorAtomicCommit)(struct _DRSD_CONNECTOR* Connector, void* AtomicData);
    void                    (*ConnectorEnableHpd)(struct _DRSD_CONNECTOR* Connector);
    void                    (*ConnectorDisableHpd)(struct _DRSD_CONNECTOR* Connector);
    //TODO  
}DRSD_CONNECTOR_ASSIST_CALLBACKS, * PDRSD_CONNECTOR_ASSIST_CALLBACKS;

typedef struct _DRSD_CONNECTOR{
    ListHeader                          Peers;
    struct _DRSD_DEVICE*                Device;
    void*                               PrivateData;
    void*                               DownwireDevices;//some setups have smart systems down the wire
    ListHeader                          GlobalConectorList;
    PDRSD_MODE_OBJECT                   Base;
    string                              Name;
    mutex_t                             ConnectorLock;
    size_t                              Index;
    int32_t                             CType;
    int32_t                             CTypeID;
    bool                                InterlaceAble;
    bool                                DoubleScanAble;
    bool                                StereoAble;
    bool                                Ycbcr420Able;
    DRSD_REGISTRATION_STATE             RegistrationState;
    ListHeader                          SupportedModes;
    DRSD_CONNECTOR_STATUS               ConnectorStatus;
    ListHeader                          ProbedModes;//these modes may burn out things so carefull implementing this in user
    DRSD_DISPLAY_INFORMATION            DisplayInformation;
    PDRSD_CONNECTOR_CALLBACKS           Callbacks;
    PDRSD_PROPERTY_BLOB                 EdidPropertiesBlob;
    DRSD_OBJECT_PROPERTIES              ConnectorProperties;
    PDRSD_PROPERTY                      ScalingModeProperties;
    PDRSD_PROPERTY                      VrrCapabilitiesProperties;
    PDRSD_PROPERTY                      ColorspaceProperties;
    PDRSD_PROPERTY_BLOB                 PathPropertyBlob;
    size_t                              MaxBpc;
    PDRSD_PROPERTY                      MaxBpcProperty;
    PDRSD_PROPERTY                      BroadcastRgbProperty;
    int                                 PowerMode;
    PDRSD_CONNECTOR_ASSIST_CALLBACKS    AssistCallbacks;
    DRSD_CONNECTOR_FORCE                Force;
    HDMI_SYNCRONIZATION_INFORMATION     HdmiSyncInformation;
    bool                                LatencyPresent[2];
    size_t                              AudioLatency[2];
    size_t                              VideoLatency[2];
    uint8_t                             Eld[128];
    mutex_t                             EldTex;
    size_t                              ProbeModeCount;
    struct _DRSD_ENCODER*               Encoder;
    struct _DRSD_CRTC*                  Crtc;
}DRSD_CONNECTOR, * PDRSD_CONNECTOR;

typedef struct _DRSD_EDID_IDENTIFICATION{
    uint32_t    PannelIdentification;
    string      EdidName;
}DRSD_EDID_IDENTIFICATION, * PDRSD_EDID_IDENTIFICATION;

typedef struct _EDID_QUIRK{
    DRSD_EDID_IDENTIFICATION    Identification;
    uint32_t                    QuirkID;
}EDID_QUIRK, * PEDID_QUIRK;

#define PREFER_LARGE_60HZ_EDID_QUIRK            (1)
#define CLOCK_TOO_HIGH_EDID_QUIRK               (1 << 1)
#define PREFER_LARGE_75HZ_EDID_QUIRK            (1 << 2)
#define DETAILED_CM_EDID_QUIRK                  (1 << 3)
#define DETAILED_USE_MAXIMUM_SIZE_EDID_QUIRK    (1 << 4)
#define DETAILED_SYNC_PP_EDID_QUIRK             (1 << 5)
#define FORCE_REDUCED_BLANKING_EDID_QUIRK       (1 << 6)
#define FORCE_8BPC_EDID_QUIRK                   (1 << 7)
#define FORCE_12BPC_EDID_QUIRK                  (1 << 8)
#define FORCE_6BPC_EDID_QUIRK                   (1 << 9)
#define FORCE_10BPC_EDID_QUIRK                  (1 << 10)
#define NON_DESKTOP_EDID_QUIRK                  (1 << 11)
#define CAP_DSC_15BPP_EDID_QUIRK                (1 << 12)

#define GET_EDID_IDENTIFCATION(VenA, VenB, VenC, Product) ((((uint32_t)(VenA) - '@') & 0x1F) << 26 | (((uint32_t)(VenB) - '@') & 0x1F) << 21 | (((uint32_t)(VenC) - '@') & 0x1F) << 16 | ((uint32_t)(Product) & 0xFFFF)) 
#define GET_EDID_PRODUCT_IDENTIFICATION(Edid) (Edid->ProductCode[0] | (Edid->ProductCode[0] << 8))

#define DEFINE_EDID_QUIRK(VenA, VenB, VenC, Product, Quirk) \
    .Identification = GET_EDID_IDENTIFCATION(VenA, VenB, VenC, Product), .QuirkID = (uint32_t)Quirk
    

#define DRSD_CONNECTOR_MODE_UNKOWN          0
#define DRSD_CONNECTOR_MODE_VGA             1
#define DRSD_CONNECTOR_MODE_DVII            2
#define DRSD_CONNECTOR_MODE_DBID            3
#define DRSD_CONNECTOR_MODE_DVIA            4
#define DRSD_CONNECTOR_MODE_COMPOSITE       5
#define DRSD_CONNECTOR_MODE_SVIDEO          6
#define DRSD_CONNECTOR_MODE_LVDS            7
#define DRSD_CONNECTOR_MODE_COMPONENT       8
#define DRSD_CONNECTOR_MODE_9PIN_DIN        9        
#define DRSD_CONNECTOR_MODE_DISPLAY_PORT    10
#define DRSD_CONNECTOR_MODE_HDMI_A          11
#define DRSD_CONNECTOR_MODE_HDMI_B          12
#define DRSD_CONNECTOR_MODE_TV              13
#define DRSD_CONNECTOR_MODE_EDP             14
#define DRSD_CONNECTOR_MODE_VIRTUAL         15
#define DRSD_CONNECTOR_MODE_DSI             16
#define DRSD_CONNECTOR_MODE_DPI             17
#define DRSD_CONNECTOR_MODE_WRITEBACK       18
#define DRSD_CONNECTOR_MODE_SPI             19
#define DRSD_CONNECTOR_MODE_USB             20

typedef struct _DRSD_ENCODER{
    ListHeader                                  Peers;
    struct _DRSD_DEVICE*                        Device;
    struct _DRSD_MODE_OBJECT*                   Base;
    string                                      EncoderName;
    int32_t                                     EncoderType;
    size_t                                      Index;
    uint32_t                                    CrtcLimit;
    uint32_t                                    CloneLimit;
    ListHeader                                  BridgeLink;
    struct _DRSD_ENCODER_CALLBACKS*             Callbacks;
    struct _DRSD_ENCODER_ASSISTED_CALLBACKS*    AssistedCallbacks;
}DRSD_ENCODER, * PDRSD_ENCODER; 

typedef struct _DRSD_ENCODER_CALLBACKS{
    void        (*ResetEncoder)(struct _DRSD_ENCODER* Encoder);
    void        (*DestroyEnocder)(struct _DRSD_ENCODER* Encoder);
    void        (*LateRegisterEnocder)(struct _DRSD_ENCODER* Encoder);
    void        (*EarlyUnregisterEncoder)(struct _DRSD_ENCODER* Encoder);
}DRSD_ENCODER_CALLBACKS, * PDRSD_ENCODER_CALLBACKS;

typedef struct _DRSD_ENCODER_ASSISTED_CALLBACKS{
    void                        (*EncoderSetPowerMode)(struct _DRSD_ENCODER* Encoder, int PowerMode);
    DRSD_MODE_STATUS            (*EncoderIsModeValid)(struct _DRSD_ENCODER* Encoder, struct _DRSD_DISPLAY_MODE* Mode);
    bool                        (*EncoderModeFixup)(struct _DRSD_ENCODER* Encoder, struct _DRSD_DISPLAY_MODE* Mode);
    void                        (*PrepareEncoder)(struct _DRSD_ENCODER* Encoder);
    void                        (*CommitEncoder)(struct _DRSD_ENCODER* Encoder);
    void                        (*ModeSet)(struct _DRSD_ENCODER* Encoder, struct _DRSD_DISPLAY_MODE Mode, struct _DRSD_DISPLAY_MODE* AdjustedMode);
    void                        (*ModeSetAtomic)(struct _DRSD_ENCODER* Encoder, struct _DRSD_CRTC_STATE* CrtcState, void* DrsdConnectorState);
    DRSD_CONNECTOR_STATUS       (*Detect)(struct _DRSD_ENCODER* Encoder, void* Connector);
    void                        (*DisableDisable)(struct _DRSD_ENCODER* Encoder, void* State);
    void                        (*EnableAtomic)(struct _DRSD_ENCODER* Encoder, void* State);
    void                        (*Disable)(struct _DRSD_ENCODER* Encoder);
    void                        (*Enable)(struct _DRSD_ENCODER* Encoder);
    LOUSTATUS                   (*CheckAtomic)(struct _DRSD_ENCODER* Encoder, struct _DRSD_CRTC_STATE* State, void* ConnectorState);
}DRSD_ENCODER_ASSISTED_CALLBACKS, * PDRSD_ENCODER_ASSISTED_CALLBACKS;


typedef struct _DRSD_CRTC_STATE{
    struct _DRSD_CRTC*  Crtc;
    bool                NeedsModeset;
    bool                Enable;
    DRSD_DISPLAY_MODE   DisplayMode;
}DRSD_CRTC_STATE, * PDRSD_CRTC_STATE;   


typedef struct _DRSD_CRTC_ASSIST_CALLBACK{
    void                        (*CrtcSetPowerMode)(struct _DRSD_CRTC* Crtc, int Mode);
    void                        (*PrepareCtrc)(struct _DRSD_CRTC* Crtc);
    void                        (*CommitMode)(struct _DRSD_CRTC* Crtc);
    DRSD_MODE_STATUS            (*ModeValid)(struct _DRSD_CRTC* Crtc, PDRSD_DISPLAY_MODE Mode);
    bool                        (*ValidateMode)(struct _DRSD_CRTC* Crtc, PDRSD_DISPLAY_MODE Mode, PDRSD_DISPLAY_MODE AdjustedMode);
    LOUSTATUS                   (*SetMode)(struct _DRSD_CRTC* Crtc, PDRSD_DISPLAY_MODE Mode, PDRSD_DISPLAY_MODE AdjustedMode, int x, int y, struct _DRSD_FRAME_BUFFER* OldFrameBuffer);
    void                        (*SetModeNoFrameBuffer)(struct _DRSD_CRTC* Crtc);
    LOUSTATUS                   (*ModeSetBase)(struct _DRSD_CRTC* Crtc, int x, int y, PDRSD_FRAME_BUFFER OldFrameBuffer);
    LOUSTATUS                   (*ModeSetBaseAtomic)(struct _DRSD_CRTC* Crtc, struct _DRSD_FRAME_BUFFER* FrameBuffer, int x, int y, void* AtomicData);
    void                        (*DisableCrtc)(struct _DRSD_CRTC* Crtc);
    LOUSTATUS                   (*AtomicCheck)(struct _DRSD_CRTC* Crtc, void* AtomicBuffer);
    void                        (*BeginAtomic)(struct _DRSD_CRTC* Crtc, void* AtomicBuffer);
    void                        (*FlushAtomic)(struct _DRSD_CRTC* Crtc, void* AtomicBuffer);
    void                        (*EnableAtomic)(struct _DRSD_CRTC* Crtc, void* AtomicBuffer);
    void                        (*DisableAtomic)(struct _DRSD_CRTC* Crtc, void* AtomicBuffer);
    bool                        (*GetCrtcScanoutPosition)(struct _DRSD_CRTC* Crtc, bool IRQ, int* VPosition, int* HPosition, uint64_t STime, uint64_t ETime, struct _DRSD_DISPLAY_MODE* Mode);
}DRSD_CRTC_ASSIST_CALLBACK, * PDRSD_CRTC_ASSIST_CALLBACK;

typedef struct _DRSD_CRTC_CALLBACK{
    void                        (*ResetCrtc)(struct _DRSD_CRTC* Crtc);
    LOUSTATUS                   (*SetCursor)(struct _DRSD_CRTC* Crtc, void* DrsdBuffer, uint32_t Handle, uint32_t Width, uint32_t Height);
    LOUSTATUS                   (*SetCursorEx)(struct _DRSD_CRTC* Crtc, void* DrsdBuffer, uint32_t Handle, uint32_t Width, uint32_t Height, int32_t HotX, int32_t HotY);
    LOUSTATUS                   (*MoveCursor)(struct _DRSD_CRTC* Crtc, int X, int Y);
    LOUSTATUS                   (*SetGamma)(struct _DRSD_CRTC* Crtc, uint16_t* R, uint16_t* G, uint16_t* B);
    void                        (*DestroyCrtc)(struct _DRSD_CRTC* Crtc);
    LOUSTATUS                   (*SetConfiguration)(void* ModeSet, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
    LOUSTATUS                   (*PageFlip)(struct _DRSD_CRTC* Crtc, DRSD_FRAME_BUFFER* FrameBuffer, void* VBlankEvent, uint32_t Flags, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
    LOUSTATUS                   (*PageFlipTarget)(struct _DRSD_CRTC* Crtc, struct _DRSD_FRAME_BUFFER* Event, uint32_t Flags, uint32_t Target, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
    LOUSTATUS                   (*SetProperty)(struct _DRSD_CRTC* Crtc,  struct _DRSD_PROPERTY* Property, uint64_t Value);
    struct _DRSD_CRTC_STATE*    (*AtomicDuplicateState)(struct _DRSD_CRTC* Crtc);
    void                        (*AtomicDestroyState)(struct _DRSD_CRTC* Crtc, struct _DRSD_CRTC_STATE* CrtcState);
    LOUSTATUS                   (*GetProperty)(struct _DRSD_CRTC* Crtc,  struct _DRSD_PROPERTY* Property, uint64_t* Value);
    LOUSTATUS                   (*AtomicSetProperty)(struct _DRSD_CRTC* Crtc, struct _DRSD_CRTC_STATE* State, struct _DRSD_PROPERTY* Property, uint64_t Value);
    LOUSTATUS                   (*AtomicGetProperty)(struct _DRSD_CRTC* Crtc, struct _DRSD_CRTC_STATE* State, struct _DRSD_PROPERTY* Property, uint64_t* Value);    
    LOUSTATUS                   (*LateRegister)(struct _DRSD_CRTC* Crtc);
    void                        (*EarlyUnregister)(struct _DRSD_CRTC* Crtc);
    LOUSTATUS                   (*SetCrcSource)(struct _DRSD_CRTC* Crtc, string Source);
    LOUSTATUS                   (*VerifyCrcSource)(struct _DRSD_CRTC* Crtc, string Source, size_t* SourceCount);
    string                      (*GetCrcSources)(struct _DRSD_CRTC* Crtc, size_t* Count);
    uint32_t                    (*GetVBlankCounter)(struct _DRSD_CRTC* Crtc);
    LOUSTATUS                   (*EnableVBlank)(struct _DRSD_CRTC* Crtc);
    void                        (*DsiableVBlank)(struct _DRSD_CRTC* Crtc);
    bool                        (*GetVBlankTimeStamp)(struct _DRSD_CRTC* Crtc, int* MaxErrors, uint64_t Time, bool IRQ);
}DRSD_CRTC_CALLBACK, * PDRSD_CRTC_CALLBACK;

typedef struct _DRSD_CRTC{
    ListHeader                      Peers;
    struct _DRSD_DEVICE*            Device;
    bool                            Enabled;
    PDRSD_FRAME_BUFFER              Framebuffer;
    DRSD_DISPLAY_MODE               DisplayMode;
    PDRSD_PLANE                     PrimaryPlane;
    PDRSD_PLANE                     CursorPlane;
    PDRSD_CRTC_CALLBACK             CrtcCallbacks;
    PDRSD_CRTC_ASSIST_CALLBACK      AssistCallbacks;
    size_t                          GammaSize;
    uint16_t*                       GammaStore;
    PDRSD_CRTC_STATE                CrtcState;    
}DRSD_CRTC, * PDRSD_CRTC;


typedef struct _DRSD_MODE_CONFIGURATION_CALLBACKS{
    PDRSD_FRAME_BUFFER              (*CreateFrameBuffer)(struct _DRSD_DEVICE* Device, void* DrsdBuffer, void* CommandBuffer);
    PDRSD_FORMAT_INFORMATION        (*GetFormatInformation)(void* CommandBuffer);
    DRSD_MODE_STATUS                (*ModeValid)(struct _DRSD_DEVICE* Device, PDRSD_DISPLAY_MODE DisplayMode);
    LOUSTATUS                       (*AtomicCheck)(struct _DRSD_DEVICE* Device, void* Ah);
    LOUSTATUS                       (*AtomicSet)(struct _DRSD_DEVICE* Device, void* Ah, bool NonBlock);
    void*                           (*AcquireAtomic)(struct _DRSD_DEVICE* Device);
    void*                           (*AtomicReset)(void* Ah);
    void*                           (*ReleaseAtomic)(struct _DRSD_DEVICE* Device);
}DRSD_MODE_CONFIGURATION_CALLBACKS, * PDRSD_MODE_CONFIGURATION_CALLBACKS;

typedef struct _DRSD_VBLANK_CRTC{
    ListHeader  Peers;
    atomic_t    Count;
    size_t      InModeset;
}DRSD_VBLANK_CRTC, * PDRSD_VBLANK_CRTC;

typedef struct _DRSD_MODE_CONFIGURATION{
    mutex_t                                 ConfigLock;
    mutex_t                                 ConnectionMutex;
    PDRSD_MODE_CONFIGURATION_CALLBACKS      Callbacks;
    size_t                                  MinimalWidth;
    size_t                                  MinimalHeight;
    size_t                                  MaximumWidth;
    size_t                                  MaximumHeight;
    size_t                                  SuggestedX;
    size_t                                  SuggestedY;
    uint8_t                                 PreferedDepth;
    size_t                                  TotalPlanes;
    uint32_t                                EnabledPlanes;
    uint32_t                                InitializedPlanes;
    struct _DRSD_PLANE*                     Planes;
    uint64_t                                ValidFormats;
    uint32_t*                               Formats;
    bool                                    UsingPolling;
}DRSD_MODE_CONFIGURATION, * PDRSD_MODE_CONFIGURATION;

typedef struct _DRSD_MODE_SET_CONTEXT{
    ListHeader              Peers;
    mutex_t                 ModeSetLock;
    bool                    Interruptable;
    struct _DRSD_DEVICE*    Device;
    size_t                  EpochCounter;
}DRSD_MODE_SET_CONTEXT, * PDRSD_MODE_SET_CONTEXT;

typedef struct _DRSD_DEVICE{
    ListHeader                      Peers;
    struct _PCI_DEVICE_OBJECT*      PDEV;
    struct _LMPOOL_DIRECTORY*       VramPool;
    DRSD_MODE_CONFIGURATION         ModeConfiguration;
    DRSD_MODE_OBJECT                BaseMode;
    PDRSD_DISPLAY_MODE              DisplayModes;
    uint32_t                        PossibleCrtcs;
    size_t                          CrtcCount;
    PDRSD_PLANE                     Planes;
    PDRSD_CRTC                      Crtcs;
    PDRSD_ENCODER                   Encoders;
    PDRSD_CONNECTOR                 Connectors;
    spinlock_t                      VBlankLock;
    size_t                          VBlankCount;
    PDRSD_VBLANK_CRTC               VBlanks;
}DRSD_DEVICE, * PDRSD_DEVICE;

#define STANDARD_INTEL_CHIPSET_EDID_SIZE 128

typedef struct __attribute__((packed)) _EDID_PRODUCT_IDENTIFICATION{
    uint16_t Manufacturer;
    uint16_t ProductCode;
    uint32_t Serial;
    uint8_t  WeekOfFacture;
    uint8_t  YearOfFacture;
}EDID_PRODUCT_IDENTIFICATION, * PEDID_PRODUCT_IDENTIFICATION;

typedef struct __attribute__((packed)) _DETAILED_PIXEL_TIMING{
    uint8_t HActiveLow;
    uint8_t HBlankLow;
    uint8_t HActiveHBlankHigh;
    uint8_t VActiveLow;
    uint8_t VBlankLow;
    uint8_t VActiveVBlankHigh;
    uint8_t HSyncLow;
    uint8_t HSyncPulseWidthLow;
    uint8_t HSyncPulseWidthHigh;
    uint8_t WidthMetricLow;
    uint8_t HeightMetricLow;
    uint8_t WidthHeightMetricHigh;
    uint8_t HBorder;
    uint8_t VBorder;
    uint8_t Misc;
}DETAILED_PIXEL_TIMING, * PDETAILED_PIXEL_TIMING;   

typedef struct __attribute__((packed)) _CVT_TIMING{
    uint8_t Code[3];
}CVT_TIMING, * PCVT_TIMING;

typedef struct __attribute__((packed)) _DETAILED_WINDOWS_WP_INDEX{
    uint8_t WhiteXyLow;
    uint8_t WhiteXHigh;
    uint8_t WhiteYHigh;
    uint8_t Gamma;
}DETAILED_WINDOWS_WP_INDEX, * PDETAILED_WINDOWS_WP_INDEX;

typedef struct __attribute__((packed)) _DETAILED_DATA_MONITOR_RANGE{
    uint8_t MinVFreq;
    uint8_t MaxVFreq;
    uint8_t MinHFreqKhz;
    uint8_t MaxHFreqKhz;
    uint8_t MhzPixelClock;
    uint8_t Flags;
    union {
        struct {
            uint8_t  Reserved;
            uint8_t  HFreqStartKhz;
            uint8_t  C;
            uint16_t M;
            uint8_t  K;
            uint8_t  J;
        }__attribute__((packed)) Gtf2;
        struct {
            uint8_t Version;
            uint8_t Data1;
            uint8_t Data2;
            uint8_t SupportedAsspects;
            uint8_t Flags;
            uint8_t SupportedScailings;
            uint8_t PreferedRefresh;
        }__attribute__((packed)) Cvt;
    }__attribute__((packed)) Form;
}DETAILED_DATA_MONITOR_RANGE, * PDETAILED_DATA_MONITOR_RANGE;

typedef struct __attribute__((packed)) _DETAILED_DATA_STRING{
    uint8_t String[13];
}DETAILED_DATA_STRING, * PDETAILED_DATA_STRING;

typedef struct __attribute__((packed)) _DETAILED_NON_PIXEL_TIMING{
    uint8_t Pad1;
    uint8_t Type;
    uint8_t Pad2;
    union{
        DETAILED_DATA_STRING String;
        DETAILED_DATA_MONITOR_RANGE MonitorRange;
        DETAILED_WINDOWS_WP_INDEX Color;
        struct {
            uint8_t HSize;
            uint8_t AspectFrequenc;
        }StdTime;
        CVT_TIMING Cvt[4];
    }__attribute__((packed));
}DETAILED_NON_PIXEL_TIMING, * PDETAILED_NON_PIXEL_TIMING;

typedef struct __attribute__((packed)) _DETAILED_TIMING{
    uint16_t PixelClock;
    union{
        DETAILED_PIXEL_TIMING       PixelData;
        DETAILED_NON_PIXEL_TIMING   OtherData;
    }__attribute__((packed)) Data;
}DETAILED_TIMING, * PDETAILED_TIMING;

typedef struct __attribute__((packed)) _INTEL_STANDARD_EDID{
    uint8_t     Header[8];
    union {
        EDID_PRODUCT_IDENTIFICATION ProductIdentification;
        struct {
            uint8_t     Manufacturer[2];
            uint8_t     ProductCode[2];
            uint32_t    Serial;
            uint8_t     WeekOfFacture;
            uint8_t     YearOfFacture;
        }__attribute__((packed));
    }__attribute__((packed));
    uint8_t Version;
    uint8_t Revision;
    uint8_t Input;
    uint8_t WidthMetric;
    uint8_t HeightMetric;
    uint8_t Gamma;
    uint8_t Features;
    uint8_t RedGreeLow;
    uint8_t BlueWhiteLow;
    uint8_t RedX;
    uint8_t RedY;
    uint8_t GreenX;
    uint8_t GreenY;
    uint8_t BlueX;
    uint8_t BlueY;
    uint8_t WhiteX;
    uint8_t WhiteY;
    struct {
        uint8_t T1;
        uint8_t T2;
        uint8_t Reserved;
    }__attribute__((packed)) EstTime[8];
    struct {
        uint8_t HSize;
        uint8_t AspectFrequenc;
    }__attribute__((packed)) Timing[4];
    uint8_t Extentions;
    uint8_t Checksum;
}INTEL_STANDARD_EDID, * PINTEL_STANDARD_EDID; 

typedef struct _DRSD_EDID_TRACKER{
    ListHeader              Peers;
    size_t                  EdidTotalSize; // 128 or more for non standard
    PINTEL_STANDARD_EDID    EdidBase;
}DRSD_EDID_TRACKER, * PDRSD_EDID_TRACKER;


#define RGB_DRSD_FRAMEBUFFER 1
#define EGA_DRSD_FRAMEBUFFER 2

#define DRSD_CORE_TRANSLATE_COLOR(R, G, B, A) (uint32_t)(((uint32_t)A << 24) | ((uint32_t)R << 16) | ((uint32_t)G << 8) | (uint32_t)B)

typedef enum {
    CLIP_DESTROYED = 0,
    
}DRSD_CLIP_UPDATE_REASON;

struct _DRSD_CLIP_CHAIN;

typedef struct _DRSD_CLIP{
    ListHeader              Peers;
    PDRSD_PLANE             Owner;
    struct _DRSD_CLIP_CHAIN* ChainOwner;
    void                    (*SignalClipChange)(struct _DRSD_CLIP*, DRSD_CLIP_UPDATE_REASON, void* UpdateData);
    size_t                  X;
    size_t                  Y;
    size_t                  Width;
    size_t                  Height;
    uint32_t*               WindowBuffer;
    size_t                  RedShift;
    size_t                  BlueShift;
    size_t                  GreenShift;
    size_t                  AlphaShift;
}DRSD_CLIP, * PDRSD_CLIP;

typedef struct _DRSD_LAYERED_CLIP{
    PDRSD_CLIP  ForwardClip;
    PDRSD_CLIP  RearClip;
    DRSD_CLIP   CurrentClip; 
}DRSD_LAYERED_CLIP, * PDRSD_LAYERED_CLIP;

typedef struct _DRSD_CLIP_CHAIN{
    ListHeader  Peers;
    PDRSD_PLANE Owner;    
    PDRSD_CLIP  Clips;
    void        (*PrimaryAtomicUpdate)(PDRSD_PLANE, void* Handle);
    bool        PlaneReady;
}DRSD_CLIP_CHAIN, * PDRSD_CLIP_CHAIN;


#ifndef _KERNEL_MODULE_

void LouKeDestroyClip(PDRSD_CLIP Clip);

void LouKeDrsdUpdateClipColor(PDRSD_CLIP Clip, uint32_t Color);
void LouKeUpdateClipState(PDRSD_CLIP Clip);

void LouKeDrsdHandleConflictingDevices(struct _PCI_DEVICE_OBJECT* PDEV);
void LouKeOsDosUpdateMapping();

void LouKeDrsdCoreClipPlotLine(
  PDRSD_CLIP Clip,
  int x0, int y0, int x1, int y1,
  uint8_t r,uint8_t g,uint8_t b
);


void LouKeDrsdCoreClipPlotLineDword(
  PDRSD_CLIP Clip,
  int x0, int y0, int x1, int y1,
  uint32_t Color
);

void LouKeDrsdClipPutPixel(
    PDRSD_CLIP Clip, 
    int64_t X, 
    int64_t Y, 
    uint32_t Color
);

void LouKeOsDosPrintCharecter(char Character);

void DirectAccessDrsdHotplugEvent(PDRSD_DEVICE Device);

LOUSTATUS LouKePassVramToDrsdMemoryManager(PDRSD_DEVICE Device, void* VramBase, size_t size, void* PAddress);

PDRSD_FRAME_BUFFER DrsdGxeCreateAsyncFramebuffer(
    PDRSD_DEVICE    Device,
    void*           DrsdBuffer,
    void*           DrsdCommandBuffer
);

DRSD_MODE_STATUS DrsdGxeVramInternalModeValid(
    PDRSD_DEVICE        Devics,
    PDRSD_DISPLAY_MODE  DisplayMode
);

LOUSTATUS DrsdInternalAtomicCheck(
    PDRSD_DEVICE        Device,
    void*               AtomicHandle
);

LOUSTATUS DrsdInternalAtomicUpdate(
    PDRSD_DEVICE        Device,
    void*               AtomicHandle,
    bool                NonBlock
);

LOUSTATUS DrsdInternalPlaneUpdateAtomic(
    PDRSD_PLANE                     Plane,
    PDRSD_CRTC                      Crtc,
    PDRSD_FRAME_BUFFER              FrameBuffer,
    int                             CrtcX, 
    int                             CrctY, 
    int                             CrtcWidth, 
    int                             CrtcHeight,
    uint32_t                        SourceX, 
    uint32_t                        SourceY, 
    uint32_t                        SourceWidth, 
    uint32_t                        SourceHeight,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext
);

LOUSTATUS DrsdInternalPlaneDisableAtomic(
    PDRSD_PLANE                     Plane,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext            
);

void DrsdInternalDestroyPlane(
    PDRSD_PLANE Plane
);

void DrsdInternalResetPlane(
    PDRSD_PLANE Plane
);

PDRSD_PLANE_STATE DrsdInternalDuplicateAtomicState(
    PDRSD_PLANE         Plane
);

void DrsdInternalDestroyPlaneAtomic(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

void DrsdGxeInternalCleanupFrameBuffer(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

LOUSTATUS DrsdGxeInternalPrepareFrameBuffer(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

LOUSTATUS DrsdGxeInternalStartFrameBufferProcessing(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

void DrsdGxeInternalStopFrameBufferProcessing(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

void DrsdGxeResetShadowPlane(
    PDRSD_PLANE         Plane
);

PDRSD_PLANE_STATE DrsdGxeDuplicateShadowPlaneState(
    PDRSD_PLANE Plane
);

void DrsdGxeDestroyShadowPlane(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

LOUSTATUS DrsdInitializeGenericPlane(
    PDRSD_DEVICE            Device, 
    PDRSD_PLANE             Plane,
    size_t                  CrtcLimit,
    PDRSD_PLANE_CALLBACKS   PlaneCallbacks,
    uint32_t*               PlaneFormats,
    size_t                  FormatCount,
    uint64_t*               FormatModifiers,
    DRSD_PLANE_TYPE         PlaneType,
    string                  Name,
    ...
);

LOUSTATUS DrsdInitializeCrtcWithPlanes(
    PDRSD_DEVICE            Device,
    PDRSD_CRTC              Crtc,
    PDRSD_PLANE             Primary,
    PDRSD_PLANE             Cursor,
    PDRSD_CRTC_CALLBACK     CrtcCallbacks
);


LOUSTATUS DrsdInitializeCrtcGammaSize(
    PDRSD_CRTC  Crtc,
    size_t      GammaSize
);

void DrsdInternalCrtcDestroyStateAtomic(
    PDRSD_CRTC  Crtc,
    void*       StateData
);

void* DrsdInternalCrtcDuplicateStateAtomic(
    PDRSD_CRTC          Crtc
);

void DrsdInternalCrtcResetAtomic(
    PDRSD_CRTC          Crtc 
);

LOUSTATUS DrsdInternalCrtcPageFlipAtomic(
    PDRSD_CRTC                      Crtc,
    PDRSD_FRAME_BUFFER              FrameBuffer,
    void*                           VBlankEvent,
    uint32_t                        Flags,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext
);

LOUSTATUS DrsdInternalCrtcSetConfigurationAtomic(
    void*                           Mode,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext
);

LOUSTATUS DrsdInitializeEncoder(
    PDRSD_DEVICE                Device,
    PDRSD_ENCODER               Encoder,
    PDRSD_ENCODER_CALLBACKS     Callbacks,
    int                         EncoderType,
    string                      EncoderName,
    ...
);

void DrsdInternalAtomicConnectorDestroyState(
    PDRSD_CONNECTOR         Connector,
    PDRSD_CONNECTOR_STATE   State
);

PDRSD_CONNECTOR_STATE DrsdInternalAtomicConnectorDuplicateState(PDRSD_CONNECTOR Connector);

void DrsdInternalResetConnector(PDRSD_CONNECTOR Connector);

LOUSTATUS DrsdConnectorInitialize(
    PDRSD_DEVICE                Device,
    PDRSD_CRTC                  Crtc,
    PDRSD_CONNECTOR             Connector,
    PDRSD_CONNECTOR_CALLBACKS   Callbacks,
    int                         ConnectorType
);

void DrsdModeConfigurationReset(PDRSD_DEVICE Device);

LOUSTATUS DrsdInternalProbeSingleConnectorModes(
    PDRSD_CONNECTOR Connector,
    uint32_t        MaxX,
    uint32_t        MaxY
);

size_t DrsdAddModesNoEDID(
    PDRSD_CONNECTOR Connector, 
    int32_t Width, 
    int32_t Height
);
size_t DrsdModeVfresh(PDRSD_DISPLAY_MODE Mode);

PDRSD_DISPLAY_MODE DrsdCvtMode(
    PDRSD_DEVICE Device, 
    uint32_t PreferedWidth, 
    uint32_t PreferedHeight, 
    uint32_t Vfresh, 
    bool Reduced, 
    bool Interlaced, 
    bool Margins
);
void DrsdAddProbedDisplayModeToConnector(PDRSD_CONNECTOR Connector, PDRSD_DISPLAY_MODE Mode);

LOUSTATUS DrsdUpdateEdidConnectorProperties(PDRSD_CONNECTOR Connector, PINTEL_STANDARD_EDID Edid);

PDRSD_PLANE_STATE DrsdGetNewPlaneState(PDRSD_PLANE_STATE OldState, PDRSD_PLANE Plane);

void LouKeDrsdClearScreen(PDRSD_PLANE Plane);

#endif
#ifdef __cplusplus
}
#ifdef _KERNEL_MODULE_

KERNEL_EXPORT 
PDRSD_FRAME_BUFFER DrsdGxeCreateAsyncFramebuffer(
    PDRSD_DEVICE    Device,
    void*           DrsdBuffer,
    void*           DrsdCommandBuffer
);

KERNEL_EXPORT
DRSD_MODE_STATUS DrsdGxeVramInternalModeValid(
    PDRSD_DEVICE        Devics,
    PDRSD_DISPLAY_MODE  DisplayMode
);

KERNEL_EXPORT
LOUSTATUS DrsdInternalAtomicCheck(
    PDRSD_DEVICE        Device,
    void*               AtomicHandle
);

KERNEL_EXPORT
LOUSTATUS DrsdInternalAtomicUpdate(
    PDRSD_DEVICE        Device,
    void*               AtomicHandle,
    bool                NonBlock
);

KERNEL_EXPORT
LOUSTATUS DrsdInternalPlaneUpdateAtomic(
    PDRSD_PLANE                     Plane,
    PDRSD_CRTC                      Crtc,
    PDRSD_FRAME_BUFFER              FrameBuffer,
    int                             CrtcX, 
    int                             CrctY, 
    int                             CrtcWidth, 
    int                             CrtcHeight,
    uint32_t                        SourceX, 
    uint32_t                        SourceY, 
    uint32_t                        SourceWidth, 
    uint32_t                        SourceHeight,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext
);

KERNEL_EXPORT
LOUSTATUS DrsdInternalPlaneDisableAtomic(
    PDRSD_PLANE                     Plane,
    struct _DRSD_MODE_SET_CONTEXT*  ModeSetAquireContext            
);

KERNEL_EXPORT
void DrsdInternalDestroyPlane(
    PDRSD_PLANE Plane
);

KERNEL_EXPORT
void DrsdInternalResetPlane(
    PDRSD_PLANE Plane
);

KERNEL_EXPORT
PDRSD_PLANE_STATE DrsdInternalDuplicateAtomicState(
    PDRSD_PLANE         Plane
);

KERNEL_EXPORT
void DrsdInternalDestroyPlaneAtomic(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

KERNEL_EXPORT
void DrsdGxeInternalCleanupFrameBuffer(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

KERNEL_EXPORT
LOUSTATUS DrsdGxeInternalPrepareFrameBuffer(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

KERNEL_EXPORT
LOUSTATUS DrsdGxeInternalStartFrameBufferProcessing(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

KERNEL_EXPORT
void DrsdGxeInternalStopFrameBufferProcessing(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

KERNEL_EXPORT
void DrsdGxeResetShadowPlane(
    PDRSD_PLANE         Plane
);

KERNEL_EXPORT
PDRSD_PLANE_STATE DrsdGxeDuplicateShadowPlaneState(
    PDRSD_PLANE Plane
);

KERNEL_EXPORT
void DrsdGxeDestroyShadowPlane(
    PDRSD_PLANE         Plane,
    PDRSD_PLANE_STATE   PlaneState
);

KERNEL_EXPORT
LOUSTATUS DrsdInitializeGenericPlane(
    PDRSD_DEVICE            Device, 
    PDRSD_PLANE             Plane,
    size_t                  CrtcLimit,
    PDRSD_PLANE_CALLBACKS   PlaneCallbacks,
    uint32_t*               PlaneFormats,
    size_t                  FormatCount,
    uint64_t*               FormatModifiers,
    DRSD_PLANE_TYPE         PlaneType,
    string                  Name,
    ...
);

KERNEL_EXPORT
LOUSTATUS DrsdInitializeCrtcWithPlanes(
    PDRSD_DEVICE            Device,
    PDRSD_CRTC              Crtc,
    PDRSD_PLANE             Primary,
    PDRSD_PLANE             Cursor,
    PDRSD_CRTC_CALLBACK     CrtcCallbacks
);

KERNEL_EXPORT
LOUSTATUS DrsdInitializeCrtcGammaSize(
    PDRSD_CRTC  Crtc,
    size_t      GammaSize
);

KERNEL_EXPORT
void DrsdInternalCrtcDestroyStateAtomic(
    PDRSD_CRTC  Crtc,
    PDRSD_CRTC_STATE       StateData
);

KERNEL_EXPORT
PDRSD_CRTC_STATE DrsdInternalCrtcDuplicateStateAtomic(
    PDRSD_CRTC          Crtc
);

KERNEL_EXPORT
void DrsdInternalCrtcResetAtomic(
    PDRSD_CRTC          Crtc 
);

KERNEL_EXPORT
LOUSTATUS DrsdInternalCrtcPageFlipAtomic(
    PDRSD_CRTC                          Crtc,
    PDRSD_FRAME_BUFFER                  FrameBuffer,
    void*                               VBlankEvent,
    uint32_t                            Flags,
    struct _DRSD_MODE_SET_CONTEXT*      ModeSetAquireContext
);

KERNEL_EXPORT
LOUSTATUS DrsdInternalCrtcSetConfigurationAtomic(
    void*                               Mode,
    struct _DRSD_MODE_SET_CONTEXT*      ModeSetAquireContext
);

KERNEL_EXPORT
LOUSTATUS DrsdInitializeEncoder(
    PDRSD_DEVICE                Device,
    PDRSD_ENCODER               Encoder,
    PDRSD_ENCODER_CALLBACKS     Callbacks,
    int                         EncoderType,
    string                      EncoderName,
    ...
);

KERNEL_EXPORT
void DrsdInternalAtomicConnectorDestroyState(
    PDRSD_CONNECTOR         Connector,
    PDRSD_CONNECTOR_STATE   State
);

KERNEL_EXPORT
PDRSD_CONNECTOR_STATE DrsdInternalAtomicConnectorDuplicateState(PDRSD_CONNECTOR Connector);

KERNEL_EXPORT
void DrsdInternalResetConnector(PDRSD_CONNECTOR Connector);

KERNEL_EXPORT
LOUSTATUS DrsdConnectorInitialize(
    PDRSD_DEVICE                Device,
    PDRSD_CRTC                  Crtc,
    PDRSD_CONNECTOR             Connector,
    PDRSD_CONNECTOR_CALLBACKS   Callbacks,
    int                         ConnectorType
);

KERNEL_EXPORT
void DrsdModeConfigurationReset(PDRSD_DEVICE Device);

KERNEL_EXPORT
LOUSTATUS DrsdInternalProbeSingleConnectorModes(
    PDRSD_CONNECTOR Connector,
    uint32_t        MaxX,
    uint32_t        MaxY
);

KERNEL_EXPORT
size_t DrsdAddModesNoEDID(
    PDRSD_CONNECTOR Connector, 
    int32_t Width, 
    int32_t Height
);

KERNEL_EXPORT size_t DrsdModeVfresh(PDRSD_DISPLAY_MODE Mode);

KERNEL_EXPORT
PDRSD_DISPLAY_MODE DrsdCvtMode(
    PDRSD_DEVICE Device, 
    uint32_t PreferedWidth, 
    uint32_t PreferedHeight, 
    uint32_t Vfresh, 
    bool Reduced, 
    bool Interlaced, 
    bool Margins
);

KERNEL_EXPORT
void DrsdAddProbedDisplayModeToConnector(PDRSD_CONNECTOR Connector, PDRSD_DISPLAY_MODE Mode);


KERNEL_EXPORT
LOUSTATUS DrsdUpdateEdidConnectorProperties(PDRSD_CONNECTOR Connector, PINTEL_STANDARD_EDID Edid);

KERNEL_EXPORT PDRSD_PLANE_STATE DrsdGetNewPlaneState(PDRSD_PLANE_STATE OldState, PDRSD_PLANE Plane);

KERNEL_EXPORT void LouKeDrsdHandleConflictingDevices(struct _PCI_DEVICE_OBJECT* PDEV);

#endif
#endif
#endif 