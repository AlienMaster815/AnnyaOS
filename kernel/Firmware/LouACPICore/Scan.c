#include <LouACPI.h>
#include <acpi.h>

//static bool AcpiScanInitialized = false;



static ACPI_DEVICE_IDENTIFICATION GenericDeviceIDs[] = {
    {ACPI_DT_NAMESPACE_ID, },
    {"", },
};

INTEGER AcpiGenericDeviceAttach(PACPI_DEVICE AcpiDev, PACPI_DEVICE_IDENTIFICATION Nui){

    

    return 1;
}

UNUSED static ACPI_SCAN_HANDLER GenericDeviceHandler = {
    .IdList = GenericDeviceIDs,
    .AtatchDevice = AcpiGenericDeviceAttach,
};

LOUSTATUS AcpiScanAddHandler(PACPI_SCAN_HANDLER ScanHandler){


    return STATUS_SUCCESS;
}

#include <acpi.h>
UINT32 AcpiPbHandler(void* Context);

void AcpiInitializeScan(){
    //ACPI_STATUS Status;
    //ACPI_TABLE_STAO* Stao;

    //AcpiInitializePciRoot();
    //AcpiInitializePciLink();

    //AcpiScanAddHandler(&GenericDeviceHandler);
    //AcpiScanInitialized = true;

    AcpiEnable();

    AcpiEnableEvent(ACPI_EVENT_POWER_BUTTON, 0);
    AcpiInstallFixedEventHandler(ACPI_EVENT_POWER_BUTTON, AcpiPbHandler, NULL);

    AcpiUpdateAllGpes();

}