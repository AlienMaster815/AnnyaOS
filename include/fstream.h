#ifndef _FSTREAM_H
#define _FSTREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdio.h>
#include <kernel/memmory.h>

typedef char* FILE_NAME;

typedef enum {
    UNKOWN_FILE_TYPE = 0,
    COFF_FILE_TYPE = 1,
    ELF_FILE_TYPE = 2,
    BITMAP_FILE_TYPE = 3,
    PNG_FILE_TYPE = 4,
}FILE_TYPE;

typedef enum _LOU_FILE_TYPE{
    LOU_FILE_TYPE_UNDEFINED = 0,
    LOU_FILE_COFF           = 1,
}LOU_FILE_TYPE;

#define FOPEN_KERNEL_GENERIC_MEMORY     0
#define FOPEN_KERNEL_DMA_MEMORY         1
#define FOPEN_USER_GENERIC_MEMORY       2
#define FOPEN_USER_DMA_MEMORY           3
#define FOPEN_MEMORY_FLAGS_MASK         0x03
#define FOPEN_CREATE_ON_FDNE            (1 << 2)
#define FOPEN_READ_ONLY                 (1 << 3)

#ifndef _USER_MODE_CODE_

string GetNextDirectoryName(string PATH);
uint8_t CurrentDirectoryStringLength(string Dir);

bool fseek(string FileName);
PVOID fopen(string PATH, uint64_t PageFlags);
void fclose(PVOID File);
size_t fsize(PVOID File);



#define LouKeMallocFileData(x, y)   LouKeMallocEx(x, y, WRITEABLE_PAGE | PRESENT_PAGE)
static inline void LouKeFreeFileData(PVOID x){
    if(!x){
        return;
    }
    LouKeFree(x);
}        

FILE_TYPE LouKeGetFileType(FILE File);

FILE* LouKeZwOpenFile(
    LOUSTR  FilePath,
    UINT64  PageFlags
);

LOUAPI
SIZE 
LouKeZwGetFileSize(
    FILE* File
);

LOUAPI
UINT64 
LouKeZwGetFileClass(
    FILE* File
);

LOUAPI
LOUSTATUS
LouKeZwReadFileBuffer(
    FILE*   File,
    SIZE    Index,
    SIZE    Length,
    PVOID   Out
);

#endif

#ifdef __cplusplus
}
#endif
#endif