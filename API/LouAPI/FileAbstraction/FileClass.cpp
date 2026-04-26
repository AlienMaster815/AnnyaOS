#include <LouDDK.h>
#include "file.h"

UINT64 LouKeOpenFileGetFileClass(LOUSTR Extention){

    if(!strcmp(Extention, ".EXE") || !strcmp(Extention, ".DLL")){ //TODO Add Case Insensitive 
        return (UINT64)LOU_FILE_COFF;
    }

    return 0;
}
