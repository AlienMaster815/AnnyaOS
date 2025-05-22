#ifndef _ACPI_DEFINITIONS_H
#define _ACPI_DEFINITIONS_H

//all structure definitions for the ACPI 6.5 Decemeber 
//2024 specification release written by -Tyler Grenier

#ifndef _GUID_TYPE 
#define _GUID_TYPE
//im in a blind spot and im 
//lazy so i just stuck this here
typedef struct _GUID {
	unsigned char DataByte[16];
} GUID,* LPGUID, UUID, * PGUID, * PUUID;
#endif


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

#define FOR_EACH_PRSDT_ENTRY(RSDT) for(size_t RsdtEntry = 0 ; RsdtEntry < ((RSDT->RsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER)) / 4); RsdtEntry++)
#define FOR_EACH_RSDT_ENTRY(RSDT) for(size_t RsdtEntry = 0 ; RsdtEntry < ((RSDT.RsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER)) / 4); RsdtEntry++)

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

#define MADT_ICS_ISO_MPS_INTI_FLAG_POLARITY         (3 << 0)
#define MADT_ICS_ISO_MPS_INTI_FLAG_TRIGGER_MODE     (3 << 2)

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

#define ELI_TIMER_FLAG_TIMER_INTERRUPT_MODE         (1 << 0)
#define ELI_TIMER_INTERRUPT_MODE_EDGE               (1 << 0)
#define ELI_TIMER_INTERRUPT_MODE_LEVEL              (0 << 0)

#define ELI_TIMER_FLAG_TIMER_INTERRUPT_POLARITY     (1 << 1)
#define ELI_TIMER_INTERRUPT_POLARITY_ACTIVE_LOW     (1 << 1)
#define ELI_TIMER_INTERRUPT_POLARITY_ACTIVE_HIGH    (0 << 1)

#define ELI_TIMER_FLAG_ALWAYS_ON_CAPABILITY         (1 << 2)

#define GTDT_PLATFORM_TIMER_STRUCUTR_TYPE_GT_BLOCK                  0
#define GTDT_PLATFORM_TIMER_STRUCUTR_TYPE_ARM_GENERIC_WATCHDOG      1

#define ARM_WATCHDOG_TIMER_FLAG_INTERRUPT_MODE  (1 << 0)
#define ARM_WATCHDOG_TIMER_INTERRUPT_MODE_EDGE  (1 << 0)
#define ARM_WATCHDOG_TIMER_INTERRUPT_MODE_LEVEL (0 << 0)

#define ARM_WATCHDOG_TIMER_FLAG_INTERRUPT_POLARITY          (1 << 1)
#define ARM_WATCHDOG_TIMER_INTERRUPT_POLARITY_ACTIVE_LOW    (1 << 1)
#define ARM_WATCHDOG_TIMER_INTERRUPT_POLARITY_ACTIVE_HIGH   (0 << 1)

#define ARM_WATCHDOG_TIMER_FLAG_SECURE_TIMER                (1 << 2)
#define ARM_WATCHDOG_TIMER_SECURE_TIMER_IS_SECURE           (1 << 2)
#define ARM_WATCHDOG_TIMER_SECURE_TIMER_IS_NON_SECURE       (0 << 2)

#define NFIT_STRUCUTRE_TYPE_SYSTEM_PHYSICAL_ADDRESS_RANGE   0
#define NFIT_STRUCUTRE_TYPE_NVDIMM_REGION_MAPPING           1
#define NFIT_STRUCUTRE_TYPE_INTERLEAVE                      2
#define NFIT_STRUCUTRE_TYPE_SMBIOS_MANAGEMENT_INFORMATION   3
#define NFIT_STRUCUTRE_TYPE_NVDIMM_CONTROL_REGION           4
#define NFIT_STRUCUTRE_TYPE_NVDIMM_BLOCK_DATA_WINDOW_REGION 5
#define NFIT_STRUCUTRE_TYPE_FLUSH_HINT_ADDRESS              6
#define NFIT_STRUCUTRE_TYPE_PLATFORM_CAPABILITIES           7

#define NVDIMM_STATE_FLAG_SAVE_FAILED                                   (1 << 0)
#define NVDIMM_STATE_FLAG_SAVE_SUCCESS                                  (0 << 0)
#define NVDIMM_STATE_FLAG_RESOTRE_FAILED                                (1 << 1)
#define NVDIMM_STATE_FLAG_RESOTRE_SUCCESS                               (0 << 1)
#define NVDIMM_STATE_FLAG_FLUSH_BEFORE_SAVE_FAILED                      (1 << 2)
#define NVDIMM_STATE_FLAG_FLUSH_BEFORE_SAVE_SUCCESS                     (0 << 2)
#define NVDIMM_STATE_FLAG_NVDIMM_PRECISTANT_WRITES_FAILED               (1 << 3)
#define NVDIMM_STATE_FLAG_NVDIMM_REGION_ARMED                           (0 << 3)
#define NVDIMM_STATE_FLAG_SMART_HEALTH_EVENT_PRIOR_TO_OSPM              (1 << 4)
#define NVDIMM_STATE_FLAG_SMART_HEALTH_PRE_OSPM_DETECTION_ENABLED       (1 << 5)
#define NVDIMM_STATE_FLAG_FIRMWARE_DID_NOT_MAP_NVDIMM                   (1 << 6)

#define SDEV_ACPI_NAMESPACE_DEVICE  0
#define SDEV_PCIE_ENDPOINT          1

