#define _KERNEL_MODULE_
#ifndef _OHCI_H
#define _OHCI_H

#include <LouDDK.h>

typedef struct _OHCI_OPERATIONAL_REGISTERS{
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

typedef struct _OHCI_DEVICE{
    PPCI_DEVICE_OBJECT              PDEV;
    POHCI_OPERATIONAL_REGISTERS     OperationalRegisters;
    spinlock_t                      IoLock;
}OHCI_DEVICE, * POHCI_DEVICE;

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
#define SET_OHCI_COTROL_HCFS(Control, x)    (Control = ((Control & ~(OHCI_CONTROL_HCFS_MASK << OHCI_CONTROL_HCFS_BITS)) |= ((x & OHCI_CONTROL_HCFS_MASK) << OHCI_CONTROL_HCFS_BITS)))
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

//command status
//126 || 112

UINT8 OhciGetHcRevision(
    POHCI_DEVICE    OhciDevice
);

void OhciSetHcRevision(
    POHCI_DEVICE    OhciDevice,
    UINT8           Revision
);

void OhciWriteHcControl(
    POHCI_DEVICE    OhciDevice,
    UINT16          Control
);

void OhciWriteHcCommandStatus(
    POHCI_DEVICE    OhciDevice,
    UINT32          CommandStatus
);

UINT32 OhciReadHcCommandStatus(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcInterruptStatus(
    POHCI_DEVICE    OhciDevice,
    UINT32          InterruptStatus
);

UINT32 OhciReadHcInterruptStatus(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcInterruptEnable(
    POHCI_DEVICE    OhciDevice,
    UINT32          InterruptEnable
);

UINT32 OhciReadHcInterruptEnable(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcInterruptDisable(
    POHCI_DEVICE    OhciDevice,
    UINT32          InterruptDisable
);

UINT32 OhciReadHcInterruptDisable(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcHCCA(
    POHCI_DEVICE    OhciDevice,
    UINT32          HCCA
);

UINT32 OhciReadHcHCCA(
    POHCI_DEVICE    OhciDevice
);

UINT32 OhciReadHcPeriodCurrentED(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcPeriodCurrentED(
    POHCI_DEVICE    OhciDevice,
    UINT32          PeriodCurrentED
);

UINT32 OhciReadHcControlHeadED(
    POHCI_DEVICE    OhciDevice
);

void OhciReadHcControlHeadED(
    POHCI_DEVICE    OhciDevice,
    UINT32          ControlHeadED
);

UINT32 OhciReadHcControlCurrentED(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcControlCurrentED(
    POHCI_DEVICE    OhciDevice,
    UINT32          ControlCurrentED
);

UINT32 OhciReadHcBulkHeadED(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcBulkHeadED(
    POHCI_DEVICE    OhciDevice,
    UINT32          BulkHeadED
);

UINT32 OhciReadHcBulkCurrentED(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcBulkCurrentED(
    POHCI_DEVICE    OhciDevice,
    UINT32          BulkCurrentED
);

UINT32 OhciReadDoneHead(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteDoneHead(
    POHCI_DEVICE    OhciDevice,
    UINT32          DoneHead
);

UINT32 OhciReadHcFmInterval(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcFmInterval(
    POHCI_DEVICE    OhciDevice,
    UINT32          HcFmInterval
);

UINT32 OhciReadHcFmRemaining(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcFmRemaining(
    POHCI_DEVICE    OhciDevice,
    UINT32          HcFmRemaining
);

UINT32 OhciReadHcPeriodicStart(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcPeriodicStart(
    POHCI_DEVICE    OhciDevice,
    UINT32          PeriodicStart
);

UINT32 OhciReadHcLSThreashold(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcLSThreashold(
    POHCI_DEVICE    OhciDevice,
    UINT32          LSThreshold
);

UINT32 OhciReadHcRhDescriptorA(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcRhDescriptorA(
    POHCI_DEVICE    OhciDevice,
    UINT32          RhDescriptorA
);

UINT32 OhciReadHcRhDescriptorB(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcRhDescriptorB(
    POHCI_DEVICE    OhciDevice,
    UINT32          RhDescriptorB
);

UINT32 OhciReadHcRhStatus(
    POHCI_DEVICE    OhciDevice
);

void OhciWriteHcRhStatus(
    POHCI_DEVICE    OhciDevice,
    UINT32          RhStatus
);

UINT32 OhciReadHcRhPortStatus(
    POHCI_DEVICE    OhciDevice,
    UINT8           Port
);

void OhciWriteHcRhPortStatus(
    POHCI_DEVICE    OhciDevice,
    UINT8           Port,
    UINT32          RhStatus
);


#endif