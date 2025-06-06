//SPDX-Licence-IdentifierL AGPL 3.0/Proprietary
//Copyright (C) 2024-2025 Tyler Grenier
//Time Started  : 12/31/2024 11:43 AM
//Time Finished : 12/31/2024  9:22 PM
//Last Modified : 12/31/2024  9:22 PM

#ifndef _MPI_SAS_LOG_H
#define _MPI_SAS_LOG_H
#pragma pack(push,1)

#define SERIAL_ATTACHED_LOG_INFO_NEXUS_LOSS         0x31170000
#define SERIAL_ATTACHED_LOG_INFO_BITS               0xFFFF0000

#define IOC_LOG_INFO_ORIGINATOR_IOP                 0x00000000
#define IOC_LOG_INFO_ORIGINATOR_PL                  0x01000000
#define IOC_LOG_INFO_ORIGINATOR_IR                  0x02000000

#define IOC_LOG_INFO_ORIGINATOR_BITS                0x0F000000

#define IOC_LOG_INFO_CODE_BITS                      0x00FF0000
#define IOC_LOG_INFO_CODE_SHIFT                     16

#define IOP_LOG_INFO_CODE_INVALID_SERIAL_ATTACH_ADDRESS                 0x00010000
#define IOP_LOG_INFO_CODE_UNUSED2                                       0x00020000
#define IOP_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE                    0x00030000
#define IOP_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_RT                 0x00030100
#define IOP_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_PN                 0x00030200
#define IOP_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_FORM               0x00030300
#define IOP_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_PT                 0x00030400
#define IOP_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_DNM                0x00030500
#define IOP_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_PERSIST            0x00030600
#define IOP_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_DEFAULT            0x00030700

#define IOP_LOG_INFO_CODE_FIRMWARE_UPLOAD_NO_FLASH_AVAILABLE            0x0003E000
#define IOP_LOG_INFO_CODE_FIRMWARE_UPLOAD_UNKOWN_IMAGE_TYPE             0x0003E001
#define IOP_LOG_INFO_CODE_FIRMWARE_UPLOAD_WRONG_IMAGE_SIZE              0x0003E002
#define IOP_LOG_INFO_CODE_FIRMWARE_UPLOAD_ENTIRE_FLASH_UPLOAD_FAILED    0x0003E003
#define IOP_LOG_INFO_CODE_FIRMWARE_UPLOAD_REGION_UPLOAD_FAILED          0x0003E004
#define IOP_LOG_INFO_CODE_FIRMWARE_UPLOAD_DMA_FAILED                    0x0003E005

#define IOP_LOG_INFO_CODE_DIAGNOSTIC_MESSAGE_ERROR                      0x00040000

#define IOP_LOG_INFO_CODE_TASK_TERMINATED                               0x00050000

#define IOP_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_READ_ACTION_ERROR        0x00060001
#define IOP_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_INVALID_BUS_ID_ERROR     0x00060002

#define IOP_LOG_INFO_CODE_TARGET_ASSIST_TERMINATED                      0x00070001
#define IOP_LOG_INFO_CODE_TARGET_STATUS_SEND_TERMINATED                 0x00070002
#define IOP_LOG_INFO_CODE_TARGET_MODE_ABORT_ALL_IO                      0x00070003
#define IOP_LOG_INFO_CODE_TARGET_MODE_ABORT_EXACT_IO                    0x00070004
#define IOP_LOG_INFO_CODE_TARGET_MODE_ABORT_EXACT_IO_REQUEST            0x00070005

#define IOP_LOG_INFO_CODE_LOG_TIME_STAMP_EVENT                          0x00080000

#define PM_LOG_INFO_SUB_CODE_OPEN_FAILURE                               0x00010000