#define SDEV_ACPI_NAMESPACE_DEVICE_FLAG_ALLOW_NONSECURE_HANDOFF             (1 << 0)
#define SDEV_ACPI_NAMESPACE_DEVICE_FLAG_SECURE_ACCESS_COMPONENTS_PRESETN    (1 << 1)

#define SDEV_SECURE_ACCESS_COMPONENT_TYPE_ID_BASED_SECURE_ACCESS_COMPONENT      0
#define SDEV_SECURE_ACCESS_COMPONENT_TYPE_MEMORY_BASED_SECURE_ACCESS_COMPONENT  1

#define HMAT_STRUCTURE_TYPE_MEMORY_PROXIMITY_DOMAIN_ATTRIBUTE   0
#define HMAT_STRUCTURE_TYPE_SYSTEM_LOCALITY_LATENCE_BANDWITH    1
#define HMAT_STRUCUTRE_TYPE_MEMORY_SIDE_CACHE                   2

#define HMAT_SSLB_FLAG_MEMORY_PERFORMANCE       0
#define HMAT_SSLB_FLAG_LEVEL_1_SIDE_CACHE       1
#define HMAT_SSLB_FLAG_LEVEL_2_SIDE_CACHE       2
#define HMAT_SSLB_FLAG_LEVEL_3_SIDE_CACHE       3
#define HMAT_SSLB_FLAG_MINIMUM_TRANSFER_SIZE    1
#define HMAT_SSLB_FLAG_NON_SEQENTIAL_TRANSFERS  2

#define PDTT_PCC_STRUCTURE_PDTT_PCC_SUB_CHANNEL_ID      (0xFF   << 0)
#define PDTT_PCC_STRUCTURE_RUNTIME                      (1      << 8)
#define PDTT_PCC_STRUCTURE_WAIT_FOR_COMPLETION          (1      << 9)
#define PDTT_PCC_STRUCTURE_TRIGGER_ORDER                (1      << 10)

#define PDTT_EXECUTE_PLATFORM_DEBUG_TRIGGER_DOORBELL_ONLY       0
#define PDTT_EXECUTE_PLATFORM_DEBUG_TRIGGER_VENDOR_SPECIFIC     1

#define PPTT_PROCESSOR_STRUCTURE_FLAG_PHYSICAL_PACKAGE          (1 << 0)
#define PPTT_PROCESSOR_STRUCTURE_FLAG_ACPI_PROCESSOR_VALID_ID   (1 << 1)
#define PPTT_PROCESSOR_STRUCTURE_FLAG_PROCESSOR_IS_THREAD       (1 << 2)
#define PPTT_PROCESSOR_STRUCTURE_FLAG_NODE_IS_LEAF              (1 << 3)
#define PPTT_PROCESSOR_STRUCTURE_FLAG_IDENTICAL_IMPLEMENTATION  (1 << 4)

#define PPTT_CACHE_STRUCTURE_FLAG_SIZE_PROPERTY_VALID           (1 << 0)
#define PPTT_CACHE_STRUCTURE_FLAG_NUMBER_OF_SET_VALID           (1 << 1)
#define PPTT_CACHE_STRUCTURE_FLAG_ASSOCIATIVITY_VALID           (1 << 2)
#define PPTT_CACHE_STRUCTURE_FLAG_ALLOCATION_TYPE_VALID         (1 << 3)
#define PPTT_CACHE_STRUCTURE_FLAG_CACHE_TYPE_VALID              (1 << 4)
#define PPTT_CACHE_STRUCTURE_FLAG_WRITE_POLICY_VALID            (1 << 5)
#define PPTT_CACHE_STRUCTURE_FLAG_LINE_POLICY_VALID             (1 << 6)
#define PPTT_CACHE_STRUCTURE_FLAG_CACHE_ID_VALID                (1 << 7)

#define PHAT_PHAR_FIRMWARE_VERSION_SATA_RECORD  0
#define PHAT_PHAR_FIRMWARE_HEALTH_DATA_RECORD   1

#define PHAT_FHDR_AM_HEALTHY_ERRORS_FOUND       0
#define PHAT_FHDR_AM_HEALTHY_NO_ERRORS_FOUND    1
#define PHAT_FHDR_AM_HEALTHY_UNKOWN             2
#define PHAT_FHDR_AM_HEALTHY_ADVISORY           3

#define PHAT_RRHR_SUPPORTED_SOURCES_UNKOWN_SOURCE       (1 << 0)
#define PHAT_RRHR_SUPPORTED_SOURCES_HARDWARE_SOURCE     (1 << 1)
#define PHAT_RRHR_SUPPORTED_SOURCES_FIRMWARE_SOURCE     (1 << 2)
#define PHAT_RRHR_SUPPORTED_SOURCES_SOFTWARE_SOURCE     (1 << 3)
#define PHAT_RRHR_SUPPORTED_SOURCES_SUPERVISOR_SOURCE   (1 << 4)

#define PHAT_RRHR_SOURCE_UNKOWN_SOURCE              (1 << 0)
#define PHAT_RRHR_SOURCE_HARDWARE_SOURCE            (1 << 1)
#define PHAT_RRHR_SOURCE_FIRMWARE_SOURCE            (1 << 2)
#define PHAT_RRHR_SOURCE_SOFTWARE_INITIATED_RESET   (1 << 3)
#define PHAT_RRHR_SOURCE_SUPERVISOR_INITIATED_RESET (1 << 4)



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

