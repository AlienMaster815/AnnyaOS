#include <LouACPI.h>

void LouKeAcpiParsePackage(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){    
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    size_t PackageLength = 0;
    switch(Context->ExecutionState){
        case SIZE_OF:
            //while(AmlStream)
            LouKeAcpiParsePackageLength(
                AmlStream, 
                Index, 
                0x00,
                &PackageLength,
                0x00
            );
            Context->ResultValue = PackageLength;
            Context->InterpreterReturn = true;
            return;

        default:
            break;
    }
    LouPrint("LouKeAcpiParsePackage()\n");
    while(1);
}
