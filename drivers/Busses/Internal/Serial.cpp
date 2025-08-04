#include <LouDDK.h>
#include <LouACPI.h>

void InitializeSerialIo(){

    PFIXED_ACPI_DESCRIPTION_TABLE Fadt = (PFIXED_ACPI_DESCRIPTION_TABLE)LouKeAquireAcpiTable(FIXED_ACPI_DESCRIPTION);    

    if(Fadt->IAPCBootArch & (1 << 1)){
        LouPrint("PS2 Bus Exists\n");
        LouKeLoadSubsystem("PS2IO.SYS", 0);
    }

}