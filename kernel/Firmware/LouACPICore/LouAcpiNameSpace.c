#include <LouACPI.h>

LOUSTATUS LouKeAcpiInterperateData(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

static mutex_t NameSpace = {0};
static PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT AcpiContext;

static void LouKeAcpiBuildRootNamespace(){

}

SET_OPTIMIZATION(3) LOUSTATUS LouKeAcpiBuildNameSpace(){
    MutexLock(&NameSpace);

    LOU_ACPI_TABLE_POINTER_UNION LouAcpiTable = {0};
    LouAcpiTable.Dsdt = LouKeAcpiGetDsdtTable();
    size_t TableLength;
    uint8_t* DsdtAmlSpace;
    LOUSTATUS Status = STATUS_SUCCESS;
    if(!LouAcpiTable.Dsdt){
        //this Should NEVER HAPPEN!!!!!
        LouPrint("Could Not Find Dsdt\n");
        while(1);
    }
    TableLength = LouAcpiTable.Dsdt->DsdtHeader.Length - sizeof(TABLE_DESCRIPTION_HEADER);
    DsdtAmlSpace = &LouAcpiTable.Dsdt->AmericanMachineLanguage[0];

    LouPrint("Table Length:%h\n", TableLength);
    AcpiContext = LouKeMallocEx(sizeof(LOU_ACPI_NAMESPACE_OBJECT), GET_ALIGNMENT(LOU_ACPI_NAMESPACE_OBJECT), KERNEL_GENERIC_MEMORY);

    AcpiContext->Length = TableLength;
    AcpiContext->Index = 0;
    AcpiContext->AmlStream = DsdtAmlSpace;
    AcpiContext->RootDirectory.DataSize = TableLength;
    AcpiContext->CurrentDirectory = &AcpiContext->RootDirectory;
    AcpiContext->ExecutionState = BUILD;
    AcpiContext->NamePool = LouKeCreateFixedPool(5000, 5, 1,  "DSDTNamePool", 0, KERNEL_GENERIC_MEMORY);
    AcpiContext->AmlObjectPool = LouKeCreateFixedPool(5000, sizeof(LOU_ACPI_NAMESPACE_OBJECT), 1,  "DSDTAmlObjectPool", 0, KERNEL_GENERIC_MEMORY);
    Status = LouKeAcpiInterperateData(AcpiContext);
    if(Status != STATUS_SUCCESS){
        LouPrint("Status Unsuccessfull\n");
        while(1);
    }
    LouPrint("LouACPI Aml Interpreter: DSDT Successfully Parsed Building Root Tree\n");
    LouKeAcpiBuildRootNamespace();

    MutexUnlock(&NameSpace);
    return Status;
}


SET_OPTIMIZATION(3) size_t AmlNameSpaceNameStringLength(uint8_t* String){
    size_t StringSize = 0;
    bool PrefixesNotParsed = true;
    while(PrefixesNotParsed){
        switch(String[StringSize]){
            case AML_PREFIX_ROOT_CAHR:
            case AML_PREFIX_PARENT_CAHR:
                StringSize++;
                break;

            default:
                PrefixesNotParsed = false;
                break;
        }
    }
    switch(String[StringSize]){
        case AML_PREFIX_DUAL_NAME:{
            StringSize += 8; //plus one for either namespace Parser Directory '.' or null
            break;
        }
        case AML_PREFIX_MULTI_NAME:{
            StringSize += 4 * String[StringSize + 1];
            break;
        }
        default:
            StringSize+=4;
    }
    return StringSize;
}

SET_OPTIMIZATION(3) size_t AmlNameSpaceNameStringLengthToUTF8Length(uint8_t* String ){
    size_t StringSize = 0;
    bool PrefixesNotParsed = true;
    while(PrefixesNotParsed){
        switch(String[StringSize]){
            case AML_PREFIX_ROOT_CAHR:
            case AML_PREFIX_PARENT_CAHR:
                StringSize++;
                break;

            default:
                PrefixesNotParsed = false;
                break;
        }
    }
    //LouPrint("Here:%s\n", String);
    switch(String[StringSize]){
        case AML_PREFIX_DUAL_NAME:{
            StringSize += 9; //plus one for either namespace Parser Directory '.' or null
            break;
        }
        case AML_PREFIX_MULTI_NAME:{
            StringSize += 5 * String[StringSize + 1];
            break;
        }
        default:
            StringSize+=5;
    }
    return StringSize;
}

SET_OPTIMIZATION(3) string CreateUTF8StringFromAcpiNameString(uint8_t* AmlString) {
    size_t i = 0;
    size_t out = 0;
    bool PrefixesNotParsed = true;

    string Result = (string)LouKeAcpiMalloc(
        AcpiContext,
        AmlNameSpaceNameStringLengthToUTF8Length(AmlString)
    );

    while (PrefixesNotParsed) {
        switch (AmlString[i]) {
            case AML_PREFIX_ROOT_CAHR:
            case AML_PREFIX_PARENT_CAHR:
                Result[out] = AmlString[i];
                out++;
                i++;
                continue;
            default:
                PrefixesNotParsed = false;
                break;
        }
    }

    switch (AmlString[i]) {
        case AML_PREFIX_MULTI_NAME: {
            uint8_t segCount = AmlString[i + 1];
            for (size_t Foo = 0; Foo < segCount; Foo++) {
                memcpy(&Result[out], &AmlString[i + 2 + (Foo * 4)], 4);
                out += 4;
                if (Foo != segCount - 1)
                    Result[out++] = '.';
            }
            break;
        }
        case AML_PREFIX_DUAL_NAME: {
            for (size_t Foo = 0; Foo < 2; Foo++) {
                memcpy(&Result[out], &AmlString[i + 1 + (Foo * 4)], 4);
                out += 4;
                if (Foo != 1)
                    Result[out++] = '.';
            }
            break;
        }
        default:
            memcpy(&Result[out], &AmlString[i], 4);
            out += 4;
            break;
    }
    Result[out] = '\0';
    return Result;
}


SET_OPTIMIZATION(3) void LouKeAcpiCreateNameSpaceObject(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context,
    bool AddAsSubDirectory,
    string Name,
    uint16_t Opcode,
    size_t DataOffset,
    size_t ObjectSize
){
    NAMESPACE_HANDLE NewObject = (NAMESPACE_HANDLE)LouKeMallocEx(sizeof(LOU_ACPI_NAMESPACE_EXECUTION_CONTEXT), GET_ALIGNMENT(LOU_ACPI_NAMESPACE_EXECUTION_CONTEXT), KERNEL_GENERIC_MEMORY);
    NewObject->Name = Name;
    NewObject->Opcode = Opcode;
    NewObject->DataSize = ObjectSize;
    NewObject->Data = &Context->AmlStream[DataOffset];
    Context->ResultValue = (uint64_t)(uint8_t*)NewObject;
    NAMESPACE_HANDLE CurrentDirectory = Context->CurrentDirectory;
    if(AddAsSubDirectory){
        while(CurrentDirectory->SubTree.NextHeader){
            CurrentDirectory = (NAMESPACE_HANDLE)CurrentDirectory->SubTree.NextHeader;
        }
        CurrentDirectory->SubTree.NextHeader = (PListHeader)NewObject;
        NewObject->SubTree.LastHeader = (PListHeader)CurrentDirectory;
    }else{
        while(CurrentDirectory->AmlTree.NextHeader){
            CurrentDirectory = (NAMESPACE_HANDLE)CurrentDirectory->AmlTree.NextHeader;
        }
        CurrentDirectory->AmlTree.NextHeader = (PListHeader)NewObject;
        NewObject->AmlTree.LastHeader = (PListHeader)CurrentDirectory;
    }
}

SET_OPTIMIZATION(3) void* LouKeAcpiMalloc(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context, 
    size_t AllocationSize 
){
    switch(AllocationSize){
        case 5:{
            return LouKeMallocFromFixedPool(Context->NamePool);
        }
        case sizeof(LOU_ACPI_NAMESPACE_OBJECT):{
            return LouKeMallocFromFixedPool(Context->AmlObjectPool);
        }
        default:
            return LouKeMalloc(AllocationSize, KERNEL_GENERIC_MEMORY);
    }

    LouPrint("LouKeAcpiMalloc()\n");
    while(1);
    return 0x00;//LouKeMallocFromFixedPool(ObjectPool);
}
