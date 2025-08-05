// Header: Dispatching.h

#ifndef DISPATCHING_H
#define DISPATCHING_H

#ifdef __cplusplus
extern "C" {
#endif

// ------------------- UNIVERSAL DATA ------------------- //
// Define shared types or macros here
// Example:
// typedef struct HeaderCommon { int CommonID; } HeaderCommon;

typedef enum {
    ANY_PRIORITY = 0,
    LOW_PRIORITY,
    MEDIUM_PRIORITY,
    HIGH_PRIORITY,
    PRIORITY_COUNT
}LOUSINE_USER_MESSAGE_PRIORITY;

typedef enum {
    ANY_EVENT_TYPE = 0,
    MOUSE_EVENT_TYPE,    
    LOUSINE_USER_MESSAGE_COUNT,
}LOUSINE_USER_MESSAGE_TYPE;

typedef struct _LOUSINE_MOUSE_EVENT_MESSAGE{
    INT64   X;
    INT64   Y;
    BOOL    LeftClick;
    BOOL    RightClick;
}LOUSINE_MOUSE_EVENT_MESSAGE, * PLOUSINE_MOUSE_EVENT_MESSAGE;

typedef struct _LOUSINE_USER_SHARED_MESSAGE{
    ListHeader                          Peers;
    LOUSINE_USER_MESSAGE_TYPE           MessageType;
    LOUSINE_USER_MESSAGE_PRIORITY       MessagePriority;
    mutex_t                             MessageMutex;
    union{
        LOUSINE_MOUSE_EVENT_MESSAGE     MouseEvent;
    };
}LOUSINE_USER_SHARED_MESSAGE, * PLOUSINE_USER_SHARED_MESSAGE;


#if defined(_USER_MODE_CODE_)

// ------------------- USER MODE ------------------------ //
#include <Annya.h>    // User mode system includes

// --- Global user-mode data (visible across all DLLs) ---

typedef void (*LOUSINE_MESSAGE_HANDLER)(PLOUSINE_USER_SHARED_MESSAGE);


#ifdef _LOUDLL_
// --- Private user-mode data (specific to MODULE_NAME.DLL) ---
__declspec(dllexport)
bool 
LouUserGetMessage(
    HANDLE*                         Message,
    LOUSINE_USER_MESSAGE_TYPE       Type,
    LOUSINE_USER_MESSAGE_PRIORITY   Priority
);

__declspec(dllexport)
void
LouUserDispatchMessage(
    HANDLE Message
);

__declspec(dllexport)
void 
LouRegisterMouseHandler(
    LOUSINE_MESSAGE_HANDLER     MessageHandler,
    LOUSINE_USER_MESSAGE_TYPE   MessageType
);

#else
// --- Shared user-mode data ---

__declspec(dllimport)
bool 
LouUserGetMessage(
    HANDLE*                         Message,
    LOUSINE_USER_MESSAGE_TYPE       Type,
    LOUSINE_USER_MESSAGE_PRIORITY   Priority
);

__declspec(dllimport)
void
LouUserDispatchMessage(
    HANDLE Message
);

__declspec(dllimport)
void 
LouRegisterMouseHandler(
    LOUSINE_MESSAGE_HANDLER     MessageHandler,
    LOUSINE_USER_MESSAGE_TYPE   MessageType
);

#endif

#else // Kernel mode section

// ------------------- KERNEL MODE ---------------------- //
#ifdef __cplusplus
#include <LouDDK.h>
#else
#include <LouAPI.h>
#endif

#ifdef _KERNEL_MODULE_
// --- Module-specific data (MODULE_NAME.SYS) ---

KERNEL_EXPORT
PLOUSINE_USER_SHARED_MESSAGE LouKeMouseAllocateMessageDevice();

KERNEL_EXPORT
void LouKeMouseUpdateInput(PLOUSINE_USER_SHARED_MESSAGE Message, INT64 X, INT64 Y, BOOL RightClick, BOOL LeftClick);

#else
// --- LOUOSKRNL.EXE-specific data ---

PLOUSINE_USER_SHARED_MESSAGE LouKeCreateNewUserMessage(
    LOUSINE_USER_MESSAGE_TYPE       MessageType,
    LOUSINE_USER_MESSAGE_PRIORITY   Priority
);

void LouKeDispatchNewUserMessage(
    PLOUSINE_USER_SHARED_MESSAGE Message
);

PLOUSINE_USER_SHARED_MESSAGE LouKeMouseAllocateMessageDevice();

void LouKeMouseUpdateInput(PLOUSINE_USER_SHARED_MESSAGE Message, INT64 X, INT64 Y, BOOL RightClick, BOOL LeftClick);

#endif

#endif // end user vs kernel

#ifdef __cplusplus
}
#endif

#endif // DISPATCHING_H
