#ifndef _FIBRE_CHANNEL_ELS_H
#define _FIBRE_CHANNEL_ELS_H

#pragma pack(push,1)

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
#define ELS_REJECT_EPLANATION_REQUEST_ALREADYPROGRESS           0x19
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

//big endian struct 
typedef struct _FIBRE_CHANNEL_ELS_PROCESS_LOGIN{
    uint8_t     ProcessLoginCommand;
    uint8_t     ProcessLoginSppLength;
    uint16_t    ProcessLoginLength;
}FIBRE_CHANNEL_ELS_PROCESS_LOGIN, * PFIBRE_CHANNEL_ELS_PROCESS_LOGIN;

//big Endian Struct
typedef struct _FIBRE_CHANNEL_ELS_PROCESS_LOGOUT{
    uint8_t     ProcessLogoutCommand;
    uint8_t     ProcessLogoutObsolete;
    uint16_t    ProcessLogoutLength;
}FIBRE_CHANNEL_ELS_PROCESS_LOGOUT, * PFIBRE_CHANNEL_ELS_PROCESS_LOGOUT;

//big Endian
typedef struct _FIBRE_CHANNEL_ELS_ADISC{
    uint8_t     AdiscCommand;
    uint8_t     AdiscReserved1[3];
    uint8_t     AdiscReserved2;
    uint8_t     AdiscHardAddress[3];
    uint64_t    AdiscWwpn;
    uint64_t    AdiscWwnn;
    uint8_t     AdiscReserved3;
    uint8_t     AdiscPortID[3];
}FIBRE_CHANNEL_ELS_ADISC, * PFIBRE_CHANNEL_ELS_ADISC;

//big endian
typedef struct _FIBRE_CHANNEL_ELS_FABRIC_LOGOUT{
    uint8_t     FabricLogoutCommand;
    uint8_t     FabricLogoutZero[3];
    uint8_t     FabricLogoutReserved;
    uint8_t     FabricLogoutNPortID[3];
    uint64_t    FabricLogoutNPortWwn;
}FIBRE_CHANNEL_ELS_FABRIC_LOGOUT, * PFIBRE_CHANNEL_ELS_FABRIC_LOGOUT;

//Big Endian
typedef struct _FIBRE_CHANNEL_ELS_READ_TIMEOUT_VALUE_ACC{
    uint8_t     ReadTimeValueCommand;
    uint8_t     ReadTimeValueZero[3];
    uint32_t    ReadTimeValueResourceAllocTimeValue;
    uint32_t    ReadTimeValueTimeoutQualifier;
}FIBRE_CHANNEL_ELS_READ_TIMEOUT_VALUE_ACC, * PFIBRE_CHANNEL_ELS_READ_TIMEOUT_VALUE_ACC;

#define FIBRE_CHANNEL_ELS_READ_TIME_VALUE_ED_RESOLUTION (1 << 26)
#define FIBRE_CHANNEL_ELS_READ_TIME_VALUE_RT_TIMEOUTVAL (1 << 19)

//big endian
typedef struct _FIBRE_CHANNEL_ELS_STATE_CHANGE_REGISTRATION{
    uint8_t Command;
    uint8_t Reserved[6];
    uint8_t RegistrationFunction;
}FIBRE_CHANNEL_ELS_STATE_CHANGE_REGISTRATION, * PFIBRE_CHANNEL_ELS_STATE_CHANGE_REGISTRATION;

#define FIBRE_CHANNEL_ELS_STATE_CHANGE_REGISTRATION_FABRIC      1
#define FIBRE_CHANNEL_ELS_STATE_CHANGE_REGISTRATION_NPORT       2
#define FIBRE_CHANNEL_ELS_STATE_CHANGE_REGISTRATION_FULL        3
#define FIBRE_CHANNEL_ELS_STATE_CHANGE_REGISTRATION_CLEAR       255

typedef struct _FIBRE_CHANNEL_ELS_REGISTERED_STATE_CHANGE_NOTIFICATION{
    uint8_t     Command;
    uint8_t     PageLength;
    uint16_t    PayloadLength;
}FIBRE_CHANNEL_ELS_REGISTERED_STATE_CHANGE_NOTIFICATION, * PFIBRE_CHANNEL_ELS_REGISTERED_STATE_CHANGE_NOTIFICATION;

