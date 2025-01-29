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

typedef struct _FIS_REGISTER_HOST_TO_DEVICE{
    //uint32_t 0
    uint8_t FisType;
    uint8_t PortMultiplyer  : 4;
    uint8_t Reserved1       : 3;
    uint8_t CommandControl  : 1;
    uint8_t Command;
    uint8_t FeatureLow;
    //uint32_t 1
    uint8_t LBAL1;
    uint8_t LBAL2;
    uint8_t LBAM1;
    uint8_t Device;
    //uint32_t 2
    uint8_t LBAM2;
    uint8_t LBAH1;
    uint8_t LBAH2;
    uint8_t FeatureHigh;
    //uint32_t 3
    uint8_t SectorCountLow;
    uint8_t SectorCountHigh;
    uint8_t IsyncCompleted;
    uint8_t ControlRegister;
    //uint32_t 4
    uint8_t Reserved2[4];
}FIS_REGISTER_HOST_TO_DEVICE, * PFIS_REGISTER_HOST_TO_DEVICE;

typedef struct _FIS_REGISTER_DEVICE_TO_HOST{
    //uint32_t 0
    uint8_t FisType;
    uint8_t PortMultiplyer  : 4;
    uint8_t Reserved0       : 2;
    uint8_t InterruptBit    : 1;
    uint8_t Reserved1       : 1;
    uint8_t Status;
    uint8_t Error;
    //uint32_t 1
    uint8_t LBAL1;
    uint8_t LBAL2;
    uint8_t LBAM1;
    uint8_t Device;
    //uint32_t 2
    uint8_t LBAM2;
    uint8_t LBAH1;
    uint8_t LBAH2;
    uint8_t Reserved2;
    //uint32_t 3
    uint8_t SectorCountLow;
    uint8_t SectorCountHigh;
    uint8_t Reserved3[2];
    //uint32_t 4
    uint8_t Reserved4[4];
}FIS_REGISTER_DEVICE_TO_HOST, * PFIS_REGISTER_DEVICE_TO_HOST;

typedef struct _DATA_FIS{
    //uint32_t 0
    uint8_t FisType;
    uint8_t PortMultiplyer  : 4;
    uint8_t Reserved0       : 4;
    uint8_t Reserved1[2];
    //uint32_t 1
    uint32_t PayloadData[1];
}DATA_FIS, * PDATA_FIS;

typedef struct _PIO_SETUP_FIS{
    //uint32_t 0
    uint8_t FisType;
    uint8_t PortMultiplyer  : 4;
    uint8_t Reserved0       : 1;
    uint8_t DataDirection   : 1; //1 is incoming
    uint8_t InterruptBit    : 1;
    uint8_t Reserved1       : 1;
    uint8_t ErrorValue;
    uint8_t Error;
    //uint32_t 1
    uint8_t LBAL1;
    uint8_t LBAL2;
    uint8_t LBAM1;
    uint8_t Device;
    //uint32_t 2
    uint8_t LBAM2;
    uint8_t LBAH1;
    uint8_t LBAH2;
    uint8_t Reserved2;
    //uint32_t 3
    uint8_t SectorCountLow;
    uint8_t SectorCountHigh;
    uint8_t Reserved3;
    uint8_t Status;
    //uint32_t 4
    uint16_t TransferCount;
    uint8_t  Reserved4[2];
}PIO_SETUP_FIS, * PPIO_SETUP_FIS;

typedef struct _DMA_SETUP_FIS{
    //uint32_t 0
    uint8_t FisType;
    uint8_t PortMultiplyer  : 4;
    uint8_t Reserved0       : 1;
    uint8_t DataDirection   : 1; //1 is device to host
    uint8_t InterruptBit    : 1;
    uint8_t AutoActivate    : 1;
    uint8_t Reserved1[2];
    //uint32_t 1 & 2
    uint64_t DmaBufferId;
    //uint32_t 3
    uint32_t Reserved2;
    //uint32_t 4
    uint32_t DmaBufferOffset;
    //uint32_t 5
    uint32_t TransferCount;
    //uint32_t 6
    uint32_t Reserved3;
}DMA_SETUP_FIS, * PDMA_SETUP_FIS;

typedef union _FIS_COMMAND{
    FIS_REGISTER_HOST_TO_DEVICE HostToDevice;
    FIS_REGISTER_DEVICE_TO_HOST DeviceToHost;
    DATA_FIS                    Data;
    PIO_SETUP_FIS               PioSetup;
    DMA_SETUP_FIS               DmaSetup;
}FIS_COMMAND, * PFIS_COMMAND;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
#endif //_SERIAL_ATA_H