typedef struct __attribute__((packed)) _GENERAL_ADRESS_STRUCTURE{//GAS
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
    char                                                    Signature[4];   //4
    uint32_t                                                Length;         //8
    uint8_t                                                 Revision;       //9
    uint8_t                                                 Checksum;       //10
    char                                                    OemID[6];       //16
    char                                                    OemTableID[8];  //24
    uint32_t                                                OemRevision;    //28
    uint32_t                                                CreatorID;      //32
    uint32_t                                                CreatorRevision;//36
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
    TABLE_DESCRIPTION_HEADER    FadtHeader;
    uint32_t                    FacsTablePhyPointer; //
    uint32_t                    DsdtTablePhyPointer; 
    uint8_t                     Reserved1;
    uint8_t                     PreferedPowerMode;
    uint16_t                    Sci8259PicInt;
    uint32_t                    SmiCommandPort;
    uint8_t                     AcpiEnable;
    uint8_t                     AcpiDisable;
    uint8_t                     S4BiosRequestValue;
    uint8_t                     ProcessorStateControlValue;
    uint32_t                    Pm1AEventRegisterBlockAddress;
    uint32_t                    Pm1BEventRegisterBlockAddress;
    uint32_t                    Pm1AControlRegisterBlockAddress;
    uint32_t                    Pm1BControlRegisterBlockAddress;
    uint32_t                    Pm2ControlRegisterBlockAddress;
    uint32_t                    PmTimerControlRegisterBlock;
    uint32_t                    GeneralPurposeEventBlock0;
    uint32_t                    GeneralPurposeEventBlock1;
    uint8_t                     Pm1EventLength;
    uint8_t                     Pm1ControlLength;
    uint8_t                     Pm2ControlLength;
    uint8_t                     PmTimerLength;
    uint8_t                     GeneralPurposeEventBlock0Length;
    uint8_t                     GeneralPurposeEventBlock1Length;
    uint8_t                     GeneralPurposeEventBase;
    uint8_t                     CstCount;
    uint16_t                    PmLevel2Latency;
    uint16_t                    PmLevel3Latency;
    uint16_t                    FlushSize;
    uint16_t                    FlushStride;
    uint8_t                     DutyOffset;
    uint8_t                     DutyWidth;
    uint8_t                     DayAlarm;
    uint8_t                     MonthAlarm;
    uint8_t                     Century;
    uint16_t                    IAPCBootArch;
    uint8_t                     Reserved2;
    uint32_t                    FeatureFlags;
    GENERAL_ADRESS_STRUCTURE    ResetRegister;
    uint8_t                     ResetValue;
    uint16_t                    ArmBootArch;
    uint8_t                     FadtMinorVersion; //major revision is in the Revision in the FadtHeader
    uint64_t                    XFirmwareControl;
    uint64_t                    XDsdtPhyAddress;
    GENERAL_ADRESS_STRUCTURE    XPm1AEventRegisterBlock;
    GENERAL_ADRESS_STRUCTURE    XPm1BEventRegisterBlock;
    GENERAL_ADRESS_STRUCTURE    XPm1AControlRegisterBlock;
    GENERAL_ADRESS_STRUCTURE    XPm1BControlRegisterBlock;
    GENERAL_ADRESS_STRUCTURE    XPm2ControlRegisterBlock;
    GENERAL_ADRESS_STRUCTURE    XPmTimerRegisterBlock;
    GENERAL_ADRESS_STRUCTURE    XGeneralPurposeEvent0;
    GENERAL_ADRESS_STRUCTURE    XGeneralPurposeEvent1;
    GENERAL_ADRESS_STRUCTURE    SleepStatusRegister;
    uint64_t                    HypervisorVendorIdentity;
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

typedef struct __attribute__((packed)) _S3_PERFROMANCE_TABLE_HEADER{
    char                        Signature[4];
    uint32_t                    Length;
}S3_PERFROMANCE_TABLE_HEADER, * PS3_PERFROMANCE_TABLE_HEADER;

typedef struct __attribute__((packed)) _BASIC_S3_RESUME_PERFORMANCE_RECORD{
    uint16_t                    RuntimePerformanceRecord;
    uint8_t                     RecordLength;
    uint8_t                     Revision;
    uint32_t                    ResumeCount;
    uint64_t                    FullResume;
    uint64_t                    AverageResume;
}BASIC_S3_RESUME_PERFORMANCE_RECORD, * PBASIC_S3_RESUME_PERFORMANCE_RECORD; 

typedef struct __attribute__((packed)) _BASIC_S3_SUSPEND_PERFORMANCE_RECORD{
    uint16_t                    RuntimePerformanceRecord;
    uint8_t                     RecordLength;
    uint8_t                     Revision;
    uint64_t                    SuspendStart;
    uint64_t                    SuspendEnd;
}BASIC_S3_SUSPEND_PERFORMANCE_RECORD, * PBASIC_S3_SUSPEND_PERFORMANCE_RECORD;

typedef struct __attribute__((packed)) _GENERIC_TIMER_DESCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER    GtdtHeader;
    uint64_t                    CounterControlBase;
    uint32_t                    Reserved;
    uint32_t                    SecureELITimerGsi;
    uint32_t                    SecureELITimerFlags;
    uint32_t                    NonSecureELITimerGsi;
    uint32_t                    NonSecureELITimerFlags;
    uint32_t                    VirtualELITimerGsi;
    uint32_t                    VirtualELITimerFlags;
    uint32_t                    EL2TimerGsi;
    uint32_t                    EL2TimerFlags;
    uint64_t                    CounterReadBase;
    uint32_t                    PlatformTimerCount;
    uint32_t                    PlatformTimerOffset;
    uint32_t                    VirtualEL2TimerGsi;
    uint32_t                    VirtualEL2TimeFlags;
    uint8_t                     PlatformTimerStruct[];
}GENERIC_TIMER_DESCRIPTION_TABLE, * PGENERIC_TIMER_DESCRIPTION_TABLE;

