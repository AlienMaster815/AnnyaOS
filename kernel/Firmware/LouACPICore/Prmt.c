#include <LouACPI.h>
#include <acpi.h>


void AcpiInitializePlatformRuntime(){
    ACPI_TABLE_HEADER*          Table;
    ACPI_STATUS                 Status;
    UNUSED int Mc = 0x00;

    Status = AcpiGetTable(ACPI_SIG_PRMT, 0, &Table);
    if(ACPI_FAILURE(Status)){
        LouPrint("LouACPI:ACPI_FAILURE PRMT Not Found:LOUSTATUS:STATUS_OK\n");
        return;
    }

    LouPrint("AcpiInitializePlatformRuntime()\n");
    while(1);
}