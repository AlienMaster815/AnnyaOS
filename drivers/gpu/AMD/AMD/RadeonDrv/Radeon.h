#ifndef _RADEON_H
#define _RADEON_H

#include "../AmdGpuBasic.h"

#define NUMBER_OF_RADEON_RINGS			8
#define RADEON_RING_TYPE_GFX_INDEX 0

typedef struct _RADEON_AGP_HEADER{
    PAGP_BRIDGE_DATA Bridge;
}RADEON_AGP_HEADER, * PRADEON_AGP_HEADER;


typedef struct _RADEON_FENCE{
    DrsdFence BaseFence;
    struct _RADEON_DEVICE* RDEV;
    uint64_t Sequence;
    uint64_t Ring;
    bool IsVmUpdated;
    LOUQ FenceWait;
}RADEON_FENCE, * PRADEON_FENCE;

typedef struct _RADEON_VM{
    mutex_t Mutex;
    uintptr_t CahcedData;
    spinlock_t StatusLock;
    ListHeader InvalidationList;
    ListHeader FreedList;
    ListHeader ClearedList;
}RADEON_VM, * PRADEON_VM;

typedef struct {
    uintptr_t Foo;
}RADEON_SYNC, * PRADEON_SYNC;

typedef struct _RADEON_IB{
    uintptr_t SubAllocationData;
    uint32_t LegthDw;
    uint64_t GpuAddress;
    uint32_t* Ptr;
    PRADEON_FENCE Fence;
    PRADEON_VM Vm;
    bool IsConstantIb;
    RADEON_SYNC Sync;
}RADEON_IB, * PRADEON_IB;

typedef struct _RADEON_RING{
    void (*IbExecute)(struct _RADEON_DEVICE* RDEV, PRADEON_IB Ib);
    uintptr_t EmitFence;
    uintptr_t EmitSemaphore;
    uintptr_t CsParse;
    uintptr_t RingStart;
    uintptr_t RingTest;
    uintptr_t IbTest;
    uintptr_t IsLockup;
    uintptr_t GetRptr;
    uintptr_t GetWptr;
    uintptr_t SetWptr;
}RADEON_RING, * PRADEON_RING;

typedef struct _RADEON_GART{
    void     (*TlbFlush)        (struct _RADEON_DEVICE* RDEV);
    uint64_t (*GetPageEntry)    (uint64_t Address, uint32_t Flags);
    void     (*SetPage)         (struct _RADEON_DEVICE* RDEV, uint64_t i, uint64_t Entry);
}RADEON_GART, * PRADEON_GART;

typedef struct _RADEON_IRQ_STRUCTURE{
    LOUSTATUS (*Set)        (struct _RADEON_DEVICE* RDEV);
    LOUSTATUS (*Process)    (struct _RADEON_DEVICE* RDEV);
}RADOEN_IRQ_STRUCTURE, * PRADOEN_IRQ_STRUCTURE;

typedef struct _RADEON_COPY_HANDLERS{
    PRADEON_FENCE (*Blit)       (struct _RADEON_DEVICE* RDEV, uint64_t Src, uint64_t Dst, uint64_t NumberOfGpuPages);
    uint64_t        BlitIndex; 
    PRADEON_FENCE (*Dma)        (struct _RADEON_DEVICE* RDEV, uint64_t Src, uint64_t Dst, uint64_t NumberOfGpuPages);
    uint64_t        DmaIndex;
    PRADEON_FENCE (*Copy)       (struct _RADEON_DEVICE* RDEV, uint64_t Src, uint64_t Dst, uint64_t NumberOfGpuPages);
    uint64_t CopyIndex;
}RADEON_COPY_HANDLERS, * PRADEON_COPY_HANDLERS;

typedef struct _RADEON_SURFACE_REGISTER{
    LOUSTATUS  (*SetRegister)       (struct _RADEON_DEVICE* RDEV, int Register, uint32_t TillingFlags, uint32_t Pitch, uint32_t Offset, uint32_t ObjSize);
    void       (*ClearRegister)     (struct _RADEON_DEVICE* RDEV, int Register);
}RADEON_SURFACE_REGISTER, * PRADEON_SURFACE_REGISTER; 

