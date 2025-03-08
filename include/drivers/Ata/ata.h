#ifndef _ATA_DEVICE_LIBRARY_H
#define _ATA_DEVICE_LIBRARY_H
#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

#include "../CdRom.h"

#define ATA_DMA_BOUNDS                          0xFFFF
#define ATA_DMA_MASK                            0xFFFFFFFF

#define UNIVERSAL_ATA_MAX_DEVICES               2
#define UNIVERSAL_ATA_MAX_PRD                   256
#define UNIVERSAL_ATA_SECTOR_SIZE               512
#define UNIVERSAL_ATA_MAX_SECTORS_128           128                                  
#define UNIVERSAL_ATA_MAX_SECTORS               256
#define UNIVERSAL_ATA_MAX_SECTORS_1024          1025
#define UNIVERSAL_ATA_MAX_SECTORS_LBA_48        0xFFFF
#define UNIVERSAL_ATA_MAX_SECTORS_TAPE          0xFFFF
#define UNIVERSAL_ATA_MAX_TRIM_RCOUNT           64
#define UNIVERSAL_ATA_ID_WORDS                  256
#define UNIVERSAL_ATA_ID_CONFIGURATION          0
#define UNIVERSAL_ATA_ID_CYCLES                 1
#define UNIVERSAL_ATA_ID_HEADS                  3
#define UNIVERSAL_ATA_ID_SECTORS                6
#define UNIVERSAL_ATA_ID_SEVERITY_ERROR_NUMBER  10            
#define UNIVERSAL_ATA_ID_BUFFER_SIZE            21
#define UNIVERSAL_ATA_ID_FIRMWARE_REVISION      23
#define UNIVERSAL_ATA_ID_PRODUCT                27
#define UNIVERSAL_ATA_ID_MAX_MULTI_SELECT       47
#define UNIVERSAL_ATA_ID_DWORD_IO               48
#define UNIVERSAL_ATA_ID_TRUSTED                48
#define UNIVERSAL_ATA_ID_CAPABILITIES           49
#define UNIVERSAL_ATA_ID_OLD_PIO_MODES          51
#define UNIVERSAL_ATA_ID_OLD_DMA_MODES          52
#define UNIVERSAL_ATA_ID_FIELD_VALID            53
#define UNIVERSAL_ATA_ID_CURRENT_CYCLES         54
#define UNIVERSAL_ATA_ID_CURRENT_HEADS          55
#define UNIVERSAL_ATA_ID_CURRENT_SECTORS        56
#define UNIVERSAL_ATA_ID_MULTI_SECTOR           59
#define UNIVERSAL_ATA_ID_LBA_CAPACITY           60
#define UNIVERSAL_ATA_ID_SWDMA_MODES            62
#define UNIVERSAL_ATA_ID_MWDMA_MODES            63
#define UNIVERSAL_ATA_ID_PIO_MODES              64
#define UNIVERSAL_ATA_ID_EIDE_DMA_MINIMUM       65
#define UNIVERSAL_ATA_ID_EIDE_DMA_TIME          66
#define UNIVERSAL_ATA_ID_EIDE_PIO               67
#define UNIVERSAL_ATA_ID_EIDE_PIO_IO_READY      68
#define UNIVERSAL_ATA_ID_ADDITIONAL_SUPPORT     69
#define UNIVERSAL_ATA_ID_QUEUE_DEPTH            75
#define UNIVERSAL_ATA_ID_SATA_CAPABLE           76
#define UNIVERSAL_ATA_ID_SATA2_CAPABLE          77
#define UNIVERSAL_ATA_ID_FEATURE_SUPPORT        78
#define UNIVERSAL_ATA_ID_MAJOR_VERSION          80
#define UNIVERSAL_ATA_ID_COMMAND_SET_1          82
#define UNIVERSAL_ATA_ID_COMMAND_SET_2          83
#define UNIVERSAL_ATA_ID_CFSSE                  84
#define UNIVERSAL_ATA_ID_CFS_ENABLE_1           85
#define UNIVERSAL_ATA_ID_CFS_ENABLE_2           86
#define UNIVERSAL_ATA_ID_CSF_DEFAULT            87
#define UNIVERSAL_ATA_ID_UDMA_MODES             88
#define UNIVERSAL_ATA_ID_HARWARE_CONFIGURATION  93
#define UNIVERSAL_ATA_ID_SPG                    98
#define UNIVERSAL_ATA_ID_LBA_CAPACITY_2         100
#define UNIVERSAL_ATA_ID_SECTOR_SIZE            106
#define UNIVERSAL_ATA_ID_WWN                    108
#define UNIVERSAL_ATA_ID_LOGICAL_SECTOR_SIZE    117
#define UNIVERSAL_ATA_ID_COMMAND_SET_3          119
#define UNIVERSAL_ATA_ID_COMMAND_SET_4          120
#define UNIVERSAL_ATA_ID_LAST_LUN               126
#define UNIVERSAL_ATA_ID_DLF                    128
#define UNIVERSAL_ATA_ID_CSFO                   129
#define UNIVERSAL_ATA_ID_CFA_POWER              160
#define UNIVERSAL_ATA_ID_CFA_KEY_MANAGEMENT     162
#define UNIVERSAL_ATA_ID_CFA_MODES              163
#define UNIVERSAL_ATA_ID_DATA_SET_MANAGEMENT    169
#define UNIVERSAL_ATA_ID_SCT_COMMAND_XPORT      206
#define UNIVERSAL_ATA_ID_ROTATION_SPEED         217
#define UNIVERSAL_ATA_ID_PIO4                   1 << 1
#define UNIVERSAL_ATA_ID_ID_SEVERITY_LENGTH     20
#define UNIVERSAL_ATA_ID_FIRMWARE_LENGTH        8
#define UNIVERSAL_ATA_ID_PRODUCT_LENGTH         40
#define UNIVERSAL_ATA_ID_WWN_LENGTH             8

#define UNIVERSAL_ATA_PCI_CONTROL_OFFSET        2

#define UNIVERSAL_ATA_PIO0                      1
#define UNIVERSAL_ATA_PIO1                      1 | 1 << 1
#define UNIVERSAL_ATA_PIO2                      1 | 1 << 1 | 1 << 2
#define UNIVERSAL_ATA_PIO3                      1 | 1 << 1 | 1 << 2 | 1 << 3
#define UNIVERSAL_ATA_PIO4                      1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4
#define UNIVERSAL_ATA_PIO5                      1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5
#define UNIVERSAL_ATA_PIO6                      1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6

#define UNIVERSAL_ATA_PIO4_ONLY                 1 << 4

#define UNIVERSAL_ATA_SWDMA0                    1
#define UNIVERSAL_ATA_SWDMA1                    1 | 1 << 1
#define UNIVERSAL_ATA_SWDMA2                    1 | 1 << 1 | 1 << 2

#define UNIVERSAL_ATA_SWDMA2_ONLY               1 << 2

#define UINVERSAL_ATA_MWDMA0                    1
#define UINVERSAL_ATA_MWDMA1                    1 | 1 << 1
#define UINVERSAL_ATA_MWDMA2                    1 | 1 << 1 | 1 << 2
#define UINVERSAL_ATA_MWDMA3                    1 | 1 << 1 | 1 << 2 | 1 << 3
#define UINVERSAL_ATA_MWDMA4                    1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4

#define UNIVERSAL_ATA_MWDMA12_ONLY              1 << 1 | 1 << 2
#define UNIVERSAL_ATA_MWDMA2_ONLY               1 << 2

#define UNIVERSAL_ATA_UDMA0                     1
#define UNIVERSAL_ATA_UDMA1                     1 | 1 << 1
#define UNIVERSAL_ATA_UDMA2                     1 | 1 << 1 | 1 << 2
#define UNIVERSAL_ATA_UDMA3                     1 | 1 << 1 | 1 << 2 | 1 << 3
#define UNIVERSAL_ATA_UDMA4                     1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4
#define UNIVERSAL_ATA_UDMA5                     1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5
#define UNIVERSAL_ATA_UDMA6                     1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6
#define UNIVERSAL_ATA_UDMA7                     1 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7

#define UNIVERSAL_ATA_UDMA24_ONLY               1 << 2 | 1 << 4
#define UNIVERSAL_ATA_UDMA_MASK_40C             UNIVERSAL_ATA_UDMA2

#define UNIVERSAL_ATA_PRD_SIZE                  8
#define UNIVERSAL_ATA_PRD_TABLE_SIZE            UNIVERSAL_ATA_MAX_PRD * UNIVERSAL_ATA_PRD_SIZE
#define UNIVERSAL_ATA_PRD_EOT                   1 << 31

