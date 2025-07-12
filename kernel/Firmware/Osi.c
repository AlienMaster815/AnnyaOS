#include <LouACPI.h>
#include <acpi.h>

static void AcpiOsiLateSetup(){
    //were im not gonna modify firmware at this time
    //but i would midify the firmware to use my kernels
    //OSI but i dont have one at this time so im going
    //to just hanlde the differences
}

static uint32_t AcpiOsiHandler(ACPI_STRING Interface, uint32_t Supported){

    LouPrint("Using Interface Behavior:[%s]\n", Interface);

    return Supported;
}


LOUSTATUS AcpiOsiInitialize(){
    AcpiInstallInterfaceHandler(AcpiOsiHandler);
    AcpiOsiLateSetup();
    return STATUS_SUCCESS;
}