#include <LouACPI.h>

 void LouKeAcpiParseMethod(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    string AmlObjectName;
    size_t PackageLength = 0;
    switch(Context->ExecutionState){
        case BUILD: 
            LouKeAcpiParsePackageLength(
                AmlStream, 
                Index, 
                &AmlObjectName,
                &PackageLength,
                0x00
            );

            LouPrint("NewObjectName:%s EXT_METHOD_OP\n", AmlObjectName);

            LouKeAcpiCreateNameSpaceObject(
                Context,
                false,
                AmlObjectName,
                AML_HANDLE_OP_METHOD,
                Index,
                Index + PackageLength
            );

            Context->Index = (Index + PackageLength + 1);
            return;
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
    LouPrint("LouKeAcpiParseMethod()\n");
    while(1);
}