#ifndef _ACPI_DEFINITIONS_H
#define _ACPI_DEFINITIONS_H

//all definitions for the ACPI 6.5 Decemeber 2024 
//specification release 

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

#define GAS_SYSTEM_MEMORY_SPACE                     0x00
#define GAS_SYSTEM_IO_SPACE                         0x01
#define GAS_PCI_CONFIG                              0x02
#define GAS_EMBEDDED_CONTROLLER                     0x03
#define GAS_SM_BUS                                  0x04
#define GAS_SYSTEM_CMOS                             0x05
#define GAS_PCI_BAR_TARGET                          0x06
#define GAS_IPMI                                    0x07
#define GAS_GENERAL_PURPOSE_IO                      0x08
#define GAS_GENERIC_SERIAL_BUS                      0x09
#define GAS_PLATFORM_COMMUNICATIONS_CHANNEL         0x0A //PCC
#define GAS_PLATFORM_RUNTIME_MECHANISM              0x0B //PRM
#define GAS_FUNCTIONAL_FIXED_HARDWARE               0x7F

#define GAS_ACCESS_SIZE_UNDEFINED                   0x00
#define GAS_ACCESS_SIZE_BYTE_ACCESS                 0x01
#define GAS_ACCESS_SIZE_WORD_ACCESS                 0x02
#define GAS_ACCESS_SIZE_DWORD_ACCESS                0x03
#define GAS_ACCESS_SIZE_QWORD_ACCESS                0x04

#define UNSPECIFIED_PREFERED_POWER_MODE             0
#define DESKTOP_PREFERED_POWER_MODE                 1
#define MOBILE_PREFERED_POWER_MODE                  2
#define WORKSTATION_PREFERED_POWER_MODE             3
#define ENTERPRISE_PREFERED_POWER_MODE              4
#define SOHO_SERVER_PREFERED_POWER_MODE             5
#define APPLIANCE_PC_PREFERED_POWER_MODE            6
#define PERFORMANCE_SERVER_PREFERED_POWER_MODE      7
#define TABLET_PREFERED_POWER_MODE                  8                  


#define MULTIPLE_APIC_DESCRIPTION                   "APIC"
#define BOOT_ERROR_RECORD                           "BERT"
#define BOOT_GRAPHICS_RESOURCE                      "BGRT"
#define CONFIDENTIAL_COMPUTING_VENT_LOG             "CCEL"
#define CORRECTED_PLATFORM_ERROR_POLLING            "CPEP"
#define DIFFERENTIATED_SYSTEM_DESCRIPTION           "DSDT"
#define EMBEDDED_CONTROLLER_ROOT_RESCOURCE          "ECDT"
#define ERROR_INJECTION                             "EINJ"
#define ERROR_RECORD_SERIALIZATIONS                 "ERST"
#define FIXED_ACPI_DESCRIPTION                      "FACP"
#define FIRMWARE_ACPI_CONTROL_STRUCTURE             "FACS"
#define FIRMWARE_PERFORMACE_DATA                    "FPDT"
#define GENERIC_TIMER_DESCRIPTION                   "GTDT"
#define HARDWARE_ERROR_SOURCE                       "HEST"
#define MISC_GUID_ENTRIES                           "MISC"
#define MAXIMUM_SYSTEM_CHARECTERISTICS              "MSCT"
#define MEMORY_POWER_STATE                          "MPST"
#define NVDIMM_FIRMWARE_INTERFACE                   "NFIT"
#define OEM_DYNAMIC                                 "OEM"
#define PLATFORM_COMMUNICATIONS_CHANNEL             "PCCT"
#define PLATFORM_HEALTH_ASSESMENT                   "PHAT"
#define PLATFORM_MEMORY_TOPOLOGY                    "PMTT"
#define PROCESSOR_PROPERTIES_TOPOLOGY               "PPTT"
#define PERSISTANT_SYSTEM_DESCRIPTION               "PSDT"
#define ACPI_RAS_FEATURE                            "RASF"
#define ACPI_RAS2_FEATURE                           "RAS2"
#define ROOT_SYSTEM_DISCRIPTION                     "DSDT"
#define SMART_BATTER_PECIFICATION                   "SBST"
#define SECURE_DEVICES                              "SDEV"
#define SYSTEM_LOCALITY_DISTANCE_INFORMATION        "SLIT"
#define SYSTEM_RESOURCE_AFFINITY                    "SRAT"
#define SECONDARY_SYSTEM_DESCRIPTION                "SSDT"
#define STORAGE_VOLUME_KEY                          "SVKL"
#define EXTENDED_SYSTEM_DESCRIPTION                 "XSDT"

#define ARM_ERROR_SOURCE                            "AEST"
#define ARM_GENERIC_DIAGNOSTIC_DUMP_AND_RESET       "AGDI"
#define ARM_PERFORMANCE_MONITORING_UNIT             "APMT"
#define BIOS_ACPI_DATA                              "BDAT"
#define CXL_EARLY_DISCOVERY                         "CEDT"
#define BOOT_RESERVED                               "BOOT"
#define CORE_SYSTEM_RESOURCE                        "CSRT"
#define DEBUG_PORT                                  "BDGP"
#define DEBUG_PORT_2                                "BDG2"
#define DMA_REMAPPING                               "DMAR"
#define DYNAMIC_ROOT_TRUST_MESURMENT                "DRTM"
#define INTEL_TRUSTED_EXECUTION_TECHNOLOGY          "DTPR"
#define EVENT_TIMER_DESCRIPTION                     "ETDT"
#define HIGH_PERCISION_EVENT_TIMER                  "HPET"
#define ISCSI_BOOT_FIRMWARE                         "IBFT"
#define INLINE_ENCRYPTION_REPORTING_STRUCTURE       "IERS"
#define IO_REMAPPING                                "IORT"
#define IO_VIRTUALIZATION_REPORTING_STRUCTURE       "IVRS"
#define KEY_ROOT_COMPLEX_PROGRAMMING_INTERFACE      "KEYP"
#define LOW_POWER_IDLE                              "LPIT"
#define PCI_EXSPRESS_MEMORY_MAPPED_CONFIGURATION    "MCFG"
#define MANAGEMENT_CONTROLLER_HOST_INTERFACE        "MCHI"
#define MICROSOFT_PLUTON_SECURITY_PROCESSOR         "MHSP"
#define ARM_MEMORY_PARTITIONING_AND_MONITORING      "MPAM"
#define MICROSOFT_DATA_MANAGEMENT                   "MSDM"
#define NVME_OVER_FABRIC_BOOT_FIRMWARE              "NBFT"
#define PLATFOMR_RUNTIME_MECHANISM                  "PRMT"
#define REGULATORY_GRAPHICS_RESOURCE                "RGRT"
#define SOFTWARE_DELGATED_EXCEPTIONS_INTERFACE      "SDEI"
#define MICROSOFT_SOFTWARE_LICENCE                  "SLIC"
#define MICROSOFT_SERIAL_PORT_CONSOLE_REDIRECTION   "SPCR"
#define SERVER_PLATFORM_MANAGEMENT_INTERFACE        "SPMI"
#define STA_OVERRIDE                                "STAO"
#define SOUND_WIRE_FILE_TABLE                       "SWFT"
#define TRUSTED_COMPUTING_PLATFORM_ALLIANCE         "TCPA"
#define TRUSTED_PLATFORM_MODULE2                    "TMP2"
#define UNIFIED_EXTENSIBLE_FIRMWARE_INTERFACE       "UEFI"
#define WINDOWS_ACPI_EUMALATED_DEVICES              "WAET"
#define WATCHDOG_DESCRIPTOR                         "WDDT"
#define WATCHDOG_RESOURCE                           "WDRT"
#define WINDOWS_PLATFORM_BINARY                     "WPBT"
#define WINDOWS_SECURITY_MITIGATIONS                "WSMT"
#define XEN_PROJECT                                 "XENV"

#define FOR_EACH_PRSDT_ENTRY(DSDT) for(size_t RsdtEntry = 0 ; RsdtEntry < ((RSDT->RsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER)) / 4); RsdtEntry++)
#define FOR_EACH_RSDT_ENTRY(DSDT) for(size_t RsdtEntry = 0 ; RsdtEntry < ((RSDT.RsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER)) / 4); RsdtEntry++)

#define FOR_EACH_PXSDT_ENTRY(XSDT) for(size_t XsdtEntry = 0 ; XsdtEntry < ((XSDT->XsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER)) / 8); XsdtEntry++)
#define FOR_EACH_XSDT_ENTRY(XSDT) for(size_t XsdtEntry = 0 ; XsdtEntry < ((XSDT.XsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER)) / 8); XsdtEntry++)

