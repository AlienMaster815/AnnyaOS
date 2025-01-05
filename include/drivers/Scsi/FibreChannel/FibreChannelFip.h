#ifndef _FIBRE_CHANNEL_FIP_H
#define _FIBRE_CHANNEL_FIP_H

#pragma pack(push,1)

#define FIP_DEF_PRIORITY        128
#define FIP_DEF_FC_MAP          0x0EFC00
#define FIP_DEF_FKA             8000
#define FIP_VN_KA_PERIOD        90000
#define FIP_FCF_FUZZ            100

#define FIP_VN_FIBRE_CHANNEL_MAP            0x0EFD00
#define FIP_VN_PROBE_WAIT                   100
#define FIP_VN_ANN_WAIT                     400
#define FIP_VN_RLIM_INT                     10000
#define FIP_VN_RLIM_COUNT                   10
#define FIP_VN_BEACON_INIT                  0x8000
#define FIP_VN_BEACON_FUZZ                  100

#define FIP_ALL_FCOE_MACS       ((uint8_t[8]) {1, 0x10, 0x18, 1, 0, 0})
#define FIP_ALL_ENODE_MACS      ((uint8_t[8]) {1, 0x10, 0x18, 1, 0, 1})
#define FIP_ALL_FCF_MACS        ((uint8_t[8]) {1, 0x10, 0x18, 1, 0, 2})
#define FIP_ALL_VN2VN_MACS      ((uint8_t[8]) {1, 0x10, 0x18, 1, 0, 4})
#define FIP_ALL_P2P_MACS        ((uint8_t[8]) {1, 0x10, 0x18, 1, 0, 5})

#define FIP_VERSION 1

#define FIP_VERSION_SHIFT   4
#define FIP_VERSION_ENCAPS(Version) ((Version) << FIP_VERSION_SHIFT)
#define FIP_VERSION_DECAPS(Version) ((Version) << FIP_VERSION_SHIFT)
#define FIP_BPW             4



typedef struct _FIP_HEADER{
    uint8_t     FipVersion;
    uint8_t     FipReserve1;
    uint16_t    FipOperationCode; //big Endian
    uint8_t     FipReserved2;
    uint8_t     FipSubCode;
    uint16_t    FipDlLength; //BigEndian
    uint16_t    Fipflags;
}FIP_HEADER, * PFIP_HEADER;

typedef enum{
    FIP_OPCODE_DISC     = 1,
    FIP_OPCODE_LS       = 2,
    FIP_OPCODE_CTRL     = 3,
    FIP_OPCODE_VLAN     = 4,
    FIP_OPCODE_VN2VN    = 5,
    FIP_OPCODE_VENDOR_MIN = 0xFFF8,
    FIP_OPCODE_VENDOR_MAX = 0xFFFE,
}FIP_OPCODE;

typedef enum{
    FIP_SUBCODE_SOL     = 1,
    FIP_SUBCODE_ADV     = 2,
}FIP_DISC_SUBCODE;

typedef enum{
    FIP_SUBCODE_REQ  = 1,
    FIP_SUBCODE_REP  = 2,
}FIP_TRANSMITION_SUBCODE;

typedef enum{
    FIP_SUBCODE_KEEP_ALIVE  = 1,
    FIP_SUBCODE_CLEAR_VLINK = 2,
}FIP_RESET_SUBCODE;

typedef enum{
    FIP_SUBCODE_VLAN_REQUEST        = 1,
    FIP_SUBCODE_VLAN_NOTIFICATION   = 2,
    FIP_SUBCODE_VLAN_VN_2VN_NOTE    = 3,
}FIP_VLAN_SUBCODE;

typedef enum{
    FIP_SUBCODE_VLAN_PROBE_REQUEST  = 1,
    FIP_SUBCODE_VLAN_PROBE_REPLY    = 2,
    FIP_SUBCODE_VLAN_CLAIM_NOTIFY   = 3,
    FIP_SUBCODE_VLAN_CLAIM_REPLY    = 4, 
    FIP_SUBCPDE_VLAN_BEACON         = 5,
}FIP_VN2VN_SUBCODE;

typedef struct _FIP_DESCRIPTOR{
    uint8_t FipDType;
    uint8_t FipDLength;
}FIP_DESCRIPTOR, * PFIP_DESCRIPTOR;