#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_NO_DESTINATION_TIME_OUT        0x00000001
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_PATHWAY_BLOCKED                0x00000002
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RES_CONTINUE0                  0x00000003
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RES_CONTINUE1                  0x00000004
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RES_INITIALIZE0                0x00000005
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RES_INITIALIZE1                0x00000006
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RES_STOP0                      0x00000007
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RES_STOP1                      0x00000008
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RETRY                          0x00000009
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_BREAK                          0x0000000A
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_UNUSED1                        0x0000000B
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_OPEN_TIMEOUT_EXP               0x0000000C
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_UNUSED2                        0x0000000D
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_DEVICE_TABLE_ACCESS_FAILED     0x0000000E
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_BAD_DESTINATION                0x00000011
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RATE_NOT_SUPPORTED             0x00000012
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_PROTOCOL_NOT_SUPPORTED         0x00000013
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RESERVED_ABANDON0              0x00000014
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RESERVED_ABANDON1              0x00000015
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RESERVED_ABANDON2              0x00000016
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_RESERVED_ABANDON3              0x00000017
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_STP_RESOURCE_BUSY              0x00000018
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_WRONG_DESTINATION              0x00000019

#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_PATH_BLOCKED                   0x0000001B
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILED_AWT_MAXED                      0x0000001C


#define PL_LOG_INFO_CODE_INVALID_SCATTER_GATHER_LIST                0x00020000
#define PL_LOG_INFO_CODE_WRONG_REL_OFF_OR_FRAME_LENGTH              0x00030000
#define PL_LOG_INFO_CODE_FRAME_XFER_ERROR                           0x00040000
#define PL_LOG_INFO_CODE_TX_FM_CONNECTED_LOW                        0x00050000
#define PL_LOG_INFO_CODE_SATA_NON_NCQ_RW_ERROR_BIT_SET              0x00060000
#define PL_LOG_INFO_CODE_SATA_READ_LOG_RECIEVE_DATA_ERROR           0x00070000
#define PL_LOG_INFO_CODE_SATA_NCQ_FAIL_ALL_COMMANDS_AFTER_ERROR     0x00080000
#define PL_LOG_INFO_CODE_SATA_ERRORRCV_SET_DEVICE_BIT_FIS       0x00090000
#define PL_LOG_INFO_CODE_RX_FORM_INVALID_MESSAGE                    0x000A0000
#define PL_LOG_INFO_CODE_RX_CONTEXT_MESSAGE_VALID_ERROR             0x000B0000
#define PL_LOG_INFO_CODE_RX_FORM_CURRENT_FRAME_ERROR                0x000C0000
#define PL_LOG_INFO_CODE_SATA_LINK_DOWN                             0x000D0000
#define PL_LOG_INFO_CODE_DISCOVERY_SATA_INIT_W_IOS                  0x000E0000
#define PL_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE                 0x000F0000
#define PL_LOG_INFO_CODE_CONFIGURATION_PL_NOT_INITIALIZED           0x000F0001
#define PL_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_PT              0x000F0100
#define PL_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_NUM_PHYS        0x000F0200
#define PL_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_NOT_IMP         0x000F0300
#define PL_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_NO_DEVICE       0x000F0400
#define PL_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_FORM            0x000F0500
#define PL_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_PHY             0x000F0600
#define PL_LOG_INFO_CODE_CONFIGURATION_INVALID_PAGE_NO_OWNER        0x000F0700
#define PL_LOG_INFO_CODE_DISCOVERY_SATA_INIT_TIMEOUT                0x00100000
#define PL_LOG_INFO_CODE_RESET                                      0x00110000
#define PL_LOG_INFO_CODE_ABORT                                      0x00120000
#define PL_LOG_INFO_CODE_IO_NOT_YET_EXECUTED                        0x00130000
#define PL_LOG_INFO_CODE_IO_EXECUTED                                0x00140000
#define PL_LOG_INFO_CODE_PERS_RESERVENOT_AFFILIATED_OWNER      0x00150000
#define PL_LOG_INFO_CODE_OPEN_TX_DMA_ABORT                          0x00160000
#define PL_LOG_INFO_CODE_IO_DEVICE_MISSING_DELAY_RETY               0x00170000
#define PL_LOG_INFO_CODE_IO_CANCELLED_DUE_TO_READ_ERROR             0x00180000
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE                           0x00000100
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_SATA_NEGOTIATED_RATE_2HI  0x00000102
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_RATE_NOT_SUPPORTED        0x00000103
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_BREAK                     0x00000104
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_ZONE_VIOLATION            0x00000114
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_ABANDON0                  0x00000114
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_ABANDON1                  0x00000115
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_ABANDON2                  0x00000116
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_ABANDON3                  0x00000117
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_ORR_TIMEOUT               0x0000011A
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_PATH_BLOCKED              0x0000011B
#define PL_LOG_INFO_SUB_CODE_OPEN_FAILURE_AWT_MAXED                 0x0000011C

