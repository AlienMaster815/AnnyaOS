#include <LouACPI.h>

LOUSTATUS LouKeAcpiInterperateData(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

SET_OPTIMIZATION(3) void LouKeAcpiParseAlias(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    size_t StringLength = AmlNameSpaceNameStringLength(&AmlStream[Index + 1]);
    StringLength += AmlNameSpaceNameStringLength(&AmlStream[Index + StringLength + 1]);
    StringLength++; //one for the opcode
    Context->Index += StringLength;
    switch(Context->ExecutionState){
        case BUILD:
            //LouPrint("NewObjectName:");
            string AmlObjectName = CreateUTF8StringFromAcpiNameString(&AmlStream[Index + 1]);
            //LouPrint("%s AML_HANDLE_OP_ALIAS\n", AmlObjectName);

            LouKeAcpiCreateNameSpaceObject(
                Context,
                false,
                AmlObjectName,
                AML_HANDLE_OP_ALIAS,
                Index,
                StringLength
            );
            return;
        
        case SIZE_OF:
            Context->InterpreterReturn = true;
            Context->ResultValue = StringLength;
            return;
        default:
            break;
    }

    LouPrint("LouKeAcpiParseAlias()\n");
    while(1);
}




void LouKeAcpiParseName(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
){

    switch(Context->ExecutionState){
        case BUILD:
            size_t Index = Context->Index;
            uint8_t* AmlStream = Context->AmlStream;
            //LouPrint("NewObjectName:");
            string AmlObjectName = CreateUTF8StringFromAcpiNameString(&AmlStream[Index + 1]);
            //LouPrint("%s NAME_OP\n", AmlObjectName);
            size_t NameLength = AmlNameSpaceNameStringLength(&AmlStream[Index + 1]);
            Context->Index = Index + NameLength + 1;
            Context->ExecutionState = SIZE_OF;
            LouKeAcpiInterperateData(Context);
            Context->ExecutionState = BUILD; //restore execution state
            Context->InterpreterReturn = false; //restore Execution Govenor
            Context->Index += Context->ResultValue + 1;
            LouKeAcpiCreateNameSpaceObject(
                Context,
                false,
                AmlObjectName,
                AML_HANDLE_OP_NAME,
                Index,
                Context->Index - Index
            );
            return;
        default:
    }
    LouPrint("LouKeAcpiParseName()\n");
    while(1);
}


SET_OPTIMIZATION(3) void LouKeAcpiParseScope(
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

        //LouPrint("NewObjectName:%s EXT_SCOPE_OP\n", AmlObjectName);
        LouKeAcpiCreateNameSpaceObject(
            Context,
            true,
            AmlObjectName,
            AML_HANDLE_OP_SCOPE,
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
    LouPrint("LouKeAcpiParseScope()\n");
    while(1);
}
