#include <LouACPI.h>

SET_OPTIMIZATION(3) void LouKeAcpiParsePrefixQWord( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = 8;
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }
    LouPrint("LouKeAcpiParsePrefixQWord()\n");
    while(1);
}

void LouKeAcpiParsePrefixRoot( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    LouPrint("LouKeAcpiParsePrefixRoot()\n");
    while(1);
}

SET_OPTIMIZATION(3) void LouKeAcpiParsePrefixWord( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = 2;
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }
    LouPrint("LouKeAcpiParsePrefixWord()\n");
    while(1);
}

void LouKeAcpiParsePrefixParent( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    LouPrint("LouKeAcpiParsePrefixParent()\n");
    while(1);
}

SET_OPTIMIZATION(3) void LouKeAcpiParsePrefixString( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = strlen((string)&Context->AmlStream[Context->Index + 1]) + 1;
            Context->InterpreterReturn = true;
            return;
        default:
    }

    LouPrint("LouKeAcpiParsePrefixString()\n");
    while(1);
}

SET_OPTIMIZATION(3) void LouKeAcpiParsePrefixMultiName( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = AmlNameSpaceNameStringLength(&AmlStream[Index]);
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }
    LouPrint("LouKeAcpiParsePrefixMultiName()\n");
    while(1);
}

SET_OPTIMIZATION(3) void LouKeAcpiParsePrefixDWord( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = 4;
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }
    LouPrint("LouKeAcpiParsePrefixDWord()\n");
    while(1);
}

SET_OPTIMIZATION(3) void LouKeAcpiParsePrefixDualName( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = AmlNameSpaceNameStringLength(&AmlStream[Index]);
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }
    LouPrint("LouKeAcpiParsePrefixDualName()\n");
    while(1);
}

SET_OPTIMIZATION(3) void LouKeAcpiParsePrefixByte( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = 1;
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }

    LouPrint("LouKeAcpiParsePrefixByte()\n");
    while(1);
}