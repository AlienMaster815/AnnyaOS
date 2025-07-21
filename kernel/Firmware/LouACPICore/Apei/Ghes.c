#include <LouACPI.h>
#include <acpi.h>

void AcpiInitializeGhes(){

    if(!LouKeAcpiCheckHestSetup()){
        return;
    }

    LouPrint("AcpiInitializeGhes()\n");
    while(1);
}