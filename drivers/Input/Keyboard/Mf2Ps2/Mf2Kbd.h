#define _KERNEL_MODULE_
#ifndef _MF2_KBD_H
#define _MF2_KBD_H
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

#define KBD_ACKNOL                              0xFA
#define KBD_RESEND                              0xFE

#define KBD_COMMAND_SET_LED                     0xED
#define KBD_LED_STATE_SCROLL_LOCK               0
#define KBD_LED_STATE_NUMBER_LOCK               1
#define KBD_LED_STATE_CAPS_LOCK                 2
#define KBD_COMMAND_ECHO                        0xEE
#define KBD_COMMAND_GET_SET_SCAN_SET            0xF0
#define GET_CURRENT_SCAN_SET                    0
#define CURRENT_SCAN_1                          0x43
#define CURRENT_SCAN_2                          0x41
#define CURRENT_SCAN_3                          0x3F
#define SET_SCAN_CODE_SET_1                     1
#define SET_SCAN_CODE_SET_2                     2
#define SET_SCAN_CODE_SET_3                     3
#define KBD_COMMAND_IDENTIFY                    0xF2
#define KBD_COMMAND_SET_TYPE_RATE_DELAY         0xF3
#define TYPE_RATE_AND_DELAY(Rate, Delay)        ((((Rate) & 0x1f) | (((Delay) & 0x03) << 5)) & ~(1 << 7)) 
#define KBD_COMMAND_ENABLE_SCANNING             0xF4
#define KBD_COMMAND_DISABLE_SCANNING            0xF5
#define KBD_COMMAND_SET_DEFAULT_PARAM           0xF6
#define KBD_COMMAND_ALL_KEYS_AUTO_REPEAT        0xF7
#define KBD_COMMAND_ALL_KEYS_MAKE_RELEASE       0xF8
#define KBD_COMMAND_ALL_KEYS_MAKE_ONLY          0xF9
#define KBD_COMMAND_ALL_KEYS_AUTO_REAPEAT_MAKE_RELEASE  0xFA
#define KBD_COMMAND_SPEC_KEYS_AUTO_REPEAT_ONLY  0xFB
#define KBD_COMMAND_SPEC_KEYS_MAKE_RELEASE      0xFC
#define KBD_COMMAND_SPEC_KEYS_MAKE_ONLY         0xFD
#define KBD_COMMAND_RESEND_LAST_BYTE            0xFE
#define KBD_COMMAND_RESET                       0xFF

#define KBD_RESPOND_INTERNAL_OVERRUN            0x00
#define KBD_SELF_TEST_SUCCESS                   0xAA
#define KBD_ECHO                                0xEE
//#define KBD_ACKNOL                            0xFA
#define KBD_SELF_TEST_FAIL1                     0xFC 
#define KBD_SELF_TEST_FAIL2                     0xFD
//#define KBD_RESEND                            0xFE
#define KBD_RESPOND_INTERNAL_OVERRUN2           0xFF

#define KBD1_KEYPRESS_ESC       0x02
#define KBD1_KEYPRESS_1         0x03
#define KBD1_KEYPRESS_2         0x04
#define KBD1_KEYPRESS_3         0x05
#define KBD1_KEYPRESS_4         0x06
#define KBD1_KEYPRESS_5         0x07
#define KBD1_KEYPRESS_6         0x08
#define KBD1_KEYPRESS_7         0x09    
#define KBD1_KEYPRESS_8         0x0A    
#define KBD1_KEYPRESS_9         0x0B    
#define KBD1_KEYPRESS_0         0x0C    
#define KBD1_KEYPRESS_DASH      0x0D    
#define KBD1_KEYPRESS_EQAUL     0x0E    
#define KBD1_KEYPRESS_BACKSPACE 0x0F
#define KBD1_KEYPRESS_TAB       0x10
#define KBD1_KEYPRESS_Q         0x11
#define KBD1_KEYPRESS_W         0x12
#define KBD1_KEYPRESS_E         0x13
#define KBD1_KEYPRESS_R         0x14
#define KBD1_KEYPRESS_T         0x15
#define KBD1_KEYPRESS_Y         0x16
#define KBD1_KEYPRESS_U         0x17
#define KBD1_KEYPRESS_I         0x18
#define KBD1_KEYPRESS_O         0x19
#define KBD1_KEYPRESS_P         0x1A
#define KBD1_KEYPRESS_O_BRACKET 0x1B
#define KBD1_KEYPRESS_I_BRACKET 0x1C
#define KBD1_KEYPRESS_ENTER     0x1D

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
Ps2WriteDataRegister(UINT8 Data);

DRIVER_IMPORT
LOUSTATUS 
Ps2ReadDataRegister(UINT8* Data);

#endif //MF2_KBD