#include <LouACPI.h>
#include <acpi.h>

static ACPI_TABLE_HEST* HestTable = 0x00;

bool LouKeAcpiCheckHestSetup(){
    return (HestTable != 0x00);
}

void AcpiInitializeHest(){
    ACPI_STATUS Status;
    //UINT32 GhesCount = 0;
    Status = AcpiGetTable(ACPI_SIG_HEST, 0 , (PACPI_TABLE_HEADER*)&HestTable);
    if(Status == AE_NOT_FOUND){
        return;
    }

    LouPrint("AcpiInitializeHest()\n");
    while(1);
}