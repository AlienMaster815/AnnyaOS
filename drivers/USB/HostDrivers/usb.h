#ifndef _USB_H
#define _USB_H

#include <LouDDK.h>

typedef struct _LOUSB_HCD_OPERATIONS{
    LOUSTATUS (*ChangeOwnership)(struct _LOUSB_HCD* Hcd);
    LOUSTATUS (*ResetHcd)(struct _LOUSB_HCD* Hcd);
}LOUSB_HCD_OPERATIONS, * PLOUSB_HCD_OPERATIONS;

typedef struct _LOUSB_HCD{
    ListHeader              Siblings;
    P_PCI_DEVICE_OBJECT     PDEV;
    int                     HcdPollTimer;
    uint8_t                 Revision;
    void*                   PrivateData;
    void*                   PhyLayer;
    void*                   Context;
    PLOUSB_HCD_OPERATIONS   HcdOperations;
    spinlock_t              HcdLock;
    bool                    KernelIsOwner;
    uint32_t                LousbFlags;
    uint32_t                CLousbFlags;
}LOUSB_HCD, * PLOUSB_HCD;

PLOUSB_HCD LouKeMallocLousbHcd(size_t SiblingCount, size_t PrivateDataSize, size_t PrivateDataAlignment);

#endif