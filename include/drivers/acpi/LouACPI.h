#ifndef _ACPI_H
#define _ACPI_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif
#include <AcpiStructures.h>
#include <AcpiNameSpace.h>
#include <AcpiState.h>
#include <AcpiPMS.h>
#include <AcpiBattery.h>
#include <AcpiThermal.h>
#include <AcpiHr.h>


#define IF_ACPI_TABLE_IS(x, y) if(strncmp(x, y, 4) == 0)

void LouKeAcpiPrintTableSignature(void* TableBase);
void LouKeInitializeLouACPISubsystem();
void LouKeInitializeLouACPITable(void* TableBase);
void* LouKeAquireAcpiTable(string TableName);
void LouKeInitializeFixedAcpiDescriptionTable(void* TableBase);
uint8_t LouKeAcpiGetVersion();
void LouKeAcpiInitializeFacs(void* TableBase);
void LouKeAcpiInitializeDsdt(void* TableBase);

typedef enum{
    NO_DATA = 0,
    VENDOR_SPECIFIC_DATA_INFO = 1,
    FADT_TABLE_DATA_START = 2,
    PREFERED_POWER_MODE_PROFILE_INFO = 3,
    SCI_8259_PIC_INT_INFO = 4,
    SMI_COMMAND_PORT = 5,
    ACPI_ENABLE = 6,
    ACPI_DISABLE = 7,
    S4BIOS_REQUEST_VALUE = 8,
    PROCESSOR_STATE_CONTROL_VALUE = 9,
    PM1A_EVENT_REGISTER_BLOCK_ADDRESS = 10,
    PM1B_EVENT_REGISTER_BLOCK_ADDRESS = 11,
    PM1A_CONTROL_REGISTER_BLOCK_ADDRESS = 12,
    PM1B_CONTROL_REGISTER_BLOCK_ADDRESS = 13,
    PM2_CONTROL_REGISTER_BLOCK_ADDRESS = 14,
    PM_TIMER_CONTROL_REGISTER_BLOCK = 15,
    GENERAL_PURPOSE_EVENT_BLOCK0 = 16,
    GENERAL_PURPOSE_EVENT_BLOCK1 = 17,
    PM1_EVENT_LENGTH = 18,
    PM1_CONTROL_LENGTH = 19,
    PM_TIMER_LENGTH = 20,
    GENERAL_PURPOSE_EVENT_BLOCK0_LENGTH = 21,
    GENERAL_PURPOSE_EVENT_BLOCK1_LENGTH = 22,
    GENERAL_PURPOSE_EVENT_BASE = 23,
    CST_COUNT = 24,
    PM_LEVEL_2_LATENCY = 25,
    PM_LEVEL_3_LATENCY = 26,
    FADT_FLUSH_SIZE = 27,
    FADT_FLUSH_STRIDE = 28,
    FADT_DUTY_OFFSET = 29,
    FADT_DUTY_WIDTH = 30,
    FADT_DAY_ALARM = 31,
    FADT_MONTH_ALARM = 32,
    FADT_CENTURY = 33,
    FADT_IAPC_BOOT_ARCH = 34,
    FADT_FEATURE_FLAGS = 35,
    FADT_RESET_REGISTER = 36,
    FADT_RESET_VALUE = 37,
    FADT_ARM_BOOT_ARCH = 38,
    FADT_MINOR_VERSION = 39,
    FADT_SLEEP_STATUS_REGISTER = 40,
    FADT_HYPERVISOR_VENDOR_ID = 41,
    PM2_CONTROL_LENGTH = 42,
    FADT_TABLE_DATA_END = 43,
    FACS_TABLE_DATA_START = 44,
    FACS_HARDWARE_SIGNATURE = 45,
    FACS_FIRMWARE_WAKING_VECTOR = 46,
    FACS_GLOBAL_LOCK = 47,
    FACS_FLAGS = 48,
    FACS_VERSION = 49,
    FACS_OSPM_FLAGS = 50,
    FACS_TABLE_DATA_END = 51,
}LOU_ACPI_INFORMATION_ID;

typedef union _LOU_ACPI_GENERIC_HW_DEVICE_DATA{
    uint32_t                    StandardDevice;
    GENERAL_ADRESS_STRUCTURE    eXtendedDevice;
}LOU_ACPI_GENERIC_HW_DEVICE_DATA, * PLOU_ACPI_GENERIC_HW_DEVICE_DATA;

