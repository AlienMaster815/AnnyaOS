#ifndef _SCSI_CORE_EXTERNAL_H
#define _SCSI_CORE_EXTERNAL_H

#include <cstdint.h>
#include <kernel/XArray.h>

//Command data types are in Big Endian (32 : 24 : 16 : 8 : 0)

typedef struct PACKED _SCSI_CDB6_COMMAND{
    UINT8   OpCode;
    UINT8   MsbMci;
    UINT16  Lba;
    UINT8   TpaLength;
    UINT8   Control;
}SCSI_CDB6_COMMAND, * PSCSI_CDB6_COMMAND;

typedef struct PACKED _SCSI_CDB10_COMMAND{
    UINT8   OpCode;
    UINT8   ServiceActionMci;
    UINT32  Lba;
    UINT8   Mci;
    UINT16  TpaLength;
    UINT8   Control;
}SCSI_CDB10_COMMAND, * PSCSI_CDB10_COMMAND;

typedef struct PACKED _SCSI_CDB12_COMMAND{
    UINT8   OpCode;
    UINT8   ServiceActionMci;
    UINT32  Lba;
    UINT32  TpaLength;
    UINT8   Mci;
    UINT8   Control;
}SCSI_CDB12_COMMAND, * PSCSI_CDB12_COMMAND;

typedef struct PACKED _SCSI_CDB16_COMMAND{
    UINT8   OpCode;
    UINT64  Lba;
    UINT32  TpaLength;
    UINT8   Mci;
    UINT8   Control;
}SCSI_CDB16_COMMAND, * PSCSI_CDB16_COMMAND;


typedef struct PACKED _SCSI_CDBVAR_COMMAND_HEADER{
    UINT8   OpCode;
    UINT8   Control;
    UINT8   Mci[5];
    UINT8   CdbAdditionalLength;
    UINT16  ServiceAction;
}SCSI_CDBVAR_COMMAND_HEADER, * PSCSI_CDBVAR_COMMAND_HEADER;

typedef struct PACKED _SCSI_CDBVAR_COMMAND{
    SCSI_CDBVAR_COMMAND_HEADER  CommandHeader;
    UINT8                       ServiceActionData[];
}SCSI_CDBVAR_COMMAND, * PSCSI_CDBVAR_COMMAND;

typedef struct PACKED _SCSI_LONG_LBA_CDBVAR_COMMAND{
    UINT8   OpCode;
    UINT8   Control;
    UINT8   Mci[5];
    UINT8   CdbAdditionalLength;
    UINT16  ServiceAction;
    UINT8   MciFuaDpoMci;
    UINT8   Mci2;
    UINT64  Lba;
    UINT64  Mci3;
    UINT32  TpaLength;
}SCSI_LONG_LBA_CDBVAR_COMMAND, * PSCSI_LONG_LBA_CDBVAR_COMMAND;

typedef struct PACKED _SCSI_DESCRIPTOR_FORMAT_SENCE_DATA{
    UINT8   ResponceCode;
    UINT8   SenseKey;
    UINT8   Asc;
    UINT8   AscQualifier;
    UINT8   Reserved[3];
    UINT8   AditionalSenceLength;
    UINT8   SenceDataDescriptorBuffer[];
}SCSI_DESCRIPTOR_FORMAT_SENCE_DATA, * PSCSI_DESCRIPTOR_FORMAT_SENCE_DATA;

typedef struct PACKED _SCSI_SENSE_DATA_DESCRIPTOR_FORMAT{
    UINT8   DescriptorType;
    UINT8   AdditionalLength;
    UINT8   SenceDataSpecific[];
}SCSI_SENSE_DATA_DESCRIPTOR_FORMAT, * PSCSI_SENSE_DATA_DESCRIPTOR_FORMAT;

//scsi sence data descriptor
typedef struct PACKED _SSDD_INFO_STRUCTURE{
    UINT8   DescriptorType;     //SSDD_TYPE_INFO        0x00
    UINT8   AdditionalLength;   //SSDD_TYPE_INFO_SIZE   0x0A
    UINT8   ReservedValid;      //(1 << 7)
    UINT8   Reserved;
    UINT64  Information;
}SSDD_INFO_STRUCTURE, * PSSDD_INFO_STRUCTURE;

typedef struct PACKED _SSDD_COMMAND_SPECIFIC_INFO_STRUCTURE{
    UINT8   DescriptorType;     //SSDD_TYPE_COMMAND_SPECIFIC_INFO       0x01
    UINT8   AdditionalLength;   //SSDD_TYPE_COMMAND_SPECIFIC_INFO_SIZE  0x0A
    UINT8   Reserved[2];
    UINT64  Information;
}SSDD_COMMAND_SPECIFIC_INFO_STRUCTURE, * PSSDD_COMMAND_SPECIFIC_INFO_STRUCTURE;

typedef struct PACKED _SSDD_SENCE_KEY_SPECIFIC_STRUCTURE{
    UINT8   DescriptorType;     //SSDD_SENCE_KEY_SPECIFIC       0x02
    UINT8   AdditionalLength;   //SSDD_TYPE_KEY_SPECIFIC_SIZE   0x06
    UINT8   Reserved[2];
    UINT8   SenceKeySpecific[3];//[0](1 << 7)
    UINT8   Reserved2;
}SSDD_SENCE_KEY_SPECIFIC_STRUCTURE, * PSSDD_SENCE_KEY_SPECIFIC_STRUCTURE;

typedef struct PACKED _SSDD_SKS_ILLEGAL_REQUEST{
    UINT8   BpBpvCdSksv;
    UINT16  FieldPointer;
}SSDD_SKS_ILLEGAL_REQUEST, * PSSDD_SKS_ILLEGAL_REQUEST;

typedef struct PACKED _SSDD_SKS_HMR_ERROR{
    UINT8   Sksv;
    UINT16  Arc;
}SSDD_SKS_HMR_ERROR, * PSSDD_SKS_HMR_ERROR,
    SSDD_SKS_HARDWARE_ERROR, * PSSDD_SKS_HARDWARE_ERROR,
        SSDD_SKS_MEDIUM_ERROR, * PSSDD_SKS_MEDIUM_ERROR,
            SSDD_SKS_RECOVERED_ERROR, * PSSDD_SKS_RECOVERED_ERROR;

typedef struct PACKED _SSDD_SKS_NO_SR{
    UINT8   Sksv;
    UINT16  ProgressIndication;
}SSDD_SKS_NO_SR, * PSSDD_SKS_NO_SR,
    SSDD_SKS_NO_SENSE, * PSSDD_SKS_NO_SENSE,
        SSDD_SKS_NOT_READY, * PSSDD_SKS_NOT_READY;

typedef struct PACKED _SCSI_SKS_COPY_ABORTED{
    UINT8   SksvSdBpvBitPointer;
    UINT16  FieldPointer;
}SCSI_SKS_COPY_ABORTED, * PSCSI_SKS_COPY_ABORTED;

typedef struct PACKED _SCSI_SKS_UNIT_ATTENTION{
    UINT8   SksvOverflow;
    UINT16  Reserved;
}SCSI_SKS_UNIT_ATTENTION, * PSCSI_SKS_UNIT_ATTENTION;

typedef struct PACKED _SSDD_FIELD_REPLACEABLE_UNIT_STRUCTURE{
    UINT8   DescriptorType;     //SSDD_FIELD_REPLACEABLE_UNIT 0x03
    UINT8   AdditionalLength;   //0x02
    UINT8   Reserved;
    UINT8   Fruc;
}SSDD_FIELD_REPLACEABLE_UNIT_STRUCTURE, * PSSDD_FIELD_REPLACEABLE_UNIT_STRUCTURE;

typedef struct PACKED _SSDD_PROGRESS_INDICATIONS_SENSE_DATA_STRUCTURE{
    UINT8   DescriptorType;     //SSDD_ANOTHER_PROGRESS_INDICATION 0x0A
    UINT8   AdditionalLength;   //0x06
    UINT8   SenseKey;
    UINT8   Asc;
    UINT8   AscQualifier;
    UINT8   Reserved;
    UINT16  ProgressIndication;
}SSDD_PROGRESS_INDICATIONS_SENSE_DATA_STRUCTURE, * PSSDD_PROGRESS_INDICATIONS_SENSE_DATA_STRUCTURE;

