#include <LouAPI.h>

typedef struct __attribute__((packed)) _TSS{
    uint32_t RESVD;
    uint64_t RSP0;
    uint64_t RSP1;
    uint64_t RSP2;
    uint64_t RSV2;
    uint64_t IST1;
    uint64_t IST2;
    uint64_t IST3;
    uint64_t IST4;
    uint64_t IST5;
    uint64_t IST6;
    uint64_t IST7;
    uint64_t RSV3;
    uint32_t RSV4;
}TSS, * PTSS;

extern uint32_t gdt64;
extern uint32_t tss64;

typedef struct __attribute__((packed)) _LongModeGdt{
    uint64_t                           NULLSEG;
    uint64_t                           KCODE;
    uint64_t                           KDATA;
    uint64_t                           UCODE;
    uint64_t                           UDATA;
    uint64_t                           TSSLo;
    uint64_t                           TSSHi;
}LongModeGdt, * PLongModeGdt;

void SetGDTSegmentEntry(
    uint8_t* GDTEntry,
    uint32_t Base, 
    uint32_t Limit,
    uint8_t Access, 
    uint8_t Flags
){
    LouPrint("Initializing GDT Segment\n");
    if(Limit > 0xFFFFF)LouPrint("WARNING : GDT Limit Cannot Be Above 0xFFFFF\nIgnoring Upper Extended Limit\n");

    GDTEntry[0] =  Limit        & 0xFF;
    GDTEntry[1] = (Limit >> 8)  & 0xFF;
    GDTEntry[6] = (Limit >> 16) & 0x0F;

    GDTEntry[2] =  Base        & 0xFF;
    GDTEntry[3] = (Base >> 8)  & 0xFF;
    GDTEntry[4] = (Base >> 16) & 0xFF;
    GDTEntry[7] = (Base >> 24) & 0xFF;

    GDTEntry[5] = Access;
    GDTEntry[6] |= Flags << 4;


    LouPrint("Done Initializing GDT Segment\n");
}

void SetGDTSystemSegmentEntry(
    uint8_t* SystemEntry,
    uint64_t Base,
    uint64_t Limit,
    uint8_t  Access,
    uint8_t  Flags
){  

    SystemEntry[0] =  Limit        & 0xFF;
    SystemEntry[1] = (Limit >> 8)  & 0xFF;
    SystemEntry[6] = (Limit >> 16) & 0x0F;

    SystemEntry[2] =  Base        & 0xFF;
    SystemEntry[3] = (Base >> 8)  & 0xFF;
    SystemEntry[4] = (Base >> 16) & 0xFF;
    SystemEntry[7] = (Base >> 24) & 0xFF;

    SystemEntry[5] = Access;
    SystemEntry[6] |= Flags << 4;

    SystemEntry[8] = (Base >> 32) & 0xFF;
    SystemEntry[9] = (Base >> 40) & 0xFF;
    SystemEntry[10] = (Base >> 48) & 0xFF;
    SystemEntry[12] = (Base >> 56) & 0xFF;

}

typedef struct __attribute__((packed)) _GDTREntry{
    uint16_t Length;
    uint64_t Base;
}GDTREntry, * PGDTREntry;

extern void InstallGDT(uint64_t GDT);

void SetupGDT(){
    LouPrint("Setting Up GDT\n");

    PLongModeGdt GDT = (PLongModeGdt)LouMalloc(sizeof(LongModeGdt));

    SetGDTSegmentEntry(
            (uint8_t*)&GDT->KCODE,
            0,
            0xFFFFF,
            0x9A,
            0xA
        );

    SetGDTSegmentEntry(
            (uint8_t*)&GDT->KDATA,
            0,
            0xFFFFF,
            0x92,
            0xC
        );
    SetGDTSegmentEntry(
            (uint8_t*)&GDT->UCODE,
            0,
            0xFFFFF,
            0xFA,
            0xA
        );
    SetGDTSegmentEntry(
            (uint8_t*)&GDT->UDATA,
            0,
            0xFFFFF,
            0xF2,
            0xC
        );

    PTSS Tss = (PTSS)LouMalloc(sizeof(TSS));

    void* KStack = LouMallocEx(64 * KILOBYTE, 16);
    Tss->RSP0 = (uintptr_t)KStack + (64 * KILOBYTE);
    
    KStack = LouMallocEx(64 * KILOBYTE, 16);
    Tss->RSP1 = (uintptr_t)KStack + (64 * KILOBYTE);
    
    KStack = LouMallocEx(64 * KILOBYTE, 16);
    Tss->RSP2 = (uintptr_t)KStack + (64 * KILOBYTE);

    void* SStack = LouMallocEx(64 * KILOBYTE, 16);
    Tss->IST1 = (uintptr_t)SStack + (64 * KILOBYTE);

    SStack = LouMallocEx(64 * KILOBYTE, 16);
    Tss->IST2 = (uintptr_t)SStack + (64 * KILOBYTE);

    SStack = LouMallocEx(64 * KILOBYTE, 16);
    Tss->IST3 = (uintptr_t)SStack + (64 * KILOBYTE);

    SetGDTSystemSegmentEntry(
        (uint8_t*)&GDT->TSSLo,
        (uintptr_t)Tss, sizeof(TSS) - 1,
        0x89,
        0x00
    );

    GDTREntry Gdtr;
    Gdtr.Length = sizeof(LongModeGdt) - 1;
    Gdtr.Base   = (uint64_t)GDT;

    InstallGDT((uint64_t)&Gdtr);
    LouPrint("Done Setting Up GDT\n");
}