typedef enum {
    FIP_DT_PRIORITY     = 1,
    FIP_DT_MAC          = 2,
    FIP_DT_MAP_OUI      = 3,
    FIP_DT_NAME         = 4,
    FIP_DT_FAB          = 5,
    FIP_DT_FCOE_SIZE    = 6,
    FIP_DT_FLOGI        = 7,
    FIP_DT_FDISC        = 8,
    FIP_DT_LOGO         = 9,
    FIP_DT_ELP          = 10,
    FIP_DT_VLAN_ID      = 11,
    FIP_DT_FKA          = 12,
    FIP_DT_VENDOR       = 13,
    FIP_DT_VLAN         = 14,
    FIP_DT_FC4F         = 15,
    FIP_DT_LIMIT,
    FIP_DT_NON_CRITICAL = 128,
    FIP_DT_CLEAR_VLINKS = 128,
    FIP_DT_VENDOR_BAS   = 241,
}FIP_DESCRIPTOR_TYPE;

typedef struct _FIP_PRIORITY_DESCRIPTOR{
    FIP_DESCRIPTOR  FdDescriptorl;
    uint8_t         FdReserved;
    uint8_t         FdPriority;
}FIP_PRIORITY_DESCRIPTOR, * PFIP_PRIORITY_DESCRIPTOR;

typedef struct _FIP_MAC_DESCRIPTOR{
    FIP_DESCRIPTOR      FdDescriptor;
    uint8_t             FdMac[6];
}FIP_MAC_DESCRIPTOR, * PFIP_MAC_DESCRIPTOR;

typedef struct _FIP_MAP_DESCRIPTOR{
    FIP_DESCRIPTOR  FdDescriptor;
    uint8_t         FdReserved[2];
    uint64_t        FdWwn; //bigEndian
}FIP_MAP_DESCRIPTOR, * PFIP_MAP_DESCRIPTOR;

typedef struct _FIP_WWN_DESCRIPTOR{
    FIP_DESCRIPTOR  FdDescriptor;
    uint8_t         FdReserved;
    uint64_t        FdWwn;//bigEndian
}FIP_WWN_DESCRIPTOR, * PFIP_WWN_DESCRIPTOR;

typedef struct _FIP_FAB_DESCRIPTOR{
    FIP_DESCRIPTOR  FdDescriptor;
    uint16_t        FdVfid; //Reserved
    uint8_t         FdReserved;
    uint8_t         FdMap[3];
    uint64_t        FdWwn;//bigEndian
}FIP_FAB_DESCRIPTOR, * PFIP_FAB_DESCRIPTOR;

typedef struct _FIP_SIZE_DESCRIPTOR{
    FIP_DESCRIPTOR  FdDescriptor;
    uint16_t        FdSize;//bigEndian
}FIP_SIZE_DESCRIPTOR, * PFIP_SIZE_DESCRIPTOR;

typedef struct _FIP_VNODE_DESCRIPTOR{
    FIP_DESCRIPTOR  FdDescriptor;
    uint8_t         FdMac[6];
    uint8_t         FdReserved;
    uint8_t         FdFcId[3];
    uint64_t        FdWwpn;
}FIP_VNODE_DESCRIPTOR, * PFIP_VNODE_DESCRIPTOR;

typedef struct _FIP_FKA_DESCRIPTOR{
    uint8_t     FdReserved;
    uint8_t     FdFlags;
    uint32_t    FdFkaPeriod; //big endian      
}FIP_FKA_DESCRIPTOR, * PFIP_FKA_DESCRIPTOR;

typedef enum{
    FIP_FKA_ADV_D = 0x01,
}FIP_FKA_FLAGS;

typedef struct _FIP_VLAN_DESCRIPTOR{
    FIP_DESCRIPTOR  FdDescriptor;
    uint16_t        FdVlan;//BigEndian 
}FIP_VLAN_DESCRIPTOR, * PFIP_VLAN_DESCRIPTOR;

typedef struct _FIP_FC4_DESCRIPTOR{
    FIP_DESCRIPTOR  FdDescriptor;
    uint8_t         FdReserved[2];
    //FC_NS_FTS       FdFts;
    //FC_NS_FF        FdFF;
}FIP_FC4_DESCRIPTOR, * PFIP_FC4_DESCRIPTOR;

typedef struct _FIP_VENDOR_DESCRIPTOR{  
    FIP_DESCRIPTOR  FdDescriptor;
    uint8_t         FdReserved[2];
    uint8_t         FdVendorID[8];
}FIP_VENDOR_DESCRIPTOR, * PFIP_VENDOR_DESCRIPTOR;

#pragma pack(pop)

#endif //_FIBRE_CHANNEL_FIP_H