typedef struct PACKED _SSDD_FIXED_FORMAT_SENSE_DATA{
    UINT8   ResponceCodeValid;
    UINT8   SenseKeyIliEomFileMark;
    UINT32  Information;
    UINT8   AdditionalLength;
    UINT32  CommandSpecificInfo;
    UINT8   Asc;
    UINT8   AscQualifier;
    UINT8   Fruc;
    UINT8   SenceKeySpecific[3];
    UINT8   AdditionalSenseBytes[];
}SSDD_FIXED_FORMAT_SENSE_DATA, * PSSDD_FIXED_FORMAT_SENSE_DATA;

typedef struct PACKED _SSDD_VENDOR_SPECIFIC_SENSE_DATA_DESCRIPTOR_FORMAT_STRUCTURE{
    UINT8   DescriptorType; //0x80 - 0xFF
    UINT8   AdditionalLength;
    UINT8   Data[];
}SSDD_VENDOR_SPECIFIC_SENSE_DATA_DESCRIPTOR_FORMAT_STRUCTURE, * PSSDD_VENDOR_SPECIFIC_SENSE_DATA_DESCRIPTOR_FORMAT_STRUCTURE;

typedef struct PACKED _SCSI_BACKGROUND_CONTROL_COMMAND_STRUCTURE{
    UINT8   OpCode;         //SCSI_COMMAND_BACKGROUND_CONTROL           0x9E
    UINT8   ServiceAction;  //SCSI_SERVICE_ACTION_BACKGROUND_CONTROL    0x15
    UINT8   BoControl;
    UINT8   BoTime;
    UINT8   Reserved[11];
    UINT8   Control;
}SCSI_BACKGROUND_CONTROL_COMMAND_STRUCTURE, * PSCSI_BACKGROUND_CONTROL_COMMAND_STRUCTURE;

typedef struct PACKED _SCSI_CHANGE_DEFINITION_COMMAND_STRUCTURE{
    UINT8   OpCode;         //SCSI_COMMAND_CHANGE_DEFINITION 0x40
    UINT8   Reserved;
    UINT8   Save;
    UINT8   DefParam;
    UINT8   Reserved2[4];
    UINT8   ParamLength;
    UINT8   Control;
}SCSI_CHANGE_DEFINITION_COMMAND_STRUCTURE, * PSCSI_CHANGE_DEFINITION_COMMAND_STRUCTURE;

typedef struct PACKED _SCSI_FORMAT_UNIT_COMMAND_STRUCTURE{
    UINT8   OpCode;                 //SCSI_COMMAND_FORMAT_UNIT 0x04
    UINT8   FmtInfoLlFmtDataClDfl;
    UINT8   VendorSpecific;
    UINT8   Reserved;
    UINT8   Ffmt;
    UINT8   Control;
}SCSI_FORMAT_UNIT_COMMAND_STRUCTURE, * PSCSI_FORMAT_UNIT_COMMAND_STRUCTURE;

typedef struct PACKED _SCSI_GET_LBA_STATUS_COMMAND_STRUCTURE{
    UINT8   OpCode;         //SCSI_COMMAND_GET_LBA_STATUS           0x9E
    UINT8   ServiceAction;  //SCSI_SERVICE_ACTION_GET_LBA_STATUS    0x12
    UINT64  StartingLba;
    UINT32  AllocationLength;
    UINT8   Reserved;
    UINT8   Control;
}SCSI_GET_LBA_STATUS_COMMAND_STRUCTURE, * PSCSI_GET_LBA_STATUS_COMMAND_STRUCTURE;

//Start Here



#define SCSI_CDBVAR_COMMAND_OPCODE                  0x7F

#define SCSI_OPCODE_GROUP_CODE_6BYTE_COMMAND        0b000
#define SCSI_OPCODE_GROUP_CODE_10_1BYTE_COMMAND     0b001
#define SCSI_OPCODE_GROUP_CODE_10_2BYTE_COMMAND     0b010
#define SCSI_OPCODE_GROUP_CODE_16_BYTE_COMMAND      0b100
#define SCSI_OPCODE_GROUP_CODE_12_BYTE_COMMAND      0b101

#define SCSI_SENSE_DATA_CURRENT_FIXED_ERROR         0x70
#define SCSI_SENSE_DATA_DEFERED_FIXED_ERROR         0x71
#define SCSI_SENSE_DATA_CURRENT_DESCRIPTOR_ERROR    0x72
#define SCSI_SENSE_DATA_DEFERED_DESCRIPTOR_ERROR    0x73

//Scsi Sence Data Descriptor
#define SSDD_TYPE_INFO                              0x00
#define SSDD_TYPE_COMMAND_SPECIFIC_INFO             0x01
#define SSDD_TYPE_SENCE_KEY_SPECIFIC                     0x02
#define SSDD_TYPE_FIELD_REPLACEABLE_UNIT                 0x03
#define SSDD_TYPE_STREAM_COMMANDS                        0x04
#define SSDD_TYPE_BLOCK_COMMANDS                         0x05
#define SSDD_TYPE_OSD_OBJECT_IDENTIFICATION              0x06
#define SSDD_TYPE_OSD_RESPONSE_INTEGRITY_CHECK_VALUE     0x07
#define SSDD_TYPE_OSD_ATTRIBUTE_IDENTIFICATION           0x08
#define SSDD_TYPE_ATA_RETURN                             0x09
#define SSDD_TYPE_ANOTHER_PROGRESS_INDICATION            0x0A

#define SSDD_TYPE_INFO_SIZE                         0x0A
#define SSDD_TYPE_COMMAND_SPECIFIC_INFO_SIZE        0x0A
#define SSDD_TYPE_KEY_SPECIFIC_SIZE                 0x06

#define SCSI_SENSE_KEY_NO_SENCE             0x00
#define SCSI_SENSE_KEY_RECOVERED_ERROR      0x01
#define SCSI_SENSE_KEY_NOT_READY            0x02
#define SCSI_SENSE_KEY_MEDIUM_ERROR         0x03
#define SCSI_SENSE_KEY_HARDWARE_ERROR       0x04
#define SCSI_SENSE_KEY_ILLEGAL_REQUEST      0x05
#define SCSI_SENSE_KEY_UNIT_ATTENTION       0x06
#define SCSI_SENSE_KEY_DATA_PROTECT         0x07
#define SCSI_SENSE_KEY_BLANK_CHECK          0x08
#define SCSI_SENSE_KEY_VENDOR_SPECIFIC      0x09
#define SCSI_SENSE_KEY_COPY_ABORTED         0x0A
#define SCSI_SENSE_KEY_ABORTED_COMMAND      0x0B
#define SCSI_SENSE_KEY_VOLUME_OVERFLOW      0x0D
#define SCSI_SENSE_KEY_MISCOMPARE           0x0E
#define SCSI_SENSE_KEY_COMPLETED            0x0F

