#include <LouACPI.h>
#include <acpi.h>

void AcpiUtilEvalError(
    ACPI_HANDLE AcpiHandle, 
    ACPI_STRING Path, 
    ACPI_STATUS Status
){



}

ACPI_STATUS 
AcpiEvaluateInteger(
    ACPI_HANDLE         AcpiHandle, 
    ACPI_STRING         Path, 
    ACPI_OBJECT_LIST*   Args, 
    UINT64*             Data
){
    ACPI_STATUS Status = AE_OK;
    ACPI_OBJECT Element;
    ACPI_BUFFER Buffer = {0, NULL};

    if(!Data){
        return AE_BAD_PARAMETER;
    }

    Buffer.Length  = sizeof(ACPI_OBJECT);
    Buffer.Pointer = &Element;
    Status = AcpiEvaluateObject(AcpiHandle, Path, Args, &Buffer);
    if(ACPI_FAILURE(Status)){
        AcpiUtilEvalError(AcpiHandle, Path, Status);
        return AE_BAD_DATA;
    }

    if(Element.Type != ACPI_TYPE_INTEGER){
        AcpiUtilEvalError(AcpiHandle, Path, AE_BAD_DATA);
        return AE_BAD_DATA;
    }    

    *Data = Element.Integer.Value;

    return AE_OK;
}
