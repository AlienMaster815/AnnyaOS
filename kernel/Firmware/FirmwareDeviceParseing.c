#include <LouACPI.h>
#include <acpi.h>

#include <acpi.h>

static ACPI_STATUS
PciRootMatchCallback(
    ACPI_HANDLE ObjHandle,
    UINT32 Level,
    void *Context,
    void **ReturnValue
){
    *(ACPI_HANDLE*)Context = ObjHandle;
    return AE_CTRL_TERMINATE;
}

ACPI_HANDLE LouKeGetPciRootBridge(){
    ACPI_STATUS Status;
    ACPI_HANDLE Root = NULL;

    Status = AcpiGetDevices(
        "PNP0A03",
        PciRootMatchCallback,
        &Root,
        NULL
    );

    if (ACPI_FAILURE(Status) || Root == NULL) {
        LouPrint("ACPICA: PCI root bridge (PNP0A03) not found\n");
        return NULL;
    }

    return Root;
}


uint8_t LouKeGetPciInterruptLineFromPin(PPCI_DEVICE_OBJECT PDEV){
    ACPI_STATUS     Status;
    ACPI_BUFFER     PrtBuffer = {ACPI_ALLOCATE_BUFFER, 0x00};
    ACPI_HANDLE     PciRootBusHandle = LouKeGetPciRootBridge();
    ACPI_OBJECT*    PrtObject;
    UINT8           PciDevice = PDEV->slot;
    UINT8           PciPin = PDEV->InterruptPin;
    UINT32          WantedAddress = (PciDevice << 16) | 0xFFFF;
    UINT8           WantedPin = PciPin - 1;
    ACPI_OBJECT*    TmpEntry;
    ACPI_OBJECT*    AddressObject;
    ACPI_OBJECT*    PinObject;
    ACPI_OBJECT*    SourceObject;
    ACPI_OBJECT*    IndexObject;

    if(!PciRootBusHandle){
        return 0xFF;
    }

    Status = AcpiEvaluateObject(
        PciRootBusHandle,
        "_PRT",
        0x00,
        &PrtBuffer
    );

    if(ACPI_FAILURE(Status)){
        LouPrint("ACPICA:_PRT Execution Failed\n");
        return 0xFF;
    }

    PrtObject = (ACPI_OBJECT*)PrtBuffer.Pointer;

    if(PrtObject->Type != ACPI_TYPE_PACKAGE){
        LouPrint("ACPICA:_PRT Did Not Return A Package\n");
        return 0xFF;
    }
    
    for(UINT32 i = 0 ; i < PrtObject->Package.Count; i++){
        TmpEntry = &PrtObject->Package.Elements[i];

        if(TmpEntry->Type != ACPI_TYPE_PACKAGE){
            continue;
        }

        if(TmpEntry->Package.Count != 4){
            continue;
        }

        AddressObject   = &TmpEntry->Package.Elements[0];        
        PinObject       = &TmpEntry->Package.Elements[1];        
        SourceObject    = &TmpEntry->Package.Elements[2];        
        IndexObject     = &TmpEntry->Package.Elements[3];        

        if(
            (AddressObject->Type != ACPI_TYPE_INTEGER) || 
            (PinObject->Type != ACPI_TYPE_INTEGER)
        ){
            continue;
        }

        if((UINT32)AddressObject->Integer.Value != WantedAddress){
            continue;
        }

        if((UINT8)PinObject->Integer.Value != WantedPin){
            continue;
        }

        if(SourceObject->Type == ACPI_TYPE_INTEGER){
        
            return (UINT8)(UINT32)IndexObject->Integer.Value;
        }

    }

    return 0xFF;
}