#define SCSI_ASC_NO_ADDITIONAL_SENSE_INFO                           0x00
#define SCSI_ASC_NO_INDEX_LBS                                       0x01
#define SCSI_ASC_NO_SEEK_COMPLETE                                   0x02
#define SCSI_ASC_PERIPHERAL_DEVICE_WRITE_FAULT                      0x03
#define SCSI_ASC_WRITE_FAULT_DATA_CURRUPTION                        0x03
#define SCSI_ASC_LUNR_CAUSE_NOT_REPORTABLE                          0x04
#define SCSI_ASC_LUNR_BECOMING_READY                                0x04
#define SCSI_ASC_LUNR_START_UNIT_REQUIRED                           0x04
#define SCSI_ASC_LUNR_MANUAL_INTERVENTION_REQUIRED                  0x04
#define SCSI_ASC_LUNR_FORMAT_IN_PROGRESS                            0x04
#define SCSI_ASC_LUNR_SELF_TEST_IN_PROGRESS                         0x04
#define SCSI_ASC_LUNR_NVC_RECOVERY_IN_PROGRESS                      0x04
#define SCSI_ASC_LUNR_NOTIFY_ENABLE_SPINUP_REQUIRED                 0x04
#define SCSI_ASC_LUNR_POWER_CYCLE_REQUIRED                          0x04
#define SCSI_ASC_LUNR_SUPER_CERTIFY_IN_PROGRESS                     0x04
#define SCSI_ASC_LOGICAL_UNIT_COMMUNICATION_FAILURE                 0x08
#define SCSI_ASC_LOGICAL_UNIT_COMMUNICATION_TIME_OUT                0x08
#define SCSI_ASC_LOGICAL_UNIT_COMMUNICATION_PARITY_ERROR            0x08
#define SCSI_ASC_TRACK_FOLLOWING_ERROR                              0x09
#define SCSI_ASC_SERVO_FAULT                                        0x09
#define SCSI_ASC_HEAD_SELECT_FAULT			                        0x09
#define SCSI_ASC_WTALOCOARFF				                        0x09
#define SCSI_ASC_RFHL5GC				                            0x09
#define SCSI_ASC_CINBTQISWTROB				                        0x09
#define SCSI_ASC_SCCAPOST				                            0x09
#define SCSI_ASC_ERROR_LOG_OVERFLOW			                        0x0A
#define SCSI_ASC_FAILED_TO_WRITE_SUPER_CERTIFY_LOG_FILE             0x0A
#define SCSI_ASC_FAILED_TO_READ_SUPER_CERTIFY_LOG_FILE	            0x0A
#define SCSI_ASC_ABORTED_COMMAND			                        0x0B
#define SCSI_ASC_WARNING_SPECIFIED_TEMPERATURE_EXCEEDED	            0x0B
#define SCSI_ASC_WARNING_ENCLOSURE_DEGRADED		                    0x0B
#define SCSI_ASC_WRITE_ERROR				                        0x0C
#define SCSI_ASC_WRITE_ERROR_RECOVERED_WITH_REALLOCATION            0x0C
#define SCSI_ASC_WRITE_ERROR_AUTO_REALLOCATION_FAILED	            0x0C
#define SCSI_ASC_WRITE_ERROR_RECOMEND_REASSIGNMENT	                0x0C
#define SCSI_ASC_WRITE_ERROR_TO_MANY_ERROR_RECOVERY_REVS            0x0C
#define SCSI_ASC_VOLUME_OVERFLOW_CONSTANTS		                    0x0D
#define SCSI_ASC_DATA_MISCOMPARE			                        0x0E
#define SCSI_ASC_ID_CRC_ECC_ERROR			                        0x10
#define SCSI_ASC_UNRECOVERED_READ_ERROR			                    0x11
#define SCSI_ASC_READ_ENTIRES_EXAUGHSTED		                    0x11
#define SCSI_ASC_ERROR_TOO_LONG_TO_CORRECT		                    0x11
#define SCSI_ASC_READ_ERROR_AUTO_ALLOCATION_FAILED                  0x11
#define SCSI_ASC_READ_ERROR_TO_MANY_ERROR_RECOVERY_REVS	            0x11
#define SCSI_ASC_ADDRESS_MARK_NOT_FOUND_FOR_ID_FIELD	            0x12
#define SCSI_ASC_RECOVERED_DATA_WITHOUGHT_ECC_USING_LBI             0x12
#define SCSI_ASC_RECOVERED_DATA_WITH_ECC_USING_LBI                  0x12
#define SCSI_ASC_LOGICAL_BLOCK_NOT_FOUND                            0x14
#define SCSI_ASC_RECORD_NOT_FOUND                                   0x14
#define SCSI_ASC_RANDOM_POSITIONING_ERROR                           0x15
#define SCSI_ASC_MECHANICAL_POSITIONING_ERROR                       0x15
#define SCSI_ASC_POSITIONING_ERROR_DETECTED_BY_READ_OF_MED          0x15
#define SCSI_ASC_DATA_SYNCHRONIZATION_MARK_ERROR                    0x16
#define SCSI_ASC_RECOVERED_DATA_WITH_NO_ERROR_CORRECTION            0x17
#define SCSI_ASC_RECOVERED_DATA_USING_RETRIES                       0x17
#define SCSI_ASC_RECOVERED_DATA_USING_POSITIVE_OFFSET	            0x17
#define SCSI_ASC_RECOVERED_DATA_USING_NEGATIVE_OFFSET	            0x17
#define SCSI_ASC_RECOVERED_DATA_USING_PREVIOUS_LBI                  0x17
#define SCSI_ASC_RECOVERED_DATA_WITHOUGHT_ECC                       0x17
#define SCSI_ASC_RECOVERED_DATA_WITH_ECC                            0x18
#define SCSI_ASC_RECOVERED_DATA_WITH_ECC_AND_RETRIES	            0x18
#define SCSI_ASC_RECOVERED_DATA_WITH_ECC_OR_RETRIES                 0x18
#define SCSI_ASC_RECOVERED_DATA_RECOMEND_REASSIGNMENT	            0x18
#define SCSI_ASC_RECOVERED_DATA_WITH_ECC_AND_OFFSETS	            0x18
#define SCSI_ASC_RECOVERED_DATA_WITH_ECC_DATA_REWRITTEN	            0x18
#define SCSI_ASC_DEFECT_LIST_ERROR                                  0x19
#define SCSI_ASC_DEFECT_LIST_NOT_AVAILABLE                          0x19
#define SCSI_ASC_DEFECT_LIST_ERROR_IN_PRIMARY_LIST                  0x19
#define SCSI_ASC_DEFECT_LIST_ERROR_IN_GROWN_LIST                    0x19
#define SCSI_ASC_FEWER_THAN_50_DEFECT_LIST_COPIES                   0x19
#define SCSI_ASC_PARAMETER_LIST_LENGTH_ERROR                        0x1A
#define SCSI_ASC_SYNCHRONOUS_DATA_TRANSFER_ERROR                    0x1B
#define SCSI_ASC_DEFECT_LIST_NOT_FOUND                              0x1C
#define SCSI_ASC_PRIMARY_DEFECT_LIST_NOT_FOUND                      0x1C
#define SCSI_ASC_GROWN_DEFECT_LIST_NOT_FOUND                        0x1C
#define SCSI_ASC_SEAGATE_UNIQUE_DIAGNOSTIC_CODE                     0x1C
#define SCSI_ASC_MISCOMPARE_DURING_VERIFY_OPERATION                 0x1D
#define SCSI_ASC_NODOTASTTRDCCH                                     0x1F
#define SCSI_ASC_INVALID_COMMAND_OPERATION_CODE                     0x20
#define SCSI_ASC_INVALID_LINKED_COMMAND_OPERATION_CODE              0x20
#define SCSI_ASC_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE                 0x21
#define SCSI_ASC_INVALID_FIELD_IN_CDB                               0x24
#define SCSI_ASC_ILLEGAL_QUEUE_TYPE_FOR_CDB                         0x24
#define SCSI_ASC_INVALID_LBA_IN_LINKED_COMMAND                      0x24
#define SCSI_ASC_INVALID_LINKED_COMMAND_OPERATION_CODE2             0x24
#define SCSI_ASC_ILLEGAL_G_TO_P_OPERATION_REQUEST                   0x24
#define SCSI_ASC_LOGICAL_UNIT_NOT_SUPPORTED                         0x25
#define SCSI_ASC_INVALID_FIELD_IN_PARAMETER_LIST                    0x26
#define SCSI_ASC_PARAMETER_NOT_SUPPORTED                            0x26
#define SCSI_ASC_PARAMETER_VALUE_INVALID                            0x26
#define SCSI_ASC_INVALID_FIELD_THRESHOLD_PARAMETER                  0x26
#define SCSI_ASC_INVALID_RELEASE_ACTIVE_PERSISTENT_RESERVE          0x26
#define SCSI_ASC_FAILED_TO_READ_VALID_LOG_DUMP_DATA                 0x26
#define SCSI_ASC_TMS_FIRMWARE_TAG_PARAMETER_INVALID                 0x26
#define SCSI_ASC_CHECK_SUM_PARAMETER_INVALID                        0x26
#define SCSI_ASC_FIRMWARE_TAG_PARAMETER_INVALID                     0x26
#define SCSI_ASC_WRITE_PROTECTED                                    0x27
#define SCSI_ASC_FLASHING_LED_OCCOURED                              0x29
#define SCSI_ASC_POWER_ON_RESET_OR_BUS_RESET_OCCOURED               0x29
#define SCSI_ASC_POWER_ON_RESET_OCCOURED                            0x29
#define SCSI_ASC_SCSI_BUS_RESET_OCCOURED                            0x29
#define SCSI_ASC_BUS_DEVICE_RESET_FUNCTION_OCCOURED                 0x29
#define SCSI_ASC_INTERNAL_RESET_OCCOURED                            0x29
#define SCSI_ASC_TRANSCEIVER_MODE_CHANGED_TO_SINGLE_ENDED           0x29
#define SCSI_ASC_TRANSCEIVER_MODE_CHANGED_TO_LVD                    0x29
#define SCSI_ASC_WRITE_LOG_DUMP_DATA_TO_DISK_SUCCESS_NEXLOS         0x29
#define SCSI_ASC_WRITE_LOG_DUMP_DATA_TO_DISK_FAILED                 0x29
#define SCSI_ASC_WRITE_LOG_DUMP_ENTRY_INFORMATION_FAILED            0x29
#define SCSI_ASC_RESERVED_DISK_SPACE                                0x29
#define SCSI_ASC_SDBP_SELF_TEST_CONTIAINED_ERROR                    0x29
#define SCSI_ASC_SDBP_INCOMING_BUFFER_OVERFLOW                      0x29
#define SCSI_ASC_COLD_RESET_FLASHING_LED                            0x29
#define SCSI_ASC_WARM_RESET_FLASHING_LED                            0x29
#define SCSI_ASC_MODE_PARAMETERS_CHANGED                            0x2A
#define SCSI_ASC_LOG_PARAMETERS_CHANGED                             0x2A
#define SCSI_ASC_RESERVATION_PREEMTED                               0x2A
#define SCSI_ASC_RESERVATION_RELEASED                               0x2A
#define SCSI_ASC_REGISTRATION_PREEMTED                              0x2A
#define SCSI_ASC_COMMAND_SEQUNCE_ERROR                              0x2C
#define SCSI_ASC_TAGGED_COMMANDS_CLEARED_BY_ANOTHER_INIT            0x2F
#define SCSI_ASC_MEDIUM_FORMAT_CORRUPTED                            0x31
#define SCSI_ASC_CORRUPTION_IN_RW_FORMAT_REGISTER                   0x31
#define SCSI_ASC_CORRUPTED_WWN_IN_DRIVE_INFORMATION_FILE            0x31
#define SCSI_ASC_NO_DEFECT_SPARE_LOCATION_AVAILABLE                 0x32
#define SCSI_ASC_DEFECT_LIST_UPDATE_ERROR                           0x32
#define SCSI_ASC_NO_SPARES_AVAILABLE                                0x32
#define SCSI_ASC_DEFECT_LIST_LARGER_THAT_ALLOCATION                 0x32
#define SCSI_ASC_FLASH_NOT_READY_FOR_ACCESS                         0x33
#define SCSI_ASC_UNSPECIFIED_ENCLOSURE_SERVICED_FAILURE             0x35
#define SCSI_ASC_UNSUPPORTED_ENCLOSURE_FUNCTION                     0x35
#define SCSI_ASC_ENCLOSURE_SERVICE_UNAVAILABLE                      0x35
#define SCSI_ASC_ENCLOSURE_TRANSFER_FAILURE                         0x35
#define SCSI_ASC_ENCLOSURE_TRANSFER_REFUSED                         0x35
#define SCSI_ASC_PARAMETER_ROUNDED                                  0x37
#define SCSI_ASC_INVALID_BITS_IN_IDENTIFY_MESSAGE                   0x3D
#define SCSI_ASC_LOGICAL_UNIT_FAILED_SELF_TEST                      0x3E
#define SCSI_ASC_LOGICAL_UNIT_HAS_NOT_SELF_CONFIGURED_YET           0x3E
#define SCSI_ASC_TARGET_OPERATING_CONDITIONS_CHANGED                0x3F
#define SCSI_ASC_DEVICE_INTERNAL_RESET_OCCOURED                     0x3F
#define SCSI_ASC_CHANGED_OPERATIONG_DEFINITION                      0x3F
#define SCSI_ASC_DEVICE_IDENTIFIER_CHANGED                          0x3F
#define SCSI_ASC_ECHO_BUFFER_OVERWRITTEN                            0x3F
#define SCSI_ASC_BUFFER_CONTENTS_HAVE_CHANGED                       0x3F
#define SCSI_ASC_INVALID_APM_PARAMETERS                             0x3F
#define SCSI_ASC_WWN_MISMATCH                                       0x3F
#define SCSI_ASC_DRAM_PARITY_ERROR                                  0x40
#define SCSI_ASC_SPINUP_ERROR_RECOVERED_WITH_RETRIES                0x40
#define SCSI_ASC_POWER_ON_OR_SELF_TEST_FAILURE                      0x42
#define SCSI_ASC_PORT_A_FAILED_LOOPBACK_TEST                        0x42
#define SCSI_ASC_PORT_B_FAILED_LOOPBACK_TEST                        0x42
#define SCSI_ASC_MESSAGE_REJECT_ERROR                               0x43
#define SCSI_ASC_INTERNAL_TARGET_FAILURE                            0x44
#define SCSI_ASC_DATA_INTEGRITY_CHECK_FAILED_ON_VERIFY              0x44
#define SCSI_ASC_DATA_INTEGRITY_CHECK_FAILED_ON_WRITE               0x44
#define SCSI_ASC_XOR_CDB_CHECK_ERROR                                0x44
#define SCSI_ASC_SELECT_RESELECT_FAILURE                            0x45
#define SCSI_ASC_SCSI_PARITY_ERROR                                  0x47
#define SCSI_ASC_INFORMATION_UNIT_CRC_ERROR                         0x47
#define SCSI_ASC_FIBRE_CHANNEL_SEQUENCE_ERROR                       0x47
#define SCSI_ASC_INITIATOR_DETECTED_ERROR_MESSAGE_RECIVED           0x48
#define SCSI_ASC_INVALID_MESSAGE_RECEIVED                           0x49
#define SCSI_ASC_DATA_PHASE_ERROR                                   0x4B
#define SCSI_ASC_INVALID_TRANSFER_TAG                               0x4B
#define SCSI_ASC_TOO_MANY_WRITE_DATA                                0x4B
#define SCSI_ASC_ACK_NAK_TIMEOUT                                    0x4B
#define SCSI_ASC_NAK_RECIVED                                        0x4B
#define SCSI_ASC_DATA_OFFSET_ERROR                                  0x4B
#define SCSI_ASC_INITIATOR_RESPONCE_TIMEOUT                         0x4B
#define SCSI_ASC_LOGICAL_UNIT_FAILED_SELF_CONFIGURATION             0x4C
#define SCSI_ASC_OVERLAPPED_COMMANDS_ATTEMPTED                      0x4E
#define SCSI_ASC_XOR_CACHE_IS_NOT_AVAILABLE                         0x55
#define SCSI_ASC_PRKT_TABLE_IS_FULL                                 0x55
#define SCSI_ASC_LOG_EXCEPTION                                      0x5B
#define SCSI_ASC_THRESHOLD_CONDITION_MET                            0x5B
#define SCSI_ASC_LOG_COUNTER_AT_MAXIMUM                             0x5B
#define SCSI_ASC_LOG_LIST_CODES_EXHAUSTED                           0x5B
#define SCSI_ASC_RPL_STATUS_CHANGE                                  0x5C
#define SCSI_ASC_SPINDLES_SYNCHRONIZED                              0x5C
#define SCSI_ASC_SPINDLES_NOT_SYNCHRONIZED                          0x5C
#define SCSI_ASC_FAILURE_PREDICTION_THRESHOLD_EXCEEDED              0x5D
#define SCSI_ASC_FALSE_FAILURE_PREDICTION_THRESHOLD_EXCEEDED        0x5D
#define SCSI_ASC_VOLTAGE_FAILURE                                    0x65
#define SCSI_ASC_GENERAL_FIRMWARE_ERROR_QUALIFIER                   0x80
#define SCSI_ASC_IOEDC_ERROR_ON_READ                                0x80
#define SCSI_ASC_IOEDC_ERROR_ON_WRITE                               0x80
#define SCSI_ASC_HOST_PARITY_CHECK_FAILED                           0x80
#define SCSI_ASC_IOEDC_ERROR_ON_READ_DETECTED_BY_FORMATTER          0x80
#define SCSI_ASC_HOST_FIFO_PARRITY_ERROR_COMMON_BUFFER              0x80
#define SCSI_ASC_HOST_FIFO_PARRITY_ERROR_FRAME_BUFFER_LOGIC         0x80
#define SCSI_ASC_HOST_DATA_FRAME_BUFFER_PARITY_ERROR                0x80
#define SCSI_ASC_REASSIGN_POWER_FAIL_RECOVERY_FAILED                0x81
#define SCSI_ASC_LA_CHECK_ERROR_LCM_BIT_0                           0x81
#define SCSI_ASC_LA_CHECK_ERROR                                     0x81
#define SCSI_ASC_NREPORTED_DEFFERRED_ERRORS_HAVE_BEEN_LOGGED        0xB4

