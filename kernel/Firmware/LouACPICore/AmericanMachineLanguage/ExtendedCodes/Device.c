#include <LouACPI.h>

void LouKeAcpiParseExtendedOpDevice( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    UNUSED uint8_t* AmlStream = Context->AmlStream;
    UNUSED size_t Index = Context->Index;
    UNUSED string AmlObjectName;
    UNUSED size_t PackageLength;
    UNUSED size_t DataStart;
    switch(Context->ExecutionState){
        case BUILD:
        LouKeAcpiParsePackageLength(
            AmlStream, 
            Index, 
            &AmlObjectName,
            &PackageLength,
            &DataStart
        );

        //LouPrint("NewObjectName:%s EXT_DEVICE_OP\n", AmlObjectName);

        LouKeAcpiCreateNameSpaceObject(
            Context,
            true,
            AmlObjectName,
            AML_HANDLE_EXTENDED_OP_DEVICE,
            Index - 1,
            Index + PackageLength + 1
        );
        LouKeAcpiExecuteSubPackageContext(
            Context,
            (NAMESPACE_HANDLE)Context->ResultValue,
            DataStart,
            PackageLength
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

    LouPrint("LouKeAcpiParseExtendedOpDevice()\n");
    while(1);
}

void LouKeAcpiParseExtendedOpProcessor( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){

    UNUSED uint8_t* AmlStream = Context->AmlStream;
    UNUSED size_t Index = Context->Index;
    UNUSED string AmlObjectName;
    UNUSED size_t PackageLength;
    UNUSED size_t DataStart;

    switch(Context->ExecutionState){
        case BUILD:
        LouKeAcpiParsePackageLength(
            AmlStream, 
            Index, 
            &AmlObjectName,
            &PackageLength,
            &DataStart
        ); 
        //LouPrint("NewObjectName:%s EXT_PROCESSOR_OP\n", AmlObjectName);
        LouKeAcpiCreateNameSpaceObject(
            Context,
            false,
            AmlObjectName,
            AML_HANDLE_EXTENDED_OP_PROCESSOR,
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

    LouPrint("LouKeAcpiParseExtendedOpProcessor()\n");
    while(1);
}