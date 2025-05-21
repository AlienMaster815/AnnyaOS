#include <LouACPI.h>

 void LouKeAcpiParseIf(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    size_t PackageLength = 0;
    switch(Context->ExecutionState){
        case BUILD:
            LouKeAcpiParsePackageLength(
                AmlStream, 
                Index, 
                0x00,
                &PackageLength,
                0x00
            );
            Context->Index = (Index + PackageLength + 1);
            return;
            default:
                break;
    }

    LouPrint("LouKeAcpiParseIf()\n");
    while(1);
}