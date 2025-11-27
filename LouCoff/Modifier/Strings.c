#include <Modifier.h>

void StrToLower_s(string Str, SIZE size){
    for(size_t i = 0 ; i < size; i++){
        Str[i] = tolower(Str[i]);
    }
}

void StrToLower(string Str){
    StrToLower_s(Str, strlen(Str));
}