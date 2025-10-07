#include <Compiler.h>


static PCOMPILER_CONTEXT CreateCompilerContext(
    LOU_STRING Path
){
    FILE* SourceFile = fopen(Path, "rb");
    size_t ReadCount;

    if(!SourceFile){
        printf("Source File Could Not Be Opened\n");
        return (PCOMPILER_CONTEXT)0x00;
    }

    PCOMPILER_CONTEXT NewContext = (PCOMPILER_CONTEXT)malloc(sizeof(COMPILER_CONTEXT));
    memset(NewContext, 0 , sizeof(COMPILER_CONTEXT));

    NewContext->Path = Path;

    if(fseek(SourceFile, 0, SEEK_END)){
        perror("fseek");
        fclose(SourceFile);
        free(NewContext);
        return (PCOMPILER_CONTEXT)0x00;
    }

    long FileSize = ftell(SourceFile);

    if(FileSize < 0){
        perror("ftell\n");
        fclose(SourceFile);
        free(NewContext);
        return (PCOMPILER_CONTEXT)0x00;
    }

    NewContext->FileSize = (size_t)FileSize;
    printf("FileSize:%zu\n", NewContext->FileSize);

    rewind(SourceFile);

    NewContext->FileContext = malloc(NewContext->FileSize);

    ReadCount = fread(NewContext->FileContext, 1, NewContext->FileSize, SourceFile);
    if(ReadCount != NewContext->FileSize){
        perror("fread");
        fclose(SourceFile);
        free(NewContext);
        return (PCOMPILER_CONTEXT)0x00;
    }

    fclose(SourceFile);
    return NewContext;
}

static int DestroyCompilerContext(
    PCOMPILER_CONTEXT CompilerContext
){
    memset(CompilerContext->FileContext, 0, CompilerContext->FileSize);
    free(CompilerContext->FileContext);
    memset(CompilerContext, 0 , sizeof(COMPILER_CONTEXT));
    free(CompilerContext);
    return 0;
}

typedef struct _COMPILER_DECLARATION_LIST{
    ListHeader      Peers;
    LPWSTR          LStr;
    LOU_STRING      Str;
}COMPILER_DECLARATION_LIST, * PCOMPILER_DECLARATION_LIST;

typedef struct _SOURCE_DECLARATION_LIST{
    ListHeader      Peers;
    LPWSTR          CommonName;
    LPWSTR          SourceName;
}SOURCE_DECLARATION_LIST, * PSOURCE_DECLARATION_LIST;

static PCOMPILER_DECLARATION_LIST MasterList = 0x00;
static PSOURCE_DECLARATION_LIST SourceList = 0x00;

LPWSTR CompilerDeclarationLookup(LOU_STRING Str){
    if (!MasterList)return 0x00;
    if(!MasterList->Peers.NextHeader)return 0x00;
    PCOMPILER_DECLARATION_LIST TmpListMember = (PCOMPILER_DECLARATION_LIST)MasterList->Peers.NextHeader;
    while(TmpListMember){
        if(!strcmp(Str, TmpListMember->Str)){
            return TmpListMember->LStr;
        }        
        TmpListMember = (PCOMPILER_DECLARATION_LIST)TmpListMember->Peers.NextHeader;
    }
    return 0x00;
}


void CreateCompilerDeclarationLookup(LOU_STRING Str){
    if (!MasterList) return;

    PCOMPILER_DECLARATION_LIST TmpListMember = MasterList;
    while(TmpListMember->Peers.NextHeader){
        TmpListMember = (PCOMPILER_DECLARATION_LIST)TmpListMember->Peers.NextHeader;
    }
    TmpListMember->Peers.NextHeader = (PListHeader)LouKeMallocType(COMPILER_DECLARATION_LIST, KERNEL_GENERIC_MEMORY);
    TmpListMember = (PCOMPILER_DECLARATION_LIST)TmpListMember->Peers.NextHeader;
    TmpListMember->LStr = LouKeCreateLpwstr(Str);
    size_t Tmp = strlen(Str) + 1;
    TmpListMember->Str = LouKeMallocArray(char, Tmp , KERNEL_GENERIC_MEMORY);
    for(size_t i = 0 ; i < Tmp; i++){
        TmpListMember->Str[i] = Str[i];
    }
}

LPWSTR SourceDeclarationLookup(
    LPWSTR Buffer, 
    size_t Length
){
    if (!SourceList)return 0x00;
    if(!SourceList->Peers.NextHeader)return 0x00;
    PSOURCE_DECLARATION_LIST TmpListMember = (PSOURCE_DECLARATION_LIST)SourceList->Peers.NextHeader;
    while(TmpListMember){
        if(!Lou_wcsncmp(Buffer, TmpListMember->SourceName, Length) && (Lou_wcslen(TmpListMember->SourceName) == Length)){
            return TmpListMember->CommonName;
        }        
        TmpListMember = (PSOURCE_DECLARATION_LIST)TmpListMember->Peers.NextHeader;
    }
    return 0x00;
}

