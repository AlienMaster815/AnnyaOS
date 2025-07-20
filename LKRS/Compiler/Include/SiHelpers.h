#ifndef _SI_HELPERS_H
#define _SI_HELPERS_H

#include <Lkrs.h>

static inline size_t LkrsGetLineTerminator(char* Buffer){
    size_t Length = 0;
    while(Buffer[Length] != ';'){
        Length++;
    }
    return Length;
}

#endif