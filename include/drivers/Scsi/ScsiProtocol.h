#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

#ifndef _SCSI_PROTOCOL_H
#define _SCSI_PROTOCOL_H

#define SCSI_OPCODE_TEST_UNIT_READY                         0x00
#define SCSI_OPCODE_RE_ZERO_UNIT                            0x01
#define SCSI_OPCODE_REQUEST_SENCE                           0x03
#define SCSI_OPCODE_FORMAT_UNIT                             0x04
#define SCSI_OPCODE_READ_BLOVK_LIMITS                       0x05
#define SCSI_OPCODE_REASIGN_BLOCKS                          0x07
#define SCSI_OPCODE_INITIALIZE_ELEMENT_STATUS               0x07
#define SCSI_OPCODE_READ6                                   0x08
#define SCSI_OPCODE_WRITE6                                  0x0A
#define SCSI_OPCODE_SEEK6                                   0x0B
#define SCSI_OPCODE_READ_REVERSE                            0x0F
#define SCSI_OPCODE_WRITE_FILEMARKS                         0x10
#define SCSI_OPCODE_SPACE                                   0x11
#define SCSI_OPCODE_INQUIRY                                 0x12
#define SCSI_OPCODE_RECOVERED_BUFFERED_DATA                 0x14
#define SCSI_OPCODE_MODE_SELECT                             0x15
#define SCSI_OPCODE_RESERVE                                 0x16
#define SCSI_OPCODE_RELEASE                                 0x17
#define SCSI_OPCODE_COPY                                    0x18
#define SCSI_OPCODE_ERASE                                   0x19
#define SCSI_OPCODE_MODE_SENCE                              0x1A
#define SCSI_OPCODE_START_STOP                              0x1B
#define SCSI_OPCODE_RECIVE_DIAGNOSTIC                       0x1C
#define SCSI_OPCODE_SEND_DIAGNOSTIC                         0x1D
#define SCSI_OPCODE_ALLOW_MEDIUM_REMOVAL                    0x1E
#define SCSI_OPCODE_READ_FORMAT_CAPACITIES                  0x23
#define SCSI_OPCODE_SET_WINDOW                              0x24
#define SCSI_OPCODE_READ_CAPACITY                           0x25
#define SCSI_OPCODE_READ10                                  0x28
#define SCSI_OPCODE_WRITE10                                 0x2A
#define SCSI_OPCODE_SEEK10                                  0x2B
#define SCSI_OPCODE_POSITION_TO_ELEMENT                     0x2B
#define SCSI_OPCODE_WRITE_VERIFY                            0x2E
#define SCSI_OPCODE_VERIFY                                  0x2F
#define SCSI_OPCODE_SEARCH_HIGH                             0x30
#define SCSI_OPCODE_SEARCH_EQUAL                            0x31
#define SCSI_OPCODE_SEARCH_LOW                              0x32
#define SCSI_OPCODE_SET_LIMIT                               0x33
#define SCSI_OPCODE_PRE_FETCH                               0x34
#define SCSI_OPCODE_READ_POSITION                           0x34
#define SCSI_OPCODE_SYNC_CACHE                              0x35
#define SCSI_OPCODE_PERMISE_CACHE                           0x36
#define SCSI_OPCODE_READ_DEFECTIVE_DATA                     0x37
#define SCSI_OPCODE_MEDIUM_SCAN                             0x38
#define SCSI_OPCODE_COMPARE                                 0x39
#define SCSI_OPCODE_COPY_VERIFY                             0x3A    
#define SCSI_OPCODE_WRITE_BUFFER                            0x3B
#define SCSI_OPCODE_READ_BUFFER                             0x3C
#define SCSI_OPCODE_UPDATE_BLOCK                            0x3D
#define SCSI_OPCODE_READ_LONG                               0x3E
#define SCSI_OPCODE_WRITE_LONG                              0x3F
#define SCSI_OPCODE_CHANGE_DEF                              0x40
#define SCSI_OPCODE_WRITE_SAME                              0x41
#define SCSI_OPCODE_UNMAP                                   0x42
#define SCSI_OPCODE_READ_TOC                                0x43
#define SCSI_OPCODE_READ_HEADER                             0x44
#define SCSI_OPCODE_GET_EVENT_STATUS_NOTIF                  0x4A
#define SCSI_OPCODE_LOG_SELECT                              0x4C
#define SCSI_OPCODE_LOG_SENCE                               0x4D
#define SCSI_OPCODE_XD_WRRD10                               0x53
#define SCSI_OPCODE_MODE_SELECT10                           0x55
#define SCSI_OPCODE_RESERVE10                               0x56
#define SCSI_OPCODE_RELEASE10                               0x57
#define SCSI_OPCODE_MODE_SENCE10                            0x5A
#define SCSI_OPCODE_PERSIST_RESERVE_IN                      0x5E
#define SCSI_OPCODE_PERSIST_RESERVE_OUT                     0x5F
#define SCSI_OPCODE_VARIAC_LENGTH_COMMAND                   0x7F
#define SCSI_OPCODE_REPORT_LUNS                             0xA0
#define SCSI_OPCODE_SECUREPRO_IN                            0xA2
#define SCSI_OPCODE_MAINTENECE_IN                           0xA3
#define SCSI_OPCODE_MAINTENECE_OUT                          0xA4
#define SCSI_OPCODE_MOVE_MEDIUM                             0xA5
#define SCSI_OPCODE_EXCHANGE_MEDIUM                         0xA6
#define SCSI_OPCODE_READ12                                  0xA8
#define SCSI_OPCODE_ACTION_OUT12                            0xA9
#define SCSI_OPCODE_WRITE12                                 0xAA
#define SCSI_OPCODE_READ_MEDIA_SERIALID                     0xAB
#define SCSI_OPCODE_SERVICE_ACTION_IN12                     0xAB
#define SCSI_OPCODE_WRITE_VERIFY12                          0xAE
#define SCSI_OPCODE_VERIFY12                                0xAF
#define SCSI_OPCODE_SEARCH_HIGH12                           0xB0
#define SCSI_OPCODE_SEARCH_EQUAL12                          0xB1
#define SCSI_OPCODE_SEACH_LOW12                             0xB2                                   
#define SCSI_OPCODE_SECUREPRO_OUT                           0xB5
#define SCSI_OPCODE_READ_ELEMENT_STATUS                     0xB8
#define SCSI_OPCODE_SEND_VOLUME_TAG                         0xB6
#define SCSI_OPCODE_WRITE_LONG2                             0xEA
#define SCSI_OPCODE_EXTENDED_COPY                           0x83
#define SCSI_OPCODE_RECIVE_COPY_RESULT                      0x84
#define SCSI_OPCODE_ACCESS_CONTROL_IN                       0x86
#define SCSI_OPCODE_ACCESS_CONTROL_OUT                      0x87
#define SCSI_OPCODE_READ16                                  0x88
#define SCSI_OPCODE_COMPARE_AND_WRITE                       0x89
#define SCSI_OPCODE_WRITE16                                 0x8A
#define SCSI_OPCODE_READ_ATTRIBUTE                          0x8C
#define SCSI_OPCODE_WRITE_ATTRIBUTE                         0x8D
#define SCSI_OPCODE_WRITE_VERIFY16                          0x8E
#define SCSI_OPCODE_VERIFY16                                0x8F
#define SCSI_OPCODE_SYNC_CACHE16                            0x91
#define SCSI_OPCODE_WRITE_SAME16                            0x93
#define SCSI_OPCODE_ZBC_OUT                                 0x94
#define SCSI_OPCODE_ZBC_IN                                  0x95
#define SCSI_OPCODE_WRITE_ATOMIC16                          0x9C
#define SCSI_OPCODE_SERVICE_ACTION_BIDI                     0x9D
#define SCSI_OPCODE_SERVICE_ACTION_IN16                     0x9E
#define SCSI_OPCODE_SERVICE_ACTION_Out16                    0x9F
#define SCSI_OPCODE_SAI_READ_CAPACITY12                     0x10
#define SCSI_OPCODE_SAI_GET_LBA_STATUS                      0x12
#define SCSI_OPCODE_SAI_REPORT_REFERALS                     0x13
#define SCSI_OPCODE_SAI_GET_STREAM_STATUS                   0x16
#define SCSI_OPCODE_MI_REPORT_IDINF                         0x05
#define SCSI_OPCODE_MI_REPORT_TPGS                          0x0A
#define SCSI_OPCODE_MI_REPORT_ALIASES                       0x0B
#define SCSI_OPCODE_MI_REPORT_SOC                           0x0C    
#define SCSI_OPCODE_MI_REPORT_STM                           0x0D
#define SCSI_OPCODE_MI_REPORT_PRI                           0x0E
#define SCSI_OPCODE_MI_REPORT_TS                            0x0F
#define SCSI_OPCODE_MI_MANAGEPRO_IN                         0x10
#define SCSI_OPCODE_MI_EXTENSION_HEADER_PARAMETER_FMT       0x20
#define SCSI_OPCODE_MO_SET_IDINF                            0x06
#define SCSI_OPCODE_MO_SET_TPGS                             0x0A
#define SCSI_OPCODE_MO_CHANGE_ALIASES                       0x0B
#define SCSI_OPCODE_MO_SET_PRI                              0x0E
#define SCSI_OPCODE_MO_SET_TS                               0x0D
#define SCSI_OPCODE_MO_MANAGEPRO_OUT                        0x10
#define SCSI_OPCODE_ZI_REPORT_ZONES                         0x00
#define SCSI_OPCODE_ZO_CLOSE_ZONE                           0x01
#define SCSI_OPCODE_ZO_FINISH_ZONE                          0x02
#define SCSI_OPCODE_ZO_OPEN_ZONE                            0x03
#define SCSI_OPCODE_ZO_RESET_WRITE_POINTER                  0x04
#define SCSI_OPCODE_READ_KEYS                               0x00
#define SCSI_OPCODE_READ_RESERVATION                        0x01
#define SCSI_OPCODE_REPORT_CAPABILITIES                     0x02
#define SCSI_OPCODE_READ_FULL_STATUS                        0x03
#define SCSI_OPCODE_XDREAD32                                0x03
#define SCSI_OPCODE_XDWRITE32                               0x04
#define SCSI_OPCODE_XPWRITE32                               0x06
#define SCSI_OPCODE_XDWRRD32                                0x07
#define SCSI_OPCODE_READ32                                  0x09
#define SCSI_OPCODE_VERIFY32                                0x0A
#define SCSI_OPCODE_WRITE32                                 0x0B
#define SCSI_OPCODE_WRITE_VERIFY32                          0x0C
#define SCSI_OPCODE_WRITE_SAME32                            0x0D
#define SCSI_OPCODE_ATA32                                   0x1FF0
#define SCSI_OPCODE_ATA16                                   0x85
#define SCSI_OPCODE_ATA12                                   0xA1

