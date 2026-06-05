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

typedef struct _PCI_LOOKUP_CONTEXT {
    UINT16 Segment;
    UINT8  Bus;
    ACPI_HANDLE FoundHandle;
} PCI_LOOKUP_CONTEXT, *PPCI_LOOKUP_CONTEXT;

ACPI_STATUS FindPciBusCallback(ACPI_HANDLE ObjHandle, UINT32 NestingLevel, void *Context, void **RetVal) {
    PPCI_LOOKUP_CONTEXT Lookup = (PPCI_LOOKUP_CONTEXT)Context;
    ACPI_INTEGER Value = 0;
    
    ACPI_STATUS Status = AcpiEvaluateInteger(ObjHandle, "_SEG", NULL, &Value);
    UINT16 CurrentSeg = ACPI_SUCCESS(Status) ? (UINT16)Value : 0;
    if (CurrentSeg != Lookup->Segment) return AE_OK;

    Status = AcpiEvaluateInteger(ObjHandle, "_BBN", NULL, &Value);
    UINT8 CurrentBus = ACPI_SUCCESS(Status) ? (UINT8)Value : 0;
    
    if (CurrentBus == Lookup->Bus) {
        Lookup->FoundHandle = ObjHandle;
        return AE_CTRL_TERMINATE;
    }
    return AE_OK;
}

KERNEL_EXPORT uint8_t LouKeGetPciInterruptLineFromPin(PPCI_DEVICE_OBJECT PDEV){
    UINT16 Segment = PDEV->Group; 
    UINT8 Bus = PDEV->Bus; 
    UINT8 Slot = PDEV->Slot; 
    UINT8 Function = PDEV->Function;
    
    ACPI_STATUS Status;
    ACPI_BUFFER PrtBuffer = {ACPI_ALLOCATE_BUFFER, 0x00};
    ACPI_HANDLE TargetBusHandle = NULL;
    ACPI_OBJECT* PrtObject;
    
    UINT8 PciPin = PDEV->InterruptPin;
    UINT8 WantedPin = PciPin - 1;

    PCI_LOOKUP_CONTEXT LookupContext = { Segment, Bus, NULL };
    
    AcpiGetDevices("PNP0A03", FindPciBusCallback, &LookupContext, NULL);
    if (!LookupContext.FoundHandle) {
        AcpiGetDevices("PNP0A08", FindPciBusCallback, &LookupContext, NULL);
    }
    
    TargetBusHandle = LookupContext.FoundHandle;
    if (!TargetBusHandle) {
        LouPrint("ACPICA: Failed to find ACPI handle for Seg %d Bus %d\n", Segment, Bus);
        return 0;
    }

    Status = AcpiEvaluateObject(TargetBusHandle, "_PRT", 0x00, &PrtBuffer);
    if (ACPI_FAILURE(Status)) {
        LouPrint("ACPICA:_PRT Execution Failed for target bus\n");
        return 0;
    }

    PrtObject = (ACPI_OBJECT*)PrtBuffer.Pointer;
    if (PrtObject->Type != ACPI_TYPE_PACKAGE) {
        AcpiOsFree(PrtBuffer.Pointer);
        return 0;
    }

    for (UINT32 i = 0; i < PrtObject->Package.Count; i++) {
        ACPI_OBJECT* TmpEntry = &PrtObject->Package.Elements[i];
        if (TmpEntry->Type != ACPI_TYPE_PACKAGE || TmpEntry->Package.Count != 4) {
            continue;
        }

        ACPI_OBJECT* AddressObject = &TmpEntry->Package.Elements[0];
        ACPI_OBJECT* PinObject     = &TmpEntry->Package.Elements[1];
        ACPI_OBJECT* SourceObject  = &TmpEntry->Package.Elements[2];
        ACPI_OBJECT* IndexObject   = &TmpEntry->Package.Elements[3];

        if ((AddressObject->Type != ACPI_TYPE_INTEGER) || (PinObject->Type != ACPI_TYPE_INTEGER)) {
            continue;
        }

        UINT32 EntryAddress = (UINT32)AddressObject->Integer.Value;
        UINT16 EntrySlot = (UINT16)(EntryAddress >> 16);
        UINT16 EntryFunc = (UINT16)(EntryAddress & 0xFFFF);

        if (EntrySlot != Slot) {
            continue;
        }

        if (EntryFunc != Function && EntryFunc != 0xFFFF) {
            continue;
        }

        if ((UINT8)PinObject->Integer.Value != WantedPin) {
            continue;
        }

        if (SourceObject->Type == ACPI_TYPE_INTEGER) {
            UINT8 Vector = (UINT8)(UINT32)IndexObject->Integer.Value;
            AcpiOsFree(PrtBuffer.Pointer);
            return Vector;
        }
    }
    AcpiOsFree(PrtBuffer.Pointer);
    return 0;
}