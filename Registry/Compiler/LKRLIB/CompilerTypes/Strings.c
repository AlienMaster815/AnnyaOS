#include <Compiler.h>

errno_t LkrAssemblerStringBlock(
    LPWSTR  Name,
    LPWSTR  Str,
    PVOID*  Out
){
    errno_t Result = 0;

    *Out = (PVOID)LkrAllocateNode(
        Name,
        Lou_wcslen(Str) * sizeof(WCHAR)
    );

    ENCODE_OP(*Out, STRING_OPCODE);

    Result = LkrFillNodeData(*Out, (uint8_t*)Str, Lou_wcslen(Str) * sizeof(WCHAR));

    if(Result){
        return Result;
    }

    return 0;
}

errno_t LkrHandleStringCreation(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    errno_t Result = 0;
    LPWSTR NewName = LouKeForkWcsStr_s(NameIndex, (size_t)(NameEndIndex - NameIndex));

    LPWSTR TmpData = LouKeForkWcsStr_s(DataIndex + 1, Length - (size_t)(DataIndex - Buffer) - 2);

    PVOID NewNode = 0;

    Result = LkrAssemblerStringBlock(
        NewName,
        TmpData,
        &NewNode
    );

    if(Result){
        return Result;
    }

    //printf("LkrHandleStringCreation()\n");
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        NewNode
    );
    LouKeFree(TmpData);
    LouKeFree(NewName);
    return 0;
}

errno_t LkrHandleStringDefinition(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    LPWSTR NewName = LouKeForkWcsStr_s(NameIndex, NameEndIndex - NameIndex);


    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        (PVOID)LkrCreateStandardTypedefNode(
            NewName,
            STRING_OPCODE
        )   
    );

    LouKeFree(NewName);
    return 0;
}