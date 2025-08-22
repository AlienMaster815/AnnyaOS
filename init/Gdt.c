#include <LouAPI.h>

typedef struct PACKED _TSS{
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

typedef struct PACKED _LongModeGdt{
    uint64_t                           NULLSEG;
    uint64_t                           KCODE;
    uint64_t                           KDATA;
    uint64_t                           UCODE;
    uint64_t                           UDATA;
    uint64_t                           KPCR;
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

typedef struct PACKED _GDTREntry{
    uint16_t Length;
    uint64_t Base;
}GDTREntry, * PGDTREntry;

extern void InstallGDT(uint64_t GDT);
uint16_t GetNPROC();
void SetGSBase(uint64_t gs_base);

extern void SetPEB(uint64_t PEB);

void SetupGDT(){
    LouPrint("Setting Up GDT\n");

    PLongModeGdt GDT = (PLongModeGdt)LouKeMallocPhysicalEx(sizeof(LongModeGdt), 16, KERNEL_GENERIC_MEMORY);
    memset(GDT,0, sizeof(LongModeGdt));

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

    PTSS Tss = (PTSS)LouKeMallocPhysicalEx(sizeof(TSS), 16, KERNEL_GENERIC_MEMORY);
    memset(Tss,0, sizeof(TSS));

    Tss->RSP0 = (uintptr_t)LouKeMallocPhysicalEx((64 * KILOBYTE), 16, KERNEL_GENERIC_MEMORY);
    Tss->RSP1 = (uintptr_t)LouKeMallocPhysicalEx((64 * KILOBYTE), 16, KERNEL_GENERIC_MEMORY);
    Tss->RSP2 = (uintptr_t)LouKeMallocPhysicalEx((64 * KILOBYTE), 16, KERNEL_GENERIC_MEMORY);
    Tss->IST1 = (uintptr_t)LouKeMallocPhysicalEx((64 * KILOBYTE), 16, KERNEL_GENERIC_MEMORY);
    Tss->IST2 = (uintptr_t)LouKeMallocPhysicalEx((64 * KILOBYTE), 16, KERNEL_GENERIC_MEMORY);
    Tss->IST3 = (uintptr_t)LouKeMallocPhysicalEx((64 * KILOBYTE), 16, KERNEL_GENERIC_MEMORY);

    SetGDTSystemSegmentEntry(
        (uint8_t*)&GDT->TSSLo,
        (uintptr_t)Tss, sizeof(TSS) - 1,
        0x89,
        0x00
    );


    uint64_t GsBase = (uint64_t)LouKeMallocPhysical(KILOBYTE_PAGE, USER_GENERIC_MEMORY);

    if(GsBase >= 0xFFFFFFFFFFFF){
        LouPrint("PANIC GsBase Over GDT Limit\n");
        while(1);
    }
    
    SetGDTSegmentEntry(
        (uint8_t*)&GDT->KPCR,
        GsBase,
        0xFFFFF,
        0xF2,
        0xC
    );

    GDTREntry Gdtr;
    Gdtr.Length = sizeof(LongModeGdt) - 1;
    Gdtr.Base   = (uint64_t)GDT;

    LouPrint("Installing GDT:%h\n", GDT);
    InstallGDT((uint64_t)&Gdtr);

    SetGSBase(GsBase);

    LouPrint("Done Setting Up GDT\n");

}
