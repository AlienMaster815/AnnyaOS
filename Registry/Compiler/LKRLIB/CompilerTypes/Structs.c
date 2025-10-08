#include <Compiler.h>

errno_t LkrHandleStrcutureCreation(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    //printf("LkrHandleStrcutureCreation()\n");
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );
 

    return 0;
}

errno_t LkrHandleStrcutureDefinition(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    //printf("LkrHandleStrcutureDefinition()\n");
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );

    return 0;
}