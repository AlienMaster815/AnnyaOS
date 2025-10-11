#include <Compiler.h>

errno_t
LkrParserCreateNode(
    LPWSTR  EntryName,
    size_t  EntryLength,
    PVOID   tContext,
    UNUSED PVOID   Data
){
    PCOMPILER_CONTEXT Context = (PCOMPILER_CONTEXT)tContext;
    LPWSTR NewNodeName = 0x00;
    if(Context->NodeContext.CurrentDirectory){
        UNUSED size_t StrLength = Lou_wcslen(Context->NodeContext.CurrentDirectory) + strlen("\\") + EntryLength;
        NewNodeName = LouKeMallocArray(WCHAR, StrLength , KERNEL_GENERIC_MEMORY);
        LPWSTR Cat = NewNodeName;
        Lou_wcsncpy(Cat, Context->NodeContext.CurrentDirectory, Lou_wcslen(Context->NodeContext.CurrentDirectory));
        Cat += Lou_wcslen(Context->NodeContext.CurrentDirectory);
        Lou_wcsncpy(Cat, CompilerDeclarationLookup("\\") , strlen("\\"));
        Cat += 1;
        Lou_wcsncpy(Cat, EntryName, StrLength - (Cat - NewNodeName));
        LPWSTR Tmp = LouKeForkWcsStr_s(NewNodeName, StrLength);
        LouKeFree(NewNodeName);
        NewNodeName = Tmp;
    }else{
        NewNodeName = LouKeForkWcsStr_s(EntryName, EntryLength);
    }

    LouKeAddLousineNodeEntryToHeader(
        Context->CompilerNode,
        NewNodeName,
        Data
    );

    //SanityCheck(NewNodeName, Lou_wcslen(NewNodeName));
    //SanityCheck(EntryName, EntryLength);

    LouKeFree(NewNodeName);

    return 0;
}

uint64_t LkrParserStringToUi64(
    LPWSTR Str,
    size_t Length
){
    uint64_t Converted = 0x00;
    LPWSTR HexChar = Lou_wcspbrk_s(Str, Length, CompilerDeclarationLookup("xX"), strlen("xX"));
    if(HexChar){
        Converted = (uint64_t)Lou__wtoh64_s(&HexChar[-1],  Length - (size_t)(&HexChar[-1] - Str));
    }else {
        Converted = (uint64_t)Lou__wtoi64_s(Str, Length);
    }
    return Converted;
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
        .Handler = LkrHandleQwordDefinition,
    },
    {
        .CommonName = "QWORD",
        .Handler = LkrHandleQwordCreation,
    },
    { 
        .CommonName = "DEFINE_STRUCTURE",
        .Handler = LkrHandleStrcutureDefinition,
    },
    { 
        .CommonName = "STRUCTURE",
        .Handler = LkrHandleStrcutureCreation,
    },
    { 
        .CommonName = "DEFINE_STRING",
        .Handler = LkrHandleStringDefinition,
    },
    { 
        .CommonName = "STRING",
        .Handler = LkrHandleStringCreation,
    },
    {0},
};

LKR_PARSER_HANDLER LkrDefinitionToManifest(
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

size_t LkrParserGetTypeSize(
    LPWSTR Declaration , 
    size_t Length
){
    LPWSTR CommonName = CompilerDeclarationGetType(
        Declaration, 
        Length
    );
    size_t i = 0;
    for(; LkrParserManifest[i].CommonName; i++){
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
            switch(i){
                case 8:
                    return 8;
                case 6:
                    return 4;
                case 4:
                    return 2;
                case 2:
                    return 1;

                default: //TODO: add structure support
                    return 0;
            }
        }   
    }
    return 0;
}