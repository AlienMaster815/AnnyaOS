#define _KERNEL_MODULE_
#ifndef _PS2_BUS_H
#define _PS2_BUS_H

#include <LouDDK.h>

#define KEYBOARD_INTERRUTP  1
#define AUX_INTERRUPT       12

#define PS2_COMMAND_REGISTER    0x64
#define PS2_STATUS_REGISTER     0x64
#define PS2_DATA_REGISTER       0x60

#define PS2_OUTPUT_BUFFER_FULL  (1)
#define PS2_INPUT_BUFFER_FULL   (1 << 1)
#define PS2_SHOULD_BE_ZERO      (1 << 2)
#define PS2_INPUT_SELECTOR      (1 << 3)
#define PS2_KEYBOARD_INHIBITED  (1 << 4)
#define PS2_TRANSMITION_TIMEOUT (1 << 5)
#define PS2_RECIEVE_TIMEOUR     (1 << 6)
#define PS2_PARITY_ERROR        (1 << 7)



static inline UINT8 Ps2ReadData(){
    return inb(PS2_DATA_REGISTER);
}

static inline UINT8 Ps2ReadStatus(){
    return inb(PS2_STATUS_REGISTER);
}

static inline void Ps2WriteData(UINT8 Data){
    outb(PS2_DATA_REGISTER, Data);
}

static inline void Ps2WriteCommand(UINT8 Command){
    outb(PS2_COMMAND_REGISTER, Command);
}

#define PS2_TIMEOUT_MS          100
#define PS2_RET_CONTROLL_TEST   0x55
#define PS2_BUFFER_SIZE         16
#define PS2_MAX_MULTIPORT       4
#define TOTAL_PS2_PORTS         (PS2_MAX_MULTIPORT + 2)

typedef enum {
    PS2_MOUSE = 0x00,
    PS2_SCROLL_MOUSE = 0x03,
    PS2_5BUTTON_MOUSE = 0x04,
    PS2_MF2_KEYBOARD1 = 0xAB63,        
    PS2_MF2_KEYBOARD2 = 0xABC1,
    PS2_SHORTBOARD_KEYBOARD = 0xAB84,
    PS2_NCDN97_KEYBOARD = 0xAB85,
    PS2_122KEY_KEYBOARD = 0xAB86,
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
    //union {

    //};
}PS2_DEVICE_OBJECT, * PPS2_DEVICE_OBJECT;


#endif