#define SCSI_ASCQ_NO_ADDITIONAL_SENSE_INFO                          0x00
#define SCSI_ASCQ_NO_INDEX_LBS                                      0x00
#define SCSI_ASCQ_NO_SEEK_COMPLETE                                  0x00
#define SCSI_ASCQ_PERIPHERAL_DEVICE_WRITE_FAULT                     0x00
#define SCSI_ASCQ_WRITE_FAULT_DATA_CURRUPTION                       0x86
#define SCSI_ASCQ_LUNR_CAUSE_NOT_REPORTABLE                         0x00
#define SCSI_ASCQ_LUNR_BECOMING_READY                               0x01
#define SCSI_ASCQ_LUNR_START_UNIT_REQUIRED                          0x02
#define SCSI_ASCQ_LUNR_MANUAL_INTERVENTION_REQUIRED                 0x03
#define SCSI_ASCQ_LUNR_FORMAT_IN_PROGRESS                           0x04
#define SCSI_ASCQ_LUNR_SELF_TEST_IN_PROGRESS                        0x09
#define SCSI_ASCQ_LUNR_NVC_RECOVERY_IN_PROGRESS                     0x0A
#define SCSI_ASCQ_LUNR_NOTIFY_ENABLE_SPINUP_REQUIRED                0x11
#define SCSI_ASCQ_LUNR_POWER_CYCLE_REQUIRED                         0x22
#define SCSI_ASCQ_LUNR_SUPER_CERTIFY_IN_PROGRESS                    0xF0
#define SCSI_ASCQ_LOGICAL_UNIT_COMMUNICATION_FAILURE                0x00
#define SCSI_ASCQ_LOGICAL_UNIT_COMMUNICATION_TIME_OUT               0x01
#define SCSI_ASCQ_LOGICAL_UNIT_COMMUNICATION_PARITY_ERROR           0x02
#define SCSI_ASCQ_TRACK_FOLLOWING_ERROR                             0x00
#define SCSI_ASCQ_SERVO_FAULT                                       0x01
#define SCSI_ASCQ_HEAD_SELECT_FAULT                                 0x04
#define SCSI_ASCQ_WTALOCOARFF				                        0x0D
#define SCSI_ASCQ_RFHL5GC				                            0x0E
#define SCSI_ASCQ_CINBTQISWTROB				                        0xF8
#define SCSI_ASCQ_SCCAPOST				                            0xFF
#define SCSI_ASCQ_ERROR_LOG_OVERFLOW			                    0x00
#define SCSI_ASCQ_FAILED_TO_WRITE_SUPER_CERTIFY_LOG_FILE            0x01
#define SCSI_ASCQ_FAILED_TO_READ_SUPER_CERTIFY_LOG_FILE	            0x02
#define SCSI_ASCQ_ABORTED_COMMAND			                        0x00
#define SCSI_ASCQ_WARNING_SPECIFIED_TEMPERATURE_EXCEEDED	        0x01
#define SCSI_ASCQ_WARNING_ENCLOSURE_DEGRADED		                0x02
#define SCSI_ASCQ_WRITE_ERROR				                        0x00
#define SCSI_ASCQ_WRITE_ERROR_RECOVERED_WITH_REALLOCATION           0x01
#define SCSI_ASCQ_WRITE_ERROR_AUTO_REALLOCATION_FAILED	            0x02
#define SCSI_ASCQ_WRITE_ERROR_RECOMEND_REASSIGNMENT	                0x03
#define SCSI_ASCQ_WRITE_ERROR_TO_MANY_ERROR_RECOVERY_REVS           0xFF
#define SCSI_ASCQ_VOLUME_OVERFLOW_CONSTANTS		                    0x00
#define SCSI_ASCQ_DATA_MISCOMPARE			                        0x00
#define SCSI_ASCQ_ID_CRC_ECC_ERROR			                        0x00
#define SCSI_ASCQ_UNRECOVERED_READ_ERROR			                0x00
#define SCSI_ASCQ_READ_ENTIRES_EXAUGHSTED		                    0x01
#define SCSI_ASCQ_ERROR_TOO_LONG_TO_CORRECT		                    0x02
#define SCSI_ASCQ_READ_ERROR_AUTO_ALLOCATION_FAILED                 0x04
#define SCSI_ASCQ_READ_ERROR_TO_MANY_ERROR_RECOVERY_REVS	        0xFF
#define SCSI_ASCQ_ADDRESS_MARK_NOT_FOUND_FOR_ID_FIELD	            0x00
#define SCSI_ASCQ_RECOVERED_DATA_WITHOUGHT_ECC_USING_LBI            0x01
#define SCSI_ASCQ_RECOVERED_DATA_WITH_ECC_USING_LBI                 0x02
#define SCSI_ASCQ_LOGICAL_BLOCK_NOT_FOUND                           0x00
#define SCSI_ASCQ_RECORD_NOT_FOUND                                  0x01
#define SCSI_ASCQ_RANDOM_POSITIONING_ERROR                          0x00
#define SCSI_ASCQ_MECHANICAL_POSITIONING_ERROR                      0x01
#define SCSI_ASCQ_POSITIONING_ERROR_DETECTED_BY_READ_OF_MED         0x02
#define SCSI_ASCQ_DATA_SYNCHRONIZATION_MARK_ERROR                   0x00
#define SCSI_ASCQ_RECOVERED_DATA_WITH_NO_ERROR_CORRECTION           0x00
#define SCSI_ASCQ_RECOVERED_DATA_USING_RETRIES                      0x01
#define SCSI_ASCQ_RECOVERED_DATA_USING_POSITIVE_OFFSET	            0x02
#define SCSI_ASCQ_RECOVERED_DATA_USING_NEGATIVE_OFFSET	            0x03
#define SCSI_ASCQ_RECOVERED_DATA_USING_PREVIOUS_LBI                 0x05
#define SCSI_ASCQ_RECOVERED_DATA_WITHOUGHT_ECC                      0x06
#define SCSI_ASCQ_RECOVERED_DATA_WITH_ECC                           0x00
#define SCSI_ASCQ_RECOVERED_DATA_WITH_ECC_AND_RETRIES	            0x01
#define SCSI_ASCQ_RECOVERED_DATA_WITH_ECC_OR_RETRIES                0x02
#define SCSI_ASCQ_RECOVERED_DATA_RECOMEND_REASSIGNMENT	            0x05
#define SCSI_ASCQ_RECOVERED_DATA_WITH_ECC_AND_OFFSETS	            0x06
#define SCSI_ASCQ_RECOVERED_DATA_WITH_ECC_DATA_REWRITTEN	        0x07
#define SCSI_ASCQ_DEFECT_LIST_ERROR                                 0x00
#define SCSI_ASCQ_DEFECT_LIST_NOT_AVAILABLE                         0x01
#define SCSI_ASCQ_DEFECT_LIST_ERROR_IN_PRIMARY_LIST                 0x02
#define SCSI_ASCQ_DEFECT_LIST_ERROR_IN_GROWN_LIST                   0x03
#define SCSI_ASCQ_FEWER_THAN_50_DEFECT_LIST_COPIES                  0x0E
#define SCSI_ASCQ_PARAMETER_LIST_LENGTH_ERROR                       0x00
#define SCSI_ASCQ_SYNCHRONOUS_DATA_TRANSFER_ERROR                   0x00
#define SCSI_ASCQ_DEFECT_LIST_NOT_FOUND                             0x00
#define SCSI_ASCQ_PRIMARY_DEFECT_LIST_NOT_FOUND                     0x01
#define SCSI_ASCQ_GROWN_DEFECT_LIST_NOT_FOUND                       0x02
#define SCSI_ASCQ_SEAGATE_UNIQUE_DIAGNOSTIC_CODE                    0x83
#define SCSI_ASCQ_MISCOMPARE_DURING_VERIFY_OPERATION                0x00
#define SCSI_ASCQ_NODOTASTTRDCCH                                    0x00
#define SCSI_ASCQ_INVALID_COMMAND_OPERATION_CODE                    0x00
#define SCSI_ASCQ_INVALID_LINKED_COMMAND_OPERATION_CODE             0xF3
#define SCSI_ASCQ_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE                0x00
#define SCSI_ASCQ_INVALID_FIELD_IN_CDB                              0x00
#define SCSI_ASCQ_ILLEGAL_QUEUE_TYPE_FOR_CDB                        0x01
#define SCSI_ASCQ_INVALID_LBA_IN_LINKED_COMMAND                     0xF0
#define SCSI_ASCQ_INVALID_LINKED_COMMAND_OPERATION_CODE2            0xF2
#define SCSI_ASCQ_ILLEGAL_G_TO_P_OPERATION_REQUEST                  0xF3
#define SCSI_ASCQ_LOGICAL_UNIT_NOT_SUPPORTED                        0x25
#define SCSI_ASCQ_INVALID_FIELD_IN_PARAMETER_LIST                   0x00
#define SCSI_ASCQ_PARAMETER_NOT_SUPPORTED                           0x01
#define SCSI_ASCQ_PARAMETER_VALUE_INVALID                           0x02
#define SCSI_ASCQ_INVALID_FIELD_THRESHOLD_PARAMETER                 0x03
#define SCSI_ASCQ_INVALID_RELEASE_ACTIVE_PERSISTENT_RESERVE         0x04
#define SCSI_ASCQ_FAILED_TO_READ_VALID_LOG_DUMP_DATA                0x05
#define SCSI_ASCQ_TMS_FIRMWARE_TAG_PARAMETER_INVALID                0x97
#define SCSI_ASCQ_CHECK_SUM_PARAMETER_INVALID                       0x98
#define SCSI_ASCQ_FIRMWARE_TAG_PARAMETER_INVALID                    0x99
#define SCSI_ASCQ_WRITE_PROTECTED                                   0x27
#define SCSI_ASCQ_FLASHING_LED_OCCOURED                             0x00
#define SCSI_ASCQ_POWER_ON_RESET_OR_BUS_RESET_OCCOURED              0x00
#define SCSI_ASCQ_POWER_ON_RESET_OCCOURED                           0x01
#define SCSI_ASCQ_SCSI_BUS_RESET_OCCOURED                           0x02
#define SCSI_ASCQ_BUS_DEVICE_RESET_FUNCTION_OCCOURED                0x03
#define SCSI_ASCQ_INTERNAL_RESET_OCCOURED                           0x04
#define SCSI_ASCQ_TRANSCEIVER_MODE_CHANGED_TO_SINGLE_ENDED          0x05
#define SCSI_ASCQ_TRANSCEIVER_MODE_CHANGED_TO_LVD                   0x06
#define SCSI_ASCQ_WRITE_LOG_DUMP_DATA_TO_DISK_SUCCESS_NEXLOS        0x07
#define SCSI_ASCQ_WRITE_LOG_DUMP_DATA_TO_DISK_FAILED                0x08
#define SCSI_ASCQ_WRITE_LOG_DUMP_ENTRY_INFORMATION_FAILED           0x09
#define SCSI_ASCQ_RESERVED_DISK_SPACE                               0x0A
#define SCSI_ASCQ_SDBP_SELF_TEST_CONTIAINED_ERROR                   0x0B
#define SCSI_ASCQ_SDBP_INCOMING_BUFFER_OVERFLOW                     0x0C
#define SCSI_ASCQ_COLD_RESET_FLASHING_LED                           0xCD
#define SCSI_ASCQ_WARM_RESET_FLASHING_LED                           0xCE
#define SCSI_ASCQ_MODE_PARAMETERS_CHANGED                           0x01
#define SCSI_ASCQ_LOG_PARAMETERS_CHANGED                            0x02
#define SCSI_ASCQ_RESERVATION_PREEMTED                              0x03
#define SCSI_ASCQ_RESERVATION_RELEASED                              0x04
#define SCSI_ASCQ_REGISTRATION_PREEMTED                             0x05
#define SCSI_ASCQ_COMMAND_SEQUNCE_ERROR                             0x00
#define SCSI_ASCQ_TAGGED_COMMANDS_CLEARED_BY_ANOTHER_INIT           0x00
#define SCSI_ASCQ_MEDIUM_FORMAT_CORRUPTED                           0x00
#define SCSI_ASCQ_CORRUPTION_IN_RW_FORMAT_REGISTER                  0x01
#define SCSI_ASCQ_CORRUPTED_WWN_IN_DRIVE_INFORMATION_FILE           0x91
#define SCSI_ASCQ_NO_DEFECT_SPARE_LOCATION_AVAILABLE                0x00
#define SCSI_ASCQ_DEFECT_LIST_UPDATE_ERROR                          0x01
#define SCSI_ASCQ_NO_SPARES_AVAILABLE                               0x02
#define SCSI_ASCQ_DEFECT_LIST_LARGER_THAT_ALLOCATION                0x03
#define SCSI_ASCQ_FLASH_NOT_READY_FOR_ACCESS                        0x00
#define SCSI_ASCQ_UNSPECIFIED_ENCLOSURE_SERVICED_FAILURE            0x00
#define SCSI_ASCQ_UNSUPPORTED_ENCLOSURE_FUNCTION                    0x01
#define SCSI_ASCQ_ENCLOSURE_SERVICE_UNAVAILABLE                     0x02
#define SCSI_ASCQ_ENCLOSURE_TRANSFER_FAILURE                        0x03
#define SCSI_ASCQ_ENCLOSURE_TRANSFER_REFUSED                        0x04
#define SCSI_ASCQ_PARAMETER_ROUNDED                                 0x00
#define SCSI_ASCQ_INVALID_BITS_IN_IDENTIFY_MESSAGE                  0x00
#define SCSI_ASCQ_LOGICAL_UNIT_FAILED_SELF_TEST                     0x03
#define SCSI_ASCQ_LOGICAL_UNIT_HAS_NOT_SELF_CONFIGURED_YET          0x00
#define SCSI_ASCQ_TARGET_OPERATING_CONDITIONS_CHANGED               0x00
#define SCSI_ASCQ_DEVICE_INTERNAL_RESET_OCCOURED                    0x01
#define SCSI_ASCQ_CHANGED_OPERATIONG_DEFINITION                     0x02
#define SCSI_ASCQ_DEVICE_IDENTIFIER_CHANGED                         0x05
#define SCSI_ASCQ_ECHO_BUFFER_OVERWRITTEN                           0x0F
#define SCSI_ASCQ_BUFFER_CONTENTS_HAVE_CHANGED                      0x80
#define SCSI_ASCQ_INVALID_APM_PARAMETERS                            0x90
#define SCSI_ASCQ_WWN_MISMATCH                                      0x91
#define SCSI_ASCQ_DRAM_PARITY_ERROR                                 0x01
#define SCSI_ASCQ_SPINUP_ERROR_RECOVERED_WITH_RETRIES               0x02
#define SCSI_ASCQ_POWER_ON_OR_SELF_TEST_FAILURE                     0x00
#define SCSI_ASCQ_PORT_A_FAILED_LOOPBACK_TEST                       0x0A
#define SCSI_ASCQ_PORT_B_FAILED_LOOPBACK_TEST                       0x0B
#define SCSI_ASCQ_MESSAGE_REJECT_ERROR                              0x00
#define SCSI_ASCQ_INTERNAL_TARGET_FAILURE                           0x00
#define SCSI_ASCQ_DATA_INTEGRITY_CHECK_FAILED_ON_VERIFY             0xF2
#define SCSI_ASCQ_DATA_INTEGRITY_CHECK_FAILED_ON_WRITE              0xF6
#define SCSI_ASCQ_XOR_CDB_CHECK_ERROR                               0xFF
#define SCSI_ASCQ_SELECT_RESELECT_FAILURE                           0x00
#define SCSI_ASCQ_SCSI_PARITY_ERROR                                 0x00
#define SCSI_ASCQ_INFORMATION_UNIT_CRC_ERROR                        0x03
#define SCSI_ASCQ_FIBRE_CHANNEL_SEQUENCE_ERROR                      0x80
#define SCSI_ASCQ_INITIATOR_DETECTED_ERROR_MESSAGE_RECIVED          0x00
#define SCSI_ASCQ_INVALID_MESSAGE_RECEIVED                          0x00
#define SCSI_ASCQ_DATA_PHASE_ERROR                                  0x00
#define SCSI_ASCQ_INVALID_TRANSFER_TAG                              0x01
#define SCSI_ASCQ_TOO_MANY_WRITE_DATA                               0x02
#define SCSI_ASCQ_ACK_NAK_TIMEOUT                                   0x03
#define SCSI_ASCQ_NAK_RECIVED                                       0x04
#define SCSI_ASCQ_DATA_OFFSET_ERROR                                 0x05
#define SCSI_ASCQ_INITIATOR_RESPONCE_TIMEOUT                        0x06
#define SCSI_ASCQ_LOGICAL_UNIT_FAILED_SELF_CONFIGURATION            0x00
#define SCSI_ASCQ_OVERLAPPED_COMMANDS_ATTEMPTED                     0x00
#define SCSI_ASCQ_XOR_CACHE_IS_NOT_AVAILABLE                        0x01
#define SCSI_ASCQ_PRKT_TABLE_IS_FULL                                0x04
#define SCSI_ASCQ_LOG_EXCEPTION                                     0x00
#define SCSI_ASCQ_THRESHOLD_CONDITION_MET                           0x01
#define SCSI_ASCQ_LOG_COUNTER_AT_MAXIMUM                            0x02
#define SCSI_ASCQ_LOG_LIST_CODES_EXHAUSTED                          0x03
#define SCSI_ASCQ_RPL_STATUS_CHANGE                                 0x00
#define SCSI_ASCQ_SPINDLES_SYNCHRONIZED                             0x01
#define SCSI_ASCQ_SPINDLES_NOT_SYNCHRONIZED                         0x02
#define SCSI_ASCQ_FAILURE_PREDICTION_THRESHOLD_EXCEEDED             0x00
#define SCSI_ASCQ_FALSE_FAILURE_PREDICTION_THRESHOLD_EXCEEDED       0xFF
#define SCSI_ASCQ_VOLTAGE_FAILURE                                   0x00
#define SCSI_ASCQ_GENERAL_FIRMWARE_ERROR_QUALIFIER                  0x00
#define SCSI_ASCQ_IOEDC_ERROR_ON_READ                               0x86
#define SCSI_ASCQ_IOEDC_ERROR_ON_WRITE                              0x87
#define SCSI_ASCQ_HOST_PARITY_CHECK_FAILED                          0x88
#define SCSI_ASCQ_IOEDC_ERROR_ON_READ_DETECTED_BY_FORMATTER         0x89
#define SCSI_ASCQ_HOST_FIFO_PARRITY_ERROR_COMMON_BUFFER             0x8A
#define SCSI_ASCQ_HOST_FIFO_PARRITY_ERROR_FRAME_BUFFER_LOGIC        0x8B
#define SCSI_ASCQ_HOST_DATA_FRAME_BUFFER_PARITY_ERROR               0x8C
#define SCSI_ASCQ_REASSIGN_POWER_FAIL_RECOVERY_FAILED               0x00
#define SCSI_ASCQ_LA_CHECK_ERROR_LCM_BIT_0                          0x00
#define SCSI_ASCQ_LA_CHECK_ERROR                                    0x00
#define SCSI_ASCQ_NREPORTED_DEFFERRED_ERRORS_HAVE_BEEN_LOGGED       0x00