#define FADT_FEATURE_FLAG_WBINVD                                    (1 << 0)
#define FADT_FEATURE_FLAG_WBINVD_FLUSH                              (1 << 1)
#define FADT_FEATURE_FLAG_PROC_C1                                   (1 << 2)
#define FADT_FEATURE_FLAG_PLVL2_UP                                  (1 << 3)
#define FADT_FEATURE_FLAG_POWER_BUTTON                              (1 << 4)
#define FADT_FEATURE_FLAG_SLEEP_BUTTON                              (1 << 5)
#define FADT_FEATURE_FLAG_FIX_RTC                                   (1 << 6)
#define FADT_FEATURE_FLAG_RTC_S4                                    (1 << 7)
#define FADT_FEATURE_FLAG_TIMER_CALUE_EXT                           (1 << 8)
#define FADT_FEATURE_FLAG_DCK_CAP                                   (1 << 9)
#define FADT_FEATURE_FLAG_RESET_REG_SUP                             (1 << 10)
#define FADT_FEATURE_FLAG_SEALED_CASE                               (1 << 11)
#define FADT_FEATURE_FLAG_HEADLESS                                  (1 << 12)
#define FADT_FEATURE_FLAG_CPU_SW_SLP                                (1 << 13)
#define FADT_FEATURE_FLAG_PCI_EXP_WAK                               (1 << 14)
#define FADT_FEATURE_FLAG_USE_PLATFORM_CLOCK                        (1 << 15)
#define FADT_FEATURE_FLAG_S4_RTC_STS_VALID                          (1 << 16)
#define FADT_FEATURE_FLAG_REMOTE_POWER_ON_CPABLE                    (1 << 17)
#define FADT_FEATURE_FLAG_FORCE_APIC_CLUSTER                        (1 << 18)
#define FADT_FEATURE_FLAG_FORCE_APIC_PHYSICAL_DESTINATION_MODE      (1 << 19)
#define FADT_FEATURE_FLAG_HW_REDUCED_ACPI                           (1 << 20)
#define FADT_FEATURE_FLAG_LOW_POWER_S0_IDLE_CAPABLE                 (1 << 21)
#define FADT_FEATURE_FLAG_PERSISTANT_CPU_CACHES                     (3 << 22)

#define IAPC_BOOT_ARCH_FLAGS_LEGACY_DEVICES         (1 << 0)
#define IAPC_BOOT_ARCH_FLAGS_8042_KEYBOARD          (1 << 1)
#define IAPC_BOOT_ARCH_FLAGS_VGA_NOT_PRESENT        (1 << 2)
#define IAPC_BOOT_ARCH_FLAGS_MSI_NOT_SUPPORTED      (1 << 3)
#define IAPC_BOOT_ARCH_FLAGS_PCIE_ASPM_CONTROLS     (1 << 4)
#define IAPC_BOOT_ARCH_FLAGS_CMOS_RTC_NOT_PRESENT   (1 << 5)

#define FACS_FEATURE_FLAG_S4_BIOS_F                 (1 << 0)
#define FACS_FEATURE_FLAG_64BIT_WAKE_SUPPORTED_F    (1 << 1)

#define FACS_OSPM_FLAG_64BIT_WAKE_F                 (1 << 0)

#define FACS_GLOBAL_LOCK_PENDING                    (1 << 0)
#define FACS_GLOBAL_LOCK_OWNED                      (1 << 1)

#define PDSDT_AML_BYTE_COUNT(PDsdt) (PDsdt->DsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER))
#define DSDT_AML_BYTE_COUNT(Dsdt) (Dsdt.DsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER))

#define PSSDT_AML_BYTE_COUNT(PSsdt) (PSsdt->SsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER))
#define SSDT_AML_BYTE_COUNT(Ssdt) (Ssdt.SsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER))

#define MULTIPLE_APIC_FLAGS_PCAT_COMPAT             (1 << 0)

#define MADT_ICS_PROCESSOR_LOCAL_APIC                                   0x00
#define MADT_ICS_IO_APIC                                                0x01
#define MADT_ICS_INTERRUPT_SOURCE_OVERIDE                               0x02
#define MADT_ICS_NON_MASKABLE_OVERIDE                                   0x03
#define MADT_ICS_LOCAL_APIC_NMI                                         0x04
#define MADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE                             0x05
#define MADT_ICS_IO_SAPIC                                               0x06
#define MADT_ICS_LOCAL_SAPIC                                            0x07
#define MADT_ICS_PLATFORM_INTERRUPT_SOURCE                              0x08
#define MADT_ICS_PROCESSOR_LOCAL_X2APIC                                 0x09
#define MADT_ICS_LOCAL_X2APIC                                           0x0A
#define MADT_ICS_GIC_CPU_INTERFACE                                      0x0B
#define MADT_ICS_GIC_DISTRIBUTER                                        0x0C
#define MADT_ICS_GIC_MSI_FRAME                                          0x0D
#define MADT_ICS_GIC_GIC_REDISTIBUTER                                   0x0E
#define MADT_ICS_GIC_INTERRUPT_TRANSLATION_SERVICE                      0x0F
#define MADT_ICS_MULTIPROCESSOR_WAKEUP                                  0x10
#define MADT_ICS_CORE_PROGRAMABLE_INTERRUPT_CONTROLLER                  0x11
#define MADT_ICS_LEGACY_PROGRAMMABLE_INTERRUPT_CONTROLLER               0x12
#define MADT_ICS_HYPER_TRANSPORT_PROGRAMMABLE_INTERUPT_CONTROLLER       0x13
#define MADT_ICS_EXTENDED_IO_PROGRAMABLE_INTERRUPT_CONTROLLER           0x14
#define MADT_ICS_MSI_PROGRAMMABLE_INTERRUPT_CONTROLLER                  0x15
#define MADT_ICS_BRIDGE_IO_PROGRAMMABLE_INTERRUPT_CONTROLLER            0x16
#define MADT_ICS_LOW_PIN_COUNT_PROGRAMMABLE_INTERRUPT_CONTROLLER        0x17

#define MADT_ICS_LOCAL_APIC_FLAG_ENABLED            (1 << 0)
#define MADT_ICS_LOCAL_APIC_FLAG_ONLINE_CAPABLE     (1 << 1)

#define MADT_ICS_ISO_MPS_INTI_FLAG_POLARITY         (2 << 0)
#define MADT_ICS_ISO_MPS_INTI_FLAG_TRIGGER_MODE     (2 << 2)

#define MADT_ICS_PIS_FLAG_CPEI_PROC_OVERIDE         (1 << 0)

#define MADT_ICS_CORE_PCI_FLAG_ENABLED              (1 << 0)

#define MADT_ICS_HT_PIC_VERSION_INVALID             0
#define MADT_ICS_HT_PIC_VERSION_V1                  1

#define MADT_ICS_EIO_PIC_VERSION_INVLAID            0
#define MADT_ICS_EIO_PIC_VERSION_V1                 1

#define MADT_ICS_MSI_PIC_VERSION_INVALID            0
#define MADT_ICS_MSI_PIC_VERSION_V1                 1

#define MADT_ICS_BIO_PIC_VERSION_INVALID            0
#define MADT_ICS_BIO_PIC_VERSION_V1                 1

#define MADT_ICS_LPC_PIC_VERSION_INVLAID            0
#define MADT_ICS_LPC_PIC_VERSION_V1                 1

#define SRAT_LOCAL_APIC_AFFINITY_TYPE               0
#define SRAT_MEMORY_AFFINITY_TYPE                   1
#define SRAT_PROCESSOR_LOCAL_X2_APIC_AFFINITY_TYPE  2
#define SRAT_PROCESSOR_GICC_AFFINITY_TYPE           3
#define SRAT_GIC_ITS_AFFINITY_TYPE                  4
#define SRAT_GENERIC_INITIATOR_TYPE                 5
#define SRAT_GENERIC_PORT_TYPE                      6

#define PSRAT_LOCAL_APIC_AFFINITY_READ_PROXIMITY_DOMAIN(LAA)     (LAA->ProximityDomainLow | (LAA->ProximityDomainHigh[0] << 8) | (LAA->ProximityDomainHigh[1] << 16) | (LAA->ProximityDomainHigh[2] << 24))
#define SRAT_LOCAL_APIC_AFFINITY_READ_PROXIMITY_DOMAIN(LAA)      (LAA.ProximityDomainLow | (LAA.ProximityDomainHigh[0] << 8) | (LAA.ProximityDomainHigh[1] << 16) | (LAA.ProximityDomainHigh[2] << 24))

#define SRAT_LOCAL_APIC_AFFINITY_FLA_ENABLED    (1 << 0)

#define SRAT_MEMORY_AFFINITY_FLAG_ENABLED       (1 << 0)
#define SRAT_MEMORY_AFFINITY_FLAG_HOT_PLUGGABLE (1 << 1)
#define SRAT_MEMORY_AFFINIRT_FLAG_NON_VOLATILE  (1 << 3)

