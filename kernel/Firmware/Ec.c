#include <LouACPI.h>
#include <acpi.h>



void AcpiEcEcdtProbe(){
    UNUSED PACPI_ECDT_TABLE                EcdtPointer = 0x00;
    UNUSED PACPI_EMBEDDED_CONTROLLER       Ec          = 0x00;
    UNUSED ACPI_STATUS                     Status      = AE_OK;
    UNUSED int                             Result      = 0x00;

    Status = AcpiGetTable(ACPI_SIG_ECDT, 1, (ACPI_TABLE_HEADER**)&EcdtPointer);
    if(ACPI_FAILURE(Status)){
        return;
    }

    LouPrint("AcpiEcEcdtProbe()\n");
    while(1);
}