//0x09 0x00



//Page 59

#define SCSI_LONG_LBA_COMMAND_SIZE 0x18

//scsi commands
#define SCSI_COMMAND_BACKGROUND_CONTROL         0x9E
#define SCSI_COMMAND_CHANGE_DEFINITION          0x40
#define SCSI_COMMAND_FORMAT_UNIT                0x04
#define SCSI_COMMAND_GET_LBA_STATUS             0x9E     
#define SCSI_COMMAND_GET_STREAM_STATUS          0x9E
#define SCSI_COMMAND_INQUIRY                    0x12
#define SCSI_COMMAND_LOG_SELECT                 0x4C
#define SCSI_COMMAND_LOG_SENCE                  0x4D
#define SCSI_COMMAND_MODE_SELECT_CDB6           0x15
#define SCSI_COMMAND_MODE_SELECT_CDB10          0x55
#define SCSI_COMMAND_MODE_SENCE_CDB6            0x1A
#define SCSI_COMMAND_MODE_SENCE_CDB10           0x5A
#define SCSI_COMMAND_PERSISTENT_RESERVE_IN      0x5E
#define SCSI_COMMAND_PERSISTENT_RESERVE_OUT     0x5F
#define SCSI_COMMAND_READ_CDB6                  0x08
#define SCSI_COMMAND_READ_CDB10                 0x28
#define SCSI_COMMAND_READ_CDB12                 0xA8
#define SCSI_COMMAND_READ_CDB16                 0x88
#define SCSI_COMMAND_READ_CDB32                 0x7F //0x0009
#define SCSI_COMMAND_READ_BUFFER_CDB10          0x3C
#define SCSI_COMMAND_READ_BUFFER_CDB16          0x9B
#define SCSI_COMMAND_READ_CAPACITY_CDB10        0x25
#define SCSI_COMMAND_READ_CAPACITY_CDB16        0x9E
#define SCSI_COMMAND_READ_DEFECT_DATA_CDB10     0x37
#define SCSI_COMMAND_READ_DEFECT_DATA_CDB12     0xB7
#define SCSI_COMMAND_READ_LONG_CDB10            0x3E
#define SCSI_COMMAND_READ_LONG_CDB16            0x9E
#define SCSI_COMMAND_REASIGN_BLOCKS             0x07
#define SCSI_COMMAND_RECIEVE_DIAGNOSTIC_RESULTS 0x1C
#define SCSI_COMMAND_RELEASE_CDB6               0x17
#define SCSI_COMMAND_RELEASE_CDB10              0x57
#define SCSI_COMMAND_REPORT_IDENTIFYING_INFO    0xA3
#define SCSI_COMMAND_REPORT_LUNS                0xA0
#define SCSI_COMMAND_REPORT_SUPPORTED_OPCODES   0xA3   
#define SCSI_COMMAND_REPORT_SUPPORTED_TASKMNG   0xA3      
#define SCSI_COMMAND_REPORT_TIMESTAMP           0xA3
#define SCSI_COMMAND_REQUEST_SENSE              0x03
#define SCSI_COMMAND_RESERVE_CDB6               0x16
#define SCSI_COMMAND_RESERVE_CDB10              0x56
#define SCSI_COMMAND_REZERO_UNIT                0x01
#define SCSI_COMMAND_SANITIZE                   0x48
#define SCSI_COMMAND_SECURITY_PROTOCOL_IN       0xA2
#define SCSI_COMMAND_SECURITY_PROTOCOL_OUT      0xB5
#define SCSI_COMMAND_SEEK_CDB6                  0x0B
#define SCSI_COMMAND_SEEK_EXTENDED_CDB10        0x2B
#define SCSI_COMMAND_SEND_DIAGNOSTIC            0x1D
#define SCSI_COMMAND_SET_IDENTIFYING_INFO       0xA4
#define SCSI_COMMAND_SET_TIMESTAMP              0xA4
#define SCSI_COMMAND_START_STOP_UNIT            0x1B
#define SCSI_COMMAND_STREAM_CONTROL             0x9E
#define SCSI_COMMAND_SYNCHRONIZE_CACHE_CDB10    0x35
#define SCSI_COMMAND_SYNCHRONIZE_CACHE_CDB16    0x91
#define SCSI_COMMAND_TEST_UNIT_READY            0x00
#define SCSI_COMMAND_UNMAP                      0x42
#define SCSI_COMMAND_VERIFY_CDB10               0x2F
#define SCSI_COMMAND_VERIFY_CDB12               0xAF
#define SCSI_COMMAND_VERIFY_CDB16               0x8F
#define SCSI_COMMAND_VERIFY_CDB32               0x7F
#define SCSI_COMMAND_WRITE_CDB6                 0x0A
#define SCSI_COMMAND_WRITE_CDB10                0x2A
#define SCSI_COMMAND_WRITE_CDB12                0xAA
#define SCSI_COMMAND_WRITE_CDB16                0x8A
#define SCSI_COMMAND_WRITE_CDB32                0x7F               
#define SCSI_COMMAND_WRITE_AND_VERIFY_CDB10     0x2E
#define SCSI_COMMAND_WRITE_AND_VERIFY_CDB12     0xAE
#define SCSI_COMMAND_WRITE_AND_VERIFY_CDB16     0x8E
#define SCSI_COMMAND_WRITE_AND_VERIFY_CDB32     0x7F
#define SCSI_COMMAND_WRITE_ATOMIC_CDB16         0x9C
#define SCSI_COMMAND_WRITE_ATOMIC_CDB32         0x7F
#define SCSI_COMMAND_WRITE_BUFFER               0x3B
#define SCSI_COMMAND_WRITE_LONG                 0x3F
#define SCSI_COMMAND_WRITE_LONG_CDB16           0x9F
#define SCSI_COMMAND_WRITE_SAME_CDB10           0x41
#define SCSI_COMMAND_WRITE_SAME_CDB16           0x93
#define SCSI_COMMAND_WRITE_SAME_CDB32           0x7F
#define SCSI_COMMAND_WRITE_STREAM_CDB16         0x9A
#define SCSI_COMMAND_WRITE_STREAM_CDB32         0x7F

