#define _KERNEL_MODULE_
#ifndef _OHCI_H
#define _OHCI_H

#include <LouDDK.h>
#include <Hal.h>
#include <usb.h>


typedef struct _OHCI_ED_INITIALIZOR{
    UINT8       FunctionAddress;
    UINT8       EndpointNumber      :   4;
    UINT8       Direction           :   2;
    UINT8       Speed               :   1;
    UINT8       Skip                :   1;
    UINT8       Format              :   1;
    UINT8       Halted              :   1;
    UINT8       ToggleCarry         :   1;
    UINT16      MaximumPacketSize   :   11;
    UINT32      TDQueueTailPointer;
    UINT32      TDQueueHeadPointer;
    UINT32      NextED;
}OHCI_ED_INITIALIZOR, * POHCI_ED_INITIALIZOR;

typedef struct PACKED FORCE_ALIGNMENT(16) _OHCI_ENDPOINT_DESCRIPTOR{
    UINT32      Dword0;
    UINT32      Dword1;
    UINT32      Dword2;
    UINT32      Dword3;
}OHCI_ENDPOINT_DESCRIPTOR, * POHCI_ENDPOINT_DESCRIPTOR;

typedef struct _OHCI_TD_INITIALIZOR{
    UINT8       BufferRounding;         :   1;      //R
    UINT8       DirectionPID            :   2;      //DP
    UINT8       DelayInterrupt          :   3;      //DI
    UINT8       DataToggle              :   2;      //T
    UINT8       ErrorCount              :   2;      //EC
    UINT8       ConditionCode           :   4;      //CC
    UINT32      CurrentBufferPointer;               //CBP
    UINT32      NextTD;                             //NextTD
    UINT32      BufferEnd;                          //BE
}OHCI_TD_INITIALIZOR, * POHCI_TD_INITIALIZOR;

typedef struct PACKED FORCE_ALIGNMENT(16) _OHCI_TRANSFER_DESCRIPTOR{
    UINT32      Dword0;
    UINT32      Dword1;
    UINT32      Dword2;
    UINT32      Dword3;
}OHCI_TRANSFER_DESCRIPTOR, * POHCI_TRANSFER_DESCRIPTOR;

typedef struct _OHCI_TD_LIST{
    ListHeader                  Peers;
    PVOID                       Td;
}OHCI_TD_LIST, * POHCI_TD_LIST;

typedef struct _OHCI_ED_LIST{
    ListHeader                  Peers;
    PVOID                       Ed;
    OHCI_TD_LIST                Tds;
}OHCI_ED_LIST, * POHCI_ED_LIST;


typedef struct PACKED _OHCI_HCCA{
    UINT32      InterruptTable[32];
    UINT16      HccaFrameNumber;
    UINT16      HccaPad1;
    UINT32      HccaDoneHead;
}OHCI_HCCA, * POHCI_HCCA;

typedef struct PACKED _OHCI_OPERATIONAL_REGISTERS{
    UINT32      HcRevision;
    UINT32      HcControl;
    UINT32      HcCommandStatus;
    UINT32      HcInterruptStatus;
    UINT32      HcInterruptEnable;
    UINT32      HcInterruptDisable;
    UINT32      HcHCCA;
    UINT32      HcPeriodCurrentED;
    UINT32      HcControlHeadED;
    UINT32      HcControlCurrentED;
    UINT32      HcBulkHeadED;
    UINT32      HcBulkCurrentED;
    UINT32      HcDoneHead;
    UINT32      HcFmInterval;
    UINT32      HcFmRemaining;
    UINT32      HcPeriodicStart;
    UINT32      HcLSThreshold;
    UINT32      HcRhDescriptorA;
    UINT32      HcRhDescriptorB;
    UINT32      HcRhStatus;
    UINT32      HcRhPortStatus[];
}OHCI_OPERATIONAL_REGISTERS, * POHCI_OPERATIONAL_REGISTERS;

typedef enum {
    ControlEndpoint = 0,
    BulkEndpoint = 1,
    InterruptEndpoint = 2,
    IsochEndpoint = 3, 
}OHCI_ED_TYPE;

typedef struct _OHCI_PORT{
    struct _OHCI_DEVICE*            Host;
    bool                            PortAttatched;
    bool                            PortEnabled;
    bool                            LowSpeed;
}OHCI_PORT, * POHCI_PORT;

typedef struct _OHCI_DEVICE{
    PPCI_DEVICE_OBJECT              PDEV;
    USB_HOST_DEVICE                 UsbHost;
    POHCI_OPERATIONAL_REGISTERS     OperationalRegisters;
    spinlock_t                      IoLock;
    mutex_t                         DeviceMutex;
    UINT64                          HccaAddress;
    UINT32                          Fminterval;
    OHCI_ED_LIST                    ControlEDs;
    OHCI_ED_LIST                    BulkEDs;
    OHCI_ED_LIST                    IsochIntEDs[32];
}OHCI_DEVICE, * POHCI_DEVICE;

