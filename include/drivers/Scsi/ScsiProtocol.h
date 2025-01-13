#ifndef _ISCSI_PROTOCOL_H
#define _ISCSI_PROTOCOL_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

#define ISCSI_DRAFT20_VERSION   0x00

#define ISCSI_LISTEN_PORT       3260
#define ISCSI_HEADER_LENGTH       48
#define ISCSI_CRC32C_LENGTH        4
#define ISCSI_PADDING              4

static inline int IscsiSnaLt(uint32_t x, uint32_t y){
    return (int)(x - y) < 0;
}

static inline int IscsiSnaLte(uint32_t x, uint32_t y){
    return (int)(x - y) < 0;
}

static inline int IscsiSnaGte(uint32_t x, uint32_t y){
    return (int)(x - y) >= 0;
}

#define NTOH24(Pointer) (((Pointer)[0] << 16) | ((Pointer)[1] << 8) | ((Pointer)[2]))
#define HTON24(Pointer, Value) {            \
    Pointer[0] = (((Value) >> 16) & 0x0FF); \
    Pointer[1] = (((Value) >> 8)  & 0xFF);  \
    Pointer[2] = ((Value) & 0xFF);          \
}
#define ScstProtocolZeroData(Pointer) {Pointer[0] = 0; Pointer[1] = 0; Pointer[2] = 0;Pointer[3] = 0;}

typedef uint32_t INITIATOR_TAG;

#define BuildInitiatorTag(Tag, Age) ((INITIATOR_TAG)((Tag) | ((Age) << ISCSI_AGE_SHIFT)))
#define GetInitiatorTag(Tag)        ((uint32_t)(INITIATOR_TAG)(Tag) & ISCSI_INITIATOR_MASK)
#define RESERVED_INITIATOR          ((INITIATOR_TAG)0xFFFFFFFF)

typedef struct _ISCSI_HEADER{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Rsvd1[2];
    uint8_t         HLength;
    uint8_t         DLength[3];
    //SCSI_LUN      ScsiLun;
    INITIATOR_TAG   Tag;
    //Big Endian Data
    uint32_t        TargetTaskType;
    uint32_t        StatSn;
    uint32_t        ExpStatsn;
    uint32_t        MaxStatsn;
    uint8_t         Other[12];
}ISCSI_HEADER, * PISCSI_HEADER;

#define ISCSI_RESERVED_TAG          0xFFFFFFFF
#define ISCSI_OPCODE_RETRY          0x80
#define ISCSI_OPCODE_IMIDIATE       0x40
#define ISCSI_OPCODE_MASK           0x3F

#define ISCSI_OPCODE_NOOP_OUT           0x00
#define ISCSI_OPCODE_SCSI_COMMAND       0x01
#define ISCSI_OPCODE_SCSI_TMFUNCTION    0x02
#define ISCSI_OPCODE_LOGIN              0x03
#define ISCSI_OPCODE_TEXT               0x04
#define ISCSI_OPCODE_SCSI_DATA_OUT      0x05
#define ISCSI_OPCODE_LOGOUT             0x06
#define ISCSI_OPCODE_SNACK              0x10

#define ISCSI_OPCODE_VENDOR_SPECIFIC_COMMAND1   0x1C
#define ISCSI_OPCODE_VENDOR_SPECIFIC_COMMAND2   0x1D
#define ISCSI_OPCODE_VENDOR_SPECIFIC_COMMAND3   0x1E
#define ISCSI_OPCODE_VENDOR_SPECIFIC_COMMAND4   0x1F

#define ISCSI_OPCODE_NOOP_IN                0x20
#define ISCSI_OPCODE_SCSI_COMMAND_RESPONCE  0x21
#define ISCSI_OPCODE_TM_FUNCTION_RESPONCE   0x22
#define ISCSI_OPCODE_LOGIN_REPSONCE         0x23
#define ISCSI_OPCODE_TEXT_RESPONCE          0x24
#define ISCSI_OPCODE_SCSI_DATA_IN           0x25
#define ISCSI_OPCODE_LOGOUT_RESPONCE        0x26
#define ISCSI_OPCODE_R2T                    0x31
#define ISCSI_OPCODE_ASYNC_EVENT            0x32
#define ISCSI_OPCODE_REJECT                 0x3F