#define SCSI_SERVICE_ACTION_BACKGROUND_CONTROL          0x0015
#define SCSI_SERVICE_ACTION_GET_LBA_STATUS              0x0012
#define SCSI_SERVICE_ACTION_GET_STREAM_STATUS           0x0016
#define SCSI_SERVICE_ACTION_READ_CDB32                  0x0009
#define SCSI_SERVICE_ACTION_READ_CAPACITY_CDB16         0x0010
#define SCSI_SERVICE_ACTION_READ_LONG16                 0x0011
#define SCSI_SERVICE_ACTION_IDENTIFYING_INFORMATION     0x0005
#define SCSI_SERVICE_ACTION_REPORT_SUPPORTED_OPCODES    0x000C
#define SCSI_SERVICE_ACTION_REPORT_SUPPORTED_TASKMNG    0x000D
#define SCSI_SERVICE_ACTION_REPORT_TIMESTAMP            0x000F
#define SCSI_SERVICE_ACTION_SET_IDENTIFYING_INFORMATION 0x0006
#define SCSI_SERVICE_ACTION_SET_TIMESTAMP               0x000F
#define SCSI_SERVICE_ACTION_STREAM_CONTROL              0x0014
#define SCSI_SERVICE_ACTION_VERIFY_CDB32                0x000A
#define SCSI_SERVICE_ACTION_WRITE_CDB32                 0x000B
#define SCSI_SERVICE_ACTION_WRITE_AND_VERIFY_CDB32      0x000C
#define SCSI_SERVICE_ACTION_WRITE_ATOMIC_CDB32          0x0018
#define SCSI_SERVICE_ACTION_WRITE_LONG_CDB15            0x0011
#define SCSI_SERVICE_ACTION_WRITE_SAME_CDB32            0x000D