#define SRAT_GICC_AFFINITY_FLAG_ENABLED         (1 << 0)

#define SRAT_GENERIC_INITIATOR_AFFINITY_HANDLE_TYPE_ACPI_DEVICE_HANDLE  0
#define SRAT_GENERIC_INITIATOR_AFFINITY_HANDLE_TYPE_PCI_DEVICE_HANDLE   1

#define SRAT_GENERIC_PORT_AFFINITY_FLAG_ENABLED             (1 << 0)
#define SRAT_GENERIC_PORT_AFFINITY_FLAG_ACRH_TRANSACTION    (1 << 1)

#define RASF_MEMORY_REGION_SIGATURE 0x52415346

#define RASF_SET_RAS_CAPABILITIES_STATUS_SUCCESS            0  
#define RASF_SET_RAS_CAPABILITIES_STATUS_NOT_VALID          1
#define RASF_SET_RAS_CAPABILITIES_STATUS_NOT_SUPPORTED      2
#define RASF_SET_RAS_CAPABILITIES_STATUS_BUSY               3
#define RASF_SET_RAS_CAPABILITIES_STATUS_FAILED_F           4
#define RASF_SET_RAS_CAPABILITIES_STATUS_ABORTED            5
#define RASF_SET_RAS_CAPABILITIES_STATUS_INVALID            6

#define RASF_PCC_COMMAND_CODE_RESERVED                      0
#define RASF_PCC_COMMAND_CODE_EXECUTE_RASF_COMMAND          1

#define RASF_PLATFORM_RAS_CAPABILITIES_HBPS_SUPPORTED       (1 << 0)    //HBPS: Hardware Based Patrol Scrub
#define RASF_PLATFORM_RAS_CAPABILITIES_HBPS_ETS             (1 << 1)

#define RASF_PATROL_SCRUB_COMMAND_GET_PATROL_PARAMTERS      0x01
#define RASF_PATROL_SCRUB_COMMAND_START_PATROL_SCRUBBER     0x02
#define RASF_PATROL_SCRUB_COMMAND_STOP_PATROL_SCRUBBER      0x03

#define RASF_PATROL_SCRUB_FLAG_SET_SPEED_SLOW               0
#define RASF_PATROL_SCRUB_FLAG_SET_SPEED_MEDIUM             0b100 //im lazy im not translating the bits
#define RASF_PATROL_SCRUB_FLAG_SET_SPEED_FAST               0b111 //im lazy im not translating the bits

#define RAS2_FEATURE_TYPE_MEMORY                            0x00

#define RAS2_PCC_SIGNATURE(SignatureID) (0x50434300 | SignatureID)
#define MPST_PCC_SIGNATURE(SignatureID) (0x50434300 | SignatureID)

#define RAS2_SET_RAS_CAPABILITIES_STATUS_SUCCESS            0b0000
#define RAS2_SET_RAS_CAPABILITIES_STATUS_NOT_VALID          0b0001
#define RAS2_SET_RAS_CAPABILITIES_STATUS_NOT_SUPPORTED      0b0010
#define RAS2_SET_RAS_CAPABILITIES_STATUS_BUSY               0b0011
#define RAS2_SET_RAS_CAPABILITIES_STATUS_FAILED             0b0100
#define RAS2_SET_RAS_CAPABILITIES_STATUS_ABORTED            0b0101
#define RAS2_SET_RAS_CAPABILITIES_STATUS_INVALID_DATA       0b0110

#define RAS2_FEATURE_PATROL_SCRUB                           0
#define RAS2_FEATURE_LA2PA_TRANSLATION                      1

#define MPST_COMMAND_CODE_EXECUTE_MPST_COMMAND              0x03

#define MPST_COMMAND_STATUS_COMMAND_COMPLETE    (1 << 0)
#define MPST_COMMAND_STATUS_SCI_DOORBELL        (1 << 1)
#define MPST_COMMAND_STATUS_ERROR               (1 << 2)
#define MPST_COMMAND_STATUS_PLATFORM_NOTIF      (1 << 3)

#define MPST_MEMORY_POWER_NODE_FLAG_ENABLED             (1 << 0)
#define MPST_MEMORY_POWER_NODE_FLAG_POWER_MANAFED       (1 << 1)
#define MPST_MEMORY_POWER_NODE_FLAG_HOT_PLUGABLE        (1 << 2)

#define MPST_MPSC_FLAG_MEMORY_CONTENT_PRESERVED                 (1 << 0)
#define MPST_MPSC_FLAG_AUTONOMUS_MEMORY_POWER_STATE_ENTRY       (1 << 1)
#define MPST_MPSC_FLAG_AUTONOMUS_MEMORY_POWER_STATE_EXIT        (1 << 2)

#define PMTT_COMMON_MEMORY_DEVICE_TYPE_SOCKET               0
#define PMTT_COMMON_MEMORY_DEVICE_TYPE_MEMORY_CONTROLLER    1
#define PMTT_COMMON_MEMORY_DEVICE_TYPE_DIMM                 2

#define FPDT_PERFORMANCE_RECORD_TYPE_BASIC_BOOT_PERFORMANCE_POINTER     0
#define FPDT_PERFORMANCE_RECORD_TYPE_BASIC_S3_PERFORMANCE_POINTER       1

#define RUNTIME_PERFORMANCE_RECORD_S3_RESUME        0
#define RUNTIME_PERFORMANCE_RECORD_S3_SUSPEND       1
#define RUNTIME_PERFORMANCE_RECORD_BASIC            2



//im putting these in because you never know when you
//will have an ARM co-processor or a slave device such
//as the old ps3 or PS2 architecture types (although it 
//was a RISC style IBM Chip for its core and the Emotion 
//Engine was a RISC style MIPS 3000A on 64 bit steroids
//with a literal MIPS 3000A for IO Handling)...
#define ARM_BOOT_ARCH_PSCI_COMPLIANT                (1 << 0)
#define ARM_BOOT_ARCH_PSCI_USE_HVC                  (1 << 1)

#define MADT_ICS_GICC_FLAG_ENABLED                          (1 << 0)
#define MADT_ICS_GICC_FLAG_PERFORMANCE_INTERRUPT_MODE       (1 << 1)
#define MADT_ICS_GICC_FLAG_VGIC_MAITNENCE_INTERRUPT_MODE    (1 << 2)
#define MADT_ICS_GICC_FLAG_ONLINE_CAPABLE                   (1 << 3)

#define MADT_ICS_GIC_VERSION_1  0x01
#define MADT_ICS_GIC_VERSION_2  0x02
#define MADT_ICS_GIC_VERSION_3  0x03
#define MADT_ICS_GIC_VERSION_4  0x04

#define MADT_ICS_GIC_MSI_FLAG_SPI_COUNT_BASE_SELECT         (1 << 0)



typedef union _GAS_ADDRES_SPACE{
    uint64_t SystemMemoryAddress;
    uint64_t SystemIoAddress;
    struct __attribute__((packed)){
        //x86_64 bit is LE 0 bit first 
        //and is confined by bus and group 0
        uint16_t Offset;
        uint16_t Functon;
        uint16_t Device;
        uint16_t Zero;
    }PciConfigAddress;
    struct __attribute__((packed)){ 
        //this compiler has a glitch for 
        //padding bit fields so all defines 
        //are uint64_t
        uint64_t Offset     : 36;
        uint64_t Bar        : 3;
        uint64_t Function   : 3;
        uint64_t Device     : 5;
        uint64_t Bus        : 8;
        uint64_t Group      : 8;
    }PciBarAddress;
}GAS_ADDRES_SPACE, * PGAS_ADDRES_SPACE;

typedef struct _GENERAL_ADRESS_STRUCTURE{//GAS
    uint8_t                                                 AddressSpaceID;
    uint8_t                                                 RegisterWidth; //bits
    uint8_t                                                 RegisterOffset;//bits
    uint8_t                                                 AccessSize;
    GAS_ADDRES_SPACE                                        Address;
}GENERAL_ADRESS_STRUCTURE, * PGENERAL_ADRESS_STRUCTURE;

typedef struct __attribute__((packed)) _ROOT_SYSTEM_DISCRIPTION_POINTER{
    char                                                    Signature[8];
    uint8_t                                                 Checksum;
    char                                                    OemID[6];
    uint8_t                                                 Revision;
    uint32_t                                                RsdtAddress;
    uint32_t                                                RsdtLength;
    uint64_t                                                XsdtAddress;
    uint8_t                                                 ExtendedChecksum;
    uint8_t                                                 Reserved[3];
}ROOT_SYSTEM_DISCRIPTION_POINTER, * PROOT_SYSTEM_DISCRIPTION_POINTER;

