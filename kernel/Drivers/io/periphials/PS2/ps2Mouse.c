#include <LouAPI.h>

//static uint16_t x = 0, y = 0;
void PS2MouseHandler(uint64_t Rsp);
void LouKeMouseMoveEventUpdate(int64_t X, int64_t Y , BOOL RigtClick, BOOL LeftClick);

static uint8_t Offset = 0;
static uint8_t Buffer[3] = {0};

static int8_t x = 0;
static int8_t y = 0;

typedef struct  PACKED _CPUContext{
    // General-Purpose Registers    
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r8;

    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;

    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;

    uint64_t cs;
    uint64_t fq;
    uint64_t FaultStack;
    uint64_t ss;
} CPUContext;

void InitializePs2Mouse(){
    LouPrint("Initializing PS/2 Mouse (If There Is One)\n");
    RegisterInterruptHandler(PS2MouseHandler, 32 + 12, false, 0x00);
    
    outb(0x64, 0xA8);
    outb(0x64, 0x20);

    uint8_t Status = (inb(0x60) | 2);
    outb(0x64, 0x60);
    outb(0x60, Status);

    outb(0x64, 0xD4);
    outb(0x60, 0xF4);
    inb(0x60);

    LouPrint("PS/2 Mouse Initialized Successfully\n");
    
}

void LouKeMouseClickEventUpdate(bool Right, bool Left);


void PS2MouseHandler(uint64_t Rsp){

    uint8_t Status = inb(0x64);
    if(!((Status) & 0x20)){
        return;
    }

    Buffer[Offset] = inb(0x60);
    
    if (Offset == 0 && !(Buffer[Offset] & 0x08)) {
        return;
    }
    
    Offset = (Offset + 1) % 3;

    if(Offset == 0){
        x = (int8_t)Buffer[1];
        y = (int8_t)Buffer[2];

        bool LeftClick = Buffer[0] & 0x01;
        bool RigtClick = Buffer[0] & 0x02;

        LouKeMouseMoveEventUpdate((int64_t)x, (int64_t)-y, RigtClick, LeftClick);
    }

}