typedef struct _FIBRE_CHANNEL_ELS_RSCN_PAGE{
    uint8_t     PageFlags;
    uint8_t     FabricID[3];
}FIBRE_CHANNEL_ELS_RSCN_PAGE, * PFIBRE_CHANNEL_ELS_RSCN_PAGE;

#define ELS_RSCN_EV_QUALIFIER_BIT       2
#define ELS_RSCN_EV_QUALIFIER_BITS      0x0F
#define ELS_RSCN_ADDRESS_FORMAT_BIT     0
#define ELS_RSCN_ADDRESS_FORMAT_BITS    0x03

#define ELS_EV_QUALIFIER_NONE                       0
#define ELS_EV_QUALIFIER_NAME_SERVICE_OBJECT        1
#define ELS_EV_QUALIFIER_PORT_ATTRIBUTE             2 
#define ELS_EV_QUALIFIER_SERVICE_OBJECT             3
#define ELS_EV_QUALIFIER_SWITCH_CONFIGURATION       4
#define ELS_EV_QUALIFIER_REMOVED_OBJECT             5

#define ELS_ADDRESS_FORMAT_PORT_ADDRESS             0
#define ELS_ADDRESS_FORMAT_AREA_ADDRESS             1
#define ELS_ADDRESS_FORMAT_DOMAIN_ADDRESS           2
#define ELS_ADDRESS_FORMAT_FABRIC_ADDRESS_CHANGE    3

typedef struct _FIBRE_CHANNEL_REQUEST_NODE_ID{
    uint8_t     Command;
    uint8_t     Reserved1[3];
    uint8_t     Format;
    uint8_t     Reserved2[3];
}FIBRE_CHANNEL_REQUEST_NODE_ID, * PFIBRE_CHANNEL_REQUEST_NODE_ID;

#define ELS_REQUEST_NODE_ID_FORMAT_NONE     0
#define ELS_REQUEST_NODE_ID_FORMAT_GENERAL  0xDF

typedef struct _FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_RESPONCE{
    uint8_t     Command;
    uint8_t     Reserved1[3];
    uint8_t     DataFormat;
    uint8_t     CommonIDLength;
    uint8_t     Reserved2;
    uint8_t     SpecificIDLength;
}FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_RESPONCE, * PFIBRE_CHANNEL_ELS_REQUEST_NODE_ID_RESPONCE;

//big endian
typedef struct _FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_COMMAND_ID{
    uint64_t    Wwpn;
    uint64_t    Wwnn;
}FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_COMMAND_ID, * PFIBRE_CHANNEL_ELS_REQUEST_NODE_ID_COMMAND_ID;

//big endian
typedef struct _FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_GENERIC{
    uint8_t     VendorID[16];
    uint32_t    AType;
    uint32_t    PhysicalPort;
    uint32_t    AttachedNodeCount;
    uint8_t     NodeManagement;
    uint8_t     IpVersion;
    uint16_t    ProtocolPort;
    uint32_t    IpAddress[4];
    uint8_t     Reserved[2];
    uint16_t    VendorSpecific;
}FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_GENERIC, * PFIBRE_CHANNEL_ELS_REQUEST_NODE_ID_GENERIC;

#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_UNKOWN      0x01
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_OTHER       0x02
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_HUB         0x03
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_SWITCH      0x04
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_GATEWAY     0x05
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_CONV        0x06
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_HBA         0x07
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_PROXY       0x08
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_STORAGE     0x09
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_HOST        0x0A
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_SUB_SYSTEM  0x0B
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_ACCESS      0x0E
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_NAS         0x11
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_BRIDGE      0x12
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_VIRTUAL     0x13
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MULTIFUNC   0xFF
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_HUB      1 << 31
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_SW       1 << 30
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_GW       1 << 29
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_ST       1 << 28
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_HOST     1 << 27
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_SUB      1 << 26
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_ACC      1 << 25
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_WDM      1 << 24
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_NAS      1 << 23
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_BR       1 << 22
#define FIBRE_CHANNEL_ELS_REQUEST_NODE_ID_ATYPE_MF_VIRT     1 << 21

