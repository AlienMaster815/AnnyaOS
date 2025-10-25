#ifndef _KULA_API_H
#define _KULA_API_H

typedef struct _KULA_TRANSITION_LAYER_OBECT{
    //Initialization
    LOUSTATUS   (*InitializeSystemSpecificTranitionLayer)(struct _KULA_TRANSITION_LAYER_DATA* KulaData);
    LOUSTATUS   (*DeInitializeSystemSpecificTranitionLayer)(struct _KULA_TRANSITION_LAYER_DATA* KulaData);
    //System Specific Transitions
    LOUSTATUS   (*SwapToSystemSpecicTransitionLayer)(struct _KULA_TRANSITION_LAYER_DATA* KulaData);
    LOUSTATUS   (*SwapFromSystemSpecicTransitionLayer)(struct _KULA_TRANSITION_LAYER_DATA* KulaData);
    //Mod Management
    BOOL        (*ModuleCompatible)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, string FilePath);
    LOUSTATUS   (*LoadModule)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, string FilePath, HMODULE* OutHandle);
    LOUSTATUS   (*UnloadModule)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle);
    //Process Magement
    LOUSTATUS   (*CreateProcess)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle, HANDLE* OutHandle);
    LOUSTATUS   (*StartProcess)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle, HANDLE ProcessHandle);
    LOUSTATUS   (*StopProcess)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle, HANDLE ProcessHandle);
    LOUSTATUS   (*DestroyProcess)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle, HANDLE ProcessHandle);
    //Thread Management
    LOUSTATUS   (*CreateThread)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle,  HANDLE ProcessHandle, HANDLE* OutHandle);
    LOUSTATUS   (*StartThread)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle, HANDLE ProcessHandle, HANDLE* ThreadHandle);
    LOUSTATUS   (*StopThread)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle, HANDLE ProcessHandle, HANDLE* ThreadHandle);
    LOUSTATUS   (*DestroyThread)(struct _KULA_TRANSITION_LAYER_DATA* KulaData, HMODULE ModHandle, HANDLE ProcessHandle, HANDLE* ThreadHandle);
    //Global KULA Data
    BOOL        NativeKulaBinarySupport;
    HMODULE     TransitionLayerModule;    
    //LOUCALL Specific Data System Private Data and Swap Layers need to handle sysenter and sysexit
    UINT64      SystemCallLayerID;
    LOUSTATUS   (*HandleSystemCall)(UINT64 CallID, UINT64* CallParameters);
    //Private Model Data
    PVOID       SystemSpecicPrivate;
}KULA_TRANSITION_LAYER_OBECT, * PKULA_TRANSITION_LAYER_OBECT;

typedef struct _KULA_TRANSITION_LAYER_OBECT_MANAGER{
    ListHeader                      Peers;
    PKULA_TRANSITION_LAYER_OBECT    KulaObject;
}KULA_TRANSITION_LAYER_OBECT_MANAGER, * PKULA_TRANSITION_LAYER_OBECT_MANAGER;


#endif