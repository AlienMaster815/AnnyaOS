#define _KERNEL_MODULE_
#ifndef _PS2_MOUSE_H
#define _PS2_MOUSE_H
#include <LouDDK.h>

typedef enum {
    PS2_MOUSE = 0x00,
    PS2_SCROLL_MOUSE = 0x03,
    PS2_5BUTTON_MOUSE = 0x04,
    PS2_MF2_KEYBOARD1 = 0xAB83,        
    PS2_MF2_KEYBOARD2 = 0xABC1,
    PS2_SHORTBOARD_KEYBOARD = 0xAB84,
    PS2_NCDN97_KEYBOARD = 0xAB85,
    PS2_122KEY_KEYBOARD = 0xAB86,
    PS2_JP_CLASS_G_KEYBOARD = 0xAB90,
    PS2_JP_CLASS_P_KEYBOARD = 0xAB91,
    PS2_JP_CLASS_A_KEYBOARD = 0xAB92,
    PS2_NCD_SUN_LAYOUT = 0xACA1,
    ANCHIENT_KEYBOARD = 0xFFFE,
    NO_DEVICE = 0xFFFF,
}PS2_DEVICE_CLASS;

typedef struct _PS2_DEVICE_OBJECT{
    PLOU_BUS            BusHandle;
    UINT8               Irq;
    BOOL                DeviceExists;
    BOOL                HasDriver;
    UINT8               PortNumber;
    PS2_DEVICE_CLASS    DeviceClass;
    BOOL                ChipsetDevice;
    PVOID               DriverPrivateData;
}PS2_DEVICE_OBJECT, * PPS2_DEVICE_OBJECT;


#define MOUSE_COMMAND_SET_SCALLING_1_1  0xE6
#define MOUSE_COMMAND_SET_SCALLING_2_1  0xE7
#define MOUSE_COMMAND_SET_RESOLUTION    0xE8
#define MOUSE_RESOLUTION_1_COUNT_MM     0x00
#define MOUSE_RESOLUTION_2_COUNT_MM     0x01
#define MOUSE_RESOLUTION_4_COUNT_MM     0x02
#define MOUSE_RESOLUTION_8_COUNT_MM     0x03
#define MOUSE_COMMAND_STATUS_REQUEST    0xE9
#define MOUSE_COMMAND_SET_STREAM_MODE   0xEA
#define MOUSE_COMMAND_READ_DATA         0xEB
#define MOUSE_COMMAND_RESET_WRAP_MODE   0xEC
#define MOUSE_COMMAND_SET_WRAP_MODE     0xEE
#define MOUSE_COMMAND_SET_REMOTE_MODE   0xF0
#define MOUSE_COMMAND_IDENTIFY_DEVICE   0xF2
#define MOUSE_COMMAND_SET_SAMPLE_RATE   0xF3
#define MOUSE_COMMAND_ENABLE_SCANNING   0xF4
#define MOUSE_COMMAND_DISABLE_SCANNING  0xF5
#define MOUSE_COMMAND_SET_DEFAULTS      0xF6
#define MOUSE_COMMAND_RESEND            0xFE
#define MOUSE_COMMAND_RESET             0xFF

#define MOUSE_ACKNOL    0xFA



typedef struct _PS2_MOUSE_PRIVATE_DATA{
    UINT8                           Scaling;
    UINT8                           Resolution;
    BOOL                            ZAxisEnabled;
    UINT8                           Data[3];
    UINT8                           Offset;
    PLOUSINE_USER_SHARED_MESSAGE    MouseMessage;
    LOUQ_WORK                       MouseWorkQueue;
    PTHREAD                         WorkQueueHandle;
    bool                            Queued;
    INT64                           Dx;
    INT64                           Dy;
    bool                            Rb;
    bool                            Lb;
}PS2_MOUSE_PRIVATE_DATA, * PPS2_MOUSE_PRIVATE_DATA;

DRIVER_IMPORT
void 
LouKeHalPs2InstallInterruptHandler(
    PPS2_DEVICE_OBJECT Device, 
    void(*Handler)(uint64_t)
);


DRIVER_IMPORT
void 
LouKeHalPs2EnableInterrupt(
    PPS2_DEVICE_OBJECT Ps2Device
);


DRIVER_IMPORT
void 
LouKeHalPs2DisableInterrupt(
    PPS2_DEVICE_OBJECT Ps2Device
);

DRIVER_IMPORT
LOUSTATUS
LouKeHalPs2CommandPs2Device(
    PPS2_DEVICE_OBJECT Ps2Device, 
    UINT8*  Input, //req
    SIZE    InSize, //req
    UINT8*  Output, //opt
    SIZE    OutSize //opt
);

DRIVER_IMPORT
LOUSTATUS
LouKeHalPs2FlushBuffer();

DRIVER_IMPORT
LOUSTATUS
LouKeHalPs2ReadDeviceBuffer(
    PPS2_DEVICE_OBJECT Ps2Device, 
    UINT8* Buffer, 
    SIZE Length
);

DRIVER_IMPORT
UINT8 
LouKeHalPs2CheckControllerStatus();

#endif