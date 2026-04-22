#include <Modifier.h>

typedef struct _KULA_BINARY_OBJECT{
    string      ExecutableName;
    string*     FunctionNames;  
    UINT64*     FunctionsPointers;
}KULA_BINARY_OBJECT, * PKULA_BINARY_OBJECT;

typedef struct _KULA_TABLE{
    string*                 ExecutableEntries;
    KULA_BINARY_OBJECT      Executables[];
}KULA_TABLE, * PKULA_TABLE;
 
#define strstr_s(Str, Buff, Length) (memmem((PVOID)Buff, (SIZE)Length, (PVOID)Str, (SIZE)strlen(Str)))

typedef LOUSTATUS (*LEXER_CALLBACK)(PVOID, PVOID, PVOID);

static 
LOUSTATUS
CountCallback(
    PVOID Data,
    PVOID DataEnd,
    PVOID Context
){
    *(UINT8*)Data = *(UINT8*)Data; //to stop the compiler from bitching
    *(UINT8*)DataEnd = *(UINT8*)DataEnd; //to stop the compiler from bitching
    SIZE* Foo = (SIZE*)Context;
    SIZE Bar = *Foo;
    *Foo = Bar + 1;
    return STATUS_SUCCESS;
}

static 
LOUSTATUS
LexerForEachToken(
    string          Token,
    string          Buffer,
    SIZE            Length,
    LEXER_CALLBACK  Callback,
    PVOID           Context
){
    if(!Token || !Buffer || !Length || !Callback){
        return STATUS_INVALID_PARAMETER;
    }

    string Tmp = Buffer;
    SIZE Index = 0;
    LOUSTATUS Status;
    while(Index < Length){
        Tmp = strstr_s(Token, &Buffer[Index], Length - Index);
        if(!Tmp){
            break;
        }
        Status = Callback((PVOID)Tmp, &Buffer[Length - 1], Context);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Index = ((SIZE)Tmp - (SIZE)Buffer) + 1;
    }
    return STATUS_SUCCESS;
}

static 
LOUSTATUS
LexerForEachTokenAndTerminator(
    string              Token,
    string              Terminator,
    string              Buffer,
    SIZE                Length,
    LEXER_CALLBACK      Callback,
    PVOID               Context
){
    if(!Token || !Buffer || !Length || !Callback){
        return STATUS_INVALID_PARAMETER;
    }

    string Tmp1 = Buffer;
    string Tmp2 = 0x00;
    SIZE Index = 0;
    LOUSTATUS Status;
    while(Index < Length){
        Tmp1 = strstr_s(Token, &Buffer[Index], Length - Index);
        Tmp2 = strstr_s(Terminator, Tmp1 + 1, Length - (Index + 1));
        if(!Tmp1 || !Tmp2){
            break;
        }
        Status = Callback((PVOID)Tmp1, Tmp2, Context);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Index = ((SIZE)Tmp2 - (SIZE)Buffer) + 1;
    }
    return STATUS_SUCCESS;
}

static 
SIZE 
GetExecutableCount(
    PVOID   SourceFile,
    SIZE    FileSize
){
    string Tmp = (string)SourceFile;
    SIZE Result = 0;

    LexerForEachToken(
        "EMULTATE_EXECUTABLE", 
        Tmp,
        FileSize,
        CountCallback,
        &Result
    );

    return Result;
}



static
LOUSTATUS 
FunctionCountCallback(
    PVOID Data,
    PVOID DataEnd,
    PVOID Context
){
    return LexerForEachToken(
        ",",
        Data, 
        (SIZE)DataEnd - (SIZE)Data,
        CountCallback,
        Context
    );
}

static 
SIZE 
GetFunctionCount(
    PVOID   SourceFile,
    SIZE    FileSize
){
    string Tmp = (string)SourceFile;
    SIZE Result = 0;

    LexerForEachTokenAndTerminator(
        "{",
        "}",
        Tmp,
        FileSize,
        FunctionCountCallback,
        &Result
    );

    return Result;
}

LOUSTATUS
MakeKulaSection(
    PLOUCOFF_MODIFIER_CONTEXT Context
){
    LOUSTATUS Status = FileContextOpenFile(&Context->SourceFile);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    SIZE ExeCount = GetExecutableCount(Context->SourceFile.FileContext, Context->SourceFile.FileSize);
    if(!ExeCount){
        FileContextCloseFile(&Context->SourceFile);
        return STATUS_INVALID_PARAMETER;
    }
    
    SIZE FunctionCount = GetFunctionCount(Context->SourceFile.FileContext, Context->SourceFile.FileSize);

    printf("Exe      Count:%zu\n", ExeCount);
    printf("Function Count:%zu\n", FunctionCount);

    FileContextCloseFile(&Context->SourceFile);
    return STATUS_SUCCESS;
}