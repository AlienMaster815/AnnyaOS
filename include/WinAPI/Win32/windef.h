/*
 * Basic types definitions
 *
 * Copyright 1996 Alexandre Julliard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef _WINDEF_H
#define _WINDEF_H

#ifndef WINVER
#define WINVER 0x0500
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define WINAPI __stdcall

#ifdef _USER_MODE_CODE_

#define __int64 long long

#include <stdbool.h>
typedef bool BOOL;
typedef unsigned int UINT;
typedef unsigned long long UINT64;
typedef unsigned long long size_t;
typedef unsigned short wchar_t;

typedef unsigned int DWORD;
typedef unsigned short UINT16;
typedef UINT16 uint16_t;
typedef unsigned int UINT32;
typedef UINT32 uint32_t;
typedef int int32_t;
typedef long long DWORD64;
typedef unsigned long ULONG64;
typedef DWORD64 *PDWORD64;
typedef unsigned char* PBYTE;
typedef unsigned char BYTE;
typedef unsigned int ULONG;
typedef long long LONGLONG;
typedef unsigned int* ULONG_PTR;
typedef ULONG_PTR* PULONG_PTR;
typedef unsigned int* PDWORD;
typedef long long LONG64;
typedef ULONG_PTR KAFFINITY;
typedef short SHORT;
typedef unsigned short USHORT;
typedef unsigned char UCHAR;
typedef ULONG64* PULONG64;

#ifndef _GUID_TYPE 
#define _GUID_TYPE

typedef struct _GUID {
	unsigned char DataByte[16];
} GUID,* LPGUID, UUID, * PGUID, * PUUID;
#endif

typedef GUID IID,*LPIID;
typedef GUID CLSID,*LPCLSID;
typedef GUID FMTID,*LPFMTID;

typedef const char*     PCSZ;
typedef char*           LPSTR;
typedef short           CSHORT, * PCSHORT;
//typedef unsigned int    ULONG; 
//typedef int             LONG; 
typedef ULONG_PTR       KAFFINITY, *PKAFFINITY;
typedef void*           HMODULE;

typedef void* LPVOID;

typedef enum _EXCEPTION_DISPOSITION
{
  ExceptionContinueExecution,
  ExceptionContinueSearch,
  ExceptionNestedException,
  ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;

#define CDECL __cdecl
#endif


typedef unsigned char* PBYTE;
typedef unsigned char BYTE;

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

typedef int* INT_PTR; //defined in common types

typedef INT_PTR (CALLBACK *FARPROC)();
typedef INT_PTR (CALLBACK *NEARPROC)();
typedef INT_PTR (CALLBACK *PROC)();

#define LOBYTE(W)               ((BYTE)((DWORD_PTR)(W) & 0xFF))
#define HIBYTE(W)               ((BYTE)((DWORD_PTR)(W) >> 8) & 0xFF)

#define LOWORD(L)               ((WORD)((LONG_PTR)(L) & 0xFFFF))
#define HIWORD(L)               ((WORD)((LONG_PTR)(L) >> 16) & 0xFFFF)

#define MAKEWORD(low,high)      ((WORD)(((BYTE)((DWORD_PTR)(low) & 0xFF)) | ((WORD)((BYTE)((DWORD_PTR)(high) & 0xFF))) << 8))
#define MAKELONG(low,high)      ((LONG)(((WORD)((DWORD_PTR)(low) & 0xFFFF)) | ((DWORD)((WORD)((DWORD_PTR)(high) & 0xFFFF))) << 16))

#ifdef NO_MIN_MAX
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifdef  min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#endif

#ifdef  MAX_PATH
#undef  MAX_PATH
#endif 

#define MAX_PATH 260
#define HFILE_ERROR ((HFILE)-1)

typedef size_t SIZE;

typedef SIZE  SIZEL;
typedef SIZE* PSIZE;
typedef SIZE* PSIZEL;
typedef SIZE* LPSIZE;
typedef SIZE* LPSIZEL;

typedef struct _POINT{
    long x;
    long y;
}POINT, * PPOINT, * LPPOINT,
    POINTL, * PPOINTL, * LPPOINTL;

typedef struct _POINTS{
    short   x;
    short   y;
}POINTS, * PPOINTS, * LPPOINTS;

typedef struct _RECT{
    long    Left;
    long    Top;
    long    Right;
    long    Bottom;    
}RECT, * PRECT, * LPRECT,
    RECTL, * PRECTL, * LPRECTL;

typedef const RECTL* LPCRECTL;

typedef struct _APP_LOCAL_DEVICE_ID{
    BYTE Value[32];
}APP_LOCAL_DEVICE_ID, * PAPP_LOCAL_DEVICE_ID, * LPAPP_LOCAL_DEVICE_ID;

typedef enum DPI_AWARENESS{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE =  0,
    DPI_AWARENESS_SYSTEM_AWARE = 1,
    DPI_AWARENESS_PER_MONITOR_AWARE = 2,
}DPI_AWARENESS;

#define DPI_AWARENESS_CONTEXT_UNAWARE                   ((DPI_AWARENESS_CONTEXT) - 1)
#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE              ((DPI_AWARENESS_CONTEXT) - 2)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE         ((DPI_AWARENESS_CONTEXT) - 3)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2      ((DPI_AWARENESS_CONTEXT) - 4)
#define DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED         ((DPI_AWARENESS_CONTEXT) - 5)

#ifdef __cplusplus 
}
#endif

typedef enum{
    DPI_HOSTING_BEHAVIOR_INVALID = -1,
    DPI_HOSTING_BEHAVIOR_DEFAULT = 0,
    DPI_HOSTING_BEHAVIOR_MIXED = 1,
}DPI_HOSTING_BEHAVIOR;

#ifndef _GUID_TYPE
#define _GUID_TYPE
typedef struct _GUID {
	unsigned char DataByte[16];
} GUID,* LPGUID, UUID, * PGUID, * PUUID;
#endif

#endif