#ifndef _ANNYA_COMMAND_PROMT_H
#define _ANNYA_COMMAND_PROMT_H

#include <windows.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

typedef LONG LSTATUS;

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllimport)
LSTATUS 
__stdcall
RegGetValueA(
    HKEY    key,
    LPCSTR  SubKey,
    LPCSTR  Value,
    DWORD   Flags,
    LPDWORD Type,
    PVOID   Data,
    LPDWORD DataCount
);

__declspec(dllimport)
void
__stdcall
SHChangeNotify(
    LONG    EventID,
    UINT    Flags,
    LPCVOID Item1,
    LPCVOID Item2
);

#ifdef __cplusplus
}
#endif

#define SHCNE_ASSOCCHANGED  0x08000000 
#define SHCNF_IDLIST        0x0000

#define RRF_RT_REG_SZ 0x00000002

#define strncasecmp _strnicmp

typedef int             CMD_STATUS;
typedef enum { //supported DOS commands
    CMD_ASSOC = 0, CMD_ATMADM, CMD_CD,
    CMD_CHDIR, CMD_CLS, CMD_COLOR,
    CMD_COPY, CMD_CTTY, CMD_DATE,
    CMD_DEL, CMD_DIR, CMD_ENDLOCAL,
    CMD_ERASE, CMD_EXIT, CMD_LH,
    CMD_LOADHIGH, CMD_LOCK, CMD_MD,
    CMD_MKDIR, CMD_MKLINK, CMD_MOVE, 
    CMD_PATH, CMD_POPD, CMD_PROMPT, 
    CMD_PUSHD, CMD_RD, CMD_REN, 
    CMD_RENAME, CMD_RMDIR, CMD_SET, 
    CMD_SETLOCAL, CMD_START, CMD_SWITCHES, 
    CMD_TIME, CMD_TITLE, CMD_TYPE, 
    CMD_UNLOCK, CMD_VER, CMD_VERIFY, 
    CMD_VOL, CMD_HELP, CMD_CHK_EXTERNAL,
    CMD_CHDRV
}COMMAND;

typedef std::string COMMAND_PARAMETER;

typedef unsigned long ULONG;

#define STATUS_OK               0
#define STATUS_EXIT             1
#define STATUS_EINVAL           2
#define STATUS_NEXT_CMD         3
#define STATUS_UNSUCCESSFUL     4
#define STATUS_DUPLICATE        5

class AnnyaOsCommandEngine;

typedef CMD_STATUS (*DISPATCH_FUNCTION)(COMMAND_PARAMETER Params);

typedef struct _STRING_COMMAND_DIRECTORY{
    const std::string       CommandLineString;
    const COMMAND           CommandMessage;
    DISPATCH_FUNCTION       CommandDispatch;
}STRING_COMMAND_DIRECTORY, * PSTRING_COMMAND_DIRECTORY;

//TODO: Add class for command interpeter

#define DOS_INTERNAL_COMMANDS_COUNT     42
#define DOS_DYNAMIC_COMMAND_COUNT       41

CMD_STATUS DispatchAssocCommand(COMMAND_PARAMETER Params);
CMD_STATUS DispatchColorCommand(COMMAND_PARAMETER Params);
CMD_STATUS DispatchCdCommand(COMMAND_PARAMETER Params);
CMD_STATUS DispatchDirCommand(COMMAND_PARAMETER Params);

#ifndef _COMMAND_MAIN_
extern std::string DriveLetter;
extern std::string DrivePath;
#endif

typedef class AnnyaOsCommandEngine{
    private:
        CMD_STATUS ParseCommand(std::string CommandLine, COMMAND* OutCommand, COMMAND_PARAMETER* OutParams);
        
        const STRING_COMMAND_DIRECTORY Commands[DOS_INTERNAL_COMMANDS_COUNT] = {
            {"ASSOC", CMD_ASSOC, DispatchAssocCommand}, {"ATMADM", CMD_ATMADM, 0x00}, {"CD", CMD_CD, DispatchCdCommand},
            {"CHDIR", CMD_CHDIR, DispatchCdCommand}, {"CLS", CMD_CLS, 0x00}, {"COLOR", CMD_COLOR, DispatchColorCommand},
            {"COPY", CMD_COPY, 0x00}, {"CTTY", CMD_CTTY, 0x00}, {"DATE", CMD_DATE, 0x00},
            {"DEL", CMD_DEL, 0x00}, {"DIR", CMD_DIR, DispatchDirCommand}, {"ENDLOCAL", CMD_ENDLOCAL, 0x00},
            {"ERASE", CMD_ERASE, 0x00}, {"EXIT", CMD_EXIT, 0x00}, {"LH", CMD_LH, 0x00},
            {"LOADHIGH", CMD_LOADHIGH, 0x00}, {"LOCK", CMD_LOCK, 0x00}, {"MD", CMD_MD, 0x00},
            {"MKDIR", CMD_MKDIR, 0x00}, {"MKLINK", CMD_MKLINK, 0x00}, {"MOVE", CMD_MOVE, 0x00},
            {"PATH", CMD_PATH, 0x00}, {"POPD", CMD_POPD, 0x00}, {"PROMPT", CMD_PROMPT, 0x00},
            {"PUSHD", CMD_PUSHD, 0x00}, {"RD", CMD_RD, 0x00}, {"REN", CMD_REN, 0x00},
            {"RENAME", CMD_RENAME, 0x00}, {"RMDIR", CMD_RMDIR, 0x00}, {"SET", CMD_SET, 0x00},
            {"SETLOCAL", CMD_SETLOCAL, 0x00}, {"START", CMD_START, 0x00}, {"SWITCHES", CMD_SWITCHES, 0x00},
            {"TIME", CMD_TIME, 0x00}, {"TITLE", CMD_TITLE, 0x00}, {"TYPE", CMD_TYPE, 0x00},
            {"ULOCK", CMD_UNLOCK, 0x00}, {"VER", CMD_VER, 0x00}, {"VERIFY", CMD_VERIFY, 0x00},
            {"VOL", CMD_VOL, 0x00}, {"HELP", CMD_HELP, 0x00}, {" :", CMD_CHDRV, 0x00},
        };

    public:
        AnnyaOsCommandEngine();
        ~AnnyaOsCommandEngine();
        CMD_STATUS GetMessage(COMMAND* CommandOut, COMMAND_PARAMETER* Params);
        CMD_STATUS DispatchMessage(COMMAND CommandIn, COMMAND_PARAMETER Params);
}ANNYA_COMMNAD_ENGINE, * PANNYA_COMMNAD_ENGINE;



#endif