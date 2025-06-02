#ifndef _NETFRAME_H
#define _NETFRAME_H

#ifndef __cplusplus
#include <LouAPI.h>
#else 
#include <LouDDK.h>
extern "C"{
#endif

typedef struct _LOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER{
    P_PCI_DEVICE_OBJECT     PDEV;
    #ifdef __cplusplus
    PDRIVER_OBJECT          DriverObject;
    PDEVICE_OBJECT          PlatformDevice;
    #else
    void*                   DriverObject;
    void*                   PlatformDevice;
    #endif
    uint8_t                 MacAddress[6];
    void*                   DriverPrivateData;
    LOUSTATUS               (*HardwareInitialize)(struct _LOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER* DriverData);
    void                    (*HardwareSetAddress)(struct _LOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER* DriverData);
    void                    (*HardwareActivate)(struct _LOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER* DriverData);
    LOUSTATUS               (*HardwareReset)(struct _LOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER* DriverData);
    void                    (*HardwareInterruptHandler)(uint64_t DriverData);
}LOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER, * PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER;


#ifndef _KERNEL_MODULE_

LOUSTATUS LoukeRegisterNetFrameHardwareDriver(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver
);

#else

KERNEL_EXPORT LOUSTATUS LoukeRegisterNetFrameHardwareDriver(
    PLOUSINE_KERNEL_NETFRAME_HARDWARE_DRIVER HardwareDriver
);

#endif

#ifdef __cplusplus
}
#endif
#endif