#define UNIVERSAL_ATA_DMA_TABLE_OFFSET          4
#define UNIVERSAL_ATA_DMA_STATUS                2
#define UNIVERSAL_ATA_DMA_COMMAND               0
#define UNIVERSAL_ATA_DMA_WRITE                 1 << 3
#define UNIVERSAL_ATA_DMA_START                 1
#define UNIVERSAL_ATA_DMA_INTERRUPT             1 << 2
#define UNIVERSAL_ATA_DMA_ERROR                 1 << 1
#define UNIVERSAL_ATA_DMA_ACTIVE                1

#define UNIVERSAL_ATA_HOB                       1 << 7
#define UNIVERSAL_ATA_NEIN                      1 << 1
#define UNIVERSAL_ATA_LBA                       1 << 6
#define UNIVERSAL_ATA_DEV1                      1 << 4
#define UNIVERSAL_ATA_DEVICE_OBS                1 << 7 | 1 << 5
#define UNIVERSAL_ATA_DEVCTL_OBS                1 << 3
#define UNIVERSAL_ATA_BUSY                      1 << 7
#define UNIVERSAL_ATA_DRDY                      1 << 6
#define UNIVERSAL_ATA_DF                        1 << 5
#define UNIVERSAL_ATA_DSC                       1 << 4
#define UNIVERSAL_ATA_DRQ                       1 << 3
#define UNIVERSAL_ATA_CORR                      1 << 2
#define UNIVERSAL_ATA_SENCE                     1 << 1
#define UNIVERSAL_ATA_ERROR                     1
#define UNIVERSAL_ATA_SRST                      1 << 2
#define UNIVERSAL_ATA_ICRC                      1 << 7
#define UNIVERSAL_ATA_BBK                       UNIVERSAL_ATA_ICRC
#define UNIVERSAL_ATA_UNC                       1 << 6
#define UNIVERSAL_ATA_MC                        1 << 5
#define UNIVERSAL_ATA_IDNF                      1 << 4
#define UNIVERSAL_ATA_MCR                       1 << 3
#define UNIVERSAL_ATA_ABORTED                   1 << 2
#define UNIVERSAL_ATA_TRACK0_CONFIG             1 << 1
#define UNIVERSAL_ATA_AMNF                      1
#define UNIVERSAL_ATA_LFS                       0xF0
#define UNIVERSAL_ATA_EOM                       1 << 1
#define UNIVERSAL_ATA_ILI                       1
#define UNIVERSAL_ATA_IO                        1 << 1
#define UNIVERSAL_ATA_COD                       1 << 0

#define UNIVERSAL_ATA_REGISTER_DATA             0
#define UNIVERSAL_ATA_REGISTER_ERROR            1
#define UNIVERSAL_ATA_REGISTER_NSECT            2
#define UNIVERSAL_ATA_REGISTER_LBAL             3
#define UNIVERSAL_ATA_REGISTER_LBAM             4
#define UNIVERSAL_ATA_REGISTER_LBAH             5
#define UNIVERSAL_ATA_REGISTER_DEVICE           6
#define UNIVERSAL_ATA_REGISTER_STATUS           7
#define UNIVERSAL_ATA_REGISTER_FEATURE          UNIVERSAL_ATA_REGISTER_ERROR
#define UNIVERSAL_ATA_REGISTER_COMMAND          UNIVERSAL_ATA_REGISTER_STATUS
#define UNIVERSAL_ATA_REGISTER_BYTEL            UNIVERSAL_ATA_REGISTER_LBAM
#define UNIVERSAL_ATA_REGISTER_BYTEH            UNIVERSAL_ATA_REGISTER_LBAH
#define UNIVERSAL_ATA_REGISTER_DEVSEL           UNIVERSAL_ATA_REGISTER_DEVICE
#define UNIVERSAL_ATA_REGISTER_IRQ              UNIVERSAL_ATA_REGISTER_NSECT

#define ATA_COMMAND_DEVICE_RESET                0x08
#define ATA_COMMAND_CHECK_POWER                 0xE5
#define ATA_COMMAND_STANDBY                     0xE2 //https://www.youtube.com/watch?v=wbshq1-dzKA
#define ATA_COMMAND_IDLE                        0xE3
#define ATA_COMMAND_EED                         0x90
#define ATA_COMMAND_DOWNLOAD_MICRO              0x92
#define ATA_COMMAND_DOWNLOAD_MICRO_DMA          0x93
#define ATA_COMMAND_NOP                         0x00
#define ATA_COMMAND_FLUSH                       0xE7
#define ATA_COMMAND_FLUSH_EXT                   0xEA
#define ATA_COMMAND_IDENTIFY_ATA                0xEC
#define ATA_COMMAND_IDENTIFY_ATAPI              0xA1
#define ATA_COMMAND_SERVICE                     0xA2
#define ATA_COMMAND_READ                        0xC8
#define ATA_COMMAND_READ_EXT                    0x25
#define ATA_COMMAND_READ_QUEUED                 0x26
#define ATA_COMMAND_READ_STREAM_EXT             0x2B
#define ATA_COMMAND_READ_STREAM_DMA_EXT         0x2A
#define ATA_COMMAND_WRITE                       0xCA
#define ATA_COMMAND_WRITE_EXT                   0x35
#define ATA_COMMAND_WRITE_QUEUED                0x36
#define ATA_COMMAND_WRITE_STREAM_EXT            0x3B
#define ATA_COMMAND_WRITE_STREAM_DMA_EXT        0x3A
#define ATA_COMMAND_WRITE_FUA_EXT               0x3D
#define ATA_COMMAND_WRITE_QUEUED_FUA_EXT        0x3E
#define ATA_COMMAND_FPDMA_READ                  0x60
#define ATA_COMMAND_FPDMA_WRITE                 0x61
#define ATA_COMMAND_NCQ_NON_DATA                0x63
#define ATA_COMMAND_FPDMA_SEND                  0x64
#define ATA_COMMAND_FPDMA_RECIEVE               0x65
#define ATA_COMMAND_PIO_READ                    0x20
#define ATA_COMMAND_PIO_READ_EXT                0x24
#define ATA_COMMAND_PIO_WRITE                   0x30
#define ATA_COMMAND_PIO_WRITE_EXT               0x34
#define ATA_COMMAND_READ_MULTI                  0xC4
#define ATA_COMMAND_READ_MULTI_EXT              0x29
#define ATA_COMMAND_WRITE_MULTI                 0xC5
#define ATA_COMMAND_WRITE_MULTI_EXT             0x39
#define ATA_COMMAND_WRITE_MULTI_FUA_EXT         0xCE
#define ATA_COMMAND_SET_FEATURES                0xEF
#define ATA_COMMAND_SET_MULTI                   0xC6
#define ATA_COMMAND_PACKET                      0xA0
#define ATA_COMMAND_VERIFY                      0x40
#define ATA_COMMAND_VERIFY_EXT                  0x42
#define ATA_COMMAND_WRITE_UNCORR_EXT            0x45
#define ATA_COMMAND_STAND_BY_NOW_1              0xE0
#define ATA_COMMAND_IDLE_IMMEDIATE              0xE1
#define ATA_COMMAND_SLEEP                       0xE6
#define ATA_COMMAND_INITIALIZE_DEV_PARAM        0x91
#define ATA_COMMAND_READ_NATIVE_MAX             0xF8
#define ATA_COMMAND_READ_NATIVE_MAX_EXT         0x27
#define ATA_COMMAND_SET_MAX                     0xF9
#define ATA_COMMAND_SET_MAX_EXT                 0x37
#define ATA_COMMAND_READ_LOG_EXT                0x2F
#define ATA_COMMAND_WRITE_LOG_EXT               0x3F
#define ATA_COMMAND_READ_LOG_DMA_EXT            0x47
#define ATA_COMMAND_WRITE_LOG_DMA_EXT           0x57
#define ATA_COMMAND_TRUSTED_NON_DATA            0x5B
#define ATA_COMMAND_TRUSTED_RCV                 0x5C
#define ATA_COMMAND_TRUSTED_RCV_DMA             0x5D
#define ATA_COMMAND_TRUSTED_SND                 0x5E
#define ATA_COMMAND_TRUSTED_SND_DMA             0x5F
#define ATA_COMMAND_PMP_READ                    0xE4
#define ATA_COMMAND_PMP_READ_DMA                0xE9
#define ATA_COMMAND_PMP_WRITE                   0xE8
#define ATA_COMMAND_PMP_WRITE_DMA               0xEB
#define ATA_COMMAND_CONF_OVERLAY                0xB1
#define ATA_COMMAND_SEC_SET_PAS                 0xF1
#define ATA_COMMAND_SEC_UNLOCK                  0xF2
#define ATA_COMMAND_SEC_ERASE_PREP              0xF3
#define ATA_COMMAND_SEC_ERASE_UNIT              0xF4
#define ATA_COMMAND_SEC_FREEZE_LOCK             0xF5
#define ATA_COMMAND_SEC_DISABLE_PASS            0xF6
#define ATA_COMMAND_CONFIG_STREAM               0x51
#define ATA_COMMAND_SMART                       0xB0
#define ATA_COMMAND_MEDIA_LOCK                  0xDE
#define ATA_COMMAND_MEDIA_UNLOCK                0xDF
#define ATA_COMMAND_DSM                         0x06
#define ATA_COMMAND_CHK_MED_CRD_TYPE            0xD1
#define ATA_COMMAND_REQ_EXT_ERROR               0x03
#define ATA_COMMAND_WRITE_NE                    0x38
#define ATA_COMMAND_TRANS_SECT                  0x87
#define ATA_COMMAND_ERASE                       0xC0
#define ATA_COMMAND_WRITE_MULT_NE               0xCD
#define ATA_COMMAND_REQ_SENCE_DATA              0x0B
#define ATA_COMMAND_SANATIZE_DEVICE             0xB4
#define ATA_COMMAND_ZAC_MANAGEMENT_IN           0x4A
#define ATA_COMMAND_ZAC_MANAGEMENT_OUT          0x9F

