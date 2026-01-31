
#define _KERNEL_MODULE_
#include <LouDDK.h>
#include <Hal.h>
#include "AtaAPI.h"

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
#define IDE_ATTRIBUTE                       -1
#define NO_ATTRIBUTE                        -2
#define RESERVED_ATTRIBUTE                  -3
#define PIIX_AHCI_SUPPORTED                 6
#define PIIX_HOST_HAS_BROKEN_SUSSPEND       true
#define PIIX_HOST_HAS_NO_BROKEN_SUSSPEND    false

#define ICH5_CONTROLLER_ID_SATA                 0
#define ICH6_CONTROLLER_ID_SATA                 1
#define ICH6M_CONTROLLER_ID_SATA                2
#define ICH8_CONTROLLER_ID_SATA                 3
#define ICH8_2P_CONTROLLER_ID_SATA              4
#define ICH8M_APPLE_CONTROLLER_ID_SATA          5
#define TOLAPI_CONTROLLER_ID_SATA               6
#define ICH8_CONTROLLER_ID_SATA_SNB             7
#define ICH8_2P_CONTROLLER_ID_SATA_SNB          8
#define ICH8_2P_CONTROLLER_ID_SATA_BYT          9
#define PIIX_CONTROLLER_ID_PATA_MWDMA           10
#define PIIX_CONTROLLER_ID_PATA_33              11
#define ICH_CONTROLLER_ID_PATA_33               12
#define ICH_CONTROLLER_ID_PATA_66               13
#define ICH_CONTROLLER_ID_PATA_100              14
#define ICH_CONTROLLER_ID_PATA_100_NO_MWDMA     15
#define PIIX_CONTROLLER_ID_VMWARE               16

typedef struct _PIIX3_HOST_PRIVATE_DATA{
    PPCI_DEVICE_OBJECT      PDEV;
    UINT32                  Bmiba;
    UINT8                   MaxPioMode;
    UINT8                   MaxUDmaMode;
    UINT8                   CurrentPioMode;
}PIIX3_HOST_PRIVATE_DATA, * PPIIX3_HOST_PRIVATE_DATA;

//Piix 3 Specification

#define BMBIA_BAR                           4       //BUS MASTER INTERFACE BAR IO PORT
#define PRIMARY_IDETIM_REGISTER_OFFSET      0x40    //PRIMARY IDE TIMING REGISTER U16
#define SECONDARY_IDETIM_REGISTER_OFFSET    0x42    //SECONDARY IDE TIMING REGISTER U16