typedef enum{
    RADEON_HPD1 = 0,
    RADEON_HPD2,    
    RADEON_HPD3,    
    RADEON_HPD4,    
    RADEON_HPD5,    
    RADEON_HPD6,    
    RADEON_HPD_NONE = 0xFF,    
}RADEON_HPD_ID;

typedef struct _HPD_HANDLERS{
    void (*InitializationHahdler)  (struct _RADOEN_DEVICE* RDEV);
    void (*DeInitializationHandler)(struct _RADEON_DEVICE* RDEV);
    bool (*SenceHandler)           (struct _RADEON_DEVICE* RDEV, RADEON_HPD_ID ID);
    void (*SetPolarity)            (struct _RADEON_DEVICE* RDEV, RADEON_HPD_ID ID);
}HPD_HANDLERS, * PHPD_HANDLERS;

typedef struct _RADEON_POWER_MANAGEMENT{
    void (*Miscilanious)(struct _RADEON_DEVICE* RDEV);
    void (*Prepare)(struct _RADEON_DEVICE* RDEV);
    void (*DeInitialize)(struct _RADEON_DEVICE* RDEV);
    void (*InitializeProfile)(struct _RADEON_DEVICE* RDEV);
    void (*GetDynamicPowerManagementState)(struct _RADEON_DEVICE* RDEV);
    uint32_t (*GetEngineClock)(struct _RADEON_DEVICE* RDEV);
    void (*SetEngineClock)(struct _RADEON_DEVICE* RDEV, uint32_t Clock);
    uint32_t (*GetMemoryClock)(struct _RADEON_DEVICE* RDEV);
    void (*SetMemoryClock)(struct _RADEON_DEVICE* RDEV, uint32_t Clock);
    int (*GetPcieLanes)(struct _RADEON_DEVICE* RDEV);
    void (*SetPcieLanes)(struct _RADEON_DEVICE* RDEV, int Lane);
    void (*SetClockGating)(struct _RADEON_DEVICE* RDEV, int Enable);
}RADEON_POWER_MANAGEMENT, * PRADEON_POWER_MANAGEMENT;

typedef struct _PFLIP{
    void (*PageFlip)        (struct _RADEON_DEVICE* RDEV, int Crtc, uint64_t CrtcBase, bool ASYNC);
    void (*PageFlipPending) (struct _RADEON_DEVICE* RDEV, int Crtc);
}PFLIP, * PPFLIP;

typedef enum{
    RMX_OFF = 0,
    RMX_FULL = 1,
    RMX_CENTER = 2,
    RMX_ASPECT = 3,
}RADEON_RMX_TYPE;

typedef enum{   
    UNDERSCAN_OFF = 0,
    UNDERSCAN_ON = 1,
    UNDERSCAN_AUTO = 2,
}RADEON_UNDERSCAN_TYPE;

typedef struct _RADEON_AUDIO_HANDLERS{
    uintptr_t Functions;
}RADEON_AUDIO_HANDLERS, * PRADEON_AUDIO_HANDLERS;

typedef enum {
    RADEON_OUTPUT_CSC_BYPASS = 0,
    RADEON_OUTPUT_CSC_TVRGB = 1,
    RADEON_OUTPUT_CSC_YCBCR601 = 2,
    RADEON_OUTPUT_CSC_YCBCR709 = 3,
}RADEON_OUTPUT_CSC;

