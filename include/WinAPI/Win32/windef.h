#ifndef _WINDEF_H
#define _WINDEF_H

#ifndef WINVER
#define WINVER 0x0500
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CALLBACK __stdcall

typedef DWORD   COLORREF, * LPCOLORREF;

typedef int HFILE;
typedef void* HANDLE;
typedef HANDLE DPI_AWARENESS_CONTEXT;
typedef HANDLE HACCEL;
typedef HANDLE HBITMAP;
typedef HANDLE HCOLORSPACE;
typedef HANDLE HDC;
typedef HANDLE HDESK;
typedef HANDLE HENHMETAFILE;
typedef HANDLE HFONT;
typedef HANDLE HGLRC;
typedef HANDLE HHOOK;
typedef HANDLE HMENU;
typedef HANDLE HMONITOR;
typedef HANDLE HPALETTE;
typedef HANDLE HPEN;
typedef HANDLE HWINEVENTHOOK;
typedef HANDLE HWND;

typedef HANDLE GLOBALHANDLE;
typedef HANDLE LOCALHANDLE;

typedef int* INT_PTR;

typedef INT_PTR (CALLBACK *FARPROC)();
typedef INT_PTR (CALLBACK *NEARPROC)();
typedef INT_PTR (CALLBACK *PROC)();

//85

#define MAX_PATH 260

#ifdef __cplusplus 
}
#endif
#endif