#define VENDOR_SPECIFIC_COMMAND_DATA_BUFFER         0xC0

#define SCSI_MAXIMUM_VARIAC_LENGTH_COMMAND_DATA_BUFFER_SIZE 260

//Big Endian
typedef struct _SCSI_VARIAC_LENGTH_COMMAND_DATA_BUFFER_HEADER{
    uint8_t     Opcode; //Always SCSI_OPCODE_VARIAC_LENGTH_COMMAND
    uint8_t     Control;
    uint8_t     Miscillanious[5];
    uint8_t     AdditionalCommandBufferLength;
    uint16_t    ServiceAction;
}SCSI_VARIAC_LENGTH_COMMAND_DATA_BUFFER_HEADER, * PSCSI_VARIAC_LENGTH_COMMAND_DATA_BUFFER_HEADER;

#define SAM_SATUS_GOOD                          0x00
#define SAM_SATUS_CHECK_CONDITION               0x02
#define SAM_SATUS_CONDITION_MET                 0x04
#define SAM_SATUS_BUSY                          0x08
#define SAM_SATUS_INTERMEDIATE                  0x10
#define SAM_SATUS_INTERMEDIATE_CONDITION_MET    0x14
#define SAM_SATUS_RESERVATION_CONFLICT          0x18
#define SAM_SATUS_COMMAND_TERMINATED            0x22
#define SAM_SATUS_TASK_SET_FULL                 0x28
#define SAM_SATUS_ACA_ACTIVE                    0x30
#define SAM_SATUS_TASK_ABORTED                  0x40

