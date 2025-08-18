#include <LouACPI.h>
#include <acpi.h>

static PACPI_EMBEDDED_CONTROLLER BootEc = 0x00;
static INTEGER EcFlagsCorectEcdt = 0;
static INTEGER EcFlagTrustDsdGpe = 0;
static INTEGER EcFlagsClearOnResume = 0;
static INTEGER AcpiEventClearing = 0;

#define ACPI_EC_EVENT_TIMING_STATUS 0x00

static PACPI_EMBEDDED_CONTROLLER AllocateAcpiEc(){
    PACPI_EMBEDDED_CONTROLLER Ec = LouKeMallocType(ACPI_EMBEDDED_CONTROLLER, KERNEL_GENERIC_MEMORY);
    Ec->TimeStamp = GetCurrentTimeInMilliseconds();
    Ec->PollingBusy = true;
    Ec->PollingGuard = 0;
    Ec->GPE = -1;
    Ec->Irq = -1;
    return Ec;
}

static INTEGER EcCorrectEcdt(PDMI_SYSTEM_ID Id){
    LouPrint("LouACPI Core: System Detected ECDT Address Needs Corection\n");
    EcFlagsCorectEcdt = 1;
    return 0;
}

static INTEGER EcHonorDsdtGpe(PDMI_SYSTEM_ID Id){
    LouPrint("LouACPI Core: System Detected DSDT Gpe To Be Honored\n");
    EcFlagTrustDsdGpe = 1;
    return 0;
}

static INTEGER EcClearOnResume(PDMI_SYSTEM_ID Id){
    LouPrint("LouACPI Core: System Detected Ec Poll On Resume\n");
    EcFlagsClearOnResume = 1;
    AcpiEventClearing = ACPI_EC_EVENT_TIMING_STATUS;
    return 0;
}

static const DMI_SYSTEM_ID EcDmiTable[] = {
    {
        .Callback = EcCorrectEcdt,
        .Matches = {
            DMI_MATCH(DMI_SYSTEM_VENDOR, "Micro-Star"),
            DMI_MATCH(DMI_PRODUCT_NAME,  "MS-171F"),
        },
    },
    {
        .Callback = EcHonorDsdtGpe,
        .Matches = {
            DMI_MATCH(DMI_SYSTEM_VENDOR, "HP"),
            DMI_MATCH(DMI_PRODUCT_NAME,  "HP Pavilion Gaming Laptop-cx0xxx"),
        },
    },
    {
        .Callback = EcHonorDsdtGpe,
        .Matches = {
            DMI_MATCH(DMI_SYSTEM_VENDOR, "HP"),
            DMI_MATCH(DMI_PRODUCT_NAME,  "HP 15-cx0041ur"),
        },
    }, 
    {
        .Callback = EcHonorDsdtGpe,
        .Matches = {
            DMI_MATCH(DMI_SYSTEM_VENDOR, "HP"),
            DMI_MATCH(DMI_PRODUCT_NAME,  "HP Pavilion Gaming Laptop 15-dk1xxx"),
        },
    },
    {
        .Callback = EcHonorDsdtGpe,
        .Matches = {
            DMI_MATCH(DMI_SYSTEM_VENDOR, "HP"),
            DMI_MATCH(DMI_PRODUCT_NAME,  "HP 250 G7 Notebook PC"),
        },
    },
    {
        .Callback = EcClearOnResume,
        .Matches = {
            DMI_MATCH(DMI_SYSTEM_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
        },
    },
    {0},
};

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

    CheckDmiSystem((PDMI_SYSTEM_ID)EcDmiTable);
    Status = AcpiGetTable(ACPI_SIG_ECDT, 1, (ACPI_TABLE_HEADER**)&EcdtPointer);
    if(ACPI_FAILURE(Status)){
        return;
    }

    if((!EcdtPointer->EccControl.Address) || (!EcdtPointer->EccData.Address)){
        //Asus X50GL Bug
        goto _ECDT_PROBE_EXIT;
    }

    if(!strstart((string)EcdtPointer->EcId, "\\")){
        //MSI INAL Quirk
        LouPrint("LouACPI Core: Ignoring ECDT Due To Firmware Bug\n");
        goto _ECDT_PROBE_EXIT;
    }

    //TODO: Before Continueing i need to implement proper work queues

    Ec = AllocateAcpiEc();
    if(!Ec){
        goto _ECDT_PROBE_EXIT;
    }

    if(EcFlagsCorectEcdt){

    }else{

    }

    _ECDT_PROBE_EXIT:
        AcpiPutTable((ACPI_TABLE_HEADER*)EcdtPointer);
}