#define ISCSI_AHTYPE_COMMAND_TYPE_BUFFER    1
#define ISCSI_AHTYPE_RLEGTH                 2
#define ISCSI_COMMAND_BUFFER_SIZE           16

//Big Endian Structure
typedef struct _ISCSI_SCSI_REQUEST{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint16_t        Reserved1;
    uint8_t         HLength;
    uint8_t         DLength[3];
    //SCSI_LUN      Lun;
    INITIATOR_TAG   Tag;
    uint32_t        DataLength;
    uint32_t        CommandSn;
    uint32_t        ExpStatSn;
    uint8_t         CommandDataBuffer[ISCSI_COMMAND_BUFFER_SIZE];
}ISCSI_SCSI_REQUEST, * PISCSI_SCSI_REQUEST;

#define ISCSI_FLAG_COMMON_FINAL         0x80
#define ISCSI_FLAG_COMMON_READ          0x40
#define ISCSI_FLAG_COMMON_WRITE         0x20
#define ISCSI_FLAG_COMMON_ATTR_MASK     0x07

#define ISCSI_ATTRIBUTE_UNTAGGED        0
#define ISCSI_ATTRIBUTE_SIMPLE          1
#define ISCSI_ATTRIBUTE_ORDERED         2
#define ISCSI_ATTRIBUTE_HEAD_Q          3
#define ISCSI_ATTRIBUTE_ACA             4

//Big Endian
typedef struct _ISCSI_RLENGTH_AHDR{
    uint16_t AhsLength;
    uint8_t  AhsType;
    uint8_t  Reserved;
    uint32_t ReadLength;
}ISCSI_RLENGTH_AHDR, * PISCSI_RLENGTH_AHDR;

//Big Endian
typedef struct _ISCSI_ECDB_AHDR{
    uint16_t    AhsLength;
    uint8_t     AhsType;
    uint8_t     Reserved;
    //uint8_t     ExtendedCommandDataBuffer[SCSI_MAX_VARLEN_CDB_SIZE - ISCSI_COMMAND_BUFFER_SIZE];
}ISCSI_ECDB_AHDR, * PISCSI_ECDB_AHDR;

//Big Endian
typedef struct _ISCSI_SCSI_RESPONCE{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Responce;
    uint8_t         CommandStatus;
    uint8_t         HLength;
    uint8_t         DLength[3];
    uint8_t         Reserved1[8];
    INITIATOR_TAG   Tag;
    uint32_t        Reserved2;
    uint32_t        StatusSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCommandSn;
    uint32_t        ExpDataSn;
    uint32_t        BiResidualCount;
    uint32_t        ResidualCount;
}ISCSI_SCSI_RESPONCE, * PISCSI_SCSI_RESPONCE;

#define ISCSI_FLAG_COMMAON_BIDI_OVERFLOW    0x10
#define ISCSI_FLAG_COMMAON_BIDI_UNDERFLOW   0x08
#define ISCSI_FLAG_COMMAON_OVERFLOW         0x04
#define ISCSI_FLAG_COMMAON_UNDERFLOW        0x02

#define ISCSI_STATUS_COMMAND_COMPLETED      0
#define ISCSI_STATUS_TARGET_FAILURE         1
#define ISCSI_STATUS_SUB_SYSTEM_FAILURE     2

typedef struct _ISCSI_ASYNC{
    uint8_t     Opcode;
    uint8_t     Flags;
    uint8_t     Reserved1[2];
    uint8_t     Reserved2;
    uint8_t     DLength[3];
    //SCSI_LUN    Lun;
    uint8_t     Reserved3[8];
    uint32_t    StatSn;
    uint32_t    ExpCommandSn;
    uint32_t    MaxCommandSn;
    uint8_t     AsyncEvent;
    uint8_t     AsyncVcode;
    uint16_t    Parameter1;
    uint16_t    Parameter2;
    uint16_t    Parameter3;
    uint8_t     Reserved5[4];
}ISCSI_ASYNC, * PISCSI_ASYNC;

