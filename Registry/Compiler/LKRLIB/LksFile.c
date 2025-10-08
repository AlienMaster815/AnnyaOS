#include <Compiler.h>


static bool LKR_SOURCE_FILE_SANITY_FAILURE(LPWSTR Str){
    return Lou_wcsncmp(CompilerDeclarationLookup("Lousine Kernel Registry File Source"), Str, strlen("Lousine Kernel Registry File Source"));
}

static LKR_PARSER_MANIFEST LkrParserManifest[] = {
    {
        .CommonName = "ARRAY",
        .Handler = LkrHandleArrayCreation,
    },
    {   
        .CommonName = "DEFINE_BYTE",
        .Handler = LkrHandleByteDefinition,
    },
    {
        .CommonName = "BYTE",
        .Handler = LkrHandleByteCreation,
    },
    {
        .CommonName = "DEFINE_WORD",
        .Handler = LkrHandleWordDefinition,
    },
    {
        .CommonName = "WORD",
        .Handler = LkrHandleWordCreation,
    },
    {
        .CommonName = "DEFINE_DWORD",
        .Handler = LkrHandleDwordDefinition,
    },
    {
        .CommonName = "DWORD",
        .Handler = LkrHandleDwordCreation,
    },
    {
        .CommonName = "DEFINE_QWORD",
        .Handler = 0x00,
    },
    {
        .CommonName = "QWORD",
        .Handler = 0x00,
    },
    { 
        .CommonName = "DEFINE_STRUCTURE",
        .Handler = LkrHandleStrcutureDefinnition,
    },
    { 
        .CommonName = "STRUCTURE",
        .Handler = 0x00,
    },
    { 
        .CommonName = "DEFINE_STRING",
        .Handler = 0x00,
    },
    { 
        .CommonName = "STRING",
        .Handler = LkrHandleStringCreation,
    },
    {0},
};

static LKR_PARSER_HANDLER LkrDefinitionToManifest(
    LPWSTR CommonName
){
    if(!CommonName){
        return 0x00;
    }
    for(size_t i = 0 ; LkrParserManifest[i].CommonName; i++){
        if(!Lou_wcsncmp(
                CompilerDeclarationLookup(
                    LkrParserManifest[i].CommonName
                ), 
                CommonName, 
                strlen(
                    LkrParserManifest[i].CommonName
                )
            )
        ){
            return LkrParserManifest[i].Handler;
        }
    }
    return 0x00;
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

    LKR_PARSER_HANDLER Handler = LkrDefinitionToManifest(CompilerDeclarationGetType(DeclarationIndex, (size_t)(DataIndex - DeclarationIndex)));
    if(Handler){
        Result = Handler(        
            Buffer, 
            Length, 
            NameIndex, 
            NameEndIndex, 
            DeclarationIndex, 
            DataIndex,
            Data
        );
    }else{
        LkrDispatchErrorMessage(
            Buffer,
            ENO_DEFINITION,
            Data
        );
        Result = ENO_DEFINITION;
    }
    
    return Result;
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