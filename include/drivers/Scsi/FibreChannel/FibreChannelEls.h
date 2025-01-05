#ifndef _FIBRE_CHANNEL_ELS_H
#define _FIBRE_CHANNEL_ELS_H


#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif

static inline uint16_t LouBeToLe16(uint16_t Be){
    uint16_t Le = (Be & 0xFF) << 8;
    Le |= (Be  & 0xFF00) >> 8;
    return Le;
}

static inline uint32_t LouBeToLe32(uint32_t Be){
    uint32_t Le = (Be & 0xFF) << 24;
    Le |= (Be & 0xFF00) << 8;
    Le |= (Be & 0xFF0000) >> 8;
    Le |= (Be & 0xFF000000) >> 24; 
    return Le;
}



typedef enum {
    ELS_LS_RJT  =   0x01,
    ELS_LS_ACC  =   0x02,
    ELS_P_LOGIC =   0x03,
    ELS_F_LOGIC =   0x04,
    ELS_LOGO    =   0x05,
    ELS_ABTX    =   0x06,
    ELS_RCS     =   0x07,
    ELS_RES     =   0x08,
    ELS_RSS     =   0x09,
    ELS_RSI     =   0x0A,
    ELS_ESTS    =   0x0B,
    ELS_ESTC    =   0x0C,
    ELS_ADVC    =   0x0D,
    ELS_RTV     =   0x0E,
    ELS_RLS     =   0x0F,
    ELS_EXHO    =   0x10,
    ELS_TEST    =   0x11,
    ELS_RRQ     =   0x12,
    ELS_REC     =   0x13,
    ELS_SRR     =   0x14,
    ELS_FPIN    =   0x16,
    ELS_EDC     =   0x17,
    ELS_RDP     =   0x18,
    ELS_RDF     =   0x19,
    ELS_PRLI    =   0x20,
    ELS_PRLO    =   0x21,
    ELS_SCN     =   0x22,
    ELS_TPLS    =   0x23,
    ELS_TPRLO   =   0x24,
    ELS_LCLM    =   0x25,
    ELS_GAID    =   0x30,
    ELS_FACT    =   0x31,
    ELS_FDACDT  =   0x32,
    ELS_NACT    =   0x33,
    ELS_NDACT   =   0x34,
    ELS_QOSR    =   0x40,
    ELS_RVCS    =   0x41,
    ELS_PDISC   =   0x50,
    ELS_FDISC   =   0x51,
    ELS_ADISC   =   0x52,
    ELS_RNC     =   0x53,
    ELS_FARP_REQ=   0x54,
    ELS_FARP_REP=   0x55,
    ELS_RPS     =   0x56,
    ELS_RPL     =   0x57,
    ELS_RPBC    =   0x58,
    ELS_FAN     =   0x60,
    ELS_RSCN    =   0x61,
    ELS_SCR     =   0x62,
    ELS_RNFT    =   0x63,
    ELS_CSR     =   0x68,
    ELS_CSU     =   0x69,
    ELS_LINIT   =   0x70,
    ELS_LSTS    =   0x72,
    ELS_RNID    =   0x78,
    ELS_RLIR    =   0x79,
    ELS_LIRR    =   0x7A,
    ELS_SRL     =   0x7B,
    ELS_SBRP    =   0x7C,
    ELS_RPSC    =   0x7D,
    ELS_QSA     =   0x7E,
    ELS_EVFP    =   0x7F,
    ELS_LKA     =   0x80,
    ELS_AUTH_ELS=   0x90,
}FC_ELS_COMMAND;