#define IDETIM_IDE_SHIFT                    15
#define IDETIM_IDE_MASK                     1
#define IDETIM_IDE                          (IDETIM_IDE_MASK << IDETIM_IDE_SHIFT)
#define IDETIM_SITRE_SHIFT                  14
#define IDETIM_SITRE_MASK                   1
#define IDETIM_SITRE                        (IDETIM_SITRE_MASK << IDETIM_SITRE_SHIFT)
#define IDETIM_ISP_SHIFT                    12
#define IDETIM_ISP_MASK                     0x03
#define IDETIM_ISP                          (IDETIM_ISP_MASK << IDETIM_ISP_SHIFT)
#define     IDETIM_ISP_5CLOCKS              0b00
#define     IDETIM_ISP_4CLOCKS              0b01
#define     IDETIM_ISP_3CLOCKS              0b10
#define     IDETIM_ISP_2CLOCKS              0b11
#define IDETIM_RTC_SHIFT                    8
#define IDETIM_RTC_MASK                     0x03
#define IDETIM_RTC                          (IDETIM_RTC_MASK << IDETIM_RTC_SHIFT)
#define     IDETIM_RTC_4CLOCK               0b00
#define     IDETIM_RTC_3CLOCK               0b01
#define     IDETIM_RTC_2CLOCK               0b10
#define     IDETIM_RTC_1CLOCK               0b11
#define IDETIM_DTE1_SHIFT                   7
#define IDETIM_DTE1_MASK                    1
#define IDETIM_DTE1                         (IDETIM_DTE1_MASK << IDETIM_DTE1_SHIFT)
#define IDETIM_PPE1_SHIFT                   6
#define IDETIM_PPE1_MASK                    1
#define IDETIM_PPE1                         (IDETIM_PPE1_MASK << IDETIM_PPE1_SHIFT)
#define IDETIM_IE1_SHIFT                    5
#define IDETIM_IE1_MASK                     1
#define IDETIM_IE1                          (IDETIM_IE1_MASK << IDETIM_IE1_SHIFT)
#define IDETIM_TIME1_SHIFT                  4
#define IDETIM_TIME1_MASK                   1
#define IDETIM_TIME1                        (IDETIM_TIME1_MASK << IDETIM_TIME1_SHIFT)
#define IDETIM_DTE0_SHIFT                   3
#define IDETIM_DTE0_MASK                    1
#define IDETIM_DTE0                         (IDETIM_DTE0_MASK << IDETIM_DTE0_SHIFT)
#define IDETIM_PPE0_SHIFT                   2
#define IDETIM_PPE0_MASK                    1
#define IDETIM_PPE0                         (IDETIM_PPE0_MASK << IDETIM_PPE0_SHIFT)
#define IDETIM_IE0_SHIFT                    1
#define IDETIM_IE0_MASK                     1
#define IDETIM_IE0                          (IDETIM_IE0_MASK << IDETIM_IE0_SHIFT)
#define IDETIM_TIME0_SHIFT                  0
#define IDETIM_TIME0_MASK                   1
#define IDETIM_TIME0                        (IDETIM_TIME0_MASK << IDETIM_TIME0_SHIFT)

#define SIDETIM_REGISTER_OFFSET             0x44 //U8
#define SIDTIM_SISP1_SHIFT                  6
#define SIDTIM_SISP1_MASK                   0x03
#define SIDTIM_SISP1                        (SIDTIM_SISP1_MASK << SIDTIM_SISP1_SHIFT)
#define     SIDTIM_SISP1_5CLOCKS            0b00
#define     SIDTIM_SISP1_4CLOCKS            0b01
#define     SIDTIM_SISP1_3CLOCKS            0b10
#define     SIDTIM_SISP1_2CLOCKS            0b11
#define SIDTIM_SRTC1_SHIFT                  4
#define SIDTIM_SRTC1_MASK                   0x03
#define SIDTIM_SRTC1                        (SIDTIM_SRTC1_MASK << SIDTIM_SRTC1_SHIFT)
#define     SIDTIM_SRTC1_4CLOCKS            0b00
#define     SIDTIM_SRTC1_3CLOCKS            0b01
#define     SIDTIM_SRTC1_2CLOCKS            0b10
#define     SIDTIM_SRTC1_1CLOCKS            0b11
#define SIDTIM_PISP1_SHIFT                  2
#define SIDTIM_PISP1_MASK                   0x03
#define SIDTIM_PISP1                        (SIDTIM_PISP1_MASK << SIDTIM_PISP1_SHIFT)
#define     SIDTIM_PISP1_5CLOCKS            0b00
#define     SIDTIM_PISP1_4CLOCKS            0b01
#define     SIDTIM_PISP1_3CLOCKS            0b10
#define     SIDTIM_PISP1_2CLOCKS            0b11
#define SIDTIM_PRTC1_SHIFT                  0
#define SIDTIM_PRTC1_MASK                   0x03
#define SIDTIM_PRTC1                        (SIDTIM_PRTC1_MASK << SIDTIM_PRTC1_SHIFT)
#define     SIDTIM_PRTC1_4CLOCKS            0b00
#define     SIDTIM_PRTC1_3CLOCKS            0b01
#define     SIDTIM_PRTC1_2CLOCKS            0b10
#define     SIDTIM_PRTC1_1CLOCKS            0b11