#define ATA_COMMAND_RESTORE                     0x10

#define ATA_SUB_COMMAND_FPDMA_RECIVE_RD_LOG_DMA_EXT             0x01
#define ATA_SUB_COMMAND_FPDMA_RECIEV_ZAC_MANAGEMENT_IN          0x02

#define ATA_SUB_COMMAND_FPDMA_SEND_DSM                          0x00
#define ATA_SUB_COMMAND_FPDMA_SEND_WR_LOG_DMA_EXT               0x02

#define ATA_SUB_COMMAND_NCQ_NON_DATA_ABORT_QUEUE                0x00
#define ATA_SUB_COMMAND_NCQ_NON_DATA_SET_FEATURES               0x05
#define ATA_SUB_COMMAND_NCQ_NON_DATA_ZERO_EXT                   0x06
#define ATA_SUB_COMMAND_NCQ_NON_DATA_ZAC_MANAGEMENT_OUT         0x07

#define ATA_SUB_COMMAND_ZAC_MANAGEMENT_IN_REPORT_ZONES          0x00
#define ATA_SUB_COMMAND_ZAC_MANAGEMENT_OUT_CLOSED_ZONE          0x01
#define ATA_SUB_COMMAND_ZAC_MANAGEMENT_OUT_FINISH_ZONE          0x02
#define ATA_SUB_COMMAND_ZAC_MANAGEMENT_OUT_OPEN_ZONE            0x03
#define ATA_SUB_COMMAND_ZAC_MANAGEMENT_OUT_RESET_WRITE_POINTER  0x04

#define UNIVERSAL_ATA_LOG_DIRECTORY                             0x00
#define UNIVERSAL_ATA_LOG_SATA_NCQ                              0x10
#define UNIVERSAL_ATA_LOG_NCQ_NON_DATA                          0x12
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV                         0x13
#define UNIVERSAL_ATA_LOG_CDL                                   0x18
#define UNIVERSAL_ATA_LOG_CDL_SIZE                              UNIVERSAL_ATA_SECTOR_SIZE
#define UNIVERSAL_ATA_LOG_IDENTIFY_DEVICE                       0x30
#define UNIVERSAL_ATA_LOG_SENCE_NCQ                             0x0F
#define UNIVERSAL_ATA_LOG_SENCE_NCQ_SIZE                        UNIVERSAL_ATA_SECTOR_SIZE * 2
#define UNIVERSAL_ATA_LOG_CONCURRENT_POSITIONING_RANGES         0x47
#define UNIVERSAL_ATA_LOG_SUPPORTED_CAPABILITES                 0x03
#define UNIVERSAL_ATA_LOG_CURRENT_SETTINGS                      0x04
#define UNIVERSAL_ATA_LOG_SECURITY                              0x06
#define UNIVERSAL_ATA_LOG_SATA_SETTINGS                         0x08
#define UNIVERSAL_ATA_LOG_ZONED_INFORMATION                     0x09
#define UNIVERSAL_ATA_LOG_DEVSLP_OFFSET                         0x30
#define UNIVERSAL_ATA_LOG_DEVSLP_SIZE                           0x08
#define UNIVERSAL_ATA_LOG_DEVSLP_MDAT                           0x00
#define UNIVERSAL_ATA_LOG_DEVSLP_MDAT_MASK                      0x1F
#define UNIVERSAL_ATA_LOG_DEVSLP_DETO                           0x01
#define UNIVERSAL_ATA_LOG_DEVSLP_VALID                          0x07
#define UNIVERSAL_ATA_LOG_DEVSLP_VALID_MASK                     0x80
#define UNIVERSAL_ATA_LOG_NCQ_PRIO_OFFSET                       0x09
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_SUB_COMMAND_OFFSET      0x00
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_SUB_COMMAND_DSM         1
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_DSM_OFFSET              0x04
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_DSM_TRIM                1
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_READ_LOG_OFFSET         0x08
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_READ_LOG_SUPPORTED      1
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_WRITE_LOG_OFFSET        0x0C
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_WRITE_LOG_SUPORTED      1
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_ZAC_MANAGEMENT_OFFSET   0x10
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_ZAC_MANAGEMENT_OUT_SUPPORTED    1
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_ZAC_MANAGEMENT_IN_SUPPORTED     1 << 1
#define UNIVERSAL_ATA_LOG_NCQ_SEND_RECV_ZAC_SIZE                0x14
#define ATA_OBSOLETE_COMMAND_READ_LONG                          0x22
#define ATA_OBSOLETE_COMMAND_READ_LONG_ONCE                     0x23
#define ATA_OBSOLETE_COMMAND_WRITE_LONG                         0x32
#define ATA_OBSOLETE_COMMAND_WRITE_LONG_ONCE                    0x33
#define SET_FEATURES_XFER                                       0x03
#define XFER_UDMA7                                              0x47
#define XFER_UDMA6                                              0x46
#define XFER_UDMA5                                              0x45
#define XFER_UDMA4                                              0x44
#define XFER_UDMA3                                              0x43
#define XFER_UDMA2                                              0x42
#define XFER_UDMA1                                              0x41
#define XFER_UDMA0                                              0x40
#define XFER_MW_UDMA4                                           0x24
#define XFER_MW_UDMA3                                           0x23
#define XFER_MW_UDMA2                                           0x22
#define XFER_MW_UDMA1                                           0x21
#define XFER_MW_UDMA0                                           0x20
#define XFER_SW_DMA2                                            0x12
#define XFER_SW_DMA1                                            0x11
#define XFER_SW_DMA0                                            0x10
#define XFER_PIO6                                               0x0E
#define XFER_PIO5                                               0x0D
#define XFER_PIO4                                               0x0C
#define XFER_PIO3                                               0x0B
#define XFER_PIO2                                               0x0A
#define XFER_PIO1                                               0x09
#define XFER_PIO0                                               0x08
#define XFER_PIO_SLOW                                           0x00
#define SET_FEATURES_WRITE_CACHE_ENABLE                         0x02
#define SET_FEATURES_WRITE_CACHE_DISABLE                        0x82
#define SET_FEATURES_READ_AHEAD_ENABLE                          0xAA
#define SET_FEATURES_READ_AHEAD_DISABLE                         0x55
#define SET_FEATURES_AAM_ENABLE                                 0x42
#define SET_FEATURES_AAM_DISABLE                                0xC2
#define SET_FEATURES_SPINUP                                     0x07
#define SET_FEATURES_SPINUP_TIMEOUT                             30000
#define SET_FEATURES_SATA_ENABLE                                0x10
#define SET_FEATURES_SATA_DISABLE                               0x90
#define SET_FEATURES_CDL                                        0x0D
#define SATA_FPDMA_OFFSET                                       0x01
#define SATA_FPDMA_AA                                           0x02
#define SATA_DIPM                                               0x03
#define SATA_FPDMA_IN_ORDER                                     0x04
#define SATA_AN                                                 0x05
#define SATA_SSP                                                0x06
#define SATA_DEVSLP                                             0x09
#define SET_FEATURES_SENCT_DATA                                 0xC3
#define SET_FEATURES_SENCT_DATA_SUCCESSFULL_NCQ                 0xC4
#define UNIVERSAL_ATA_MAX_ADDRESS                                0x00
#define UNIVERSAL_ATA_MAX_PASWORD                               0x01
#define UNIVERSAL_ATA_MAX_LOCK                                  0x02
#define UNIVERSAL_ATA_MAX_UNLOCK                                0x03    
#define UNIVERSAL_ATA_MAX_FREEZE_LOCK                           0x04
#define UNIVERSAL_ATA_MAX_PASSWORD_DMA                          0x05
#define UNIVERSAL_ATA_MAX_UNLOCK_DMA                            0x06
#define UNIVERSAL_ATA_DEVICE_CONFIGURE_OVERLAY_RESTORE          0xC0
#define UNIVERSAL_ATA_DEVICE_CONFIGURE_OVERLAY_FREEZE_LOCK      0xC1
#define UNIVERSAL_ATA_DEVICE_CONFIGURE_OVERLAY_IDENTIFY         0xC2
#define UNIVERSAL_ATA_DEVICE_CONFIGURE_OVERLAY_SET              0xC3
#define UNIVERSAL_ATA_SMART_ENABLE                              0xD8
#define UNIVERSAL_ATA_SMART_READ_VALUES                         0xD0
#define UNIVERSAL_ATA_SMART_READ_THRESHOLD                      0xD1
#define UNIVERSAL_ATA_DSM_TRIM                                  0x01
#define UNIVERSAL_ATA_SMART_LBAM_PASS                           0x4F
#define UNIVERSAL_ATA_SMART_LBAH_PASS                           0xC2
#define UNIVERSAL_ATAPI_PACKET_DMA                              1
#define UNIVERSAL_ATAPI_DMA_DIRECTORY                           1 << 2
#define UNIVERSAL_ATAPI_COMMAND_DATA_BUFFER_LENGTH              16
#define SATA_PMP_MAX_PORTS                                      15
#define SATA_PMP_CONTROL_PORTS                                  15
#define SATA_PMP_GSCR_DWORDS                                    128
#define SATA_PMP_GSCR_PRODUCT_ID                                0
#define SATA_PMP_GSCR_REVISION                                  1
#define SATA_PMP_GSCR_PORT_INFORMATION                          2
#define SATA_PMP_GSCR_ERROR                                     32
#define SATA_PMP_GSCR_ERROR_ENABLE                              33
#define SATA_PMP_GSCR_FEATURE                                   64
#define SATA_PMP_GSCR_FEATURE_ENABLE                            96

