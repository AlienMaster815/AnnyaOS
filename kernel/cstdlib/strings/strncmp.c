#include <LouAPI.h>

LOUSTR StrFingFirstFromEndSafe(LOUSTR String, LOUSTR Token, int64_t Limit){
    if(strlen(Token) > Limit){
        return 0x00;
    }
    for(int64_t i = Limit - (int64_t)strlen(Token); i >= 0; i--){
        if(!strncmp(&String[i], Token, strlen(Token))){
            return &String[i];
        }     
    }
    return 0x00;
}

LOUSTR StrFingFirstFromEnd(LOUSTR String, LOUSTR Token){
    return StrFingFirstFromEndSafe(String, Token, strlen(String));
}   