#define SAM_STATUS_BITS                         0xFE

#define SENCE_KEY_NO_SENCE                  0x00
#define SENCE_KEY_REVOVERED_ERROR           0x01
#define SENCE_KEY_NOT_READY                 0x02
#define SENCE_KEY_MEDIUM_ERROR              0x03
#define SENCE_KEY_HARDWARE_ERROR            0x04
#define SENCE_KEY_INVALID_REQUEST           0x05
#define SENCE_KEY_UNIT_NEEDS_ATTENTION      0x06
#define SENCE_KEY_DATA_PROTECT              0x07
#define SENCE_KEY_BLANK_CHECK               0x08
#define SENCE_KEY_VENDOR_SPECIFIC           0x09
#define SENCE_KEY_COPY_ABORTED              0x0A
#define SENCE_KEY_COMMAND_ABORTED           0x0B
#define SENCE_KEY_VOLUME_OVERFLOW           0x0D
#define SENCE_KEY_MISCILLANIOUS_COMPARE     0x0E
#define SENCE_KEY_COMPLETED                 0x0F

#define DEVICE_TYPE_DISK                    0x00
#define DEVICE_TYPE_TAPE                    0x01
#define DEVICE_TYPE_PRINTER                 0x02
#define DEVICE_TYPE_PROCESSOR               0x03
#define DEVICE_TYPE_WORM                    0x04
#define DEVICE_TYPE_ROM                     0x05
#define DEVICE_TYPE_SCANNER                 0x06
#define DEVICE_TYPE_MOD                     0x07
#define DEVICE_TYPE_MEDIUM_CHANGER          0x08
#define DEVICE_TYPE_COMMUNICATIONS          0x09
#define DEVICE_TYPE_RAID                    0x0C
#define DEVICE_TYPE_ECLOSURE                0x0D
#define DEVICE_TYPE_RBC                     0x0E
#define DEVICE_TYPE_OSD                     0x11
#define DEVICE_TYPE_ZBC                     0x14
#define DEVICE_TYPE_WLUN                    0x1E
#define DEVICE_TYPE_NO_LUN                  0x7F