#define PRIMARY_BMICOM_REGISTER_OFFSET      0x00
#define PRIMARY_BMICOM_REGISTER(x)          (((PPIIX3_HOST_PRIVATE_DATA)x)->Bmiba + PRIMARY_BMICOM_REGISTER_OFFSET)
#define SECONDARY_BMICOM_REGISTER_OFFSET    0x08
#define SECONDARY_BMICOM_REGISTER(x)        (((PPIIX3_HOST_PRIVATE_DATA)x)->Bmiba + SECONDARY_BMICOM_REGISTER_OFFSET)
#define BMICOM_RWCON_SHIFT                  3
#define BMICOM_RWCON_MASK                   1
#define BMICOM_RWCON                        (BMICOM_RWCON_MASK << BMICOM_RWCON_SHIFT)
#define BMICOM_SSBM_SHIFT                   0
#define BMICOM_SSBM_MASK                    1
#define BMICOM_SSBM                         (BMICOM_SSBM_MASK << BMICOM_SSBM_SHIFT)

#define PRIMARY_BMISTA_REGISTER_OFFSET      0x02
#define PRIMARY_BMISTA_REGISTER(x)          (((PPIIX3_HOST_PRIVATE_DATA)x)->Bmiba + PRIMARY_BMISTA_REGISTER_OFFSET)
#define SECONDARY_BMISTA_REGISTER_OFFSET    0x0A
#define SECONDARY_BMISTA_REGISTER(x)        (((PPIIX3_HOST_PRIVATE_DATA)x)->Bmiba + SECONDARY_BMISTA_REGISTER_OFFSET)
#define BMISTA_DMA1CAP_SHIFT                6
#define BMISTA_DMA1CAP_MASK                 1
#define BMISTA_DMA1CAP                      (BMISTA_DMA1CAP_MASK << BMISTA_DMA1CAP_SHIFT)
#define BMISTA_DMA0CAP_SHIFT                5
#define BMISTA_DMA0CAP_MASK                 1
#define BMISTA_DMA0CAP                      (BMISTA_DMA0CAP_MASK << BMISTA_DMA0CAP_SHIFT)
#define BMISTA_IDEINTR_SHIFT                2
#define BMISTA_IDEINTR_MASK                 1
#define BMISTA_IDEINTR                      (BMISTA_IDEINTR_MASK << BMISTA_IDEINTR_SHIFT)
#define BMISTA_DMAERR_SHIFT                 1
#define BMISTA_DMAERR_MASK                  1
#define BMISTA_DMAERR                       (BMISTA_DMAERR_MASK << BMISTA_DMAERR_SHIFT)
#define BMISTA_BMIDEA_SHIFT                 0
#define BMISTA_BMIDEA_MASK                  1
#define BMISTA_BMIDEA                       (BMISTA_BMIDEA_MASK << BMISTA_BMIDEA_SHIFT)
#define     BMISTA_INTACT_DMA_IN_PROGRESS   0b0001
#define     BMISTA_INTACT_PRD_EXHAUSTED     0b0100
#define     BMISTA_INTACT_VALID_COMPLETION  0b0101
#define     BMISTA_INTACT_DMA_ERROR         0b0000
#define PRIMARY_BMIDTP_REGISTER_OFFSET      0x04
#define PRIMARY_BMIDTP_REGISTER(x)          (((PPIIX3_HOST_PRIVATE_DATA)x)->Bmiba + PRIMARY_BMIDTP_REGISTER_OFFSET)
#define SECONDARY_BMIDTP_REGISTER_OFFSET    0x0C
#define SECONDARY_BMIDTP_REGISTER(x)        (((PPIIX3_HOST_PRIVATE_DATA)x)->Bmiba + SECONDARY_BMIDTP_REGISTER_OFFSET)
#define BMIDTP_MASK                         0xFFFFFFFC



//Endof Piix 3 Specification