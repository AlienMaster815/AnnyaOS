#include <LouACPI.h>
#include <acpi.h>

static ACPI_PCC_INFORMATION PccContext = {0};

static ACPI_STATUS AcpiPccAddressSpaceHandler(
    uint32_t                    Function,
    ACPI_PHYSICAL_ADDRESS       PhyAddress,
    uint32_t                    Bits,
    ACPI_INTEGER*               Value,
    void*                       HandlerContext,
    void*                       RegionContext
){


    LouPrint("AcpiPccAddressSpaceHandler()\n");
    while(1);
    return AE_OK;
}

static ACPI_STATUS AcpiPccAddressSpaceSetup(
    ACPI_HANDLE     RegionHandle,
    uint32_t        Function,
    void*           HandlerContext,
    void**          RegionContext
){

    LouPrint("AcpiPccAddressSpaceSetup()\n");
    while(1);
    return AE_OK;
}

void AcpiInitializePlatformCommunications(){
    ACPI_STATUS Status;

    Status = AcpiInstallAddressSpaceHandler(
        ACPI_ROOT_OBJECT,
        ACPI_ADR_SPACE_PLATFORM_COMM,
        &AcpiPccAddressSpaceHandler,
        &AcpiPccAddressSpaceSetup,
        &PccContext
    );

    if(ACPI_FAILURE(Status)){
        LouPrint("LouACPI:ERROR:OperationRegion Handler Could Not Be Installed\n");
    }
}
