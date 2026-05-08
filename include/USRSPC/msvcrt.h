#ifndef _MSVCRT_GLOBAL_H
#define _MSVCRT_GLOBAL_H

#include <Modulation.h>

#ifndef _MSVCRT_H
#define MSVCRT_API __declspec(dllimport)
#else 
#define MSVCRT_API __declspec(dllexport)
#endif

#define FMODE_O_TEXT    0x00004000
#define FMODE_O_BINARY  0x00008000
#define FMODE_O_WTEXT   0x00010000
#define FMODE_O_U16TEXT 0x00020000
#define FMODE_O_U8TEXT  0x00040000
#define FMODE_O_RAW     FMODE_O_BINARY

MSVCRT_API int _fmode;

#define COMMODE_O_NO_COMMIT 0x00000000
#define COMMODE_O_COMMIT    0x00000800

MSVCRT_API int _commode;

#define SET_APP_TYPE_UNKNOWN_APP    0
#define SET_APP_TYPE_CONSOLE_APP    1
#define SET_APP_TYPE_GUI_APP        2

typedef void (LOU_CDECL *PVFV)(void);

MSVCRT_API
void 
_initterm(
    PVFV* StartFunction,
    PVFV* EndFunction
);

MSVCRT_API
void 
__set_app_type(
    int Type
);

#endif