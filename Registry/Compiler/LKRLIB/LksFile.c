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

    LKR_PARSER_HANDLER Handler = LkrDefinitionToManifest(
        CompilerDeclarationGetType(
            DeclarationIndex, 
            (size_t)(DataIndex - DeclarationIndex)
        )
    );
    
    if(Handler){
        Result = Handler(        
            Buffer, 
            Length, 
            NameIndex, 
            NameEndIndex, 
            DeclarationIndex, 
            DataIndex + 1,
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

static size_t GetNameSpaceLength(
    LPWSTR  Buffer,
    size_t  Length,
    PVOID   Data
){
    PCOMPILER_CONTEXT Context = (PCOMPILER_CONTEXT)Data;
    LPWSTR NameSpaceEnd = Lou_wcsstr(Buffer, CompilerDeclarationLookup("["));
    if(!NameSpaceEnd){ //last block may be the terminator so a null is not a tuma
        NameSpaceEnd = (LPWSTR)((uintptr_t)Context->FileContext + (uintptr_t)Context->FileSize);
    }
    Length = NameSpaceEnd - Buffer;
    return Length;
}

errno_t LouKeNameSpaceHandler(
    LPWSTR  Buffer,
    size_t  Length,
    PVOID   Data
){
    errno_t Result = 0;
    
    //printf("LouKeNameSpaceHandler()\n");
    UNUSED PCOMPILER_CONTEXT Context = (PCOMPILER_CONTEXT)Data;
    //enclose NameSpace
    Buffer++;
    Length--;

    LPWSTR NewEntry = LouKeForkWcsStr_s(Buffer, Length);
    
    Result = LouKeAddLousineNodeEntryToHeader(
        Context->CompilerNode,
        NewEntry,
        0x00
    );

    if(Result){
        printf("ERROR Creating Node\n");
        return Result;
    }

    Context->NodeContext.CurrentDirectory = NewEntry;

    Buffer += Length + 2;
    Length = GetNameSpaceLength(
        Buffer,
        Length,
        Data
    );    

    LouKeLexerWcsWithTerminator(
        Buffer,
        CompilerDeclarationLookup("\""),
        CompilerDeclarationLookup(";"),
        Length,
        LouKeObjectHandler,
        Data
    );

    LouKeFree(NewEntry);

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

    LouKeLexerWcsWithTerminator(
        FirstDefinitionBlock,
        CompilerDeclarationLookup("["),
        CompilerDeclarationLookup("]"),
        (size_t)(((LPWSTR)Context->FileSize ) - ((LPWSTR)FirstDefinitionBlock - (LPWSTR)Context->FileContext)),
        LouKeNameSpaceHandler,
        (PVOID)Context
    );

    //SanityCheckNodes(Context->CompilerNode);

    return 0;
}