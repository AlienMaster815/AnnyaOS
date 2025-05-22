#include <LouACPI.h>

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