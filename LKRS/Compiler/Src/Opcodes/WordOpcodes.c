#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Lkrs.h>

static size_t LkrsWordDeclarationGetNameSize(char* WordBuffer){
    size_t Length = 0;
    size_t Fubar = 0;
    bool Null1 = false;
    while(1){
        if(WordBuffer[Length] == ' '){
            Null1 = true;
            Fubar++;
        }else if(WordBuffer[Length] == '=' || (WordBuffer[Length] == ';')){
            break;
        }else if((Null1) && (WordBuffer[Length] == ' ')){
            return (uint8_t)-1;
        }
        Length++;
    }
    return Length - Fubar;
}

size_t LkrsCountWordDeclarationSize(char* WordBuffer){
    WordBuffer += strlen(LKRS_WORD);
    size_t Foo = LkrsWordDeclarationGetNameSize(WordBuffer);
    return Foo + 4; //WordOp, NameLength, (Name), LowByte, HighByte
}

size_t LkrsCountWordDeclarationSourceLength(char* WordBuffer){
    return LkrsGetLineTerminator(WordBuffer);
}