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

static void LkrPrintError(
    UNUSED LPWSTR   Buffer, 
    UNUSED size_t   Length,
    UNUSED errno_t  Error,
    UNUSED PVOID    Data,
    LOU_STRING      ErrorMessage
){
    PCOMPILER_CONTEXT Context = (PCOMPILER_CONTEXT)Data;
    LPWSTR LineTerminator = Lou_wcsnstr(Buffer, CompilerDeclarationLookup("\n"), Length);
    Length = (size_t)(LineTerminator - Buffer); 

    printf("Error:%d Line:%zu %s:: --> ", Error, GetErrorLine(Context->FileContext, (size_t)(LineTerminator - (LPWSTR)Context->FileContext)), ErrorMessage);

    PrintDocumentBuffer(Buffer, Length);

    printf(" <--\n");
}

static void LkrEnoDeclSeperator(
    UNUSED LPWSTR   Buffer, 
    UNUSED size_t   Length,
    UNUSED errno_t  Error,
    UNUSED PVOID    Data
){
    LkrPrintError(
        Buffer,
        Length,
        Error,
        Data,
        "Missing Seperator"
    );
}

static void LkrEnoDeclaration(
    UNUSED LPWSTR  Buffer,
    UNUSED size_t  Length,
    UNUSED errno_t Error,
    UNUSED PVOID   Data
){
    LkrPrintError(
        Buffer,
        Length,
        Error,
        Data,
        "Missing Declaration"
    );
}


static void LkrEinvalidNameDeclaration(
    UNUSED LPWSTR  Buffer,
    UNUSED size_t  Length,
    UNUSED errno_t Error,
    UNUSED PVOID   Data
){
    LkrPrintError(
        Buffer,
        Length,
        Error,
        Data,
        "Invalid Name Declaration"
    );
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
        case ENO_DECLARATION:{
            LkrEnoDeclaration(
                Buffer,
                Length,
                Error,
                Data
            );
            return;
        }
        case EINVALID_NAME_DECLARATION:{
            LkrEinvalidNameDeclaration(
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