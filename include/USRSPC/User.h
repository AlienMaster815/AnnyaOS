#ifndef _USER32_GLOBAL_H
#define _USER32_GLOBAL_H

#include <Ldm.h>

typedef LONG    LRESULT;
typedef HANDLE  HWND;
typedef WORD    WPARAM;
typedef HANDLE  HICON;
typedef HANDLE  HCURSOR;
typedef HANDLE  HBRUSH;

typedef LRESULT (*WNDPROC)(HWND WindowHandle, UINT Message, WPARAM WordParam, LPARAM LongParam); 

#define HBRUSH_COLOR_3DDKSHADOW                 21
#define HBRUSH_COLOR_3DFACE                     15
#define HBRUSH_COLOR_3DHIGHLIGHT                20
#define HBRUSH_COLOR_3DHLIGHT                   20
#define HBRUSH_COLOR_3DLIGHT                    22
#define HBRUSH_COLOR_3DSHADOW                   16
#define HBRUSH_COLOR_ACTIVEBORDER               10
#define HBRUSH_COLOR_ACTIVECAPTION              2
#define HBRUSH_COLOR_APPWORKSPACE               12
#define HBRUSH_COLOR_BACKGROUND                 1
#define HBRUSH_COLOR_BTNFACE                    15
#define HBRUSH_COLOR_BTNHIGHLIGHT               20
#define HBRUSH_COLOR_BTNSHADOW                  16
#define HBRUSH_COLOR_BTNTEXT                    18
#define HBRUSH_COLOR_CAPTIONTEXT                9
#define HBRUSH_COLOR_DESKTOP                    1
#define HBRUSH_COLOR_GRADIENTACTIVECAPTION      27
#define HBRUSH_COLOR_GRADIENTINACTIVECAPTION    28
#define HBRUSH_COLOR_GRAYTEXT                   17
#define HBRUSH_COLOR_HIGHLIGHT                  13
#define HBRUSH_COLOR_HIGHLIGHTTEXT              14
#define HBRUSH_COLOR_HOTLIGHT                   26
#define HBRUSH_COLOR_INACTIVEBORDER             11
#define HBRUSH_COLOR_INACTIVECAPTION            3
#define HBRUSH_COLOR_INACTIVECAPTIONTEXT        19
#define HBRUSH_COLOR_INFOTEXT                   23
#define HBRUSH_COLOR_MENU                       4
#define HBRUSH_COLOR_MENUHILIGHT                29
#define HBRUSH_COLOR_MENUBAR                    30
#define HBRUSH_COLOR_MENUTEXT                   7
#define HBRUSH_COLOR_SCROLLBAR                  0
#define HBRUSH_COLOR_WINDOW                     5
#define HBRUSH_COLOR_WINDOWFRAME                6              
#define HBRUSH_COLOR_WINDOWTEXT                 8              

typedef struct _WINDOW_CLASS_EX_A{
    UINT        Size;
    UINT        Style;
    WNDPROC     WindowProcedure;
    int         ExtraClassDataSize;
    int         ExtraWindowDataSize;
    HINSTANCE   WndProcInstance;
    HICON       ClassIcon;
    HCURSOR     ClassCursor;
    HBRUSH      BackgroundBrush;
    LPSTR       MenuName;
    LPSTR       ClassName;
    HICON       TaskbarIcon;
}WINDOW_CLASS_EX_A, * PWINDOW_CLASS_EX_A,
    WNDCLASSEXA, * PWNDCLASSEXA, * NPWNDCLASSEXA, * LPWNDCLASSEXA;

typedef struct _WINDOW_CLASS_EX_W{
    UINT        Size;
    UINT        Style;
    WNDPROC     WindowProcedure;
    int         ExtraClassDataSize;
    int         ExtraWindowDataSize;
    HINSTANCE   WndProcInstance;
    HICON       ClassIcon;
    HCURSOR     ClassCursor;
    HBRUSH      BackgroundBrush;
    LPWSTR      MenuName;
    LPWSTR      ClassName;
    HICON       TaskbarIcon;
}WINDOW_CLASS_EX_W, * PWINDOW_CLASS_EX_W,
    WNDCLASSEXW, * PWNDCLASSEXW, * NPWNDCLASSEXW, * LPWNDCLASSEXW;

#define WINDOW_CS_BYTE_ALIGN_CLIENT     0x00001000
#define WINDOW_CS_BYTE_ALIGN_WINDOW     0x00002000
#define WINDOW_CS_CLASS_DC              0x00000040
#define WINDOW_CS_DBL_CLKS              0x00000008
#define WINDOW_CS_DROP_SHADOW           0x00020000
#define WINDOW_CS_GLOBAL_CLASS          0x00004000
#define WINDOW_CS_H_REDRAW              0x00000002
#define WINDOW_CS_NO_CLOSE              0x00000200
#define WINDOW_CS_OWN_DC                0x00000020
#define WINDOW_CS_PARENT_DC             0x00000080
#define WINDOW_CS_SAVE_BITS             0x00000800
#define WINDOW_CS_V_REDRAW              0x00000001


#ifndef _USER32_INTERNAL_H
ANNA_IMPORT ATOM RegisterClassExW(
    const WINDOW_CLASS_EX_W* NewClass
);
#endif
#endif