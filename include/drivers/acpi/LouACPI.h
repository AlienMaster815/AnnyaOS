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

typedef struct _AML_EXECUTION_INTERNAL_PARAMETER_PASS{
    uint16_t    Opcode;
    uint64_t    DataLocation;
    uint64_t    DataSize;
}AML_EXECUTION_INTERNAL_PARAMETER_PASS, * PAML_EXECUTION_INTERNAL_PARAMETER_PASS;


typedef struct _LOU_ACPI_NAMESPACE_OBJECT{
    ListHeader                              AmlTree;
    struct _LOU_ACPI_NAMESPACE_OBJECT*      LastTreeEntry;
    ListHeader                              SubTree;
    struct _LOU_ACPI_NAMESPACE_OBJECT*      LastSubEntry;
    string                                  Name;
    uint16_t                                Opcode;
    size_t                                  DataSize;
    uint8_t*                                Data;
}LOU_ACPI_NAMESPACE_OBJECT, * PLOU_ACPI_NAMESPACE_OBJECT, * NAMESPACE_HANDLE;

typedef enum {
    BUILD = 0,
    BUILD_PARAMETER_PASS = 1,
    SIZE_OF = 2,
    EVALUATE = 3,
    INVALID_OPCODE = 4,
}AML_INTERPRETER_EXECUTION_STATE;

