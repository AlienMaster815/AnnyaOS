#ifndef _ATA_CORE_H
#define _ATA_CORE_H

#include <cstdlib.h>

#define STANDARD_ATA_COMMAND_PACKET \
    union{ \
        UINT8   Features; \
        UINT8   Error; \
    }; \
    UINT8       SectorCount; \
    UINT8       LbaLow; \
    UINT8       LbaMid; \
    UINT8       LbaHigh; \
    UINT8       Device; \
    union{ \
        UINT8   Command; \
        UINT8   Status; \
    }

typedef struct PACKED _ATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE{
    STANDARD_ATA_COMMAND_PACKET;
}ATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE, * PATA_COMMAND_CFA_ERASE_SECTORS_STRUCTURE;

typedef struct PACKED _ATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE{
    STANDARD_ATA_COMMAND_PACKET;
}ATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE, * PATA_COMMAND_CFA_REQUEST_EXTENDED_ERROR_CODE_STRUCTURE;

#define ATA_COMMAND_CODE_NOP                                    0x00
#define ATA_COMMAND_CODE_CFA_REQUEST_EXTENDED_ERROR             0x03
#define ATA_COMMAND_CODE_DEVICE_RESET                           0x08
#define ATA_COMMAND_CODE_READ_SECTOR                            0x20
#define ATA_COMMAND_CODE_READ_SECOTRS_EX                        0x24
#define ATA_COMMAND_CODE_READ_DMA_EXT                           0x25
#define ATA_COMMAND_CODE_READ_DMA_QUEUED_EXT                    0x26
#define ATA_COMMAND_CODE_READ_NATIVE_MAX_ADDRESS_EXT            0x27
#define ATA_COMMAND_CODE_READ_MULTIPLE_EXT                      0x29
#define ATA_COMMAND_CODE_READ_STREAM_DMA                        0x2A
#define ATA_COMMAND_CODE_READ_STREAM_PIO                        0x2B
#define ATA_COMMAND_CODE_READ_LOG_EXT                           0x2F
#define ATA_COMMAND_CODE_WRITE_SECTOR                           0x30 
#define ATA_COMMAND_CODE_WRITE_SECTOR_EXT                       0x34
#define ATA_COMMAND_CODE_WRITE_DMA_EXT                          0x35
#define ATA_COMMAND_CODE_WRITE_DMA_QUEUED_EXT                   0x36
#define ATA_COMMAND_CODE_SET_MAX_ADDRESS_EXT                    0x37
#define ATA_COMMAND_CODE_CFA_WRITE_SECTORS_WOUT_ERASE           0x38
#define ATA_COMMAND_CODE_WRITE_MULTIPLE_EXT                     0x39
#define ATA_COMMAND_CODE_READ_VERIFY_SECTOR                     0x40
#define ATA_COMMAND_CODE_READ_VERIFY_SECTOR_EXT                 0x42
#define ATA_COMMAND_CODE_CONFIGURE_STREAM                       0x51
#define ATA_COMMAND_CODE_SEEK                                   0x70
#define ATA_COMMAND_CODE_CFA_TRANSLATE_SECTOR                   0x87
#define ATA_COMMAND_CODE_EXECUTE_DEVICE_DIAGNOSTICS             0x90
#define ATA_COMMAND_CODE_DOWNLOAD_MICROCODE                     0x92
#define ATA_COMMAND_CODE_PACKET                                 0xA0
#define ATA_COMMAND_CODE_IDENTIFY_PACKET_DEVICE                 0xA1
#define ATA_COMMAND_CODE_SERVICE                                0xA2
#define ATA_COMMAND_CODE_SMART_DISABLE_OPERATIONS               0xB0
#define ATA_COMMAND_CODE_SMART_TOGGLE_AUTOSAVE                  0xB0
#define ATA_COMMAND_CODE_SMART_ENABLE_OPERATIONS                0xB0
#define ATA_COMMAND_CODE_SMART_EXECUTE_OFF_LINE                 0xB0
#define ATA_COMMAND_CODE_SMART_READ_DATA                        0xB0
#define ATA_COMMAND_CODE_SMART_READ_LOG_SECTOR                  0xB0
#define ATA_COMMAND_CODE_SMART_RETURN_STATUS                    0xB0
#define ATA_COMMAND_CODE_SMART_WRITE_LOG_SECTOR                 0xB0
#define ATA_COMMAND_CODE_DEVICE_CONFIGURATION_FREEZE_LOCK       0xB1
#define ATA_COMMAND_CODE_DEVICE_CONFIGURATION_IDENTIFY          0xB1
#define ATA_COMMAND_CODE_DEVICE_CONFIGURATION_RESTORE           0xB1
#define ATA_COMMAND_CODE_DEVICE_CONFIGURATION_SET               0xB1
#define ATA_COMMAND_CODE_CFA_ERASE_SECTORS                      0xC0
#define ATA_COMMAND_CODE_READ_MULTIPLE                          0xC4
#define ATA_COMMAND_CODE_WRITE_MULTIPLE                         0xC5
#define ATA_COMMAND_CODE_SET_MULTIPLE_MODE                      0xC6
#define ATA_COMMAND_CODE_READ_DMA_QUEUED                        0xC7
#define ATA_COMMAND_CODE_READ_DMA                               0xC8
#define ATA_COMMAND_CODE_WRITE_DMA                              0xCA
#define ATA_COMMAND_CODE_WRITE_DMA_QUEUED                       0xCC
#define ATA_COMMAND_CODE_WRITE_MULTIPLE_WO_ERASE                0xCD
#define ATA_COMMAND_CODE_CHECK_MEDIA_CARD_TYPE                  0xD1
#define ATA_COMMAND_CODE_GET_MEDIA_STATUS                       0xDA
#define ATA_COMMAND_CODE_MEDIA_LOCK                             0xDE
#define ATA_COMMAND_CODE_MEDIA_UNLOCK                           0xDF
#define ATA_COMMAND_CODE_STANDBY_IMMEDIATE                      0xE0
#define ATA_COMMAND_CODE_IDLE_IMMEDIATE                         0xE1
#define ATA_COMMAND_CODE_STANDBY                                0xE2
#define ATA_COMMAND_CODE_IDLE                                   0xE3
#define ATA_COMMAND_CODE_READ_BUFFER                            0xE4
#define ATA_COMMAND_CODE_CHECK_POWER_MODE                       0xE5
#define ATA_COMMAND_CODE_SLEEP                                  0xE6
#define ATA_COMMAND_CODE_FLUSH_CACHE                            0xE7
#define ATA_COMMAND_CODE_WRITE_BUFFER                           0xE8
#define ATA_COMMAND_CODE_FLUSH_CACHE_EXT                        0xEA
#define ATA_COMMAND_CODE_IDENTIFY_DEVICE                        0xEC
#define ATA_COMMAND_CODE_MEDIA_EJECT                            0xED
#define ATA_COMMAND_CODE_SET_FEATURES                           0xEF
#define ATA_COMMAND_CODE_SECURITY_SET_PASWORD                   0xF1
#define ATA_COMMAND_CODE_SECURITY_UNLOCK                        0xF2
#define ATA_COMMAND_CODE_SECURITY_ERASE_PREPARE                 0xF3
#define ATA_COMMAND_CODE_SECURITY_ERASE_UNIT                    0xF4
#define ATA_COMMAND_CODE_SECURITY_FREEZE_LOCK                   0xF5
#define ATA_COMMAND_CODE_SECURITY_DISABLE_PASSWORD              0xF6
#define ATA_COMMAND_CODE_READ_NATIVE_MAX_ADDRESS                0xF8
#define ATA_COMMAND_CODE_SET_MAX_ADDRESS                        0xF9

typedef enum {
    ATA_DEVICE_COMMAND_STATUS_SUCCESS = 0,
    ATA_DEVICE_COMMAND_STATUS_PANIC,
    ATA_DEVICE_COMMAND_STATUS_RESET,
    ATA_DEVICE_COMMAND_STATUS_NEEDS_RESET,
    ATA_DEVICE_COMMAND_STATUS_ABORTED,
    ATA_DEVICE_COMMAND_STATUS_NOT_SUPPORTED,
    ATA_DEVICE_COMMAND_STATUS_MEDIA_ERROR,
    ATA_DEVICE_COMMAND_STATUS_USER_ACCESSABLE_ADDRESS_NOT_FOUND,

}ATA_DEVICE_COMMAND_STATUS;



#endif