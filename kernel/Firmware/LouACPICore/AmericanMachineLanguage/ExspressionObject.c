#include <LouACPI.h>

 void LouKeAcpiParseBuffer(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    size_t PackageLength = 0;

    switch(Context->ExecutionState){
        case SIZE_OF:
            LouKeAcpiParsePackageLength(
                AmlStream, 
                Index, 
                0x00,
                &PackageLength,
                0x00
            );
            Context->InterpreterReturn = true;
            Context->ResultValue = PackageLength;
            return;
        default:
            break;
    }

    LouPrint("LouKeAcpiParseBuffer()\n");
    while(1);
}