#define SATA_PMP_PSCR_STATUS                                    0
#define SATA_PMP_PSCR_ERROR                                     1
#define SATA_PMP_PSCR_CONTROL                                   2

#define SATA_PMP_FEATURE_BIST                                   1
#define SATA_PMP_FEATURE_PM_REQUIRED                            1 << 1
#define SATA_PMP_FEATURE_DYNSSC                                 1 << 2
#define SATA_PMP_FEATURE_NOTIFY                                 1 << 3

#define ATA_CABLE_TYPE_NONE                     0
#define ATA_CABLE_TYPE_PATA40                   1
#define ATA_CABLE_TYPE_PATA80                   2
#define ATA_CABLE_TYPE_PATA40_SHORT             3
#define ATA_CABLE_TYPE_PATA40_UNKONW            4
#define ATA_CABLE_TYPE_PATA40_IGNORE_CABLE      5
#define ATA_CABLE_TYPE_PATA40_SATA              6

#define SATA_STATUS_CONTROL_STATUS              0
#define SATA_STATUS_CONTROL_ERROR               1
#define SATA_STATUS_CONTROL_CONTROL             2
#define SATA_STATUS_CONTROL_ACTIVE              3
#define SATA_STATUS_CONTROL_NOTIFICATION        4

#define UNIVERSAL_ATA_SEVERITY_DATA_RECOVERED               1 << 0
#define UNIVERSAL_ATA_SEVERITY_COMM_RECOVERED               1 << 1
#define UNIVERSAL_ATA_SEVERITY_DATA                         1 << 8
#define UNIVERSAL_ATA_SEVERITY_PERSISTANT                   1 << 9
#define UNIVERSAL_ATA_SEVERITY_PROTOCOL                     1 << 10
#define UNIVERSAL_ATA_SEVERITY_INTERNAL                     1 << 11
#define UNIVERSAL_ATA_SEVERITY_PHT_READY                    1 << 16
#define UNIVERSAL_ATA_SEVERITY_PHY_INTERNAL                 1 << 17
#define UNIVERSAL_ATA_SEVERITY_COMM_WAKE                    1 << 18
#define UNIVERSAL_ATA_SEVERITY_10B_8B_ERORO                 1 << 19
#define UNIVERSAL_ATA_SEVERITY_DISPARITY                    1 << 20
#define UNIVERSAL_ATA_SEVERITY_CRC                          1 << 21
#define UNIVERSAL_ATA_SEVERITY_HANDSHAKE                    1 << 22
#define UNIVERSAL_ATA_SEVERITY_LINK_SEQUENCE_ERROR          1 << 23
#define UNIVERSAL_ATA_SEVERITY_TRANSPORT_STATE_ERROR        1 << 24
#define UNIVERSAL_ATA_SEVERITY_UNRECOGNIZED_FIS             1 << 25
#define UNIVERSAL_ATA_SEVERITY_DEVICE_EXCHANGE              1 << 26

#define UNIVERSAL_ATA_PROTOCOL_FLAGS_PIO                    1
#define UNIVERSAL_ATA_PROTOCOL_FLAGS_DMA                    1 << 1
#define UNIVERSAL_ATA_PROTOCOL_FLAGS_NCQ                    1 << 2
#define UNIVERSAL_ATA_PROTOCOL_FLAGS_ATAPI                  1 << 3
#define UNIVERSAL_ATA_PROTOCOL_UNKOWN                       (uint8_t)-1
#define UNIVERSAL_ATA_PROTOCOL_NO_DATA                      0
#define UNIVERSAL_ATA_PROTOCOL_PIO                          UNIVERSAL_ATA_PROTOCOL_FLAGS_PIO
#define UNIVERSAL_ATA_PROTOCOL_DMA                          UNIVERSAL_ATA_PROTOCOL_DMA
#define UNIVERSAL_ATA_PROTOCOL_NCQ_NO_DATA                  UNIVERSAL_ATA_PROTOCOL_FLAGS_NCQ
#define UNIVERSAL_ATA_PROTOCOL_NCQ                          UNIVERSAL_ATA_PROTOCOL_DMA | UNIVERSAL_ATA_PROTOCOL_FLAGS_NCQ
#define UNIVERSAL_ATAPI_PROTOCOL_NO_DATA                    UNIVERSAL_ATA_PROTOCOL_FLAGS_ATAPI
#define UNIVERSAL_ATAPI_PROTOCOL_PIO                        UNIVERSAL_ATA_PROTOCOL_FLAGS_ATAPI | UNIVERSAL_ATA_PROTOCOL_FLAGS_PIO
#define UNIVERSAL_ATAPI_PROTOCOL_DMA                        UNIVERSAL_ATA_PROTOCOL_FLAGS_ATAPI | UNIVERSAL_ATA_PROTOCOL_DMA

#define UNIVERSAL_ATA_IO_CONTROL_GET_IO32                   0x309
#define UNIVERSAL_ATA_IO_CONTROL_SET_IO32                   0x324

#define ATA_FLAG_COMMON         1
#define ATA_FLAG_NO_DIPM        1 << 1
#define ATA_FLAG_SATA           1 << 2
#define ATA_FLAG_PIO_DMA        1 << 3
#define ATA_FLAG_NCQ            1 << 4
#define ATA_FLAG_FPDMA_AA       1 << 5
#define ATA_FLAG_FPDMA_AUXILERY 1 << 6
#define ATA_FLAG_PMP            1 << 7
#define ATA_FLAG_NO_SSC         1 << 8
#define ATA_FLAG_NO_DEV_SLP     1 << 9
#define ATA_FLAG_SLAVE_POSS     1 << 10

typedef struct _ATA_BMDMA_PRD{
    uint32_t    Address;
    uint32_t    FlagsAndLength;
}ATA_BMDMA_PRD, * PATA_BMDMA_PRD;

