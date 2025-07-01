#define _CODECS_

#ifndef _CODECS_DEF_H
#define _CODECS_DEF_H

#include <Annya.h>
#include <USRSPC/DRSD.h>
#include "CodecsTypes.h"
#define CODECS_API __declspec(dllexport)

PCODECS_TYPE_QUERY AnnyaCodecsCreateHandle(
    CODEC_HANDLE_TYPE HandleType, 
    int SubHandle, 
    HANDLE PrivateData
);

#endif