typedef struct __attribute__((packed)) _TABLE_DESCRIPTION_HEADER{
    char                                                    Signature[4];
    uint32_t                                                Length;
    uint8_t                                                 Revision;
    uint8_t                                                 Checksum;
    char                                                    OemID[6];
    char                                                    OemTableID[8];
    uint32_t                                                OemRevision;
    uint32_t                                                CreatorID;
    uint32_t                                                CreatorRevision;
}TABLE_DESCRIPTION_HEADER, * PTABLE_DESCRIPTION_HEADER;

typedef struct __attribute__((packed)) _ROOT_SYSTEM_DISCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER                                RsdtHeader;//XSDT
    uint32_t                                                DescriptionHeaders[];
}ROOT_SYSTEM_DISCRIPTION_TABLE, * PROOT_SYSTEM_DISCRIPTION_TABLE;

typedef struct __attribute__((packed)) _EXTENDED_SYSTEM_DESCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER                                XsdtHeader; //XSDT
    uint64_t                                                DescriptionHeaders[];
}EXTENDED_SYSTEM_DESCRIPTION_TABLE, * PEXTENDED_SYSTEM_DESCRIPTION_TABLE;

typedef struct __attribute__((packed)) _FIXED_ACPI_DESCRIPTION_TABLE{ //FADT
    TABLE_DESCRIPTION_HEADER                                FadtHeader;
    uint32_t                                                FacsTablePhyPointer; //FIRMWARE_ACPI_CONTROL_STRUCTURE
    uint32_t                                                DsdtTablePhyPointer; 
    uint8_t                                                 Reserved1;
    uint8_t                                                 PreferedPowerMode;
    uint16_t                                                Sci8259PicInt;
    uint32_t                                                SmiCommandPort;
    uint8_t                                                 AcpiEnable;
    uint8_t                                                 AcpiDisable;
    uint8_t                                                 S4BiosRequestValue;
    uint8_t                                                 ProcessorStateControlValue;
    uint32_t                                                Pm1AEventRegisterBlockAddress;
    uint32_t                                                Pm1BEventRegisterBlockAddress;
    uint32_t                                                Pm1AControlRegisterBlockAddress;
    uint32_t                                                Pm1BControlRegisterBlockAddress;
    uint32_t                                                Pm2ControlRegisterBlockAddress;
    uint32_t                                                PmTimerControlRegisterBlock;
    uint32_t                                                GeneralPurposeEventBlock0;
    uint32_t                                                GeneralPurposeEventBlock1;
    uint8_t                                                 Pm1EventLength;
    uint8_t                                                 Pm1ControlLength;
    uint8_t                                                 Pm2ControlLength;
    uint8_t                                                 PmTimerLength;
    uint8_t                                                 GeneralPurposeEventBlock0Length;
    uint8_t                                                 GeneralPurposeEventBlock1Length;
    uint8_t                                                 GeneralPorposeEventBase;
    uint16_t                                                PmLevel2Latence;
    uint16_t                                                PmLevel3Latence;
    uint16_t                                                FlushSize;
    uint16_t                                                FlushStride;
    uint8_t                                                 DutyOffset;
    uint8_t                                                 DutyWidth;
    uint8_t                                                 DayAlarm;
    uint8_t                                                 MonthAlarm;
    uint8_t                                                 Century;
    uint16_t                                                IAPCBootArch;
    uint8_t                                                 Reserved2;
    uint32_t                                                FeatureFlags;
    uint8_t                                                 ResetRegister[12];
    uint8_t                                                 ResetValue;
    uint16_t                                                ArmBootArch;
    uint8_t                                                 FadtMinorVersion; //major revision is in the Revision in the FadtHeader
    uint64_t                                                XFirmwareControl;
    uint64_t                                                XDsdtPhyAddress;
    uint8_t                                                 XPm1AEventRegisterBlock[12];
    uint8_t                                                 XPm1BEventRegisterBlock[12];
    uint8_t                                                 XPm1AControlRegisterBlock[12];
    uint8_t                                                 XPm1BControlRegisterBlock[12];
    uint8_t                                                 XPm2ControlRegisterBlock[12];
    uint8_t                                                 XPmTimerRegisterBlock[12];
    uint8_t                                                 XGeneralPurposeEvent0[12];
    uint8_t                                                 XGeneralPurposeEvent1[12];
    uint8_t                                                 SleepStatusRegister[12];
    uint64_t                                                HypervisorVendorIdentity;
}FIXED_ACPI_DESCRIPTION_TABLE, * PFIXED_ACPI_DESCRIPTION_TABLE;

typedef struct __attribute__((packed)) _FIRMWARE_ACPI_CONTROL_STRUCTURE_TABLE{
    char                                                    Signature[4]; //FACS
    uint32_t                                                Length;
    uint32_t                                                HardwareSignature;
    uint32_t                                                FirmwareWakingVector;
    uint32_t                                                GlobalLock;
    uint32_t                                                FeatureFlags;
    uint64_t                                                XFirmwareWakingVector;
    uint8_t                                                 Version;
    uint8_t                                                 Reserved1[3];
    uint32_t                                                OspmFlags;
    uint8_t                                                 Reserved2[24];
}FIRMWARE_ACPI_CONTROL_STRUCTURE_TABLE, * PFIRMWARE_ACPI_CONTROL_STRUCTURE_TABLE;

typedef struct __attribute__((packed)) _DIFFERETIATED_SYSTEM_DESCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER                                DsdtHeader;
    uint8_t                                                 AmericanMachineLanguage[];
}DIFFERETIATED_SYSTEM_DESCRIPTION_TABLE, * PDIFFERETIATED_SYSTEM_DESCRIPTION_TABLE;

typedef struct __attribute__((packed)) _SECONDARY_SYSTEM_DESCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER                                SsdtHeader;
    uint8_t                                                 AmericanMachineLanguage[];
}SECONDARY_SYSTEM_DESCRIPTION_TABLE, * PSECONDARY_SYSTEM_DESCRIPTION_TABLE;

typedef struct __attribute__((packed)) _MULTIPLE_APIC_DESCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER                                MadtHeader;
    uint32_t                                                LICAddress;
    uint32_t                                                MultipleApicFlags;
    uint8_t                                                 DynamicMADTBuffer[];
    //use a current base + sizeof 
    //structure to index based 
    //of structures
}MULTIPLE_APIC_DESCRIPTION_TABLE, * PMULTIPLE_APIC_DESCRIPTION_TABLE;

typedef struct __attribute__((packed)) _MADT_ICS_PROCESSOR_LOCAL_APIC_STRUCTURE{
    uint8_t                                                 Type;  //0 
    uint8_t                                                 Length;//8
    uint8_t                                                 AcpiProcessorUID;
    uint8_t                                                 ApicID;
    uint32_t                                                LocalApicFlags;
}MADT_ICS_PROCESSOR_LOCAL_APIC_STRUCTURE, * PMADT_ICS_PROCESSOR_LOCAL_APIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_IO_APIC_STRUCTURE{
    uint8_t                                                 Type;  //1
    uint8_t                                                 Length;//12
    uint8_t                                                 IoApicID;
    uint8_t                                                 Reserved1;
    uint32_t                                                IoApicAddress;
    uint32_t                                                GsiBase;
}MADT_ICS_IO_APIC_STRUCTURE, * PMADT_ICS_IO_APIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_INTERRUPT_SOURCE_OVERIDE_STRUCTURE{
    uint8_t                                                 Type;  //2
    uint8_t                                                 Length;//10
    uint8_t                                                 Bus;
    uint8_t                                                 IrqSource;
    uint32_t                                                Gsi;
    uint16_t                                                MpsIntiFlags;
}MADT_ICS_INTERRUPT_SOURCE_OVERIDE_STRUCTURE, * PMADT_ICS_INTERRUPT_SOURCE_OVERIDE_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_NON_MASKABLE_INTERRUPT_SOURCE_STRUCTURE{
    uint8_t                                                 Type;  //3
    uint8_t                                                 Length;//8
    uint16_t                                                MpsIntiFlags;
    uint32_t                                                Gsi;
}MADT_ICS_NON_MASKABLE_INTERRUPT_SOURCE_STRUCTURE, * PMADT_ICS_NON_MASKABLE_INTERRUPT_SOURCE_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_LOCAL_APIC_NMI_STRUCTURE{
    uint8_t                                                 Type;  //4
    uint8_t                                                 Length;//6
    uint8_t                                                 ProcessorID;
    uint16_t                                                MpsIntiFlags;
    uint8_t                                                 LocalInterrupt;
}MADT_ICS_LOCAL_APIC_NMI_STRUCTURE, * PMADT_ICS_LOCAL_APIC_NMI_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE_STRUCTURE{
    uint8_t                                                 Type;  //5
    uint8_t                                                 Length;//12
    uint16_t                                                Reserved;//i see what you did here uefi.org thanks for not breaking my -O2 /s
    uint64_t                                                LocalApicAddress;
}MADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE_STRUCTURE, * PMADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_IO_SAPIC_STRUCTURE{
    uint8_t                                                 Type;  //6
    uint8_t                                                 Length;//16
    uint8_t                                                 IoApicID;
    uint8_t                                                 Reserved;
    uint32_t                                                GsiBase;
    uint64_t                                                IoSapicAddress;
}MADT_ICS_IO_SAPIC_STRUCTURE, * PMADT_ICS_IO_SAPIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_LOCAL_SAPIC_STATIC_STRUCTURE{
    uint8_t                                                 Type;  //7
    uint8_t                                                 Length;//Variac
    uint8_t                                                 ProcessorID;
    uint8_t                                                 LocalSapicID;
    uint8_t                                                 Reserved[3];
    uint32_t                                                SapicFlags;
    uint32_t                                                ProcessorUID;
}MADT_ICS_LOCAL_SAPIC_STATIC_STRUCTURE, * PMADT_ICS_LOCAL_SAPIC_STATIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_LOCAL_SAPIC_STRUCTURE{
    MADT_ICS_LOCAL_SAPIC_STATIC_STRUCTURE                   LocalSapicStatic;
    char                                                    ProcessorUIDStr[];
}MADT_ICS_LOCAL_SAPIC_STRUCTURE, * PMADT_ICS_LOCAL_SAPIC_STRUCTURE; 