#define FIBRE_CHANNEL_COMMAND_INIT {                                                        \
    [ELS_LS_RJT]    =   "ENHANCED_LINK_SERVICE_REJECT",                                     \
    [ELS_LS_ACC]    =   "ENHANCED_LINK_SERVICE_ACCEPT",                                     \
    [ELS_P_LOGIC]   =   "ENAHNCED_LINK_SERVICE_N_PORT_LOGIN",                               \
    [ELS_F_LOGIC]   =   "ENHANCED_LINK_SERVICE_F_PORT_LOGIN",                               \
    [ELS_LOGO]      =   "ENHANCED_LINK_SERVICE_LOGOUT",                                     \
    [ELS_ABTX]      =   "ENHANCED_LINK_SERVICE_ABORT_EXCHANGE",                             \
    [ELS_RCS]       =   "ENHANCED_LINK_SERVICE_READ_CONNECTION_STATUS",                     \
    [ELS_RES]       =   "ENHANCED_LINK_SERVICE_READ_EXCHANGE_STATUS_BLOCK",                 \
    [ELS_RSS]       =   "ENHANCED_LINK_SERVICE_READ_SEQUENCE_STATUS_BLOCK",                 \
    [ELS_RSI]       =   "ENHANCED_LINK_SERVICE_READ_SEQUENCE_INITIATIVE",                   \
    [ELS_ESTS]      =   "ENHANCED_LINK_SERVICE_ESTABLISH_STREAMING",                        \
    [ELS_ESTC]      =   "ENHANCED_LINK_SERVICE_ESTIMATE_CREDIT",                            \
    [ELS_ADVC]      =   "ENHANCED_LINK_SERVICE_ADVISE_CREDIT",                              \
    [ELS_RTV]       =   "ENHANCED_LINK_SERVICE_READ_TIMEOUT_VALUE",                         \
    [ELS_RLS]       =   "ENHANCED_LINK_SERVICE_READ_LINK_ERROR_STATUS_BLOCK",               \
    [ELS_ECHO]      =   "ENHANCED_LINK_SERVICE_ECHO",                                       \
    [ELS_TEST]      =   "ENHANCED_LINK_SERVICE_TEST",                                       \
    [ELS_RRQ]       =   "ENHANCED_LINK_SERVICE_RRQ",                                        \
    [ELS_REC]       =   "ENHANCED_LINK_SERVICE_READ_EXCHANGE_CONCISE",                      \
    [ELS_SRR]       =   "ENHANCED_LINK_SERVICE_SEQUENCE_RETRANSMITION_REQUEST",             \
    [ELS_FPIN]      =   "ENHANCED_LINK_SERVICE_FABRIC_PERFORMANCE_IMPACT_NOTIFICATION",     \
    [ELS_EDC]       =   "ENHANCED_LINK_SERVICE_EXCHANGE_DIAGNOSTIC_CAPABILITIES",           \
    [ELS_RDP]       =   "ENHANCED_LINK_SERVICE_EXCHANGE_DIAGNOSTIC_PARAMETERS",             \
    [ELS_RDF]       =   "ENHANCED_LINK_SERVICE_EXCHANGE_DIAGNOSTIC_FUNCTIONS",              \
    [ELS_PRLI]      =   "ENHANCED_LINK_SERVICE_PROCESS_LOGN",                               \
    [ELS_PRLO]      =   "ENHANCED_LINK_SERVICE_PROCESS_LOGOUT",                             \
    [ELS_SCN]       =   "ENHANCED_LINK_SERVICE_STATE_CHANGE_NOTIFICATION",                  \
    [ELS_TPLS]      =   "ENHANCED_LINK_SERVICE_PROCESS_LOGIN_STATE",                        \
    [ELS_TPRLO]     =   "ENHANCED_LINK_SERVICE_PROCESS_THIRD_PARTY_PRROCESS_LOGOUT",        \
    [ELS_LCLM]      =   "ENHANCED_LINK_SERVICE_LOGIN_CONTROL_LIST_MANAGEMENT",              \
    [ELS_GAID]      =   "ENHANCED_LINK_SERVICE_GET_ALIAS_ID",                               \
    [ELS_FACT]      =   "ENHANCED_LINK_SERVICE_FABRIC_ACTIVATE_ALIAS_ID",                   \
    [ELS_FDACDT]    =   "ENHANCED_LINK_SERVICE_FABRIC_DEACTIVATE_ALIAS_ID",                 \
    [ELS_NACT]      =   "ENHANCED_LINK_SERVICE_N_PORT_ACTIVATE_ALIAS_ID",                   \
    [ELS_NDACT]     =   "ENHANCED_LINK_SERVICE_N_PORT_DEACTIVATE_ALIAS_ID",                 \
    [ELS_QOSR]      =   "ENHANCED_LINK_SERVICE_QUALITY_OF_SERVICE_REQUEST",                 \
    [ELS_RVCS]      =   "ENHANCED_LINK_SERVICE_READ_VIRTUAL_CIRCUIT_STATUS",                \
    [ELS_PDISC]     =   "ENHANCED_LINK_SERVICE_N_PORT_SERIVCE_PARAM",                       \
    [ELS_FDISC]     =   "ENHANCED_LINK_SERVICE_F_PORT_SERVICE_PARAM",                       \
    [ELS_ADISC]     =   "ENHANCED_LINK_SERVICE_DISCOVER_ADDRESS",                           \
    [ELS_RNC]       =   "ENHANCED_LINK_SERVICE_REPORT_NODE_CAP",                            \
    [ELS_FARP_REQ]  =   "ENHANCED_LINK_SERVICE_FC_ARP_REQUEST",                             \
    [ELS_FARP_REP]  =   "ENHANCED_LINK_SERVICE_FC_ARP_REPLY",                               \
    [ELS_RPS]       =   "ENHANCED_LINK_SERVICE_READ_PORT_STATUS_BLOCK",                     \
    [ELS_RPL]       =   "ENHANCED_LINK_SERVICE_READ_PORT_LIST",                             \
    [ELS_RPBC]      =   "ENHANCED_LINK_SERVICE_READ_PORT_BUFFER_CONDITION",                 \
    [ELS_FAN]       =   "ENHANCED_LINK_SERVICE_FABRIC_ADDRESS_NOTIFICATION",                \
    [ELS_RSCN]      =   "ENHANCED_LINK_SERVICE_REGISTERED_STATE_CHANGE_NOTIFICATION",       \
    [ELS_SCR]       =   "ENHANCED_LINK_SERVICE_STATE_CHANGE_REGISTRATION",                  \
    [ELS_RNFT]      =   "ENHANCED_LINK_SERVICE_REPORT_NODE_FC4",                            \
    [ELS_CSR]       =   "ENHANCED_LINK_SERVICE_CLOCK_SYNC_REQUEST",                         \
    [ELS_CSU]       =   "ENHANCED_LINK_SERVICE_CLOCK_SYNC_UPDATE",                          \
    [ELS_LINIT]     =   "ENHANCED_LINK_SERVICE_LOOP_INITIALIZE",                            \
    [ELS_LSTS]      =   "ENHANCED_LINK_SERVICE_LOOP_STATUS",                                \
    [ELS_RNID]      =   "ENHANCED_LINK_SERVICE_REQUEST_NODE_ID",                            \
    [ELS_RLID]      =   "ENHANCED_LINK_SERVICE_REGISTERED_LINK_INCIDENT",                   \
    [ELS_LIRR]      =   "ENHANCED_LINK_SERVICE_LINK_INCEDENT_RECORD_REGISTRATION",          \
    [ELS_SRL]       =   "ENHANCED_LINK_SERVICE_SCAN_REMOTE_LOOP",                           \
    [ELS_SBRP]      =   "ENHANCED_LINK_SEVICE_SET_BIT_ERROR_REPORTING_PARAMETERS",          \
    [ELS_RPSC]      =   "ENHANCED_LINK_SEVICE_REPORT_SPEED_CAPABILITIES",                   \
    [ELS_QSA]       =   "ENHANCED_LINK_SEVICE_QUERY_SECURITY_ATTRIBUTES",                   \
    [ELS_EVFP]      =   "ENHANCED_LINK_SEVICE_EXCHANGE_VIRTUAL_FABRICS_PARAMETERS",         \
    [ELS_LKA]       =   "ENHANCED_LINK_SEVICE_LINK_KEEP_ALIVE",                             \
    [ELS_AUTH_ELS]  =   "ENHANCED_LINK_SEVICE_AUTHENTICATE_ELS",                            \
}

