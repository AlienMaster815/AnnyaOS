#include <LouACPI.h>
#include <acpi.h>

//static bool AcpiScanInitialized = false;

void AcpiInitializeScan(){
    //ACPI_STATUS Status;
    //ACPI_TABLE_STAO* Stao;

    AcpiInitializePciRoot();

    //AcpiScanInitialized = true;

}