#include <Compiler.h>



errno_t 
LouKeLexerWcsWithTerminator(
    UNUSED LPWSTR              Buffer,
    UNUSED LPWSTR              OpenToken,
    UNUSED LPWSTR              CloseToken,
    UNUSED size_t              Length,
    UNUSED LEXER_HANLDER       Handler,
    UNUSED PVOID               Data
){  
    LPWSTR End = (LPWSTR)(Buffer + Length);
    LPWSTR Open;
    LPWSTR Close;
    while(End - Buffer){
        Open = Lou_wcsnstr(Buffer, OpenToken, End - Buffer);
        if(!Open){
            break;
        }
        Close = Lou_wcsnstr(Open + 1, CloseToken, End - Buffer);
        if(!Close){
            break;
        }
        Handler(Open, Close - Open, Data);
        Buffer = Close + 1;
    }

    return 0;
}