#include <Compiler.h>

errno_t LkrAssemblerQwordBlock(
    LPWSTR      Name,
    size_t      NameLength,
    uint64_t    ByteData,
    PVOID*      Out
){
    if((!Out) || (!Name) || (!NameLength)){
        return EINVAL;
    }
    LPWSTR TmpName = LouKeForkWcsStr_s(Name, NameLength);
    *Out = (PVOID)LkrAllocateNode(TmpName, 8);
    ENCODE_OP(*Out, QWORD_OPCODE);
    LouKeFree(TmpName);
    return LkrFillNodeData(*Out, (uint8_t*)&ByteData, 8);
}

errno_t LkrHandleQwordCreation(
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
    uint32_t QWordValue = LkrParserStringToUi64(
        DataIndex,
        Length - (size_t)(DataIndex - Buffer)
    );
    Result = LkrAssemblerQwordBlock(
        NameIndex, 
        NameEndIndex - NameIndex, 
        QWordValue, 
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



errno_t LkrHandleQwordDefinition(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    //printf("LkrHandleQwordDefinition()\n");
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );
    return 0;
}