#ifndef _SERIAL_ATA_H
#define _SERIAL_ATA_H

#ifdef __cplusplus
#include <LouDDk.h>
extern "C"{
#else 
#include <LouAPI.h>
#endif

//The Following Code Was Created from information from
//the Serial Ata 1.0a Specification, Ahci Specification
//and the Ahci Page Of osdev.org: https://wiki.osdev.org/AHCI
//and is copyright By the GPL2 Licesnce By: 
//Tyler Grenier (2025)

#define FIS_TYPE_REGISTER_HOST_TO_DEVICE    0x27
#define FIS_TYPE_REGISTER_DEVICE_TO_HOST    0x34
#define FIS_TYPE_DMA_ACTIVATE               0x39
#define FIS_TYPE_DMA_SETUP                  0x41
#define FIS_TYPE_DATA                       0x46
#define FIS_TYPE_BIST                       0x58
#define FIS_TYPE_PIO_SETUP                  0x5F
#define FIS_TYPE_DEVICE_BITS                0xA1
#pragma pack(push, 1)

typedef struct _RECIEVED_FIS_ORGINIZATION{
    uint8_t FIS_DATA[0xFF];
}AHCI_RECIEVED_FIS_ORGINIZATION, * PAHCI_RECIEVED_FIS_ORGINIZATION;

typedef struct _COMMAND_LIST_STRUCTURE{
    uint8_t  CFL_A_W_P;
    uint8_t  R_B_C_R_PMP;
    uint16_t PRDTL;
    uint32_t PRDTByteCount;
    uint32_t CommandTableBaseLow; //7 bits aligned
    uint32_t CommandTableBaseHigh;
    uint32_t Reserved[4];
}AHCI_COMMAND_LIST_STRUCTURE, * PAHCI_COMMAND_LIST_STRUCTURE;

typedef struct _COMMAND_TABLE_ENTRY{
    uint8_t CommandFis[0x40];
    uint8_t AtapiCommand[0x50 - 0x40];
    uint8_t Reserved[0x80 - 0x50];
}AHCI_COMMAND_TABLE_ENTRY, * PAHCI_COMMAND_TABLE_ENTRY;

typedef struct _AHCI_PRDT_ENTRY{
    uint32_t    DataBaseAdrressLow;
    uint32_t    DataBaseAddressHigh;
    uint32_t    Reserved;
    uint32_t    ByteCount;
}AHCI_PRDT_ENTRY,* PAHCI_PRDT_ENTRY;


static inline void FillOutCommandTableStructure(
    PAHCI_PRDT_ENTRY PrdtEntry,
    uint64_t    DataBaseAddress,
    uint32_t    DataCount
){
    PrdtEntry->DataBaseAdrressLow = DataBaseAddress & 0xFFFFFFFF;
    PrdtEntry->DataBaseAddressHigh = DataBaseAddress >> 32;
    PrdtEntry->Reserved = 0;
    PrdtEntry->ByteCount = DataCount;
}

static inline void FillOutCommandListStructure(
    PAHCI_COMMAND_LIST_STRUCTURE PCLS,
    uint8_t CFL,
    bool AtapiCommand,
    bool WriteCommand,
    bool Prefetchable,
    bool Reset,
    bool Bist,
    bool ClearBusyOnRok,
    uint8_t PMP,
    uint16_t Prdtl,
    uint32_t PRDTByteCount,
    uint64_t CommandTableBase
){

    PCLS->CFL_A_W_P      = CFL & 0x1F;
    PCLS->CFL_A_W_P     |= AtapiCommand     ? (1 << 5) : 0;
    PCLS->CFL_A_W_P     |= WriteCommand     ? (1 << 6) : 0;
    PCLS->CFL_A_W_P     |= Prefetchable     ? (1 << 7) : 0;
    PCLS->R_B_C_R_PMP    = Reset            ? (1 << 0) : 0;
    PCLS->R_B_C_R_PMP   |= Bist             ? (1 << 1) : 0;
    PCLS->R_B_C_R_PMP   |= ClearBusyOnRok   ? (1 << 3) : 0;
    PCLS->R_B_C_R_PMP   |= (PMP & 0xF)           << 4;
    PCLS->PRDTL          = Prdtl;
    PCLS->PRDTByteCount  = PRDTByteCount;
    PCLS->CommandTableBaseLow = CommandTableBase & 0xFFFFFF80;
    PCLS->CommandTableBaseHigh= CommandTableBase >> 32;

    //clear the reserved
    for(uint8_t i = 0 ; i < 4; i++){
        PCLS->Reserved[i] = 0;
    }
}

#pragma pack(pop)
#ifdef __cplusplus
}
#endif
#endif //_SERIAL_ATA_H