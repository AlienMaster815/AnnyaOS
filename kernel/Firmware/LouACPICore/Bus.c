#include <LouACPI.h>
#include <acpi.h>

ACPI_STATUS AcpiOsInitialize1();
void AcpiInitializePlatformRuntime();
PACPI_PCC_INFORMATION GetPccContext();
void AcpiEcEcdtProbe();
void AcpiEarlyProcessorControlSetup();
void AcpiEcProbDsdt();
LOUSTATUS AcpiInitializeSleep();

static ACPI_STATUS AcpiBusTableHandler(
    UINT32 Event, 
    PVOID Table, 
    PVOID Context
){


    LouPrint("AcpiBusTableHandler()\n");
    while(1);
    return AE_OK;
}

ACPI_STATUS AcpiRunOsc(ACPI_HANDLE AcpiHandle, PACPI_OSC_CONTEXT Ctx){
    UNUSED ACPI_STATUS      Status; 
    UNUSED ACPI_OBJECT_LIST ObjList; 
    UNUSED ACPI_OBJECT      Input[4];
    UNUSED ACPI_OBJECT*     OutObj;
    UNUSED UINT32           Errors;
    UNUSED ACPI_BUFFER      Output = {ACPI_ALLOCATE_BUFFER, NULL};
    
    if(!Ctx){
        return AE_ERROR;
    }
    
    Ctx->Return.Length = ACPI_ALLOCATE_BUFFER;
    Ctx->Return.Pointer = NULL;

    ObjList.Count           = 4;
    ObjList.Pointer         = Input;
    Input[0].Type           = ACPI_TYPE_BUFFER;
    Input[0].Buffer.Length  = 16;
    Input[0].Buffer.Pointer = (UINT8*)Ctx->Uuid;
    Input[1].Type           = ACPI_TYPE_INTEGER;
    Input[1].Integer.Value  = Ctx->Revision;
    Input[2].Type           = ACPI_TYPE_INTEGER;
    Input[2].Integer.Value  = Ctx->Capabilities.Length / sizeof(UINT32);
    Input[3].Type           = ACPI_TYPE_BUFFER;
    Input[3].Buffer.Length  = Ctx->Capabilities.Length;
    Input[3].Buffer.Pointer = (UINT8*)Ctx->Capabilities.Pointer;

    Status = AcpiEvaluateObject(AcpiHandle, "_OSC", &ObjList, &Output);
    if(ACPI_FAILURE(Status)){
        LouPrint("OSC Evaluation Failed:%h\n", Status);
        return Status;
    }

    LouPrint("AcpiRunOsc()\n");
    while(1);
    return AE_OK;
}

static GUID RootUuid = {DEFINE_GUID(0x0811B06E, 0x4A27, 0x44F9, 0x8D, 0x60, 0x3C, 0xBB, 0xC2, 0x2E, 0x7B, 0x48)};
static void AcpiBusOscNegotiatePlatformControl(){
    UINT32                  CapBuffer[2] = {0};
    UNUSED UINT32*          CapBufferRet = 0x00; 
    ACPI_HANDLE      AcpiHandle;
    ACPI_OSC_CONTEXT Ctx = {
        .Uuid = &RootUuid,
        .Revision = 1,
        .Capabilities.Length = 8,
        .Capabilities.Pointer = CapBuffer,
    };

    //the following will be re configured once Userspace takes over
    CapBuffer[OSC_QUERY_DWORD] = OSC_QUERY_ENABLE;
    CapBuffer[OSC_SUPPORT_DWORD] = OSC_SB_PR3_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_PAD_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_PPC_OST_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_FAST_THERMAL_SAMPLING_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_BATTERY_CHARGE_LIMITING_SUPPORT;

    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_HOTPLUG_OST_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_PCLPI_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_OVER_16_PSTATES_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_GED_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_IRQ_RESOURCE_SOURCE_SUPPORT;

    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_PRM_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_FFH_OPR_SUPPORT;

    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_GENERIC_INITIATOR_SUPPORT; 
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_CPC_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_CPCV2_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_CPC_FLEXIBLE_ADR_SPACE;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_CPC_DIVERSE_HIGH_SUPPORT; 
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_NATIVE_USB4_SUPPORT;
    CapBuffer[OSC_SUPPORT_DWORD] |= OSC_SB_APEI_SUPPORT;

    if(ACPI_FAILURE(AcpiGetHandle(0x00, "\\_SB", &AcpiHandle))){
        LouPrint("Acpica Was Unable To Get Root\n");
        return;
    }

    if(ACPI_FAILURE(AcpiRunOsc(AcpiHandle, &Ctx))){
        return;
    }


    LouPrint("AcpiBusOscNegotiatePlatformControl()\n");
    while(1);
}

