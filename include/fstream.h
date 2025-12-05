#ifndef _FSTREAM_H
#define _FSTREAM_H


#ifdef __cplusplus
#include <NtAPI.h>
KERNEL_IMPORT{
#else 
#include <LouAPI.h>
typedef void* FILE;
#endif

typedef char* FILE_NAME;

#ifndef _KERNEL_MODULE_
string GetNextDirectoryName(string PATH);
uint8_t CurrentDirectoryStringLength(string Dir);

bool fseek(string FileName);
FILE* fopen(string PATH, uint64_t PageFlags);
void fclose(FILE* File);
size_t fsize(FILE* File);

#define LouKeMallocFileData(x, y)  LouKeMallocEx(x, y, WRITEABLE_PAGE | PRESENT_PAGE)
#define LouKeFreeFileData(x)    LouKeFree(x)

typedef enum {
    UNKOWN_FILE_TYPE = 0,
    COFF_FILE_TYPE = 1,
    ELF_FILE_TYPE = 2,
    BITMAP_FILE_TYPE = 3,
    PNG_FILE_TYPE = 4,
}FILE_TYPE;

FILE_TYPE LouKeGetFileType(FILE File);

#endif

#ifdef __cplusplus
}
#endif
#endif