#define PL_LOG_INFO_SUB_CODE_TARGET_BUS_RESET                       0x00000120
#define PL_LOG_INFO_SUB_CODE_TRANSPORT_LAYER                        0x00000130
#define PL_LOG_INFO_SUB_CODE_PORT_LAYER                             0x00000140

#define PL_LOG_INFO_SUB_CODE_INVALID_SCATTER_GATHER_LIST            0x00000200
#define PL_LOG_INFO_SUB_CODE_WRONG_REL_OFF_OR_FRAME_LENGTH          0x00000300
#define PL_LOG_INFO_SUB_CODE_FRAME_XFER_ERROR                       0x00000400

#define PL_LOG_INFO_SUB_CODE_TX_FORM_CONNECTED_LOW                  0x00000500
#define PL_LOG_INFO_SUB_CODE_SATA_NON_NCQ_RW_ERROR_BIT_SET          0x00000600
#define PL_LOG_INFO_SUB_CODE_SATA_READ_LOG_RECIEVE_DATA_ERROR       0x00000700
#define PL_LOG_INFO_SUB_CODE_SATA_NCQ_FAIL_ALL_COMMANDS_AFTER_ERROR 0x00000800
#define PL_LOG_INFO_SUB_CODE_SATA_ERRORRCV_SET_DEVICE_BIT_FIS   0x00000900
#define PL_LOG_INFO_SUB_CODE_RX_FORM_INVALID_MESSAGE                0x00000A00
#define PL_LOG_INFO_SUB_CODE_RX_CONTEXT_MESSAGE_VALID_ERROR         0x00000B00
#define PL_LOG_INFO_SUB_CODE_RX_FORM_CURRENT_FRAME_ERROR            0x00000C00
#define PL_LOG_INFO_SUB_CODE_SATA_LINK_DOWN                         0x00000D00
#define PL_LOG_INFO_SUB_CODE_DISCOVERY_SATA_INITIALIZE_W_IOS        0x00000E00
#define PL_LOG_INFO_SUB_CODE_DISCOVERY_REMOTE_SEP_RESET             0x00000E01
#define PL_LOG_INFO_SUB_CODE_SECOND_OPEN                            0x00000F00
#define PL_LOG_INFO_SUB_CODE_DISCOVERY_SATA_INIT_TIMEOUT            0x00001000
#define PL_LOG_INFO_SUB_CODE_BREAK_ON_SATA_CONECTION                0x00002000

#define PL_LOG_INFO_SUB_CODE_BREAK_ON_STUCK_LINK                    0x00003000
#define PL_LOG_INFO_SUB_CODE_BREAK_ON_STUCK_LINK_AIP                0x00004000
#define PL_LOG_INFO_SUB_CODE_BREAK_ON_INCOMPLETE_BREAK_RCVD         0x00005000

#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_SMP_FRAME_FAILURE                 0x00200000
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_SMP_READ_ERROR                    0x00200010
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_SMP_WRITE_ERROR                   0x00200020
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_NOT_SUPPORTED_ON_ENCLOSURE        0x00200040
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_ADDRESS_MODE_NOT_SUPPORTED        0x00200050
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_BAD_SLOT_NUMBER                   0x00200060
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_SGPIO_NOT_PRESENT                 0x00200070
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_GPIO_NOT_CONFIGURED               0x00200080
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_GPIO_FRAME_ERROR                  0x00200090
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_GPIO_CONFIGURATION_PAGE_ERROR     0x002000A0
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_SES_FRAMER_ALLOCATION_ERROR       0x002000B0
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_SES_IO_ERROR                      0x002000C0
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_SES_RETRIES_EXHAUSTED             0x002000D0
#define PL_LOG_INFO_CODE_ENCLOSURE_MANAGEMENT_SMP_FRAME_ALLOCATION_ERROR        0x002000E0