typedef struct _OHCI_IO_PACKET_PRIVATE_DATA{
    POHCI_ED_LIST   EdItem;
}OHCI_IO_PACKET_PRIVATE_DATA, * POHCI_IO_PACKET_PRIVATE_DATA;

#define OHCI_REVISION_HC_BIT     (0x01)
#define OHCI_REVISION_HCD_BIT    (0x02)

#define GET_OHCI_REVISION_HC(Revision)       (Revision & OHCI_REVISION_HC_BIT)
#define GET_OHCI_REVISION_HCD(Revision)      ((Revision & OHCI_REVISION_HCD_BIT) >> 1)
#define SET_OHCI_REVISION_HC(Revision, Ena)  (Revision = (Revision & ~(OHCI_REVISION_HC_BIT) |= (Ena ? OHCI_REVISION_HC_BIT : 0)))
#define SET_OHCI_REVISION_HCD(Revision, Ena) (Revision = (Revision & ~(OHCI_REVISION_HCD_BIT) |= (Ena ? OHCI_REVISION_HCD_BIT : 0)))

#define OHCI_CONTROL_CBSR_MASK 0x03
#define OHCI_CONTROL_HCFS_MASK OHCI_CONTROL_CBSR_MASK

#define OHCI_CONTROL_CBSR_BITS  (0)
#define OHCI_CONTROL_PLE_BIT    (2)
#define OHCI_CONTROL_IE_BIT     (3)
#define OHCI_CONTROL_CLE_BIT    (4)
#define OHCI_CONTROL_BLE_BIT    (5)
#define OHCI_CONTROL_HCFS_BITS  (6)
#define OHCI_CONTROL_IR_BIT     (8)
#define OHCI_CONTROL_RWC_BIT    (9)
#define OHCI_CONTROL_RWE_BIT    (10)

#define OHCI_CONTROL_CBSR       (OHCI_CONTROL_CBSR_MASK << OHCI_CONTROL_CBSR_BITS)
#define OHCI_CONTROL_HCFS       (OHCI_CONTROL_HCFS_MASK << OHCI_CONTROL_HCFS_BITS)

#define OHCI_CONTROL_PLE        (1 << OHCI_CONTROL_PLE_BIT)
#define OHCI_CONTROL_IE         (1 << OHCI_CONTROL_IE_BIT)
#define OHCI_CONTROL_CLE        (1 << OHCI_CONTROL_CLE_BIT)
#define OHCI_CONTROL_BLE        (1 << OHCI_CONTROL_BLE_BIT)
#define OHCI_CONTROL_IR         (1 << OHCI_CONTROL_IR_BIT)
#define OHCI_CONTROL_RWC        (1 << OHCI_CONTROL_RWC_BIT)
#define OHCI_CONTROL_RWE        (1 << OHCI_CONTROL_RWE_BIT)



#define GET_OHCI_CONTROL_CSBR(Control)  (Control & OHCI_CONTROL_CBSR_MASK)
#define GET_OHCI_CONTROL_PLE(Control)   ((Control >> OHCI_CONTROL_PLE_BIT) & 0x01)
#define GET_OHCI_CONTROL_IE(Control)    ((COntrol >> OHCI_CONTROL_IE_BIT) & 0x01)
#define GET_OHCI_CONTROL_CLE(Control)   ((Control >> OHCI_CONTROL_CLE_BIT) & 0x01)
#define GET_OHCI_CONTROL_BLE(Control)   ((Control >> OHCI_CONTROL_BLE_BIT) & 0x01)
#define GET_OHCI_CONTROL_HCFS(Control)  ((Control >> OHCI_CONTROL_HCFS_BITS) & OHCI_CONTROL_HCFS_MASK)
#define GET_OHCI_CONTROL_IR(Control)    ((Control >> OHCI_CONTROL_IR_BIT) & 0x01)
#define GET_OHCI_CONTROL_RWC(Control)   ((Control >> OHCI_CONTROL_RWC_BIT) & 0x01)
#define GET_OHCI_CONTROL_RWE(Control)   ((Control >> OHCI_CONTROL_RWE_BIT) & 0x01)