#define ISCSI_ASYNC_MESSAGE_SCSI_EVENT                  0
#define ISCSI_ASYNC_MESSAGE_REQUEST_LOGOUT              1
#define ISCSI_ASYNC_MESSAGE_DROPPING_CONNECTION         2
#define ISCSI_ASYNC_MESSAGE_DROPPING_ALL_CONNECTIONS    3
#define ISCSI_ASYNC_MESSAGE_PARAMETER_NAGOTIATION       4
#define ISCSI_ASYNC_MESSAGE_VENDOR_SPECIFIC             255

//big Endian Structure
typedef struct _ISCSI_NOP_OUT{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint16_t        Reserved1;
    uint8_t         Reserved2;
    uint8_t         DLength[3];
    //SCSI_LUN        Lun;
    INITIATOR_TAG   Tag;
    uint32_t        TargetTaskType;
    uint32_t        CommandSn;
    uint32_t        ExpStatSn;
    uint8_t         Reserved3[16];
}ISCSI_NOP_OUT, * PISCSI_NOP_OUT;

//Big Endian
typedef struct _ISCSI_NOP_IN{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint16_t        Reserved1;
    uint8_t         Reserved2;
    //SCSI_LUN        Lun;
    INITIATOR_TAG   Tag;
    uint32_t        TargetTaskType;
    uint32_t        StatSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCommandSn;
    uint8_t         Reserved3[12];
}ISCSI_NOP_IN, * PISCSI_NOP_IN;

typedef struct _ISCSI_TM{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Reserved1[2];
    uint8_t         HLeghth;
    uint8_t         DLength[3];
    //SCSI_LUN        Lun;
    INITIATOR_TAG   Tag;
    INITIATOR_TAG   Rtt;
    uint32_t        CommandSn;
    uint32_t        ExpStatSn;
    uint32_t        RefCommandSn;
    uint32_t        ExpDataSn;
    uint8_t         Reserved2[8];
}ISCSI_TM, * PISCSI_TM;

#define ISCSI_FLAG_TM_FUNCTION_MASK 0x7F

#define ISCSI_TM_FUNCTION_ABORT_TASK            1
#define ISCSI_TM_FUNCTION_ABORT_TASK_SET        2
#define ISCSI_TM_FUNCTION_CLEAR_ACA             3
#define ISCSI_TM_FUNCTION_CLEAR_TASK_SET        4
#define ISCSI_TM_FUNCTION_LOGICAL_UNIT_RESET    5
#define ISCSI_TM_FUNCTION_TARGET_WARM_RESET     6
#define ISCSI_TM_FUNCTION_TARGET_COLD_RESET     7
#define ISCSI_TM_FUNCTION_TASK_REASSIGN         8

#define ISCSI_TM_FUNCTION_VALUE(Header) ((Header)->Flags & ISCSI_FLAG_TM_FUNCTION_MASK)

typedef struct _ISCSI_TM_RESPONCE{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Responce;
    uint8_t         Qualifier;
    uint8_t         HLength;
    uint8_t         DLength[3];
    uint8_t         Reserved1[8];
    INITIATOR_TAG   Itt;
    INITIATOR_TAG   Rtt;
    uint32_t        StatSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCmdSn;
    uint8_t         Rserved2[12];
}ISCSI_TM_RESPONCE, * PISCSI_TM_RESPONCE;

#define ISCSI_TMF_RESPONCE_COMPLETE                 0x00
#define ISCSI_TMF_RESPONCE_NO_TASK                  0x01
#define ISCSI_TMF_RESPONCE_NO_LUN                   0x02
#define ISCSI_TMF_RESPONCE_TASK_ALLEGIANT           0x03
#define ISCSI_TMF_RESPONCE_NO_FAIL_OVER             0x04
#define ISCSI_TMF_RESPONCE_NOT_SUPPORTED            0x05
#define ISCSI_TMF_RESPONCE_AUTHENTICATION_FAILED    0x06
#define ISCSI_TMF_RESPONCE_REJECTED                 0xFF

