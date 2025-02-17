
#define _KERNEL_MODULE_
#include <LouDDK.h>

#define PIIX_IO_CFG_REG                     0x54
#define ICH5_ADDRESS_MAP_REG                0x90
#define ICH5_PORT_CONTROL_STATUS            0x92
#define PIIX_SID_PR_BAR                     5
#define PIIX_SID_PR_LENGTH                  16
#define PIIX_SID_PR_INDEX                   0
#define PIIX_SID_PR_DATA                    4
#define PIIX_FLAG_CHECK_INTERRUPT           (1 << 31)
#define PIIX_FLAG_SID_PR                    (1 << 30)
#define PIIX_PATA_FLAGS                     ATA_FLAG_SLAVE_POSS
#define PIIX_SATA_FLAGS                     ATA_FLAG_SATA | PIIX_FLAG_CHECK_INTERRUPT
#define PIIX_FLAG_PIO16                     (1 << 29)
#define PIIX_80C_PRIMARY                    ((1 << 5) | (1 << 4))
#define PIIX_80C_SECONDARY                  ((1 << 7) | (1 << 6))
#define PORT_0                              0
#define PORT_1                              1
#define PORT_2                              2
#define PORT_3                              3
#define IDE_STTRIBUTE                       -1
#define NO_ATTRIBUTE                        -2
#define RESERVED_ATTRIBUTE                  -3
#define PIIX_AHCI_SUPPORTED                 6
#define PIIX_HOST_HAS_BROKEN_SUSSPEND       true
#define PIIX_HOST_HAS_NO_BROKEN_SUSSPEND    false

#define PIIX_CONTROLLER_ID_PATA_MWDMA           0
#define PIIX_CONTROLLER_ID_PATA_33              1
#define ICH_CONTROLLER_ID_PATA_33               2
#define ICH_CONTROLLER_ID_PATA_66               3
#define ICH_CONTROLLER_ID_PATA_100              4
#define ICH_CONTROLLER_ID_PATA_100_NO_MWDMA     5
#define ICH5_CONTROLLER_ID_SATA                 6
#define ICH6_CONTROLLER_ID_SATA                 7
#define ICH6M_CONTROLLER_ID_SATA                8
#define ICH8_CONTROLLER_ID_SATA                 9
#define ICH8_2P_CONTROLLER_ID_SATA              10
#define ICH8M_APPLE_CONTROLLER_ID_SATA          11
#define TOLAPI_CONTROLLER_ID_SATA               12
#define PIIX_CONTROLLER_ID_VMWARE               13
#define ICH8_2P_CONTROLLER_ID_SATA_SNB          14
#define ICH8_2P_CONTROLLER_ID_SATA_BYT          15

typedef struct _PIIX_MAP_ENTRY{
    uint32_t Bits;
    uint16_t PortEnabled;
    int      PortMap[][4];
}PIIX_MAP_ENTRY, * PPIIX_MAP_ENTRY;

typedef struct _PIIX_HOST_PRIVATE_DATA{
    int*     PortMap;
    uint32_t SavedIoConfiguration;
    void*    SidPr;
}PIIX_HOST_PRIVATE_DATA, * PPIIX_HOST_PRIVATE_DATA;
