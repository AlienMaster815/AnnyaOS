#ifndef _EXTERNAL_DEVICES_H
#define _EXTERNAL_DEVICES_H

#include "Notifications.h"
#include "Networking/NetFrame.h"

typedef struct _EXTERNALLY_CONNECTED_DEVICE{
    string                                  DeviceName;
    uint32_t*                               CableSupportID;
    uint32_t*                               MutualExclusionID;
    #ifdef __cplusplus
    struct _DEVICE_OBJECT*                          PlatformDevice;    
    #else
    void*                                   PlatformDevice;
    #endif
    uint32_t                                Identification;
    PLOUSINE_KERNEL_RAW_NOTIFICATION_HEAD   AllNotifierHeads;
    PLOUSINE_KERNEL_RAW_NOTIFICATION_HEAD   NotifierHead;
    ListHeader                              Entry;
    int                                     MaxSupport;
    spinlock_t                              ExconLock;
    uint32_t                                State;
    uint32_t                                DeviceTypeIdentifier;
    void*                                   CableData;
    uint64_t                                AttributeGroupFlags;
    void*                                   AttributeData;
    void*                                   DeviceAttributesData;
}EXTERNALLY_CONNECTED_DEVICE, * PEXTERNALLY_CONNECTED_DEVICE;

#endif