#define ELS_REQUEST_NODE_ID_MANAGEMENT_SNMP     0
#define ELS_REQUEST_NODE_ID_MANAGEMENT_TELNET   1
#define ELS_REQUEST_NODE_ID_MANAGEMENT_HTTP     2
#define ELS_REQUEST_NODE_ID_MANAGEMENT_HTTPS    3
#define ELS_REQUEST_NODE_ID_MANAGEMENT_XML      4

#define ELS_REQUEST_NODE_ID_IP_VERSION_NONE     0
#define ELS_REQUEST_NODE_ID_IP_VERSION_V4       1
#define ELS_REQUEST_NODE_ID_IP_VERSION_V6       2

//big endian struct
typedef struct _FIBRE_CHANNEL_ELS_READ_PORT_LIST{
    uint8_t     Command;
    uint8_t     Reserved1[5];
    uint16_t    MaxSize;
    uint8_t     Reserved2;
    uint8_t     Index[3];
}FIBRE_CHANNEL_ELS_READ_PORT_LIST, * PFIBRE_CHANNEL_ELS_READ_PORT_LIST;

//big endian struct 
typedef struct _FIBRE_CHANNEL_ELS_PORT_NUMBER_BLOCK{
    uint32_t    PhysicalPortNumber;
    uint8_t     Reserved;
    uint8_t     PortID[3];
    uint64_t    Wwpn;
}FIBRE_CHANNEL_ELS_PORT_NUMBER_BLOCK, * PFIBRE_CHANNEL_ELS_PORT_NUMBER_BLOCK;

//Big Endian Struct
typedef struct _FIBRE_CHANNEL_ELS_READ_PORT_LIST_RESPONCE{
    uint8_t     Command;
    uint8_t     Reserved1;
    uint16_t    PayloadLength;
    uint8_t     Reserved2;
    uint8_t     ListLength[3];
    uint8_t     Reserved3;
    uint8_t     Index[3];
}FIBRE_CHANNEL_ELS_READ_PORT_LIST_RESPONCE, * PFIBRE_CHANNEL_ELS_READ_PORT_LIST_RESPONCE;

//Big Endian
typedef struct _FIBRE_CHANNEL_ELS_LINK_ERROR_STATUS_BLOCK{
    uint32_t    LinkFail;
    uint32_t    SyncLoss;
    uint32_t    SingnalLoss;
    uint32_t    PrimativeError;
    uint32_t    InvalidWordCount;
    uint32_t    InvalidCrcCount;
}FIBRE_CHANNEL_ELS_LINK_ERROR_STATUS_BLOCK, * PFIBRE_CHANNEL_ELS_LINK_ERROR_STATUS_BLOCK;

//Big Endian Struct
typedef struct _FIBRE_CHANNEL_ELS_READ_PORT_STATUS_BLOCK_REQUEST{
    uint8_t     Command;
    uint8_t     Reserved2[2];
    uint8_t     Flags;
    uint64_t    PortSelect;
}FIBRE_CHANNEL_ELS_READ_PORT_STATUS_BLOCK_REQUEST, * PFIBRE_CHANNEL_ELS_READ_PORT_STATUS_BLOCK_REQUEST;

#define FIBRE_CHANNEL_READ_PORT_STATUS_D_ID                     0x00
#define FIBRE_CHANNEL_READ_PORT_STATUS_PHYSICAL_PORT_NUMBER     0x01
#define FIBRE_CHANNEL_READ_PORT_STATUS_WWPN                     0x02

//Big Endian Struct
typedef struct _FIBRE_CHANNEL_ELS_READ_PORT_STATUS_BLOCK_RESPONCE{
    uint8_t     Command; 
    uint8_t     Reserved1[2];
    uint8_t     Flags;
    uint8_t     Reserved2[2];
    uint16_t    Status;
}FIBRE_CHANNEL_ELS_READ_PORT_STATUS_BLOCK_RESPONCE, * PFIBRE_CHANNEL_ELS_READ_PORT_STATUS_BLOCK_RESPONCE;

#define FIBRE_CHANNEL_ELS_READ_PORT_STATUS_LPORT_EXTENTION  0x01