typedef struct __attribute__((packed)) _MADT_ICS_PLATFORM_INTERRUPT_SOURCE_STRUCTURE{
    uint8_t                                                 Type;//8
    uint8_t                                                 Length;//16
    uint16_t                                                MpsIntiFlags;
    uint8_t                                                 InterruptType;
    uint8_t                                                 ProcessorID;
    uint8_t                                                 ProcessorEID;
    uint8_t                                                 IoSapicVector;
    uint32_t                                                Gsi;
    uint32_t                                                PlatformInterruptSource;
}MADT_ICS_PLATFORM_INTERRUPT_SOURCE_STRUCTURE, * PMADT_ICS_PLATFORM_INTERRUPT_SOURCE_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_LOCAL_X2_APIC_STRUCTURE{
    uint8_t                                                 Type; //9
    uint8_t                                                 Length;//16
    uint16_t                                                Reserved1;
    uint32_t                                                X2ApicId;
    uint32_t                                                Flags;
    uint32_t                                                ProcessorID;
}MADT_ICS_LOCAL_X2_APIC_STRUCTURE, * PMADT_ICS_LOCAL_X2_APIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_LOCAL_X2_APIC_NMI_STRUCTURE{
    uint8_t                                                 Type;//A
    uint8_t                                                 Length;//12
    uint16_t                                                Flags;
    uint32_t                                                ProcessorUID;
    uint8_t                                                 localInt;
    uint8_t                                                 Reserved[3];
}MADT_ICS_LOCAL_X2_APIC_NMI_STRUCTURE, * PMADT_ICS_LOCAL_X2_APIC_NMI_STRUCTURE;;

typedef union __attribute__((packed)) _MPIDR{ //once again 64s for bit padding glitch
    uint64_t                                                FlatValue;
    struct { //Arm systems are BE Last Bit First
        uint64_t                                            MustBeZero : 40;
        uint64_t                                            AFF2       : 8;
        uint64_t                                            AFF1       : 8;
        uint64_t                                            AFF0       : 8;
    }ArmV7;         
    struct {                                    
        uint64_t                                            MustBeZero1: 24;
        uint64_t                                            AFF3       : 8;
        uint64_t                                            MustBeZero2: 8;
        uint64_t                                            AFF2       : 8;
        uint64_t                                            AFF1       : 8;
        uint64_t                                            AFF0       : 8;
    }ArmV8;
}MPIDR, * PMPIDR;

typedef struct __attribute__((packed)) _MADT_ICS_GIC_CPU_INTERFACE_STRUCTURE{
    uint8_t                                                 Type;//B
    uint8_t                                                 Length;//82
    uint16_t                                                Reserved1;
    uint32_t                                                CpuInterfaceNumber;
    uint32_t                                                ProcessorUID;
    uint32_t                                                Flags;
    uint32_t                                                ParkingProtocolVersion;
    uint32_t                                                PerformanceInterruptGsi;
    uint64_t                                                ParkedAddress;
    uint64_t                                                PhysicalBaseAddress;
    uint64_t                                                Gicv;
    uint64_t                                                Gich;
    uint32_t                                                VGicMaitnenceInterrupt;
    uint64_t                                                GICRBaseAddress;
    MPIDR                                                   Mpidr;
    uint8_t                                                 PPECC;
    uint8_t                                                 Reserved2;
    uint16_t                                                SpeOverflowInterrupt;
    uint16_t                                                Trbeinterrupt;
}MADT_ICS_GIC_CPU_INTERFACE_STRUCTURE, * PMADT_ICS_GIC_CPU_INTERFACE_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_GICD_STRUCTURE{
    uint8_t                                                 Type; //C
    uint8_t                                                 Length;//24
    uint16_t                                                Reserved1;
    uint32_t                                                GicId;
    uint64_t                                                PhysicalBaseAddress;
    uint32_t                                                SystemVectorBase;
    uint8_t                                                 GicVersion;
    uint8_t                                                 Reserved2[3];
}MADT_ICS_GICD_STRUCTURE, * PMADT_ICS_GICD_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_GIC_MSI_FRAME_STRUCTURE{
    uint8_t                                                 Type;//D
    uint8_t                                                 Length;//24
    uint16_t                                                Reseved1;
    uint32_t                                                GicMsiFrameID;
    uint64_t                                                PhysicalBaseAddress;
    uint32_t                                                Flags;
    uint16_t                                                SpiCount;
    uint16_t                                                SpiBase;
}MADT_ICS_GIC_MSI_FRAME_STRUCTURE, * PMADT_ICS_GIC_MSI_FRAME_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_GIC_REDISTRIBUTER_STRUCTURE{
    uint8_t                                                 Type;//E
    uint8_t                                                 Length;//16
    uint16_t                                                Reserved1;
    uint64_t                                                DiscoveryRangeBase;
    uint32_t                                                DiscoveryRangeLength;
}MADT_ICS_GIC_REDISTRIBUTER_STRUCTURE, * PMADT_ICS_GIC_REDISTRIBUTER_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_GIC_INTERRUPT_TRANSLATION_SERIVCE_STRUCTURE{
    uint8_t                                                 Type;//F
    uint8_t                                                 Length;//20
    uint16_t                                                Reserved1;
    uint32_t                                                GicItsId;
    uint64_t                                                PhysicalBaseAddress;
    uint32_t                                                Reserved2;
}MADT_ICS_GIC_INTERRUPT_TRANSLATION_SERIVCE_STRUCTURE, * PMADT_ICS_GIC_INTERRUPT_TRANSLATION_SERIVCE_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_MULTIPROCESSOR_WAKEUP_MAILBOX_STRUCTURE{
    uint16_t                                                Command;
    uint16_t                                                Reserved1;
    uint32_t                                                ApicID;
    uint64_t                                                WakeupVector;
    uint8_t                                                 OsReserved[2032];
    uint8_t                                                 FirmwareReserved[2048];
}MADT_ICS_MULTIPROCESSOR_WAKEUP_MAILBOX_STRUCTURE, * PMADT_ICS_MULTIPROCESSOR_WAKEUP_MAILBOX_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_MULTIPROCESSOR_WAKEUP_STRUCTURE{
    uint8_t                                                 Type;//10
    uint8_t                                                 Length;//16
    uint16_t                                                MailboxVersion;
    uint32_t                                                Reserved1;
    MADT_ICS_MULTIPROCESSOR_WAKEUP_MAILBOX_STRUCTURE        MailboxAddress;
}MADT_ICS_MULTIPROCESSOR_WAKEUP_STRUCTURE, * PMADT_ICS_MULTIPROCESSOR_WAKEUP_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_CORE_PIC_STRUCTURE{
    uint8_t                                                 Type; //11
    uint8_t                                                 Length;
    uint8_t                                                 Version;
    uint32_t                                                ProcessorID;
    uint32_t                                                PhysicalProcessorID;
    uint32_t                                                Flags;
}MADT_ICS_CORE_PIC_STRUCTURE, * PMADT_ICS_CORE_PIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_LEGACY_IO_PIC_STRUCTURE{
    uint8_t                                                 Type; //12
    uint8_t                                                 Length;
    uint8_t                                                 Version;
    uint64_t                                                BaseAddress;
    uint16_t                                                Size;
    uint16_t                                                CascadeVector;
    uint64_t                                                CascadeVectorMapping;
}MADT_ICS_LEGACY_IO_PIC_STRUCTURE, * PMADT_ICS_LEGACY_IO_PIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_HT_PIC_STRUCTURE{
    uint8_t                                                 Type;   //13
    uint8_t                                                 Length;
    uint16_t                                                Version;
    uint64_t                                                BaseAddress;
    uint16_t                                                Size;
    uint64_t                                                CascadeVector;
}MADT_ICS_HT_PIC_STRUCTURE, * PMADT_ICS_HT_PIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_EIO_PCI_STRUCTURE{
    uint8_t                                                 Type;//14
    uint8_t                                                 Length;
    uint8_t                                                 Version;
    uint8_t                                                 CascadeVector;
    uint8_t                                                 Node;
    uint64_t                                                NodeMap;
}MADT_ICS_EIO_PCI_STRUCTURE, * PMADT_ICS_EIO_PCI_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_MSI_PIC_STRUCTURE{
    uint8_t                                                 Type; //15
    uint8_t                                                 Length;
    uint8_t                                                 Version;
    uint64_t                                                MessageAddress;
    uint32_t                                                StartVector;
    uint32_t                                                VectorCount;
}MADT_ICS_MSI_PIC_STRUCTURE, * PMADT_ICS_MSI_PIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_BIO_PIC_STRUCTURE{
    uint8_t                                                 Type;//16
    uint8_t                                                 Length;
    uint8_t                                                 Version;
    uint64_t                                                BaseAddress;
    uint16_t                                                Size;
    uint16_t                                                HardwareID;
    uint16_t                                                GsiBase;
}MADT_ICS_BIO_PIC_STRUCTURE, * PMADT_ICS_BIO_PIC_STRUCTURE;

