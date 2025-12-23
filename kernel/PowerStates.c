#include <LouAPI.h>
#include <acpi.h>

UINT32 RunAcpiPowerOff(){
    ACPI_STATUS Status;

    Status = AcpiEnterSleepStatePrep(ACPI_STATE_S5);
    if (ACPI_FAILURE(Status)) {
        LouPrint("Failed to prepare S5 sleep state: %h\n", Status);
        return ACPI_INTERRUPT_HANDLED;
    }

    Status = AcpiEnterSleepState(ACPI_STATE_S5);
    if (ACPI_FAILURE(Status)) {
        LouPrint("Failed to enter S5 sleep state: %h\n", Status);
        return ACPI_INTERRUPT_HANDLED;
    }

    return ACPI_INTERRUPT_HANDLED;
}

UINT32 AcpiPbHandler(void* Context){
    LouPrint("Power button pressed. Initiating shutdown...\n");
    return RunAcpiPowerOff();
}

static void RunSafeShutdownSequence(
    SHUTDOWN_ACTION Action
){

}

void LouKeSystemShutdown(
    SHUTDOWN_ACTION Action
){
    
    RunSafeShutdownSequence(Action);

    switch(Action){

        case ShutdownNoReboot:
            while(1);
        case ShutdownReboot: 
            if(AcpiGbl_FADT.Flags & ACPI_FADT_RESET_REGISTER){
                AcpiWrite(
                    AcpiGbl_FADT.ResetValue,
                    &AcpiGbl_FADT.ResetRegister
                );
            }
        case ShutdownPowerOff:
            RunAcpiPowerOff();
            break;
    }
}
