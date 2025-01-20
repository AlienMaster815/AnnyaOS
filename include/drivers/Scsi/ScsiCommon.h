#ifndef _SCSI_COMMON_H
#define _SCSI_COMMON_H
#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif

#define SCSI_PR_TYPE_WRITE_EXCLUSIVE                    0x01
#define SCSI_PR_TYPE_EXCLUSIVE_ACCESS                   0x03
#define SCSI_PR_TYPE_WRITE_EXCLUSIVE_REGISTER_ONLY      0x05
#define SCSI_PR_TYPE_EXCLUSIVE_ACCESS_REGISTER_ONLY     0x06
#define SCSI_PR_TYPE_WRITE_EXCLUSIVE_ALL_REGISTERS      0x07
#define SCSI_PR_TYPE_EXCLUSIVE_ACCESS_ALL_REGISTERS     0x08

uint32_t ScsiBlockPrTypeToBlock(uint32_t PrType);
uint32_t ScsiPrTypeToBlock(uint32_t ScsiPrType);

typedef struct _SCSI_SENCE_HEADER{
    uint8_t ResponceCode;
    uint8_t SenceKey;
    uint8_t Asc;
    uint8_t Ascq;
    uint8_t Byte4;
    uint8_t Byte5;
    uint8_t Byte6;
    uint8_t AdditionalLength;
}SCSI_SENCE_HEADER, * PSCSI_SENCE_HEADER;

static inline bool ScsiSenceValid(PSCSI_SENCE_HEADER SenceHeader){
    if(!SenceHeader){
        return false;
    }
    return ((SenceHeader->ResponceCode & 0x70) == 0x70);
}

int32_t ScsiSetSenceInformation(uint8_t* Buffer, int32_t BufferLength, uint64_t Info);
int32_t ScsiSetSenceFieldPointer(uint8_t* Buffer, int32_t BufferLength, uint16_t Fp, uint8_t Bp, bool Cd);

#ifdef __cplusplus
}
#endif
#endif //_SCSI_COMMON_H
