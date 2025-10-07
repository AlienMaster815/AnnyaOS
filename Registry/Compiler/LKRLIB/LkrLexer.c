#include <Compiler.h>

static LPWSTR GetDeclaration(
    LPWSTR Buffer, 
    LPWSTR Data
){
    int Length = (size_t)(Data - Buffer);
    Buffer += Length;
    int i;
    for(i = 1 ; i < Length; i++){
        if(!Lou_wcsncmp(&Buffer[-i], CompilerDeclarationLookup("="), strlen("="))){
            return 0x00;
        }
        if(!Lou_iswspace(Buffer[-i]))break;
    }
    for(; i < Length; i++){
        if(!Lou_wcsncmp(&Buffer[-i], CompilerDeclarationLookup("="), strlen("="))){
            return 0x00;
        }
        if(Lou_iswspace(Buffer[-i]))break;
    }
    return &Buffer[-i];
}

static errno_t GetNameData(
    LPWSTR Buffer,
    LPWSTR* Name, 
    LPWSTR* NameEnd, 
    LPWSTR Declaration
){
    size_t Length = (size_t)(Declaration - Buffer);
    size_t i = 0;
    
    for(i = 0 ; i < Length; i++){
        if(!Lou_wcsncmp(&Buffer[i], CompilerDeclarationLookup("="), strlen("="))){
            return 1;
        }
        if(!Lou_wcsncmp(&Buffer[i], CompilerDeclarationLookup("\""), strlen("\""))){
            break;
        }
    }
    *Name = &Buffer[++i];
    for(; i < Length; i++){
        if(!Lou_wcsncmp(&Buffer[i], CompilerDeclarationLookup("="), strlen("="))){
            return 1;
        }
        if(!Lou_wcsncmp(&Buffer[i], CompilerDeclarationLookup("\""), strlen("\""))){
            break;
        }
    }
    *NameEnd = &Buffer[i];
    return 0;
}

errno_t 
LouKeLexerGetSyntaxes(
    LPWSTR      Buffer,
    size_t      Length,
    LPWSTR*     Name,
    LPWSTR*     NameEnd,
    LPWSTR*     Declaration,
    LPWSTR*     Data,
    PVOID       Context
){
    errno_t Result = 0;
    if((!NameEnd) || (!Declaration) || (!Data) || (!Name)){
        return EINVAL;
    }else if(!Length){
        *NameEnd = 0;
        *Declaration = 0;
        *Data = 0;
        *Name = 0;
        return EINVAL;
    }

    *Data = Lou_wcsnstr(Buffer, CompilerDeclarationLookup(":"), Length);
    if(!(*Data)){
        LkrDispatchErrorMessage(
            Buffer,
            Length,
            ENO_DECLSEPORATOR,
            Context
        );
        return ENO_DECLSEPORATOR;
    }
    *Declaration = GetDeclaration(Buffer, *Data);
    if(!(*Declaration)){
        LkrDispatchErrorMessage(
            Buffer,
            Length,
            ENO_DECLARATION,
            Context
        );
    }

    Result = GetNameData(
        Buffer,
        Name,
        NameEnd,
        *Declaration
    );
    if(Result){
        LkrDispatchErrorMessage(
            Buffer,
            Length,
            EINVALID_NAME_DECLARATION,
            Context
        );
    }

    return Result;
}

errno_t 
LouKeLexerWcsWithTerminator(
    LPWSTR              Buffer,
    LPWSTR              OpenToken,
    LPWSTR              CloseToken,
    size_t              Length,
    LEXER_HANLDER       Handler,
    PVOID               Data
){  
    LPWSTR End = (LPWSTR)(Buffer + Length);
    LPWSTR Open;
    LPWSTR Close;
    errno_t Result;
    while(End - Buffer){
        Open = Lou_wcsnstr(Buffer, OpenToken, End - Buffer);
        if(!Open){
            break;
        }
        Close = Lou_wcsnstr(Open + 1, CloseToken, End - Buffer);
        if(!Close){
            break;
        }
        Result = Handler(Open, Close - Open, Data);
        if(Result){
            return Result;
        }
        Buffer = Close + 1;
    }

    return 0;
}


errno_t 
LouKeLexerWcsWithoutTerminator(
    LPWSTR              Buffer,
    LPWSTR              OpenToken,
    size_t              Length,
    LEXER_HANLDER       Handler,
    PVOID               Data
){  
    LPWSTR End = (LPWSTR)(Buffer + Length);
    LPWSTR Open;
    errno_t Result;
    while(End - Buffer){
        Open = Lou_wcsnstr(Buffer, OpenToken, End - Buffer);
        if(!Open){
            break;
        }
        Result = Handler(Open, End - Open, Data);
        if(Result){
            return Result;
        }
        Buffer = Open + 1;
    }

    return 0;
}