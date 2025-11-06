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
    UINT32      HCPeriodCurrentED;
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
    PPCI_DEVICE_OBJECT PDEV;
    POHCI_OPERATIONAL_REGISTERS OperationalRegisters;
    spinlock_t IoLock;
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



#endif