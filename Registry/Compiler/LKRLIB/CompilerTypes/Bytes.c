#include <Compiler.h>



errno_t LkrAssemblerByteBlock(
    LPWSTR  Name,
    size_t  NameLength,
    uint8_t ByteData,
    PVOID*  Out
){
    if((!Out) || (!Name) || (!NameLength)){
        return EINVAL;
    }
    LPWSTR TmpName = LouKeForkWcsStr_s(Name, NameLength);
    *Out = (PVOID)LkrAllocateNode(TmpName, 1);
    ENCODE_OP(*Out, BYTE_OPCODE);
    LouKeFree(TmpName);
    return LkrFillNodeData(*Out, &ByteData, 1);
}



errno_t LkrHandleByteCreation(
    LPWSTR   Buffer,
    size_t   Length,
    LPWSTR   NameIndex,
    LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    PVOID    Data
){
    errno_t Result = 0;
    PVOID NodeData = 0;
    uint8_t ByteValue = LkrParserStringToUi64(
        DataIndex,
        Length - (size_t)(DataIndex - Buffer)
    );
    if(ByteValue != (ByteValue & 0xFF)){
        return ETYPE_OVERFLOW;
    }
    Result = LkrAssemblerByteBlock(
        NameIndex, 
        NameEndIndex - NameIndex, 
        ByteValue, 
        &NodeData
    );
    if(Result){
        return Result;
    }
    Result = LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        NodeData
    );
    return Result;
}



errno_t LkrHandleByteDefinition(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    //printf("LkrHandleByteDefinition()\n");
    
    LPWSTR NewName = LouKeForkWcsStr_s(NameIndex, NameEndIndex - NameIndex);


    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        (PVOID)LkrCreateStandardTypedefNode(
            NewName,
            BYTE_OPCODE
        )   
    );

    LouKeFree(NewName);

    return 0;
}