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

FILE* fopen(string PATH);
void fclose(FILE* File);

#define LouKeMallocFileData(x, y)  LouKeMallocEx(x, y, WRITEABLE_PAGE | PRESENT_PAGE)
#define LouKeFreeFileData(x)    LouKeFree(x)

#endif

#ifdef __cplusplus
}
#endif
#endif