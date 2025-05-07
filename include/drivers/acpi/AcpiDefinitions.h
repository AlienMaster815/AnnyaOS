#ifndef _ACPI_DEFINITIONS_H
#define _ACPI_DEFINITIONS_H

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

#define FOR_EACH_PXSDT_ENTRY(XSDT) for(size_t XsdtEntry = 0 ; XsdtEntry < ((XSDT->RsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER)) / 8); XsdtEntry++)
#define FOR_EACH_XSDT_ENTRY(XSDT) for(size_t XsdtEntry = 0 ; XsdtEntry < ((XSDT.RsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER)) / 8); XsdtEntry++)

#define FADT_FEATURE_FLAG_WBINVD        (1 << 0)
#define FADT_FEATURE_FLAG_WBINVD_FLUSH  (1 << 1)
#define FADT_FEATURE_FLAG_PROC_C1       (1 << 2)
#define FADT_FEATURE_FLAG_PLVL2_UP      (1 << 3)
#define FADT_FEATURE_FLAG_POWER_BUTTON  (1 << 4)
#define FADT_FEATURE_FLAG_SLEEP_BUTTON  (1 << 5)


typedef union _GAS_ADDRES_SPACE{
    uint64_t SystemMemoryAddress;
    uint64_t SystemIoAddress;
    struct __attribute__((packed)){
        //64 bit is LE 0 bit first and is confined by bus and group 0
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
    uint8_t             AddressSpaceID;
    uint8_t             RegisterWidth; //bits
    uint8_t             RegisterOffset;//bits
    uint8_t             AccessSize;
    GAS_ADDRES_SPACE    Address;
}GENERAL_ADRESS_STRUCTURE, * PGENERAL_ADRESS_STRUCTURE;

typedef struct __attribute__((packed)) _ROOT_SYSTEM_DISCRIPTION_POINTER{
    char                Signature[8];
    uint8_t             Checksum;
    char                OemID[6];
    uint8_t             Revision;
    uint32_t            RsdtAddress;
    uint32_t            RsdtLength;
    uint64_t            XsdtAddress;
    uint8_t             ExtendedChecksum;
    uint8_t             Reserved[3];
}ROOT_SYSTEM_DISCRIPTION_POINTER, * PROOT_SYSTEM_DISCRIPTION_POINTER;

typedef struct __attribute__((packed)) _TABLE_DESCRIPTION_HEADER{
    char                Signature[4];
    uint32_t            Length;
    uint8_t             Revision;
    uint8_t             Checksum;
    char                OemID[6];
    char                OemTableID[8];
    uint32_t            OemRevision;
    uint32_t            CreatorID;
    uint32_t            CreatorRevision;
}TABLE_DESCRIPTION_HEADER, * PTABLE_DESCRIPTION_HEADER;

typedef struct __attribute__((packed)) _ROOT_SYSTEM_DISCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER        RsdtHeader;
    uint32_t                        DescriptionHeaders[];
}ROOT_SYSTEM_DISCRIPTION_TABLE, * PROOT_SYSTEM_DISCRIPTION_TABLE;

typedef struct __attribute__((packed)) _EXTENDED_SYSTEM_DESCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER        RsdtHeader;
    uint64_t                        DescriptionHeaders[];
}EXTENDED_SYSTEM_DESCRIPTION_TABLE, * PEXTENDED_SYSTEM_DESCRIPTION_TABLE;

typedef struct __attribute__((packed)) _FIXED_ACPI_DESCRIPTION_TABLE{
    TABLE_DESCRIPTION_HEADER        FadtHeader;
    uint32_t                        FacsTablePhyPointer; //FIRMWARE_ACPI_CONTROL_STRUCTURE
    uint32_t                        DsdtTablePhyPointer; 
    uint8_t                         Reserved1;
    uint8_t                         PreferedPowerMode;
    uint16_t                        Sci8259PicInt;
    uint32_t                        SmiCommandPort;
    uint8_t                         AcpiEnable;
    uint8_t                         AcpiDisable;
    uint8_t                         S4BiosRequestValue;
    uint8_t                         ProcessorStateControlValue;
    uint32_t                        Pm1AEventRegisterBlockAddress;
    uint32_t                        Pm1BEventRegisterBlockAddress;
    uint32_t                        Pm1AControlRegisterBlockAddress;
    uint32_t                        Pm1BControlRegisterBlockAddress;
    uint32_t                        Pm2ControlRegisterBlockAddress;
    uint32_t                        PmTimerControlRegisterBlock;
    uint32_t                        GeneralPurposeEventBlock0;
    uint32_t                        GeneralPurposeEventBlock1;
    uint8_t                         Pm1EventLength;
    uint8_t                         Pm1ControlLength;
    uint8_t                         Pm2ControlLength;
    uint8_t                         PmTimerLength;
    uint8_t                         GeneralPurposeEventBlock0Length;
    uint8_t                         GeneralPurposeEventBlock1Length;
    uint8_t                         GeneralPorposeEventBase;
    uint16_t                        PmLevel2Latence;
    uint16_t                        PmLevel3Latence;
    uint16_t                        FlushSize;
    uint16_t                        FlushStride;
    uint8_t                         DutyOffset;
    uint8_t                         DutyWidth;
    uint8_t                         DayAlarm;
    uint8_t                         MonthAlarm;
    uint8_t                         Century;
    uint16_t                        IAPCBootArch;
    uint8_t                         Reserved2;
    uint32_t                        FeatureFlags;
    uint8_t                         ResetRegister[12];
    uint8_t                         ResetValue;
    uint16_t                        ArmBootArch;
    uint8_t                         FadtMinorVersion; //major revision is in the Revision in the FadtHeader
    uint64_t                        XFirmwareControl;
    uint64_t                        XDsdtPhyAddress;
    uint8_t                         XPm1AEventRegisterBlock[12];
    uint8_t                         XPm1BEventRegisterBlock[12];
    uint8_t                         XPm1AControlRegisterBlock[12];
    uint8_t                         XPm1BControlRegisterBlock[12];
    uint8_t                         XPm2ControlRegisterBlock[12];
    uint8_t                         XPmTimerRegisterBlock[12];
    uint8_t                         XGeneralPurposeEvent0[12];
    uint8_t                         XGeneralPurposeEvent1[12];
    uint8_t                         SleepStatusRegister[12];
    uint64_t                        HypervisorVendorIdentity;
}FIXED_ACPI_DESCRIPTION_TABLE, * PFIXED_ACPI_DESCRIPTION_TABLE;



#ifdef __cplusplus
}
#endif
#endif