#define PL_LOG_INFO_DA_SEP_NOT_PRESENT                                      0x00200100
#define PL_LOG_INFO_DA_SEP_SINGLE_THREAD_ERROR                              0x00200101
#define PL_LOG_INFO_DA_SEP_ISTWI_INTRIDLE_STATE                         0x00200102
#define PM_LOG_INFO_DA_SEP_RECIEVED_NACK_FROM_SLAVE                         0x00200103
#define PM_LOG_INFO_DA_SEP_DID_NOT_RECIEVE_ACKNOWLEDGE                      0x00200104
#define PM_LOG_INFO_DA_SEP_BAD_STATUS_HDR_CHECKSUM                          0x00200105
#define PL_LOG_INFO_DA_SEP_STOP_ON_DATA                                     0x00200106
#define PL_LOG_INFO_DA_SEP_STOP_ON_SENCE_DATA                               0x00200107
#define PM_LOG_INFO_DA_SEP_UNSUPPORTED_SCSI_STATUS1                         0x00200108
#define PM_LOG_INFO_DA_SEP_UNSUPPORTED_SCSI_STATUS2                         0x00200109
#define PM_LOG_INFO_DA_SEP_CHECKSUM_ERROR_AFTER_STOP                        0x0020010A
#define PM_LOG_INFO_DA_SEP_CHECKSUM_ERROR_AFTER_STOP_GETDATA                0x0020010B
#define PM_LOG_INFO_DA_SEP_UNSUPPORTED_COMMAND0                             0x0020010C
#define PM_LOG_INFO_DA_SEP_UNSUPPORTED_COMMAND1                             0x0020010D
#define PM_LOG_INFO_DA_SEP_UNSUPPORTED_COMMAND2                             0x0020010E

#define IR_LOG_INFO_VOLUME_CREATE_INVALID_LENGTH                            0x00010001
#define IR_LOG_INFO_VOLUME_CREATE_DUPLICATE                                 0x00010002
#define IR_LOG_INFO_VOLUME_CREATE_NO_SLOTS                                  0x00010003
#define IR_LOG_INFO_VOLUME_CREATE_DMA_ERROR                                 0x00010004
#define IR_LOG_INFO_VOLUME_CREATE_INVALID_VOLUME_TYPE                       0x00010005
#define IR_LOG_INFO_VOLUME_MFG_PAGE4_ERROR                                  0x00010006
#define IR_LOG_INFO_VOLUME_INTERNAL_CONFIGURATION_STRUCTURE_ERROR           0x00010007
#define IR_LOG_INFO_VOLUME_ACTIVATING_AN_ACTIVE_VOLUME                      0x00010010
#define IR_LOG_INFO_VOLUME_ACTIVATING_INVALID_VOLUME_TYPE                   0x00010011
#define IR_LOG_INFO_VOLUME_ACTIVATING_TOO_MANY_VOLUMES                      0x00010012
#define IR_LOG_INFO_VOLUME_ACTIVATING_VOLUME_IDUSE                      0x00010013
#define IR_LOG_INFO_VOLUME_ACTIVATING_VOLUME_FAILED                         0x00010014
#define IR_LOG_INFO_VOLUME_ACTIVATING_IMPORT_VOLUME_FAILED                  0x00010015
#define IR_LOG_INFO_VOLUME_ACTIVATING_TOO_MANY_PHY_DISKS                    0x00010016

