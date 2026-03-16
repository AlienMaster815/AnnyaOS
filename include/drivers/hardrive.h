#ifndef _GLOBAL_HARDRIVE_H
#define _GLOBAL_HARDRIVE_H

#ifdef __cplusplus
extern "C" {
#endif

#define AHCI_BAR_OFFSET       0x10  // Offset of AHCI controller's BAR in PCI configuration space
#define AHCI_REG_CAP          0x00  // Offset of AHCI capabilities register
#define AHCI_REG_GHC          0x04  // Offset of AHCI global host control register
#define AHCI_CAP_SSS          (1U << 27) // Staggered Spin-Up Supported bit in AHCI capabilities register
#define AHCI_GHC_AE           (1U << 31) // AHCI Enable bit in AHCI global host control register

//PCI Header Ofsets
#define DEVICE_ID_OFFSET 0x0
#define VENDOR_ID_OFFSET 0x2
#define CMD_OFFSET 0x4
#define STS_OFFSET 0x6
#define RID_OFFSET 0x8
#define CC_OFFSET 0x9
#define CLS_OFFSET 0xC
#define MLT_OFFSET 0xD
#define HTYPE_OFFSET 0xE
#define BIST_OFFSET 0xF
#define BAR0_OFFSET 0x10
#define BAR1_OFFSET 0x14
#define BAR2_OFFSET 0x18
#define BAR3_OFFSET 0x1B
#define BAR4_OFFSET 0x20
#define BAR5_OFFSET 0x24
#define SS_DEV_ID_OFFSET 0x2C
#define SS_VEN_ID_OFFSET 0x2E
#define EROM_OFFSET 0x30
#define CAP_OFFSET 0x34
#define INTERRUPT_PIN_OFFSET 0x3C
#define INTERRUPT_LINE_OFFSET 0x3D
#define MGNT_OFFSET 0x3E
#define MLANT_OFFSET 0x3F


//HBA Generic Offset Information
#define HBA_CAP_OFFSET 0x0
#define HBA_GHC_OFFSET 0x4
#define HBA_IS_OFFSET 0x8
#define HBA_PI_OFFSET 0xC
#define HBA_VS_OFFSET 0x10
#define HBA_CCC_CTL_OFFSET 0x14
#define HBA_CCC_PORTS_OFFSET 0x18
#define HBA_EM_LOC_OFFSET 0x1C
#define HBA_EM_CTL_OFFSET 0x20
#define HBA_CAP2_OFFSET 0x24
#define HBA_BOHC_OFFSET 0x28
//End Of Generic

//Start Of Intel HBA Information
#define INTEL_RESERVED_OFFSET 0x2C
#define INTEL_RESERVED_NVMHCI_OFFSET 0x60
#define INTEL_SPECIFIC_REGISTERS_OFFSET 0xA0
#define INTEL_PORT0_CONTROL_REGISTERS_OFFSET 0x100
#define INTEL_PORT1_CONTROL_REGISTERS_OFFSET 0x180
#define INTEL_PORT2_TO_29_CONTROL_REGISTERS_OFFSET 0x200
#define INTEL_PORT30_CONTROL_REGISTERS_OFFSET 0x1000
#define INTEL_PORT31_CONTROL_REGISTERS_OFFSET 0x1080
//End Of Intel Information
#define _1_3_1_INTEL 1



#ifdef __cplusplus
}
#endif
#endif