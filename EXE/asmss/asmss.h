//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#ifndef _ANNYA_SESSION_MANAGER
#define _ANNYA_SESSION_MANAGER
#include <Annya.h>

typedef struct _REGISTERED_WINDOW_CLASSES_EX_W{
    ListHeader              Peers;
    ATOM                    ClassNameAtom;
    PWINDOW_CLASS_EX_W      WindowClass;
}REGISTERED_WINDOW_CLASSES_EX_W, * PREGISTERED_WINDOW_CLASSES_EX_W;

#endif