#include <Compiler.h>

static errno_t LouKeLineCounterHandler(
    UNUSED  LPWSTR  Buffer,
    UNUSED  size_t  Length,
    PVOID   Data
){
    size_t* LineCount = (size_t*)Data;
    *LineCount = *LineCount + 1; //-Wunused-value
    return 0;
}

static size_t GetErrorLine(
    UNUSED LPWSTR   FileStart,
    UNUSED size_t   SearchLength
){
    size_t i = 0;
    LouKeLexerWcsWithoutTerminator(
        FileStart,
        CompilerDeclarationLookup("\n"),
        SearchLength,
        LouKeLineCounterHandler,
        &i
    );
    return i + 1;
}

static void LkrEnoDeclSeperator(
    UNUSED LPWSTR   Buffer, 
    UNUSED size_t   Length,
    UNUSED errno_t  Error,
    UNUSED PVOID    Data
){
    PCOMPILER_CONTEXT Context = (PCOMPILER_CONTEXT)Data;
    LPWSTR LineTerminator = Lou_wcsnstr(Buffer, CompilerDeclarationLookup("\n"), Length);
    Length = (size_t)(LineTerminator - Buffer); 

    printf("Error:%d Line:%zu Missing Declaration Seperator:: --> ", Error, GetErrorLine(Context->FileContext, (size_t)(LineTerminator - (LPWSTR)Context->FileContext)));


    PrintDocumentBuffer(Buffer, Length);

    printf(" <--\n");
}

void LkrDispatchErrorMessage(
    LPWSTR  Buffer,
    size_t  Length,
    errno_t Error,
    PVOID   Data
){

    switch(Error){
        case ENO_DECLSEPORATOR:{
            LkrEnoDeclSeperator(
                Buffer,
                Length,
                Error,
                Data
            );
            return;
        }
        default:
            printf("Unkown Compiler Error\n");
    }
}