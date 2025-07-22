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

typedef struct _FIRMWARE_NODE_HANDLE{
    struct _FIRMWARE_NODE_HANDLE*       Secondary;
    struct _FIRMWARE_NODE_OPERATIONS*   NodeOperations;
}FIRMWARE_NODE_HANDLE, * PFIRMWARE_NODE_HANDLE;


typedef struct _FIRMWARE_NODE_OPERATIONS{
    PFIRMWARE_NODE_HANDLE   (*GetFirmwareReference)(PFIRMWARE_NODE_HANDLE NodeHandle);
    void                    (*PutFirmwareReference)(PFIRMWARE_NODE_HANDLE NodeHandle);
    BOOL                    (*CheckDeviceAvailability)(PFIRMWARE_NODE_HANDLE NodeHandle);
    PVOID                   (*DeviceGetMatchData)(PFIRMWARE_NODE_HANDLE NodeHandle, PVOID PlatformDevice);
    BOOL                    (*DeviceHasDma)(PFIRMWARE_NODE_HANDLE NodeHandle);
    UINT32                  (*GetDeviceDmaAttributes)(PFIRMWARE_NODE_HANDLE NodeHandle);
    
}FIRMWARE_NODE_OPERATIONS, * PFIRMWARE_NODE_OPERATIONS;

#ifdef __cplusplus
}
#endif
#endif
