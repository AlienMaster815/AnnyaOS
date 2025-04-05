#ifndef _EHCI_H
#define _EHCI_H

#include <usb.h>

typedef struct _USB_HR_TIMER{
    void* Foo;
}USB_HR_TIMER, * PUSB_HR_TIMER;

typedef struct _EHCI_CAPABILITIES{
    uint32_t HcCapBase;
    uint32_t HcsParameters;
    uint32_t HccParameters;
    uint8_t  PortRouting[8];
}EHCI_CAPABILITIES, * PEHCI_CAPABILITIES;

typedef struct __attribute__((aligned(32))) _EHCI_HARDWARE_QH{
    uint32_t        NextHardware;
    uint32_t        HardwareInfo;
    uint32_t        HardwareInfoExtention;
    uint32_t        CurrentHardware;
    uint32_t        HardwareNextQTD;
    uint32_t        HardwareNextALT;
    uint32_t        HardwareToken;
    uint32_t        HardwareBuffer[5];
    uint32_t        HardwareBufferHigh[5];
}EHCI_HARDWARE_QH, * PEHCI_HARDWARE_QH;

typedef struct _EHCI_QH{
    PEHCI_HARDWARE_QH   Hardware;
}EHCI_QH, * PEHCI_QH;

typedef struct _EHCI_REGISTERS{
    uint32_t                HcCommand;
    uint32_t                HcStatus;
    uint32_t                HcInterruptEnable;
    uint32_t                HcFrameIndex;
    uint32_t                HcSegment;
    uint32_t                HcFrameList;
    uint32_t                HcAsyncNext;
    uint32_t                HcReserved1[2];
    uint32_t                HcTxFillTuning;
    uint32_t                HcReserved2[6];
    uint32_t                HcConfiguredFlags;
    union{
        uint32_t            HcPortStatus[15];
        struct{
            uint32_t        Reserved3[9];
            uint32_t        UsbMode;                      
        };
    };
    union{
        struct {
            uint32_t        Reserved4;
            uint32_t        HostPc[15];
        };
        uint32_t            BrcmInsnReg;
    };
    uint32_t                Reserved5[2];
    uint32_t                UsbExtended;
}EHCI_REGISTERS, * PEHCI_REGISTERS;

typedef struct _EHCI_HOST_CONTROLLER_DRIVER{
    uint8_t                 EhciHrTimerEvent;
    uint64_t                HrTimerEventsEnabled;
    size_t                  HrTimeouts[13];
    USB_HR_TIMER            HrTimer;
    size_t                  PeriodicCpuSpin;
    size_t                  AsyncCpuSpin;
    size_t                  DeathCpuSpin;
    PEHCI_CAPABILITIES      HostCapabilities;
    PEHCI_REGISTERS         HostRegisters;
    void*                   DebugPort;
    uint32_t                HcsParameters;
    spinlock_t              HcLock;
    uint8_t                 RhState;
    uint8_t                 Flags1;
    PEHCI_QH                QhList;
}EHCI_HOST_CONTROLLER_DRIVER, * PEHCI_HOST_CONTROLLER_DRIVER;

#define ECHI_DRIVER_SCANNING(Ehci)              (((PEHCI_HOST_CONTROLLER_DRIVER)Ehci)->Flags1 & 1)
#define ECHI_DRIVER_NEEDS_RESCAN(Ehci)          (((PEHCI_HOST_CONTROLLER_DRIVER)Ehci)->Flags1 & (1 << 1))
#define ECHI_DRIVER_INTERRUPT_UNLINKING(Ehci)   (((PEHCI_HOST_CONTROLLER_DRIVER)Ehci)->Flags1 & (1 << 2))
#define EHCI_DRIVER_IAA_IN_PROGRESS(Ehci)       (((PEHCI_HOST_CONTROLLER_DRIVER)Ehci)->Flags1 & (1 << 3))
#define EHCI_DRIVER_ASYNC_UNLINKING(Ehci)       (((PEHCI_HOST_CONTROLLER_DRIVER)Ehci)->Flags1 & (1 << 4))
#define EHCI_DRIVER_SHUTDOWN(Ehci)              (((PEHCI_HOST_CONTROLLER_DRIVER)Ehci)->Flags1 & (1 << 5))

#endif