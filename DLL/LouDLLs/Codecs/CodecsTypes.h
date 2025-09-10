#ifndef _CODECS_TYPE_H
#define _CODECS_TYPE_H

#include <Annya.h>

typedef enum {
    PNG = 0,
    BMP = 1,
}CODEC_HANDLE_IMAGE_SUBTYPE;

typedef enum{
    INVALID_HANDLE = 0,
    IMAGE_HANDLE = 1
}CODEC_HANDLE_TYPE;

typedef struct _CODECS_TYPE_QUERY{
    CODEC_HANDLE_TYPE   HandleType;
    union{
        struct{
            CODEC_HANDLE_IMAGE_SUBTYPE ImageSubType;
            HANDLE PrivateDataHandle;
            size_t Width;
            size_t Height;
        }ImageHandleData;
    }HandleInformation;
}CODECS_TYPE_QUERY, * PCODECS_TYPE_QUERY;

static inline UINT32 AnnyaCodecsImageHandleToWidth(void* Handle){
    PCODECS_TYPE_QUERY Query = (PCODECS_TYPE_QUERY)Handle;
    return Query->HandleInformation.ImageHandleData.Width;
}
static inline UINT32 AnnyaCodecsImageHandleToHeight(void* Handle){
    PCODECS_TYPE_QUERY Query = (PCODECS_TYPE_QUERY)Handle;
    return Query->HandleInformation.ImageHandleData.Height;
}

#endif