#define SET_OHCI_CONTROL_CSBR(Control, x)   (Control = ((Control & ~(OHCI_CONTROL_CBSR_MASK)) |= (x & OHCI_CONTROL_CBSR_MASK)))
#define SET_OHCI_CONTROL_PLE(Control, x)    (Control = ((Control & ~(1 << OHCI_CONTROL_PLE_BIT)) |= ((x & 0x01) << OHCI_CONTROL_PLE_BIT)))
#define SET_OHCI_CONTROL_IE(Control, x)     (Control = ((Control & ~(1 << OHCI_CONTROL_IE_BIT)) |= ((x & 0x01) << OHCI_CONTROL_IE_BIT)))
#define SET_OHCI_CONTROL_CLE(Control, x)    (Control = ((Control & ~(1 << OHCI_CONTROL_CLE_BIT)) |= ((x & 0x01) << OHCI_CONTROL_CLE_BIT)))
#define SET_OHCI_COTROL_BLE(Control, x)     (Control = ((Control & ~(1 << OHCI_CONTROL_BLE_BIT)) |= ((x & 0x01) << OHCI_CONTROL_BLE_BIT)))
static inline UINT32 SET_OHCI_COTROL_HCFS(UINT32 Control, UINT32 Mod){
    Control = Control & ~(OHCI_CONTROL_HCFS_MASK << OHCI_CONTROL_HCFS_BITS);
    Control |= ((Mod & OHCI_CONTROL_HCFS_MASK) << OHCI_CONTROL_HCFS_BITS);
    return Control;
}
#define SET_OHCI_COTROL_IR(Control, x)      (Control = ((Control & ~(1 << OHCI_CONTROL_IR_BIT)) |= ((x & 0x01) << OHCI_CONTROL_IR_BIT)))
#define SET_OHCI_COTROL_WRC(Control, x)     (Control = ((Control & ~(1 << OHCI_CONTROL_WRC_BIT)) |= ((x & 0x01) << OHCI_CONTROL_WRC_BIT)))
#define SET_OHCI_COTROL_WRE(Control, x)     (Control = ((Control & ~(1 << OHCI_CONTROL_WRE_BIT)) |= ((x & 0x01) << OHCI_CONTROL_WRE_BIT)))

//CBSR ControlBulkServiceRatio
#define RESET_CBSR_VALUE            0b00
//No. Control ED's Over Bulk ED's Served
#define OHCI_CBSR_1_1               0b00
#define OHCI_CBSR_2_1               0b01
#define OHCI_CBSR_3_1               0b10
#define OHCI_CBSR_4_1               0b11

//set to enable and unset to disable periodic list processing
#define OHCI_PLE_ENABLE             1
#define OHCI_PLE_DISABLE            0

//Set To Enable Unset To disable isoch list processing
#define OHCI_IE_ENABLE              1
#define OHCI_IE_DISABLE             0

//set to Enable Unset To disable control list processing
#define OHCI_CLE_ENABLE             1
#define OHCI_CLE_DISABLE            0

//set to Enable Unset To disable Bulk list processing
#define OHCI_BLE_ENABLE             1
#define OHCI_BLE_DISABLE            0

//HostControlFunctionalState
#define OHCI_HCFS_USBRESET          0b00
#define OHCI_HCFS_USBRESUME         0b01
#define OHCI_HCFS_USBOPERATIONAL    0b10
#define OHCI_HCFS_USBSUSPEND        0b11

//interrupt rounting
#define OHCI_IR_HOSTBUS             0
#define OHCI_IR_SMILINE             1

//remote wakeup connected
#define OHCI_RWC_ENABLE             1
#define OHCI_RWC_DISABLE            0

//Remote Wakeup Enable
#define OHCI_RWE_ENABLE             1
#define OHCI_REW_DISABLE            0

#define OHCI_OPERATIONAL_REGISTER_BAR       0
#define OHCI_OPERATIONAL_REGISTER_OFFSET    0

#define OHCI_COMMAND_STATUS_HCR     (1)
#define OHCI_COMMAND_STATUS_CLF     (1 << 1)
#define OHCI_COMMAND_STATUS_BLF     (1 << 2)
#define OHCI_COMMAND_STATUS_OCR     (1 << 3)
#define OHCI_COMMAND_STATUS_SOC     (0b11 << 16)

//endpoint descritor data 
#define OHCI_ED_FA_MASK         ((1 << 7) - 1)
#define OHCI_ED_EN_MASK         ((1 << 5) - 1)
#define OHCI_ED_D_MASK          ((1 << 3) - 1)
#define OHCI_ED_S_MASK          (1)
#define OHCI_ED_K_MASK          (1)
#define OHCI_ED_F_MASK          (1)
#define OHCI_ED_MPS_MASK        ((1 << 12) - 1)

#define OHCI_ED_TAILP_MASK      (0xFFFFFFF0)
#define OHCI_ED_H_MASK          (1)
#define OHCI_ED_C_MASK          (1)
#define OHCI_ED_HEADP_MASK      (0xFFFFFFF0)
#define OHCI_ED_NEXTED_MASK     (0xFFFFFFF0)