typedef struct _LOU_ACPI_GENERIC_HW_DEVICE{
    bool                                eXtendedDevice;
    LOU_ACPI_GENERIC_HW_DEVICE_DATA     HwDeviceData;
}LOU_ACPI_GENERIC_HW_DEVICE, * PLOU_ACPI_GENERIC_HW_DEVICE;

typedef union _LOU_ACPI_FADT_INFORMATION_DATA{
    uint8_t                         PreferedPowerMode;
    uint16_t                        Sci8259PicInt;
    LOU_ACPI_GENERIC_HW_DEVICE      SmiCommandPort;
    uint8_t                         AcpiEnable;
    uint8_t                         AcpiDisable;
    uint8_t                         S4BiosRequestValue;
    uint8_t                         ProcessorStateControlValue;
    LOU_ACPI_GENERIC_HW_DEVICE      Pm1AEventRegister;
    LOU_ACPI_GENERIC_HW_DEVICE      Pm1BEventRegister;
    LOU_ACPI_GENERIC_HW_DEVICE      Pm1AControlRegister;
    LOU_ACPI_GENERIC_HW_DEVICE      Pm1BControlRegister;
    LOU_ACPI_GENERIC_HW_DEVICE      Pm2ControlRegister;
    LOU_ACPI_GENERIC_HW_DEVICE      PmTimerControlRegister;
    LOU_ACPI_GENERIC_HW_DEVICE      GeneralPurposeEventBlock0;
    LOU_ACPI_GENERIC_HW_DEVICE      GeneralPurposeEventBlock1;
    uint8_t                         Pm1EventLength;
    uint8_t                         Pm1ControlLength;
    uint8_t                         Pm2ControlLength;
    uint8_t                         PmTimerLength;
    uint8_t                         GeneralPurposeEventBlock0Length;
    uint8_t                         GeneralPurposeEventBlock1Length;
    uint8_t                         GeneralPurposeEventBase;
    uint8_t                         CstCount;
    uint16_t                        PmLevel2Latency;
    uint16_t                        PmLevel3Latency;
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
    LOU_ACPI_GENERIC_HW_DEVICE      ResetRegister;
    uint8_t                         ResetValue;
    uint16_t                        ArmBootArch;
    uint8_t                         FadtMinorVersion;
    LOU_ACPI_GENERIC_HW_DEVICE      SleepStatusRegister;
    uint64_t                        HypervisorVendorIdentity;
}LOU_ACPI_FADT_INFORMATION_DATA, * PLOU_ACPI_FADT_INFORMATION_DATA;

typedef union _LOU_ACPI_FACP_INFORMATION_DATA{
    uint32_t    HardwareSignature;
    uint64_t    FirmwareWakingVector;
    uint32_t    GlobalLock;
    uint32_t    FeatureFlags;
    uint8_t     Version;
    uint32_t    OspmFlags;
}LOU_ACPI_FACP_INFORMATION_DATA, * PLOU_ACPI_FACP_INFORMATION_DATA;

typedef union _LOU_ACPI_INFORMATION_DATA{
    LOU_ACPI_FADT_INFORMATION_DATA Fadt;
    LOU_ACPI_FACP_INFORMATION_DATA Facs;
}LOU_ACPI_INFORMATION_DATA, * PLOU_ACPI_INFORMATION_DATA;

typedef struct _LOU_ACPI_INFORMATION{
    LOU_ACPI_INFORMATION_ID     InfoID;
    LOU_ACPI_INFORMATION_DATA   InfoData;
    void*                       VendorSpecifc;
}LOU_ACPI_INFORMATION, * PLOU_ACPI_INFORMATION, 
 LOU_ACPI_TABLE_OBJECT, * PLOU_ACPI_TABLE_OBJECT;

LOUSTATUS LouKeAcpiInformationQuery(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput);

static inline PFIXED_ACPI_DESCRIPTION_TABLE LouKeAcpiGetFadtTable(){
    return (PFIXED_ACPI_DESCRIPTION_TABLE)LouKeAquireAcpiTable(FIXED_ACPI_DESCRIPTION);
}

