#include <Compiler.h>



errno_t LkrOpcodeByteAssembler(
    UNUSED LPWSTR  Name,
    UNUSED size_t  NameLength,
    UNUSED uint8_t Byte,
    UNUSED PVOID*  Out
){
    if((!Out) || (!Name) || (!NameLength)){
        return EINVAL;
    }

    //PLKR_NODE_ENTRY  



    return 0;
}

errno_t LkrHandleByteCreation(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    //printf("LkrHandleByteCreation()\n");
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );
    return 0;
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
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );
    return 0;
}