#define IR_LOG_INFO_PHYS_DISK_CREATE_TOO_MANY_DISKS                         0x00010020
#define IR_LOG_INFO_PHYS_DISK_CREATE_INVALID_LENGTH                         0x00010021
#define IR_LOG_INFO_PHYS_DISK_CREATE_DMA_ERROR                              0x00010022
#define IR_LOG_INFO_PHYS_DISK_CREATE_BUS_TID_INVALID                        0x00010023
#define IR_LOG_INFO_PHYS_DISK_CREATE_CONFIGURATION_PAGE_ERROR               0x00010024

#define IR_LOG_INFO_COMPAT_ERROR_RAID_DISABLED                              0x00010030
#define IR_LOG_INFO_COMPAT_ERROR_INQUIRY_FAILED                             0x00010031
#define IR_LOG_INFO_COMPAT_ERROR_NOT_DIRECT_ACCESS                          0x00010032
#define IR_LOG_INFO_COMPAT_ERROR_REMOVABLE_FOUND                            0x00010033
#define IR_LOG_INFO_COMPAT_ERROR_NEED_SCSI2_OR_ABOVE                        0x00010034
#define IR_LOG_INFO_COMPAT_ERROR_SATA48_BIT_LBA_NOT_SUPPORTED               0x00010035
#define IR_LOG_INFO_COMPAT_ERROR_DEVICE_NOT_512_BYTE_BLOCKS                 0x00010036
#define IR_LOG_INFO_COMPAT_ERROR_VOLUME_TYPE_CHECK_FAILED                   0x00010037
#define IR_LOG_INFO_COMPAT_ERROR_UNSUPPORTED_VOLUME_TYPE                    0x00010038
#define IR_LOG_INFO_COMPAT_ERROR_DISK_TOO_SMALL                             0x00010039
#define IR_LOG_INFO_COMPAT_ERROR_PHYS_DISK_NOT_FOUND                        0x0001003A
#define IR_LOG_INFO_COMPAT_ERROR_MEMBERSHIP_COUNT                           0x0001003B
#define IR_LOG_INFO_COMPAT_ERROR_NOW_64K_STRIPE_SIZE                        0x0001003C
#define IR_LOG_INFO_COMPAT_ERROR_IME_VOLUME_NOT_CURRENTLY_SUPPORTED         0x0001003D

#define IR_LOG_INFO_DEVICE_FIRMWARE_UPDATE_ERR_DFUPROGRESS              0x00010050
#define IR_LOG_INFO_DEVICE_FIRMWARE_UPDATE_ERR_DEVICEINVALID_STATE      0x00010051
#define IR_LOG_INFO_DEVICE_FIRMWARE_UPDATE_ERR_INVALID_TIMEOUT              0x00010052
#define IR_LOG_INFO_DEVICE_FIRMWARE_UPDATE_ERR_NO_TIMERS                    0x00010053
#define IR_LOG_INFO_DEVICE_FIRMWARE_UPDATE_ERR_READING_CFG_PAGE             0x00010054
#define IR_LOG_INFO_DEVICE_FIRMWARE_UPDATE_ERR_PORT_IO_TIMEOUT_REQUIRED     0x00010055
#define IR_LOG_INFO_DEVICE_FIRMWARE_UPDATE_ERR_ALLOC_CFG_PAGE               0x00010056

#define IOC_LOG_INFO_PREFIX_IOP     ((MPI_IOC_LOG_INFO_TYPE_SAS << MPI_IOC_LOG_INFO_TYPE_SHIFT) | IOC_LOG_INFO_ORIGINATOR_IOP)
#define IOC_LOG_INFO_PREFIX_PL      ((MPI_IOC_LOG_INFO_TYPE_SAS << MPI_IOC_LOG_INFO_TYPE_SHIFT) | IOC_LOG_INFO_ORIGINATOR_PL)
#define IOC_LOG_INFO_PREFIX_IR      ((MPI_IOC_LOG_INFO_TYPE_SAS << MPI_IOC_LOG_INFO_TYPE_SHIFT) | IOC_LOG_INFO_ORIGINATOR_IR)

#pragma pack(pop)
#endif //_MPI_SAS_LOG_H