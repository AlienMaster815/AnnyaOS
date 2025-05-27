#include <LouACPI.h>

#define METHOD_SERIALIZED 1

void LouKeAcpiParseMethod(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t Index = Context->Index;
    string AmlObjectName;
    size_t PackageLength = 0;
    size_t DataOffset = 0;
    UNUSED NAMESPACE_HANDLE EvaluationHandle;
    UNUSED PAML_EXECUTION_INTERNAL_PARAMETER_PASS ParameterStack = Context->InputValue;

    switch(Context->ExecutionState){
        case BUILD: 
            LouKeAcpiParsePackageLength(
                AmlStream, 
                Index, 
                &AmlObjectName,
                &PackageLength,
                0x00
            );

            //LouPrint("NewObjectName:%s EXT_METHOD_OP\n", AmlObjectName);

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
        
        case EVALUATE:
            LouKeAcpiParsePackageLength(
                AmlStream, 
                Index, 
                0x00,
                &PackageLength,
                &DataOffset
            );
            if(AmlStream[DataOffset] != Context->InputSize){
                Context->ExecutionState = INVALID_OPCODE;
                return;
            }
            for(size_t i = DataOffset + 1 ; i < PackageLength; i++){
                if(!LouKeAcpiIsByteOpcode(AmlStream[i])){
                    char FunctionName[5] = {'\0'};
                    memcpy(FunctionName, &AmlStream[i], 4);
                    UNUSED NAMESPACE_HANDLE NestedFunction = LouKeAcpiGetAcpiObjectHandle(FunctionName, Context->CurrentDirectory);
                    size_t ParamCount = LouKeAcpiGetMethodParameterCount(NestedFunction);
                    PAML_EXECUTION_INTERNAL_PARAMETER_PASS* PassingArgs = LouKeMallocArray(PAML_EXECUTION_INTERNAL_PARAMETER_PASS, ParamCount, KERNEL_GENERIC_MEMORY);
                    LouPrint("ParamCount:%d\n", ParamCount);
                    Context->ExecutionState = BUILD_PARAMETER_PASS;
                    Context->Index = i + 4;
                    for(size_t Foo = 0; Foo < ParamCount; Foo++){
                        LouKeAcpiInterperateData(Context);
                        Context->InterpreterReturn = false;
                        PassingArgs[Foo] = (PAML_EXECUTION_INTERNAL_PARAMETER_PASS)Context->ResultValue;
                    }
                    Context->ExecutionState = EVALUATE;


                    


                    //cleanup arguments
                    for(size_t Foo = 0; Foo < ParamCount; Foo++){
                        if(PassingArgs[Foo]->Opcode != AML_NAMESPACE_HANDLE_ARGUMENT){
                            LouKeFree(PassingArgs[Foo]);
                        }
                    }
                    LouKeFree(PassingArgs);
                }
                
                break;
            }
            LouPrint("HERE\n");
            while(1);
            return;

        default:
            break;
    }
    LouPrint("LouKeAcpiParseMethod()\n");
    while(1);
}