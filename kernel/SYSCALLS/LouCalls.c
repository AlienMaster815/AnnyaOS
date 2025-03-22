#include <LouAPI.h>

void LouKeDrsdResetFBDEV(uint64_t* FBDEV);
void LouKeLoadFileCall(uint64_t* Data);
void LouKeDrsdDrawDesktopBackground(
    FILE* ImageFile,
    uint16_t DrsdFileType
);

uintptr_t LouKeCreateUserStackThread(
    void (*Function)(), 
    PVOID FunctionParameters, 
    size_t StackSize
);

uint8_t LouKeGetCurrentTimeMinute();

int LouPrint_s(char* format, va_list args);

void LouUpdateButton(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    PBUTTONHANDLE HBUTTON
);

void LogButtonToProccess(
    PBUTTONHANDLE ButtonHandle, 
    PLOADED_WIN32_BINARY_OBJECT BinaryBind
);

LOUSTATUS LouKeRegisterCallbackProcedure(
    void* CallbackHandler,
    PLOADED_WIN32_BINARY_OBJECT BinaryBind
);

void LouKeDestroyThread(uint64_t Thread);

extern uint64_t RSPPoint;

HANDLE LouKeLoadLibraryA(string Name);

void* LouKeGenericAllocateHeapEx();

void CheckLouCallTables(uint64_t Call, uint64_t DataTmp){
    uint64_t* Tmp2 = (uint64_t*)DataTmp;
    uint64_t Data = (uint64_t)&Tmp2[1];
    switch (Call){
        case LOUVMALLOC:{
            *(uint64_t*)Data = (uint64_t)LouKeMalloc(*(uint64_t*)Data, USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
            return;
        } 
        case LOUCREATETHREAD:{
            uint64_t* Tmp = (uint64_t*)Data;
            UNUSED uintptr_t Result = LouKeCreateUserStackThread((void(*)(PVOID))Tmp[0], (PVOID)Tmp[1], 2 * MEGABYTE);
            Tmp[0] = Result;
            return;
        }
        case LOURESETMONITOR:{
            LouKeDrsdResetFBDEV((uint64_t*)Data);
            return;
        }
        case LOULOADFILE:{
            LouKeLoadFileCall((uint64_t*)Data);
            return;
        }
        case LOUPRINTCALL:{
            uint64_t* Tmp = (uint64_t*)Data;

            *(uint64_t*)Data = LouPrint_s((string)Tmp[0], *(va_list*)Tmp[1]);
            return;
        }
        case LOULOADBITMAP:{
            string File = (string)*(uint64_t*)Data;
            PBITMAP_HANDLE BitHandle = LouKeOpenBitmapImage(File);
            *(uint64_t*)Data = (uint64_t)BitHandle;
            return;
        }
        case LOUDRAWDESKBACK:{
            uint64_t* Tmp = (uint64_t*)Data;
            FILE* File = (FILE*)Tmp[0];
            uint16_t FileType = (uint16_t)Tmp[1];
            LouKeDrsdDrawDesktopBackground(File, FileType);
            return;
        }
        case LOUCREATEWINDOW:{
            uint64_t* Tmp = (uint64_t*)Data;

            uint16_t x = (uint16_t)Tmp[0];
            uint16_t y = (uint16_t)Tmp[1];
            uint16_t Width = (uint16_t)Tmp[2];
            uint16_t Height = (uint16_t)Tmp[3];
            uintptr_t ParentWindow = (uintptr_t)Tmp[4];
            PWINDOW_CHARECTERISTICS Charecteristics = (PWINDOW_CHARECTERISTICS)Tmp[5];
            
            LouCreateWindow(
                x,y,Width,Height,
                ParentWindow, Charecteristics
            );
        
            return;
        }
        case GETSCREENHEIGHT:{
            uint64_t* Datap = (uint64_t*)Data;
            *Datap = (uint64_t)GetScreenBufferHeight();
            return;
        }
        case GETSCREENWIDTH:{
            uint64_t* Datap = (uint64_t*)Data;
            *Datap = (uint64_t)GetScreenBufferWidth();
            return;
        }
        case LOUCREATECANVASBUFF:{
            uint64_t* Tmp = (uint64_t*)Data;
            volatile PWINDHANDLE Return = LouCreateCanvasBuffer(
                (uint16_t)Tmp[0], (uint16_t)Tmp[1],
                (uint16_t)Tmp[2], (uint16_t)Tmp[3],
                (uintptr_t)Tmp[4],
                (PWINDOW_CHARECTERISTICS)Tmp[5]
            );
            Tmp[0] = (uint64_t)Return;
            return;
        }
        case LOUCHAGECANVASCOLOR:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouChangeCanvasBufferColor(
                (volatile PWINDHANDLE)Tmp[0],
                (uint8_t)Tmp[1],
                (uint8_t)Tmp[2],
                (uint8_t)Tmp[3]
            );
            return;
        }
        case LOUCREATEBUTTON:{
            uint64_t* Tmp = (uint64_t*)Data;
            PBUTTONHANDLE Return = LouCreateButton(
                (uint16_t)Tmp[0], (uint16_t)Tmp[1],
                (uint16_t)Tmp[2], (uint16_t)Tmp[3],
                (uintptr_t)Tmp[4],
                (uint64_t)Tmp[5]
            );
            Tmp[0] = (uint64_t)Return;
            return;
        }
        case LOUGETRTCDATA:{
            TIME_T* PTIME = (TIME_T*)*(uint64_t*)Data;
            LouKeGetRtcData(PTIME);
            return;
        }
        case LOUUPDATEBUTTON:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouUpdateButton(
                (uint16_t)Tmp[0],
                (uint16_t)Tmp[1],
                (uint16_t)Tmp[2],
                (uint16_t)Tmp[3],
                (PBUTTONHANDLE)Tmp[4]
            );
            return;
        }
        case LOUREGISTERCALLBACK:{
            uint64_t* Tmp = (uint64_t*)Data;
            uint64_t Result = 0;//LouKeRegisterCallbackProcedure(
            //    (void*)*Tmp,
            //    (PLOADED_WIN32_BINARY_OBJECT)BinObj
            //);

            Tmp[0] = Result;
            return;
        }
        case LOUVFREE:{
            LouPrint("LouVFREE\n");
            while(1);
        }
        case LOUDESTROYTHREAD:{
            //TODO: Do A Privaledge Check
            LouKeDestroyThread(*(uint64_t*)Data);
            return;
        }

        case LOULOADLIBRARYA:{
            uint64_t* Tmp = (uint64_t*)Data;
            Tmp[1] = (uint64_t)LouKeLoadLibraryA((string)Tmp[0]);
            return;
        }
        case LOULOADLIBRARYW:{

            LouPrint("LOULOADLIBRARYW SYSCALL\n");
            while(1);
        }
        case LOULOADLIBRARYEXA:{
            LouPrint("LOULOADLIBRARYEXA SYSCALL\n");
            while(1);
        }
        case LOULOADLIBRARYEXW:{
            LouPrint("LOULOADLIBRARYEXW SYSCALL\n");
            while(1);
        }
        case LOUALLOCHEAPGENERICEX:{
            uint64_t* tmp = (uint64_t*)Data;
            tmp[3] = (uint64_t)LouKeGenericAllocateHeapEx(tmp[0], tmp[1], tmp[2]);
            return;
        }

        default:
        LouPrint("Unkown Call:%d\n", Call);
    }

}