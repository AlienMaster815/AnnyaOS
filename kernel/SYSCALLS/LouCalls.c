#include <LouAPI.h>

void LouKeLoadFileCall(uint64_t* Data);
void LouKeCloseFileCall(uint64_t* Data);
void LouKeUpdateShadowClipState(PDRSD_CLIP Clip);
void LouKeGetSystemUpdate(PSYSTEM_STATE_STACK Stack);
uintptr_t LouKeCreateUserStackThread(
    void (*Function)(), 
    PVOID FunctionParameters, 
    size_t StackSize
);
void LouKeUpdateClipSubState(
    PDRSD_CLIP Clip, 
    size_t X, size_t Y, 
    size_t Width, size_t Height
);
uint8_t LouKeGetCurrentTimeMinute();
void LouKeUpdateShadowClipSubState(PDRSD_CLIP Clip, size_t X, size_t Y, size_t Width, size_t Height);
int LouPrint_s(char* format, va_list args);


void LogButtonToProccess(
    PBUTTONHANDLE ButtonHandle, 
    PLOADED_WIN32_BINARY_OBJECT BinaryBind
);

LOUSTATUS LouKeRegisterCallbackProcedure(
    void* CallbackHandler,
    PLOADED_WIN32_BINARY_OBJECT BinaryBind
);

uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

void LouKeDestroyThread(uint64_t Thread);
void LouKeGenericHeapFree(void* heap, void* Address);
extern uint64_t RSPPoint;
void LouKeUpdateClipState(PDRSD_CLIP Clip);
HANDLE LouKeLoadLibraryA(string Name, mutex_t* Lock);
void* LouDrsdGetPlaneInformation(size_t* CountHandle);
void* LouKeGenericAllocateHeapEx(
    void* HeapHandle, 
    size_t AllocationSize,
    size_t Alignment
);
uint64_t LouKeGetThreadIdentification();
void LouKeExitDosMode();
void LouKeDrsdSyncScreen(PDRSD_CLIP_CHAIN Chain);
PDRSD_CLIP LouKeDrsdCreateClip(
    PDRSD_PLANE Plane, 
    size_t X, size_t Y, 
    size_t Width, size_t Height, 
    uint8_t R, uint8_t G, uint8_t B, uint8_t A
);

//returns a void* to a new heap
void* LouKeVirtualAllocUser(
    size_t      CommitSize,     //allocated PhysicalMemory
    size_t      ReservedSize,   //AllocatedVirtual
    uint64_t    PageFlags
);

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
            UNUSED uintptr_t Result = LouKeCreateUserStackThread((void(*)())Tmp[0], (PVOID)Tmp[1], 2 * MEGABYTE);
            Tmp[0] = Result;
            return;
        }
        case LOUEXITDOSMODE:{
            LouKeExitDosMode();
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

            return;
        }
        case LOUGLOBALMALLOC:{
            uint64_t* Tmp = (uint64_t*)Data; 
            Tmp[0] = (uint64_t)LouKeMallocEx(Tmp[1], Tmp[2], USER_GENERIC_MEMORY);
            return;
        }
        case LOUDRSDGETPLANEINFO:{
            uint64_t* Tmp = (uint64_t*)Data;
            Tmp[0] = (uint64_t)LouDrsdGetPlaneInformation((size_t*)Tmp[1]);
            return;
        }
        case LOUDRSDCREATECLIP:{
            uint64_t* Tmp = (uint64_t*)Data;
            Tmp[0] = (uint64_t)LouKeDrsdCreateClip(
                (PDRSD_PLANE)Tmp[1], //Plane
                (size_t)Tmp[2], //X
                (size_t)Tmp[3], //Y
                (size_t)Tmp[4], //Width
                (size_t)Tmp[5], //Height
                (uint8_t)Tmp[6], //R
                (uint8_t)Tmp[7], //G
                (uint8_t)Tmp[8], //B
                (uint8_t)Tmp[9] //A
            );
            return;
        }
        case LOUDRSDSYNCSCREEN:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouKeDrsdSyncScreen((PDRSD_CLIP_CHAIN)Tmp[0]);
            return;
        }
        case LOUUPDTATECLIP:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouKeUpdateClipState((PDRSD_CLIP)Tmp[0]);
            return;
        }
        case LOUGLOBALFREE:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouKeFree((void*)Tmp[0]);
            return;
        }
        case LOUFREEGENERICHEAP:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouKeGenericHeapFree((void*)Tmp[0], (void*)Tmp[1]);
            return;
        }
        case LOUGETRTCDATA:{
            TIME_T* PTIME = (TIME_T*)*(uint64_t*)Data;
            LouKeGetRtcData(PTIME);
            return;
        }
        case LOUDPDATESHADOWCLIP:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouKeUpdateShadowClipState((PDRSD_CLIP)Tmp[0]);
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
            Tmp[1] = (uint64_t)LouKeLoadLibraryA((string)Tmp[0], (mutex_t*)Tmp[2]);
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
            tmp[3] = (uint64_t)LouKeGenericAllocateHeapEx((void*)tmp[0], (size_t)tmp[1], (size_t)tmp[2]);
            return;
        }
        case LOUGETTHREADID:{
            uint64_t* tmp = (uint64_t*)Data;
            tmp[0] = LouKeGetThreadIdentification();
            return;
        }
        case LOUVIRTUALALLOCUSER:{
            uint64_t* tmp =(uint64_t*)Data;
            tmp[3] = (uint64_t)LouKeVirtualAllocUser(tmp[0], tmp[1], tmp[2]);
            return;
        }case LOUAGLFN:{ 
            uint64_t* tmp = (uint64_t*)Data;
            tmp[2] = LouKeLinkerGetAddress((string)(uint8_t*)tmp[0], (string)(uint8_t*)tmp[1]);
            return;
        }
        case LOUCLOSEFILE:{
            LouKeCloseFileCall((uint64_t*)Data);
            return;
        }
        case LOUGETSYSTEMSTATE:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouKeGetSystemUpdate((PSYSTEM_STATE_STACK)Tmp[0]);
            return;
        }case LOUDRSDUPDATECLIPSUBSTATE:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouKeUpdateClipSubState((PDRSD_CLIP)Tmp[0], (size_t)Tmp[1], (size_t)Tmp[2], (size_t)Tmp[3], (size_t)Tmp[4]);
            return;
        }
        case LOUDRSDUPDATESHADOWCLIPSUBSTATE:{
            uint64_t* Tmp = (uint64_t*)Data;
            LouKeUpdateShadowClipSubState((PDRSD_CLIP)Tmp[0],(size_t)Tmp[1], (size_t)Tmp[2], (size_t)Tmp[3], (size_t)Tmp[4]);
            return;
        }
        default:
        LouPrint("Unkown Call:%d\n", Call);
    }

}