#define FIBRE_CHANNEL_ELS_READ_PORT_STATUS_POINT_TO_POINT   1 << 5
#define FIBRE_CHANNEL_ELS_READ_PORT_STATUS_LOOP             1 << 4
#define FIBRE_CHANNEL_ELS_READ_PORT_STATUS_FABRIC           1 << 3
#define FIBRE_CHANNEL_ELS_READ_PORT_STATUS_NO_SIGNAL        1 << 2
#define FIBRE_CHANNEL_ELS_READ_PORT_STATUS_NO_SYNX          1 << 1
#define FIBRE_CHANNEL_ELS_READ_PORT_STATUS_RESET            1

typedef struct _FIBRE_CHANNEL_ELS_LINK_INCEDENT_RECORD_REQUEST{
    uint8_t     Command;    
    uint8_t     Reserved1[3];
    uint8_t     Function;
    uint8_t     Format;
    uint8_t     Reserved2[2];
}FIBRE_CHANNEL_ELS_LINK_INCEDENT_RECORD_REQUEST, * PFIBRE_CHANNEL_ELS_LINK_INCEDENT_RECORD_REQUEST;

#define ELS_LINK_INCEDENT_RECORD_REQUEST_SET_CONDITIONAL        0x01
#define ELS_LINK_INCEDENT_RECORD_REQUEST_SET_UNCONDITIONAL      0x02
#define ELS_LINK_INCEDENT_RECORD_REQUEST_CLEAR                  0xFF

typedef struct _FIBRE_CHANNEL_SCAN_REMOTE_LIST_LOOP_REQUEST{
    uint8_t     Command;
    uint8_t     Reserved[3];
    uint8_t     Flags;
    uint8_t     FlagParameter[3];
}FIBRE_CHANNEL_SCAN_REMOTE_LIST_LOOP_REQUEST, * PFIBRE_CHANNEL_SCAN_REMOTE_LIST_LOOP_REQUEST;

#define FIBRE_CHANNEL_ELS_SCAN_REMOTE_LIST_ALL                  0x00
#define FIBRE_CHANNEL_ELS_SCAN_REMOTE_LIST_ONE                  0x01
#define FIBRE_CHANNEL_ELS_SCAN_REMOTE_LIST_ENABLE_PERIODIC      0x02
#define FIBRE_CHANNEL_ELS_SCAN_REMOTE_LIST_DISABLE_PERIODIC     0x03

typedef struct _FIBRE_CHANNEL_READ_LINK_ERROR_STATUS_BLOCK_REQUEST{
    uint8_t     Command;
    uint8_t     Reserved1[4];
    uint8_t     PortID[3];
}FIBRE_CHANNEL_READ_LINK_ERROR_STATUS_BLOCK_REQUEST, * PFIBRE_CHANNEL_READ_LINK_ERROR_STATUS_BLOCK_REQUEST;

typedef struct _FIBRE_CHANNEL_ELS_REGISTERD_LINK_INCIDENT_REPORT{
    uint8_t     Command;
    uint8_t     Reserved[3];
    uint8_t     Format;
    uint8_t     CommonLinkIncidentRecordLength;
    uint8_t     CommonLinkIncidentDescriptorLength;
    uint8_t     SpecificIncidentRecordLength;
}FIBRE_CHANNEL_ELS_REGISTERD_LINK_INCIDENT_REPORT, * PFIBRE_CHANNEL_ELS_REGISTERD_LINK_INCIDENT_REPORT;

typedef struct _FIBRE_CHANNEL_COMMON_LINK_INCIDENT_RECORD_DATA{
    uint64_t    Wwpn;
    uint64_t    Wwnn;
    uint8_t     PortType;
    uint8_t     PortID[3];
    uint64_t    ConnectedWwpn;
    uint64_t    ConnectedWwnn;
    uint64_t    FabricName;
    uint32_t    PhysicalPort;
    uint32_t    TransactionID;
    uint8_t     Reserved[3];
    uint8_t     TimeStampFormat;
    uint64_t    TimeStamp;
}FIBRE_CHANNEL_COMMON_LINK_INCIDENT_RECORD_DATA, * PFIBRE_CHANNEL_COMMON_LINK_INCIDENT_RECORD_DATA;

#define ELS_CLIR_TIME_STAMP_VALUE_UNKOWN                0
#define ELS_CLIR_TIME_STAMP_VALUE_SECOND_AND_FRACTION   1
#define ELS_CLIR_TIME_STAMP_VALUE_CLOCK_SYNC_UPDATE     2

