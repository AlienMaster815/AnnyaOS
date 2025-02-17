#ifndef _PNH_H
#define _PNG_H

typedef struct _PNG_FILE_HANDLE{
    void* UnpackedBase;;
}PNG_FILE_HANDLE, * PPNG_FILE_HANDLE;

PPNG_FILE_HANDLE LouKeOpenPngImage(string Path);

#endif //PNG_H