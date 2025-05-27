 #include <LouACPI.h>
 
 
 void LouKeAcpiParsePrefixByte( 
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

 void LouKeAcpiParsePrefixWord( 
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

 void LouKeAcpiParsePrefixDWord( 
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


 void LouKeAcpiParsePrefixQWord( 
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

 void LouKeAcpiParsePrefixString( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = strlen((string)&Context->AmlStream[Context->Index + 1]) + 1;
            Context->InterpreterReturn = true;
            return;
        case EVALUATE:
            Context->ResultValue = (uint64_t)&Context->AmlStream[Context->Index + 1];
            Context->InterpreterReturn = true;
            return;
        case BUILD_PARAMETER_PASS:
            PAML_EXECUTION_INTERNAL_PARAMETER_PASS Result = LouKeMallocType(AML_EXECUTION_INTERNAL_PARAMETER_PASS, KERNEL_GENERIC_MEMORY);
            Result->DataLocation = (uint64_t)&Context->AmlStream[Context->Index + 1];
            Result->DataSize = strlen((string)&Context->AmlStream[Context->Index + 1]);
            Result->Opcode = AML_HANDLE_PREFIX_STRING;
            Context->Index += strlen((string)&Context->AmlStream[Context->Index + 1]) + 1;
            Context->InterpreterReturn = true;
            Context->ResultValue = (uint64_t)Result;
            return;
        default:
    }

    LouPrint("LouKeAcpiParsePrefixString()\n");
    while(1);
}

void LouKeAcpiParseZero(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = 0;//nothing in front of this
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }

    LouPrint("LouKeAcpiParseZero()\n");
    while(1);
}

void LouKeAcpiParseOne(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = 0; //nothing in front of this
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }
    LouPrint("LouKeAcpiParseOne()\n");
    while(1);
}


void LouKeAcpiParseOnes(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    switch(Context->ExecutionState){
        case SIZE_OF:
            Context->ResultValue = 0; //nothing in front of this
            Context->InterpreterReturn = true;
            return;
        default:
            break;
    }

    LouPrint("LouKeAcpiParseOnes()\n");
    while(1);
}