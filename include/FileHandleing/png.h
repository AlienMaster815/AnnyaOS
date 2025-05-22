#ifndef _PNH_H
#define _PNG_H

#define U16_TO_PNG_2_BYTE(x) U16_TO_NETWORK_BYTE_ORDER((x))

typedef struct _PNG_FILE_HANDLE{
    void* UnpackedBase;;
}PNG_FILE_HANDLE, * PPNG_FILE_HANDLE;

PPNG_FILE_HANDLE LouKeOpenPngImage(string Path);

#endif //PNG_H