typedef struct __attribute__((packed)) _MADT_ICS_LPC_PIC_STRUCTURE{
    uint8_t                                                 Type; //17
    uint8_t                                                 Length;
    uint8_t                                                 Version;
    uint64_t                                                BaseAddress;
    uint16_t                                                Size;
    uint16_t                                                CascadeVector;
}MADT_ICS_LPC_PIC_STRUCTURE, * PMADT_ICS_LPC_PIC_STRUCTURE;

typedef struct __attribute__((packed)) _SMART_BATTER_TABLE{
    TABLE_DESCRIPTION_HEADER                                SbstHeader;
    uint32_t                                                WarningEnergyLevel;
    uint32_t                                                LowEnergyLevel;
    uint32_t                                                CriticalEnergyLevel;
}SMART_BATTER_TABLE, * PSMART_BATTER_TABLE;

typedef struct __attribute__((packed)) _EMBEDDED_CONTROLLER_BOOT_RESOURCES_TABLE{
    TABLE_DESCRIPTION_HEADER                                EcdtHeader;
    uint8_t                                                 EccControl[12];
    uint8_t                                                 EccData[12];
    uint32_t                                                Uid;
    uint8_t                                                 GpeBit;
    uint8_t                                                 EcId[];
}EMBEDDED_CONTROLLER_BOOT_RESOURCES_TABLE, * PEMBEDDED_CONTROLLER_BOOT_RESOURCES_TABLE;

typedef struct __attribute__((packed)) _STATIC_RESOURCE_AFINITY_TABLE{
    TABLE_DESCRIPTION_HEADER                                SratHeader;
    uint8_t                                                 Reserved[12];
    uint8_t                                                 SratBuffer[];    
}STATIC_RESOURCE_AFINITY_TABLE, * PSTATIC_RESOURCE_AFINITY_TABLE;

typedef struct __attribute__((packed)) _SRAT_LOCAL_APIC_AFFINITY_STRUCTURE{
    uint8_t                                                 Type;//0
    uint8_t                                                 Length;//16
    uint8_t                                                 ProximityDomainLow;
    uint8_t                                                 ApicID;
    uint32_t                                                Flags;
    uint8_t                                                 LocalSapicEID;
    uint8_t                                                 ProximityDomainHigh;
    uint32_t                                                ClockDomain;
}SRAT_LOCAL_APIC_AFFINITY_STRUCTURE, * PSRAT_LOCAL_APIC_AFFINITY_STRUCTURE;

typedef struct __attribute__((packed)) _SRAT_MEMORY_AFFINITY_STRUTURE{
    uint8_t                                                 Type;//1
    uint8_t                                                 Length;//40
    uint32_t                                                ProximityDomain;
    uint16_t                                                Reserved1;
    uint32_t                                                BaseAddressLow;
    uint32_t                                                BaseAddressHigh;
    uint32_t                                                LengthLow;
    uint32_t                                                LengthHigh;
    uint32_t                                                Reserved2;
    uint32_t                                                Flags;
    uint64_t                                                Reserved3;
}SRAT_MEMORY_AFFINITY_STRUTURE, * PSRAT_MEMORY_AFFINITY_STRUTURE;

typedef struct __attribute__((packed)) _SRAT_PROCESSOR_LOCAL_X2_APIC_AFFINITY_STRUCTURE{
    uint8_t                                                 Type;//2
    uint8_t                                                 Length;//24
    uint16_t                                                Reserved1;
    uint32_t                                                ProximityDomain;
    uint32_t                                                X2ApicId;
    uint32_t                                                Flags;
    uint32_t                                                ClockDomain;
    uint32_t                                                Reserved2;
}SRAT_PROCESSOR_LOCAL_X2_APIC_AFFINITY_STRUCTURE, * PSRAT_PROCESSOR_LOCAL_X2_APIC_AFFINITY_STRUCTURE;

typedef struct __attribute__((packed)) _SRAT_GICC_AFFINITY_STRUCTURE{
    uint8_t                                                 Type;//3
    uint8_t                                                 ProximityDomain;
    uint32_t                                                ProcessorUID;
    uint32_t                                                Flags;
    uint32_t                                                ClockDomain;
}SRAT_GICC_AFFINITY_STRUCTURE, * PSRAT_GICC_AFFINITY_STRUCTURE;

typedef struct __attribute__((packed)) _SRAT_GIC_ITS_AFFINITY_STRUCTURE{
    uint8_t                                                 Type;//4;
    uint8_t                                                 Length;// 12
    uint32_t                                                ProximityDomain;
    uint16_t                                                Reserved;
    uint32_t                                                ItsID;
}SRAT_GIC_ITS_AFFINITY_STRUCTURE, * PSRAT_GIC_ITS_AFFINITY_STRUCTURE;

typedef struct __attribute__((packed)) _SRAT_GENERIC_INITIATOR_AFFINITY_STRUCTURE{
    uint8_t                                                 Type;//5
    uint8_t                                                 Length;//32
    uint8_t                                                 Reserved1;
    uint8_t                                                 DeviceHandleType;
    uint32_t                                                ProximityDomain;
    uint8_t                                                 DeviceHandle[16];
    uint32_t                                                Flags;
    uint32_t                                                Reserved2;
}SRAT_GENERIC_INITIATOR_AFFINITY_STRUCTURE, * PSRAT_GENERIC_INITIATOR_AFFINITY_STRUCTURE;

typedef struct __attribute__((packed)) _ACPI_SPEC_ACPI_DEVICE_HANDLE{
    uint64_t                                                AcpiHID;
    uint32_t                                                AcpiUID;
    uint32_t                                                Reserved;
}ACPI_SPEC_ACPI_DEVICE_HANDLE, * PACPI_SPEC_ACPI_DEVICE_HANDLE;

typedef struct __attribute__((packed)) _ACPI_BDF_STRUCTURE{
    uint8_t     Reserved;
    uint8_t     BusNumber;
    //split bit LE bit 0 first
    uint8_t    FunctionNumber   : 2;
    uint8_t    DeviceNumber     : 6;
}ACPI_BDF_STRUCTURE, * PACPI_BDF_STRUCTURE;

typedef union __attribute__((packed)) _ACPI_BDF{
    uint16_t            FlatValue;
    ACPI_BDF_STRUCTURE  BdfMembers;
}ACPI_BDF, * PACPI_BDF;

typedef struct __attribute__((packed)) _ACPI_SPEC_PCI_DEVICE_HANDLE{
    uint16_t                                                PciSegment;
    ACPI_BDF                                                BdfNumber;
    uint8_t                                                 Reserved;
}ACPI_SPEC_PCI_DEVICE_HANDLE, * PACPI_SPEC_PCI_DEVICE_HANDLE;

typedef struct __attribute__((packed)) _SRAT_GENERIC_PORT_AFFINITY_STRUCTURE{
    uint8_t                                                 Type;//6
    uint8_t                                                 Length;//32
    uint8_t                                                 Reserved1;
    uint8_t                                                 DeviceHandleType;
    uint32_t                                                ProximityDomain;
    uint8_t                                                 DeviceHandle[16];
    uint32_t                                                Flags;
    uint32_t                                                Reserved2;
}SRAT_GENERIC_PORT_AFFINITY_STRUCTURE, * PSRAT_GENERIC_PORT_AFFINITY_STRUCTURE;

typedef struct __attribute__((packed)) _SYSTEM_LOCALITY_INFORMATION_TABLE{
    TABLE_DESCRIPTION_HEADER    SlitHeader;
    uint64_t                    NumberOfSystemLocality;
    uint8_t                     Entries[];//the matrix entries 00 and 10 = 10
}SYSTEM_LOCALITY_INFORMATION_TABLE, * PSYSTEM_LOCALITY_INFORMATION_TABLE;