typedef struct _FC_ELS_LS_ACC_PAYLOAD{
    uint8_t LaCmd;
    uint8_t LaReserved;
}FC_ELS_LS_ACC_PAYLOAD, * PFC_ELS_LS_ACC_PAYLOAD;

typedef struct _FC_ELS_LS_REJECT_PAYLOAD{
    uint8_t ErCmd;
    uint8_t ErReserved[4];
    uint8_t ErReason;
    uint8_t ErEplanation;
    uint8_t ErVendor;
}FC_ELS_LS_REJECT_PAYLOAD, * PFC_ELS_LS_REJECT_PAYLOAD;

#define ELS_REJECT_REASON_NONE                  0x00
#define ELS_REJECT_REASON_INVALIDATE            0x01
#define ELS_REJECT_REASON_LOGICAL_ERROR         0x03
#define ELS_REJECT_REASON_BUSY                  0x05
#define ELS_REJECT_REASON_PROTOCOL_ERROR        0x07
#define ELS_REJECT_REASON_COMMAND_UNABLE        0x09
#define ELS_REJECT_REASON_UNSUPORTED            0x0B
#define ELS_REJECT_REASON_INPROGRESS            0x0E
#define ELS_REJECT_REASON_FIP_ERROR             0x20
#define ELS_REJECT_REASON_VENDOR_ERROR          0xFF