typedef struct _FIBRE_CHANNEL_ELS_COMMON_LINK_INCIDENT_DESCRIPTOR{
    uint8_t     IncidentQualifier;
    uint8_t     IncidentCode;
    uint16_t    DomainAreaOfISL;
}FIBRE_CHANNEL_ELS_COMMON_LINK_INCIDENT_DESCRIPTOR, * PFIBRE_CHANNEL_ELS_COMMON_LINK_INCIDENT_DESCRIPTOR;

#define ELS_CLID_SWITCH                 0x20
#define ELS_CLID_E_PORT                 0x10
#define ELS_CLID_SEVERITY_BITS          0x0C
#define ELS_CLID_SEVERITY_INFO          0x00
#define ELS_CLID_SEVERITY_NOP           0x08
#define ELS_CLID_SEVERITY_DEGRADED      0x04
#define ELS_CLID_LASER_DISC             0x02
#define ELS_CLID_FRU_FORMATED           0x01

#define ELS_CLID_IC_IMPLICIT            1
#define ELS_CLID_IC_BIT_ERROR           2
#define ELS_CLID_IC_LOSS_OF_FOO         3
#define ELS_CLID_IC_NOP_PRIM_SEQ        4
#define ELS_CLID_IC_PRIM_SEQ_TO         5
#define ELS_CLID_IC_INVAL_PRIM_SEQ      6
#define ELS_CLID_IC_LOOP_TO             7
#define ELS_CLID_IC_LIP                 8

#define FPIN_LI_UNKOWN              0x00
#define FPIN_LI_LINK_FAILURE        0x01
#define FPIN_LI_LOSS_OF_SYNC        0x02
#define FPIN_LI_LOSS_OF_SIGNAL      0x03
#define FPIN_LI_PRIM_SEQ_ERR        0x04
#define FPIN_LI_INVALID_TX_WD       0x05
#define FPIN_LI_INVALID_CRC         0x06
#define FPIN_LI_DEVICE_SPEC         0x0F

#define FIBRE_CHANNEL_LI_EVENT_TYPES_INIT {                 \
    {FPIN_LI_UNKOWN,        "Unkown"},                      \
    {FPIN_LI_LINK_FAILURE,  "Link Failure"},                \
    {FPIN_LI_LOSS_OF_SYNC,  "Loss Of Sync"},                \
    {FPIN_LI_LOSS_OF_SIGNAL,"Loss Of Signal"},              \
    {FPIN_LI_PRIM_SEQ_ERR,  "Primitive Sequnce Error"},     \
    {FPIN_LI_INVALID_TX_WD, "Invalid Transmition Word"},    \
    {FPIN_LI_INVALID_CRC,   "Invalid Crc"},                 \
    {FPIN_LI_DEVICE_SPEC,   "Device Specific"},             \
}

#define FPIN_DELIVERY_UNKOWN            0x00
#define FPIN_DELIVERY_TIMEOUT           0x01
#define FPIN_DELIVERY_UNABLE_TO_ROUTE   0x02
#define FPIN_DELIVERY_DEVICE_SPEC       0x0F

#define FIBRE_CHANNEL_DELIVERY_EVENT_TYPES_INIT {               \
    {FPIN_DELIVERY_UNKOWN,              "Unkown"},              \
    {FPIN_DELIVERY_TIMEOUT,             "Timeout"},             \
    {FPIN_DELIVERY_UNABLE_TO_ROUTE,     "Unable To Route"},     \
    {FPIN_DELIVERY_DEVICE_SPEC,         "Device Specific"},     \
}

#define FPIN_CONGESTION_CLEAR               0x00
#define FPIN_CONGESTION_LOST_CREDIT         0x01
#define FPIN_CONGESTION_CREDIT_STALL        0x02
#define FPIN_CONGESTION_OVER_SUBSCIPTION    0x03
#define FPIN_CONGESTION_DEVICE_SPECIFIC     0x0F

