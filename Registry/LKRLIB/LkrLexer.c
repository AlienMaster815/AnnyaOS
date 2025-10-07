#include <Compiler.h>


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



    return 0;
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