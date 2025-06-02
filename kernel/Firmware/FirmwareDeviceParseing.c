#include <LouACPI.h>
#include <acpi.h>


uint8_t LouKeGetPciInterruptLineFromPin(P_PCI_DEVICE_OBJECT PDEV){
    ACPI_STATUS Status;
    ACPI_HANDLE PrtHandle;
    ACPI_BUFFER ResultBuffer = { ACPI_ALLOCATE_BUFFER, NULL };
    ACPI_OBJECT* ResultObject;
    ACPI_OBJECT* TmpPackage;
    ACPI_OBJECT* TmpPrtObject;
    size_t PackageCount = 0x00;
    Status = AcpiGetHandle(NULL, "\\_SB.PCI0._PRT", &PrtHandle);
    size_t Address = (PDEV->slot << 16) | PDEV->func;

    if(ACPI_FAILURE(Status)){
        LouPrint("ACPICA Failed To Find the PCI Rounting Table\n");
        //return (uint8_t)-1;
        while(1);//while one for debugging
    }

    Status = AcpiEvaluateObject(PrtHandle, NULL, NULL, &ResultBuffer);
    if(ACPI_FAILURE(Status)){
        LouPrint("ACPICA Faild To Evaluate PCI Routing Table\n");
        //return (uint8_t)-1;
        while(1);
    }

    ResultObject = (ACPI_OBJECT*)ResultBuffer.Pointer;

    if(ResultObject->Type != ACPI_TYPE_PACKAGE){
        LouPrint("ACPICA Returned An Invalid PCI Routing Table");
        //return (uint8_t)-1;
        while(1);
    }

    LouPrint("Parsing ACPI Package\n");

    PackageCount = ResultObject->Package.Count;

    for(size_t i = 0 ; i < PackageCount; i++){
        TmpPackage = &ResultObject->Package.Elements[i];
        TmpPrtObject = &TmpPackage->Package.Elements[0];

        if((TmpPrtObject->Integer.Value == (Address & 0xFFFFFFFF)) || ((Address & 0xFFFFFFFF) | 0xFFFF)) {
            TmpPrtObject = &TmpPackage->Package.Elements[1];
            if(TmpPrtObject->Integer.Value != PDEV->InterruptPin){
                continue;
            }
            TmpPrtObject = &TmpPackage->Package.Elements[2];
            if(TmpPrtObject->Integer.Value == 0){
                TmpPrtObject = &TmpPackage->Package.Elements[3];
                uint8_t Gsi = (uint8_t)TmpPrtObject->Integer.Value;
                //LouPrint("Gsi:%h\n", Gsi);
                return Gsi;
            }
        }
    }

    LouPrint("LouKeGetPciInterruptLineFromPin()\n");
    while(1);
    return 0x00;
}