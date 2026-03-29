 /*
 * Copyright (c) 2026 AnnyaOS
 *
 * This file is a derivative work based on Linux DRM,
 * Copyright (c) 1994 - current
 *   - Dave Airlie          <airlied@linux.ie>
 *   - Daniel Vetter        <daniel.vetter@ffwll.ch>
 *   - Thomas Hellstrom     <thomas@vmware.com>
 *   - Alex Deucher         <alexander.deucher@amd.com>
 *   - Michel Dänzer        <michel@daenzer.net>
 *   - The X.Org / Mesa / DRM community
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _DRSD_H
#define _DRSD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel/LouQs.h>
#include <ListManagement.h>
#include <kernel/Objects.h>
#include <Ldm/CommonTypes.h>
#include <kernel/XArray.h>
#include <drivers/Hdmi/Picture.h>
#include <drivers/Notifications.h>
#include <drivers/Hdmi/Info.h>

#define DRSD_ROTATION_MODE_0 1

#define DRSD_PIXEL_BLEND_PRE_MULTI 1

#define DRSD_MAXIMUM_OBJECT_PROPERTIES 64

#define DRSD_GXE_VRAM_DRIVER \
    .DumbCreate = DrsdGxeVRamDriverDumbCreate, \
    .DumbMapOffset = DrsdGxeTtmDumbMapOffset



struct _DRSD_FRAME_BUFFER;
struct _DRSD_PLANE;
struct _DRSD_CRTC;
struct _DRSD_ENCODER_CALLBACKS;
struct _DRSD_ENCODER_ASSISTED_CALLBACKS;
struct _DRSD_CRTC_STATE;
struct _DRSD_CONNECTOR;
struct _DRSD_PROPERTY;
struct _DRSD_MODE_SET_CONTEXT;
struct _DRSD_PRIVATE_OBJECT;
struct _DRSD_COLOR_OP;
struct _DRSD_ATOMIC_STATE;

//8 bit color
#define DRSD_COLOR_FORMAT_RGB332    'RGB8'
#define DRSD_COLOR_FORMAT_BGR233    'BGR8'

//16 bit Color
#define DRSD_COLOR_FORMAT_XRGB4444  'XR12'
#define DRSD_COLOR_FORMAT_XBGR4444  'XB12'
#define DRSD_COLOR_FORMAT_RGBX4444  'RX12'
#define DRSD_COLOR_FORMAT_BGRX4444  'XB12'
//Alpha 16 bit color
#define DRSD_COLOR_FORMAT_ARGB4444  'AR12'
#define DRSD_COLOR_FORMAT_ABGR4444  'AB12'
#define DRSD_COLOR_FORMAT_RGBA4444  'RA12'
#define DRSD_COLOR_FORMAT_BGRA4444  'BA12'
//PBD 16 bit color
#define DRSD_COLOR_FORMAT_XRGB1555  'XR15'
#define DRSD_COLOR_FORMAT_XBGR1555  'XB15'
#define DRSD_COLOR_FORMAT_RGBX5551  'RX15'
#define DRSD_COLOR_FORMAT_BGRX5551  'BX15'

#define DRSD_COLOR_FORMAT_ARGB1555  'AR15'
#define DRSD_COLOR_FORMAT_ABGR1555  'AB15'
#define DRSD_COLOR_FORMAT_RGBA5551  'RA15'
#define DRSD_COLOR_FORMAT_BGRA5551  'BA15'


#define DRSD_COLOR_FORMAT_RGB565    'RG16'
#define DRSD_COLOR_FORMAT_GRB565    'BG16'

//24 true RGB
#define DRSD_COLOR_FORMAT_RGB888    'RG24'
#define DRSD_COLOR_FORMAT_BBR888    'BG24'

//32 true RGB
#define DRSD_COLOR_FORMAT_XRGB8888  'XR24'
#define DRSD_COLOR_FORMAT_XBGR8888  'XB24'
#define DRSD_COLOR_FORMAT_RGBX8888  'RX24'
#define DRSD_COLOR_FORMAT_BGRX8888  'BX24'
//Alpha True RGB
#define DRSD_COLOR_FORMAT_ARGB8888  'AR24'
#define DRSD_COLOR_FORMAT_ABGR8888  'AB24'
#define DRSD_COLOR_FORMAT_RGBA8888  'RA24'
#define DRSD_COLOR_FORMAT_BGRA8888  'BA24'
//PBD 32 bit True RGB

//48 Bit RGB
#define DRSD_COLOR_FORMAT_XRGB2101010 'XR30'
#define DRSD_COLOR_FORMAT_XBGR2101010 'XB30'
#define DRSD_COLOR_FORMAT_RGBX1010102 'RX30'
#define DRSD_COLOR_FORMAT_BGRX1010102 'BX30'

#define DRSD_COLOR_FORMAT_ARGB2101010 'AR30'
#define DRSD_COLOR_FORMAT_ABGR2101010 'AB30'
#define DRSD_COLOR_FORMAT_RGBA1010102 'RX30'
#define DRSD_COLOR_FORMAT_BGRA1010102 'BX30'

#define DRSD_MODE_OBJECT_CRTC           0xCCCCCCCC
#define DRSD_MODE_OBJECT_CONNECTOR      0xC0C0C0C0
#define DRSD_MODE_OBJECT_ENCODER        0xE0E0E0E0
#define DRSD_MODE_OBJECT_MODE           0xDEDEDEDE
#define DRSD_MODE_OBJECT_PROPERTY       0xB0B0B0B0
#define DRSD_MODE_OBJECT_FB             0xFBFBFBFB
#define DRSD_MODE_OBJECT_BLOB           0xBBBBBBBB
#define DRSD_MODE_OBJECT_PLANE          0xEEEEEEEE
#define DRSD_MODE_OBJECT_COLOROP        0xFAFAFAFA
#define DRSD_MODE_OBJECT_ANY            0



typedef enum _DRSD_SCALING_FILTER{
    DRSD_SCALING_FILTER_DEFAULT = 0,
    DRSD_SCALING_FILTER_NEAREST_NEIGHBOR ,
}DRSD_SCALING_FILTER, * PDRSD_SCALING_FILTER;

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

typedef enum _DRSD_MODE_SUB_CONNECTOR{
    DRSD_MODE_SUBCONNECTOR_AUTOMATIC = 0,
    DRSD_MODE_SUBCONNECTOR_UNKOWN = 0,
    DRSD_MODE_SUBCONNECTOR_VGA = 1,
    DRSD_MODE_SUBCONNECTOR_DVID = 3,
    DRSD_MODE_SUBCONNECTOR_DVIA = 4,
    DRSD_MODE_SUBCONNECTOR_COMPOSITE = 5,
    DRSD_MODE_SUBCONNECTOR_SVIDEO = 6,
    DRSD_MODE_SUBCONNECTOR_COMPONENT = 8,
    DRSD_MODE_SUBCONNECTOR_SCART = 9,
    DRSD_MODE_SUBCONNECTOR_DISPLAY_PORT = 10,
    DRSD_MODE_SUBCONNECTOR_HDMIA = 11,
    DRSD_MODE_SUBCONNECTOR_NATIVE = 15,
    DRSD_MODE_SUBCONNECTOR_WIRELESS = 18
}DRSD_MODE_SUB_CONNECTOR, * PDRSD_MODE_SUB_CONNECTOR;

typedef enum _DRSD_COLOR_SPACE{
    DRSD_MODE_COLORIMETRY_DEFAULT = 0,
    DRSD_MODE_COLORIMETRY_NO_DATA = 0,
    DRSD_MODE_COLORIMETRY_SMPTE_170M_YCC = 1,
    DRSD_MODE_COLORIMETRY_BT_709_YCC = 2,
    DRSD_MODE_COLORIMETRY_XVYCC_601 = 3,
    DRSD_MODE_COLORIMETRY_XVYCC_709 = 4,
    DRSD_MODE_COLORIMETRY_SYCC_601 = 5,
    DRSD_MODE_COLORIMETRY_OPYCC_601 = 6,
    DRSD_MODE_COLORIMETRY_OPRGB = 7,
    DRSD_MODE_COLORIMETRY_BT2020_CYCC = 8,
    DRSD_MODE_COLORIMETRY_BT2020_RGB = 9,
    DRSD_MODE_COLORIMETRY_BT2020_YCC = 10,
    DRSD_MODE_COLORIMETRY_DCI_P3_RGB_D65 = 11,
    DRSD_MODE_COLORIMETRY_DCI_P3_RGB_THEATER = 12,
    DRSD_MODE_COLORIMETRY_RGB_WIDE_FIXED = 13,
    DRSD_MODE_COLORIMETRY_RGB_WIDE_FLOAT = 14,
    DRSD_MODE_COLORIMETRY_BT601_YCC = 15,
    DRSD_MODE_COLORIMETRY_COUNT,
}DRSD_COLOR_SPACE, * PDRSD_COLOR_SPACE;

typedef enum _DRSD_DRIVER_FEATURES{
    DRIVER_GXE = (1 << 0),
    DRIVER_MODESET = (1 << 1),
    DRIVER_RENDER = (1 << 3),
    DRIVER_ATOMIC = (1 << 4),
    DRIVER_SYNCOBJ = (1 << 5),
    DRIVER_SYNCOBJ_TIMELINE = (1 << 6),
    DRIVER_COMPUTE_ACCEL = (1 << 7),
    DRIVER_GXE_GPUVA = (1 << 8),
    DRIVER_CURSOR_HOTSPOT = (1 << 9),
    DRIVER_USE_AGP = (1 << 25),
    DRIVER_LEGACY = (1 << 26),
    DRIVER_PCI_DMA = (1 << 27),
    DRIVER_SG = (1 << 28),
    DRIVER_HAVE_DMA = (1 << 29),
    DRIVER_HAVE_IRQ = (1 << 30),
}DRSD_DRIVER_FEATURES, * PDRSD_DRIVER_FEATURES;

typedef enum _DRSD_MINOR_TYPE{
    DRSD_MINOR_PRIMARY = 0,
    DRSD_MINOR_CONTROL,
    DRSD_MINOR_RENDER,
    DRSD_MINOR_ACCEL,
}DRSD_MINOR_TYPE, * PDRSD_MINOR_TYPE;

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

#define DRSD_MODE_CONNECTOR_UNKOWN	        0
#define DRSD_MODE_CONNECTOR_VGA		        1
#define DRSD_MODE_CONNECTOR_DVII		    2
#define DRSD_MODE_CONNECTOR_DVID		    3
#define DRSD_MODE_CONNECTOR_DVIA		    4
#define DRSD_MODE_CONNECTOR_COMPOSITE	    5
#define DRSD_MODE_CONNECTOR_SVIDEO	        6
#define DRSD_MODE_CONNECTOR_LVDS		    7
#define DRSD_MODE_CONNECTOR_Component	    8
#define DRSD_MODE_CONNECTOR_9PINDIN	        9
#define DRSD_MODE_CONNECTOR_DISPLAY_PORT	10
#define DRSD_MODE_CONNECTOR_HDMIA	        11
#define DRSD_MODE_CONNECTOR_HDMIB	        12
#define DRSD_MODE_CONNECTOR_TV		        13
#define DRSD_MODE_CONNECTOR_eDP		        14
#define DRSD_MODE_CONNECTOR_VIRTUAL         15
#define DRSD_MODE_CONNECTOR_DSI		        16
#define DRSD_MODE_CONNECTOR_DPI		        17
#define DRSD_MODE_CONNECTOR_WRITEBACK	    18
#define DRSD_MODE_CONNECTOR_SPI		        19
#define DRSD_MODE_CONNECTOR_USB		        20


typedef struct _DRSD_CONNECTOR_TV_MARGINS{
    UINT    Bottom;
    UINT    Left;
    UINT    Right;
    UINT    Top;
}DRSD_CONNECTOR_TV_MARGINS, * PDRSD_CONNECTOR_TV_MARGINS;

typedef struct _DRSD_MODESET_LOCK{
    mutex_t     Mutex;
    ListHeader  Head;
}DRSD_MODESET_LOCK, * PDRSD_MODESET_LOCK;

typedef struct _DRSD_PROPERTY{
    uintptr_t Foo;
}DRSD_PROPERTY, * PDRSD_PROPERTY;

typedef struct _DRSD_MODE_OBJECT{
    ListHeader                          Peers;
    uint32_t                            Identification;
    uint32_t                            ModeType;
    struct _DRSD_OBJECT_PROPERTIES*     Properties;
    KERNEL_REFERENCE                    ReferenceCount;
    void                                (*FreeCb)(PKERNEL_REFERENCE Reference);
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

typedef struct _DRSD_FRAMEBUFFER_FUNCTIONS{
    void        (*DestroyFramebuffer)(struct _DRSD_FRAME_BUFFER* FrameBuffer);
    LOUSTATUS   (*CreateHandle)(struct _DRSD_FRAME_BUFFER* FrameBuffer, void* DrsdBuffer, uint32_t* Handle);
    LOUSTATUS   (*DrsdFlushFramebufferSyscall)(struct _DRSD_FRAME_BUFFER* FrameBuffer, void* DrsdBuffer, 
                                                                 uint64_t Flags, uint64_t Color, 
                                                                 void* Clip , uint64_t ClipCount);
    semaphore_t CallbackLock;
}DRSD_FRAMEBUFFER_FUNCTIONS, * PDRSD_FRAMEBUFFER_FUNCTIONS;

typedef struct _DRSD_VMA_OFFSET_NODE{
    mutex_t                     VmLock;
    struct _DRSD_MM_NODE*       VmNode;
    HANDLE                      VmFiles;
    PVOID                       DriverPrivate;
}DRSD_VMA_OFFSET_NODE, * PDRSD_VMA_OFFSET_NODE;

struct _DRSD_GXE_OBJECT;

typedef UINT DRSD_MAGIC;

typedef struct _DRSD_PRIME_FILE_PRIVATE{
    mutex_t     Lock;
    HANDLE      DmaBuffers;
    PHANDLE     Handles;
}DRSD_PRIME_FILE_PRIVATE, * PDRSD_PRIME_FILE_PRIVATE;

typedef struct _DRSD_FILE{
    BOOLEAN                 Authenticated;
    BOOLEAN                 StereoAllowed;
    BOOLEAN                 UniversalPlanes;
    BOOLEAN                 Atomic;
    BOOLEAN                 AspectRatioAllowed;
    BOOLEAN                 WritebackConnectors;
    BOOLEAN                 PlaneColorPipeline;
    BOOLEAN                 WasMaster;
    BOOLEAN                 IsMaster;
    BOOLEAN                 SupportsVirtualizedCursorPlane;
    struct _DRSD_MASTER*    Master;
    spinlock_t              MasterLookupLock;
    HANDLE                  Pid;
    UINT64                  ClientId;
    DRSD_MAGIC              DrsdMagic;
    ListHeader              Head;
    struct _DRSD_MINOR*     Minor;
    XARRAY                  ObjectIdr;
    spinlock_t              TableLock;
    XARRAY                  SyncObjectXArray;
    FILE*                   Filp;
    PVOID                   DriverPrivate;
    ListHeader              Fbs;
    mutex_t                 FbsLock;
    ListHeader              Blobs;
    LOUQ_WAIT_QUEUE         EventWait;
    ListHeader              PendingEventList;
    ListHeader              EventList;
    int                     EventSpace;
    mutex_t                 EventReadLock;
    DRSD_PRIME_FILE_PRIVATE Prime;
    LOUSTR                  ClientName;
    mutex_t                 ClientNameLock;
    HANDLE                  ClfsClient;
}DRSD_FILE, * PDRSD_FILE;

typedef enum _DRSD_GXE_OBJECT_STATUS{
    DRSD_GXE_OBJECT_RESIDENT  = (1 << 0),
    DRSD_GXE_OBJECT_PURGEABLE = (1 << 1),
    DRSD_GXE_OBJECT_ACTIVE    = (1 << 2),
}DRSD_GXE_OBJECT_STATUS, * PDRSD_GXE_OBJECT_STATUS;

typedef struct _DRSD_GXE_OBJECT_FUNCTIONS{
    void                        (*Free)(struct _DRSD_GXE_OBJECT* Object);
    LOUSTATUS                   (*Open)(struct _DRSD_GXE_OBJECT* Object, PDRSD_FILE File);
    LOUSTATUS                   (*Close)(struct _DRSD_GXE_OBJECT* Object, PDRSD_FILE File);
    LOUSTATUS                   (*PrintInfo)(HANDLE DrsdClfsServer, UINT Indent, struct _DRSD_GXE_OBJECT* Object);
    HANDLE                      (*Export)(struct _DRSD_GXE_OBJECT* Object, int Flags);
    LOUSTATUS                   (*Pin)(struct _DRSD_GXE_OBJECT* Object);
    void                        (*Unpin)(struct _DRSD_GXE_OBJECT* Object);
    HANDLE                      (*GetScatterGatherTable)(struct _DRSD_GXE_OBJECT* Object);
    LOUSTATUS                   (*Vmap)(struct _DRSD_GXE_OBJECT* Object, PIO_MAP_OBJECT IoMap);
    void                        (*Vunmap)(struct _DRSD_GXE_OBJECT* Object, PIO_MAP_OBJECT IoMap);
    LOUSTATUS                   (*Mmap)(struct _DRSD_GXE_OBJECT* Object, HANDLE Vma);
    LOUSTATUS                   (*Evict)(struct _DRSD_GXE_OBJECT* Object);
    DRSD_GXE_OBJECT_STATUS      (*Status)(struct _DRSD_GXE_OBJECT* Object);
    SIZE                        (*Rss)(struct _DRSD_GXE_OBJECT* Object);
    HANDLE                      VmmOperations;
}DRSD_GXE_OBJECT_FUNCTIONS, * PDRSD_GXE_OBJECT_FUNCTIONS;

typedef struct _DRSD_CONNECTOR_LIST_ITERATION{
    struct _DRSD_DEVICE*    Device;
    struct _DRSD_CONNECTOR* Connector;
}DRSD_CONNECTOR_LIST_ITERATION, * PDRSD_CONNECTOR_LIST_ITERATION;

typedef struct  DRSD_GXE_LRU{
    mutex_t     Lock;
    SIZE        Count;
    ListHeader  List;
}DRSD_GXE_LRU, * PDRSD_GXE_LRU;

typedef struct _DRSD_GXE_OBJECT{
    KERNEL_REFERENCE            KRef;
    UINT                        HandleCount;
    struct _DRSD_DEVICE*        Device;
    FILE                        Filp;
    DRSD_VMA_OFFSET_NODE        VmaNode;
    SIZE                        Size;
    int                         Name;
    HANDLE                      DmaBuffer;
    HANDLE                      ImportAttatch;
    HANDLE                      DmaReserve;
    HANDLE                      _DmaReserved;
    struct{
        ListHeader              List;
        mutex_t                 Lock;
    }GpuVA;
    DRSD_GXE_OBJECT_FUNCTIONS   Functions;
    ListHeader                  LruNode;        
    PDRSD_GXE_LRU               Lru;

    //old data
    semaphore_t                 ObjectLock;
    void*                       Buffers;
    struct _LMPOOL_DIRECTORY*   GxeVmaPool;
    size_t                      GxeSize;
    void*                       DmaPropertiesBuffer;
}DRSD_GXE_OBJECT, * PDRSD_GXE_OBJECT;

typedef struct _DRSD_FRAME_BUFFER{
    ListHeader                              Peers;
    struct _DRSD_DEVICE*                    Device;
    DRSD_MODE_OBJECT                        Base;
    string                                  Comm;
    PDRSD_FORMAT_INFORMATION                FormatInfo;
    PDRSD_FRAMEBUFFER_FUNCTIONS             Callbacks;
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

typedef struct _DRSD_PENDING_EVENT{
    PLOUQ_COMPLETION        Completion;
    void                  (*CompletionRelease)(PLOUQ_COMPLETION Completion);
    HANDLE                  DmaFence;
    ListHeader              Link;
    ListHeader              PendingList;
}DRSD_PENDING_EVENT, * PDRSD_PENDING_EVENT;

typedef struct _DRSD_EVENT{
    UINT32 Type;
    UINT32 Length;
}DRSD_EVENT, * PDRSD_EVENT;

typedef struct _DRSD_EVENT_BLANK{
    DRSD_EVENT      Base;
    UINT64          UserData;
    UINT32          TvSec;
    UINT32          TvUsec;
    UINT32          Sequence;
    UINT32          CrtcID;
}DRSD_EVENT_BLANK, * PDRSD_EVENT_BLANK;

typedef struct _DRSD_CRTC_SEQUENCE{
    DRSD_EVENT      Base;
    UINT64          UserData;
    INT64           TimeNs;
    UINT64          Sequence;
}DRSD_CRTC_SEQUENCE, * PDRSD_CRTC_SEQUENCE;

typedef struct _DRSD_PENDING_VBLANK_EVENT{
    DRSD_PENDING_EVENT      Base;
    UINT                    Pipe;
    UINT64                  Sequence;
    union{
        DRSD_EVENT          Base;
        DRSD_EVENT_BLANK    VBlank;
        DRSD_CRTC_SEQUENCE  Sequence;
    }Event;
}DRSD_PENDING_VBLANK_EVENT, * PDRSD_PENDING_VBLANK_EVENT;


typedef struct _DRSD_CRTC_COMMIT{
    struct _DRSD_CRTC*              Crtc;
    KERNEL_REFERENCE                Reference;
    LOUQ_COMPLETION                 FlipDone;
    LOUQ_COMPLETION                 HwDone;
    LOUQ_COMPLETION                 CleanupDone;
    ListHeader                      CommitEntry;
    PDRSD_PENDING_VBLANK_EVENT      Event;
    BOOLEAN                         AbortCompletion;
}DRSD_CRTC_COMMIT, * PDRSD_CRTC_COMMIT;

typedef enum _DRSD_COLOR_ENCODING {
	DRSD_COLOR_YCBCR_BT601,
	DRSD_COLOR_YCBCR_BT709,
	DRSD_COLOR_YCBCR_BT2020,
	DRSD_COLOR_ENCODING_MAX,
}DRSD_COLOR_ENCODING, * PDRSD_COLOR_ENCODING;

typedef enum _DRSD_COLOR_RANGE {
	DRSD_COLOR_YCBCR_LIMITED_RANGE,
	DRSD_COLOR_YCBCR_FULL_RANGE,
	DRSD_COLOR_RANGE_MAX,
}DRSD_COLOR_RANGE, * PDRSD_COLOR_RANGE;

typedef struct _DRSD_RECT{
    int X1;
    int Y1;
    int X2;
    int Y2;
}DRSD_RECT, * PDRSD_RECT, 
    DRSD_MODE_RECT, * PDRSD_MODE_RECT;

typedef struct _DRSD_PLANE_STATE{
    struct _DRSD_PLANE*         Plane;
    struct _DRSD_CRTC*          Crtc;
    struct _DRSD_FRAME_BUFFER*  FrameBuffer;
    HANDLE                      DmaFence;
    INT32                       CrtcX;
    INT32                       CrtcY;
    UINT32                      CrtcWidth;
    UINT32                      CrtcHeight;
    UINT32                      SourceX;
    UINT32                      SourceY;
    UINT32                      SourceWidth;
    UINT32                      SourceHeight;
    INT32                       HotSpotX;
    INT32                       HotSpotY;
    UINT16                      Alpha;
    UINT16                      PixelBlend;
    UINT                        Rotation;
    UINT                        ZPos;
    UINT                        NormalizedZPos;
    DRSD_COLOR_ENCODING         ColorEncoding;
    DRSD_COLOR_RANGE            ColorRange;
    struct _DRSD_PROPERTY_BLOB* FbDamageClips;
    BOOLEAN                     IgnoreDamageClips;
    DRSD_RECT                   Source;
    DRSD_RECT                   Destiantion;
    BOOLEAN                     Visable;
    DRSD_SCALING_FILTER         ScalingFilter;
    struct _DRSD_COLOR_OP*      ColorPipeline;
    struct _DRSD_CRTC_COMMIT*   Commit; 
    struct _DRSD_ATOMIC_STATE*  State;
    BOOLEAN                     ColorMgmtChanged : 1;

    //TODO: Get rid of old members
    atomic_t                        Fence;
    struct _DRSD_PROPERTY_BLOB*     Base;
    uint32_t                        Height;
    uint32_t                        Width;
    uint32_t*                       Formats;
    size_t                          FormatCount;
    UINT32                          FormatUsed;
}DRSD_PLANE_STATE, * PDRSD_PLANE_STATE;

typedef struct _SHADOW_PLANE_STATE{
    DRSD_PLANE_STATE Base;
}SHADOW_PLANE_STATE, * PSHADOW_PLANE_STATE;

typedef struct _DRSD_PLANE_ASSIST_FUNCTIONS{
    LOUSTATUS   (*PrepareFrameBuffer)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* NewState);
    void        (*CleanupFrameBuffer)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* OldState);
    LOUSTATUS   (*BeginFrameBufferAccess)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* NewState);
    void        (*EndFrameBufferAccess)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* OldState);
    LOUSTATUS   (*AtomicCheck)(struct _DRSD_PLANE* Plane, struct _DRSD_ATOMIC_STATE* State);
    void        (*AtomicUpdate)(struct _DRSD_PLANE* Plane, struct _DRSD_ATOMIC_STATE* State);
    void        (*AtomicEnable)(struct _DRSD_PLANE* Plane, struct _DRSD_ATOMIC_STATE* State);
    void        (*AtomicDisable)(struct _DRSD_PLANE* Plane, struct _DRSD_ATOMIC_STATE* State);
    LOUSTATUS   (*AtomicAsyncCheck)(struct _DRSD_PLANE* Plane, struct _DRSD_ATOMIC_STATE* State, bool Flip);
    void        (*AtomicAsyncUpdate)(struct _DRSD_PLANE* Plane, struct _DRSD_ATOMIC_STATE* State);
    LOUSTATUS   (*GetScanoutBuffer)(struct _DRSD_PLANE* Plane, void* ScanBuffer);
    void        (*PanicFlush)(struct _DRSD_PLANE* Plane);
}DRSD_PLANE_ASSIST_FUNCTIONS, * PDRSD_PLANE_ASSIST_FUNCTIONS;

typedef struct _DRSD_PLANE_CALLBACKS{
    LOUSTATUS                   (*UpdatePlane)(struct _DRSD_PLANE* Plane, struct _DRSD_CRTC* Crtc, struct _DRSD_FRAME_BUFFER* FrameBuffer, int CrtcX, int CrtcY, int CrtcWidth, int CrtcHeight, uint32_t SourceX, uint32_t SourceY, uint32_t SourceWidth, uint32_t SourceHeight, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
    LOUSTATUS                   (*DisablePlane)(struct _DRSD_PLANE* Plane, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
    void                        (*DestroyPlane)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* PlaneState);
    void                        (*ResetPlane)(struct _DRSD_PLANE* Plane);
    LOUSTATUS                   (*SetProperty)(struct _DRSD_PLANE* Plane, struct _DRSD_PROPERTY* Property, uint64_t Value);
    struct _DRSD_PLANE_STATE*   (*AtomicDuplicateState)(struct _DRSD_PLANE* Plane);
    void                        (*AtomicDestroyState)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* PlaneState);
    LOUSTATUS                   (*AtomicSetProperty)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* PlaneState, struct _DRSD_PROPERTY* Property, uint64_t Value);
    LOUSTATUS                   (*AtomicGetProperty)(struct _DRSD_PLANE* Plane, struct _DRSD_PLANE_STATE* PlaneState, struct _DRSD_PROPERTY* Property, uint64_t* Value);
    LOUSTATUS                   (*LateRegister)(struct _DRSD_PLANE* Planem);
    LOUSTATUS                   (*EarlyRegister)(struct _DRSD_PLANE* Planem);
    void                        (*PrintAtomicState)(struct _DRSD_PLANE_STATE* State);
    bool                        (*ModifierFormatSupported)(struct _DRSD_PLANE* Plane, uint32_t Format, uint64_t Modifier);
    bool                        (*AsyncModifierFormatSupported)(struct _DRSD_PLANE* Plane, uint32_t Format, uint64_t Modifier);
}DRSD_PLANE_CALLBACKS, * PDRSD_PLANE_CALLBACKS, 
    DRSD_PLANE_FUNCTIONS, * PDRSD_PLANE_FUNCTIONS;

typedef enum{
    OVERLAY_PLANE = 0,
    PRIMARY_PLANE = 1,
    CURSOR_PLANE  = 2,
}DRSD_PLANE_TYPE;



typedef struct _DRSD_PLANE{
    struct _DRSD_DEVICE*            Device;
    ListHeader                      Head;
    LOUSTR                          Name;
    DRSD_MODESET_LOCK               Mutex;
    DRSD_MODE_OBJECT                Base;
    UINT32                          PossibleCrtcs;
    UINT32*                         FormatTypes;
    UINT                            FormatCount;
    BOOLEAN                         FormatDefault;
    UINT64*                         Modifiers;
    UINT                            ModifierCount;
    struct _DRSD_CRTC*              Crtc;
    PDRSD_FRAME_BUFFER              Fb;
    PDRSD_FRAME_BUFFER              OldFb;
    PDRSD_PLANE_FUNCTIONS           Functions;
    DRSD_PROPERTY                   Properties;
    DRSD_PLANE_TYPE                 PlaneType;
    UINT                            Index;
    PDRSD_PLANE_ASSIST_FUNCTIONS    AssistFunctions;
    PDRSD_PLANE_STATE               State;
    PDRSD_PROPERTY                  AlphaProperty;
    PDRSD_PROPERTY                  ZPositionProperty;
    PDRSD_PROPERTY                  RotationProperty;
    PDRSD_PROPERTY                  BlendModeProperty;
    PDRSD_PROPERTY                  ColorEncodingProperty;
    PDRSD_PROPERTY                  ColorRangeProperty;
    PDRSD_PROPERTY                  ColorPipelineProperty;
    PDRSD_PROPERTY                  ScalingFilterProperty;
    PDRSD_PROPERTY                  HotSpotXProperty;
    PDRSD_PROPERTY                  HotSpotYProperty;


    //TODO Yatah Yatah Ya

    ListHeader                      Peers;
    DRSD_MODE_OBJECT                BaseMode;
    string                          PlaneName;
    mutex_t                         PlaneLock;
    uint32_t*                       Formats;
    bool                            ModifierDefault;
    PDRSD_FRAME_BUFFER              FrameBuffer;
    PDRSD_FRAME_BUFFER              OldBuffer;
    PDRSD_PLANE_CALLBACKS           Callbacks;
    PDRSD_PLANE_STATE               PlaneState;


    bool                            PlaneInUse;
    uint64_t                        DrsdPutPixelCase;
    size_t                          AlphaShift;
    size_t                          RedShift;
    size_t                          BlueShift;
    size_t                          GreenShift;
    bool                            IsDirty;
    INT64                           DirtyX;
    INT64                           DirtyY;
    INT64                           DirtyWidth;
    INT64                           DirtyHeight;
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
    uint32_t                            Bpc;
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

typedef struct _DRSD_TV_CONNECTOR_STATE{
    DRSD_MODE_SUB_CONNECTOR     SelectSubConnector;
    DRSD_MODE_SUB_CONNECTOR     SubConnector;
    DRSD_CONNECTOR_TV_MARGINS   Margins;
    UINT                        LegacyMode;
    UINT                        Mode;
    UINT                        Brightness;
    UINT                        Contrast;
    UINT                        FlickerReduction;
    UINT                        Overscan;
    UINT                        Saturation;
    UINT                        Hue;
}DRSD_TV_CONNECTOR_STATE, * PDRSD_TV_CONNECTOR_STATE;

typedef enum _DRSD_PRIVACY_SCREEN_STATUS{
    PRIVACY_SCREEN_DISABLED = 0,
    PRIVACY_SCREEN_ENABLED,
    PRIVACY_SCREEN_DISABLED_LOCKED,
    PRIVACY_SCREEN_ENABLED_LOCKED,
}DRSD_PRIVACY_SCREEN_STATUS, * PDRSD_PRIVACY_SCREEN_STATUS;

typedef struct _DRSD_WRITEBACK_JOB{
    struct _DRSD_WRITEBACK_CONNECTOR*   Connector;
    BOOLEAN                             Prepared;
    LOUQ_WORK                           CleanupWork;
    ListHeader                          ListEntry;
    struct _DRSD_FRAME_BUFFER*          FrameBuffer;
    HANDLE                              DmaOutFence;
    PVOID                               PrivateData;
}DRSD_WRITEBACK_JOB, * PDRSD_WRITEBACK_JOB;

typedef struct _DRSD_CONNECTOR_HDMI_STATE{
    PVOID Todo; 
}DRSD_CONNECTOR_HDMI_STATE, * PDRSD_CONNECTOR_HDMI_STATE;

typedef struct _DRSD_CONNECTOR_STATE{
    struct _DRSD_CONNECTOR*     Connector;
    struct _DRSD_CRTC*          Crtc;
    struct _DRSD_ENCODER*       BestEncoder;
    DRSD_LINK_STATUS            LinkStatus;
    struct _DRSD_ATOMIC_STATE*  State;
    struct _DRSD_CRTC_COMMIT*   Commit;
    DRSD_TV_CONNECTOR_STATE     Tv;
    BOOLEAN                     SelfRefreshAware;
    HDMI_PICTURE_ASPECT         PictureAspectRatio;
    UINT                        ContentType;
    UINT                        HdcpContentType;
    UINT                        ScalingMode;
    UINT                        ContentProtection;
    DRSD_COLOR_SPACE            ColorSpace;
    PDRSD_WRITEBACK_JOB         WritebackJob;
    UINT8                       MaxRequestedBpc;
    UINT8                       MaxBpc;
    DRSD_PRIVACY_SCREEN_STATUS  PrivacyScreenSwState;
    struct _DRSD_PROPERTY_BLOB* HdrOutputMetaData;
    DRSD_CONNECTOR_HDMI_STATE   Hdmi;  
}DRSD_CONNECTOR_STATE, * PDRSD_CONNECTOR_STATE;

typedef struct _DRSD_CONNECTOR_CALLBACKS{
    LOUSTATUS                   (*Dpms)(struct _DRSD_CONNECTOR* Connector, int Mode);
    void                        (*Reset)(struct _DRSD_CONNECTOR* Connector);
    DRSD_CONNECTOR_STATUS       (*Detect)(struct _DRSD_CONNECTOR* Connector, bool Force);
    void                        (*Force)(struct _DRSD_CONNECTOR* Connector);
    LOUSTATUS                   (*FillModes)(struct _DRSD_CONNECTOR* Connector, uint32_t MaxWidth, uint32_t MaxHeight);
    LOUSTATUS                   (*SetProperty)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_PROPERTY* Property, uint64_t Value);
    LOUSTATUS                   (*LateRegister)(struct _DRSD_CONNECTOR* Connector);
    void                        (*EarlyUnregister)(struct _DRSD_CONNECTOR* Connector);
    void                        (*Destroy)(struct _DRSD_CONNECTOR* Connector);
    PDRSD_CONNECTOR_STATE       (*AtomicDuplicateState)(struct _DRSD_CONNECTOR* Connector);
    void                        (*AtomicDestroyState)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_CONNECTOR_STATE* State);
    LOUSTATUS                   (*AtomicSetProperty)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_CONNECTOR_STATE* State, struct _DRSD_PROPERTY* Property, uint64_t Value);
    LOUSTATUS                   (*AtomicGetProperty)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_CONNECTOR_STATE* State, struct _DRSD_PROPERTY* Property, uint64_t* Value);
    void                        (*OobHotplugEvent)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_CONNECTOR_STATE* State);
}DRSD_CONNECTOR_CALLBACKS , * PDRSD_CONNECTOR_CALLBACKS, 
    DRSD_CONNECTOR_FUNCTIONS , * PDRSD_CONNECTOR_FUNCTIONS;

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

#define DRSD_DISPLAY_MODE_LENGTH    32

typedef enum _DRSD_PANEL_ORIENTATION{
	DRSD_MODE_PANEL_ORIENTATION_UNKNOWN = -1,
	DRSD_MODE_PANEL_ORIENTATION_NORMAL = 0,
	DRSD_MODE_PANEL_ORIENTATION_BOTTOM_UP,
	DRSD_MODE_PANEL_ORIENTATION_LEFT_UP,
	DRSD_MODE_PANEL_ORIENTATION_RIGHT_UP,
}DRSD_PANEL_ORIENTATION;

typedef enum _DRSD_CONNECTOR_TV_MODE{
	DRSD_MODE_TV_MODE_NTSC = 0,
	DRSD_MODE_TV_MODE_NTSC_443,
	DRSD_MODE_TV_MODE_NTSC_J,
	DRSD_MODE_TV_MODE_PAL,
	DRSD_MODE_TV_MODE_PAL_M,
	DRSD_MODE_TV_MODE_PAL_N,
	DRSD_MODE_TV_MODE_SECAM,
	DRSD_MODE_TV_MODE_MONOCHROME,
	DRSD_MODE_TV_MODE_MAX,
}DRSD_CONNECTOR_TV_MODE;

typedef struct _DRSD_CMDLINE_MODE{
    CHAR                        Name[DRSD_DISPLAY_MODE_LENGTH];
    BOOL                        Specified;
    BOOL                        RefreshSpecified;
    BOOL                        BppSpecified;
    UINT                        PixelClock;
    INTEGER                     Xres;
    INTEGER                     YRes;
    INTEGER                     Bpp;
    INTEGER                     Refresh;
    BOOL                        ReducedBlanking;
    BOOL                        Interlaced;
    BOOL                        Cvt;
    BOOL                        Margins;
    DRSD_CONNECTOR_FORCE        Force;
    UINT                        RotationReflection;
    DRSD_PANEL_ORIENTATION      PanelOrientation;
    DRSD_CONNECTOR_TV_MARGINS   TvMargins;
    DRSD_CONNECTOR_TV_MODE      TvMode;
    BOOL                        TvModeSpecified;
}DRSD_CMDLINE_MODE, * PDRSD_CMDLINE_MODE;

typedef enum _DRSD_CONNECTOR_REISTRATION_STATE{
    DRSD_CONNECTOR_INITIALIZING = 0,
    DRSD_CONNECTOR_REGISTERED,
    DRSD_CONNECTRO_UNREGISTERED,
}DRSD_CONNECTOR_REISTRATION_STATE, * PDRSD_CONNECTOR_REISTRATION_STATE;

#define DRSD_CONNECTOR_POLL_HPD         (1 << 0)
#define DRSD_CONNECTOR_POLL_CONNECT     (1 << 1)
#define DRSD_CONNECTOR_POLL_DISCONNECT  (1 << 2)

#define DRSD_MAX_ELD_BYTES 128

typedef struct _DRSD_TITLE_GROUP{
    KERNEL_REFERENCE        Reference;
    struct _DRSD_DEVICE*    Device;
    int                     Id;
    UINT8                   GroupData[8];
}DRSD_TITLE_GROUP, * PDRSD_TITLE_GROUP;

typedef struct _DRSD_CONNECTOR_INFOFRAME_FUNCTIONS{
    LOUSTATUS   (*ClearInfoFrame)(struct _DRSD_CONNECTOR* Connector);
    LOUSTATUS   (*WriteInfoFrame)(struct _DRSD_CONNECTOR* Connector, UINT8* Buffer, SIZE Length);
}DRSD_CONNECTOR_INFOFRAME_FUNCTIONS, * PDRSD_CONNECTOR_INFOFRAME_FUNCTIONS;

typedef struct _DRSD_CONNECTOR_HDMI_FUNCTIONS{
    DRSD_MODE_STATUS                        (*TmdsCHarRateValid)(struct _DRSD_CONNECTOR* Connector, struct _DRSD_DISPLAY_MODE* Mode, ULONGLONG TmdsRate);
    struct _DRSD_EDID_TRACKER*              (*ReadEdid)(struct _DRSD_CONNECTOR* Connector);
    DRSD_CONNECTOR_INFOFRAME_FUNCTIONS      Avi;
    DRSD_CONNECTOR_INFOFRAME_FUNCTIONS      Hdmi;
    DRSD_CONNECTOR_INFOFRAME_FUNCTIONS      Audio;
    DRSD_CONNECTOR_INFOFRAME_FUNCTIONS      HdrDrsd;
    DRSD_CONNECTOR_INFOFRAME_FUNCTIONS      Spd;
}DRSD_CONNECTOR_HDMI_FUNCTIONS, * PDRSD_CONNECTOR_HDMI_FUNCTIONS;

typedef struct _DRSD_CONNECTOR_HDMI_INFOFRAME{
    HDMI_INFOFRAME  Data;
    BOOLEAN         Set;
}DRSD_CONNECTOR_HDMI_INFOFRAME, * PDRSD_CONNECTOR_HDMI_INFOFRAME;

#define DRSD_CONNECTOR_HDMI_VENDOR_LENGTH  8
#define DRSD_CONNECTOR_HDMI_PRODUCT_LENGTH 16

typedef struct _DRSD_CONNECTOR_HDMI{
    UCHAR                               Vendor[DRSD_CONNECTOR_HDMI_VENDOR_LENGTH];
    UCHAR                               Product[DRSD_CONNECTOR_HDMI_PRODUCT_LENGTH];
    UINT64                              SupportedFormats;
    PDRSD_CONNECTOR_HDMI_FUNCTIONS      Functions;
    struct{
        mutex_t                         Lock;
        DRSD_CONNECTOR_HDMI_INFOFRAME   Audio;
    }InfoFrames;    
}DRSD_CONNECTOR_HDMI, * PDRSD_CONNECTOR_HDMI;

typedef struct _DRSD_CONNECTOR_HDMI_AUDIO_FUNCTIONS{
    LOUSTATUS   (*StartUp)(struct _DRSD_CONNECTOR* Connector);
    LOUSTATUS   (*Prepare)(struct _DRSD_CONNECTOR* Connector, struct _HDMI_CODEC_DAIFMT* Format, struct _HDMI_CODEC_PARAMETERS* Parameters);
    void        (*ShutDown)(struct _DRSD_CONNECTOR* Connector);
    LOUSTATUS   (*MuteStream)(struct _DRSD_CONNECTOR* Connector, BOOLEAN Enable, int Direction);
}DRSD_CONNECTOR_HDMI_AUDIO_FUNCTIONS, * PDRSD_CONNECTOR_HDMI_AUDIO_FUNCTIONS;

typedef struct _DRSD_CONNECTOR_HDMI_AUDIO{
    PDRSD_CONNECTOR_HDMI_AUDIO_FUNCTIONS    Functions;
    PLATFORM_DEVICE                         CodecPDev;
    mutex_t                                 Lock;
    void                                    (*PluggedCb)(PLATFORM_DEVICE Device, BOOLEAN Plugged);
    PLATFORM_DEVICE                         PluggedCbDevice;
    BOOLEAN                                 LastState;
    int                                     DaiPort;
}DRSD_CONNECTOR_HDMI_AUDIO, * PDRSD_CONNECTOR_HDMI_AUDIO;

typedef struct _DRSD_CONNECTOR_CEC_FUNCTIONS{
    void    (*PhysAddressInvalidate)(struct _DRSD_CONNECTOR* Connector);
    void    (*PhysAddressSet)(struct _DRSD_CONNECTOR* Connector, UINT16 Address);
}DRSD_CONNECTOR_CEC_FUNCTIONS, PDRSD_CONNECTOR_CEC_FUNCTIONS;

typedef struct _DRSD_CONNECTOR_CEC{
    mutex_t                         Mutex;
    PDRSD_CONNECTOR_CEC_FUNCTIONS   Functions;
    PVOID                           Data;
}DRSD_CONNECTOR_CEC, * PDRSD_CONNECTOR_CEC;

typedef struct _DRSD_CONNECTOR{
    struct _DRSD_DEVICE*                Device;
    PLATFORM_DEVICE                     KernelDevice;
    HANDLE                              DeviceAttributes;
    HANDLE                              FwNodeHandle;
    ListHeader                          Head;
    ListHeader                          GlobalConectorList;
    DRSD_MODE_OBJECT                    Base;
    string                              Name;
    mutex_t                             ConnectorLock;
    size_t                              Index;
    int                                 ConnectorType;
    int                                 ConnectorTypeId;
    BOOLEAN                             InterlacedAllowed;
    BOOLEAN                             DoublescanAllowed;
    BOOLEAN                             StereoAllowed;
    BOOLEAN                             Ycbcr420Allowed;
    DRSD_CONNECTOR_REISTRATION_STATE    RegistrationState;
    ListHeader                          Modes;
    DRSD_CONNECTOR_STATUS               Status;
    ListHeader                          ProbedModes;
    DRSD_DISPLAY_INFORMATION            DisplayInfo;
    PDRSD_CONNECTOR_FUNCTIONS           Functions;
    struct _DRSD_PROPERTY_BLOB*         EdidBlobPointer;
    DRSD_OBJECT_PROPERTIES              Properties;
    struct _DRSD_PROPERTY*              ScalingModeProperty;
    struct _DRSD_PROPERTY*              VrrCapableProperty;
    struct _DRSD_PROPERTY*              ColorSpaceProperty;
    struct _DRSD_PROPERTY_BLOB*         PathBlobPointer;
    UINT                                MaxBpc;
    struct _DRSD_PROPERTY*              MaxBpcProperty;
    struct _DRSD_PRIVACY_SCREEN*        PrivacyScreen;
    LOUSINE_KERNEL_NOTIFICATION_BLOCK   PrivacyScreenNotifier;
    struct _DRSD_PROPERTY*              PrivacyScreenSwStateProperty;
    struct _DRSD_PROPERTY*              PrivacyScreenHwStateProperty;
    struct _DRSD_PROPERTY*              BroadcastRgbProperty;
    UINT8                               Polled;    
    int                                 Dpms;
    struct _DRSD_EDID_TRACKER*          EdidOverride;
    mutex_t                             EdidOverrideMutex;
    UINT64                              EpochCounter;
    UINT32                              PossibleEncoders;
    struct _DRSD_ENCODER*               Encoder;
    UINT8                               Eld[DRSD_MAX_ELD_BYTES];
    BOOLEAN                             LatencyPresent[2];
    int                                 VideoLatency[2];
    int                                 AudioLatency[2];
    PLATFORM_DEVICE                     Ddc;
    int                                 NullEdidCounter;
    UINT                                BadEdidCounter;
    BOOLEAN                             EdidCurrupt;
    UINT8                               RealEdidChecksum;
    HANDLE                              ClfsServer;
    struct _DRSD_CONNECTOR_STATE*       State;
    struct _DRSD_PROPERTY_BLOB*         TitleBlobPointer;
    BOOLEAN                             HasTitle;
    PDRSD_TITLE_GROUP                   TitleGroup;
    BOOLEAN                             TitleIsSingleMonitor;
    UINT8                               HTileCount;
    UINT8                               VTileCount;
    UINT8                               HTileLocation;
    UINT8                               VTileLocation;
    UINT16                              HTileSize;
    UINT16                              VTileSize;
    ListHeader                          FreeNode;
    DRSD_CONNECTOR_HDMI                 Hdmi;
    DRSD_CONNECTOR_HDMI                 HdmiAudio;
    DRSD_CONNECTOR_CEC                  Cec;
    //TODO: make new structure and then move to the new structure



    //TODO Finish cleaning the old stuff below

    ListHeader                          Peers;
    void*                               PrivateData;
    void*                               DownwireDevices;//some setups have smart systems down the wire

    int32_t                             CType;
    int32_t                             CTypeID;
    bool                                InterlaceAble;
    bool                                DoubleScanAble;
    bool                                StereoAble;
    bool                                Ycbcr420Able;
    ListHeader                          SupportedModes;
    DRSD_CONNECTOR_STATUS               ConnectorStatus;
    DRSD_CMDLINE_MODE                   CommandLineMode;
    DRSD_DISPLAY_INFORMATION            DisplayInformation;
    PDRSD_CONNECTOR_CALLBACKS           Callbacks;
    PDRSD_PROPERTY_BLOB                 EdidPropertiesBlob;
    DRSD_OBJECT_PROPERTIES              ConnectorProperties;
    int                                 PowerMode;
    PDRSD_CONNECTOR_ASSIST_CALLBACKS    AssistFunctions;
    DRSD_CONNECTOR_FORCE                Force;
    HDMI_SYNCRONIZATION_INFORMATION     HdmiSyncInformation;
    mutex_t                             EldTex;
    size_t                              ProbeModeCount;
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
#define DRSD_CONNECTOR_MODE_DVID            3
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
    DRSD_MODE_OBJECT                            Base;
    LOUSTR                                      Name;
    ListHeader                                  BridgeChain;

    string                                      EncoderName;
    int32_t                                     EncoderType;
    size_t                                      Index;
    uint32_t                                    CrtcLimit;
    uint32_t                                    CloneLimit;
    struct _DRSD_ENCODER_CALLBACKS*             Callbacks;
    struct _DRSD_ENCODER_ASSISTED_CALLBACKS*    AssistedCallbacks;
}DRSD_ENCODER, * PDRSD_ENCODER; 

typedef struct _DRSD_WRITEBACK_CONNECTOR{
    DRSD_CONNECTOR                  Base;
    DRSD_ENCODER                    Encoder;
    struct _DRSD_PROPERTY_BLOB*     PixelFormatsBlopPointer;
    spinlock_t                      JobLock;
    ListHeader                      JobQueue;
    UINT                            FenceContext;
    spinlock_t                      FenceLock;
    UINT64                          FenceSequenceNumber;
    CHAR                            TimeLineName[32];
}DRSD_WRITEBACK_CONNECTOR, * PDRSD_WRITEBACK_CONNECTOR;

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
    struct _DRSD_CRTC*              Crtc;
    BOOLEAN                         Enable              :   1;
    BOOLEAN                         Active              :   1;
    BOOLEAN                         PlanesChanged       :   1;
    BOOLEAN                         ModeChanged         :   1;
    BOOLEAN                         ActiveChanged       :   1;
    BOOLEAN                         ConnectorsChanged   :   1;
    BOOLEAN                         ZPosChanged         :   1;
    BOOLEAN                         ColorMgmtChanged    :   1;
    BOOLEAN                         NoVBlank;
    UINT32                          PlaneMask;
    UINT32                          ConnectorMask;
    UINT32                          EncoderMask;
    DRSD_DISPLAY_MODE               AdjustedMode;
    DRSD_DISPLAY_MODE               Mode;
    struct _DRSD_PROPERTY_BLOB*     ModeBlob;
    struct _DRSD_PROPERTY_BLOB*     DegammaLut;
    struct _DRSD_PROPERTY_BLOB*     Ctm;
    struct _DRSD_PROPERTY_BLOB*     GammaLut;
    UINT32                          TargetVBlank;
    BOOLEAN                         AsyncFlip;
    BOOLEAN                         VrrEnabled;
    BOOLEAN                         SelfRefreshActive;
    DRSD_SCALING_FILTER             ScalingFilter;
    UINT8                           SharpnesStrength;
    PDRSD_PENDING_VBLANK_EVENT      Event;
    struct _DRSD_CRTC_COMMIT*       Commit;
    struct _DRSD_ATOMIC_STATE*      State;
    //TODO remove the following
    BOOLEAN                         NeedsModeset;
    DRSD_DISPLAY_MODE               DisplayMode;
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
    void                        (*Reset)(struct _DRSD_CRTC* Crtc);
    LOUSTATUS                   (*SetCursor)(struct _DRSD_CRTC* Crtc, struct _DRSD_FILE* DrsdFile, uint32_t Handle, uint32_t Width, uint32_t Height);
    LOUSTATUS                   (*SetCursorEx)(struct _DRSD_CRTC* Crtc, struct _DRSD_FILE* DrsdFile, uint32_t Handle, uint32_t Width, uint32_t Height, int32_t HotX, int32_t HotY);
    LOUSTATUS                   (*MoveCursor)(struct _DRSD_CRTC* Crtc, int X, int Y);
    LOUSTATUS                   (*SetGamma)(struct _DRSD_CRTC* Crtc, uint16_t* R, uint16_t* G, uint16_t* B, struct _DRSD_MODE_SET_CONTEXT* Context);
    void                        (*Destroy)(struct _DRSD_CRTC* Crtc);
    LOUSTATUS                   (*SetConfiguration)(void* ModeSet, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
    LOUSTATUS                   (*PageFlip)(struct _DRSD_CRTC* Crtc, DRSD_FRAME_BUFFER* FrameBuffer, struct _DRSD_PENDING_VBLANK_EVENT* VBlankEvent, uint32_t Flags, struct _DRSD_MODE_SET_CONTEXT* ModeSetAquireContext);
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
}DRSD_CRTC_CALLBACK, * PDRSD_CRTC_CALLBACK, DRSD_CRTC_FUNCTIONS, * PDRSD_CRTC_FUNCTIONS;

#define DRSD_MAX_CRC_NR 10

typedef struct _DRSD_CRTC_CRC_ENTRY{
    BOOLEAN     HasFrameCounter;
    UINT32      Frame;
    UINT32      Crcs[DRSD_MAX_CRC_NR];
}DRSD_CRTC_CRC_ENTRY, * PDRSD_CRTC_CRC_ENTRY;

typedef struct _DRSD_CRTC_CRC{
    spinlock_t              Lock;
    LOUSTR                  Source;
    BOOLEAN                 Opened;
    BOOLEAN                 Overflow;
    PDRSD_CRTC_CRC_ENTRY    Entries;
    int                     Head;
    int                     Tail;
    SIZE                    ValuesCount;
    PLOUQ_WAIT_QUEUE        Wq;
}DRSD_CRTC_CRC, * PDRSD_CRTC_CRC;

typedef struct _DRSD_SELF_REFRESH_DATA{
    struct _DRSD_CRTC*      Crtc;
    PLOUQ_DELAYED_WORK      EntryWork;
    mutex_t                 AvgMutex;
    SIZE                    EntryAvgMs;   
    SIZE                    ExitAvgMs;   
}DRSD_SELF_REFRESH_DATA, * PDRSD_SELF_REFRESH_DATA;

typedef struct _DRSD_CRTC{
    struct _DRSD_DEVICE*            Device;
    PLATFORM_DEVICE                 Port;
    ListHeader                      Head;
    LOUSTR                          Name;
    DRSD_MODESET_LOCK               Mutex;
    DRSD_MODE_OBJECT                Base;
    PDRSD_PLANE                     Primary;
    PDRSD_PLANE                     Cursor;
    UINT                            Index;
    int                             CursorX;
    int                             CursorY;
    BOOLEAN                         Enabled;
    DRSD_DISPLAY_MODE               Mode;
    DRSD_DISPLAY_MODE               HwMode;
    int                             X;
    int                             Y;
    PDRSD_CRTC_FUNCTIONS            Functions;
    UINT32                          GammaSize;
    UINT16*                         GammaStore;
    DRSD_OBJECT_PROPERTIES          Properties;
    PDRSD_PROPERTY                  ScalingFilterProperty;
    PDRSD_PROPERTY                  SharpnesStrengthProperty;
    PDRSD_CRTC_STATE                State;
    ListHeader                      CommitList;
    spinlock_t                      CommitLock;
    HANDLE                          ClfsServer;
    DRSD_CRTC_CRC                   Crc;
    UINT                            FenceContext;
    spinlock_t                      FenceSeqNo;
    CHAR                            TimelineName[32];
    PDRSD_SELF_REFRESH_DATA         SlefRefreshData;    

    //TODO: Clean Up Old And Set Up New

    ListHeader                      Peers;
    PDRSD_FRAME_BUFFER              Framebuffer;
    DRSD_DISPLAY_MODE               DisplayMode;
    PDRSD_PLANE                     PrimaryPlane;
    PDRSD_PLANE                     CursorPlane;
    PDRSD_CRTC_CALLBACK             CrtcCallbacks;
    PDRSD_CRTC_ASSIST_CALLBACK      AssistFunctions;
    PDRSD_CRTC_STATE                CrtcState;    
}DRSD_CRTC, * PDRSD_CRTC;

typedef struct _DRSD_MODE_FB_COMMAND2{
    UINT32  FbId;
    UINT32  Width;
    UINT32  Height;
    UINT32  PixelFormat;
    UINT32  Flags;
    UINT32  Handles[4];
    UINT32  Pitches[4];
    UINT32  Offsets[4];
    UINT64  Modifiers[4];
}DRSD_MODE_FB_COMMAND2, * PDRSD_MODE_FB_COMMAND2;

typedef struct _DRSD_MODE_CONFIGURATION_CALLBACKS{
    PDRSD_FRAME_BUFFER              (*FbCreate)(struct _DRSD_DEVICE* Device, struct _DRSD_FILE* FilePrivate, PDRSD_FORMAT_INFORMATION Info, DRSD_MODE_FB_COMMAND2* ModeCommand);
    PDRSD_FORMAT_INFORMATION        (*GetFormatInfo)(UINT32 PixelFormat, UINT64 Modifier);
    DRSD_MODE_STATUS                (*ModeValid)(struct _DRSD_DEVICE* Device, PDRSD_DISPLAY_MODE DisplayMode);
    LOUSTATUS                       (*AtomicCheck)(struct _DRSD_DEVICE* Device, struct _DRSD_ATOMIC_STATE* State);
    LOUSTATUS                       (*AtomicCommit)(struct _DRSD_DEVICE* Device, struct _DRSD_ATOMIC_STATE* State, BOOLEAN  NonBlock);
    struct _DRSD_ATOMIC_STATE*      (*AtomicStateAllocate)(struct _DRSD_DEVICE* Device);
    void                            (*AtomicStateClear)(struct _DRSD_ATOMIC_STATE*);
    void*                           (*AtomicStateFree)(struct _DRSD_ATOMIC_STATE* State);
}DRSD_MODE_CONFIGURATION_CALLBACKS, * PDRSD_MODE_CONFIGURATION_CALLBACKS,
    DRSD_MODE_CONFIGURATION_FUNCTIONS, * PDRSD_MODE_CONFIGURATION_FUNCTIONS;

typedef struct _DRSD_VBLANK_CRTC{
    ListHeader  Peers;
    atomic_t    Count;
    size_t      InModeset;
}DRSD_VBLANK_CRTC, * PDRSD_VBLANK_CRTC;

typedef struct _DRSD_MODE_CONFIGURATION_HELPER_FUNCTIONS{
    PVOID TODO;
}DRSD_MODE_CONFIGURATION_HELPER_FUNCTIONS, * PDRSD_MODE_CONFIGURATION_HELPER_FUNCTIONS;

typedef struct _DRSD_MODE_CONFIGURATION{
    mutex_t                                     Mutex;
    DRSD_MODESET_LOCK                           ConnectionMutex;
    struct _DRSD_MODESET_ACQURE_CONTEXT*        AcquireContext;
    mutex_t                                     IdrMutex;
    XARRAY                                      ObjectIdr;
    XARRAY                                      TitleIdr;
    mutex_t                                     FbLock;
    SIZE                                        FbCount;
    ListHeader                                  FbList;
    spinlock_t                                  ConnectorListLock;
    SIZE                                        ConnectorCount;
    XARRAY                                      ConnectorIda;
    ListHeader                                  ConnectorList;
    ListHeader                                  ConnectorFreeList;
    LOUQ_WORK                                   ConnectorFreeWork;
    SIZE                                        EncoderCount;
    ListHeader                                  EncoderList;
    SIZE                                        TotalPlaneCount;
    ListHeader                                  PlaneList;
    spinlock_t                                  PanicLock;
    SIZE                                        ColorOpCount;
    ListHeader                                  ColorOpList;
    SIZE                                        CrtcCount;
    ListHeader                                  CrtcList;
    ListHeader                                  PropertyList;
    ListHeader                                  PrivateObjectsList;
    UINT                                        MinWidth;
    UINT                                        MinHeight;
    UINT                                        MaxWidth;
    UINT                                        MaxHeight;
    PDRSD_MODE_CONFIGURATION_FUNCTIONS          Functions;
    BOOLEAN                                     PollEnabeld;
    BOOLEAN                                     PollRunning;
    BOOLEAN                                     DelayedEvent;
    LOUQ_DELAYED_WORK                           OutputPollWork;
    mutex_t                                     BlobLock;
    ListHeader                                  PropertyBlobList;
    struct _DRSD_PROPERTY*                      EdidProperty;
    struct _DRSD_PROPERTY*                      DpmsProperty;
    struct _DRSD_PROPERTY*                      PathProperty;
    struct _DRSD_PROPERTY*                      TitleProperty;
    struct _DRSD_PROPERTY*                      LinkStatusProperty;
    struct _DRSD_PROPERTY*                      PlaneTypeProperty;
    struct _DRSD_PROPERTY*                      PropSrcX;
    struct _DRSD_PROPERTY*                      PropSrcY;
    struct _DRSD_PROPERTY*                      PropSrcW;
    struct _DRSD_PROPERTY*                      PropSrcH;
    struct _DRSD_PROPERTY*                      PropCrtcX;
    struct _DRSD_PROPERTY*                      PropCrtcY;
    struct _DRSD_PROPERTY*                      PropCrtcW;
    struct _DRSD_PROPERTY*                      PropCrtcH;
    struct _DRSD_PROPERTY*                      PropFbId;
    struct _DRSD_PROPERTY*                      PropInFenceFb;
    struct _DRSD_PROPERTY*                      PropOutFencePtr;
    struct _DRSD_PROPERTY*                      PropCrtcId;
    struct _DRSD_PROPERTY*                      PropFbDamageClips;
    struct _DRSD_PROPERTY*                      PropActive;
    struct _DRSD_PROPERTY*                      PropModeId;
    struct _DRSD_PROPERTY*                      PropVrrEnabled;
    struct _DRSD_PROPERTY*                      DviISubConnectorProperty;
    struct _DRSD_PROPERTY*                      DviISelsectSubConnectorProperty;
    struct _DRSD_PROPERTY*                      DpSubConnectorProperty;
    struct _DRSD_PROPERTY*                      TvSubConnectorProperty;
    struct _DRSD_PROPERTY*                      LegacyTvModeProperty;
    struct _DRSD_PROPERTY*                      TvModeProperty;
    struct _DRSD_PROPERTY*                      TvLeftMarginProperty;
    struct _DRSD_PROPERTY*                      TvRightMarginProperty;
    struct _DRSD_PROPERTY*                      TvTopMarginProperty;
    struct _DRSD_PROPERTY*                      TvBottomMarginProperty;
    struct _DRSD_PROPERTY*                      TvBrightnessProperty;
    struct _DRSD_PROPERTY*                      TvContrastMarginProperty;
    struct _DRSD_PROPERTY*                      TvFlickerReductionProperty;
    struct _DRSD_PROPERTY*                      TvOverScanProperty;
    struct _DRSD_PROPERTY*                      TvSaturationProperty;
    struct _DRSD_PROPERTY*                      TvHueProperty;
    struct _DRSD_PROPERTY*                      ScalingModeProperty;
    struct _DRSD_PROPERTY*                      AspectRatioProperty;
    struct _DRSD_PROPERTY*                      ContentTypeProperty;
    struct _DRSD_PROPERTY*                      DeGammaLutProperty;
    struct _DRSD_PROPERTY*                      DeGammaLutSizeProperty;
    struct _DRSD_PROPERTY*                      CtmProperty;
    struct _DRSD_PROPERTY*                      GammaLutProperty;
    struct _DRSD_PROPERTY*                      GammaLutSizeProperty;
    struct _DRSD_PROPERTY*                      SuggestedXProperty;
    struct _DRSD_PROPERTY*                      SuggestedYProperty;
    struct _DRSD_PROPERTY*                      NonDesktopProperty;
    struct _DRSD_PROPERTY*                      PanelOrientationProperty;
    struct _DRSD_PROPERTY*                      WritebackFbIdProperty;
    struct _DRSD_PROPERTY*                      WriteBackPixelFormatsProperty;
    struct _DRSD_PROPERTY*                      WriteBackOutFencePtrProperty;
    struct _DRSD_PROPERTY*                      HdrOutputMetadataProperty;
    struct _DRSD_PROPERTY*                      ContentProtectionProperty;
    struct _DRSD_PROPERTY*                      HdcpContentTypeProperty;
    UINT32                                      PreferredDepth;
    UINT32                                      PreferredShadow;
    BOOLEAN                                     QuirkAddFbPreferXbgr30Bpp;
    BOOLEAN                                     QuirkAddFbPreferHostOrder;
    BOOLEAN                                     AsyncPageFlip;
    BOOLEAN                                     FbModifiersNotSupported;
    BOOLEAN                                     NormalizeZPos;
    struct _DRSD_PROPERTY*                      ASyncModifiersProperty;
    struct _DRSD_PROPERTY*                      ModifiersProperty;
    struct _DRSD_PROPERTY*                      SizeHintsProperty;
    UINT32                                      CursorWidth;
    UINT32                                      CursorHeight;
    struct _DRSD_ATOMIC_STATE*                  SuspendState;
    PDRSD_MODE_CONFIGURATION_HELPER_FUNCTIONS   HelperPrivate;

    //old functions    
    mutex_t                                 IdLock;
    PDRSD_MODE_CONFIGURATION_CALLBACKS      Callbacks;
    LIST_OBJECT                             FreeList;         
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



typedef struct _DRSD_MINOR{
    int                     Index;
    int                     Type;
    PLATFORM_DEVICE         KernelDevice;
    struct _DRSD_DEVICE*    Device;
    HANDLE                  ClfsServer;
    HANDLE                  ClfsPath;
}DRSD_MINOR, * PDRSD_MINOR;


struct _DRSD_MASTER;

typedef struct _DRSD_MASTER{
    KERNEL_REFERENCE        KRef;
    struct _DRSD_DEVICE*    Device;
    LOUSTR                  Uid;
    int                     UidLength;
    XARRAY                  MagicMap;
    PVOID                   DriverPrivate;
    struct _DRSD_MASTER*    Lessor;
    int32_t                 LesseeId;
    ListHeader              Lessees;
    XARRAY                  Leases;
    XARRAY                  LeasesIdr;
}DRSD_MASTER, * PDRSD_MASTER;

struct _DRSD_MM;

#define DRSD_MM_NODE_ALLOCATED_BIT	0
#define DRSD_MM_NODE_SCANNED_BIT    1

typedef struct _DRSD_MM_NODE{
    UINT64              Color;
    UINT64              Start;
    UINT64              Size;
    struct _DRSD_MM*    Mm;
    ListHeader          NodeList;
    ListHeader          HoleStack;
    HANDLE              Rb;
    HANDLE              HolesSize;
    HANDLE              HolesAddr;
    UINT64              SubtreeLast;
    UINT64              HoleSize;
    UINT64              SubtreeMaxHole;
    UINT64              Flags;
    HANDLE              Stack;
}DRSD_MM_NODE, * PDRSD_MM_NODE;

typedef struct _DRSD_MM{
    void            (*ColorAdjust)(PDRSD_MM_NODE Node, UINT64 Color, UINT64* Start, UINT64* End);
    ListHeader      HoleStack;
    DRSD_MM_NODE    HeadNode;
    HANDLE          IntervalTree;
    HANDLE          HolesSize;
    HANDLE          HolesAddress;
    UINT64          ScanActive; 
}DRSD_MM, * PDRSD_MM;

typedef struct _DRSD_VMA_OFFSET_MANAGER{
    spinlock_t      Lock;
    PDRSD_MM        VmAddressSpaceMm;
}DRSD_VMA_OFFSET_MANAGER, * PDRSD_VMA_OFFSET_MANAGER;

struct _DRSD_TTM_DEVICE;

#define TTM_TT_FLAGS_SWAPPED                (1 << 0)
#define TTM_TT_FLAGS_ZERO_ALLOC             (1 << 1)
#define TTM_TT_FLAGS_EXTERNAL               (1 << 2)
#define TTM_TT_FLAGS_EXTERNAL_MAPPABLE      (1 << 3)
#define TTM_TT_FLAGS_DECRYPTED              (1 << 4)
#define TTM_TT_FLAGS_BACKED_UP              (1 << 5)
#define TTM_TT_FLAGS_PRIVATE_POPULATED      (1 << 6)

#define TTM_ALLOCATION_POOL_BENIFICIAL_ORDER(n) (n & 0xFF)
#define TTM_ALLOCATION_POOL_USE_DMA_ALLOC       (1 << 8) 
#define TTM_ALLOCATION_POOL_USE_DMA32           (1 << 9)
#define TTM_ALLOCATION_PROPAGATE_ENOSPC         (1 << 10)

#define TTM_NUM_CACHING_TYPES 3

typedef enum _TTM_CACHING{
    TtmUncached = 0,
    TtmWriteCombined,
    TtmCached,
}TTM_CACHING, * PTTM_CACHING;

#define TTM_CACHING_TYPES_COUNT 3

#define TTM_PL_SYSTEM   0
#define TTM_PL_TT       1
#define TTM_PL_VRAM     2
#define TTM_PL_PRIV     3

struct _TTM_POOL;

typedef struct _TTM_POOL_TYPE{
    struct _TTM_POOL*   Pool;
    UINT                Order;
    TTM_CACHING         Caching;
    ListHeader          ShrinkerList;
    spinlock_t          Lock;
    ListHeader          Pages;           
}TTM_POOL_TYPE, * PTTM_POOL_TYPE;

typedef struct _TTM_POOL{
    PLATFORM_DEVICE     Device;
    int                 Nid;
    UINT                AllocationFlags;
    struct {
        TTM_POOL_TYPE   Orders[NR_PAGE_ORDERS];
    }                   Caching[TTM_NUM_CACHING_TYPES];
}TTM_POOL, * PTTM_POOL;

typedef struct _TTM_POOL_ALLOCATION_STATE{
    HANDLE                  TtmPageData;
    HANDLE                  TtmCacheDivide;
    UINT64                  DmaAddress;
    SIZE                    RemainingPages;
    TTM_CACHING             TtmCaching;
}TTM_POOL_ALLOCATION_STATE, * PTTM_POOL_ALLOCATION_STATE;

typedef struct _TTM_POOL_TT_RESTORE{
    PTTM_POOL                       Pool;
    TTM_POOL_ALLOCATION_STATE       SnapshotAllocation;
    HANDLE                          AllocedPages;
    UINT64                          FirstDma;
    SIZE                            AllocatedPages;
    SIZE                            RestoredPages;
    TTM_CACHING                     PageCaching;
    UINT                            Order;
}TTM_POOL_TT_RESTORE, * PTTM_POOL_TT_RESTORE;

typedef struct _TTM_TT{
    HANDLE                  TtmPageData;
    UINT32                  TtmPageFlags;
    UINT32                  PageCount;
    HANDLE                  ScatterGather;
    UINT64                  DmaAddress;
    FILE*                   SwapStorage;
    FILE*                   Backup;
    PTTM_POOL_TT_RESTORE    Restore;
}TTM_TT, * PTTM_TT;

typedef enum _TTM_BUFFER_OBJECT_TYPE{
    TtmBoTypeDevice = 0,
    TtmBoTypeKernel,
    TtmBoTypeScatterGather,
}TTM_BUFFER_OBJECT_TYPE, * PTTM_BUFFER_OBJECT_TYPE;

struct _TTM_BUFFER_OBJECT;

typedef enum _TTM_LRU_TYPE{
    TTM_LRU_RESOURCE = 0,
    TTM_LRU_HITCH,
}TTM_LRU_TYPE, * PTTM_LRU_TYPE;

typedef struct _TTM_LRU_ITEM{   
    ListHeader      Link;
    TTM_LRU_TYPE    Type;
}TTM_LRU_ITEM, * PTTM_LRU_ITEM;

typedef struct _TTM_BUS_PLACEMENT{
    PVOID       Address;
    UINT64      PhyAddress;
    BOOLEAN     IsIoMem;
    TTM_CACHING Cahcing;
}TTM_BUS_PLACEMENT, * PTTM_BUS_PLACEMENT;

typedef struct _TTM_RESOURCE{
    UINT64                      State;
    SIZE                        Size;
    UINT32                      MemType;
    UINT32                      Placement;
    TTM_BUS_PLACEMENT           Bus;
    struct _TTM_BUFFER_OBJECT*  BufferObject;
    HANDLE                      CssPoolState;
    TTM_LRU_ITEM                LruItem;
}TTM_RESOURCE, * PTTM_RESOURCE;

#define TTM_MEM_TYPES_COUNT                 9
#define TTM_MAX_BUFFER_OBJECT_PRIORITIES    4

typedef struct _TTM_LRU_BULK_MOVE_POSITION{
    struct _TTM_RESOURCE*   First;  //if you aint first,
    struct _TTM_RESOURCE*   Last;   //your last
}TTM_LRU_BULK_MOVE_POSITION, * PTTM_LRU_BULK_MOVE_POSITION;

typedef struct _TTM_LRU_BULK_MOVE{
    TTM_LRU_BULK_MOVE_POSITION  Position[TTM_MEM_TYPES_COUNT][TTM_MAX_BUFFER_OBJECT_PRIORITIES];
    ListHeader                  CursorList;
}TTM_LRU_BULK_MOVE, * PTTM_LRU_BULK_MOVE;

typedef struct _TTM_BUFFER_OBJECT{
    DRSD_GXE_OBJECT             Base;    
    struct _DRSD_TTM_DEVICE*    TtmDevice;
    TTM_BUFFER_OBJECT_TYPE      Type;
    UINT32                      PageAlignment;
    void                        (*Destroy)(struct _TTM_BUFFER_OBJECT* TtmObject);
    KERNEL_REFERENCE            KRef;
    PTTM_RESOURCE               Resource;
    struct _TTM_TT*             Ttm;
    BOOLEAN                     Deleted;
    PTTM_LRU_BULK_MOVE          BulkMove;
    UINT                        Priority;
    UINT                        PinCount;
    LOUQ_WORK                   DelayedDelete;
    HANDLE                      ScatterGatherTable;
}TTM_BUFFER_OBJECT, * PTTM_BUFFER_OBJECT;

typedef struct _TTM_OPERATION_CONTEXT{
    BOOLEAN     Interruptable;
    BOOLEAN     NoWaitGpu;
    BOOLEAN     GfpRetryMayFail;
    BOOLEAN     AllowResEvict;
    HANDLE      Reserve;
    UINT64      BytesMoved;    
}TTM_OPERATION_CONTEXT, * PTTM_OPERATION_CONTEXT;

typedef struct _TTM_PLACE{
    UINT        Fpfn;
    UINT        Lpfn;
    UINT32      Flags;
}TTM_PLACE, * PTTM_PLACE;

typedef struct _TTM_PLACEMENT{
    UINT        NumPlacement;
    PTTM_PLACE  Placement;
}TTM_PLACEMENT, * PTTM_PLACEMENT;

typedef struct _TTM_DEVICE_FUNCTIONS{
    PTTM_TT     (*TtmTtCreate)(PTTM_BUFFER_OBJECT BufferObject, UINT64 TtmPageFlags);
    LOUSTATUS   (*TtmTtPopulate)(struct _DRSD_TTM_DEVICE* Device, struct _TTM_TT* Ttm, PTTM_OPERATION_CONTEXT Context);
    void        (*TtmTtUnpopulate)(struct _DRSD_TTM_DEVICE* Device, struct _TTM_TT* Ttm);
    void        (*TtmTtDestroy)(struct _DRSD_TTM_DEVICE* Device, struct _TTM_TT* Ttm);
    BOOLEAN     (*EvictionValuable)(PTTM_BUFFER_OBJECT Bo, PTTM_PLACE Place);
    void        (*EvictFlags)(PTTM_BUFFER_OBJECT BufferObject, PTTM_PLACEMENT Placement);
    LOUSTATUS   (*Move)(PTTM_BUFFER_OBJECT BufferObject, BOOLEAN Evict, PTTM_OPERATION_CONTEXT Context, PTTM_RESOURCE NewMem, PTTM_PLACE Hop);
    void        (*DeleteMemNotify)(PTTM_BUFFER_OBJECT BufferObject);
    void        (*SwapNotify)(PTTM_BUFFER_OBJECT BufferObject);
    LOUSTATUS   (*IoMemReserve)(struct _DRSD_TTM_DEVICE* Device, PTTM_RESOURCE Mem);
    void        (*IoMemFree)(struct _DRSD_TTM_DEVICE* Device, PTTM_RESOURCE Mem);
    UINT64      (*IoMemPfn)(PTTM_BUFFER_OBJECT BufferObject, UINT64 PageOffset);
    LOUSTATUS   (*AccessMemory)(PTTM_BUFFER_OBJECT BufferObject, UINT64 Offset, PVOID Buffer, int Length, int Write);
    void        (*ReleaseNotify)(PTTM_BUFFER_OBJECT BufferObject);
}TTM_DEVICE_FUNCTIONS, * PTTM_DEVICE_FUNCTIONS;

struct _TTM_RESOURCE_MANAGER;

typedef struct _TTM_RESOURCE_MANAGER_FUNCTION{
    LOUSTATUS   (*Alloc)(struct _TTM_RESOURCE_MANAGER* Manager, PTTM_BUFFER_OBJECT BufferObject, PTTM_PLACE TtmPlace, PTTM_RESOURCE* Resource);
    void        (*Free)(struct _TTM_RESOURCE_MANAGER* Manager, PTTM_RESOURCE Resource);
    BOOLEAN     (*Intersects)(struct _TTM_RESOURCE_MANAGER* Manager, PTTM_RESOURCE Resource, PTTM_PLACE Place, SIZE Size);
    BOOLEAN     (*Compatible)(struct _TTM_RESOURCE_MANAGER* Manager, PTTM_RESOURCE Resource, PTTM_PLACE Place, SIZE Size);
    void        (*Debug)(struct _TTM_RESOURCE_MANAGER* Manager, HANDLE DrsdClfsServer);
}TTM_RESOURCE_MANAGER_FUNCTION, * PTTM_RESOURCE_MANAGER_FUNCTION;

#define TTM_MOVE_FENCES_COUNT 8

typedef struct _TTM_RESOURCE_MANAGER{
    BOOLEAN                             UseType;
    BOOLEAN                             UseTt;
    struct _DRSD_TTM_DEVICE*            TtmDevice;    
    UINT64                              Size;
    PTTM_RESOURCE_MANAGER_FUNCTION      Functions;
    spinlock_t                          EvictionLock;
    HANDLE                              DmaFences[TTM_MOVE_FENCES_COUNT];
    ListHeader                          Lcu[TTM_MAX_BUFFER_OBJECT_PRIORITIES];
    UINT64                              Usage;
    HANDLE                              CGroupRegion;
}TTM_RESOURCE_MANAGER, * PTTM_RESOURCE_MANAGER;

typedef struct _DRSD_TTM_DEVICE{
    ListHeader                  DeviceList;
    UINT                        AllocationFlags;
    PTTM_DEVICE_FUNCTIONS       Functions;
    TTM_RESOURCE_MANAGER        SystemManager;
    PTTM_RESOURCE_MANAGER       ManagerDriver[TTM_MEM_TYPES_COUNT];
    PDRSD_VMA_OFFSET_MANAGER    VmaManager;
    TTM_POOL                    Pool;
    spinlock_t                  LruLock;
    ListHeader                  Unevictable;
    PLOUQ_WORK_QUEUE            WorkQueue;
}DRSD_TTM_DEVICE, * PDRSD_TTM_DEVICE;

typedef struct _TTM_GLOBAL{
    PVOID       DumbyReadPage;
    ListHeader  DeviceList;
    atomic_t    BoCount;
}TTM_GLOBAL, * PTTM_GLOBAL;

typedef struct _DRSD_VRAM_MM{
    UINT64              VRamBase;
    SIZE                VRamSize;
    DRSD_TTM_DEVICE     TtmDevice;
}DRSD_VRAM_MM, * PDRSD_VRAM_MM;

typedef enum _DRSD_SWITCH_POWER_STATE{
    DRSD_SWITCH_POWER_ON = 0,
    DRSD_SWITCH_POWER_OFF,
    DRSD_SWITCH_POWER_CHANGING,
    DRSD_SWITCH_POWER_DYNAMIC_OFF,
}DRSD_SWITCH_POWER_STATE, * PDRSD_SWITCH_POWER_STATE;

struct _DRSD_CLIENT_DEVICE;

typedef struct _DRSD_CLIENT_FUNCTIONS{
    PDRIVER_OBJECT      Owner;
    void                (*Free)(struct _DRSD_CLIENT_DEVICE* Client);
    void                (*Unregister)(struct _DRSD_CLIENT_DEVICE* Client);
    LOUSTATUS           (*Restore)(struct _DRSD_CLIENT_DEVICE* Client, BOOLEAN Force);
    LOUSTATUS           (*Hotplug)(struct _DRSD_CLIENT_DEVICE* Client);
    LOUSTATUS           (*Suspend)(struct _DRSD_CLIENT_DEVICE* Client);
    LOUSTATUS           (*Resume)(struct _DRSD_CLIENT_DEVICE* Client);
}DRSD_CLIENT_FUNCTIONS, * PDRSD_CLIENT_FUNCTIONS;

typedef struct _DRSD_MODE_SET{
    PDRSD_FRAME_BUFFER      FrameBuffer;
    PDRSD_CRTC              Crtc;
    PDRSD_DISPLAY_MODE      Mode;
    UINT32                  X;
    UINT32                  Y;
    PDRSD_CONNECTOR*        Connectors;
    SIZE                    ConnectorCount;
}DRSD_MODE_SET, * PDRSD_MODE_SET;

typedef struct _DRSD_CLIENT_DEVICE{
    struct _DRSD_DEVICE*    Device;
    LOUSTR                  Name;
    ListHeader              List;
    PDRSD_CLIENT_FUNCTIONS  Functions;
    DRSD_FILE               File;
    mutex_t                 ModesetMutex;
    PDRSD_MODE_SET          ModeSets;
    BOOLEAN                 Suspend;
    BOOLEAN                 HotplugPending;
    BOOLEAN                 HotplugFailed;
}DRSD_CLIENT_DEVICE, * PDRSD_CLIENT_DEVICE;

typedef struct _DRSD_CLIENT_BUFFER{
    PDRSD_CLIENT_DEVICE             ClientDevice;
    PDRSD_GXE_OBJECT                GxeObject;
    PIO_MAP_OBJECT                  IoMap;
    PDRSD_FRAME_BUFFER              FrameBuffer;
}DRSD_CLIENT_BUFFER, * PDRSD_CLIENT_BUFFER;

typedef struct _DRSD_CLIP_RECT{
    USHORT  X1;
    USHORT  Y1;
    USHORT  X2;
    USHORT  Y2;
}DRSD_CLIP_RECT, * PDRSD_CLIP_RECT;

struct _DRSD_FB_HELPER;

typedef struct _DRSD_FB_HELPER_FUNCTIONS{
    LOUSTATUS   (*FbDirty)(struct _DRSD_FB_HELPER* Helper, PDRSD_CLIP_RECT Clip);
    void        (*FbRestore)(struct _DRSD_FB_HELPER* Helper);
    void        (*FbSetSuspend)(struct _DRSD_FB_HELPER* Helper, BOOLEAN Suspend);
}DRSD_FB_HELPER_FUNCTIONS, * PDRSD_FB_HELPER_FUNCTIONS;

typedef struct _FB_BITFIELD{
    UINT32      Offset;
    UINT32      Length;
    UINT32      MsbRight;
}FB_BITFIELD, * PFB_BITFIELD;

typedef struct _FB_VAR_SCREEN_INFO{
    UINT32          XRes;
    UINT32          YRes;
    UINT32          XResVirt;
    UINT32          YResVirt;
    UINT32          XOffset;
    UINT32          YOffset;
    UINT32          Bpp;
    UINT32          Grayscale;
    FB_BITFIELD     Red;
    FB_BITFIELD     Green;
    FB_BITFIELD     Blue;
    FB_BITFIELD     Transparent;
    UINT32          NonStd;
    UINT32          Activate;
    UINT32          Height;
    UINT32          Width;
    UINT32          AccelFlags;
    UINT32          PixelClock;
    UINT32          LeftMargin;
    UINT32          RightMargin;
    UINT32          UpperMargin;
    UINT32          LowerMargin;
    UINT32          HSyncLength;
    UINT32          YSyncLength;
    UINT32          Sync;
    UINT32          VMode;
    UINT32          Rotate;
    UINT32          ColorSpace;
    UINT32          Reserved[4];       
}FB_VAR_SCREEN_INFO, * PFB_VAR_SCREEN_INFO;

typedef struct _DRSD_FB_FIX_SCREEN_INFO{
    CHAR        Id[16];
    UINT64      SMemStart;
    UINT32      SMemLength;
    UINT32      Type;
    UINT32      TypeAux;
    UINT32      Visual;
    UINT16      XPanStep;
    UINT16      YPanStep;
    UINT16      YWrapStep;
    UINT32      LineLength;
    UINT64      MmioStart;
    UINT32      MmioLength;
    UINT32      Accel;
    UINT16      Cap;
    UINT16      Reserved[2];
}DRSD_FB_FIX_SCREEN_INFO, * PDRSD_FB_FIX_SCREEN_INFO;

typedef struct _DRSD_FB_CHROMA{
    UINT32  Redx;
    UINT32  Greenx;
    UINT32  Bluex;
    UINT32  Whitex;
    UINT32  Redy;
    UINT32  ReGreeny;
    UINT32  Bluey;
    UINT32  Whitey;
}DRSD_FB_CHROMA, * PDRSD_FB_CHROMA;

typedef struct _DRSD_FB_VIDEO_MODE{
    LOUSTR  Name;
    UINT32  Refresh;
    UINT32  XRes;
    UINT32  YRes;
    UINT32  PixelClock;
    UINT32  LeftMargin;
    UINT32  RightMargin;
    UINT32  UpperMargin;
    UINT32  LowerMargin;
    UINT32  HSyncLength;
    UINT32  VSyncLength;
    UINT32  Sync;
    UINT32  VMode;
    UINT32  Flag;
}DRSD_FB_VIDEO_MODE, * PDRSD_FB_VIDEO_MODE;

typedef struct _DRSD_FB_MONSPECS{
    DRSD_FB_CHROMA          Chroma;
    PDRSD_FB_VIDEO_MODE     ModeDataBase;
    UINT8                   Manufacturer[4];
    UINT8                   Monitor[14];
    UINT8                   SerialNo[14];
    UINT8                   Ascii[14];
    UINT32                  ModeDataBaseLength;
    UINT32                  Model;
    UINT32                  Serial;
    UINT32                  Year;
    UINT32                  Week;
    UINT32                  HfMin;
    UINT32                  HfMax;
    UINT32                  DclMin;
    UINT32                  DclMax;
    UINT16                  Input;
    UINT16                  Dpms;
    UINT16                  Signal;
    UINT16                  VfMin;
    UINT16                  VfMax;
    UINT16                  Gamma;
    UINT16                  Misc;
    BOOLEAN                 Gtf;
    UINT8                   Version;
    UINT8                   Revision;
    UINT8                   MaxX;                 
    UINT8                   MaxY;                 
}DRSD_FB_MONSPECS, * PDRSD_FB_MONSPECS;

struct _DRSD_FB_INFO;

typedef struct _DRSD_FB_PIXMAP{
    UINT8*      Address;
    UINT32      Size;
    UINT32      BufferAlignment;
    UINT32      ScanAlignment;
    UINT32      AccessAlignment;
    UINT32      Flags;
    SIZE        BLitX;
    SIZE        BLitY;
    void        (*WriteIo)(struct _DRSD_FB_INFO* Info, PVOID Destination, PVOID Source, SIZE Size);
    void        (*ReadIo)(struct _DRSD_FB_INFO* Info, PVOID Destination, PVOID Source, SIZE Size);
}DRSD_FB_PIXMAP, * PDRSD_FB_PIXMAP;

typedef struct _DRSD_FB_CMAP{
    UINT32      Start;
    UINT32      Length;
    UINT16*     Red;
    UINT16*     Green;
    UINT16*     Blue;
    UINT16*     Transparent;
}DRSD_FB_CMAP, * PDRSD_FB_CMAP;

typedef struct _DRSD_BACKLIGHT_DEVICE{
    UINT64 Todo; //TODO
}DRSD_BACKLIGHT_DEVICE, * PDRSD_BACKLIGHT_DEVICE;

#define FB_BACKLIGHT_LEVELS 128

typedef struct _DRSD_LCD_DEVICE{
    UINT64 Todo; //TODO
}DRSD_LCD_DEVICE, * PDRSD_LCD_DEVICE;

typedef struct _DRSD_FB_DEFERRED_IO_PAGE_REFERENCES{
    UINT64 Todo; //TODO
}DRSD_FB_DEFERRED_IO_PAGE_REFERENCES, * PDRSD_FB_DEFERRED_IO_PAGE_REFERENCES;

typedef struct _DRSD_FB_DEFERRED_IO{
    UINT64 Todo; //TODO
}DRSD_FB_DEFERRED_IO, * PDRSD_FB_DEFERRED_IO;

typedef struct _DRSD_FB_TITLE_BLITTING{
    UINT64 Todo; //TODO
}DRSD_FB_TITLE_BLITTING, * PDRSD_FB_TITLE_BLITTING;

typedef struct _DRSD_FBCON_PAR{
    UINT64 Todo; //TODO
}DRSD_FBCON_PAR, * PDRSD_FBCON_PAR; 

typedef struct _DRSD_FB_INFO{
    KERNEL_REFERENCE                        Count;
    int                                     Node;
    int                                     Flags;
    int                                     FbConRototateHint;
    mutex_t                                 Lock;
    mutex_t                                 MmLock;
    FB_VAR_SCREEN_INFO                      Var;
    DRSD_FB_FIX_SCREEN_INFO                 Fix;
    DRSD_FB_MONSPECS                        MonoSpecs;
    DRSD_FB_PIXMAP                          PixMap;
    DRSD_FB_PIXMAP                          Sprite;
    DRSD_FB_CMAP                            Cmap;
    ListHeader                              ModeList;
    DRSD_FB_VIDEO_MODE                      VideoMode;
    int                                     Blank;
    PDRSD_BACKLIGHT_DEVICE                  BackLightDevice;
    mutex_t                                 BlCurveMutex;
    UINT8                                   BlCurve[FB_BACKLIGHT_LEVELS];
    PDRSD_LCD_DEVICE                        LcdDevice;
    PLOUQ_DELAYED_WORK                      DeferredWork;
    UINT64                                  PageReferenceCount;
    PDRSD_FB_DEFERRED_IO_PAGE_REFERENCES    PageReferences;
    PDRSD_FB_DEFERRED_IO                    FbDefIo;
    PLATFORM_DEVICE                         ParrentDevice;
    PLATFORM_DEVICE                         Device;
    PDRSD_FB_TITLE_BLITTING                 TileOps;
    union {
        LOUSTR                              ScreenBase;
        LOUSTR                              ScreenBuffer;
    };
    UINT64                                  ScreenSize;
    PVOID                                   PseudoPallette;
    UINT32                                  State;
    PDRSD_FBCON_PAR                         FbConPar;
    PVOID                                   Par;
    BOOLEAN                                 VtSkipSwitch;
    BOOLEAN                                 SkipPanic;
}DRSD_FB_INFO, * PDRSD_FB_INFO;

typedef struct _DRSD_FB_HELPER{
    DRSD_CLIENT_DEVICE              ClientDevice;
    PDRSD_CLIENT_BUFFER             Buffer;
    DRSD_FRAME_BUFFER               FrameBuffer;
    struct _DRSD_DEVICE*            Device;
    PDRSD_FB_HELPER_FUNCTIONS       Functions;
    PDRSD_FB_INFO                   Info;
    UINT32                          SudoPalette[17];
    DRSD_CLIP_RECT                  DamageClip;
    spinlock_t                      DamageLock;
    LOUQ_WORK                       DamageWork;
    LOUQ_WORK                       ResumeWork;
    mutex_t                         Lock;
    BOOLEAN                         DelayedHotplug;
    BOOLEAN                         DeferredSetup;
    int                             PreferedBpp;
    DRSD_FB_DEFERRED_IO             FbDeferredIo;
}DRSD_FB_HELPER, * PDRSD_FB_HELPER;

typedef struct _DRSE_MODE_CREATE_DUMB{
    UINT32      Height;
    UINT32      Width;
    UINT32      Bpp;
    UINT32      Flags;
    UINT32      Handle;
    UINT32      Pitch;
    UINT64      Size;
}DRSE_MODE_CREATE_DUMB, * PDRSE_MODE_CREATE_DUMB;

typedef struct _DRSD_FB_HELPER_SURFACE_SIZE{
    UINT32 FbWidth;
    UINT32 FbHeight;
    UINT32 SurfaceWidth;
    UINT32 SurfaceHeight;
    UINT32 SurfaceBpp;
    UINT32 SurfaceDepth;
}DRSD_FB_HELPER_SURFACE_SIZE, * PDRSD_FB_HELPER_SURFACE_SIZE;

typedef struct _DRSD_DRIVER{
    UINT32              DriverFeatures;
    LOUSTATUS           (*Load)(struct _DRSD_DEVICE* Device, UINT64 Flags); //Notice: Dont use this for new drivers
    LOUSTATUS           (*Open)(struct _DRSD_DEVICE* Device, PDRSD_FILE DrsdFile);
    void                (*PostClose)(struct _DRSD_DEVICE* Device, PDRSD_FILE DrsdFile);
    void                (*Unload)(struct _DRSD_DEVICE* Device);
    void                (*Release)(struct _DRSD_DEVICE* Device);
    void                (*MasterSet)(struct _DRSD_DEVICE* Device, PDRSD_FILE FilePrivate, BOOLEAN FromOpen);
    void                (*MasterDrop)(struct _DRSD_DEVICE* Device, PDRSD_FILE FilePrivate);
    void                (*ClfsServerInitialze)(PDRSD_MINOR Minor);
    PDRSD_GXE_OBJECT    (*GxeCreateObject)(struct _DRSD_DEVICE* Device, SIZE Size);
    LOUSTATUS           (*PrimeHandleToFd)(struct _DRSD_DEVICE* Device, PDRSD_FILE FilePrivate, UINT32 Handle, UINT32 Flags, int* PrimeFd);
    LOUSTATUS           (*PrimeFdToHandle)(struct _DRSD_DEVICE* Device, PDRSD_FILE FilePrivate, int PrimeFd, UINT32* Handle);
    
    LOUSTATUS           (*DumbCreate)(PDRSD_FILE File, struct _DRSD_DEVICE* Device, PDRSE_MODE_CREATE_DUMB Args);
    LOUSTATUS           (*DumbMapOffset)(PDRSD_FILE File, struct _DRSD_DEVICE* Device, UINT32 Handle, UINT64* Offset);
    LOUSTATUS           (*FbDevProbe)(PDRSD_FB_HELPER FbDevHelpers, PDRSD_FB_HELPER_SURFACE_SIZE Sizes);
}DRSD_DRIVER, * PDRSD_DRIVER;

typedef struct _DRSD_DEVICE{
    ListHeader                      Peers;
    struct _PCI_DEVICE_OBJECT*      PDEV;
    struct _LMPOOL_DIRECTORY*       VramPool;
    DRSD_MODE_OBJECT                BaseMode;
    PDRSD_DISPLAY_MODE              DisplayModes;
    uint32_t                        PossibleCrtcs;
    PDRSD_PLANE                     Planes;
    PDRSD_CRTC                      Crtcs;
    PDRSD_ENCODER                   Encoders;
    PDRSD_CONNECTOR                 Connectors;
    spinlock_t                      VBlankLock;
    PDRSD_VBLANK_CRTC               VBlanks;

    //New Drsd data
    int                             InterfaceVersion;
    KERNEL_REFERENCE                Reference;
    PLATFORM_DEVICE                 BusDevice;
    PLATFORM_DEVICE                 DmaDevice;
    struct {    
        ListHeader                  Resources;
        PVOID                       FinalFree;
        spinlock_t                  Lock;
    }Managed;
    PDRSD_DRIVER                    DeviceDriver;
    PVOID                           DevicePrivateData;
    PDRSD_MINOR                     Primary;
    PDRSD_MINOR                     Render;
    PDRSD_MINOR                     Accel;
    BOOL                            Registered;
    PDRSD_MASTER                    Master;
    LOUSTR                          HugeMount;
    UINT32                          DriverFeatures;
    BOOLEAN                         Unplugged;
    HANDLE                          Inode;
    LOUSTR                          Uid;
    mutex_t                         MasterMutex;
    atomic_t                        OpenCount;
    mutex_t                         FileListMutex;
    ListHeader                      FileList;
    ListHeader                      FileListInternal;
    mutex_t                         ClientListMutex;
    ListHeader                      ClientList;
    ListHeader                      ClientSysrqList;
    BOOLEAN                         VBlankImmediateDisable;
    PDRSD_VBLANK_CRTC               VBlankCount;
    spinlock_t                      VBlankTimeLock;
    spinlock_t                      VblLock;
    UINT32                          MaxVBlankCount;
    ListHeader                      VBlankEventList;
    spinlock_t                      EventLock;
    UINT                            CrtcCount;
    DRSD_MODE_CONFIGURATION         ModeConfig;
    mutex_t                         ObjectNameLock;
    XARRAY                          ObjectNameIdr;
    PDRSD_VMA_OFFSET_MANAGER        VmaOffsetManager;
    PDRSD_VRAM_MM                   VramManager;
    DRSD_SWITCH_POWER_STATE         SwitchPowerState;
    HANDLE                          DrsdClfsServer;
}DRSD_DEVICE, * PDRSD_DEVICE;

#define STANDARD_INTEL_CHIPSET_EDID_SIZE 128

typedef struct PACKED _EDID_PRODUCT_IDENTIFICATION{
    uint16_t Manufacturer;
    uint16_t ProductCode;
    uint32_t Serial;
    uint8_t  WeekOfFacture;
    uint8_t  YearOfFacture;
}EDID_PRODUCT_IDENTIFICATION, * PEDID_PRODUCT_IDENTIFICATION;

typedef struct PACKED _DETAILED_PIXEL_TIMING{
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

typedef struct PACKED _CVT_TIMING{
    uint8_t Code[3];
}CVT_TIMING, * PCVT_TIMING;

typedef struct PACKED _DETAILED_WINDOWS_WP_INDEX{
    uint8_t WhiteXyLow;
    uint8_t WhiteXHigh;
    uint8_t WhiteYHigh;
    uint8_t Gamma;
}DETAILED_WINDOWS_WP_INDEX, * PDETAILED_WINDOWS_WP_INDEX;

typedef struct PACKED _DETAILED_DATA_MONITOR_RANGE{
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
        }PACKED Gtf2;
        struct {
            uint8_t Version;
            uint8_t Data1;
            uint8_t Data2;
            uint8_t SupportedAsspects;
            uint8_t Flags;
            uint8_t SupportedScailings;
            uint8_t PreferedRefresh;
        }PACKED Cvt;
    }PACKED Form;
}DETAILED_DATA_MONITOR_RANGE, * PDETAILED_DATA_MONITOR_RANGE;

typedef struct PACKED _DETAILED_DATA_STRING{
    uint8_t String[13];
}DETAILED_DATA_STRING, * PDETAILED_DATA_STRING;

typedef struct PACKED _DETAILED_NON_PIXEL_TIMING{
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
    }PACKED;
}DETAILED_NON_PIXEL_TIMING, * PDETAILED_NON_PIXEL_TIMING;

typedef struct PACKED _DETAILED_TIMING{
    uint16_t PixelClock;
    union{
        DETAILED_PIXEL_TIMING       PixelData;
        DETAILED_NON_PIXEL_TIMING   OtherData;
    }PACKED Data;
}DETAILED_TIMING, * PDETAILED_TIMING;

typedef struct PACKED _INTEL_STANDARD_EDID{
    uint8_t     Header[8];
    union {
        EDID_PRODUCT_IDENTIFICATION ProductIdentification;
        struct {
            uint8_t     Manufacturer[2];
            uint8_t     ProductCode[2];
            uint32_t    Serial;
            uint8_t     WeekOfFacture;
            uint8_t     YearOfFacture;
        }PACKED;
    }PACKED;
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
    }PACKED EstTime[8];
    struct {
        uint8_t HSize;
        uint8_t AspectFrequenc;
    }PACKED Timing[4];
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

struct _DRSD_CLIP;

typedef struct _DRSD_PLANE_CHAIN{
    ListHeader          Peers;
    PDRSD_PLANE         PlaneID;
    void                (*PrimaryAtomicUpdate)(PDRSD_PLANE, void* Handle);
    bool                PlaneReady;
}DRSD_PLANE_CHAIN, * PDRSD_PLANE_CHAIN;

typedef struct _LAYERED_CLIP_CHAIN{
    PDRSD_PLANE_CHAIN NextChain;
    PDRSD_PLANE_CHAIN LastChain;
    PDRSD_PLANE_CHAIN CurrentChain;
}LAYERED_CLIP_CHAIN, * PLAYERED_CLIP_CHAIN;

typedef struct _DRSD_CLIP{
    ListHeader              Peers;
    PDRSD_PLANE_CHAIN       PlaneGroup;
    size_t                  PlaneCount;
    void                    (*SignalClipChange)(struct _DRSD_CLIP*, DRSD_CLIP_UPDATE_REASON, void* UpdateData);
    INT64                   X;
    INT64                   Y;
    INT64                   Width;
    INT64                   Height;
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



typedef enum _DRSD_COLOR_OP_CURVE_1D_TYPE{
    DRSD_COLOR_OP_1D_CURVE_SRGB_EOTF = 0,
    DRSD_COLOR_OP_1D_CURVE_SRGB_INV_EOTF,
    DRSD_COLOR_OP_1D_CURVE_PQ_125_EOTF,
    DRSD_COLOR_OP_1D_CURVE_PQ_125_INV_EOTF,
    DRSD_COLOR_OP_1D_CURVE_BT2020_INV_OETF,
    DRSD_COLOR_OP_1D_CURVE_BT2020_OETF,
    DRSD_COLOR_OP_1D_CURVE_GAMMA22,
    DRSD_COLOR_OP_1D_CURVE_GAMMA22_INV,
    DRSD_COLOR_OP_1D_CURVE_MAX,
}DRSD_COLOR_OP_CURVE_1D_TYPE, * PDRSD_COLOR_OP_CURVE_1D_TYPE;

typedef struct _DRSD_PROPRIETARY_BLOB{
    PDRSD_MODE_OBJECT       ModeObject;
    PDRSD_DEVICE            DrsdDevice;
    ListHeader              GlobalHead;
    ListHeader              FileHead;
    SIZE                    Length;
    PVOID                   Data;
}DRSD_PROPRIETARY_BLOB, * PDRSD_PROPRIETARY_BLOB;

typedef struct _DRSD_COLOR_OP_STATE{
    struct _DRSD_COLOR_OP*          ColorOp;
    BOOLEAN                         Bypass;
    DRSD_COLOR_OP_CURVE_1D_TYPE     Curve1DType;
    UINT64                          Multiplier;
    PDRSD_PROPRIETARY_BLOB          Data;
    struct _DRSD_ATOMIC_STATE*      State;
}DRSD_COLOR_OP_STATE, * PDRSD_COLOR_OP_STATE;

typedef enum _DRSD_COLOR_OP_TYPE{
    DRSD_COLOR_OP_1D_CURVE = 0,
    DRSD_COLOR_OP_1D_LUT,
    DRSD_COLOR_OP_CTM_3X4,
    DRSD_COLOR_OP_MULTIPLIER,
    DRSD_COLOR_OP_3D_LUT,
}DRSD_COLOR_OP_TYPE, * PDRSD_COLOR_OP_TYPE;

struct _DRSD_COLOR_OP;

typedef enum _DRSD_COLOR_OP_LUT1D_INTERPOLATION_TYPE{
    DRSD_COLOR_OP_LUT1D_INTERPOLATION_LINEAR = 0,
}DRSD_COLOR_OP_LUT1D_INTERPOLATION_TYPE, * PDRSD_COLOR_OP_LUT1D_INTERPOLATION_TYPE;

typedef enum _DRSD_COLOR_OP_LUT3D_INTERPOLATION_TYPE{
    DRSD_COLOR_OP_LUT3d_INTERPOLATION_TETRAHEDRAL = 0,
}DRSD_COLOR_OP_LUT3D_INTERPOLATION_TYPE, * PDRSD_COLOR_OP_LUT3D_INTERPOLATION_TYPE;

typedef struct _DRSD_COLOR_OP{
    PDRSD_DEVICE                                Device;
    ListHeader                                  Head;
    UINT                                        Index;
    DRSD_MODE_OBJECT                            Base;
    PDRSD_PLANE                                 Plane;
    PDRSD_COLOR_OP_STATE                        State;
    PDRSD_OBJECT_PROPERTIES                     Properties;
    DRSD_COLOR_OP_TYPE                          Type;
    struct _DRSD_COLOR_OP*                      Next;
    PDRSD_PROPERTY                              TypeProperty;
    PDRSD_PROPERTY                              BypassProperty;
    UINT32                                      Size;
    DRSD_COLOR_OP_LUT1D_INTERPOLATION_TYPE      Lut1dInterpolation;
    DRSD_COLOR_OP_LUT3D_INTERPOLATION_TYPE      Lut3dInterpolation;
    PDRSD_PROPERTY                              Lut1dInterpolationProperty;
    PDRSD_PROPERTY                              Curve1dTypeProperty;
    PDRSD_PROPERTY                              MultiplierProperty;
    PDRSD_PROPERTY                              SizeProperty;
    PDRSD_PROPERTY                              Lut3dInterpolationProperty;
    PDRSD_PROPERTY                              DataProperty;
    PDRSD_PROPERTY                              NextProperty;
}DRSD_COLOR_OP, * PDRSD_COLOR_OP;

typedef struct _DRSD_COLOR_OPS{
    PDRSD_COLOR_OP          ColorOp;
    PDRSD_COLOR_OP_STATE    State; 
    PDRSD_COLOR_OP_STATE    OldState; 
    PDRSD_COLOR_OP_STATE    NewState; 
}DRSD_COLOR_OPS, * PDRSD_COLOR_OPS;

typedef struct _DRSD_PLANES_STATE{
    PDRSD_PLANE             Plane;
    PDRSD_PLANE_STATE       StateToDestroy;
    PDRSD_PLANE_STATE       OldState;
    PDRSD_PLANE_STATE       NewState;
}DRSD_PLANES_STATE, * PDRSD_PLANES_STATE;

typedef struct _DRSD_CRTCS_STATE{
    PDRSD_CRTC          Crtc;
    PDRSD_CRTC_STATE    StateToDestroy;
    PDRSD_CRTC_STATE    OldState;
    PDRSD_CRTC_STATE    NewState;
    PDRSD_CRTC_COMMIT   Commit;
    INT32*              OutFence;
    UINT64              LastVBlankCount;
}DRSD_CRTCS_STATE, * PDRSD_CRTCS_STATE;

typedef struct _DRSD_CONNECTORS_STATE{
    PDRSD_CONNECTOR         Connector;
    PDRSD_CONNECTOR_STATE   StateToDestroy;         
    PDRSD_CONNECTOR_STATE   OldState;         
    PDRSD_CONNECTOR_STATE   NewState;
    INT32*                  OutFence;         
}DRSD_CONNECTORS_STATE, * PDRSD_CONNECTORS_STATE;

struct _DRSD_PRIVATE_OBJECTS_STATE;

typedef struct _DRSD_MODESET_ACQURE_CONTEXT{
    PVOID               AcquireContext;
    PDRSD_MODESET_LOCK  Contended;
    PVOID               DebugStack;
    ListHeader          Locked;
    BOOLEAN             TryLockOnly;
    BOOLEAN             Interruptable;
}DRSD_MODESET_ACQURE_CONTEXT, * PDRSD_MODESET_ACQUIRE_CONTEXT;

typedef struct _DRSD_ATOMIC_STATE{
    KERNEL_REFERENCE                        Reference;
    PDRSD_DEVICE                            Device;
    BOOLEAN                                 AllowModeSet;
    BOOLEAN                                 LegacyCurrsorUpdate;
    BOOLEAN                                 AsyncUpdate;
    BOOLEAN                                 Duplicated;
    BOOLEAN                                 Checked;
    BOOLEAN                                 PlaneColorPipeline;
    PDRSD_COLOR_OPS                         ColorOps;
    PDRSD_PLANES_STATE                      Planes;
    PDRSD_CRTCS_STATE                       Crtcs;
    INT32                                   ConnectorCount;
    PDRSD_CONNECTORS_STATE                  Connectors;
    INT32                                   PrivateObjectsCount;
    struct _DRSD_PRIVATE_OBJECTS_STATE*     PrivateObjects;
    PDRSD_MODESET_ACQUIRE_CONTEXT            AcquireContext;
    PDRSD_CRTC_COMMIT                       FakeCommit;
    LOUQ_WORK                               CommitWork;
}DRSD_ATOMIC_STATE, * PDRSD_ATOMIC_STATE;       

typedef struct _DRSD_PRIVATE_STATE{
    PDRSD_ATOMIC_STATE              State;
    struct _DRSD_PRIVATE_OBJECT*    Object;
}DRSD_PRIVATE_STATE, * PDRSD_PRIVATE_STATE;

typedef struct _DRSD_PRIVATE_OBJECTS_STATE{
    struct _DRSD_PRIVATE_OBJECT*    Object;
    PDRSD_PRIVATE_STATE             StateToDestroy;
    PDRSD_PRIVATE_STATE             OldState;
    PDRSD_PRIVATE_STATE             NewState;
}DRSD_PRIVATE_OBJECTS_STATE, * PDRSD_PRIVATE_OBJECTS_STATE;

struct _DRSD_PRIVATE_STATE_FUNCTIONS;

typedef struct _DRSD_PRIVATE_OBJECT{
    PDRSD_DEVICE                            Device;
    ListHeader                              Head;
    DRSD_MODESET_LOCK                       Lock;
    PDRSD_PRIVATE_STATE                     State;
    struct _DRSD_PRIVATE_STATE_FUNCTIONS*   Functions;
}DRSD_PRIVATE_OBJECT, * PDRSD_PRIVATE_OBJECT;   

typedef struct _DRSD_PRIVATE_STATE_FUNCTIONS{
    PDRSD_PRIVATE_STATE (*AtomicDuplicateState)(PDRSD_PRIVATE_OBJECT Object);
    void                (*AtomicDestroyState)(PDRSD_PRIVATE_OBJECT Object, PDRSD_PRIVATE_STATE State);
    void                (*AtomicPrintState)(HANDLE Server, PDRSD_PRIVATE_STATE State);
}DRSD_PRIVATE_STATE_FUNCTIONS, * PDRSD_PRIVATE_STATE_FUNCTIONS;

typedef struct _DRSD_BRIDGE_TIMINGS{
    UINT32  InputBusFlags;
    UINT32  SetupTimePs;
    UINT32  HoldTimePs;
    BOOLEAN DualLink;    
}DRSD_BRIDGE_TIMINGS, * PDRSD_BRIDGE_TIMINGS;

typedef enum _DRSD_BRIDGE_ATTATCH_FLAGS{
    DRSD_BRIDGE_ATTATCH_NO_CONNECTOR = 0,
}DRSD_BRIDGE_ATTATCH_FLAGS, * PDRSD_BRIDGE_ATTATCH_FLAGS;

struct _DRSD_BRIDGE;

typedef struct _DRSD_BUS_CONFIG{
    UINT32      Format;
    UINT32      Flags;
}DRSD_BUS_CONFIG, * PDRSD_BUS_CONFIG;   

typedef struct _DRSD_BRIDGE_STATE{
    PDRSD_PRIVATE_STATE     Base;
    struct _DRSD_BRIDGE*    Bridge;
    DRSD_BUS_CONFIG         InputBusConfig;
    DRSD_BUS_CONFIG         OutputBusConfig;
}DRSD_BRIDGE_STATE, * PDRSD_BRIDGE_STATE;

#include <drivers/Hdmi/Sound.h>
#include <drivers/Hdmi/Cec.h>

typedef struct _DRSD_BRIDGE_FUNCTIONS{
    LOUSTATUS                       (*Attatch)(struct _DRSD_BRIDGE* Bridge, PDRSD_ENCODER Encoder, DRSD_BRIDGE_ATTATCH_FLAGS Flags);
    void                            (*Destroy)(struct _DRSD_BRIDGE* Bridge);
    void                            (*Detatch)(struct _DRSD_BRIDGE* Bridge);
    DRSD_MODE_STATUS                (*ModeValid)(struct _DRSD_BRIDGE* Bridge, PDRSD_DISPLAY_INFORMATION DisplayInfo, PDRSD_DISPLAY_MODE DisplayMode);
    BOOLEAN                         (*ModeFixup)(struct _DRSD_BRIDGE* Bridge, PDRSD_DISPLAY_MODE Mode, PDRSD_DISPLAY_MODE AdjustedMode);
    void                            (*Disable)(struct _DRSD_BRIDGE* Bridge);
    void                            (*PostDisable)(struct _DRSD_BRIDGE* Bridge);
    void                            (*ModeSet)(struct _DRSD_BRIDGE* Bridge, PDRSD_DISPLAY_MODE DisplayMode, PDRSD_DISPLAY_MODE AdjustedMode);
    void                            (*PreEnable)(struct _DRSD_BRIDGE* Bridge);
    void                            (*Enable)(struct _DRSD_BRIDGE* Bridge);
    void                            (*AtomicPreEnable)(struct _DRSD_BRIDGE* Bridge, PDRSD_ATOMIC_STATE State);
    void                            (*AtomicEnable)(struct _DRSD_BRIDGE* Bridge, PDRSD_ATOMIC_STATE State);
    void                            (*AtomicDisable)(struct _DRSD_BRIDGE* Bridge, PDRSD_ATOMIC_STATE State);
    void                            (*AtomicPostDisable)(struct _DRSD_BRIDGE* Bridge, PDRSD_ATOMIC_STATE State);
    PDRSD_BRIDGE_STATE              (*AtomicDuplicateState)(struct _DRSD_BRIDGE* Bridge);
    void                            (*AtomicDestroyState)(struct _DRSD_BRIDGE* Bridge, PDRSD_BRIDGE_STATE State);
    PUINT32                         (*AtomicGetOutputBusFormats)(struct _DRSD_BRIDGE* Bridge, PDRSD_BRIDGE_STATE BridgeState, PDRSD_CRTC_STATE CrtcState, PDRSD_CONNECTOR_STATE ConnectorState, UINT32 OutputFormat, UINT* NumOutputFormats);
    PUINT32                         (*AtmoicGetInputBusFormats)(struct _DRSD_BRIDGE* Bridge, PDRSD_BRIDGE_STATE BridgeState, PDRSD_CRTC_STATE CrtcState, PDRSD_CONNECTOR_STATE ConnectorState, UINT32 InputFormat, UINT* NumInputFormats);
    LOUSTATUS                       (*AtomicCheck)(struct _DRSD_BRIDGE* Bridge, PDRSD_BRIDGE_STATE RidgeState, PDRSD_CRTC_STATE CrtcState, PDRSD_CONNECTOR_STATE ConnectorState);
    PDRSD_BRIDGE_STATE              (*AtomicReset)(struct _DRSD_BRIDGE* Bridge);
    DRSD_CONNECTOR_STATUS           (*Detect)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector);
    LOUSTATUS                       (*GetModes)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector);
    PDRSD_EDID_TRACKER              (*EdidRead)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector);
    void                            (*HpdNotify)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector, DRSD_CONNECTOR_STATUS Status);
    void                            (*HpdEnable)(struct _DRSD_BRIDGE* Bridge);
    void                            (*HpdDisable)(struct _DRSD_BRIDGE* Bridge);
    DRSD_MODE_STATUS                (*HdmiTmdsCharRateValid)(struct _DRSD_BRIDGE* Bridge, PDRSD_DISPLAY_MODE Mode, ULONGLONG TmdsRate);
    LOUSTATUS                       (*HdmiClearAviInfoFrame)(struct _DRSD_BRIDGE* Bridge);
    LOUSTATUS                       (*HdmiWriteAviInfoFrame)(struct _DRSD_BRIDGE* Bridge, UINT8* Buffer, SIZE Length);
    LOUSTATUS                       (*HdmiClearHdmiInfoFrame)(struct _DRSD_BRIDGE* Bridge);
    LOUSTATUS                       (*HdmiWriteHdmiInfoFrame)(struct _DRSD_BRIDGE* Bridge, UINT8* Buffer, SIZE Length);
    LOUSTATUS                       (*HdmiClearDrsdInfoFrame)(struct _DRSD_BRIDGE* Bridge);
    LOUSTATUS                       (*HdmiWriteDrsdInfoFrame)(struct _DRSD_BRIDGE* Bridge, UINT8* Buffer, SIZE Length);
    LOUSTATUS                       (*HdmiClearSpdInfoFrame)(struct _DRSD_BRIDGE* Bridge);
    LOUSTATUS                       (*HdmiWriteSpdInfoFrame)(struct _DRSD_BRIDGE* Bridge, UINT8* Buffer, SIZE Length);
    LOUSTATUS                       (*HdmiClearAudioInfoFrame)(struct _DRSD_BRIDGE* Bridge);
    LOUSTATUS                       (*HdmiWriteAudioInfoFrame)(struct _DRSD_BRIDGE* Bridge, UINT8* Buffer, SIZE Length);
    LOUSTATUS                       (*HdmiAudioStartup)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector);
    LOUSTATUS                       (*HdmiAudioPrepare)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connecor, PHDMI_CODEC_DAIFMT Format, PHDMI_CODEC_PARAMETERS hParams);
    void                            (*HdmiAudioShutdown)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector);
    LOUSTATUS                       (*HdmiAudioMuteStream)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector, BOOLEAN Enable, int Direction);
    LOUSTATUS                       (*HdmiCecInit)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector);
    LOUSTATUS                       (*HdmiCecEnable)(struct _DRSD_BRIDGE* Bridge, BOOLEAN Enable);
    LOUSTATUS                       (*HdmiCecLogAddress)(struct _DRSD_BRIDGE* Bridge, UINT8 LogicalAddress);
    LOUSTATUS                       (*HdmiCecTransmit)(struct _DRSD_BRIDGE* Bridge, UINT8 Atempts, UINT32 SignalFreeTime, PCEC_MESSAGE CecMassage);
    LOUSTATUS                       (*DpAudioStartup)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector);
    LOUSTATUS                       (*DpAudioPrepare)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector, PHDMI_CODEC_DAIFMT Format, PHDMI_CODEC_PARAMETERS hParams);
    void                            (*DpAudioShutdown)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector);
    LOUSTATUS                       (*DpAudioMuteStream)(struct _DRSD_BRIDGE* Bridge, PDRSD_CONNECTOR Connector, BOOLEAN Enable, int Direction);
    void                            (*DrsdClfsCreateFile)(struct _DRSD_BRIDGE* Bridge, LOUSTR Path);
}DRSD_BRIDGE_FUNCTIONS, * PDRSD_BRIDGE_FUNCTIONS;

typedef enum _DRSD_BRIDGE_OPS{
    DRSD_BRIDGE_OP_DETECT = (1),
    DRSD_BRIDGE_OP_EDID = (1 << 1),
    DRSD_BRIDGE_OP_HPD = (1 << 2),
    DRSD_BRIDGE_OP_MODES = (1 << 3),
    DRSD_BRIDGE_OP_HDMI = (1 << 4), 
    DRSD_BRIDGE_OP_HDMI_AUDIO = (1 << 5),
    DRSD_BRIDGE_OP_DP_AUDIO = (1 << 6),
    DRSD_BRIDGE_OP_HDMI_CEC_NATIFIER = (1 << 7),
    DRSD_BRIDGE_OP_HDMI_CEC_ADAPTER = (1 << 7), 
    DRSD_BRIDGE_OP_HDMI_HDR_DRSD_INFO_FREAM = (1 << 9),
    DRSD_BRIDGE_OP_HDMI_SPD_INFO_FRAME = (1 << 10),
}DRSD_BRIDGE_OPS, * PDRSD_BRIDGE_OPS;

typedef struct _DRSD_BRIDGE{
    DRSD_PRIVATE_OBJECT             Base;
    PDRSD_DEVICE                    Device;
    PDRSD_ENCODER                   Encoder;
    ListHeader                      ChainNode;
    PVOID                           DeviceNode;
    ListHeader                      List;
    PDRSD_BRIDGE_TIMINGS            Timing;
    PDRSD_BRIDGE_FUNCTIONS          Functions;
    PVOID                           Container;
    KERNEL_REFERENCE                ReferenceCount;
    BOOLEAN                         Unplugged;
    PVOID                           DriverPrivate;
    DRSD_BRIDGE_OPS                 Ops;
    INT32                           Type;
    BOOLEAN                         InterlaceAllowed;
    BOOLEAN                         Ycbcr420Allowed;
    BOOLEAN                         PreEnablePreFirst;
    BOOLEAN                         SupportHdcp;
    PVOID                           I2cDdc;
    LOUSTR                          Vendor;
    LOUSTR                          Product;
    UINT                            SupportedFormats;
    UINT                            MaxBpc;
    PVOID                           HdmiCecDevice;
    PVOID                           HdmiAudioDevice;
    int                             HdmiAudioMaxI2csPlaybackChannels;
    BOOLEAN                         HdmiAudioSpdifPlaback;
    int                             HdmiAudioDaiPort;
    LOUSTR                          HdmiCecAdapterName;
    uint8_t                         HdmiCecAvailableLas;
    mutex_t                         HdpMutex;
    void                            (*HpdCb)(PVOID Data, DRSD_CONNECTOR_STATUS Status);
    PVOID                           HpdData;
    struct _DRSD_BRIDGE*            NextBridge;                
}DRSD_BRIDGE, * PDRSD_BRIDGE;

typedef struct _TTM_RANGE_MANAGER{
    TTM_RESOURCE_MANAGER    Manager;
    DRSD_MM                 Mm;
    spinlock_t              Lock;
}TTM_RANGE_MANAGER, * PTTM_RANGE_MANAGER;

#ifndef _USER_MODE_CODE_
#ifndef _DRSD_CORE_H
void LouKeDestroyClip(PDRSD_CLIP Clip);

void LouKeDrsdUpdateClipColor(PDRSD_CLIP Clip, uint32_t Color);
void LouKeUpdateClipState(PDRSD_CLIP Clip);

void LouKeDrsdHandleConflictingDevices(struct _PCI_DEVICE_OBJECT* PDEV);
//LOUAPI void LouKeOsDosUpdateMapping();

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

//LOUAPI void LouKeOsDosPrintCharecter(char Character);

void DirectAccessDrsdHotplugEvent(PDRSD_DEVICE Device);

LOUSTATUS LouKePassVramToDrsdMemoryManager(PDRSD_DEVICE Device, void* VramBase, size_t size, void* PAddress);

PDRSD_FRAME_BUFFER DrsdGxeCreateAsyncFramebuffer(
    PDRSD_DEVICE                Device,
    PDRSD_FILE                  FilePrivate,
    PDRSD_FORMAT_INFORMATION    Info,
    PDRSD_MODE_FB_COMMAND2      ModeCommand
);

DRSD_MODE_STATUS DrsdGxeVramInternalModeValid(
    PDRSD_DEVICE        Devics,
    PDRSD_DISPLAY_MODE  DisplayMode
);

LOUSTATUS DrsdInternalAtomicCheck(
    PDRSD_DEVICE        Device, 
    PDRSD_ATOMIC_STATE  State
);

LOUSTATUS DrsdInternalAtomicCommit(
    PDRSD_DEVICE        Device,
    PDRSD_ATOMIC_STATE  State,
    BOOLEAN             NonBlock
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
    PDRSD_CRTC         Crtc,
    PDRSD_CRTC_STATE   StateData
);

PDRSD_CRTC_STATE DrsdInternalCrtcDuplicateStateAtomic(
    PDRSD_CRTC          Crtc
);

void DrsdInternalCrtcResetAtomic(
    PDRSD_CRTC          Crtc 
);

LOUSTATUS DrsdInternalCrtcPageFlipAtomic(
    PDRSD_CRTC                      Crtc,
    PDRSD_FRAME_BUFFER              FrameBuffer,
    PDRSD_PENDING_VBLANK_EVENT      VBlankEvent,
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

void DrsdModeConfigReset(PDRSD_DEVICE Device);

DRIVER_IMPORT LOUSTATUS DrsdInternalProbeSingleConnectorModes(
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

DRIVER_IMPORT
LOUSTATUS DrsdUpdateEdidConnectorProperties(PDRSD_CONNECTOR Connector, PINTEL_STANDARD_EDID Edid);

PDRSD_PLANE_STATE DrsdGetNewPlaneState(PDRSD_PLANE_STATE OldState, PDRSD_PLANE Plane);

void LouKeDrsdClearScreen(PDRSD_PLANE Plane);

DRIVER_IMPORT
void DrsdModeConfigCleanup(PDRSD_DEVICE DrsdDevice);

DRIVER_IMPORT
PVOID
DrsdDeviceManagerAllocateDeviceEx(PPCI_DEVICE_OBJECT Pdev, PDRSD_DRIVER Driver, SIZE Size, SIZE Offset);

#define DrsdDeviceManagerAllocateDevice(Parent, Driver, Type, Member) \
    DrsdDeviceManagerAllocateDeviceEx(Parent, Driver, sizeof(Type), offsetof(Type, Member))

DRIVER_IMPORT
LOUSTATUS 
DrsdGxeVRamDriverDumbCreate(
    PDRSD_FILE Dile, 
    PDRSD_DEVICE Device, 
    PDRSE_MODE_CREATE_DUMB Args
);

DRIVER_IMPORT
LOUSTATUS
DrsdGxeTtmDumbMapOffset(
    PDRSD_FILE      File,
    PDRSD_DEVICE    Device,
    UINT32          Handle,
    UINT64*         Offset 
);

DRIVER_IMPORT
LOUSTATUS 
DrsdVRamHelperInitialize(
    PDRSD_DEVICE    Device,
    UINT64          VRamBase,
    SIZE            VRamSize
);

#ifdef DRSD_DRIVER_CONFIG_FBDEV_EMULATION 
//TODO
#else
#define DRSD_FBDEV_TTM_DRIVER_OPS \
    .FbDevProbe = 0x00
#endif

#endif
#endif
#ifdef __cplusplus
}
#endif
#endif