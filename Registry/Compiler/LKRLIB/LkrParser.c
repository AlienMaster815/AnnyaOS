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