typedef struct _RADEON_ENCODER{
    DrsdEncoder BaseEncoder;
    uint32_t EncoderEnumeration;
    uint32_t EncoderId;
    uint32_t Devices;
    uint32_t ActivatDevice;
    uint32_t Flags;
    uint32_t PixelCLock;
    RADEON_RMX_TYPE RmxType;
    RADEON_UNDERSCAN_TYPE UnderscanType;
    uint32_t UnderScanHorizontal;
    uint32_t UnderScanVertical;
    PFrameBufferModeDefinition NativeDisplayMode;
    void* EncPrivate;
    int AudioPollingActive;
    bool IsExtendedEncoder;
    uint16_t Caps;
    PRADEON_AUDIO_HANDLERS Audio;
    RADEON_OUTPUT_CSC OutputCsc;
    bool  CanMst;
    uint32_t Offset;
}RADEON_ENCODER, * PRADEON_ENCODER;

typedef struct _RADEON_DISPLAY_HANDLERS{
    void     (*BandwithUpdate)      (struct _RADEON_DEVICE* RDEV);
    uint32_t (*GetVblankCounter)    (PDrsdCrtc Crtc);
    void     (*WaitForVblank)       (PDrsdDevice Dev);
    void     (*SetBackLightLevel)   (PRADEON_ENCODER Encoder, uint8_t Level);
    uint8_t  (*GetBackLightLevel)   (PRADEON_ENCODER Encoder);
}RADEON_DISPLAY_HANDLERS, * PRADEON_DISPLAY_HANDLERS;


typedef struct _RADEON_ASIC_DRIVER_HANDLER{
    LOUSTATUS (*InitializationHandler)          (struct _RADEON_DEVICE* RDEV);
    void      (*DeInitializationHandler)        (struct _RADEON_DEVICE* RDEV);
    LOUSTATUS (*SuspendHandler)                 (struct _RADEON_DEVICE* RDEV);
    LOUSTATUS (*ResumeHandler)                  (struct _RADEON_DEVICE* RDEV);
    void      (*VgaSetStateHandler)             (struct _RADEON_DEVICE* RDEV, bool  State);
    LOUSTATUS (*AsicResetHandler)               (struct _RADEON_DEVICE* RDEV, bool  HardRest);
    void      (*MmioHdpFlushHandler)            (struct _RADEON_DEVICE* RDEV);
    bool      (*GuiIdleHandler)                 (struct _RADEON_DEVICE* RDEV);
    LOUSTATUS (*McWaitForIdle)                  (struct _RADEON_DEVICE* RDEV);
    LOUSTATUS (*GetAllowedInfoRegister)         (struct _RADEON_DEVICE* RDEV, uint32_t Register, uint32_t* Value);
    RADEON_GART GartHandler;
    RADEON_RING RingsHandler;
    RADOEN_IRQ_STRUCTURE InterruptStructure;
    RADEON_DISPLAY_HANDLERS DisplayHandlers;
    RADEON_COPY_HANDLERS CopyHandlers;
    RADEON_SURFACE_REGISTER Surface;
    HPD_HANDLERS HpdHandlers; 
    RADEON_POWER_MANAGEMENT PowerManagement;
    PFLIP FlipHandlers;
}RADEON_ASIC_DRIVER_HANDLER, * PRADEON_ASIC_DRIVER_HANDLER;

typedef struct _RADEON_SCRATCH_REGISTER{
    uint8_t RegisterCount;
    uintptr_t RegisterBase;
    bool Free[7];
    uintptr_t Register[7];
}RADEON_SCRATCH_REGISTER, * PRADEON_SCRATCH_REGISTER;

