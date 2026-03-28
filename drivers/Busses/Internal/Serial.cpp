//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include <LouDDK.h>
#include <LouACPI.h>

void InitializeSerialIo(){

    PFIXED_ACPI_DESCRIPTION_TABLE Fadt = (PFIXED_ACPI_DESCRIPTION_TABLE)LouKeAquireAcpiTable(FIXED_ACPI_DESCRIPTION);    

    if(Fadt->IAPCBootArch & (1 << 1)){
        LouPrint("PS2 Bus Exists\n");
        LouKeLoadSubsystem("PS2IO.SYS", 0);
    }

}