#define FIBRE_CHANNEL_CONGESTED_EVENT_TYPE_INIT {               \
    {FPIN_CONGESTION_CLEAR,             "Clear"},               \
    {FPIN_CONGESTION_LOST_CREDIT,       "Lost Credit"},         \
    {FPIN_CONGESTION_CREDIT_STALL,      "Credit Stall"},        \
    {FPIN_CONGESTION_OVER_SUBSCIPTION   "Over Subscription"},   \
    {FPIN_CONGESTION_DEVICE_SPECIFIC,   "Device Specific"},     \
}

#define FPIN_CONGESTION_SEVERITY_WARNING    0xF1
#define FPIN_CONGESTION_SEVERITY_ERROR      0xF7

typedef struct _FIBRE_CHANNEL_LINK_INTEGRITY_DESCRIPTOR{
    uint32_t    DescriptorTag;
    uint32_t    DescriptorLength;
    uint64_t    DetectingWwpn;
    uint64_t    AttachedWwpn;
    uint16_t    EventType;
    uint16_t    EventModifier;
    uint32_t    EventThreshold;
    uint32_t    EventCount;
    uint32_t    PortNameCount;
    uint64_t    PortNameList[];
}FIBRE_CHANNEL_LINK_INTEGRITY_DESCRIPTOR, * PFIBRE_CHANNEL_LINK_INTEGRITY_DESCRIPTOR;

typedef struct _FIBRE_CHANNEL_DELIVERY_DESCRIPTOR{
    uint32_t    DescriptorTag;
    uint32_t    DescriptorLength;
    uint64_t    DetectingWwpn;
    uint64_t    AttachedWwpn;
    uint32_t    DeliveryReason;
}FIBRE_CHANNEL_DELIVERY_DESCRIPTOR, * PFIBRE_CHANNEL_DELIVERY_DESCRIPTOR;

typedef struct _FIBRE_CHANNEL_PEER_CONGESTION_DESCRIPTOR{
    uint32_t    DescriptorTag;
    uint32_t    DescriptorLength;
    uint64_t    DetectingWwpn;
    uint64_t    AttachedWwpn;
    uint16_t    EventType;
    uint16_t    EventModifier;
    uint32_t    EventPeriod;
    uint32_t    PNameCount;
    uint64_t    PNameList[];
}FIBRE_CHANNEL_PEER_CONGESTION_DESCRIPTOR, * PFIBRE_CHANNEL_PEER_CONGESTION_DESCRIPTOR;

typedef struct _FIBRE_CHANNEL_CONGESTION_DESCRIPTOR{
    uint32_t    DescriptorTag;
    uint32_t    DescriptorLength;
    uint16_t    EventType;
    uint16_t    EventModifier;
    uint32_t    EventPeriod;
    uint8_t     Severity;
    uint8_t     Reserved[3];
}FIBRE_CHANNEL_CONGESTION_DESCRIPTOR, * PFIBRE_CHANNEL_CONGESTION_DESCRIPTOR;

typedef struct _FIBRE_CHANNEL_ELS_FPIN{
    uint8_t                         Command;
    uint8_t                         Zero[3];
    uint32_t                        Length;
    FIBRE_CHANNEL_TLV_DESCRIPTOR    FpinDescriptor[];
}FIBRE_CHANNEL_ELS_FPIN, * PFIBRE_CHANNEL_ELS_FPIN;

typedef struct _FIBRE_CHANNEL_DIAGNOSTIC_FUNCTION_FPIN_REGISTRATION{
    uint32_t    Tag;
    uint32_t    Length;
    uint32_t    Count;
    uint32_t    Tags[];
}FIBRE_CHANNEL_DIAGNOSTIC_FUNCTION_FPIN_REGISTRATION, * PFIBRE_CHANNEL_DIAGNOSTIC_FUNCTION_FPIN_REGISTRATION;

typedef struct _FIBRE_CHANNEL_ELS_REGISTER_DIAGNOSTIC_FUNCTION{
    uint8_t                         Command;
    uint8_t                         Zero[3];
    uint32_t                        Length;
    FIBRE_CHANNEL_TLV_DESCRIPTOR    Descriptor[];
}FIBRE_CHANNEL_ELS_REGISTER_DIAGNOSTIC_FUNCTION, * PFIBRE_CHANNEL_ELS_REGISTER_DIAGNOSTIC_FUNCTION;


