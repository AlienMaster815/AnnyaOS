#define _KERNEL_MODULE_
#ifndef _XHCI_H
#define _XHCI_H
#include <LouDDK.h>
#include "XhciExtCap.h"
#include "XhciPorts.h"
#include "XhciCap.h"

#define XHCI_MAX_DISPATCHES         500
#define XHCI_SBRN_OFFSET            0x60
#define XHCI_MAX_HC_SLOTS           256
#define XHCI_MAX_HC_PORTS           127

#define XHCI_REGISTER_PER_PORT      4
#define XHCI_SC_PORT                0
#define XHCI_PMSC_PORT              1
#define XHCI_LI_PORT                2
#define XHCI_HLPMC_PORT             3

#define XHCI_COMMAND_RESET          (1 << 1)
#define XHCI_COMMAND_LRESET         (1 << 7)
#define XHCI_COMMAND_CSS            (1 << 8)
#define XHCI_COMMAND_CRS            (1 << 9)
#define XHCI_COMMAND_PM_INDEX       (1 << 11)
#define XHCI_COMMAND_ETE            (1 << 14)

#define XHCI_RESET_LONG_TIMEOUT     (10 * 1000)
#define XHCI_RESET_SHORT_TIMEOUT    (250)

#define XHCI_STATUS_FATAL           (1 << 2)
#define XHCI_STATUS_EINT            (1 << 3)
#define XHCI_STATUS_PORT_CHANGE     (1 << 4)
#define XHCI_STATUS_SAVE            (1 << 8)
#define XHCI_STATUS_RESTORE         (1 << 9)
#define XHCI_STATUS_SRE             (1 << 10)
#define XHCI_STATUS_HCE             (1 << 12)

#define XHCI_DEVICE_NOTE_MASK       (0xFFFF)
#define XHCI_DEVICE_NOTE_WAKE       (1 << 1)

#define XHCI_DEVRNG_CYCLE           (1)
#define XHCI_DEVRNG_PAUSE           (1 << 1)
#define XHCI_DEVRNG_ABORT           (1 << 2)
#define XHCI_DEVRNG_RUNNING         (1 << 3)
#define XHCI_DEVRNG_POINTER_MASK    (0xFFFFFFFFFFFFFFD0)

#define XHCI_MAX_DEVICES(Port)      ((Port) & 0xFF)
#define XHCI_CONFIG_U3E             (1 << 8)
#define XHCI_CONFIG_CIE             (1 << 9)
#define XHCI_PAGE_SIZE_MASK         (0xFFFF)

#define XHCI_IMAN_IP                (1)
#define XHCI_IMAN_IE                (1 << 1)
#define XHCI_IMODI_MASK             (0xFFFF)
#define XHCI_IMODC_MASK             (0xFFFF << 16)

#define XHCI_ERST_SIZE_MASK         (0xFFFF)

#define XHCI_ERST_BASE_ADDRESS_MASK XHCI_DEVRNG_POINTER_MASK



//266

typedef struct _XHCI_CAPABILITIES_REGISTER{
    UINT32      HcCapBase;
    UINT32      HcsParameter1;
    UINT32      HcsParameter2;
    UINT32      HcsParameter3;
    UINT32      HccParameter;
    UINT32      DoorbellOffset;
    UINT32      RuntimeRegisterOffset;
    UINT32      HccParameter2;   
}XHCI_CAPABILITIES_REGISTER, * PXHCI_CAPABILITIES_REGISTER;

typedef struct _XHCI_OPERATIONAL_PORT{
    UINT32      StatusBase;
    UINT32      PowerPortBase;
    UINT32      PortLinkBase;
    UINT32      Reserved;
}XHCI_OPERATIONAL_PORT, * PXHCI_OPERATIONAL_PORT;

typedef struct _XHCI_OPERATIONAL_REGISTER{
    UINT32                  Command;
    UINT32                  Status;
    UINT32                  PageSize;
    UINT32                  Reserved1;
    UINT32                  Reserved2;
    UINT32                  DeviceNotification;
    UINT64                  CommandRing;
    UINT32                  Reserved3[4];
    UINT64                  DCBAAPointer;
    UINT32                  CongiurationRegister;
    UINT32                  Reserved4[241];
    XHCI_OPERATIONAL_PORT   Ports[255]; 
}XHCI_OPERATIONAL_REGISTER, * PXHCI_OPERATIONAL_REGISTER;

typedef struct _XHCI_INTERRUPT_REGISTER{
    UINT32          Man;
    UINT32          Mod;
    UINT32          ERstSize;
    UINT32          Reserved;
    UINT64          ErstBase;
    UINT64          ErstDeQueue;
}XHCI_INTERRUPT_REGISTER, * PXHCI_INTERRUPT_REGISTER;



#endif