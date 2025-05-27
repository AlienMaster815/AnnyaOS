#include <LouACPI.h>

LOUSTATUS LouKeAcpiInterperateData(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

static mutex_t NameSpace = {0};
static PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT AcpiContext = 0x00;


 LOUSTATUS LouKeAcpiBuildNameSpace(){
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
    AcpiContext = (PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT)LouKeMallocEx(sizeof(LOU_ACPI_NAMESPACE_EXECUTION_CONTEXT), GET_ALIGNMENT(LOU_ACPI_NAMESPACE_EXECUTION_CONTEXT), KERNEL_GENERIC_MEMORY);

    AcpiContext->Length = TableLength;
    AcpiContext->Index = 0;
    AcpiContext->AmlStream = DsdtAmlSpace;
    AcpiContext->RootDirectory = (NAMESPACE_HANDLE)LouKeMallocEx(sizeof(LOU_ACPI_NAMESPACE_OBJECT), GET_ALIGNMENT(LOU_ACPI_NAMESPACE_OBJECT), KERNEL_GENERIC_MEMORY);
    AcpiContext->RootDirectory->Data = DsdtAmlSpace;
    AcpiContext->RootDirectory->DataSize = TableLength;

    AcpiContext->CurrentDirectory = AcpiContext->RootDirectory; 
    AcpiContext->ExecutionState = BUILD;
    Status = LouKeAcpiInterperateData(AcpiContext);
    if(Status != STATUS_SUCCESS){
        LouPrint("Status Unsuccessfull\n");
        while(1);
    }
    LouPrint("LouACPI Aml Interpreter: DSDT Successfully Parsed Building Root Tree\n");

    MutexUnlock(&NameSpace);
    return Status;
}


 size_t AmlNameSpaceNameStringLength(uint8_t* String){
    size_t StringSize = 0;
    bool PrefixesNotParsed = true;
    while(PrefixesNotParsed){
        switch(String[StringSize]){
            case AML_PREFIX_ROOT_CHAR:
            case AML_PREFIX_PARENT_CHAR:
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

 size_t AmlNameSpaceNameStringLengthToUTF8Length(uint8_t* String ){
    size_t StringSize = 0;
    bool PrefixesNotParsed = true;
    while(PrefixesNotParsed){
        switch(String[StringSize]){
            case AML_PREFIX_ROOT_CHAR:
            case AML_PREFIX_PARENT_CHAR:
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

 string CreateUTF8StringFromAcpiNameString(uint8_t* AmlString) {
    size_t i = 0;
    size_t out = 0;
    bool PrefixesNotParsed = true;

    string Result = (string)LouKeAcpiMalloc(
        AcpiContext,
        AmlNameSpaceNameStringLengthToUTF8Length(AmlString)
    );

    while (PrefixesNotParsed) {
        switch (AmlString[i]) {
            case AML_PREFIX_ROOT_CHAR:
            case AML_PREFIX_PARENT_CHAR:
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

 void LouKeAcpiCreateNameSpaceObject(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context,
    bool AddAsSubDirectory,
    string Name,
    uint16_t Opcode,
    size_t DataOffset,
    size_t ObjectSize
){
    NAMESPACE_HANDLE Result = LouKeMallocEx(sizeof(LOU_ACPI_NAMESPACE_OBJECT), GET_ALIGNMENT(LOU_ACPI_NAMESPACE_OBJECT), KERNEL_GENERIC_MEMORY);
    memset(Result, 0 , sizeof(LOU_ACPI_NAMESPACE_OBJECT)); //memset for sanity
    NAMESPACE_HANDLE CurrentDirectory = Context->CurrentDirectory;

    //CurrentDirectory is the top of the directory and each aml
    //tree entry is a data object in the namespace each suntree
    //is a data object with nested data e.g. a scope or device
    if(AddAsSubDirectory){
        //the last sub tree is in the LastSubEntry and if there 
        //is no entry the data is 0x00 which most likely will be
        //the case due to the fact that unlike money devices and
        //scopes grom on trees and unlike the real world there 
        //are not a lot of trees in computers mostly rocks(silicon)
        //if the data isnt 0x00 update the last entries next subtree
        if(CurrentDirectory->LastSubEntry){
            CurrentDirectory->LastSubEntry->SubTree.NextHeader = (PListHeader)Result;
            Result->SubTree.LastHeader = (PListHeader)CurrentDirectory->LastSubEntry;
        }else{
            //and as before the 0x00 means there is no link up so create
            //the linkup
            CurrentDirectory->SubTree.NextHeader = (PListHeader)Result;
        }
        //assign the next last entry
        CurrentDirectory->LastSubEntry = Result;
    }
    //other wise the data is a normal Data, Name, or Execution Object
    //and exists in the Directory we are in AKA the AmlTree
    else{
        //this is the same specification above
        if(CurrentDirectory->LastTreeEntry){
            CurrentDirectory->LastTreeEntry->AmlTree.NextHeader = (PListHeader)Result;
            Result->AmlTree.LastHeader = (PListHeader)CurrentDirectory->LastTreeEntry;
        }else{
            //same again
            CurrentDirectory->AmlTree.NextHeader = (PListHeader)Result;
        }
        CurrentDirectory->LastTreeEntry = Result;
    }

    //the tree should look like this for reference
    // Root -> Data1 -> Data2 -> Data2/LastAmlTreeEntry; AmlTree
    //   | 
    //   V
    //   Scope1 -> Data1 -> Data2; AmlTree/LastTreeEntry; AmlTree
    //   |  |
    //   |  V
    //   |  LastSubEntry = 0x00
    //   V
    //   Scope2 -> Data1 -> Data2/LastTreeEntry; AmlTree
    //   |  |
    //   |  v
    //   |  Device1/LastSubEntry -> Data1 -> Data2/LastTreeEntry; AmlTree
    //   v
    //   Scope3/LastSubEntry -> Data1 -> Data2 -> Data3/LastTreeEntry; AmlTree
    //   ; SubTree
    //fill the new data;

    Result->Name = Name;
    Result->Opcode = Opcode;
    Result->DataSize = ObjectSize;
    Result->Data = &Context->AmlStream[DataOffset];

    Context->ResultValue = (uint64_t)(uint8_t*)Result;
    return;
}

 void* LouKeAcpiMalloc(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context, 
    size_t AllocationSize 
){
    return LouKeMalloc(AllocationSize, KERNEL_GENERIC_MEMORY);
}

NAMESPACE_HANDLE SearchAcpiSpaceDirectory(string SearchName, NAMESPACE_HANDLE Directory){
    NAMESPACE_HANDLE TmpHandle = Directory;
    TmpHandle = (NAMESPACE_HANDLE)Directory->AmlTree.LastHeader;

//    LouPrint("TmpHandleName:%s\n", TmpHandle->Name);

    while(TmpHandle){
        if(strncmp(TmpHandle->Name, "DBG_", 4) == 0){
            return TmpHandle;
        }
        LouPrint("TmpHandle->Name:%s\n", TmpHandle->Name);
        TmpHandle = (NAMESPACE_HANDLE)TmpHandle->AmlTree.LastHeader;
    }
    TmpHandle = (NAMESPACE_HANDLE)Directory->AmlTree.NextHeader;
    while(TmpHandle){
        if(strncmp(TmpHandle->Name, "DBG_", 4) == 0){
            return TmpHandle;
        }
        LouPrint("TmpHandle->Name:%s\n", TmpHandle->Name);
        TmpHandle = (NAMESPACE_HANDLE)TmpHandle->AmlTree.NextHeader;
    }
    return 0x00;
}

NAMESPACE_HANDLE LouKeAcpiGetAcpiObjectHandle(string HandleName, NAMESPACE_HANDLE CurrentHandle){
    NAMESPACE_HANDLE Result = AcpiContext->RootDirectory;
    Result = (NAMESPACE_HANDLE)Result->AmlTree.NextHeader;
    int StringCompareResult;
    if(HandleName[0] == '\\'){
        HandleName++;

        while(Result){
            StringCompareResult = strncmp(Result->Name, HandleName, 4);
            if((StringCompareResult == 0) && (HandleName[4] == '\0')){
                return Result;
            }
            else if((StringCompareResult == 0) && (HandleName[4] != '\0')){
                LouPrint("LouKeAcpiGetAcpiObjectHandle()\n");
                while(1);
            }

            //LouPrint("RootObject:%s\n", Result->Name);
            Result = (NAMESPACE_HANDLE)Result->AmlTree.NextHeader;
        }

        LouPrint("Here\n");
        while(1);
    }


    while(Result){
        StringCompareResult = strncmp(Result->Name, HandleName, 4);
        if((StringCompareResult == 0) && (HandleName[4] == '\0')){
            return Result;
        }

        Result = (NAMESPACE_HANDLE)Result->AmlTree.NextHeader;
    }

    return 0x00;   
}


LOUSTATUS LouKeAcpiExecuteMethod(
    NAMESPACE_HANDLE                        MethodHandle, 
    PAML_EXECUTION_INTERNAL_PARAMETER_PASS  MethodArguments,
    size_t                                  ArgCount
){
    LOU_ACPI_NAMESPACE_EXECUTION_CONTEXT StackContext = {0};
    if(MethodHandle->Opcode != AML_HANDLE_OP_METHOD){
        LouPrint("Aml Handle Not Method\n");
        return STATUS_INVALID_PARAMETER;
    }

    StackContext.CurrentDirectory = MethodHandle;
    StackContext.InputValue = MethodArguments;
    StackContext.InputSize = (uint64_t)ArgCount;
    StackContext.Length = MethodHandle->DataSize;
    StackContext.AmlStream = MethodHandle->Data;
    StackContext.Index = 0;
    StackContext.ExecutionState = EVALUATE;
    return LouKeAcpiInterperateData(&StackContext);
}

size_t LouKeAcpiGetMethodParameterCount(
    NAMESPACE_HANDLE    MethodHandle
){
        size_t DataOffset;
        LouKeAcpiParsePackageLength(
        MethodHandle->Data, 
        0, 
        0x00,
        0x00,
        &DataOffset
    );
    return MethodHandle->Data[DataOffset];
}

NAMESPACE_HANDLE LouKeAcpiCreateBasicAmlObject(uint16_t Opcode, uint64_t Data, size_t DataSize){
    NAMESPACE_HANDLE Result = (NAMESPACE_HANDLE)LouKeMallocEx(sizeof(LOU_ACPI_NAMESPACE_OBJECT), GET_ALIGNMENT(LOU_ACPI_NAMESPACE_OBJECT), KERNEL_GENERIC_MEMORY);
    Result->Data = (uint8_t*)Data;
    Result->DataSize = DataSize;
    Result->Opcode = Opcode;
    return Result;
}