//Big Endian
typedef struct _ISCSI_READY_TO_TRANSFER_RESPONCE{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Reserved1[2];
    uint8_t         HLength;
    uint8_t         DLength[3];
    //SCSI_LUN        Lun;
    INITIATOR_TAG   Tag;
    uint32_t        TargetTransferTag;
    uint32_t        StatSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCommandSn;
    uint32_t        ReadyToTransferSn;
    uint32_t        DataOffset;
    uint32_t        DataLength;
}ISCSI_READY_TO_TRANSFER_RESPONCE, * PISCSI_READY_TO_TRANSFER_RESPONCE;

//Big Endian
typedef struct _ISCSI_DATA{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Reserved1[2];
    uint8_t         Reserved2;
    uint8_t         DLengthp[3];
    //SCSI_LUN        Lun;
    INITIATOR_TAG   Tag;
    uint32_t        Ttt;
    uint32_t        Reserved3;
    uint32_t        ExpStatSn;
    uint32_t        Reserved4;
    uint32_t        DataSn;
    uint32_t        Offset;
    uint32_t        Reserved5;
}ISCSI_DATA, * PISCSI_DATA;

//BigEndian
typedef struct _ISCSI_DATA_RESPONCE{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Reserved1;
    uint8_t         CommandStatus;
    uint8_t         HLength;
    uint8_t         DLength[3];
    //SCSI_LUN        Lun;
    INITIATOR_TAG   Tag;
    uint32_t        Ttt;
    uint32_t        StatusSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCommandSn;
    uint32_t        DataSn;
    uint32_t        Offset;
    uint32_t        ResidualCount;
}ISCSI_DATA_RESPONCE, * PISCSI_DATA_RESPONCE;

#define ISCSI_FLAGS_DATA_ACKNOLEDGE     0x40
#define ISCSI_FLAGS_DATA_OVERFLOW       0x04
#define ISCSI_FLAGS_DATA_UNDERFLOW      0x02
#define ISCSI_FLAGS_DATA_STATUS         0x01

#define ISCSI_FLAG_TEXT_CONTINUE        0x40

//Big Endian
typedef struct _ISCSI_TEXT{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Reserved1[2];
    uint8_t         HLength;
    uint8_t         DLength[3];
    uint8_t         Reserved2[8];
    INITIATOR_TAG   Itt;
    uint32_t        Ttt;
    uint32_t        CommandSn;
    uint32_t        ExpStatSn;
    uint8_t         Reserved3[16];
}ISCSI_TEXT, * PISCSI_TEXT;

//big endian
typedef struct _ISCSI_TEXT_RESPONCE{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Reserved1[2];
    uint8_t         HLength;
    uint8_t         DLength[3];
    uint8_t         Reserved2[8];
    INITIATOR_TAG   Itt;
    uint32_t        Ttt;
    uint32_t        StatSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCommandSn;
    uint8_t         Reserved3[12];
}ISCSI_TEXT_RESPONCE, * PISCSI_TEXT_RESPONCE;

//big endian
typedef struct _ISCSI_LOGIN_REQUEST{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         MaxVersion;
    uint8_t         MinVersion;
    uint8_t         HLength;
    uint8_t         DLength[3];
    uint8_t         ISID[6];
    uint16_t        Tsih;
    INITIATOR_TAG   Itt;
    uint16_t        Cid;
    uint16_t        Reserved1;
    uint32_t        CommandSn;
    uint32_t        ExpStatSn;
    uint8_t         Reserved2[16];
}ISCSI_LOGIN_REQUEST, * PISCSI_LOGIN_REQUEST;

