#include <LouACPI.h>
#include <acpi.h>

static PACPI_EMBEDDED_CONTROLLER BootEc = 0x00;

void AcpiEcProbDsdt(){
    UNUSED PACPI_EMBEDDED_CONTROLLER Ec = 0x0;
    UNUSED ACPI_STATUS Status;

    if(!BootEc){
        return;
    }


    LouPrint("AcpiEcProbDsdt()\n");
    while(1);
}


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