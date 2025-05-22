#include <LouACPI.h>

void  LouKeAcpiParseExtendedOpBankFeild( 
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

        //LouPrint("NewObjectName:%s EXT_BANK_FEILD_OP\n", AmlObjectName);

        LouKeAcpiCreateNameSpaceObject(
            Context,
            false,
            AmlObjectName,
            AML_HANDLE_EXTENDED_OP_BANK_FEILD,
            Index - 1,
            Index + PackageLength + 1
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
    LouPrint("LouKeAcpiParseExtendedOpBankFeild()\n");
    while(1);
}

void LouKeAcpiParseCreateBitFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    UNUSED uint8_t* AmlStream = Context->AmlStream;
    UNUSED size_t Index = Context->Index;
    UNUSED string AmlObjectName;
    UNUSED size_t PackageLength = 0;
    switch(Context->ExecutionState){

        

        default:
            break;
    }
    LouPrint("LouKeAcpiParseCreateBitFeild()\n");
    while(1);
}
