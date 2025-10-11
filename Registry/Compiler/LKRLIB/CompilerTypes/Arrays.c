#include <Compiler.h>

//TODO: array implementations

errno_t LkrHandleArrayCreation(
    UNUSED LPWSTR   Buffer,
    UNUSED size_t   Length,
    UNUSED LPWSTR   NameIndex,
    UNUSED LPWSTR   NameEndIndex,
    UNUSED LPWSTR   DeclarationIndex,
    UNUSED LPWSTR   DataIndex,
    UNUSED PVOID    Data
){
    LPWSTR DeclarationEnd = Lou_wcsnstr(DataIndex, CompilerDeclarationLookup(":"), Length - (DataIndex - Buffer)); 
    while(Lou_iswspace(*DataIndex)){
        DataIndex++;
    }
    LPWSTR CommonName = CompilerDeclarationGetType(DataIndex, DeclarationEnd - DataIndex);
    //SanityCheck(CommonName, Lou_wcslen(CommonName));

    //printf("LkrHandleArrayCreation()\n");
    
    if(!Lou_wcscmp(CommonName, CompilerDeclarationLookup("STRUCTURE"))){
        //SanityCheck();


    }else{


    }
    
    LkrParserCreateNode(
        NameIndex,
        NameEndIndex - NameIndex,
        Data,
        0x00
    );
    return 0;
}

