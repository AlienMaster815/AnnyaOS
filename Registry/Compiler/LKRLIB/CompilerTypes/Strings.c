#include <Compiler.h>

errno_t LkrHandleStringCreation(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){

    SanityCheck(DataIndex, Length - (size_t)(DataIndex - Buffer));

    //printf("LkrHandleStringCreation()\n");
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );
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
    //printf("LkrHandleStringDefinition()\n");
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );
    return 0;
}