typedef struct __attribute__((packed)) _CPEP_PROCESSOR_STRUCUTRE{
    uint8_t                     Type; //0
    uint8_t                     Length;//8
    uint8_t                     ProcessorID;
    uint8_t                     ProcessorEID;
    uint32_t                    PollingInterval;
}CPEP_PROCESSOR_STRUCUTRE, * PCPEP_PROCESSOR_STRUCUTRE;

typedef struct __attribute__((packed)) _CORRECTED_PLATFORM_ERROR_POLLING_TABLE{
    TABLE_DESCRIPTION_HEADER    CpepHeader;
    uint64_t                    Reserved1;
    CPEP_PROCESSOR_STRUCUTRE    ProcessorStructure[];
}CORRECTED_PLATFORM_ERROR_POLLING_TABLE, * PCORRECTED_PLATFORM_ERROR_POLLING_TABLE;

typedef struct __attribute__((packed)) _MAXIMUM_SYSTEM_CHARECTERISTICS_TABLE{
    TABLE_DESCRIPTION_HEADER    MsctHeader;
    uint32_t                    ProximityDomainInfoOffset;
    uint32_t                    MaximumProximityDomains;
    uint32_t                    MaximumClockDomains;
    uint64_t                    MaximumPhysicalAddresses;
    uint8_t                     TableBuffer[]; //starts at MaximumProximityDomains
}MAXIMUM_SYSTEM_CHARECTERISTICS_TABLE, * PMAXIMUM_SYSTEM_CHARECTERISTICS_TABLE;

typedef struct __attribute__((packed)) _MAXIMUM_PROXIMITY_DOMAIN_INFORMATION_STRUCTURE{
    uint8_t                     Revision;//1
    uint8_t                     Length;//22
    uint32_t                    ProximityDomainLow;
    uint32_t                    ProximityDomainHigh;
    uint32_t                    MaximumProcessorCapacity;
    uint64_t                    MaximumMemoryCapacity;
}MAXIMUM_PROXIMITY_DOMAIN_INFORMATION_STRUCTURE, *  PMAXIMUM_PROXIMITY_DOMAIN_INFORMATION_STRUCTURE;

typedef struct __attribute__((packed)) _RAS_FEATURE_TABLE{
    TABLE_DESCRIPTION_HEADER    RasfHeader;
    uint8_t                     RasfPlatformCommunicationChannelID[12];
}RAS_FEATURE_TABLE, * PRAS_FEATURE_TABLE;

typedef struct __attribute__((packed)) _RASF_PLAT_COMM_CHANNEL_SHARED_MEMORY_REGION{
    uint32_t                    Signature;
    uint16_t                    Command;
    uint16_t                    Status;
    uint16_t                    Version;
    uint8_t                     RasCapabilities[16];
    uint8_t                     SetRasCapabilities[16];
    uint16_t                    NumberOfRasfParameterBlocks;
    uint32_t                    SetRasCapabilitiesStatus;
    uint8_t                     ParameterBlocks[];
}RASF_PLAT_COMM_CHANNEL_SHARED_MEMORY_REGION, * PRASF_PLAT_COMM_CHANNEL_SHARED_MEMORY_REGION;

typedef struct __attribute__((packed)) _RASF_PATROL_SCRUB_FLAGS_STRCUTRE{
    uint8_t     CurrentPatrolSpeed : 3;
    uint8_t     ReservedLow        : 5;
    uint16_t    ReservedHigh;
}RASF_PATROL_SCRUB_FLAGS_STRCUTRE, * PRASF_PATROL_SCRUB_FLAGS_STRCUTRE;

typedef union __attribute__((packed)) _RASF_PATROL_SCRUB_FLAGS{
    uint16_t                            FlatValue;
    RASF_PATROL_SCRUB_FLAGS_STRCUTRE    SpecFlags;
}RASF_PATROL_SCRUB_FLAGS, * PRASF_PATROL_SCRUB_FLAGS;

typedef struct __attribute__((packed)) _RASF_PATROL_SCRUB_REQUEST_SPEED_STRUCTURE{
    uint8_t     Speed       : 2;
    uint8_t     Reserved    : 6;
}RASF_PATROL_SCRUB_REQUEST_SPEED_STRUCTURE, * PRASF_PATROL_SCRUB_REQUEST_SPEED_STRUCTURE;

typedef union __attribute__((packed)) _RASF_PATROL_SCRUB_REQUEST_SPEED{
    uint8_t                                     FlatValue;
    RASF_PATROL_SCRUB_REQUEST_SPEED_STRUCTURE   Speed;
}RASF_PATROL_SCRUB_REQUEST_SPEED, * PRASF_PATROL_SCRUB_REQUEST_SPEED;

typedef struct __attribute__((packed)) _RASF_PATROL_SCRUB{
    uint16_t                            Type;   
    uint16_t                            Version;
    uint16_t                            Length;
    uint16_t                            PatrolScrubCommand;
    uint8_t                             RequestedRange[16];
    uint8_t                             ActualAddressRange[16];
    RASF_PATROL_SCRUB_FLAGS             Flags;
    RASF_PATROL_SCRUB_REQUEST_SPEED     RequestSpeed;
}RASF_PATROL_SCRUB, * PRASF_PATROL_SCRUB;

typedef struct __attribute__((packed)) _RAS2_PCC_DESCRIPTOR{
    uint8_t                             PccID;
    uint16_t                            Reserved;
    uint8_t                             FeatureType;
    uint32_t                            Instance;
}RAS2_PCC_DESCRIPTOR, * PRAS2_PCC_DESCRIPTOR;

typedef struct __attribute__((packed)) _RAS_FEATURE_2_TABLE{
    TABLE_DESCRIPTION_HEADER            Ras2Header;
    uint16_t                            Reserved1;
    uint16_t                            PccDescriptors;
    RAS2_PCC_DESCRIPTOR                 Ras2PCCDescriptorList[];
}RAS_FEATURE_2_TABLE, * PRAS_FEATURE_2_TABLE;

typedef struct __attribute__((packed)) _RAS2_PCC_CHANNEL_SHARED_MEMPRY_REGION{
    uint32_t                            Signature;
    uint16_t                            Command;
    uint16_t                            Status;
    uint16_t                            Version;
    uint8_t                             RasFeatures[16];
    uint8_t                             SetRasCapabilities[16];
    uint16_t                            Ras2ParameterBlocks;
    uint32_t                            SetRasCapabilitiesStatus;
    uint8_t                             ParameterBlocks[];
}RAS2_PCC_CHANNEL_SHARED_MEMPRY_REGION, * PRAS2_PCC_CHANNEL_SHARED_MEMPRY_REGION;

typedef struct __attribute__((packed)) _RAS2_FEATURE_TYPE_0{
    uint8_t                             PccIdentifier;
    uint16_t                            Reserved;
    uint8_t                             FeatureType;
    uint32_t                            Instance;
}RAS2_FEATURE_TYPE_0, * PRAS2_FEATURE_TYPE_0;

typedef struct __attribute__((packed)) _RAS2_PATROL_SCRUB_PARAMETER_BLOCK{
    uint16_t                            Type;
    uint16_t                            Version;
    uint16_t                            Length;
    uint16_t                            PatrolScrubCommand;
    uint8_t                             RequestedRange[16];
    uint8_t                             ActualAddressRange[16];
    uint32_t                            Flags;
    uint32_t                            ScrubParameters;
}RAS2_PATROL_SCRUB_PARAMETER_BLOCK, * PRAS2_PATROL_SCRUB_PARAMETER_BLOCK;

typedef struct __attribute__((packed)) _RAS2_LA2PA_TRANSLATION_PARAMETER_BLOCK{
    uint16_t        Type;
    uint16_t        Version;
    uint16_t        Length;
    uint16_t        AddressTranslation;
    uint64_t        SubInstanceIdentifier;
    uint64_t        LogicalAddress;
    uint64_t        PhysicalAddress;
    uint32_t        Status;
}RAS2_LA2PA_TRANSLATION_PARAMETER_BLOCK, * PRAS2_LA2PA_TRANSLATION_PARAMETER_BLOCK;

typedef struct __attribute__((packed)) _MEMORY_POWER_STATE_TABLE{
    TABLE_DESCRIPTION_HEADER            MpstHeader;
    uint8_t                             MpstPccID;
    uint8_t                             Reserved1[3];
    uint16_t                            MemoryPowerNodeCount;
    uint16_t                            Reserved2;
    uint8_t                             MemoryPowerNodeBuffer[];
}MEMORY_POWER_STATE_TABLE, * PMEMORY_POWER_STATE_TABLE;