typedef struct __attribute__((packed)) _GTDT_GT_BLOCK_TIMER_STRUCTURE{
    uint8_t     GtFrameNumber;
    uint8_t     Reserved1[3];
    uint64_t    CountControlBaseX;
    uint64_t    CountEL0BaseX;
    uint32_t    GTxPhysicalTimerGsi;
}GTDT_GT_BLOCK_TIMER_STRUCTURE, * PGTDT_GT_BLOCK_TIMER_STRUCTURE;

typedef struct __attribute__((packed)) _GTDT_GT_BLOCK_STRUCUTRE{
    uint8_t                         Type;
    uint16_t                        Length;
    uint8_t                         Reserved;
    uint64_t                        CountControlBase;
    uint32_t                        GtBlobkTimerCount;
    uint32_t                        GtBlovkTimerOffset;
    GTDT_GT_BLOCK_TIMER_STRUCTURE   GtBlockTimerData[];
}GTDT_GT_BLOCK_STRUCUTRE, * PGTDT_GT_BLOCK_STRUCUTRE;

typedef struct __attribute__((packed)) _GTDT_ARM_GENERIC_WATCHDOG_STRUCUTRE{
    uint8_t     Type;
    uint16_t    Length;
    uint8_t     Reserved1;
    uint64_t    RefreshFramePhyAddress;
    uint64_t    WatchdogControlFramePhyAddress;
    uint32_t    WatchdogTimerGsi;
    uint32_t    WatchdogTimerFlags;
}GTDT_ARM_GENERIC_WATCHDOG_STRUCUTRE, * PGTDT_ARM_GENERIC_WATCHDOG_STRUCUTRE;

typedef struct __attribute__((packed)) _NVDIMM_FIRMWARE_INTERFACE_TABLE{
    TABLE_DESCRIPTION_HEADER        NFitHeader;
    uint32_t                        Reserved;
    uint8_t                         NFitBuffer[];
}NVDIMM_FIRMWARE_INTERFACE_TABLE, * PNVDIMM_FIRMWARE_INTERFACE_TABLE;

typedef struct __attribute__((packed)) _NFIT_SPA_RANGE_STRUCTURE{
    uint16_t    Type;
    uint16_t    Length;
    uint16_t    SPARangeIndex;
    uint16_t    Flags;
    uint32_t    Reserved1;
    uint32_t    ProximityDomain;
    uint8_t     AddressRangeTypeGUID[16];
    uint64_t    SystemPhysicalAddressRangeBase;
    uint64_t    SystemPhysicalAddressRangeLength;
    uint64_t    AddressRangeMemoryMappingAttribute;
    uint64_t    SpaLocationCookie;
}NFIT_SPA_RANGE_STRUCTURE, * PNFIT_SPA_RANGE_STRUCTURE;

typedef struct __attribute__((packed)) _NFIT_NVDIMM_REGION_MAPPING{
    uint16_t    Type;
    uint16_t    Length;
    uint32_t    NFITDeviceHandle;
    uint16_t    NVDIMMPhysicalID;
    uint16_t    NVDIMMRegionID;
    uint16_t    SpaRangeStructureIndex;
    uint16_t    NVDIMMControlRegionIndex;
    uint64_t    NVDIMMRegionSize;
    uint64_t    RegionOffset;
    uint64_t    NVDIMMPhysicalAddressRegionBase;
    uint16_t    InterleaveStructureINdex;
    uint16_t    InterleaveWays;
    uint16_t    NVDIMMStateFlags;
    uint16_t    Reserved2;
}NFIT_NVDIMM_REGION_MAPPING, * PNFIT_NVDIMM_REGION_MAPPING;

typedef struct __attribute__((packed)) _NFIT_INTERLEAVE_STRUCTURE{
    uint16_t    Type;
    uint16_t    Length;
    uint16_t    InterleaveIndex;
    uint16_t    Reserved1;
    uint32_t    NumberOfLines;
    uint32_t    LineSize;
    uint32_t    Line1Offset;
    uint32_t    FOOBAR;
    uint32_t    LineMOffset[];
}NFIT_INTERLEAVE_STRUCTURE, * PNFIT_INTERLEAVE_STRUCTURE;

typedef struct __attribute__((packed)) _NFIT_SMBIOS_INFORMATION_STRUCTURE{
    uint16_t    Type;
    uint16_t    Length;
    uint32_t    Reserved1;
    uint8_t     Data[];
}NFIT_SMBIOS_INFORMATION_STRUCTURE, * PNFIT_SMBIOS_INFORMATION_STRUCTURE;

