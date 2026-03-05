#ifndef _KERNEL_FIRMWARE_H
#define _KERNEL_FIRMWARE_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

#include "../Firmware/Efi.h"

#define DEVICE_DMA_NOT_SUPPORTED    0
#define DEVICE_DMA_NON_COHERENT     1
#define DEVICE_DMA_COHERENT         2

#define FIRMWARE_NODE_FLAG_LINKS_ADDRESS        1
#define FIRMWARE_NODE_FLAG_NOT_DEVICE                   (1 << 1)
#define FIRMWARE_NODE_FLAG_INITIALIZED                  (1 << 2)
#define FIRMWARE_NODE_FLAG_NEEDS_CHILD_BOUND_ON_ADD     (1 << 3)
#define FIRMWARE_NODE_FLAG_BEST_EFFORT                  (1 << 4)
#define FIRMWARE_NODE_FLAG_VISITED                      (1 << 5)

typedef struct _FIRMWARE_NODE_HANDLE{
    struct _FIRMWARE_NODE_HANDLE*       Secondary;
    struct _FIRMWARE_NODE_OPERATIONS*   NodeOperations;
    PVOID                               PlatformDevice;
    ListHeader                          Suppliers;
    ListHeader                          Consumers;
    UINT8                               Flags;
}FIRMWARE_NODE_HANDLE, * PFIRMWARE_NODE_HANDLE;

typedef struct _FIRMWARE_NODE_REFERENCE_ARGUMENTS{
    PFIRMWARE_NODE_HANDLE       NodeHandle;
    UINT32                      NArgs;
    UINT64                      Arguments[16];
}FIRMWARE_NODE_REFERENCE_ARGUMENTS, * PFIRMWARE_NODE_REFERENCE_ARGUMENTS;

typedef struct _FIRMWARE_NODE_OPERATIONS{
    PFIRMWARE_NODE_HANDLE   (*GetFirmwareReference)(PFIRMWARE_NODE_HANDLE NodeHandle);
    void                    (*PutFirmwareReference)(PFIRMWARE_NODE_HANDLE NodeHandle);
    BOOL                    (*CheckDeviceAvailability)(PFIRMWARE_NODE_HANDLE NodeHandle);
    PVOID                   (*DeviceGetMatchData)(PFIRMWARE_NODE_HANDLE NodeHandle, PVOID PlatformDevice);
    BOOL                    (*DeviceHasDma)(PFIRMWARE_NODE_HANDLE NodeHandle);
    UINT32                  (*GetDeviceDmaAttributes)(PFIRMWARE_NODE_HANDLE NodeHandle);
    BOOL                    (*IsPropertyPresent)(PFIRMWARE_NODE_HANDLE NodeHandle, string PropertyName);
    BOOL                    (*PropertyReadBool)(PFIRMWARE_NODE_HANDLE NodeHandle, string PropertyName);
    LOUSTATUS               (*PropertyReadIntegerArray)(PFIRMWARE_NODE_HANDLE NodeHandle, string PropertyName, UINT32 ElementCount, PVOID Value, SIZE Values);
    LOUSTATUS               (*PropertyReadStringArray)(PFIRMWARE_NODE_HANDLE NodeHandle, string PropertyName, string* Value, SIZE Values);
    string                  (*NodeGetName)(PFIRMWARE_NODE_HANDLE NodeHandle);
    string                  (*NodeGetNamePrefix)(PFIRMWARE_NODE_HANDLE NodeHandle);
    PFIRMWARE_NODE_HANDLE   (*GetParentNode)(PFIRMWARE_NODE_HANDLE NodeHandle);
    PFIRMWARE_NODE_HANDLE   (*GetNextChildNode)(PFIRMWARE_NODE_HANDLE NodeHandle, PFIRMWARE_NODE_HANDLE ChildHandle);
    PFIRMWARE_NODE_HANDLE   (*GetNamedChildNode)(PFIRMWARE_NODE_HANDLE NodeHandle, string Name);
    LOUSTATUS               (*GetReferenceArguments)(PFIRMWARE_NODE_HANDLE NodeHandle, string Properties, string NArgumentProperty, UINT32 NArgs, UINT32 Index, PFIRMWARE_NODE_REFERENCE_ARGUMENTS Arguments);
    PFIRMWARE_NODE_HANDLE   (*GraphGetNextEndpoint)(PFIRMWARE_NODE_HANDLE NodeHandle, PFIRMWARE_NODE_HANDLE Previous);
    PFIRMWARE_NODE_HANDLE   (*GraphGetRemoteEndpoint)(PFIRMWARE_NODE_HANDLE NodeHandle);
    PFIRMWARE_NODE_HANDLE   (*GraphGetPortParent)(PFIRMWARE_NODE_HANDLE NodeHandle);
    LOUSTATUS               (*GraphParseEndpoint)(PFIRMWARE_NODE_HANDLE NodeHandle, PFIRMWARE_NODE_HANDLE Endpoint);
    PVOID                   (*IoMap)(PFIRMWARE_NODE_HANDLE NodeHAndle, INTEGER Index);
    INTEGER                 (*NodeGetIrq)(PFIRMWARE_NODE_HANDLE Node, UINT32 INdex);
    LOUSTATUS               (*NodeAddLink)(PFIRMWARE_NODE_HANDLE Node);
}FIRMWARE_NODE_OPERATIONS, * PFIRMWARE_NODE_OPERATIONS;

#ifdef __cplusplus
}
#endif
#endif
