#ifndef _SCSI_DEVICE_H
#define _SCSI_DEVICE_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif


typedef uint64_t BLIST_FLAGS;

#define SCSI_SENCE_BUFFERSIZE   96

typedef struct _SCSI_MODE_DATA{
    uint32_t    EntryLength;
    uint16_t    BDL;
    uint8_t     MediumType;
    uint8_t     DeviceSpecifc;
    uint8_t     HeaderLength;
    uint8_t     LongLba : 1;
}SCSI_MODE_DATA, * PSCSI_MODE_DATA;

#define SCSI_DEV_STATE_CREATED              1
#define SCSI_DEV_STATE_RUNNING              2
#define SCSI_DEV_STATE_CANCEL               3
#define SCSI_DEV_STATE_DELETE               4
#define SCSI_DEV_STATE_QUIESCENT            5
#define SCSI_DEV_STATE_OFFLINE              6
#define SCSI_DEV_STATE_TRANSPORT_OFFLINE    7
#define SCSI_DEV_STATE_BLOCK                8
#define SCSI_DEV_STATE_CREATED_BLOCK        9

#define SCSI_SCAN_INITIAL 0
#define SCSI_SCAN_RESCAN  1
#define SCSI_SCAN_MANUAL  2

#define SCSI_EVENT_MEDIA_CHANGE                         1
#define SCSI_EVENT_INQUIRY_CHANGE_REPORTED              2
#define SCSI_EVENT_CAPACITY_CHANGE_REPORTED             3
#define SCSI_EVENT_SOFT_THRESHOLD_REACHED_REPORTED      4
#define SCSI_EVENT_MODE_PARAMETER_CHANGE_REPORTED       5
#define SCSI_EVENT_LUN_CHANGE_REPORTED                  6
#define SCSI_EVENT_ALUA_STATE_CHANGE_REPORTED           7
#define SCSI_EVENT_POWER_ON_RESET_OCCOURED              8
#define SCSI_EVENT_FIRST                                SCSI_EVENT_MEDIA_CHANGE
#define SCSI_EVENT_LAST                                 SCSI_EVENT_POWER_ON_RESET_OCCOURED
#define SCSI_EVENT_MAXBITS                              SCSI_EVENT_POWER_ON_RESET_OCCOURED + 1

typedef struct _READ_COPY_UPDATE_HEADER{
    struct _READ_COPY_UPDATE_HEADER* NextHeader;
    void (*ReadCopyUpdate)(struct _READ_COPY_UPDATE_HEADER* Header);
}READ_COPY_UPDATE_HEADER, * PREAD_COPY_UPDATE_HEADER;

typedef struct _SCSI_EVENT{
    uint32_t    EventType;
    ListHeader  NodeChain;
}SCSI_EVENT, * PSCSI_EVENT;

typedef struct _SCSI_VIRTUAL_PRODUCT_DATA{
    READ_COPY_UPDATE_HEADER     ReadCopyUpdateHeader;
    int                         Length;
    uint8_t                     DataBuffer[];
}SCSI_VIRTUAL_PRODUCT_DATA, * PSCSI_VIRTUAL_PRODUCT_DATA;

//typedef struct _LOU_SCSI_DEVICE{

//}LOU_SCSI_DEVICE, * PLOU_SCSI_DEVICE;

#ifdef __cplusplus
}
#endif

#endif //_SCSI_DEVICE_H