#define SCSI_BO_CONTROL_NO_CHANGE   0
#define SCSI_BO_CONTROL_START_OP    1
#define SCSI_BO_CONTROL_STOP_OP     2

#define SCSI_BO_TIME_NO_LIMIT       0

#define SCSI_CHGDEF_SAVE            1

#define SCSI_CHGDEF_DEFPARAM_CURRENT_OPDEF              0x00
#define SCSI_CHGDEF_DEFPARAM_SCSI2_OPDEF                0x03
#define SCSI_CHGDEF_DEFPARAM_SCSI3_OPDEF                0x04
#define SCSI_CHGDEF_DEFPARAM_MANUFACTURE_OPDEF          0x3F

struct _SCSI_HOST_DEVICE_DRIVER_OBJECT;
struct _SCSI_HOST_DEVICE_OBJECT;


#define SCSI_BACKGROUND_CONTROL_FEATURE     (1ULL << 0)
#define SCSI_CHANGE_DEFINITION_FEATURE      (1ULL << 1)
#define SCSI_CHANGE_FORMAT_UNIT_FEATURE     (1ULL << 2)
#define SCSI_CHANGE_GET_LBA_STATUS_FEATURE  (1ULL << 3)


typedef struct _SCSI_DEVICE_OBJECT{
    struct _SCSI_HOST_DEVICE_OBJECT*    Shdd;
    UINT64                              ScsiFeatures;
}SCSI_DEVICE_OBJECT, * PSCSI_DEVICE_OBJECT;

