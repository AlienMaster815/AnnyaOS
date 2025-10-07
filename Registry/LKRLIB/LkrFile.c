#include <Compiler.h>


static bool LKR_SOURCE_FILE_SANITY_FAILURE(LPWSTR Str){
    return Lou_wcsncmp(CompilerDeclarationLookup("Lousine Kernel Registry File Source"), Str, strlen("Lousine Kernel Registry File Source"));
}

errno_t LouKeObjectHandler(
    LPWSTR  Buffer,
    size_t  Length,
    PVOID   Data
){
    UNUSED PCOMPILER_CONTEXT Context = (PCOMPILER_CONTEXT)Data;
    errno_t Result = 0;
    LPWSTR NameIndex = 0;
    LPWSTR NameEndIndex = 0;
    LPWSTR DeclarationIndex = 0;
    LPWSTR DataIndex = 0;

    Result = LouKeLexerGetSyntaxes(
        Buffer, 
        Length, 
        &NameIndex, 
        &NameEndIndex, 
        &DeclarationIndex, 
        &DataIndex,
        Data
    );
    if(Result){
        return Result;
    }



    return 0;
}

errno_t
LouKeCreateSourceNodes(
    PCOMPILER_CONTEXT Context
){
    LPWSTR CheckString = (LPWSTR)((uintptr_t)Context->FileContext + sizeof(WCHAR)); 

    SanityCheck(CheckString, strlen("Lousine Kernel Registry File Source"));

    if(LKR_SOURCE_FILE_SANITY_FAILURE(CheckString)){
        printf("Error: Invalid Registry Source File Header\n");
        return EINVAL;
    }


    Context->CompilerNode = LouKeCreateLousineNode(
        LouKeCreateLpwstr("REG_DEFAULT")
    );

    LPWSTR FirstDefinitionBlock = Lou_wcsnstr((LPWSTR)Context->FileContext, CompilerDeclarationLookup("["), Context->FileSize / sizeof(WCHAR));

    LouKeLexerWcsWithTerminator(
        CheckString,
        CompilerDeclarationLookup("\""),
        CompilerDeclarationLookup(";"),
        FirstDefinitionBlock - CheckString,
        LouKeObjectHandler,
        (PVOID)Context
    );

    //LouKeLexerWcsWithTerminator(
    //    Context->FileContext,
    //    CompilerDeclarationLookup("["),
    //    CompilerDeclarationLookup("]"),
    //    Context->
    //);

    LouKeDestroyLousineNodeTree(Context->CompilerNode);

    return 0;
}