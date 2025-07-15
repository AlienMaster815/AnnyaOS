#include <LouACPI.h>
#include <acpi.h>

PVOID UnusedFfhCtx = 0x00;

static ACPI_STATUS AcpiFfhAddressSpaceSetup(
    ACPI_HANDLE RegionHandle, UINT32 Function,
    PVOID HandlerCtx, PVOID* RegionCtx
){
    return STATUS_NO_SUCH_DEVICE;
}

static ACPI_STATUS AcpiFfhAddressSpaceHandler(
    UINT32 Function, ACPI_PHYSICAL_ADDRESS Phy,
    UINT32 Bits, ACPI_INTEGER* v, 
    PVOID HandlerCtx, PVOID RegionCtx
){
    return STATUS_NO_SUCH_DEVICE;
}

void AcpiInitializeFfh(){

    ACPI_STATUS Status = AcpiInstallAddressSpaceHandler(
        ACPI_ROOT_OBJECT,
        ACPI_ADR_SPACE_FIXED_HARDWARE,
        &AcpiFfhAddressSpaceHandler,
        &AcpiFfhAddressSpaceSetup,
        &UnusedFfhCtx
    );
    if(ACPI_FAILURE(Status)){
        LouPrint("Operation Region Handler Could Not Be Installed\n");
    }

    LouPrint("AcpiInitializeFfh()\n");
} 