#ifndef _WDK_LOADER_H
#define _WDK_LOADER_H
#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>

struct _WDF_CLASS_BIND_INFO;

typedef void (*WDF_FUNCTION)();
typedef WDF_FUNCTION* PWDF_FUNCTION;

typedef struct _WDF_VERSION{
    ULONG   MajorVersion;
    ULONG   MinorVersion;
    ULONG   BuildVersion;
}WDF_VERSION, * PWDF_VERSION;

typedef struct _WDF_BIND_INFO{
    ULONG           InfoSize;
    LPWSTR          Component;
    WDF_VERSION     Version;
    ULONG           FunctionCount;
    WDF_FUNCTION    FunctionTable[];
}WDF_BIND_INFO, * PWDF_BIND_INFO;

typedef PVOID PFN_CLASS_BIND_INFO;
typedef PVOID WDF_COMPONENT_GLOBALS, * PWDF_COMPONENT_GLOBALS; 

typedef LOUSTATUS (*PFN_WDF_VERSION_BIND_CLASS)(PWDF_BIND_INFO BindInfo, PWDF_COMPONENT_GLOBALS Globals, struct  _WDF_CLASS_BIND_INFO* ClassBindInfo);
typedef LOUSTATUS (*PFN_WDF_VERSION_UNBIND_CLASS)(PWDF_BIND_INFO BindInfo, PWDF_COMPONENT_GLOBALS Globals, struct  _WDF_CLASS_BIND_INFO* ClassBindInfo);

typedef LOUSTATUS (*PFN_CLIENT_BIND_CLASS)(PFN_WDF_VERSION_BIND_CLASS BindFunction, PWDF_BIND_INFO BindInfo, PWDF_COMPONENT_GLOBALS Globals, struct  _WDF_CLASS_BIND_INFO* ClassBindInfo);
typedef LOUSTATUS (*PFN_CLIENT_UNBIND_CLASS)(PFN_WDF_VERSION_BIND_CLASS BindFunction, PWDF_BIND_INFO BindInfo, PWDF_COMPONENT_GLOBALS Globals, struct  _WDF_CLASS_BIND_INFO* ClassBindInfo);



typedef struct _WDF_CLASS_BIND_INFO{
    ULONG                   InfoSize;
    LPWSTR                  ClassName;
    WDF_VERSION             Version;
    PWDF_FUNCTION           FunctionTable;
    ULONG                   FunctionCount;
    PFN_CLASS_BIND_INFO     BindInfo;
    PFN_CLIENT_BIND_CLASS   ClientBindClass;
    PFN_CLIENT_UNBIND_CLASS ClientUnbindClass;
    PVOID                   ClassModule;
}WDF_CLASS_BIND_INFO, * PWDF_CLASS_BIND_INFO;

#ifdef __cplusplus
}
#endif
#endif