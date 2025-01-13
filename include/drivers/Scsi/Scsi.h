#ifndef _SCSI_H
#define _SCSI_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else 
#include <LouAPI.h>
#endif

#define SCSI_PR_TYPE_WRITE_EXSCLUSIVE                       0x01
#define SCSI_PR_TYPE_EXSCLUSIVE_ACCESS                      0x03
#define SCSI_PR_TYPE_WRITE_EXSCLUSIVE_REGISTER_ONLY         0x05
#define SCSI_PR_TYPE_EXSCLUSIVE_ACCESS_REGISTER_ONLY        0x06
#define SCSI_PR_TYPE_WRITE_EXSCLUSIVE_ALL_REGISTERS         0x07
#define SCSI_PR_TYPE_EXSCLUSIVE_ACCESS_ALL_REGISTERS        0x08

uint32_t ScsiBlockPrTypeToBlock(uint32_t PrType);
uint32_t ScsiPrTypeToBlock(uint32_t ScsiPrType);

//static inline 
//uint64_t ScsiVariedLengthCommandBufferLength(
//    void* Header
//){
//    return (())
//}

#ifdef __cplusplus
}
#endif
#endif //_SCSI_H