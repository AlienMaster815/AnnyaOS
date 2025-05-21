#include <LouACPI.h>

LOUSTATUS LouKeAcpiInterperateData(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

  static size_t CalculateAmlObjectSize(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context,
    size_t Index
){
    uint8_t* AmlStream = Context->AmlStream;
    size_t ObjectSize = 0;
    size_t Length = Context->Length;
    
    for(uint8_t i = 0; i < 2; i++){
        switch(AmlStream[Index + ObjectSize]){
            //count the object size
            case AML_PREFIX_BYTE:{
                ObjectSize+=2;
                break;
            }
            case AML_PREFIX_WORD:{
                ObjectSize+=3;
                break;
            }
            case AML_PREFIX_DWORD:{
                ObjectSize+=5;
                break;
            }
            case AML_PREFIX_QWORD:{
                ObjectSize+=9;
                break;
            }
            default:
                ObjectSize++;
        }
        if((Index + ObjectSize) > Length){
            Context->ExecutionState = INVALID_OPCODE;
            return ObjectSize;
        }
    }
    return ObjectSize;
}


 void LouKeAcpiParseExtendedOpRegion(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
) {
    UNUSED uint8_t* AmlStream = Context->AmlStream;
    UNUSED size_t DataIndex = 0;
    UNUSED size_t Index = Context->Index;
    UNUSED size_t ObjectSize = 0;

    switch(Context->ExecutionState){

        case BUILD:   
            string AmlObjectName = CreateUTF8StringFromAcpiNameString(&AmlStream[Index + 1]);
            LouPrint("NewObjectName:%s EXT_REGION_OP\n", AmlObjectName);
            DataIndex = AmlNameSpaceNameStringLength(&AmlStream[Index + 1]) + 2;
            ObjectSize = CalculateAmlObjectSize(Context, Index + DataIndex);
            if (Context->ExecutionState != BUILD) {
                LouPrint("VM Exec Error: AmlExtRegionOp : ObjectSize\n");
                return;
            }
            LouKeAcpiCreateNameSpaceObject(
                Context,
                false,
                AmlObjectName,
                AML_HANDLE_EXTENDED_OP_REGION,
                Index - 1,
                DataIndex + ObjectSize + 1
            );
            Context->Index += (DataIndex + ObjectSize);
            Context->InputValue = 0;
            return;
        default:
            LouPrint("LouKeAcpiParseExtendedOpRegion()\n");
            while(1);
    }
}


//void LouKeAcpiParseExtendedOpDataRegion( 
//    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
//){

//    LouPrint("LouKeAcpiParseExtendedOpDataRegion()\n");
//    while(1);
//}