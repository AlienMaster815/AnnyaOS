#ifndef _USB_H
#define _USB_H
#include <LouDDK.h>

#pragma pack(push, 1)
typedef struct _USB_SELF{
    bool IsRootHub;
}USB_SELF, * PUSB_SELF;

typedef enum {
    PHY_MODE_USB_HOST_SS = 0,
}PHY_MODE;

typedef struct _PHY_OPERATIONS{
    LOUSTATUS (*SetMode)(struct _PHY_LINK* Phy, PHY_MODE Mode, int SubMode);
}PHY_OPERATIONS, * PPHY_OPERATIONS;

typedef struct _PHY_LINK{
    PHY_OPERATIONS Operations;
}PHY_LINK, * PPHY_LINK;

typedef struct _PHY_ROOT_HUB{
    ListHeader PhyList;
    PPHY_LINK Phy;
}PHY_ROOT_HUB, * PPHY_ROOT_HUB;

typedef struct _HCD_DEVICE{
    P_PCI_DEVICE_OBJECT PDEV;
    bool AmdResumeBug;
    uint8_t IrqVector;
    uintptr_t ResourceStart;
    size_t    ResourceSize;
    mutex_t   CompanionSemaphoreLock;
    USB_SELF Self;
    bool SkipPhyInit;
    bool IsPrimaryHcd;
    uint32_t NumberOfPhys;
    PPHY_ROOT_HUB PhyRootHub;

    uint32_t (*LouKeHalHcdGetPhyNumber)(struct _HCD_DEVICE*);

}HCD_DEVICE, * PHCD_DEVICE;

#define LouKeHalUsbGetPhyNumber(x) Hcd->LouKeHalHcdGetPhyNumber((PHCD_DEVICE)x);

#define PHY_MODE_HOST_SS 1

#pragma pack(pop)
#endif