#define ISCSI_FLAG_LOGIN_TRANSIT                0x80
#define ISCSI_FLAG_LOGIN_CONTINUE               0x40
#define ISCSI_FLAG_LOGIN_CURRENT_STAGE_MASK     0x0C
#define ISCSI_FLAG_LOGIN_CURRENT_STAGE1         0x04
#define ISCSI_FLAG_LOGIN_CURRENT_STAGE2         0x08
#define ISCSI_FLAG_LOGIN_CURRENT_STAGE3         0x0C
#define ISCSI_FLAG_LOGIN_NEXT_STAGE_MASK        0x03
#define ISCSI_FLAG_LOGIN_NEXT_STAGE1            0x01
#define ISCSI_FLAG_LOGIN_NEXT_STAGE2            0x02
#define ISCSI_FLAG_LOGIN_NEXT_STAGE3            0x03
#define ISCSI_LOGIN_CURRENT_STAGE_SHIFT 2
#define ISCSI_LOGIN_CURRENT_STAGE(Flags) ((Flags & ISCSI_FLAG_LOGIN_CURRENT_STAGE_MASK) >> ISCSI_LOGIN_CURRENT_STAGE_SHIFT)
#define ISCSI_LOGIN_NEXT_STAGE(Flags) (Flags & ISCSI_FLAG_LOGIN_NEXT_STAGE_MASK)

//Big Endian
typedef struct _ISCSI_LOGIN_RESPONCE{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         MaxVersion;
    uint8_t         ActiveVersion;
    uint8_t         HLength;
    uint8_t         DLength[3];
    uint8_t         ISID[6];
    uint16_t        TSIH;
    INITIATOR_TAG   Itt;
    uint32_t        Reserved1;
    uint32_t        StatSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCommandSn;
    uint8_t         StatusClass;
    uint8_t         StatusDetail;
    uint8_t         Reserved2[10];
}ISCSI_LOGIN_RESPONCE, * PISCSI_LOGIN_RESPONCE;

#define ISCSI_INITIAL_LOGIN_STAGE              -1
#define ISCSI_SECURITY_NEGOTIATION_STAGE        0
#define ISCSI_OP_PARAMETERS_NEGOTIATION_STAGE   1
#define ISCSI_FULL_FEATURE_PHASE                3

#define ISCSI_STATUS_CLASS_SUCCESS          0x00
#define ISCSI_STATUS_CLASS_REDIRECT         0x01
#define ISCSI_STATUS_CLASS_INITATOR_ERROR   0x02
#define ISCSI_STATUS_CLASS_TARGET_ERROR     0x03

#define ISCSI_LOGIN_STATUS_ACCEPT           0x00

#define ISCSI_LOGIN_STATUS_TARGET_MOVED_TEMPORARY       0x01
#define ISCSI_LOGIN_STATUS_TARGET_MOVED_PERMINANT       0x02

#define ISCSI_LOGIN_STATUS_INIT_ERROR               0x00
#define ISCSI_LOGIN_STATUS_AUTHENTICATION_FAILED    0x01   
#define ISCSI_LOGIN_STATUS_TARGET_FORBIDDEN         0x02
#define ISCSI_LOGIN_STATUS_TARGET_NOT_FOUND         0x03
#define ISCSI_LOGIN_STATUS_TARGET_REMOVED           0x04
#define ISCSI_LOGIN_STATUS_NO_VERSION               0x05
#define ISCSI_LOGIN_STATUS_ISID_ERROR               0x06
#define ISCSI_LOGIN_STATUS_MISSING_FIELD            0x07
#define ISCSI_LOGIN_STATUS_CONNECTION_ADD_FAILED    0x08
#define ISCSI_LOGIN_STATUS_NO_SESSION_TYPE          0x09
#define ISCSI_LOGIN_STATUS_NO_SESSION               0x0A
#define ISCSI_LOGIN_STATUS_INVALID_REQUEST          0x0B

#define ISCSI_LOGIN_STATUS_TARGET_ERROR             0x00
#define ISCSI_LOGIN_STATUS_SERVICE_UNAVAILABLE      0x01
#define ISCSI_LOGIN_STATUS_NO_RESOURCES             0x02

#define ISCSI_FLAG_LOGOUT_REASON_MASK 0x7F

#define ISCSI_LOGOUT_REASON_CLOSE_SESSION       0
#define ISCSI_LOGOUT_REASON_CLOSE_CONNECTION    1
#define ISCSI_LOGOUT_REASON_RECOVERY            2
#define ISCSI_LOGOUT_REASON_AEN_REQUEST         3