typedef struct _RADEON_DEVICE{
    P_PCI_DEVICE_OBJECT PDEV;
    uint32_t RadeonFlags;
    PRADEON_AGP_HEADER AgpHeader;
    bool Shutdown;
    uint8_t Family;
    bool AtomBios;
    uint64_t MsTimeout;
    uint64_t McGttSize;
    bool Acceleration;
    RADEON_RING Rings[NUMBER_OF_RADEON_RINGS];
    uint64_t MaxPfn;
    uint64_t McMask;
    uint64_t RMMIO_BASE;
    uint64_t RMMIO_SIZE;
    uint64_t RIO_MEM;
    uint64_t RIO_MEM_SIZE;
    uint64_t RADEON_VRAM_LIMIT;
    uint64_t GART_SIZE;
    uint64_t RADEON_VM_SIZE;
    uint64_t RADEON_VMBLOCK_SIZE;
    uint64_t RadeonVmMaxPfn;
    uint64_t PllErrAta;
    spinlock_t PllIdxLock;
    spinlock_t McIdxLock;
    spinlock_t PciepIdxLock;
    uint8_t NumberOfCrts;
    bool HasUvd;
    bool HasVce;
    RADEON_ASIC_DRIVER_HANDLER AsicHandlers;
    RADEON_SCRATCH_REGISTER Scratch;
    //uint32_t ReadReg(PRADEON_DEVICE RDEV, uint32_t Register);
    //uint32_t WriteReg(PRADEON_DEVICE RDEV, unit32_t Refister, uint32_t Value);
    uint32_t PcieRegisterMask;
    uint32_t (*McReadRegister)(_RADEON_DEVICE*, uint32_t);
    void (*McWriteRegister)(_RADEON_DEVICE*,uint32_t,uint32_t);
    uint32_t (*PllReadRegister)(_RADEON_DEVICE*, uint32_t);
    void (*PllWriteRegister)(_RADEON_DEVICE*,uint32_t,uint32_t);
    uint32_t (*PciepReadRegister)(_RADEON_DEVICE*, uint32_t);
    void (*PciepWriteRegister)(_RADEON_DEVICE*,uint32_t,uint32_t);
}RADEON_DEVICE, * PRADEON_DEVICE;

#define RADEON_MAX_TIMEOUT_MS 100

#define RADEON_CLOCK_CONTROL_DATA  0x000C
#define RADEON_CLOCK_CONTROL_INDEX 0x0008
#       define RADEON_PLL_WR_EN (1 << 7)
#       define RADEON_PLL_DIV_SEL (3 << 8)
#       define RADEON_PLL2_DIV_SEL_MASK (~(3 << 8))

#define MC_INDEX 0x01F8
#define MC_INDEX_DATA 0x1FC

#define WREG8(Register, V) WRITE_REGISTER_UCHAR((PUCHAR)(RDEV->RMMIO_BASE) + Register, V)
#define RREG32(Register)   READ_REGISTER_ULONG((PULONG)(RDEV->RMMIO_BASE + Register))
#define WREG32(Register, V)   WRITE_REGISTER_ULONG((PULONG)(RDEV->RMMIO_BASE + Register), V)
#define RRE8(Register) READ_REGISTER_UCHAR((PUCHAR)(RDEV->RMMIO_BASE + Register))
#define WRE8(Register, Value) WRITE_REGISTER_UCHAR((PUCHAR)(RDEV->RMMIO_BASE + Register), Value)


#define CHIP_ERRATA_PLL_DUMMYREADS 1
#define CHIP_ERRATA_PLL_DELAY     (1 << 1)
#define CHIP_ERRATA_R300_CG       (1 << 2)


#define RADEON_CRTC_GEN_CONTROL 0x0050
#define RADEON_SCRATCH_REGISTER0 0x15E0
#define RADEON_GEM_MAX_SURFACES 8
#define RADEON_SURFACE_CONTROL 0x0B00
#define RADEON_CP_CSQ_CONTROL 0x0740
#define RADEON_CP_RB_CONTROL 0x0704
#define RADEON_SCRATCH_UMSK 0x0770
#define RADEON_CONFIG_MEMSIZE 0x00f8
#define R600_CONFIG_MEMSIZE 0x5428

#define ASIC_IS_NODCE(RDEV) (RDEV->Family == CHIP_HAINAN)
#define ASIC_IS_DCE4(RDEV) (RDEV->Family >= CHIP_CEDAR)
#define ASIC_IS_AVIVO(RDEV) (RDEV->Family >= CHIP_RS600)

#define RADEON_CLEAR_SURFACE_REGISTER(RDEV, Register) ((RDEV)->AsicHandlers.Surface.ClearRegister(RDEV, Register))

#endif