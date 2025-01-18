#ifndef _ATA_DEVICE_LIBRARY_H
#define _ATA_DEVICE_LIBRARY_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

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
#define UNIVERSAL_ATA_ID_ADDITIONAL_SUPPLY      69
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
#define UNIVERSAL_ATA_ID_COMMAND_SET_5          120
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


#define ATA_CABLE_TYPE_NONE                     0
#define ATA_CABLE_TYPE_PATA40                   1
#define ATA_CABLE_TYPE_PATA80                   2
#define ATA_CABLE_TYPE_PATA40_SHORT             3
#define ATA_CABLE_TYPE_PATA40_UNKONW            4
#define ATA_CABLE_TYPE_PATA40_IGNORE_CABLE      5
#define ATA_CABLE_TYPE_PATA40_SATA              6

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



struct _ATA_QUEUED_COMMAND;

typedef struct _LOUSINE_KERNEL_DEVICE_ATA_PORT{
    struct _LOUSINE_SCSI_HOST*      ScsiHost;
    //PATA_PORT_OPERATION           Operations;
    spinlock_t                      PortLock;
    unsigned long                   AtaFlags;
    unsigned int                    AtaPFlags;
    unsigned int                    UserPortID;
    unsigned int                    PortNumber;
    //ATA_IO_PORT                   IoAddress;
    uint8_t                         ControlRegisterCahce;
    uint8_t                         LastWritenControlRegisterCache;
    //PATA_LINK                     SffPioTaskLink;
    DELAYED_FUNCTION                SffPioTask;
    //PATA_BMDMA_PRD                BmDmaPrd;
    uintptr_t                       DmaAddress;
    unsigned int                    PioBits;
    unsigned int                    MwDmaBits;
    unsigned int                    UDmaBits;
    unsigned int                    CableType;
    //PATA_QUEUED_COMMAND           QueuedCommand[ATA_MAX_QUEUE_COMMANDS + 1];
    uint64_t                        QueueCommandActive;
    int                             ActiveQcsLinks;
    //ATA_LINK                      HostDefaultLink;
    //PATA_LINK                     HostSlaveLink;
    int                             AvailablePmpLinks;
    //PATA_LINK                     PmpLink;
    //PATA_LINK                     PmpQcExclusionLink;
    //ATA_PORT_STATUS               PortStatus;
    //PATA_HOST                     AtaHost;
    P_PCI_DEVICE_OBJECT             PDEV;
    mutex_t                         ScsiScanMutex;
    DELAYED_FUNCTION                HotplugTask;
    DELAYED_FUNCTION                ScsiRescanTask;
    unsigned int                    HsmTaskState;
    ListHeader                      IoStackDoneQueue;
    LOUQ_WAIT                       IoStackWaitQueue;
    int                             IoStackTries;
    //LOUQ_COMPLETION               ParkRequestPending;
    //POWER_MANAGEMENT_MESSAGE      PowerMessgae
    uint32_t                        LpmPolicy;
    //TIMER_LIST                      FastdrainTimer;
    unsigned int                    FastdrainCount;
    //ASYNC_COOKIE                    AsyncCookie;
    int                             EclosuerManagementMessage;
    void*                           PrivateExtendedData;
    //ATA_ACPI_GTM                    AcpiInitializationGTM;
}LOUSINE_KERNEL_DEVICE_ATA_PORT, * PLOUSINE_KERNEL_DEVICE_ATA_PORT;

typedef struct _LOUSINE_ATA_PORT_OPERATIONS{
    int         (*DelayQueuedCommand)       (struct _ATA_QUEUED_COMMAND* QueuedCommand);
    int         (*CheckAtapiDma)            (struct _ATA_QUEUED_COMMAND* QueuedCommand);
    uint32_t    (*PrepCommand)              (struct _ATA_QUEUED_COMMAND* QueuedCommand);
    uint32_t    (*IssueCommand)             (struct _ATA_QUEUED_COMMAND* QueuedCommand);
    void        (*FillRtf)                  (struct _ATA_QUEUED_COMMAND* QueuedCommand);
    void        (*FillNcqRtf)               (PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort, uint64_t DoneMask);                  
}LOUSINE_ATA_PORT_OPERATIONS, * PLOUSINE_ATA_PORT_OPERATIONS;



int AtaBmdaPortStart(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);

#ifdef __cplusplus
}
#endif
#endif //_ATA_DEVICE_LIBRARY_H
