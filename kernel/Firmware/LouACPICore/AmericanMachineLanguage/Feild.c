#include <LouACPI.h>

void LouKeAcpiParseCreateFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    LouPrint("LouKeAcpiParseCreateFeild()\n");
    while(1);
}

void LouKeAcpiParseCreateQWordFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    LouPrint("LouKeAcpiParseCreateQWordFeild()\n");
    while(1);
}

 void LouKeAcpiParseCreateWordFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    size_t Index = Context->Index;
    uint8_t* AmlStream = Context->AmlStream;
    string AmlObjectName;
    switch(Context->ExecutionState){

        case BUILD:
        Context->Index += AmlNameSpaceNameStringLength(&AmlStream[Context->Index + 1]) + 2;
        AmlObjectName = CreateUTF8StringFromAcpiNameString(&AmlStream[Context->Index]);
        Context->Index += AmlNameSpaceNameStringLength(&AmlStream[Context->Index]);
        LouKeAcpiCreateNameSpaceObject(
            Context,
            false,
            AmlObjectName,
            AML_HANDLE_OP_CREATE_WORD_FEILD,
            Index,
            Context->Index - Index
        );

        return;
        default:
            break;
    }

    LouPrint("LouKeAcpiParseCreateWordFeild()\n");
    while(1);
}

void LouKeAcpiParseCreateDWordFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    LouPrint("LouKeAcpiParseCreateDWordFeild()\n");
    while(1);
}

void LouKeAcpiParseCreateByteFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    LouPrint("LouKeAcpiParseCreateByteFeild()\n");
    while(1);
}