#define ELS_REJECT_EXPLANATION_NONE                                 0x00
#define ELS_REJECT_EPLANATION_SERVICE_PARAM_ERROR                   0x01
#define ELS_REJECT_EPLANATION_SPP_ICTL_ERROR                        0x03
#define ELS_REJECT_EPLANATION_BAD_ASSOCIATION_HEADER                0x11
#define ELS_REJECT_EPLANATION_ASSOCIATION_HEADER_REQUIRED           0x13
#define ELS_REJECT_EPLANATION_INVALID_ORIGINATOR_SID                0x15
#define ELS_REJECT_EPLANATION_INVALID_OXID_RXID                     0x17
#define ELS_REJECT_EPLANATION_REQUEST_ALREADY_IN_PROGRESS           0x19
#define ELS_REJECT_EPLANATION_N_PORT_LOGIN_REQUIRED                 0x1E
#define ELS_REJECT_EPLANATION_INSIFFICENT_RESOURCES                 0x29
#define ELS_REJECT_EPLANATION_UNABLE_TO_SUPPLY_DATA                 0x2A
#define ELS_REJECT_EPLANATION_UNSUPORTED_REQUEST                    0x2C
#define ELS_REJECT_EPLANATION_INVALID_LENGTH                        0x2D
#define ELS_REJECT_EPLANATION_NOT_NEIGHBOR                          0x62

#define ELS_DESCRIPTOR_TAG_REQUEST_INFORMATION                      0x00000001
#define ELS_DESCRIPTOR_TAG_FAULT_CAPABILITY                         0x0001000D
#define ELS_DESCRIPTOR_TAG_CG_SIGNAL_CAPABILITY                     0x0001000F
#define ELS_DESCRIPTOR_TAG_LINK_INTEGRITY                           0x00020001
#define ELS_DESCRIPTOR_TAG_DELIVERY_NOTIFICATION                    0x00020002
#define ELS_DESCRIPTOR_TAG_PEER_CONGEST_NOTIFICATION                0x00020003
#define ELS_DESCRIPTOR_TAG_CONGEST_NOTIFICATION                     0x00020004
#define ELS_DESCRIPTOR_TAG_FPIN_REGISTRATION                        0x00030001

#define FIBRE_CHANNEL_TLV_DESCRIPTOR_TAG_INIT {                                         \
    {ELS_DESCRIPTOR_TAG_REQUEST_INFORMATION,        "Request Information"},             \
    {ELS_DESCRIPTOR_TAG_FAULT_CAPABILITY,           "Fault Capability"},                \
    {ELS_DESCRIPTOR_TAG_CG_SIGNAL_CAPABILITY,       "Congestion Signal Capability"},    \
    {ELS_DESCRIPTOR_TAG_LINK_INTEGRITY,             "Link Integrity Notification"},     \
    {ELS_DESCRIPTOR_TAG_DELIVERY_NOTIFICATION,      "Delivery Notification"},           \
    {ELS_DESCRIPTOR_TAG_PEER_CONGEST_NOTIFICATION,  "Peer Congestion Notification"},    \
    {ELS_DESCRIPTOR_TAG_CONGEST_NOTIFICATION,       "Congestion Notification"},         \
    {ELS_DESCRIPTOR_TAG_FPIN_REGISTRATION,          "FPIN Registration"},               \
}

typedef struct _FIBRE_CHANNEL_TLV_DESCRIPTOR{
    uint32_t        DescriptorTag;      //Big Endian
    uint32_t        DescriptorLength;   //BigEndian
    uint8_t         DescriptorValue[];
}FIBRE_CHANNEL_TLV_DESCRIPTOR, * PFIBRE_CHANNEL_TLV_DESCRIPTOR;