#define SCSI_INTERFACE_PROTOCOL_FCP         0
#define SCSI_INTERFACE_PROTOCOL_SPI         1
#define SCSI_INTERFACE_PROTOCOL_SSA         2
#define SCSI_INTERFACE_PROTOCOL_SBP         3
#define SCSI_INTERFACE_PROTOCOL_SRP         4
#define SCSI_INTERFACE_PROTOCOL_ISCSI       5
#define SCSI_INTERFACE_PROTOCOL_SAS         6
#define SCSI_INTERFACE_PROTOCOL_ADT         7
#define SCSI_INTERFACE_PROTOCOL_ATA         8
#define SCSI_INTERFACE_PROTOCOL_USSPECIFIED 0xF

typedef struct _SCSI_LUN{
    uint8_t     ScsiLunDaa[8];
}SCSI_LUN, * PSCSI_LUN;

typedef struct _SCSI_IO_GROUP_DESCRIPTOR{
    uint8_t     IcEnable    :   1;
    uint8_t     CsEnable    :   1;
    uint8_t     StEnable    :   1;
    uint8_t     Reserved1   :   3;
    uint8_t     IAHM        :   2;
    uint8_t     Reserved2[3];
    uint8_t     LbmDescType :   4;
    uint8_t     RlBsr       :   2;
    uint8_t     Reserved3   :   1;
    uint8_t     AcdLu       :   1;
    uint8_t     Parameters[2];
    uint8_t     Reserved4;
    uint8_t     Reserved5[8];
}SCSI_IO_GROUP_DESCRIPTOR, * PSCSI_IO_GROUP_DESCRIPTOR;

//Big Endian
typedef struct _SCSI_STREAM_STATUS{
    uint8_t     Reserved1   :   7;
    uint8_t     Permit      :   1;
    uint8_t     Reserved2;
    uint16_t    StreamID;
    uint8_t     RelativeTime:   6;
    uint8_t     Reserved3   :   2;
    uint8_t     Reserved4[3];   
}SCSI_STREAM_STATUS, * PSCSI_STREAM_STATUS;

//Big Endian
typedef struct _SCSI_STREAM_STATUS_HEADER{
    uint32_t            ArrayLength;
    uint16_t            Reserved;
    uint16_t            OpenStreams;
    SCSI_STREAM_STATUS  StreamStatus[];
}SCSI_STREAM_STATUS_HEADER, * PSCSI_STREAM_STATUS_HEADER;

