#include <Compiler.h>

errno_t LkrAssemblerWordBlock(
    LPWSTR      Name,
    size_t      NameLength,
    uint16_t    ByteData,
    PVOID*      Out
){
    if((!Out) || (!Name) || (!NameLength)){
        return EINVAL;
    }
    LPWSTR TmpName = LouKeForkWcsStr_s(Name, NameLength);
    *Out = (PVOID)LkrAllocateNode(TmpName, 2);
    ENCODE_OP(*Out, WORD_OPCODE);
    LouKeFree(TmpName);
    return LkrFillNodeData(*Out, (uint8_t*)&ByteData, 2);
}



errno_t LkrHandleWordCreation(
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
    uint16_t WordValue = LkrParserStringToUi64(
        DataIndex,
        Length - (size_t)(DataIndex - Buffer)
    );
    if(WordValue != (WordValue & 0xFFFF)){
        return ETYPE_OVERFLOW;
    }
    Result = LkrAssemblerWordBlock(
        NameIndex, 
        NameEndIndex - NameIndex, 
        WordValue, 
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

errno_t LkrHandleWordDefinition(
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
            WORD_OPCODE
        )   
    );

    LouKeFree(NewName);
    return 0;
}