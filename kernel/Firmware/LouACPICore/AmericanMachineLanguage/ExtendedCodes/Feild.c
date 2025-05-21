#include <LouACPI.h>


SET_OPTIMIZATION(3) void LouKeAcpiParseExtendedOpFeild( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    string AmlObjectName;
    size_t PackageLength;
    switch(Context->ExecutionState){

        case BUILD:
        LouKeAcpiParsePackageLength(
            AmlStream, 
            Index, 
            &AmlObjectName,
            &PackageLength,
            0x00
        );

        //LouPrint("NewObjectName:%s EXT_FEILD_OP\n", AmlObjectName);

        LouKeAcpiCreateNameSpaceObject(
            Context,
            false,
            AmlObjectName,
            AML_HANDLE_EXTENDED_OP_FEILD,
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
    LouPrint("LouKeAcpiParseExtendedOpFeild()\n");
    while(1);
}


SET_OPTIMIZATION(3)  void LouKeAcpiParseExtendedOpIndexFeild( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    string AmlObjectName;
    size_t PackageLength;
    switch(Context->ExecutionState){

        case BUILD:
        LouKeAcpiParsePackageLength(
            AmlStream, 
            Index, 
            &AmlObjectName,
            &PackageLength,
            0x00
        );

        //LouPrint("NewObjectName:%s EXT_INDEX_FEILD_OP\n", AmlObjectName);

        LouKeAcpiCreateNameSpaceObject(
            Context,
            false,
            AmlObjectName,
            AML_HANDLE_EXTENDED_OP_INDEX_FEILD,
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
    LouPrint("LouKeAcpiParseExtendedOpIndexFeild()\n");
    while(1);
}