typedef struct __attribute__((packed)) _NFIT_NVDIMM_CONTROL_REGION_STRUCTURE{
    uint16_t    Type;
    uint16_t    Length;
    uint16_t    NVDIMMControlRegionIndex;
    uint16_t    VendorID;
    uint16_t    DeviceID;
    uint16_t    RevsionID;
    uint16_t    SubVendorID;
    uint16_t    SubDeviceID;
    uint16_t    SubRevionID;
    uint8_t     ValidFeilds;
    uint8_t     ManufacturingLocations;
    uint16_t    ManufacturingDate;
    uint16_t    Reserved1;
    uint32_t    SerialNumber;
    uint16_t    RegionFormatInterfaceCode;
    uint16_t    NumberOfBlockControlWindows;
    uint64_t    SizeOfBlockControlWindow;
    uint64_t    CommandRegisterOffset;
    uint64_t    CommandRegisterSize;
    uint64_t    StatusRegisterOffset;
    uint64_t    StatusRegisterSize;
    uint16_t    NVDIMMControlRegionFlag;
    uint8_t     Reserved2[6];
}NFIT_NVDIMM_CONTROL_REGION_STRUCTURE, * PNFIT_NVDIMM_CONTROL_REGION_STRUCTURE;

typedef struct __attribute__((packed)) _NFIT_NVDIMM_BLOCK_DATA_WINDOWS_REGION{
    uint16_t    Type;
    uint16_t    Length;
    uint16_t    NVDIMMControlRegionIndex;
    uint16_t    NumberOfBlockDataWindows;
    uint64_t    BlockDataWindowStartOffset;
    uint64_t    BlockDataWindowsSize;
    uint64_t    BlockAccessableMemoryCapacity;
    uint64_t    AddressOfFirstBlock;
}NFIT_NVDIMM_BLOCK_DATA_WINDOWS_REGION, * PNFIT_NVDIMM_BLOCK_DATA_WINDOWS_REGION;

typedef struct __attribute__((packed)) _NFIT_FLUSH_HINT_ADDRESS{
    uint16_t    Type;
    uint16_t    Length;
    uint32_t    NFITDeviceHandle;
    uint16_t    FluchHintAddressCount;
    uint8_t     Reserved1[6];
    uint64_t    HintAddress1;
    uint64_t    FOOBAR;
    uint64_t    FlushHintM[];
}NFIT_FLUSH_HINT_ADDRESS, * PNFIT_FLUSH_HINT_ADDRESS;

typedef struct __attribute__((packed)) _NFIT_PLATFORM_CAPABILITIES{
    uint16_t Type;
    uint16_t Length;
    uint8_t  HighValidCap;
    uint8_t  Reserved1[3];
    uint32_t Capabilities;
    uint32_t Reserved2;
}NFIT_PLATFORM_CAPABILITIES, * PNFIT_PLATFORM_CAPABILITIES;

typedef struct __attribute__((packed)) _SECURE_DEVICES_TABLE{
    TABLE_DESCRIPTION_HEADER    SdevHeader;
    uint8_t                     SecureDeviceData[];
}SECURE_DEVICES_TABLE, * PSECURE_DEVICES_TABLE;

typedef struct __attribute__((packed)) _SDEV_ACPI_NAMESPACE_DEVICE_STRUCUTRE{
    uint8_t                     Type;
    uint8_t                     Flags;
    uint16_t                    Length;
    uint16_t                    DeviceIdentifierOffset;
    uint16_t                    DeviceIdentifierLength;
    uint16_t                    VendorSpecificDataOffset;
    uint16_t                    VendorSpecificDataLength;
    uint16_t                    SecureAccessComponentOffset;
    uint16_t                    SecureAccessComponentLength;
}SDEV_ACPI_NAMESPACE_DEVICE_STRUCUTRE, * PSDEV_ACPI_NAMESPACE_DEVICE_STRUCUTRE;

typedef struct __attribute__((packed)) _SDEV_SECURE_ACCESS_COMPONENT_ID_BASED{
    uint8_t                     Type;
    uint8_t                     Flags;
    uint16_t                    Length;
    uint16_t                    HardwareIDOffset;
    uint16_t                    HardwareIDLength;
    uint16_t                    SusbsystemIDOffset;
    uint16_t                    SusbsystemIDLength;
    uint16_t                    HardwareRevision;
    uint8_t                     HardwareRevisionPresent;
    uint8_t                     ClassCodePresent;
    uint8_t                     PciCompatibleBaseClass;
    uint8_t                     PciCompatibleSubClass;
    uint8_t                     PciCompatibleProgIF;
}SDEV_SECURE_ACCESS_COMPONENT_ID_BASED, * PSDEV_SECURE_ACCESS_COMPONENT_ID_BASED;

typedef struct __attribute__((packed)) _SDEV_SECURE_ACCESS_COMPONENT_MEMORY_BASED{ 
    uint8_t     Type;
    uint8_t     Flags;
    uint16_t    Length;
    uint32_t    Reserved1;
    uint64_t    MemoryBaseAddress;
    uint64_t    MemoryLength;
}SDEV_SECURE_ACCESS_COMPONENT_MEMORY_BASED, * PSDEV_SECURE_ACCESS_COMPONENT_MEMORY_BASED;

typedef struct __attribute__((packed)) _SDEV_PCIE_ENDPOINT_DEVICE{
    uint8_t     Type;
    uint8_t     Flags;
    uint16_t    Length;
    uint16_t    PciGroup;
    uint16_t    PciBus;
    uint16_t    PciPathOffset;
    uint16_t    PciPathLength;
    uint16_t    VendorSpecificDataOffset;
    uint16_t    VendorSpecificDataLength;
}SDEV_PCIE_ENDPOINT_DEVICE, * PSDEV_PCIE_ENDPOINT_DEVICE;

