#include <LouDDK.h>
#include <NtAPI.h>
#include "../Processors.h"
#include "apic.h"
#include <LouACPI.h>

//backup pic for non APIC machines

#define MASTER_PIC_COMMAND      0x20
#define MASTER_PIC_DATA         0x21
#define SLAVE_PIC_COMMAND       0xA0
#define SLAVE_PIC_DATA          0xA1
#define PIC_EOI                 0x20

#define PIC_ICW1_ICW4           0x01
#define PIC_ICW1_SINGLE         0x02
#define PIC_ICW1_INTERVAL4      0x04
#define PIC_ICW1_LEVEL          0x08
#define PIC_ICW1_INIT           0x10

#define PIC_ICW4_8086           0x01
#define PIC_ICW4_AUTO           0x02
#define PIC_ICW4_SLAVE_BUFF     0x08
#define PIC_ICW4_MASTER_BUFF    0x0C
#define PIC_ICW4_SFNM           0x10

#define PIC_CASCADE_IRQ         2

static inline void PicWriteMasterCommand(UINT8 Data){
    outb(MASTER_PIC_COMMAND, Data);
}

static inline UINT8 PicReadMasterCommand(){
    return inb(MASTER_PIC_COMMAND);
}

static inline void PicWriteMasterData(UINT8 Data){
    outb(MASTER_PIC_DATA, Data);
}

static inline UINT8 PicReadMasterData(){
    return inb(MASTER_PIC_DATA);
}

static inline void PicWriteSlaveCommand(UINT8 Data){
    outb(SLAVE_PIC_COMMAND, Data);
}

static inline UINT8 PicReadSlaveCommand(){
    return inb(SLAVE_PIC_COMMAND);
}

static inline void PicWriteSlaveData(UINT8 Data){
    outb(SLAVE_PIC_DATA, Data);
}

static inline UINT8 PicReadSlaveData(){
    return inb(SLAVE_PIC_DATA);
}


static inline void IODelay() {
    outb(0x80, 0);
}

static void RemapPic(UINT8 V1, UINT8 V2, UINT8 Mask1, UINT8 Mask2){
    PicWriteMasterCommand(PIC_ICW1_INIT | PIC_ICW1_ICW4);
    IODelay();
    PicWriteSlaveCommand(PIC_ICW1_INIT | PIC_ICW1_ICW4);
    IODelay();
    PicWriteMasterData(V1);
    IODelay();
    PicWriteSlaveData(V2);
    IODelay();
    PicWriteMasterData(1 << PIC_CASCADE_IRQ);
    IODelay();
    PicWriteSlaveData(2);
    IODelay();
    PicWriteMasterData(PIC_ICW4_8086);
    IODelay();
    PicWriteSlaveData(PIC_ICW4_8086);
    IODelay();

    PicWriteMasterData(Mask1);
    PicWriteSlaveData(Mask2);
}

static void PicEoi(UINT8 Irq){
    if(Irq >= 8){
        PicWriteSlaveCommand(PIC_EOI);
    }
    PicWriteMasterCommand(PIC_EOI);
}

void PicUnmask(UINT8 Irq){
    if(Irq < 8){
        PicWriteMasterData(PicReadMasterData() & ~(1 << Irq));
    }else if(Irq < 16){
        PicWriteSlaveData(PicReadSlaveData() & ~(1 << (Irq - 8)));
    }
}

void PicMask(UINT8 Irq){
    if(Irq < 8){
        PicWriteMasterData(PicReadMasterData() | (1 << Irq));
    }else if(Irq < 16){
        PicWriteSlaveData(PicReadSlaveData() | (1 << (Irq - 8)));
    }
}

void LouKeInitializeBackupPic(){

    RemapPic(0x20, 0x28, 0xFF, 0xFF);

    LouKeInitializeEoiHandler((PVOID)PicEoi, 0);
    LouKeInitializeMaskHandler((PVOID)PicMask, 0);
    LouKeInitializeUnmaskHandler((PVOID)PicUnmask, 0);

    PicUnmask(0);

}