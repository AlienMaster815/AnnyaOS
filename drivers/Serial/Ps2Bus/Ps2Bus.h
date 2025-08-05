#define _KERNEL_MODULE_
#ifndef _PS2_BUS_H
#define _PS2_BUS_H

#include <LouDDK.h>

#define KEYBOARD_INTERRUPT  1
#define AUX_INTERRUPT       12

#define PS2_COMMAND_REGISTER    0x64
#define PS2_STATUS_REGISTER     0x64
#define PS2_DATA_REGISTER       0x60

#define PS2_OUTPUT_BUFFER_FULL  (1)
#define PS2_INPUT_BUFFER_FULL   (1 << 1)
#define PS2_SHOULD_BE_ZERO      (1 << 2)
#define PS2_INPUT_SELECTOR      (1 << 3)
#define PS2_TIMEOUT_ERROR       (1 << 6)
#define PS2_PARITY_ERROR        (1 << 7)

#define PS2_READ_BYTE(n)                ((n + 0x20) & 0x3F)
#define PS2_WRITE_BYTE(n)               ((n + 0x60) & 0x7F)
#define PS2_CONFIG_BYTE                 0
#define PS2_DISABLE_SECONDARY_PORT      0xA7
#define PS2_ENABLE_SECONDARY_PORT       0xA8
#define PS2_TEST_SECONDARY_PORT         0xA9
#define PS2_TEST_CONTROLLER             0xAA
#define PS2_TEST_PRIMARY_PORT           0xAB
#define PS2_DISAGNOSTIC_DUMP            0xAC
#define PS2_DISABLE_PRIMARY_PORT        0xAD
#define PS2_ENABLE_PRIMARY_PORT         0xAE
#define PS2_READ_CONTROLLER_INPUT       0xC0
#define PS2_COPY_0_TO_3_TO_STATUS       0xC1
#define PS2_COPY_4_TO_7_TO_STATUS       0xC2
#define PS2_READ_CONTROLLER_OUTPUT      0xD1
#define PS2_WRITE_TO_PRIMARY_OUTPUT     0xD2
#define PS2_WRITE_TO_SECONDARY_OUTPUT   0xD3
#define PS2_WRITE_TO_SECONDARY_INPUT    0xD4

#define PS2_PRIMARY_PORT_IRQ_ENABLED            (1)
#define PS2_SECONDARY_PORT_IRQ_ENABLED          (1 << 1)
#define PS2_SYSTEM_FLAG                         (1 << 2)
#define PS2_PRIMARY_PORT_CLOCK_DISABLED         (1 << 4)
#define PS2_SECONDARY_PORT_CLOCK_DSIABLED       (1 << 5)
#define PS2_PRIMARY_PORT_TRANSLATION            (1 << 6)

#define PS2_CHIPSET_CLASS               "8042 PS/2"

#define PS2_RESET_DEVICE 0xFF
#define PS2_DISABLE_SCANNING    0xF5
#define PS2_IDENTIFY_DEVICE     0xF2
#define PS2_DEVICE_ACK          0xFA


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


#endif