#define SCSI_ASYM_ACCESS_STATE_OPTIMAL          0x00
#define SCSI_ASYM_ACCESS_STATE_ACTIVE           0x01
#define SCSI_ASYM_ACCESS_STATE_STANDBY          0x02
#define SCSI_ASYM_ACCESS_STATE_UNAVAILABLE      0x03
#define SCSI_ASYM_ACCESS_STATE_LBA              0x04
#define SCSI_ASYM_ACCESS_STATE_OFFLINE          0x0E
#define SCSI_ASYM_ACCESS_STATE_TRANSITIONING    0x0F

#define SCSI_RTGS_ACCESS_STATE_BITS         0x0F
#define SCSI_RTGS_ACCESS_STATE_PREFERED     0x80

#define ZBC_ZONE_REPORT_OPTION_ALL                      0x00
#define ZBC_ZONE_REPORT_OPTION_EMPTY                    0x01
#define ZBC_ZONE_REPORT_OPTION_IMPLICIT_OPEN            0x02
#define ZBC_ZONE_REPORT_OPTION_EXPLICIT_OPEN            0x03
#define ZBC_ZONE_REPORT_OPTION_CLOSED                   0x04
#define ZBC_ZONE_REPORT_OPTION_FULL                     0x05
#define ZBC_ZONE_REPORT_OPTION_READ_ONLY                0x06
#define ZBC_ZONE_REPORT_OPTION_OFFLINE                  0x07
#define ZBC_ZONE_REPORT_OPTION_NEED_RESET_WP            0x10
#define ZBC_ZONE_REPORT_OPTION_NON_SEQUENTIAL_WRITE     0x11
#define ZBC_ZONE_REPORT_OPTION_NON_WP                   0x3F

#define ZBC_ZONE_REPORT_PARTIAL                         0x80

#define ZBC_ZONE_COMMAND_NO_WP              0x00
#define ZBC_ZONE_COMMAND_EMPTY              0x01
#define ZBC_ZONE_COMMAND_IMPLICIT_OPEN      0x02
#define ZBC_ZONE_COMMAND_EXPLICIT_OPEN      0x03
#define ZBC_ZONE_COMMAND_CLOSED             0x04
#define ZBC_ZONE_COMMAND_READ_ONLY          0x0D
#define ZBC_ZONE_COMMAND_FULL               0x0E
#define ZBC_ZONE_COMMAND_OFLINE             0x0F

#define ZBC_CONSTANT_ZONE_LENGTH            0x01
#define ZBC_CONSTANT_ZONE_START_OFFSET      0x08

#define SCSI_VERSION_FCP4       0x0A40
#define SCSI_VERSION_ISCSI      0x0960
#define SCSI_VERSION_SAM5       0x00A0  
#define SCSI_VERSION_SAS3       0x0C60
#define SCSI_VERSION_SBC3       0x04C0
#define SCSI_VERSION_SBP3       0x0980
#define SCSI_VERSION_SPC4       0x0460
#define SCSI_VERSION_SRP        0x0940

#define SCSI_SUPPORT_OPCODE_NO_INFFORMATION     0
#define SCSI_SUPPORT_OPCODE_NOT_SUPPORTED       1
#define SCSI_SUPPORT_OPCODE_FULL                3
#define SCSI_SUPPORT_OPCODE_VENDOR              5

#define SCSI_CONTROL_BITS                       0
#define SCSI_GROUP_NUMBER_BITS                  0

#endif //_SCSI_PROTOCOL_H

#ifndef _ISCSI_PROTOCOL_H
#define _ISCSI_PROTOCOL_H



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
    SCSI_LUN      ScsiLun;
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
    SCSI_LUN      Lun;
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
    uint8_t     ExtendedCommandDataBuffer[SCSI_MAXIMUM_VARIAC_LENGTH_COMMAND_DATA_BUFFER_SIZE - ISCSI_COMMAND_BUFFER_SIZE];
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
    SCSI_LUN    Lun;
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
    SCSI_LUN        Lun;
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
    SCSI_LUN        Lun;
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
    SCSI_LUN        Lun;
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
    SCSI_LUN        Lun;
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
    SCSI_LUN        Lun;
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
    SCSI_LUN        Lun;
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
#endif//_ISCSI_PROTOCOL_H
#endif //C++