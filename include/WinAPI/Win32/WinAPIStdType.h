#ifndef _WIN_API_STD_TYPE_H
#define _WIN_API_STD_TYPE_H

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _USER_MODE_CODE_

typedef unsigned int UINT;

typedef void* HTREEITEM;
typedef void* PFNTVCOMPARE;
typedef void* LPARAM;


typedef wchar_t*        LPWSTR;
typedef char*           LPSTR;
typedef LPWSTR          HKEY;
#define LPCSTR    const LPSTR     
#define LPCWSTR   const LPWSTR

typedef void* HWND;
typedef void* TVITEMPART;
typedef void* RECT;
typedef void* POINT;
typedef void* HINSTANCE;

typedef void* TV_ITEMW;

typedef void* PFTASKDIALOGCALLBACK;
typedef void* HICON;
typedef void* TASKDIALOG_BUTTON;
typedef void* TASKDIALOG_COMMON_BUTTON_FLAGS;
typedef void* TASKDIALOG_FLAGS;

typedef uint64_t ULONG64;
typedef void* PVOID;

typedef uint32_t DWORD;
typedef uintptr_t ULONG_PTR;

typedef void* HMODULE;
typedef void* LPVOID;

typedef unsigned long* PULONG;

typedef bool BOOL;
#define TRUE true

typedef struct __type_info_nodeTag{
    void* memPtr;
    struct __type_info_nodeTag* Next;
}__type_info_node;

#define EXCEPTION_MAXIMUM_PARAMETERS 15

typedef struct _DISPATCHER_CONTEXT {
    ULONG64 ControlPc;
    ULONG64 ImageBase;
    void* FunctionEntry;
    ULONG64 EstablisherFrame;
    ULONG64 TargetIp;
    void* ContextRecord;
    void* LanguageHandler;
    PVOID HandlerData;
} DISPATCHER_CONTEXT, *PDISPATCHER_CONTEXT;

typedef struct _EXCEPTION_RECORD {
  DWORD                    ExceptionCode;
  DWORD                    ExceptionFlags;
  struct _EXCEPTION_RECORD *ExceptionRecord;
  PVOID                    ExceptionAddress;
  DWORD                    NumberParameters;
  ULONG_PTR                ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD;

typedef struct _FrameInfo{
    void* EstablishedFrame;
    void* FunctionEntry;
    void* ExitContext;
    struct _FrameInfo* NextFrame;
}FRAME_INFO, * PFRAME_INFO;  






#endif

#ifdef __cplusplus
}
#endif

#endif