typedef struct _LOU_ACPI_NAMESPACE_EXECUTION_CONTEXT{
    NAMESPACE_HANDLE                            CurrentDirectory;
    POOL                                        AmlObjectPool;
    POOL                                        NamePool;
    uint8_t*                                    AmlStream;
    size_t                                      Index;
    size_t                                      Length;
    AML_INTERPRETER_EXECUTION_STATE             ExecutionState;
    PAML_EXECUTION_INTERNAL_PARAMETER_PASS      InputValue;
    uint64_t                                    InputSize;
    bool                                        InterpreterReturn;
    bool                                        InternalPassing;
    uint64_t                                    ResultValue;
    NAMESPACE_HANDLE                            RootDirectory;
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

LOUSTATUS LouKeAcpiExecuteMethod(
    NAMESPACE_HANDLE                        MethodHandle, 
    PAML_EXECUTION_INTERNAL_PARAMETER_PASS  MethodArguments,
    size_t                                  ArgCount
);

bool LouKeAcpiIsByteValidStringName(uint8_t byte);

size_t LouKeAcpiGetMethodParameterCount(
    NAMESPACE_HANDLE    MethodHandle
);

NAMESPACE_HANDLE LouKeAcpiCreateBasicAmlObject(uint16_t Opcode, uint64_t Data, size_t DataSize);
size_t LouKeAcpiGetTableCount();

typedef union _ACPI_SUB_TABLE_HEADERS{ 
    //these are Sub Headers that are 
    //used for Power Interfaces in Advanced 
    //Configuration Power Interface specification
    struct{
        uint8_t Type;
        uint8_t Length;
    }GenericHeader;
    HETEROGENEOUS_MEMORY_ATTRIBUTE_HEADER   HmatHeader;
    PLATFORM_RUNTIME_MECHANISM_HEADER       PrmtHeader;
    CXL_EARLY_DISCOVERY_HEADER              CedtHeader;
    CDAT_COMMON_HEADER                      CdatHeader;
}ACPI_SUB_TABLE_HEADERS, * PACPI_SUB_TABLE_HEADERS;

typedef LOUSTATUS (*ACPI_TABLE_ENTRY_HANDLER)(PACPI_SUB_TABLE_HEADERS, size_t);
typedef LOUSTATUS (*ACPI_TABLE_ENTRY_HANDLER_ARGS)(PACPI_SUB_TABLE_HEADERS, void*, size_t);

typedef struct _ACPI_SUB_TABLE_PROCESSOR{
    int                                     Id;
    ACPI_TABLE_ENTRY_HANDLER                Handler;
    ACPI_TABLE_ENTRY_HANDLER_ARGS           HandlerArgs;
    void*                                   Arguments;
    int                                     ReferenceCount;
}ACPI_SUB_TABLE_PROCESSOR, * PACPI_SUB_TABLE_PROCESSOR;

typedef union _FIRMWARE_TABLE_HEADER{
    TABLE_DESCRIPTION_HEADER                CommonTable;
    ACPI_CDAT_TABLE                         CdatTable;
}FIRMWARE_TABLE_HEADER, * PFIRMWARE_TABLE_HEADER;

typedef enum{
    ACPI_SUB_TABLE_COMMON   = 0,
    ACPI_SUB_TABLE_HMAT     = 'HMAT',
    ACPI_SUB_TABLE_PRMT     = 'PRMT',
    ACPI_SUB_TABLE_CEDT     = 'CEDT',
    ACPI_CDAT_SUB_TABLE     = 'CDAT',
}ACPI_SUB_TABLE_TYPE;

typedef struct _ACPI_SUB_TABLE_ENTRY{
    PACPI_SUB_TABLE_HEADERS     Header;
    ACPI_SUB_TABLE_TYPE         Type;
}ACPI_SUB_TABLE_ENTRY, * PACPI_SUB_TABLE_ENTRY;

#define PACPI_ECDT_TABLE PEMBEDDED_CONTROLLER_BOOT_RESOURCES_TABLE
#define ACPI_ECDT_TABLE  EMBEDDED_CONTROLLER_BOOT_RESOURCES_TABLE

typedef struct _ACPI_EC_TRANSACTION{
    uint8_t*        WriteData;
    uint8_t*        ReadData;
    uint16_t        IrqCount;
    uint8_t         Command;
    uint8_t         WriteIndex;
    uint8_t         ReadIndex;
    uint8_t         WriteLength;
    uint8_t         ReadLength;
    uint8_t         Flags;
}ACPI_EC_TRANSACTION, * PACPI_EC_TRANSACTION;

typedef enum{
    EC_EVENT_READY          = 0,
    EC_EVENT_IN_PROGRESS    = 1,
    EC_EVENT_COMPLETE       = 2,
}ACPI_EC_EVENT_STATE;

typedef struct _ACPI_EMBEDDED_CONTROLLER{
    void*                       Handle;
    int                         GPE;
    int                         Irq;
    uint64_t                    CommandAddress;
    uint64_t                    DataAddress;
    bool                        GlobalLock;
    uint64_t                    Flags;
    uint64_t                    ReferenceCount;
    mutex_t                     EcMutex;
    PLOUQ_WAIT                  WaitQueue;
    ListHeader                  List;
    PACPI_EC_TRANSACTION        CurrentTransaction;
    spinlock_t                  EcLock;
    PLOUQ_WORK                  WorkQueue;
    uint64_t                    TimeStamp;
    ACPI_EC_EVENT_STATE         EventState;
    uint32_t                    EventReady;
    uint32_t                    EventsProccessing;
    uint32_t                    EventsInProgress;
    bool                        PollingBusy;
    uint32_t                    PollingGuard;
}ACPI_EMBEDDED_CONTROLLER, * PACPI_EMBEDDED_CONTROLLER;

typedef struct _LOUACPI_BUFFER{
    SIZE    Length;
    PVOID   Pointer;   
}LOUACPI_BUFFER, * PLOUACPI_BUFFER;

typedef struct _ACPI_OSC_CONTEXT{
    GUID*           Uuid;
    INTEGER         Revision;
    LOUACPI_BUFFER  Capabilities;
    LOUACPI_BUFFER  Return;
}ACPI_OSC_CONTEXT, * PACPI_OSC_CONTEXT;

#define OSC_PCI_CAP_DWORDS  3
#define OSC_CXL_CAP_DWORDS  5

#define OSC_QUERY_DWORD         0
#define OSC_SUPPORT_DWORD       1
#define OSC_CONTROL_DWORD       2
#define OSC_EXT_SUPPORT_DWORD   3
#define OSC_EXT_CONTROL_DWORD   4

#define OSC_QUERY_ENABLE            0x01
#define OSC_REQUEST_ERROR           0x02
#define OSC_INVALID_UUID_ERROR      0x04
#define OSC_INVALID_REVISION_ERROR  0x08
#define OSC_CAP_MASK_ERROR          0x10

#define OSC_SB_PAD_SUPPORT			                0x01
#define OSC_SB_PPC_OST_SUPPORT			            0x02
#define OSC_SB_PR3_SUPPORT			                0x04
#define OSC_SB_HOTPLUG_OST_SUPPORT		            0x08
#define OSC_SB_APEI_SUPPORT			                0x10
#define OSC_SB_CPC_SUPPORT			                0x20
#define OSC_SB_CPCV2_SUPPORT			            0x40
#define OSC_SB_PCLPI_SUPPORT			            0x80
#define OSC_SB_OSLPI_SUPPORT			            0x0100
#define OSC_SB_FAST_THERMAL_SAMPLING_SUPPORT	    0x0200
#define OSC_SB_OVER_16_PSTATES_SUPPORT		        0x0400
#define OSC_SB_GED_SUPPORT			                0x0800
#define OSC_SB_CPC_DIVERSE_HIGH_SUPPORT		        0x1000
#define OSC_SB_IRQ_RESOURCE_SOURCE_SUPPORT	        0x2000
#define OSC_SB_CPC_FLEXIBLE_ADR_SPACE		        0x4000
#define OSC_SB_GENERIC_INITIATOR_SUPPORT	        0x00020000
#define OSC_SB_NATIVE_USB4_SUPPORT		            0x00040000
#define OSC_SB_BATTERY_CHARGE_LIMITING_SUPPORT	    0x00080000
#define OSC_SB_PRM_SUPPORT			                0x00200000
#define OSC_SB_FFH_OPR_SUPPORT			            0x00400000

#define OSC_USB_USB3_TUNNELING                  0x01
#define OSC_USB_DP_TUNNELING                    0x02
#define OSC_USB_PCIE_TUNNELING                  0x04
#define OSC_USB_XDOMAIN                         0x08

#define OSC_PCI_EXT_CONFIG_SUPPORT		        0x01
#define OSC_PCI_ASPM_SUPPORT			        0x02
#define OSC_PCI_CLOCK_PM_SUPPORT		        0x04
#define OSC_PCI_SEGMENT_GROUPS_SUPPORT		    0x08
#define OSC_PCI_MSI_SUPPORT			            0x10
#define OSC_PCI_EDR_SUPPORT			            0x80
#define OSC_PCI_HPX_TYPE_3_SUPPORT		        0x0100

#define OSC_PCI_EXPRESS_NATIVE_HP_CONTROL	    0x01
#define OSC_PCI_SHPC_NATIVE_HP_CONTROL		    0x02
#define OSC_PCI_EXPRESS_PME_CONTROL		        0x04
#define OSC_PCI_EXPRESS_AER_CONTROL		        0x08
#define OSC_PCI_EXPRESS_CAPABILITY_CONTROL	    0x10
#define OSC_PCI_EXPRESS_LTR_CONTROL		        0x20
#define OSC_PCI_EXPRESS_DPC_CONTROL		        0x80

#define OSC_CXL_1_1_PORT_REG_ACCESS_SUPPORT	    0x01
#define OSC_CXL_2_0_PORT_DEV_REG_ACCESS_SUPPORT	0x02
#define OSC_CXL_PROTOCOL_ERR_REPORTING_SUPPORT	0x04
#define OSC_CXL_NATIVE_HP_SUPPORT		        0x08

#define OSC_CXL_ERROR_REPORTING_CONTROL		    0x01

#define INVALID_CPU_ID (~(INT32_MAX))

#define INVALID_ACPI_CPU_ID(CpuId)      (bool)(INVALID_CPU_ID == CpuId)
#define INVALID_ACPI_CPU_PHY_ID(PhyId)  (bool)(PhyId == (UINT64_MAX))


#define ACPI_PROCESSOR_DEVICE_HID	"ACPI0007"


#ifndef __cplusplus
#include <acpi.h>
ACPI_STATUS AcpiEvaluateInteger(ACPI_HANDLE AcpiHandle, ACPI_STRING Path, ACPI_OBJECT_LIST* Args, UINT64* Data);
#endif

#include "Pcc.h"

#ifdef __cplusplus
}
#endif
#endif