#define FIBRE_CHANNEL_TLV_DESCRIPTOR_HEADER_SIZE                     sizeof(FIBRE_CHANNEL_TLV_DESCRIPTOR)
#define FIBRE_CHANNEL_TLV_DESCRIPTOR_LENGTH_FROM_SIZE(Descriptor)   (sizeof(Descriptor) - FIBRE_CHANNEL_TLV_DESCRIPTOR_HEADER_SIZE)

static inline uint64_t FIBRE_CHANNEL_TLV_DESCRIPTOR_SIZE_FROM_LENGTH(PFIBRE_CHANNEL_TLV_DESCRIPTOR Tlv){
    uint32_t Tmp = Tlv->DescriptorLength;
    uint64_t Result = (uint64_t)LouBeToLe32(Tmp);
    Result += FIBRE_CHANNEL_TLV_DESCRIPTOR_HEADER_SIZE; 
    return (uint64_t)Result;
}

static inline void* LouFibreChannelTlvWalkListkNext(void* Descriptor){
    PFIBRE_CHANNEL_TLV_DESCRIPTOR    Tlv = (PFIBRE_CHANNEL_TLV_DESCRIPTOR)Descriptor;
    return (void*)((uint64_t)Descriptor + FIBRE_CHANNEL_TLV_DESCRIPTOR_SIZE_FROM_LENGTH(Tlv));
}

typedef struct _FIBRE_CHANNEL_LSRI_DESCRIPTOR{
    uint32_t DescriptorTag;     //big endian
    uint32_t DescriptorLength;  //big Endian
    struct {
        uint8_t Commad;
        uint8_t Bytes[3];
    } RequestDWORD;
}FIBRE_CHANNEL_LSRI_DESCRIPTOR, * PFIBRE_CHANNEL_LSRI_DESCRIPTOR;

typedef struct _FIBRE_CHANNEL_ELS_CSP{
    uint8_t     SupportedVersionHigh;
    uint8_t     SupportedVersionLow;
    uint16_t    BtbCredits;             //BigEndian
    uint16_t    CommonFeatures;         //BigEndian
    uint16_t    BtbData;
    union{
        struct{
            uint16_t TCS;               //big endian
            uint16_t RelitiveOffset;    //Big Endian
        }PLogicAcc;
        struct {
            uint32_t ResourceAllocTimeout; //big endian
        }FLogicAcc;
    }SpUnion;
    uint32_t ErrorDetectTimeout;        //Big Endian
}FIBRE_CHANNEL_ELS_CSP, * PFIBRE_CHANNEL_ELS_CSP;

#define FIBRE_CHANNEL_SP_BTB_DATA_BITS  0xFFF

#define FIBRE_CHANNEL_SP_MINIMUM_MAXIMUM_PAYLOAD   FIBRE_CHANNEL_MINIMUM_MAXIMUM_PAYLOAD
#define FIBRE_CHANNEL_SP_MAXIMUM_MAXIMUM_PAYLOAD   FIBRE_CHANNEL_MAXIMUM_MAXIMUM_PAYLOAD

#define FIBRE_CHANNEL_SP_FEATURE_NPIV           0x8000
#define FIBRE_CHANNEL_SP_FEATURE_CIRO
#define FIBRE_CHANNEL_SP_FEATURE_CLAD
#define FIBRE_CHANNEL_SP_FEATURE_RAND
#define FIBRE_CHANNEL_SP_FEATURE_VAL
#define FIBRE_CHANNEL_SP_FEATURE_NPIV_ACC
#define FIBRE_CHANNEL_SP_FEATURE_FPORT
#define FIBRE_CHANNEL_SP_FEATURE_ABB
#define FIBRE_CHANNEL_SP_FEATURE_EDTR
#define FIBRE_CHANNEL_SP_FEATURE_MCAST
#define FIBRE_CHANNEL_SP_FEATURE_BCAST
#define FIBRE_CHANNEL_SP_FEATURE_HUNT
#define FIBRE_CHANNEL_SP_FEATURE_SIMP
#define FIBRE_CHANNEL_SP_FEATURE_SEC
#define FIBRE_CHANNEL_SP_FEATURE_CSYN
#define FIBRE_CHANNEL_SP_FEATURE_RTTOV
#define FIBRE_CHANNEL_SP_FEATURE_HALF
#define FIBRE_CHANNEL_SP_FEATURE_SEQC
#define FIBRE_CHANNEL_SP_FEATURE_PAYL