static void AcpiBusNotify(ACPI_HANDLE Handle, UINT32 Type, PVOID Data){
    LouPrint("AcpiBusNotify()\n");
    while(1);
}

LOUSTATUS AcpiBusInitialize(){
    ACPI_STATUS AcpiStatus;
    ACPI_HANDLE PicHandle;

    AcpiStatus = AcpiOsInitialize1();

    LouPrint("Loading Tables\n");
    AcpiStatus = AcpiLoadTables();
    if (ACPI_FAILURE(AcpiStatus)) {
        LouPrint("AcpiLoadTables failed\n");
        goto _ACPI_BUS_INITIALIZE_ERROR;
    }
    
    AcpiEcEcdtProbe();

    LouPrint("Enabling System\n");
    AcpiStatus = AcpiEnableSubsystem(ACPI_NO_ACPI_ENABLE);
    if (ACPI_FAILURE(AcpiStatus)) {
        LouPrint("AcpiEnableSubsystem failed\n");
        goto _ACPI_BUS_INITIALIZE_ERROR;
    }

    LouPrint("Initializing Objects\n");
    AcpiStatus = AcpiInitializeObjects(ACPI_FULL_INITIALIZATION);
    if (ACPI_FAILURE(AcpiStatus)) {
        LouPrint("AcpiInitializeObjects failed\n");
        goto _ACPI_BUS_INITIALIZE_ERROR;
    }

    AcpiBusOscNegotiatePlatformControl();

    //TODO: Negotiate USB

    AcpiStatus = AcpiInstallTableHandler(AcpiBusTableHandler, NULL);

    AcpiEarlyProcessorControlSetup();
    
    AcpiEcProbDsdt();

    LouPrint("Interpreter Enabled\n");

    AcpiInitializeSleep();

    AcpiStatus = AcpiGetHandle(NULL, "\\_PIC", &PicHandle);
    if(ACPI_SUCCESS(AcpiStatus)) {
        LouPrint("_PIC method located\n");
        ACPI_OBJECT Arg;
        Arg.Type = ACPI_TYPE_INTEGER;
        Arg.Integer.Value = 1; // APIC mode

        ACPI_OBJECT_LIST ArgList;
        ArgList.Count = 1;
        ArgList.Pointer = &Arg;

        AcpiStatus = AcpiEvaluateObject(PicHandle, NULL, &ArgList, NULL);
        if (ACPI_FAILURE(AcpiStatus)) {
            LouPrint("Failed to evaluate _PIC method\n");
        } else {
            LouPrint("_PIC method executed successfully\n");
        }
    }

    AcpiInstallNotifyHandler(ACPI_ROOT_OBJECT, ACPI_SYSTEM_NOTIFY, &AcpiBusNotify, NULL);
    if (ACPI_FAILURE(AcpiStatus)) {
        LouPrint("Failed to Register AcpiBusNotify Handler\n");
        goto _ACPI_BUS_INITIALIZE_ERROR;
    } 

    return STATUS_SUCCESS;

    _ACPI_BUS_INITIALIZE_ERROR:
        return STATUS_NO_SUCH_DEVICE;
}

ACPI_STATUS AcpiPccAddressSpaceHandler(
    uint32_t                    Function,
    ACPI_PHYSICAL_ADDRESS       PhyAddress,
    uint32_t                    Bits,
    ACPI_INTEGER*               Value,
    void*                       HandlerContext,
    void*                       RegionContext
);

ACPI_STATUS AcpiPccAddressSpaceSetup(
    ACPI_HANDLE     RegionHandle,
    uint32_t        Function,
    void*           HandlerContext,
    void**          RegionContext
);

void AcpiInitializePlatformCommunications();
void AcpiInitializeFfh();
void PciMmcfgLateInit();

void LouKeInitializeFullLouACPISubsystem(){
    ACPI_STATUS Status;
    LOUSTATUS St;
    LouPrint("Initializing Acpica Subsystem\n");

    Status = AcpiInitializeSubsystem();
    if (ACPI_FAILURE(Status)) {
        LouPrint("AcpiInitializeSubsystem failed\n");
        return;
    }
    
    LouPrint("Initializing Tables\n");
    Status = AcpiInitializeTables(NULL, LouKeAcpiGetTableCount(), FALSE);
    if (ACPI_FAILURE(Status)) {
        LouPrint("AcpiInitializeTables failed\n");
        return;
    }
    AcpiInitializePlatformRuntime();
    AcpiInitializePlatformCommunications();
    St = AcpiBusInitialize();
    if(St != STATUS_SUCCESS){
        LouPrint("St != STATUS_SUCCESS\n");
        while(1);
    }

    AcpiInitializeFfh();

    PciMmcfgLateInit();
    EarlyInitializeViot();
    AcpiInitializeHest();
    AcpiInitializeScan();


    LouPrint("LouKeInitializeFullLouACPISubsystem()\n");
    //while(1);
}