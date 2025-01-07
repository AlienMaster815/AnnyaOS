#ifndef _SCSI_FIBRE_CHANNEL_NTELINK_H
#define _SCSI_FIBRE_CHANNEL_NTELINK_H
#pragma pack(push,1)

#include "ScsiNetlink.h"
#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

#define FIBRE_CHANNEL_NET_LINK_ASYNC_EVENT    0x100

#define FIBRE_CHANNEL_NET_LINK_MESAGE_ALIGN(Length) (((Length) + 7) & ~7)

typedef struct _FIBRE_CHANNEL_NET_LINK_EVENT{
    SCSI_NET_LINK_HEADER    Header;
    uint64_t                Seconds;
    uint64_t                VendorID;
    uint16_t                HostNumber;
    uint16_t                DataLength;
    uint32_t                EventNumber;
    uint32_t                EventCode;
    uint8_t                 EventData[];
}FIBRE_CHANNEL_NET_LINK_EVENT, * PFIBRE_CHANNEL_NET_LINK_EVENT;

#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif //_SCSI_FIBRE_CHANNEL_NTELINK_H