typedef struct __attribute__((packed)) _HETEROGENEOUS_MEMORY_ATTRIBUTE_TABLE{
    TABLE_DESCRIPTION_HEADER    HmatHeader;
    uint32_t                    Reserved;
    uint8_t                     HmatData[];
}HETEROGENEOUS_MEMORY_ATTRIBUTE_TABLE, * PHETEROGENEOUS_MEMORY_ATTRIBUTE_TABLE;

typedef struct __attribute__((packed)) _HMAT_MEMORY_PROXIMITY_DOMAIN_STRUCTURE{
    uint16_t    Type;
    uint16_t    Reserved1;
    uint32_t    Length;
    uint16_t    Flags;
    uint16_t    Reserved2;
    uint32_t    AttachedInitiatorDomain;
    uint32_t    MemoryDomain;
    uint8_t     Reserved3[20];
}HMAT_MEMORY_PROXIMITY_DOMAIN_STRUCTURE, * PHMAT_MEMORY_PROXIMITY_DOMAIN_STRUCTURE;

typedef struct __attribute__((packed)) _HMAT_SSLB_FLAG_STRUCTURE{
    uint8_t MemoryHierarchy     : 4;
    uint8_t AccessAttributes    : 2;
    uint8_t Reserved            : 2;
}HMAT_SSLB_FLAG_STRUCTURE, * PHMAT_SSLB_FLAG_STRUCTURE;

typedef union __attribute__((packed)) _HMAT_SSLB_FLAGS{
    uint8_t                     FlatValue;
    HMAT_SSLB_FLAG_STRUCTURE    SpecFlags;
}HMAT_SSLB_FLAGS, * PHMAT_SSLB_FLAGS;

typedef struct __attribute__((packed)) _HMAT_SYSTEM_LOCALITY_LATENCY_BANDWITH_STRUCTURE{
    uint16_t    Type;
    uint16_t    Reserved1;
    uint32_t    Length;
    uint8_t     Flags;
    uint8_t     DataType;
    uint8_t     MinimumTransferSize;
    uint8_t     Reserved2;
    uint32_t    InitiatorProximityDomainCount;
    uint32_t    TargetProximityDomainCount;
    uint32_t    Reserved3;
    uint64_t    EntryBaseUnit;
    uint8_t     DataBuffer[];
}HMAT_SYSTEM_LOCALITY_LATENCY_BANDWITH_STRUCTURE, * PHMAT_SYSTEM_LOCALITY_LATENCY_BANDWITH_STRUCTURE;

typedef struct __attribute__((packed)) _HMAT_MSC_CACHE_ATTRIBUTE_STRUCTURE{
    uint32_t    CacheLevelCount         : 4;
    uint32_t    CacheLevel              : 4;
    uint32_t    CacheAssociativiy       : 4;
    uint32_t    WritePolicy             : 4;
    uint32_t    CacheLineSize           : 16;
}HMAT_MSC_CACHE_ATTRIBUTE_STRUCTURE, * PHMAT_MSC_CACHE_ATTRIBUTE_STRUCTURE;

typedef union __attribute__((packed)) _HMA_MSC_CACHE_ATTRIBUTES{
    uint32_t                                FlatValue;
    HMAT_MSC_CACHE_ATTRIBUTE_STRUCTURE      SpecFlags;
}HMA_MSC_CACHE_ATTRIBUTES, * PHMA_MSC_CACHE_ATTRIBUTES;

typedef struct __attribute__((packed)) _HMAT_MEMORY_SIDE_CACHE_STRUCTURE{
    uint16_t                    Type;
    uint16_t                    Reserved1;
    uint32_t                    Length;
    uint32_t                    MemoryProximityDomains;
    uint32_t                    Reserved2;
    uint64_t                    MemorySideCacheSize;
    HMA_MSC_CACHE_ATTRIBUTES    CacheAttributes;
    uint16_t                    SmbiosHandleCount;
    uint8_t                     DataBuffer[];
}HMAT_MEMORY_SIDE_CACHE_STRUCTURE, * PHMAT_MEMORY_SIDE_CACHE_STRUCTURE;

typedef struct __attribute__((packed)) _PLATFORM_DEBUG_TRIGGER_TABLE{
    TABLE_DESCRIPTION_HEADER    PdttHeader;
    uint8_t                     TriggerCount;
    uint8_t                     Reserved1[3];
    uint32_t                    TriggerIdentifierArray;
    uint8_t                     PCCBuffer;
}PLATFORM_DEBUG_TRIGGER_TABLE, * PPLATFORM_DEBUG_TRIGGER_TABLE;

typedef struct __attribute__((packed)) _PDTT_PCC_SHARED_MEMORY_STRUCTURE{
    uint8_t     Signature[4];
    uint8_t     VendorSpecificData[];
}PDTT_PCC_SHARED_MEMORY_STRUCTURE, * PPDTT_PCC_SHARED_MEMORY_STRUCTURE;

typedef struct __attribute__((packed)) _PDTT_PLATFOMR_COMMUNICATION_CHANNEL{
    uint8_t     Signature[4];
    uint16_t    Command;
    uint16_t    Status;
    uint8_t     VendorSpecific[];
}PDTT_PLATFOMR_COMMUNICATION_CHANNEL, * PPDTT_PLATFOMR_COMMUNICATION_CHANNEL;