typedef enum{
    SCSI_COMMAND_BACKGROUND_CONTROL_ID = 0,
    SCSI_COMMAND_CHANGE_DEFINITION_ID,
    SCSI_COMMAND_FORMAT_UNIT_ID,
    SCSI_COMMAND_GET_LBA_STATUS_ID,
}SCSI_COMMAND_PACKET_ID;

typedef struct _SCSI_FORMAT_UNIT_COMMAND_PACKET{
    SCSI_FORMAT_UNIT_COMMAND_STRUCTURE  Cdb;
    PVOID                               ListData;
    SIZE                                ListSize;
}SCSI_FORMAT_UNIT_COMMAND_PACKET, * PSCSI_FORMAT_UNIT_COMMAND_PACKET;

typedef struct _SCSI_GET_LBA_STATUS_COMMAND_PACKET{
    SCSI_GET_LBA_STATUS_COMMAND_STRUCTURE       Cdb;
    PVOID                                       StatusData;
    SIZE                                        StatusSize;
}SCSI_GET_LBA_STATUS_COMMAND_PACKET, * PSCSI_GET_LBA_STATUS_COMMAND_PACKET;

typedef struct _SCSI_COMMAND_PACKET{
    SCSI_COMMAND_PACKET_ID                          CommandID;
    struct _SCSI_HOST_DEVICE_OBJECT*                Shdd;
    PSCSI_DEVICE_OBJECT                             ScsiDeviceObject;
    PVOID                                           SenceResult;
    union {
        SCSI_BACKGROUND_CONTROL_COMMAND_STRUCTURE   BackgroundControl;
        SCSI_CHANGE_DEFINITION_COMMAND_STRUCTURE    ChangeDefinition;
        SCSI_FORMAT_UNIT_COMMAND_PACKET             FormatUnit;
        SCSI_GET_LBA_STATUS_COMMAND_PACKET          GetLbaStatus;
    }Command;
}SCSI_COMMAND_PACKET, * PSCSI_COMMAND_PACKET;

typedef struct _SCSI_HOST_DEVICE_OBJECT{
    struct _SCSI_HOST_DEVICE_DRIVER_OBJECT*     DriverObject;

}SCSI_HOST_DEVICE_OBJECT, * PSCSI_HOST_DEVICE_OBJECT;

typedef struct _SCSI_HOST_DEVICE_CALLBACKS{
    LOUSTATUS   (*ScsiDeviceSendScsiCommand)(PSCSI_COMMAND_PACKET ScsiCommandPacket);
    LOUSTATUS   (*ScsiDevicePrepScsiCommand)(PSCSI_DEVICE_OBJECT ScsiDevice, PSCSI_COMMAND_PACKET ScsiCommandPacket);
}SCSI_HOST_DEVICE_CALLBACKS, * PSCSI_HOST_DEVICE_CALLBACKS;

typedef struct _SCSI_HOST_DEVICE_DRIVER_OBJECT{
    LOUSTR                          DriverName;
    PSCSI_HOST_DEVICE_CALLBACKS     Callbacks;
}SCSI_HOST_DEVICE_DRIVER_OBJECT, * PSCSI_HOST_DEVICE_DRIVER_OBJECT;

#endif
