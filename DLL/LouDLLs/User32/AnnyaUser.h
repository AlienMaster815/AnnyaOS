#include <Annya.h>


struct _HCURSOR;


typedef struct _CURSOR_INFO{
    DWORD               CursorSize;
    DWORD               CursorFlags;
    struct _HCURSOR*    CursorHandle;
    POINT               ScreenPosition;
}CURSOR_INFO, * PCURSOR_INFO, * LPCURSOR_INFO;

typedef struct _HCURSOR{
    CURSOR_INFO     CursorInfo;
    WINAPI_BITMAP   CurrsorMap;
}HCURSOR, * PHCURSOR;




typedef struct _WNDCLASSEX{
    unsigned int    ClassSize;
    unsigned int    ClassStyle;
    WNDPROC         WindowProc;
    int             CbClsExtra;
    HINSTANCE       Instance;
    HICON           Icon;
    HCURSOR         Cursor;
    HBRUSH          BackGround;
    LPCSTR          MenuName; 
    LPCSTR          ClassName;
    HICON           IconSm; 
}WNDCLASSEX, * PWNDCLASSEX, WNDCLASSEXA, * PWNDCLASSEXA;

typedef struct _WNDCLASSEXW{
    unsigned int    ClassSize;
    unsigned int    ClassStyle;
    WNDPROC         WindowProc;
    int             CbClsExtra;
    HINSTANCE       Instance;
    HICON           Icon;
    HCURSOR         Cursor;
    HBRUSH          BackGround;
    LPCSTR          MenuName; 
    LPCSTR          ClassName;
    HICON           IconSm; 
}WNDCLASSEXW, * PWNDCLASSEXW;



#ifndef _USER_32_

#else

#endif