typedef struct __attribute__((packed)) _PROCESSOR_PROPERTIES_TOPOLOGY_TABLE{
    TABLE_DESCRIPTION_HEADER    PpttHeader;
    uint8_t                     TableData[];
}PROCESSOR_PROPERTIES_TOPOLOGY_TABLE, * PPROCESSOR_PROPERTIES_TOPOLOGY_TABLE;

typedef struct __attribute__((packed)) _PPTT_PROCESSOR_HIERARCHY_NODE{
    uint8_t     Type;
    uint8_t     Length;
    uint16_t    Reserved1;
    uint32_t    Flags;
    uint32_t    Parent;
    uint32_t    AcpiProcessorID;
    uint32_t    PrivateResourceCount;
    uint32_t    PRivateResources[];
}PPTT_PROCESSOR_HIERARCHY_NODE, * PPPTT_PROCESSOR_HIERARCHY_NODE;

typedef struct __attribute__((packed)) _PPTT_CACHE_TYPE_ATTRIBUTE_STRUCTURE{
    uint8_t     AllocationType  : 2;
    uint8_t     CacheType       : 2;
    uint8_t     WritePolicy     : 1;
    uint8_t     Reserved        : 3;
}PPTT_CACHE_TYPE_ATTRIBUTE_STRUCTURE, * PPPTT_CACHE_TYPE_ATTRIBUTE_STRUCTURE;

typedef union __attribute__((packed)) _PPTT_CACHE_TYPE_ATTRIBUTE{
    uint8_t                                 FlatValue;
    PPTT_CACHE_TYPE_ATTRIBUTE_STRUCTURE     SpecAttributes;
}PPTT_CACHE_TYPE_ATTRIBUTE, * PPPTT_CACHE_TYPE_ATTRIBUTE;

typedef struct __attribute__((packed)) _PPTT_CACHE_TYPE{
    uint8_t                     Type;
    uint8_t                     Length;
    uint16_t                    Reserved1;
    uint32_t                    Flags;
    uint32_t                    NextLevelCache;
    uint32_t                    Size;
    uint32_t                    NumberOfSets;
    uint8_t                     Associatives;
    PPTT_CACHE_TYPE_ATTRIBUTE   Attributes;
    uint16_t                    LineSize;
    uint32_t                    CacheID;
}PPTT_CACHE_TYPE, * PPPTT_CACHE_TYPE;

typedef struct __attribute__((packed)) _PLATFORM_HEALTH_ASSESMENT_TABLE{
    TABLE_DESCRIPTION_HEADER    PhatHeader;
    uint8_t                     PhatData[];
}PLATFORM_HEALTH_ASSESMENT_TABLE, * PPLATFORM_HEALTH_ASSESMENT_TABLE;

typedef struct __attribute__((packed)) _PHAT_PLATFORM_HEALTH_ASSESMENT_RECORD{
    uint16_t                    PlatformHealthAssesmentType;
    uint16_t                    Length;
    uint8_t                     Revision;
    uint8_t                     RecordData[];
}PHAT_PLATFORM_HEALTH_ASSESMENT_RECORD, * PPHAT_PLATFORM_HEALTH_ASSESMENT_RECORD;

typedef struct __attribute__((packed)) _PHAT_VERSION_ELEMENT{
    GUID                        ComponentID;
    uint64_t                    VersionValue;
    uint32_t                    ProducerID;
}PHAT_VERSION_ELEMENT, * PPHAT_VERSION_ELEMENT;

typedef struct __attribute__((packed)) _PHAT_FIRMWARE_VERSION_DATA_RECORD{
    uint16_t                    PlatformRecordType;
    uint16_t                    RecoreLength;
    uint8_t                     Revision;
    uint8_t                     Reserved[3];
    uint32_t                    RecordCount;
    uint8_t                     PhatVersionElement[];
}PHAT_FIRMWARE_VERSION_DATA_RECORD, * PPHAT_FIRMWARE_VERSION_DATA_RECORD;

typedef struct __attribute__((packed)) _PHAT_FIRMWARE_HEALTH_DATA_RECORD{
    uint16_t    PlatformRecordType;
    uint16_t    RecordLength;
    uint8_t     Revision;
    uint16_t    Reserved;
    uint8_t     AmHealthy;
    GUID        DeviceStructure;
    uint32_t    DeviceSpecificOffset;
    uint8_t     Buffer[];
}PHAT_FIRMWARE_HEALTH_DATA_RECORD, * PPHAT_FIRMWARE_HEALTH_DATA_RECORD; 

typedef struct __attribute__((packed)) _PHAT_REASON_HEALTH_RECORD{
    uint16_t    PlatformRecordType;
    uint16_t    RecordLength;
    uint8_t     Revision;
    uint16_t    Reserved;
    uint8_t     AmHealthy;
    GUID        DeviceStructure;
    uint32_t    DeviceSpecificDataPffset;
    uint8_t     DevicePath[8];
    uint8_t     DeviceData[];
}PHAT_REASON_HEALTH_RECORD, * PPHAT_REASON_HEALTH_RECORD;

typedef struct __attribute__((packed)) _PHAT_RESET_REASON_HEALTH_RECORD{
    uint8_t     SupportedSources;
    uint8_t     Source;
    uint8_t     SubSource;
    uint8_t     Reason;
    uint16_t    VendorCount;
    uint8_t     VendorSpecificData[];
}PHAT_RESET_REASON_HEALTH_RECORD, * PPHAT_RESET_REASON_HEALTH_RECORD;