typedef struct _FIBRE_CHANNEL_ELS_RDF_RESPONCE{
    FC_ELS_LS_ACC_PAYLOAD           AccHeader;
    uint32_t                        ListLength;
    FIBRE_CHANNEL_LSRI_DESCRIPTOR   Lrsi;
    FIBRE_CHANNEL_TLV_DESCRIPTOR    Descriptor[];
}FIBRE_CHANNEL_ELS_RDF_RESPONCE, * PFIBRE_CHANNEL_ELS_RDF_RESPONCE;

typedef struct _FIBRE_CHANNEL_DIAGNOSTIC_LINK_FAULT_DESCRIPTOR{
    uint32_t    Tag;
    uint32_t    Length;
    uint32_t    Dat;
    uint32_t    Ddt;
    uint32_t    Fdi;
}FIBRE_CHANNEL_DIAGNOSTIC_LINK_FAULT_DESCRIPTOR, * PFIBRE_CHANNEL_DIAGNOSTIC_LINK_FAULT_DESCRIPTOR;

#define EDC_CG_SINGAL_NOT_SUPPORTED 0x00
#define EDC_CG_SINGAL_WARN_ONLY     0x01
#define EDC_CG_SINGAL_WARN_ALARM    0x02

#define FIBRE_CHANNEL_EDC_SIGNAL_CAP_TYPES_INTI {               \
    {EDC_CG_SINGAL_NOT_SUPPORTED,   "Signal Not Supported"},    \
    {EDC_CG_SINGAL_WARN_ONLY,       "Warning Signal"},          \
    {EDC_CG_SINGAL_WARN_ALARM,      "Warning And Alarm Signal"},\
}

#define EDC_CG_SIGNAL_FREQUENCY_COUNT_MIN       1
#define EDC_CG_SIGNAL_FREQUENCY_COUNT_MAX       999

#define EDC_CG_SIGNAL_FREQUENCY_SECONDS         0x01
#define EDC_CG_SIGNAL_FREQUENCY_MSECONDS        0x01

typedef struct _FIBRE_CHANNEL_DIAGNOSTIC_SINGNAL_FREQUENCY{
    uint16_t Count;
    uint16_t Units;
}FIBRE_CHANNEL_DIAGNOSTIC_SINGNAL_FREQUENCY, * PFIBRE_CHANNEL_DIAGNOSTIC_SINGNAL_FREQUENCY;

typedef struct _FIBRE_CHANNEL_DIAGNOSTIC_CONGESTION_SINGAL_CAP_DESCRIPTOR{
    uint32_t                                    Tag;
    uint32_t                                    Length;
    uint32_t                                    XmtSignalCapability;
    FIBRE_CHANNEL_DIAGNOSTIC_SINGNAL_FREQUENCY  XmtFrequency;
    uint32_t                                    RcvSingalCapability;
    FIBRE_CHANNEL_DIAGNOSTIC_SINGNAL_FREQUENCY  RcvFrequency;
}FIBRE_CHANNEL_DIAGNOSTIC_CONGESTION_SINGAL_CAP_DESCRIPTOR, * PFIBRE_CHANNEL_DIAGNOSTIC_CONGESTION_SINGAL_CAP_DESCRIPTOR;

typedef struct _FIBRE_CHANNEL_EXCHANGE_DIAGNOSTIC_CAPABILITY{
    uint8_t                         Command;
    uint8_t                         Zero[3];
    uint32_t                        Length;
    FIBRE_CHANNEL_TLV_DESCRIPTOR    Descriptor[];
}FIBRE_CHANNEL_EXCHANGE_DIAGNOSTIC_CAPABILITY, * PFIBRE_CHANNEL_EXCHANGE_DIAGNOSTIC_CAPABILITY;

typedef struct _FIBRE_CHANNEL_ELS_EDS_RESPONCE{
    FC_ELS_LS_ACC_PAYLOAD            AccHeader;
    uint32_t                            ListLength;
    FIBRE_CHANNEL_LSRI_DESCRIPTOR   Lsri;
    FIBRE_CHANNEL_TLV_DESCRIPTOR        Descriptor[];
}FIBRE_CHANNEL_ELS_EDS_RESPONCE, * PFIBRE_CHANNEL_ELS_EDS_RESPONCE;

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif //_FIBRE_CHANNEL_ELS_H