static inline PFIRMWARE_ACPI_CONTROL_STRUCTURE_TABLE LouKeAcpiGetFacsTable(){
    return (PFIRMWARE_ACPI_CONTROL_STRUCTURE_TABLE)LouKeAquireAcpiTable(FIRMWARE_ACPI_CONTROL_STRUCTURE);
}

static inline PDIFFERETIATED_SYSTEM_DESCRIPTION_TABLE LouKeAcpiGetDsdtTable(){
    return (PDIFFERETIATED_SYSTEM_DESCRIPTION_TABLE)LouKeAquireAcpiTable(DIFFERENTIATED_SYSTEM_DESCRIPTION);
}

static inline bool NonZeroGasValue(PGENERAL_ADRESS_STRUCTURE pGas){
    uint8_t* Foo = (uint8_t*)pGas;
    for(size_t i = 0 ; i < sizeof(GENERAL_ADRESS_STRUCTURE); i++){
        if(Foo[i]){
            return true;
        }
    }
    return false;
}

#include "TableParsing.h"



typedef struct _LOU_ACPI_NAMESPACE_OBJECT{
    ListHeader                              AmlTree;
    //struct _LOU_ACPI_NAMESPACE_OBJECT*      LastAmlTreeEntry;
    ListHeader                              ApendationTree;
    //struct _LOU_ACPI_NAMESPACE_OBJECT*      LastApendationTreeEntry;
    ListHeader                              SubTree;
    //struct _LOU_ACPI_NAMESPACE_OBJECT*      LastSubTreeEntry;
    string                                  Name;
    uint16_t                                Opcode;
    size_t                                  DataSize;
    uint8_t*                                Data;
}LOU_ACPI_NAMESPACE_OBJECT, * PLOU_ACPI_NAMESPACE_OBJECT, * NAMESPACE_HANDLE;

typedef enum {
    BUILD = 0,
    BUILD_CHILDREN = 1,
    SIZE_OF = 2,
    INVALID_OPCODE = 3,
}AML_INTERPRETER_EXECUTION_STATE;

typedef struct _LOU_ACPI_NAMESPACE_EXECUTION_CONTEXT{
    NAMESPACE_HANDLE                    CurrentDirectory;
    POOL                                AmlObjectPool;
    POOL                                NamePool;
    uint8_t*                            AmlStream;
    size_t                              Index;
    size_t                              Length;
    AML_INTERPRETER_EXECUTION_STATE     ExecutionState;
    uint64_t                            InputValue;
    bool                                InterpreterReturn;
    uint64_t                            ResultValue;
    LOU_ACPI_NAMESPACE_OBJECT           RootDirectory;
}LOU_ACPI_NAMESPACE_EXECUTION_CONTEXT, * PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT;

#define LouKeAcpiFreeNameSpaceObject(x) LouKeFree(x)

void InitializeDeferNamespaceObject(
    PLOU_ACPI_NAMESPACE_OBJECT NewObject
);

void LouKeAcpiCreateNameSpaceObject(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context,
    bool AddAsSubDirectory,
    string Name,
    uint16_t Opcode,
    size_t DataOffset,
    size_t ObjectSize
);

void LouKeAcpiNameSpaceAddChild(
    NAMESPACE_HANDLE CurrentDirectory,
    NAMESPACE_HANDLE NewStream
);

LOUSTATUS LouKeAcpiInterperateData(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiExecuteSubPackageContext(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context,
    NAMESPACE_HANDLE CurrentDirectory,
    size_t DataStart,
    size_t PackageLength
);

NAMESPACE_HANDLE LouKeAcpiGetNameSpaceHandle(string ObjectName, NAMESPACE_HANDLE CurrentHandle, uint16_t Opcode);
NAMESPACE_HANDLE LouKeAcpiSearchDeferHandles(string ObjectName);
NAMESPACE_HANDLE LouKeAcpiGetAcpiObjectHandle(string HandleName, NAMESPACE_HANDLE CurrentHandle);

#define AML_IS_ROOT  ((uint64_t)Context->CurrentDirectory == (uint64_t)&Context->RootDirectory)

void* LouKeAcpiMalloc(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context, 
    size_t AllocationSize 
);

#ifdef __cplusplus
}
#endif
#endif