#define OHCI_ED_FA_SHIFT        (0)
#define OHCI_ED_EN_SHIFT        (7)
#define OHCI_ED_D_SHIFT         (11)
#define OHCI_ED_S_SHIFT         (13)
#define OHCI_ED_K_SHIFT         (14)
#define OHCI_ED_F_SHIFT         (15)
#define OHCI_ED_MPS_SHIFT       (16)
#define OHCI_ED_TAILP_SHIFT     (4)
#define OHCI_ED_H_SHIFT         (0)
#define OHCI_ED_C_SHIFT         (1)
#define OHCI_ED_HEADP_SHIFT     (4)
#define OHCI_ED_NEXTED_SHIFT    (4)

#define OHCI_ED_DIRECTION_GFTD0 0b00
#define OHCI_ED_DIRECTION_OUT   0b01
#define OHCI_ED_DIRECTION_IN    0b10
#define OHCI_ED_DIRECTION_GFTD3 0b11

#define OHCI_ED_SPEED_FULL      0
#define OHCI_ED_SPEED_LOW       1

#define OHCI_ED_SKIP            1

#define OHCI_ED_FORMAT_GENERAL_TD   0
#define OHCI_ED_FORMAT_ISOCH_TD     1

#define OHCI_ED_HALTED          1
#define OHCI_ED_TOGGLE_CARRY    1

#define OHCI_RH_STATUS_LPSC     (1)

#define OHCI_PORT_STATUS_CCS    (1)
#define OHCI_PORT_STATUS_PES    (1 << 1)
#define OHCI_PORT_STATUS_PSS    (1 << 2)
#define OHCI_PORT_STATUS_POCI   (1 << 3)
#define OHCI_PORT_STATUS_PRS    (1 << 4)
#define OHCI_PORT_STATUS_PPS    (1 << 8)
#define OHCI_PORT_STATUS_LSDA   (1 << 9)
#define OHCI_PORT_STATUS_CSC    (1 << 16)
#define OHCI_PORT_STATUS_PESC   (1 << 17)
#define OHCI_PORT_STATUS_PSSC   (1 << 18)
#define OHCI_PORT_STATUS_OCIC   (1 << 19)
#define OHCI_PORT_STATUS_PRSC   (1 << 20)

#define OHCI_TD_DIRECTION_SETUP 0b00
#define OHCI_TD_DIRECTION_OUT   0b01
#define OHCI_TD_DIRECTION_IN    0b10


#define OHCI_TD_R_MASK          0x01
#define OHCI_TD_R_SHIFT         18
#define OHCI_TD_DP_MASK         0x03
#define OHCI_TD_DP_SHIFT        19
#define OHCI_TD_DI_MASK         0x07
#define OHCI_TD_DI_SHIFT        21
#define OHCI_TD_T_MASK          0x03
#define OHCI_TD_T_SHIFT         24
#define OHCI_TD_EC_MASK         0x03
#define OHCI_TD_EC_SHIFT        26
#define OHCI_TD_CC_MASK         0x0F
#define OHCI_TD_CC_SHIFT        28

#define UsbHcdToOhciDevice(HostDevice) CONTAINER_OF(HostDevice, OHCI_DEVICE, UsbHost)

LOUSTATUS 
OhciInitialzeHcca(
    POHCI_DEVICE    OhciDevice
);

LOUSTATUS OhciCreateEndpoint(
    POHCI_DEVICE    OhciDevice,
    UINT8           FunctionAddress,
    UINT8           EndpointNumber,
    UINT8           Direction,
    BOOL            LowSpeed,
    OHCI_ED_TYPE    EdType
);

LOUSTATUS
OhciAllocateDma(
    size_t  Size,
    size_t  Alignment,
    PVOID*  Out
); 

void OhciFreeDma(
    PVOID VAddress
);

UINT32 OhciGetDmaAddress(
    PVOID VAddress
);

LOUSTATUS OhciResetHostController(PUSB_HOST_DEVICE HostDevice);
LOUSTATUS OhciProbeRootHub(PUSB_HOST_DEVICE HostDevice);
LOUSTATUS OhciStopHostController(PUSB_HOST_DEVICE HostDevice);
LOUSTATUS OhciStartHostController(PUSB_HOST_DEVICE HostDevice);
void OhciInterruptHandler(uint64_t UsbHostData);
LOUSTATUS OhciInitializeDefaultControl(POHCI_DEVICE OhciDevice);
LOUSTATUS OhciCreateControlED(POHCI_DEVICE OhciDevice, POHCI_ENDPOINT_DESCRIPTOR* EdOut, POHCI_ED_INITIALIZOR Initializor);
LOUSTATUS OhciCommitRequest(PUSB_HOST_IO_PACKET IoPacket);
#endif