#include <Compiler.h>

errno_t LkrAssemblerDwordBlock(
    LPWSTR      Name,
    size_t      NameLength,
    uint32_t    ByteData,
    PVOID*      Out
){
    if((!Out) || (!Name) || (!NameLength)){
        return EINVAL;
    }
    LPWSTR TmpName = LouKeForkWcsStr_s(Name, NameLength);
    *Out = (PVOID)LkrAllocateNode(TmpName, 4);
    ENCODE_OP(*Out, DWORD_OPCODE);
    LouKeFree(TmpName);
    return LkrFillNodeData(*Out, (uint8_t*)&ByteData, 4);
}



errno_t LkrHandleDwordCreation(
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
    uint32_t DWordValue = LkrParserStringToUi64(
        DataIndex,
        Length - (size_t)(DataIndex - Buffer)
    );
    if(DWordValue != (DWordValue & 0xFFFFFFFF)){
        return ETYPE_OVERFLOW;
    }
    Result = LkrAssemblerDwordBlock(
        NameIndex, 
        NameEndIndex - NameIndex, 
        DWordValue, 
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


errno_t LkrHandleDwordDefinition(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    //printf("LkrHandleDwordDefinition()\n");
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );
    return 0;
}