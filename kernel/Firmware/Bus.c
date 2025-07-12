#include <LouACPI.h>
#include <acpi.h>

ACPI_STATUS AcpiOsInitialize1();
void AcpiInitializePlatformRuntime();
PACPI_PCC_INFORMATION GetPccContext();
void AcpiEcEcdtProbe();

static void AcpiBusOscNegotiatePlatformControl(){

    LouPrint("AcpiBusOscNegotiatePlatformControl()\n");
    while(1);
}

LOUSTATUS AcpiBusInitialize(){
    LOUSTATUS Status = STATUS_SUCCESS;
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
    //Continue Here

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


    LouPrint("AcpiBusInitialize()\n");
    while(1);
    return Status;

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


void LouKeInitializeFullLouACPISubsystem(){
    ACPI_STATUS Status;
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
    AcpiBusInitialize();
    


    LouPrint("LouKeInitializeFullLouACPISubsystem()\n");
    while(1);
}