#define IsAtaIdentifcatiionAta(Identification)                              (((Identification)[UNIVERSAL_ATA_ID_CONFIGURATION] & (1 << 15)) == 0)
#define DoesAtaIdentificationHaveLba(Identification)                        ((Identification)[UNIVERSAL_ATA_ID_CAPABILITIES] & (1 << 9))
#define DoesAtaIdentificationHaveDma(Identification)                        ((Identification)[UNIVERSAL_ATA_ID_CAPABILITIES] & (1 << 8))
#define DoesAtaIdentificationHaveNcq(Identification)                        ((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] & (1 << 8))
#define AtaIdentificationGetQueueDepth(Identification)                      (((Identification)[UNIVERSAL_ATA_ID_QUEUE_DEPTH]  & 0x1F) + 1)
#define DoesAtaIdentificationAllowDeviceRemoval(Identification)             ((Identification)[UNIVERSAL_ATA_ID_CONFIGURATION] & (1 << 7))
#define DoesAtaIdnetificationHaveAtapi(Identification)                      ((((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0x0000) && ((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0xFFFF)) && ((Identification)[UNIVERSAL_ATA_ID_FEATURE_SUPPORT] & (1 << 5)))
#define DoesAtaIdnetificationHaveFpDmaAa(Identification)                    ((((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0x0000) && ((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0xFFFF)) && ((Identification)[UNIVERSAL_ATA_ID_FEATURE_SUPPORT] & (1 << 2)))
#define DoesAtaIdnetificationHaveDevslp(Identification)                     ((((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0x0000) && ((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0xFFFF)) && ((Identification)[UNIVERSAL_ATA_ID_FEATURE_SUPPORT] & (1 << 8)))
#define DoesAtaIdnetificationHaveNcqAutosence(Identification)               ((((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0x0000) && ((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0xFFFF)) && ((Identification)[UNIVERSAL_ATA_ID_FEATURE_SUPPORT] & (1 << 7)))
#define DoesAtaIdnetificationHaveDipm(Identification)                       ((((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0x0000) && ((Identification)[UNIVERSAL_ATA_ID_SATA_CAPABLE] != 0xFFFF)) && ((Identification)[UNIVERSAL_ATA_ID_FEATURE_SUPPORT] & (1 << 3)))
#define IsAtaIdentificationIoReadyDisable(Identification)                   ((Identification)[UNIVERSAL_ATA_ID_CAPABILITIES] & (1 << 10))
#define DoesAtaIdentificationHaveIoReady(Identification)                    ((Identification)[UNIVERSAL_ATA_ID_CAPABILITIES] & (1 << 11))
#define AtaIdentification32Bit(Identification,Offset)                       (((uint32_t)(Identification)[(Offset) + 1] << 16) | ((uint32_t)(Identification)[Offset]))
#define AtaIdentification64Bit(Identification,Offset)                       (((uint64_t)(Identification)[(Offset) + 3] << 48) | ((uint64_t)(Identification)[(Offset) + 2] << 32) | ((uint64_t)(Identification)[(Offset) + 1] << 16) | ((uint64_t)(Identification)[Offset]))
#define DoesAtaIdentificationHaveCommandCompletionInterrupt(Identification) (((Identification)[UNIVERSAL_ATA_ID_CONFIGURATION] & 0x60) == 0x20)
#define DoesAtaIdentificationHaveDataAttention(Identification)              ((Identification)[UNIVERSAL_ATA_ID_SATA2_CAPABLE] & (1 << 4))

static inline bool DoesAtaIdentificationHaveHipm(uint16_t* Identification){
    uint16_t Result = Identification[UNIVERSAL_ATA_ID_CAPABILITIES];

    if((Result == 0) || (Result == 0xFFFF)){
        return false;
    }

    return (Result & (1 << 9));
}

static inline bool DoesAtaIdentificationHaveFua(uint16_t* Identification){
    uint16_t Result = Identification[UNIVERSAL_ATA_ID_CFSSE];
    if((Result & 0xC000) != 0x4000){
        return false;
    }
    return (Result & (1 << 6));
}

static inline bool DoesAtaIdentificationHaveFlush(uint16_t* Identification){
    uint16_t Result = Identification[UNIVERSAL_ATA_ID_COMMAND_SET_2];
    if((Result & 0xC000) != 0x4000){
        return false;
    }
    return (Result & (1 << 12));
}

static inline bool DoesAtaIdentificationHaveFlushExt(uint16_t* Identification){
    uint16_t Result = Identification[UNIVERSAL_ATA_ID_COMMAND_SET_2];
    if((Result & 0xC000) != 0x4000){
        return false;
    }
    return (Result & (1 << 13));
}

static inline uint32_t GetAtaIdentificationLogicalSectorSize(uint16_t* Identification){
    if((Identification[UNIVERSAL_ATA_SECTOR_SIZE] & 0xD000) == 0x5000){
        return (((Identification[UNIVERSAL_ATA_ID_LOGICAL_SECTOR_SIZE+1] << 16) + Identification[UNIVERSAL_ATA_ID_LOGICAL_SECTOR_SIZE]) * sizeof(uint16_t));
    }
    return UNIVERSAL_ATA_SECTOR_SIZE;
}

static inline uint8_t AtaIdentificationLog2PerPhysicalSector(uint16_t* Identification){
    uint16_t Result = Identification[UNIVERSAL_ATA_ID_SECTOR_SIZE];
    if((Result & 0xE000) == 0x6000){
        return Result & 0x0F;
    }
    return 0;
}

static inline uint16_t GetAtaIdentificationLogicalSectorOffset(uint16_t* Identification, uint8_t Log2PerPhysical){
    uint16_t Word209 = Identification[209];
    if((Log2PerPhysical > 1) && (Word209 & 0xC000) == 0x4000){
        uint16_t FirstSector = (Word209 & 0x3FFF);
        if(FirstSector > 0){
            return ((1 << Log2PerPhysical) - FirstSector);
        }
    }
    return 0;
}

static inline bool DoesAtaIdentificationHaveLba48(uint16_t* Identification){
    uint16_t CommandSet2 = Identification[UNIVERSAL_ATA_ID_COMMAND_SET_2];
    if((CommandSet2 & 0xC000) != 0x4000){
        return false;
    }
    if(!AtaIdentification64Bit(Identification, UNIVERSAL_ATA_ID_LBA_CAPACITY_2)){
        return false;
    }
    return (CommandSet2 & (1 << 10));
}

