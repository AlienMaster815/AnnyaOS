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
    UNUSED errno_t  Error,
    UNUSED PVOID    Data,
    LOU_STRING      ErrorMessage
){
    PCOMPILER_CONTEXT Context = (PCOMPILER_CONTEXT)Data;
    LPWSTR LineTerminator = Lou_wcsstr(Buffer, CompilerDeclarationLookup("\n"));
    if(!LineTerminator)LineTerminator = Lou_wcsstr(Buffer, CompilerDeclarationLookup("\0"));
    size_t Length = (size_t)(LineTerminator - Buffer); 

    printf("Error:%d Line:%zu %s:: --> ", Error, GetErrorLine(Context->FileContext, (size_t)(LineTerminator - (LPWSTR)Context->FileContext)), ErrorMessage);

    PrintDocumentBuffer(Buffer, Length);

    printf(" <--\n");
}

static void LkrEnoDeclSeperator(
    UNUSED LPWSTR   Buffer, 
    UNUSED errno_t  Error,
    UNUSED PVOID    Data
){
    LkrPrintError(
        Buffer,
        Error,
        Data,
        "Missing Seperator"
    );
}

static void LkrEnoDeclaration(
    UNUSED LPWSTR  Buffer,
    UNUSED errno_t Error,
    UNUSED PVOID   Data
){
    LkrPrintError(
        Buffer,
        Error,
        Data,
        "Missing Declaration"
    );
}


static void LkrEinvalidNameDeclaration(
    UNUSED LPWSTR  Buffer,
    UNUSED errno_t Error,
    UNUSED PVOID   Data
){
    LkrPrintError(
        Buffer,
        Error,
        Data,
        "Invalid Name Declaration"
    );
}

static void LkrEnoDefinition(
    UNUSED LPWSTR  Buffer,
    UNUSED errno_t Error,
    UNUSED PVOID   Data
){
    LkrPrintError(
        Buffer,
        Error,
        Data,
        "Undeclared Type"
    );
}

void LkrDispatchErrorMessage(
    LPWSTR  Buffer,
    errno_t Error,
    PVOID   Data
){

    switch(Error){
        case ENO_DECLSEPORATOR:{
            LkrEnoDeclSeperator(
                Buffer,
                Error,
                Data
            );
            return;
        }
        case ENO_DECLARATION:{
            LkrEnoDeclaration(
                Buffer,
                Error,
                Data
            );
            return;
        }
        case EINVALID_NAME_DECLARATION:{
            LkrEinvalidNameDeclaration(
                Buffer,
                Error,
                Data
            );
            return;
        }
        case ENO_DEFINITION:{
            LkrEnoDefinition(
                Buffer,
                Error,
                Data
            );
            return;
        }
        default:
            printf("Unkown Compiler Error\n");
    }
}