typedef struct _FIBRE_CHANNEL_ELS_CSSP{
    uint16_t CpClass;   //BigEndian
    uint16_t CpInit;    
    uint16_t CpRecip;   
    uint16_t CpRdfs;
    uint16_t CpConSeq;
    uint16_t CpEeCredit;
    uint8_t  CpReserved1;
    uint8_t  CpOpenSequence;
    uint8_t  CpReserved[2];
}FIBRE_CHANNEL_ELS_CSSP, * PFIBRE_CHANNEL_ELS_CSSP;

#define FIBRE_CHANNEL_CPC_VALID     0x8000
#define FIBRE_CHANNEL_CPC_IMIX      0x4000
#define FIBRE_CHANNEL_CPC_SEQUENCE  0x0800
#define FIBRE_CHANNEL_CPC_CAMP      0x0200
#define FIBRE_CHANNEL_CPC_PRIORITY  0x0080

#define FIBRE_CHANNEL_CPI_CSYN  0x0010

#define FIBRE_CHANNEL_CPR_CSYN  0x0008

//big endian structure
typedef struct _FIBRE_CHANNEL_ELS_SPP{
    uint8_t SppType;
    uint8_t SppTypeExtention;
    uint8_t SppFlags;
    uint8_t SppReserved;
    uint32_t SppOriginPa;
    uint32_t SppRespPa;
    uint32_t SppParameters;
}FIBRE_CHANNEL_ELS_SPP, * PFIBRE_CHANNEL_ELS_SPP;

#define FIBRE_CHANNEL_OPA_VALID     0x80
#define FIBRE_CHANNEL_RPA_VALID     0x40
#define FIBRE_CHANNEL_EST_IMG_PAIR  0x20
#define FIBRE_CHANNEL_RESP_BITS     0x0F

#define FIBRE_CHANNEL_SSP_RESPONCE_ACKNOWLEDGE      1
#define FIBRE_CHANNEL_SSP_RESPONCE_RESOURCES        2
#define FIBRE_CHANNEL_SSP_RESPONCE_INITIALIZATION   3
#define FIBRE_CHANNEL_SSP_RESPONCE_NO_PA            4
#define FIBRE_CHANNEL_SSP_RESPONCE_CONFIGURATION    5
#define FIBRE_CHANNEL_SSP_RESPONCE_CONDIFIONALLY    6
#define FIBRE_CHANNEL_SSP_RESPONCE_MULTIPLE         7
#define FIBRE_CHANNEL_SSP_RESPONCE_INVALID          8

//big endian struct
typedef struct _FIBRE_CHANNEL_ELS_RRQ{
    uint8_t     RrqCommand;
    uint8_t     RrqZero[3];
    uint8_t     RrqReserved;
    uint8_t     RrqSID[3];
    uint16_t    RrqOxID;
    uint16_t    RrqRxID;
}FIBRE_CHANNEL_ELS_RRQ, * PFIBRE_CHANNEL_ELS_RRQ;

//big endian struct
typedef struct _FIBRE_CHANNEL_ELS_REC{
    uint8_t     RecCommand;
    uint8_t     RecZero[3];
    uint8_t     RecReserved;
    uint8_t     RecSID[3];
    uint16_t    RecOxID;
    uint16_t    RecRxID;
}FIBRE_CHANNEL_ELS_REC, * PFIBRE_CHANNEL_ELS_REC;

//big endian struct
typedef struct _FIBRE_CHANNEL_ELS_REC_ACC{
    uint8_t     RecaCommand;
    uint8_t     RecaZero[3];
    uint16_t    RecaOxID;
    uint16_t    RecaRxID;
    uint8_t     RecaReserved1;
    uint8_t     RecaOfID[3];
    uint8_t     RecaReserved2;
    uint8_t     RecaRfID[3];
    uint32_t    RecaFcValue;
    uint32_t    RecaEStatus;
}FIBRE_CHANNEL_ELS_REC_ACC, * PFIBRE_CHANNEL_ELS_REC_ACC;



#ifdef __cplusplus
}
#endif
#endif //_FIBRE_CHANNEL_ELS_H