void CreateSourceDeclarationLookup(
    LPWSTR SourceName, 
    size_t SourceNameLength,
    LPWSTR CommonName,
    size_t CommonNameLength
){
    //TODO: Add Redefinition error handling
    if (!SourceList)return;
    PSOURCE_DECLARATION_LIST TmpListMember = SourceList;
    while(TmpListMember->Peers.NextHeader){
        TmpListMember = (PSOURCE_DECLARATION_LIST)TmpListMember->Peers.NextHeader;
    }
    TmpListMember->Peers.NextHeader = (PListHeader)LouKeMallocType(SOURCE_DECLARATION_LIST, KERNEL_GENERIC_MEMORY);
    TmpListMember = (PSOURCE_DECLARATION_LIST)TmpListMember->Peers.NextHeader;
    TmpListMember->CommonName = LouKeForkWcsStr_s(CommonName, CommonNameLength + 1);
    TmpListMember->SourceName = LouKeForkWcsStr_s(SourceName, SourceNameLength + 1);
}

static LOU_STRING StandardizedDeclarations[] = {
    "ARRAY",
    "DEFINE_BYTE",
    "BYTE",
    "DEFINE_WORD",
    "WORD",
    "DEFINE_DWORD",
    "DWORD",
    "DEFINE_QWORD",
    "QWORD",
    "DEFINE_STRUCTURE",
    "STRUCTURE",
    "DEFINE_STRING",
    "STRING",
    0,
};

LPWSTR CompilerDeclarationGetType(LPWSTR InBuffer, size_t Length){
    //TODO: Add error handling
    //check standardized values
    LPWSTR Result = 0x00;
    for (size_t i = 0; StandardizedDeclarations[i]; i++) {
        LPWSTR Declaration = CompilerDeclarationLookup(StandardizedDeclarations[i]);
        if(!Declaration){
            continue;
        }
        if(!Lou_wcsncmp(InBuffer, Declaration, Length)){
            return Declaration;
        }
    
    }
    return SourceDeclarationLookup(InBuffer, Length);
}


static void CreateDeclarationList(){
    
    MasterList = LouKeMallocType(COMPILER_DECLARATION_LIST, KERNEL_GENERIC_MEMORY);
    SourceList = LouKeMallocType(SOURCE_DECLARATION_LIST, KERNEL_GENERIC_MEMORY);

    CreateCompilerDeclarationLookup("Lousine Kernel Registry File Source");
    CreateCompilerDeclarationLookup("NodeID");
    CreateCompilerDeclarationLookup("BYTE");
    CreateCompilerDeclarationLookup("DEFINE_BYTE");
    CreateCompilerDeclarationLookup("WORD");
    CreateCompilerDeclarationLookup("DEFINE_WORD");
    CreateCompilerDeclarationLookup("DWORD");
    CreateCompilerDeclarationLookup("DEFINE_DWORD");
    CreateCompilerDeclarationLookup("QWORD");
    CreateCompilerDeclarationLookup("DEFINE_QWORD");
    CreateCompilerDeclarationLookup("DEFINE_STRUCTURE");
    CreateCompilerDeclarationLookup("STRUCTURE");
    CreateCompilerDeclarationLookup("ARRAY");
    CreateCompilerDeclarationLookup("STRING");
    CreateCompilerDeclarationLookup("DEFINE_STRING");
    CreateCompilerDeclarationLookup("\"");
    CreateCompilerDeclarationLookup("//");
    CreateCompilerDeclarationLookup("\\");
    CreateCompilerDeclarationLookup("/*");
    CreateCompilerDeclarationLookup("*/");
    CreateCompilerDeclarationLookup("[");
    CreateCompilerDeclarationLookup("]");
    CreateCompilerDeclarationLookup(";");
    CreateCompilerDeclarationLookup(":");
    CreateCompilerDeclarationLookup("=");
    CreateCompilerDeclarationLookup("\n");
    CreateCompilerDeclarationLookup("/");
    

}

static void DestroyDeclarationList(){
    if (!MasterList){
        goto _SOURCE_LIST;
    }
    void* TmpListMember;
    void* Next = MasterList;
    while(Next){
        TmpListMember = Next;
        Next = ((PCOMPILER_DECLARATION_LIST)TmpListMember)->Peers.NextHeader;
        if(((PCOMPILER_DECLARATION_LIST)TmpListMember)->Str)LouKeFree(((PCOMPILER_DECLARATION_LIST)TmpListMember)->Str);
        if(((PCOMPILER_DECLARATION_LIST)TmpListMember)->LStr)LouKeFree(((PCOMPILER_DECLARATION_LIST)TmpListMember)->LStr);
        LouKeFree(TmpListMember);
    }
    _SOURCE_LIST:
    if(!SourceList){
        return;
    }
    Next = SourceList;
    while(Next){
        TmpListMember = Next;
        Next = ((PSOURCE_DECLARATION_LIST)TmpListMember)->Peers.NextHeader;
        if(((PSOURCE_DECLARATION_LIST)TmpListMember)->CommonName)LouKeFree(((PSOURCE_DECLARATION_LIST)TmpListMember)->CommonName);
        if(((PSOURCE_DECLARATION_LIST)TmpListMember)->SourceName)LouKeFree(((PSOURCE_DECLARATION_LIST)TmpListMember)->SourceName);
        LouKeFree(TmpListMember);
    }
}

int main(int argc, char *argv[]){

    if(argc > 2){
        printf("Too Many Parameters\n");
        return -1;
    }

    CreateDeclarationList();

    PCOMPILER_CONTEXT NewContext = CreateCompilerContext(argv[1]);
    if(!NewContext){
        printf("Could Not Create New Compiler Context\n");
        return -1;
    }
        
    LouKeCreateSourceNodes(
        NewContext
    );


    DestroyCompilerContext(NewContext);

    DestroyDeclarationList();

    return 0;
}