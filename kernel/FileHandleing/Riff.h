#ifndef _RIFF_H
#define _RIFF_H
#define _PRIFF_OBJECT
#include <LouAPI.h>

typedef UINT32                      RIFF_DWORD;
typedef UINT8                       RIFF_BYTE;
typedef UINT32                      RIFF_FOUR_CHARECTER_CODE;
typedef RIFF_FOUR_CHARECTER_CODE    RIFF_CHUNK_ID;
typedef UINT32                      RIFF_CHUNK_SIZE;

typedef struct _RIFF_CHUNK{
    RIFF_CHUNK_ID       ChunkID;
    RIFF_CHUNK_SIZE     ChunkSize;
    RIFF_BYTE           ChunkData[];
}RIFF_CHUNK, * PRIFF_CHUNK;

typedef enum {
    UNKOWN_FILE = 0,
    WAVE_FILE = 1,
}RIFF_FILE_TYPE;

typedef struct _RIFF_WAVE_FILE{
    PRIFF_CHUNK     Fmt;
    PRIFF_CHUNK     Data;
}RIFF_WAVE_FILE, * PRIFF_WAVE_FILE;

typedef struct _RIFF_OBJECT{
    RIFF_FILE_TYPE      FileType;
    PRIFF_CHUNK         Riff;
    union{
        RIFF_WAVE_FILE  WaveFile;
    };
}RIFF_OBJECT, * PRIFF_OBJECT;

#endif