typedef struct __attribute__((packed)) _MPST_PCC_SHARED_MEMORY_REGION{
    uint32_t    Signature;
    uint16_t    Command;
    uint16_t    Status;
    uint32_t    MemoryPowerCommandRegister;
    uint32_t    MemoryPowerStatusRegister;
    uint32_t    PowerStateID;
    uint32_t    MemoryPowerNodeID;
    uint64_t    MemoryEnergyConsumed;
    uint64_t    ExpectedAveragePowerConsumed;
}MPST_PCC_SHARED_MEMORY_REGION, * PMPST_PCC_SHARED_MEMORY_REGION;

typedef struct __attribute__((packed)) _MPST_MEMORY_POWER_NODE{
    uint8_t     Flag;
    uint8_t     Reserved;
    uint16_t    MemoryPowerNodeID;
    uint32_t    Length;
    uint32_t    BaseAddressLow;
    uint32_t    BaseAddressHigh;
    uint32_t    LengthLow;
    uint32_t    LengthHigh;
    uint32_t    NumberOfPowerState;
    uint32_t    NumberOfPhysicalComponents;
    uint8_t     MPNBuffer[];
}MPST_MEMORY_POWER_NODE, * PMPST_MEMORY_POWER_NODE;

typedef struct __attribute__((packed)) _MPST_MEMORY_POWER_STATE{
    uint8_t     PowerStateValue;
    uint8_t     PowerStateInformationIndex;
}MPST_MEMORY_POWER_STATE, * PMPST_MEMORY_POWER_STATE;

typedef struct __attribute__((packed)) _MPST_MPSC_POWER_STATE_ID_STRCUTURE{
    uint8_t     FormatID            : 6;
    uint8_t     StrucutreRevision   : 2;
}MPST_MPSC_POWER_STATE_ID_STRCUTURE, * PMPST_MPSC_POWER_STATE_ID_STRCUTURE;

typedef union __attribute__((packed)) _MPST_MPSC_POWER_STATE_ID{
    uint8_t                                 FlatValue;
    MPST_MPSC_POWER_STATE_ID_STRCUTURE      SpecValue;
}MPST_MPSC_POWER_STATE_ID, * PMPST_MPSC_POWER_STATE_ID;

typedef struct __attribute__((packed)) _MPST_MEMORY_POWER_STATE_CHARECTERISTICS{
    MPST_MPSC_POWER_STATE_ID        PowerStateID;
    uint8_t                         Flags;
    uint16_t                        Reserved1;
    uint32_t                        APC;
    uint32_t                        RelativePowerSaving;
    uint64_t                        ExitLatency;
    uint64_t                        Reserved2;
}MPST_MEMORY_POWER_STATE_CHARECTERISTICS, * PMPST_MEMORY_POWER_STATE_CHARECTERISTICS;

typedef struct __attribute__((packed)) _PLATFORM_MEMORY_TOPOLOGY_TABLE{
    TABLE_DESCRIPTION_HEADER        PmttHeader;
    uint32_t                        NumberOfMemoryDevices;
    uint8_t                         MemoryDeviceBuffer[];
}PLATFORM_MEMORY_TOPOLOGY_TABLE, * PPLATFORM_MEMORY_TOPOLOGY_TABLE;

typedef struct __attribute__((packed)) _PMTT_COMMON_MEMORY_DEVICE{
    uint8_t     Type;
    uint8_t     Reserved1;
    uint16_t    Length;
    uint16_t    Flags;
    uint16_t    Reserved2;
    uint32_t    NumberOfMemoryDevices;
}PMTT_COMMON_MEMORY_DEVICE, * PPMTT_COMMON_MEMORY_DEVICE;

typedef struct __attribute__((packed)) _PMTT_CMD_SOCKET_TYPE_DATA{
    PMTT_COMMON_MEMORY_DEVICE   CommonDeviceHeader;
    uint16_t                    SocketIdentifier;
    uint16_t                    Reserved1;
    uint8_t                     MemorDeviceData[];
}PMTT_CMD_SOCKET_TYPE_DATA, * PPMTT_CMD_SOCKET_TYPE_DATA;

typedef struct __attribute__((packed)) _PMTT_CMD_MEMORY_CONTROLLER_TYPE_DATA{
    PMTT_COMMON_MEMORY_DEVICE   CommonDeviceHeader;
    uint16_t                    MemoryControllerIdentifier;
    uint16_t                    Reserved1;
    uint8_t                     MemorDeviceData[];
}PMTT_CMD_MEMORY_CONTROLLER_TYPE_DATA, * PPMTT_CMD_MEMORY_CONTROLLER_TYPE_DATA;

typedef struct __attribute__((packed)) _PMTT_CMD_DIMM_TYPE_DATA{
    PMTT_COMMON_MEMORY_DEVICE   CommonDeviceHeader;
    uint32_t                    SmBiosHandle;
}PMTT_CMD_DIMM_TYPE_DATA, * PPMTT_CMD_DIMM_TYPE_DATA;

typedef struct __attribute__((packed)) _PMTT_CMD_VENDOR_SPECIFIC_TYPE_DATA{
    PMTT_COMMON_MEMORY_DEVICE   CommonDeviceHeader;
    uint8_t                     TypeUUID[16];
    uint8_t                     VendorSpecificData[];
}PMTT_CMD_VENDOR_SPECIFIC_TYPE_DATA, * PPMTT_CMD_VENDOR_SPECIFIC_TYPE_DATA;

typedef struct __attribute__((packed)) _BGRT_STATUS_STRUCTURE{
    uint8_t                     Displayed           : 1;
    uint8_t                     OrientationOffset   : 2;
    uint8_t                     Reserved            : 5;
}BGRT_STATUS_STRUCTURE, * PBGRT_STATUS_STRUCTURE;

typedef union __attribute__((packed)) _BGRT_STATUS{
    uint8_t                 FlatValue;
    BGRT_STATUS_STRUCTURE   SpecFlags;
}BGRT_STATUS, * PBGRT_STATUS;

typedef struct __attribute__((packed)) _BOOT_GRAPHICS_RESOURCE_TABLE{
    TABLE_DESCRIPTION_HEADER    BgrtHeader;
    uint16_t                    Version;
    BGRT_STATUS                 Status;
    uint8_t                     ImageType;
    uint64_t                    ImageAddress;
    uint32_t                    ImageOffsetX;
    uint32_t                    ImageOffsetY;
}BOOT_GRAPHICS_RESOURCE_TABLE, * PBOOT_GRAPHICS_RESOURCE_TABLE;

typedef struct __attribute__((packed)) _FIRMWARE_PERFORMANCE_DATA_TABLE{
    TABLE_DESCRIPTION_HEADER    FpdtHeader;
    uint8_t                     RecordBuffer[];
}FIRMWARE_PERFORMANCE_DATA_TABLE, * PFIRMWARE_PERFORMANCE_DATA_TABLE;

typedef struct __attribute__((packed)) _FPDT_PERFORMANCE_RECORD{
    uint16_t                    PerformanceRecord;
    uint8_t                     RecordLength;
    uint8_t                     Revision;
    uint8_t                     Data[];
}FPDT_PERFORMANCE_RECORD, * PFPDT_PERFORMANCE_RECORD;

typedef struct __attribute__((packed)) _FPDT_BASIC_BOOT_PERFORMANCE_TABLE_POINTER{
    uint16_t                    PerformanceRecordType;
    uint8_t                     RecordLength; //16
    uint8_t                     Revision;
    uint32_t                    Reserved;
    uint64_t                    Pointer;
}FPDT_BASIC_BOOT_PERFORMANCE_TABLE_POINTER, * PFPDT_BASIC_BOOT_PERFORMANCE_TABLE_POINTER;

typedef struct __attribute__((packed)) _FPDT_S3_PERFORMANCE_TABLE_POINTER{
    uint16_t                    PerformanceRecordType;
    uint8_t                     RecordLength; //16
    uint8_t                     Revision;
    uint32_t                    Reserved;
    uint64_t                    Pointer;
}FPDT_S3_PERFORMANCE_TABLE_POINTER, * PFPDT_S3_PERFORMANCE_TABLE_POINTER;

typedef struct __attribute__((packed)) _PFPDT_BASIC_BOOT_PERFORMANCE_TABLE{
    char                        Signature[4];
    uint32_t                    Length;
    uint16_t                    PerformanceRecordType;
    uint8_t                     RecordLength;
    uint8_t                     Revision;
    uint32_t                    Reserved1;
    uint64_t                    ResetEnd;
    uint64_t                    OsLoaderLoadImage;
    uint64_t                    OsLoaderStartImage;
    uint64_t                    ExitBootServiceEntry;
    uint64_t                    ExitBootServiceExit;
}PFPDT_BASIC_BOOT_PERFORMANCE_TABLE, * PPFPDT_BASIC_BOOT_PERFORMANCE_TABLE;



#ifdef __cplusplus
}
#endif
#endif