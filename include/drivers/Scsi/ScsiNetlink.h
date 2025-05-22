#ifndef _SCSI_NET_LINK_H
#define _SCSI_NET_LINK_H
#pragma pack(push, 1)
#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif


#ifndef NL_MESSAGE_MIN_TYPE
#define NL_MESSAGE_MIN_TYPE 0x10
#endif

#define SCSI_TRANSPORT_MESSAGE  NL_MESSAGE_MIN_TYPE + 1

#define SCSI_NET_LINK_GROUP_FIBRE_CHANNEL_EVENTS    1 << 2
#define SCSI_NET_LINK_GROUP_COUNT                   3

//Always ALign this By 8 bytes
typedef struct _SCSI_NET_LINK_HEADER{
    uint8_t     Version;
    uint8_t     Transport;
    uint16_t    Magic;
    uint16_t    Type;
    uint16_t    Length;
}SCSI_NET_LINK_HEADER, * PSCSI_NET_LINK_HEADER;

#define SCSI_NET_LINK_VERSION   1
#define SCSI_NET_LINK_MAGIC     0xA1B2

#define SCSI_NET_LINK_TRANSPORT                 0       
#define SCSI_NET_LINK_TRANSPORT_FIBRE_CHANNEL   1
#define SCSI_NET_LINK_MAX_TRANSPORTS            2

#define SCSI_NET_LINK_VENDOR                     0x0001

#define SCSI_NET_LINK_MESSAGE_ALIGN(Length)      (((Length) + 7) & ~7)

//Always ALign this By 8 bytes
typedef struct _SCSI_NET_LINK_HOST_VENDOR_MESSAGE{
    SCSI_NET_LINK_HEADER    Header;
    uint64_t                VendorID;
    uint16_t                HostNumber;
    uint16_t                DataLength;
}SCSI_NET_LINK_HOST_VENDOR_MESSAGE, * PSCSI_NET_LINK_HOST_VENDOR_MESSAGE;

#define SCSI_NET_LINK_VID_TYPE_SHIFT    56
#define SCSI_NET_LINK_VID_TYPE_BITS     0xFF << SCSI_NET_LINK_VID_TYPE_SHIFT
#define SCSI_NET_LINK_VID_TYPE_PCI      1 << SCSI_NET_LINK_VID_TYPE_SHIFT
#define SCSI_NET_LINK_VID_ID_BITS       (~SCSI_NET_LINK_VID_TYPE_BITS)

static inline void InitializeScsiNetlinkHeader(
    PSCSI_NET_LINK_HEADER    Header,
    uint8_t                 Transport,
    uint16_t                MessageType,
    uint16_t                MessageLength
){
    Header->Version         =   SCSI_NET_LINK_VERSION;
    Header->Transport       =   Transport;
    Header->Magic           =   SCSI_NET_LINK_MAGIC;
    Header->Type     =   MessageType;
    Header->Length   =   MessageLength;
}

#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif //_SCSI_NET_LINK_H