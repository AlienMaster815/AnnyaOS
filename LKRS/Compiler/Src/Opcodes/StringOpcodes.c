#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Lkrs.h>



static size_t LkrsGetStringNameLength(char* StringBuffer, char** Name){
    size_t Length = 0;
    size_t Fubar = 0;
    bool Null1 = false;
    while(1){
        if(Name){
            if((!Name[0]) && (StringBuffer[Length] != ' ')){
                Name[0] = &StringBuffer[Length];
            }
        }
        if(StringBuffer[Length] == ' '){
            Null1 = true;
            Fubar++;
        }else if(StringBuffer[Length] == '=' || (StringBuffer[Length] == ';')){
            break;
        }else if((Null1) && (StringBuffer[Length] == ' ')){
            return (uint8_t)-1;
        }
        Length++;
    }
    return Length - Fubar;
}

size_t LkrsCountStringDeclarationSize(char* StringBuffer){
    StringBuffer += strlen(LKRS_STRING);
    size_t NameLength = LkrsGetStringNameLength(StringBuffer, 0x00);
    return NameLength + 10; //NameOp, NameSize, Name, QWORD;
}

size_t LkrsCountStringDeclarationSourceLength(char* StringBuffer){
    return LkrsGetLineTerminator(StringBuffer);
}