static inline bool IsAtaIdentificationHpaEnabled(uint16_t* Identification){
    if((Identification[UNIVERSAL_ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000){
        return false;
    }
    if((Identification[UNIVERSAL_ATA_ID_CSF_DEFAULT] & 0xC000) != 0x4000){
        return false;
    }
    if((Identification[UNIVERSAL_ATA_ID_CFS_ENABLE_1] & (1 << 10)) == 0){
        return false;
    } 
    return (Identification[UNIVERSAL_ATA_ID_COMMAND_SET_1] & (1 << 10));
}

static inline bool DoesAtaIdentificationHaveWCache(uint16_t* Identification){
    if((Identification[UNIVERSAL_ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000){
        return false;
    }
    return (Identification[UNIVERSAL_ATA_ID_COMMAND_SET_1] & (1 << 5));
}

static inline bool DoesAtaIdentificationHavePowerManagement(uint16_t* Identification){
    if((Identification[UNIVERSAL_ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000){
        return false;
    }
    return (Identification[UNIVERSAL_ATA_ID_COMMAND_SET_1] & (1 << 3));
}

static inline bool IsAtaIdentificationReadAheadEnabled(uint16_t* Identification){
    if((Identification[UNIVERSAL_ATA_ID_CSF_DEFAULT] & 0xC000) != 0x4000){
        return false;
    }
    return (Identification[UNIVERSAL_ATA_ID_CFS_ENABLE_1] & (1 << 6));
}

static inline bool AtaIdentificationWCacheEnabled(uint16_t* Identification){
    if((Identification[UNIVERSAL_ATA_ID_CSF_DEFAULT] & 0xC000) != 0x4000){
        return false;
    }
    return (Identification[UNIVERSAL_ATA_ID_CFS_ENABLE_1] & (1 << 5));
}

static inline bool DoesAtaIdentificationHaveLogDmaExt(uint16_t* Identification){
    if(!(Identification[UNIVERSAL_ATA_ID_CFS_ENABLE_2] & (1 << 15))){
        return false;
    }
    if(((Identification[UNIVERSAL_ATA_ID_COMMAND_SET_3] & 0xC008) == 0x4008) || ((Identification[UNIVERSAL_ATA_ID_COMMAND_SET_4] & 0xC008) == 0x4008)){
        return true;
    }
    return false;
}

static inline bool DoesAtaIdentificationHaveSenceReporting(uint16_t* Identification){
    if(!(Identification[UNIVERSAL_ATA_ID_CFS_ENABLE_2] & (1 << 15))){
        return false;
    }
    if((Identification[UNIVERSAL_ATA_ID_COMMAND_SET_3] & ((1 << 15) | (1 << 14))) != (1 << 14)){
        return false;
    }
    return (Identification[UNIVERSAL_ATA_ID_COMMAND_SET_3] & (1 << 6));
}

static inline bool IsAtaIdentificationSenceReportingEnabled(uint16_t* Identification){
    if(!IsAtaIdentificationSenceReportingEnabled(Identification)){
        return false;
    }
    if((Identification[UNIVERSAL_ATA_ID_COMMAND_SET_4] & ((1 << 15) | (1 << 14))) != (1 << 14)){
        return false;
    }
    return (Identification[UNIVERSAL_ATA_ID_COMMAND_SET_4] & (1 << 6));
}

static inline bool AtaIdentificationSctDataTable(uint16_t* Identification){
    return ((Identification[UNIVERSAL_ATA_ID_SCT_COMMAND_XPORT] & (1 << 5)) ? true : false);
}

static inline bool AtaIdentificationSctFeaturesControl(uint16_t* Identification){
    return ((Identification[UNIVERSAL_ATA_ID_SCT_COMMAND_XPORT] & (1 << 4)) ? true : false);
}

static inline bool AtaIdentificationSctErrorRecoveryControl(uint16_t* Identification){
    return ((Identification[UNIVERSAL_ATA_ID_SCT_COMMAND_XPORT] & (1 << 1)) ? true : false);
}

static inline bool AtaIdentificationSctSupported(uint16_t* Identification){
    return ((Identification[UNIVERSAL_ATA_ID_SCT_COMMAND_XPORT] & (1)) ? true : false);
}

static uint32_t AtaIdentificationGetMajorVersion(uint16_t* Identification){
    uint32_t Version;
    if(Identification[UNIVERSAL_ATA_ID_MAJOR_VERSION] == 0xFFFF){
        return 0;
    }
    for(Version = 14; Version >= 1; Version--){
        if(Identification[UNIVERSAL_ATA_ID_MAJOR_VERSION] & (1 << Version)){
            break;
        }
    }
    return Version;
}

static inline bool DoeAtaIdentificationHaveSata(uint16_t* Identification){
    if((Identification[UNIVERSAL_ATA_ID_HARWARE_CONFIGURATION] == 0) && ((uint16_t)Identification[UNIVERSAL_ATA_ID_MAJOR_VERSION] > 0x20)){
        return true;
    }
    return false;
}

static inline bool DoesAtaIdentificationHaveDwordIo(uint16_t* Identification){
    if(AtaIdentificationGetMajorVersion(Identification) > 7){
        return false;
    }
    return (Identification[UNIVERSAL_ATA_ID_DWORD_IO] & (1 << 0));
}

static inline bool DoesAtaIdentificationHaveTrust(uint16_t* Identification){
    if((AtaIdentificationGetMajorVersion(Identification) <= 7) && ((Identification[UNIVERSAL_ATA_ID_CFSSE] & 0xC000) ==  0x4000) && (Identification[UNIVERSAL_ATA_ID_CFSSE] & (1 << 13))){
        return true;
    }
    return false;
}

static inline bool DoesAtaIdentificationHaveUnloading(uint16_t* Identification){
    if((AtaIdentificationGetMajorVersion(Identification) >= 7) && (Identification[UNIVERSAL_ATA_ID_CFSSE] & (1 << 13)) && (Identification[UNIVERSAL_ATA_ID_CFSSE] & 0xC000) == 0x4000){
        return true;
    }
    return false;
}

static inline bool DoesAtaIdentificationHaveWwn(uint16_t* Identification){
    return ((Identification[UNIVERSAL_ATA_ID_CSF_DEFAULT] & 0xC100) == 0x4100);
}

static inline int WhatAtaIdentificationFormFactor(uint16_t* Identification){
    uint16_t Result = Identification[168];
    if((AtaIdentificationGetMajorVersion(Identification) < 7) || (Result == 0) || (Result == 0xFFFF)){
        return 0;
    } 
    Result &= 0x0F;
    if(Result > 5){
        return 0;
    }
    return Result;
}

static inline int WhatAtaIdentificationRotationRate(uint16_t* Identification){
    uint16_t Result = Identification[217];
    if((AtaIdentificationGetMajorVersion(Identification) < 7) || (Result == 0) || (Result == 0xFFFF)){
        return 0;
    }
    if((Result > 1) && (Result < 0x401)){
        return 0;
    }
    return Result;
} 

static inline bool DoesAtaIdentificationHaveNcqSendAndRecive(uint16_t* Identification){
    return (Identification[UNIVERSAL_ATA_ID_SATA2_CAPABLE] & (1 << 6));
}

static inline bool DoesAtaIdentificationHaveNcqNonData(uint16_t* Identification){
    return (Identification[UNIVERSAL_ATA_ID_SATA2_CAPABLE] & (1 << 5));
}

static inline bool DoesAtaIdentificationHaveNcqPriority(uint16_t* Identification){
    return (Identification[UNIVERSAL_ATA_ID_SATA_CAPABLE] & (1 << 12));
}

static inline bool DoesAtaIdentificationHaveTrim(uint16_t* Identification){
    if((AtaIdentificationGetMajorVersion(Identification) >= 7) && (Identification[UNIVERSAL_ATA_ID_DATA_SET_MANAGEMENT] & 0x01)){
        return true;
    }
    return false;
}

static inline bool DoesAtaIdentificationHaveZeroAfterTrim(uint16_t* Identification){
    if((DoesAtaIdentificationHaveTrim(Identification)) && ((Identification[UNIVERSAL_ATA_ID_ADDITIONAL_SUPPORT] & 0x4020) == 0x4020)){
        return true;
    }
    return false;
}

static inline bool IsAtaIdentificationCurrentChecksumValid(uint16_t* Identification){
    return ((Identification[UNIVERSAL_ATA_ID_FIELD_VALID] & 0x01) && (Identification[UNIVERSAL_ATA_ID_CURRENT_CYCLES]) && (Identification[UNIVERSAL_ATA_ID_CURRENT_HEADS]) && (Identification[UNIVERSAL_ATA_ID_CURRENT_HEADS] <= 0x0F) && (Identification[UNIVERSAL_ATA_ID_CURRENT_SECTORS]));
}

static inline bool IsAtaIdentificationCfa(uint16_t* Identification){
    if((Identification[UNIVERSAL_ATA_ID_CONFIGURATION] == 0x848A) || (Identification[UNIVERSAL_ATA_ID_CONFIGURATION] == 0x844A)){
        return true;
    }
    return ((Identification[UNIVERSAL_ATA_ID_COMMAND_SET_2] & 0xC004) == 0x4004);
}

static inline bool IsAtaIdentificationSsd(uint16_t* Identification){
    return (Identification[UNIVERSAL_ATA_ID_ROTATION_SPEED] == 0x01);
}

static inline uint8_t IsAtaIdentificationZonedCap(uint16_t* Identification){
    return (Identification[UNIVERSAL_ATA_ID_ADDITIONAL_SUPPORT] & 0x03);
}

static inline bool DoesAtaIdentificationNeedIoReady(uint16_t* Identification, uint8_t Pio){
    if((Pio > 4) && (IsAtaIdentificationCfa(Identification))){
        return false;
    }
    if(Pio > 2){
        return true;
    }
    return DoesAtaIdentificationHaveIoReady(Identification);
}

static inline bool IsAtaDrive40Wire(uint16_t* DeviceIdentification){
    if(DoeAtaIdentificationHaveSata(DeviceIdentification)){
        return false;
    }
    if((DeviceIdentification[UNIVERSAL_ATA_ID_HARWARE_CONFIGURATION] & 0xE000) == 0x6000){
        return false;
    }
    return true;
}

static inline bool IsAtaDrive40WireReleaxed(uint16_t* DeviceIdentification){
    if((DeviceIdentification[UNIVERSAL_ATA_ID_HARWARE_CONFIGURATION] & 0x2000) == 0x2000){
        return false;
    }
    return true;
}

static inline int AtapiCommandDataBufferLength(uint16_t* DeviceIdentification){
    uint16_t Result = (DeviceIdentification[UNIVERSAL_ATA_ID_CONFIGURATION] & 0x03);
    switch(Result){
        case 0:     return 12;
        case 1:     return 10;
    }
    return -1;
}

static inline int AtapiCommandPacketSet(uint16_t* DeviceIdentification){
    return ((DeviceIdentification[UNIVERSAL_ATA_ID_CONFIGURATION] >> 8) & 0x1F);
}

static inline bool IdAtapiIdentificationGetDmaDirectory(uint16_t* DeviceIdentification){
    return ((AtaIdentificationGetMajorVersion(DeviceIdentification) >= 7) && (DeviceIdentification[62] & 0x8000));
}

static inline bool AtaStatusOk(uint8_t Status){
    return ((Status & (UNIVERSAL_ATA_BUSY | UNIVERSAL_ATA_DRDY | UNIVERSAL_ATA_DF | UNIVERSAL_ATA_DRQ | UNIVERSAL_ATA_ERROR)) == UNIVERSAL_ATA_DRDY);
}

static inline bool Lba28Ok(uint64_t Block, uint64_t BlockCount){
    return (((Block + BlockCount - 1) < ((uint64_t)1 << 28)) && (BlockCount <= UNIVERSAL_ATA_MAX_SECTORS));
}

static inline bool Lba48Ok(uint64_t Block, uint64_t BlockCount){
    return (((Block + BlockCount - 1) < ((uint64_t)1 << 48)) & (BlockCount <= UNIVERSAL_ATA_MAX_SECTORS_LBA_48));
}

#define SataPmpGscrVendorID(GSCR)   ((GSCR)[SATA_PMP_GSCR_PRODUCT_ID] & 0xFFFF)
#define SataPmpGscrDeviceID(GSCR)   ((GSCR)[SATA_PMP_GSCR_PRODUCT_ID] >> 16)
#define SataPmpGscrRevision(GSCR)   (((GSCR)[SATA_PMP_GSCR_REVISION] >> 8) & 0xFF)
#define SataPmpGscrPortData(GSCR)   ((GSCR)[SATA_PMP_GSCR_PORT_INFORMATION] & 0x0F)



#define ATA_PFLAG_IO_REQUEST_PENDING            1
#define ATA_PFLAG_IO_REQUEST_IN_PROGGRESS       1 << 1
#define ATA_PFLAG_PORT_FROZEN                   1 << 2
#define ATA_PFLAG_PORT_RECOVERED                1 << 3
#define ATA_PFLAG_PORT_LOADING                  1 << 4
#define ATA_PFLAG_SCSI_HOTPLUG                  1 << 6
#define ATA_PFLAG_INITIALIZING                  1 << 7
#define ATA_PFLAG_RESETTING                     1 << 8
#define ATA_PFLAG_UNLOADING                     1 << 8
#define ATA_PFLAG_UNLOADED                      1 << 10
#define ATA_PFLAG_RESUMING                      1 << 16
#define ATA_PFLAG_SUSPENDED                     1 << 17
#define ATA_PFLAG_PM_OPERATION_PENDING          1 << 18
#define ATA_PFLAG_INIT_GTM_VALID                1 << 19
#define ATA_PFLAG_PIO32                         1 << 20
#define ATA_PFLAG_PIO32_CHANGE                  1 << 21
#define ATA_PFLAG_EXTERNAL                      1 << 22

#define ATA_TAG_POISONED    0xFAFBFCFD

#define ATA_DEVICE_QUIRK_DIAGNOSTIC             1
#define ATA_DEVICE_QUIRK_NO_DMA                 1 << 1
#define ATA_DEVICE_QUIRK_NO_NCQ                 1 << 2
#define ATA_DEVICE_QUIRK_MAX_SECTORS_128        1 << 3
#define ATA_DEVICE_QUIRK_BROKEN_HPA             1 << 4
#define ATA_DEVICE_QUIRK_DISABLE_DEVICE         1 << 5
#define ATA_DEVICE_QUIRK_IVB                    1 << 6
#define ATA_DEVICE_QUIRK_STUCK_ERROR            1 << 7
#define ATA_DEVICE_QUIRK_BRIDGE_OK              1 << 8
#define ATA_DEVICE_QUIRK_ATAPI_MOD16_DMA        1 << 9
#define ATA_DEVICE_QUIRK_DUMP_IDENTIFY          1 << 10
#define ATA_DEVICE_QUIRK_MAX_SECTORS_LBA48      1 << 11
#define ATA_DEVICE_QUIRK_ATAPI_DMA_DIR          1 << 12
#define ATA_DEVICE_QUIRK_NO_NCQ_TRIMMING        1 << 12
#define ATA_DEVICE_QUIRK_NO_LPM                 1 << 14
#define ATA_DEVICE_QUIRK_WD_BROKEN_LPM          1 << 15
#define ATA_DEVICE_QUIRK_ZERO_AFTER_TRIM        1 << 16
#define ATA_DEVICE_QUIRK_NO_DMA_LOG             1 << 17
#define ATA_DEVICE_QUIRK_NO_TRIM                1 << 18
#define ATA_DEVICE_QUIRK_MAX_SECTORS_1024       1 << 19
#define ATA_DEVICE_QUIRK_MAX_TRIM_128MB         1 << 20
#define ATA_DEVICE_QUIRK_NCQ_ON_ATI             1 << 21
#define ATA_DEVICE_QUIRK_NO_ID_LOG              1 << 22
#define ATA_DEVICE_QUIRK_NO_LOG_DIR             1 << 23
#define ATA_DEVICE_QUIRK_NO_FUA                 1 << 24
#define ATA_DEVICE_QUIRK_MAX                    1 << 25

#define ATA_IRQ_1 14
#define ATA_IRQ_2 15

typedef struct _ATA_QUEUED_COMMAND{
    struct _LOUSINE_KERNEL_DEVICE_ATA_PORT* Port;
    bool     WriteCommand;
    bool     CommandCompleted;
    uint8_t  Device;
    uint32_t Auxillery;
    uint32_t Command;
    uint32_t Lbal;
    uint32_t Lbam;
    uint32_t Lbah;
    uint8_t  Feature;
    uint32_t HobLbal;
    uint32_t HobLbam;
    uint32_t HobLbah;
    uint8_t  HobFeature;
    uint32_t SectorCount;
    uint32_t HobSectorCount;
    uint8_t  Control;
    uint64_t DataAddress;
    uint64_t DataSize;
    bool     PacketCommand;
    uint8_t  ScsiCommandLength;
    //PioData
    uint16_t MaxByteSize;
    uint8_t  ScsiCommand[16];
    uint8_t  HardwareTag;
    uintptr_t PrdtLocation;
}ATA_QUEUED_COMMAND, * PATA_QUEUED_COMMAND;

typedef struct _LOUSINE_KERNEL_DEVICE_ATA_PORT{
    struct _LOUSINE_SCSI_HOST*              ScsiHost;
    struct _LOUSINE_ATA_PORT_OPERATIONS*    Operations;
    uint32_t                                PollTimer;
    spinlock_t                              PortLock;
    mutex_t                                 OperaionLock;
    uint64_t                                AtaFlags;
    unsigned int                            AtaPFlags;
    char                                    UserPortID;
    unsigned int                            PortNumber;
    void*                                   CommandIoAddress;
    void*                                   ControlIoAddress;
    void*                                   DmaIoAddress;
    void*                                   PrdtAddress;
    uint32_t                                PrdtBoundry;
    uint32_t                                SectorSize;
    PATA_QUEUED_COMMAND*                    CurrentQueuedCommand;
    struct _LOUSINE_KERNEL_DEVICE_ATA_HOST* AtaHost;
    P_PCI_DEVICE_OBJECT                     PDEV;
    void*                                   PortPrivateData;
    uint8_t                                 Siblings;
    bool                                    PortScsiDevice;
    bool                                    PortFunctioning;
    bool                                    SerialDevice;
    uint8_t                                 ScsiMaxCommandLength;
    bool                                    InNativeMode;
    bool                                    NativeSupported;
    bool                                    DeviceAttached;
    bool                                    DmaPort;
    uint8_t                                 SectorCountLimit;
    uint8_t                                 CommandLengthFlags;
}LOUSINE_KERNEL_DEVICE_ATA_PORT, * PLOUSINE_KERNEL_DEVICE_ATA_PORT;


typedef struct _LOUSINE_KERNEL_DEVICE_ATA_HOST{
    P_PCI_DEVICE_OBJECT                         PDEV;
    uint8_t                                     PortCount;
    spinlock_t                                  HostLock;
    void*                                       HostIoAddress;
    void*                                       HostPrivateData;
    uint64_t                                    PrivateDataSize;
    LOUSINE_KERNEL_DEVICE_ATA_PORT              Ports[];
}LOUSINE_KERNEL_DEVICE_ATA_HOST, * PLOUSINE_KERNEL_DEVICE_ATA_HOST;

typedef struct _LOUSINE_ATA_PORT_OPERATIONS{
    int         (*DelayQueuedCommand)       (PATA_QUEUED_COMMAND QueuedCommand);
    int         (*CheckAtapiDma)            (PATA_QUEUED_COMMAND QueuedCommand);
    LOUSTATUS   (*PrepCommand)              (PATA_QUEUED_COMMAND QueuedCommand);
    LOUSTATUS   (*IssueCommand)             (PATA_QUEUED_COMMAND QueuedCommand);
    void        (*CleanupCommand)           (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    LOUSTATUS   (*ResetPort)                (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    void        (*FillRtf)                  (PATA_QUEUED_COMMAND QueuedCommand);
    void        (*FillNcqRtf)               (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort, uint64_t DoneMask);                  
    LOUSTATUS   (*HardReset)                (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    LOUSTATUS   (*HostReset)                (PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);
    void        (*PortStart)                (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    void        (*PortStop)                 (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    void        (*PortSleep)                (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    void        (*PortWake)                 (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    void        (*PortPowerOff)             (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
    void        (*PortPowerOn)              (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);
}LOUSINE_ATA_PORT_OPERATIONS, * PLOUSINE_ATA_PORT_OPERATIONS;


#define COMMAND_LENGTH_FLAG_LBA48 1 



#define PRIMARY_COMMAND_REGISTER_OFFSET         0x10
#define PRIMARY_CONTROL_REGISTER_OFFSET         0x14
#define SECONDARY_COMMAND_REGISTER_OFFSET       0x18
#define SECONDARY_CONTROL_REGISTER_OFFSET       0x1C
#define ALTERNATE_STATUS_DEVICE_OFFSET          0x02
#define PRIMARY_CHANNEL_SUPPORTS_NATIVE         1 << 1
#define SECONDARY_CHANNEL_SUPPORTS_NATIVE       1 << 3
#define PRIMARY_CHANNEL_NATIVE_ENABLE           1
#define SECONDARY_CHANNEL_NATIVE_ENABLE         1 << 2

#define COMPATIBILITY_PRIMARY_CONTROL_BASE      (void*)0x3F6
#define COMPATIBILITY_SECONDARY_CONTROL_BASE    (void*)0x376

#define COMPATIBILITY_PRIMARY_COMMAND_BASE      (void*)0x1F0
#define COMPATIBILITY_SECONDARY_COMMAND_BASE    (void*)0x170

#define COMPATIBILITY_PRIMARY_IRQ               14
#define COMPATIBILITY_SECONDARY_IRQ             15

//Command Port Offsets
#define COMMAND_DATA_PORT_OFFSET                0 //RW : PIO Data Bytes 16 bit
#define COMMAND_ERROR_PORT_OFFSET               1 //R  : Used To Retrive Errors
#define COMMAND_FEATURE_PORT_OFFSET             1 //W  : Used To Controll Comand Specific Features
#define COMMAND_SECTOR_COUNT_PORT_OFFSET        2 //RW : Used to Controll Hosw Many Sectors Are Read
#define COMMAND_LBAL_PORT_OFFSET                3 //RW : Used to Select Sector To Read Or Write
#define COMMAND_LBAM_PORT_OFFSET                4 //RW
#define COMMAND_LBAH_PORT_OFFSET                5 //RW
#define COMMAND_DRIVE_HEAD_PORT_OFFSET          6 //RW
#define COMMAND_STATUS_PORT_OFFSET              7 //R
#define COMMAND_COMMAND_PORT_OFFSET             7 //W

//Command Port Manipulation
#define COMMAND_READ_DATA_PORT                      inw(CommandPort + COMMAND_DATA_PORT_OFFSET)
#define COMMAND_WRITE_DATA_PORT(x)                  outw(CommandPort + COMMAND_DATA_PORT_OFFSET, (x))
#define COMMAND_WRITE_DATA_PORT_BUFFER(x,y)         outsw(CommandPort + COMMAND_DATA_PORT_OFFSET, (x), (y))
#define COMMAND_READ_DATA_PORT_BUFFER(x,y)          insw(CommandPort + COMMAND_DATA_PORT_OFFSET, (x), (y))
#define COMMAND_READ_ERROR_PORT_LBA28               inb(CommandPort + COMMAND_ERROR_PORT_OFFSET)
#define COMMAND_READ_ERROR_PORT_LBA48               inw(CommandPort + COMMAND_ERROR_PORT_OFFSET)
#define COMMAND_WRITE_FEATURE_PORT_LBA28(x)         outb(CommandPort + COMMAND_FEATURE_PORT_OFFSET, (x))
#define COMMAND_WRITE_FEATURE_PORT_LBA48(x)         outw(CommandPort + COMMAND_FEATURE_PORT_OFFSET, (x))
#define COMMAND_READ_SECTOR_COUNT_PORT_LBA28        inb(CommandPort + COMMAND_SECTOR_COUNT_PORT_OFFSET)
#define COMMAND_READ_SECTOR_COUNT_PORT_LBA48        inw(CommandPort + COMMAND_SECTOR_COUNT_PORT_OFFSET)
#define COMMAND_WRITE_SECTOR_COUNT_PORT_LBA28(x)    outb(CommandPort + COMMAND_SECTOR_COUNT_PORT_OFFSET, (x))
#define COMMAND_WRITE_SECTOR_COUNT_PORT_LBA48(x)    outw(CommandPort + COMMAND_SECTOR_COUNT_PORT_OFFSET, (x))
#define COMMAND_READ_LBAL_PORT_LBA28                inb(CommandPort + COMMAND_LBAL_PORT_OFFSET)
#define COMMAND_READ_LBAL_PORT_LBA48                inw(CommandPort + COMMAND_LBAL_PORT_OFFSET)
#define COMMAND_WRITE_LBAL_PORT_LBA28(x)            outb(CommandPort + COMMAND_LBAL_PORT_OFFSET, (x))
#define COMMAND_WRITE_LBAL_PORT_LBA48(x)            outw(CommandPort + COMMAND_LBAL_PORT_OFFSET, (x))
#define COMMAND_READ_LBAM_PORT_LBA28                inb(CommandPort + COMMAND_LBAM_PORT_OFFSET)
#define COMMAND_READ_LBAM_PORT_LBA48                inw(CommandPort + COMMAND_LBAM_PORT_OFFSET)
#define COMMAND_WRITE_LBAM_PORT_LBA28(x)            outb(CommandPort + COMMAND_LBAM_PORT_OFFSET, (x))
#define COMMAND_WRITE_LBAM_PORT_LBA48(x)            outw(CommandPort + COMMAND_LBAM_PORT_OFFSET, (x))
#define COMMAND_READ_LBAH_PORT_LBA28                inb(CommandPort + COMMAND_LBAH_PORT_OFFSET)
#define COMMAND_READ_LBAH_PORT_LBA48                inw(CommandPort + COMMAND_LBAH_PORT_OFFSET)
#define COMMAND_WRITE_LBAH_PORT_LBA28(x)            outb(CommandPort + COMMAND_LBAH_PORT_OFFSET, (x))
#define COMMAND_WRITE_LBAH_PORT_LBA48(x)            outw(CommandPort + COMMAND_LBAH_PORT_OFFSET, (x))
#define COMMAND_READ_DRIVE_HEAD_PORT                inb(CommandPort + COMMAND_DRIVE_HEAD_PORT_OFFSET)
#define COMMAND_WRITE_DRIVE_HEAD_PORT(x)            outb(CommandPort + COMMAND_DRIVE_HEAD_PORT_OFFSET, (x))
#define COMMAND_READ_STATUS_PORT                     inb(CommandPort + COMMAND_STATUS_PORT_OFFSET)
#define COMMAND_WRITE_COMMAND_PORT(x)               outb(CommandPort + COMMAND_COMMAND_PORT_OFFSET, (x))

//Control Port data
#define CONTROL_ALTERNATE_STATUS_PORT_OFFSET    0 //R
#define CONTROL_DEVICE_CONTROL_PORT_OFFSET      0 //W
#define CONTROL_DRIVE_ADDRESS_PORT_OFFSET       1 //RW

//Control Operations 
#define CONTROL_READ_ALTERNATE_STATUS_PORT          inb(ControlPort + CONTROL_ALTERNATE_STATUS_PORT_OFFSET)
#define CONTROL_WRITE_DEVICE_CONTROL_PORT(x)        outb(ControlPort + CONTROL_DEVICE_CONTROL_PORT_OFFSET, (x))
#define CONTROL_READ_DRIVE_ADDRESS_PORT             inb(ControlPort + CONTROL_DRIVE_ADDRESS_PORT_OFFSET)

//Error Register Bits
#define ERROR_REGISTER_ADDRESS_MARK_NOT_FOUND   1
#define ERROR_REGISTER_TRACK_ZERO_NOT_FOUND     1 << 1
#define ERROR_REGISTER_ABORTED_COMMAND          1 << 2
#define ERROR_REGISTER_MEDIA_CHANGE_REQUEST     1 << 3
#define ERROR_REGISTER_ID_NOT_FOUND             1 << 4
#define ERROR_REGISTER_MEDIA_CHANGE             1 << 5
#define ERROR_REGISTER_UNCORECTABLE_DATA_ERROR  1 << 6
#define ERROR_REGISTER_BAD_BLOCK_DETECTED       1 << 7

//Drive Head Bits
#define DRIVE_HEAD_REGISTER_GET_CHS_ADDRESSING(x)   (x & 0xF)
#define DRIVE_HEAD_REGISTER_SET_CHS_ADDRESSING(x,y) (x | (y & 0xF))
#define DRIVE_HEAD_REGISTER_GET_DRIVE(x)            ((x >> 3) & 0x01)
#define DRIVE_HEAD_REGISTER_SET_DRIVE(x)            (x | (1 << 4))
#define DRIVE_HEAD_REGISTER_UNSET_DRIVE(x)          (x & ~(1 << 4))
#define DRIVE_HEAD_REGISTER_GET_LBA_BIT(x)          ((x >> 5) & 0x01)
#define DRIVE_HEAD_REGISTER_SET_LBA_BIT(x)          (x | (1 << 6))
#define DRIVE_HEAD_REGISTER_UNSET_LBA_BIT(x)        (x & ~(1 << 6))

#include "AtaDma.h"
#include "Ahci.h"

PLOUSINE_KERNEL_DEVICE_ATA_HOST
LouKeMallocAtaDevice(P_PCI_DEVICE_OBJECT PDEV, uint8_t PortCount);

void
LouKeMallocAtaPrivateData(
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost,
    uint64_t SizeofPrivateData,
    uint64_t AlignmentOfPrivateData
);

void LouKeForkAtaHostPrivateDataToPorts(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost);

#define ForEachAtaPort(AtaHost) for(uint8_t AtaPortIndex = 0; AtaPortIndex < (AtaHost)->PortCount; AtaPortIndex++)

void QueuedCommandToFis(PATA_QUEUED_COMMAND, uint8_t PortMultiplier, uint8_t IsCommand, uint8_t* Fis, uint8_t IsNcq);

#ifdef __cplusplus
}
#endif
#endif //_ATA_DEVICE_LIBRARY_H