typedef struct _ISCSI_LOGOUT{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Reserved1[2];
    uint8_t         HLength;
    uint8_t         DLength[3];
    uint8_t         Reserved2[8];
    INITIATOR_TAG   Itt;
    uint16_t        Cid;
    uint8_t         Reserved3[2];
    uint32_t        CommandSn;
    uint32_t        ExpStatSn;
    uint8_t         Reserved4[16];
}ISCSI_LOGOUT, * PISCSI_LOGOUT;

typedef struct _ISCSI_LOGOUT_REESPONCE{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Rseponce;
    uint8_t         Reserved1;
    uint8_t         HLength[3];
    uint8_t         Reserved2[8];
    INITIATOR_TAG   Itt;
    uint32_t        Reserved3;
    uint32_t        StatSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCommandSn;
    uint32_t        Reserved4;
    uint16_t        TransferWait;
    uint16_t        TransferRetain;
    uint32_t        Reserved5;
}ISCSI_LOGOUT_REESPONCE, * PISCSI_LOGOUT_REESPONCE;

#define ISCSI_LOGOUT_SUCCESS                    0
#define ISCSI_LOGOUT_CID_NOT_FOUND              1
#define ISCSI_LOGOUT_RECOVERY_UNSUPPORTED       2
#define ISCSI_LOGOUT_CLEANUP_FAILED             3

//big endian
typedef struct _ISCSI_REJECT{
    uint8_t         Opcode;
    uint8_t         Flags;
    uint8_t         Reason;
    uint8_t         Reserved1;
    uint8_t         HLength;
    uint8_t         DLength[3];
    uint8_t         Reserved2[8];
    uint32_t        ShouldBeUint32Max;
    uint8_t         Reserved3[4];
    uint32_t        StatSn;
    uint32_t        ExpCommandSn;
    uint32_t        MaxCommandSn;
    uint32_t        DataSn;
    uint8_t         Reserved4[5];
}ISCSI_REJECT, * PISCSI_REJECT;

#define ISCSI_REASON_COMMAND_BEFORE_LOGIN       1
#define ISCSI_REASON_DATA_DIGEST_ERROR          2
#define ISCSI_REASON_DATA_SNACK_REJECT          3
#define ISCSI_REASON_PROTOCOL_ERROR             4
#define ISCSI_REASON_COMMAND_NOT_SUPPORTED      5
#define ISCSI_REASON_IMM_COMMAND_REJECTED       6
#define ISCSI_REASON_TASK_IN_PROGRESS           7
#define ISCSI_REASON_INVALID_SNACK              8
#define ISCSI_REASON_BOOKMARK_INVALID           9
#define ISCSI_REASON_BOOKMARK_NO_RESOURCES      10
#define ISCSI_REASON_NEGOTIATION_RESET          11

#define MAXIMUM_KEY_VALUE_PAIRS                 8192

#define MAXIMUM_KEY_LENGTH                      64
#define MAXIMUM_VALUE_LENGTH                    255
#define MAXIMUM_TARGET_LENGTH                   MAXIMUM_VALUE_LENGTH

#define ISCSI_DEFINE_MAX_RECIVE_SGEMENT_LENGTH  8192
#define ISCSI_MIN_MAX_RECIVE_SEGMENT_LENGTH     512
#define ISCSI_MAX_MAX_RECIVE_SEGMENT_LENGTH     16777215

#define ISCSI_DEFINE_FIRST_BURST_LENGTH         0xFFFF
#define ISCSI_MIN_FIRST_BURST_LENGTH            ISCSI_MIN_MAX_RECIVE_SEGMENT_LENGTH
#define ISCSI_MAX_FIRST_BURST_LENGTH            ISCSI_MAX_MAX_RECIVE_SEGMENT_LENGTH

#define ISCSI_DEFINE_MAX_BURST_LENGTH           262144
#define ISCSI_MIN_MAX_BURST_LENGTH              ISCSI_MIN_MAX_RECIVE_SEGMENT_LENGTH
#define ISCSI_MAX_MAX_BURST_LENGTH              ISCSI_MAX_MAX_RECIVE_SEGMENT_LENGTH

#define ISCSI_DEFINE_WAIT_TIME                  2

#define ISCSI_NAME_LENGTH                       224

#ifdef __cplusplus
}
#endif
#endif //_ISCSI_PROTOCOL_H