typedef struct __attribute__((packed)) _PHAT_RESET_REASON_HEALTH_RECORD_DATA_ENTRY{
    GUID        VenodrDataID;
    uint16_t    Length;
    uint16_t    Revision;
    uint8_t     Data[];
}PHAT_RESET_REASON_HEALTH_RECORD_DATA_ENTRY, * PPHAT_RESET_REASON_HEALTH_RECORD_DATA_ENTRY;

typedef struct __attribute__((packed)) _VIRTUAL_IO_TRANSLATION_TABLE{
    TABLE_DESCRIPTION_HEADER    ViotTable;
    uint16_t                    NodeCount;
    uint16_t                    NodeOffset;
    uint64_t                    Reserved;
    uint8_t                     NodeList[];    
}VIRTUAL_IO_TRANSLATION_TABLE, * PVIRTUAL_IO_TRANSLATION_TABLE;

typedef struct __attribute__((packed)) _PCI_RANGENODE_STRUCTURE{
    uint8_t     Type;
    uint8_t     Reserved1;
    uint16_t    Length;
    uint32_t    EndpointStart;
    uint16_t    SegmentStart;
    uint16_t    SegmentEnd;
    uint16_t    BDFStart;
    uint16_t    BDFEnd;
    uint16_t    OutputNode;
    uint8_t     Reserved2[16];
}PCI_RANGENODE_STRUCTURE, * PPCI_RANGENODE_STRUCTURE;

typedef struct __attribute__((packed)) _SINGLE_MMIO_ENDPOINT_NODE_STRUCTURE{
    uint8_t     Type;
    uint8_t     Reserved1;
    uint16_t    Length;
    uint32_t    EndpointID;
    uint64_t    BaseAddress;
    uint16_t    OutputNode;
    uint8_t     Reserved2[6];
}SINGLE_MMIO_ENDPOINT_NODE_STRUCTURE, * PSINGLE_MMIO_ENDPOINT_NODE_STRUCTURE;

typedef struct __attribute__((packed)) _VIRTIO_PCI_NODE_STRUCTURE{
    uint8_t     Type;
    uint8_t     Reserved1;
    uint16_t    Length;
    uint16_t    Segment;
    uint16_t    BDFNumber;
    uint64_t    Reserved2;
}VIRTIO_PCI_NODE_STRUCTURE, * PVIRTIO_PCI_NODE_STRUCTURE;

typedef struct __attribute__((packed)) _VIRTIO_MMIO_NODE_STRUCTURE{
    uint8_t     Type;
    uint8_t     Reserved1;
    uint16_t    Length;
    uint32_t    Reserved2;
    uint64_t    BaseAddress;
}VIRTIO_MMIO_NODE_STRUCTURE, * PVIRTIO_MMIO_NODE_STRUCTURE;

typedef struct __attribute__((packed)) _MISC_GUIDED_TABLE_ENTRIES{
    TABLE_DESCRIPTION_HEADER    MiscHeader;
    uint8_t                     Entries;
}MISC_GUIDED_TABLE_ENTRIES, * PMISC_GUIDED_TABLE_ENTRIES;

typedef struct __attribute__((packed)) _MISC_GUIDED_ENTRY_FORMAT{
    GUID        EntryID;
    uint32_t    EntryLength;
    uint32_t    Revision;
    uint32_t    ProducerID;
    uint8_t     Data[];
}MISC_GUIDED_ENTRY_FORMAT, * PMISC_GUIDED_ENTRY_FORMAT;

typedef struct __attribute__((packed)) _CC_EVENT_LOG_ACPI_TABLE{
    TABLE_DESCRIPTION_HEADER    CcelHeader;
    uint8_t                     CcType;
    uint8_t                     CcSubType;
    uint16_t                    Reserved1;
    uint64_t                    LogAreaMinimalLength;
    uint64_t                    LogAreaStartAddress;
}CC_EVENT_LOG_ACPI_TABLE, * PCC_EVENT_LOG_ACPI_TABLE;

typedef struct __attribute__((packed)) _SKVL_KEY_STRUCTURE{
    uint16_t    KeyType;
    uint16_t    KeyFormat;
    uint32_t    KeySize;
    uint64_t    KeyAddress;
}SKVL_KEY_STRUCTURE, * PSKVL_KEY_STRUCTURE;

typedef struct __attribute__((packed)) _STORAGE_VOLUME_KEY_LOCATION_TABLE{
    TABLE_DESCRIPTION_HEADER    SkvlHeader;
    uint32_t                    KeyCount;
    SKVL_KEY_STRUCTURE          KeyStructure[];
}STORAGE_VOLUME_KEY_LOCATION_TABLE, * PSTORAGE_VOLUME_KEY_LOCATION_TABLE;
 
typedef union _LOU_ACPI_TABLE_POINTER_UNION{
    PFIXED_ACPI_DESCRIPTION_TABLE               Fadt;
    PFIRMWARE_ACPI_CONTROL_STRUCTURE_TABLE      Facs;
    PDIFFERETIATED_SYSTEM_DESCRIPTION_TABLE     Dsdt;
}LOU_ACPI_TABLE_POINTER_UNION, * PLOU_ACPI_TABLE_POINTER_UNION;

#ifdef __cplusplus
}
#endif
#endif