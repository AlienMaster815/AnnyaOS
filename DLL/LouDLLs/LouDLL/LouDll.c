
//Copyright GPL-2 Tyler Grenier (2025 - 2026)
//x86_64-w64-mingw32-gcc -shared -o LouDll.dll LouDll.c -nostdlib -nodefaultlibs -I../../../Include
#include "LouDll.h"
#include <Security.h>

void LouYeildExecution();

#define FSI_NONE    0
#define FSI_FSAVE   1
#define FSI_XSAVE   2
#define FSI_FXSAVE  3

static UINT64 FsiLevel = 0;

UINT64 LouGetFloatStoreImplementation(){
    return FsiLevel;
}

UINT64 LouGetFSI(){
    UINT64 KulaPacket[2] = {0};
    LouCALL(LOUGETPROCFSI, (UINT64)&KulaPacket[0], 0);
    return KulaPacket[1];
}





LOUDLL_API 
LOUSTATUS 
LouSwapEndianess(
    void* InStreamTmp, 
    void* OutStreamTmp, 
    size_t StreamSize
){
    uint8_t* InStream = (uint8_t*)InStreamTmp; 
    uint8_t* OutStream = (uint8_t*)OutStreamTmp;

    if(RangeInterferes(
        (UINT64)InStreamTmp,
        (UINT64)OutStreamTmp,
        StreamSize,
        StreamSize
    )){
        return STATUS_INVALID_PARAMETER;
    }

    for(size_t i = 0 ; i < StreamSize; i++){
        OutStream[(StreamSize - 1) - i] = InStream[i]; 
    }
    return STATUS_SUCCESS;
}


BOOL NtDllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);



static mutex_t PrintLock;
LOUDLL_API
int LouPrint(char* Str, ...){
    va_list Arg;
    va_start(Arg, Str);
    uint64_t Data[4] = {0};
    Data[0] = 0;
    Data[1] = (uint64_t)Str;
    Data[2] = (uint64_t)&Arg;
    LouCALL(LOUPRINTCALL, (uint64_t)&Data[0], 0);
    va_end(Arg);
    return Data[3];
}

#define BOOTVID_GETBOOTVIDFB 0

static DEFINE_LOU_IOCTL_TABLE(
    LouDllIoCalls,
    DEFINE_OPTIONAL_LOU_IOCTL_ENTRY("BOOTVID.SYS", "GetBootVidFrameBuffer"),
);

LOUDLL_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    BOOL Tmp = true;
    if(ul_reason_for_call == DLL_PROCESS_ATTACH){
        FsiLevel = LouGetFSI();
        LouPrint("LOUDLL.DLL Attatched To New Process\n");
        if(LouInitializeIoCtlTable(LouDllIoCalls) != STATUS_SUCCESS){
            LouPrint("LOUDLL.DLL Failed To Register IOCTLs\n");
        }
    }
    
    //Tmp = NtDllMainCRTStartup(hModule, ul_reason_for_call, lpReserved);
    if(!Tmp){
        return Tmp;
    }
    return TRUE;    
}

LOUDLL_API
PTHREAD AnnyaCreateThread(DWORD (*Function)(PVOID), PVOID FunctionParameters){
    if(!Function){
        return 0x00;
    }
    //uint64_t Result;
    uint64_t Data[3] = {0};
    Data[0] = 0;
    Data[1] = (uint64_t)Function;
    Data[2] = (uint64_t)FunctionParameters;
    LouCALL(LOUCREATETHREAD, (uint64_t)&Data[0] ,0);
    return (PTHREAD)Data[1];
}


LOUDLL_API
void AnnyaDestroyThread(PTHREAD Thread){
    uint64_t Data[2] = {0};
    Data[1] = (uint64_t)Thread;
    LouCALL(LOUDESTROYTHREAD, (uint64_t)&Data[0], 0);
}

LOUDLL_API
void 
uintToHexString(
    uint64_t number, 
    char* hexString
) {
    int i = 0;
    hexString[0] = '0';
    hexString[1] = 'x';
    i = 2;
    char tempString[16];
    int tempIndex = 0;
    if (number == 0) {
        hexString[i++] = '0';
        hexString[i] = '\0';
        return;
    }
    while (number != 0) {
        int digit = number % 16;
        tempString[tempIndex++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        number /= 16;
    }
    while (tempIndex > 0) {
        hexString[i++] = tempString[--tempIndex];
    }
    hexString[i] = '\0';
}


void intToString(uint64_t num, char* str) {
    uint64_t i = 0;

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (num > 0) {
        uint64_t digit = num % 10;
        str[i++] = digit + '0';
        num /= 10;
    }

    str[i] = '\0';

    // Reverse the string
    uint64_t left = 0;
    uint64_t right = i - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

#define VSPRINTF_S_OVERFLOW (((size_t)Buffer - (size_t)BufferStart) + Addition) > BufferCount
#include <stdarg.h>

LOUDLL_API
char* strncpy(char* dest, const char* src, size_t n) {
    char* original_dest = dest;

    // Copy at most 'n' characters from src to dest
    while (*src && n > 0) {
        *dest++ = *src++;
        n--;
    }

    // If 'n' is greater than the length of src, pad with null bytes
    while (n > 0) {
        *dest++ = '\0';
        n--;
    }

    return original_dest;
}

LOUDLL_API
int strncmp(const char* str1, const char* str2, size_t n) {
    // Compare characters until we reach the specified number of characters (n)
    while (n > 0) {
        // Compare the current characters in both strings
        char c1 = *str1++;
        char c2 = *str2++;

        // If the characters are equal or both are null terminators, continue
        if (c1 == c2 || c1 == '\0' || c2 == '\0') {
            // If we've compared n characters or reached the end of either string, return 0
            if (n == 1 || (c1 == '\0' && c2 == '\0')) {
                return 0;
            }
        }
        else {
            // The characters are not equal, return the difference
            return c1 - c2;
        }

        // Decrement the remaining characters to compare
        n--;
    }

    // If we've reached here, the first n characters are equal
    return 0;
}

//strcmp from ACPICA
LOUDLL_API
int
strcmp (
    const char              *String1,
    const char              *String2)
{


    for ( ; (*String1 == *String2); String2++)
    {
        if (!*String1++)
        {
            return (0);
        }
    }

    return ((unsigned char) *String1 - (unsigned char) *String2);
}



static mutex_t VsSprintFLock;

#include <stdarg.h>
#include <cstdint.h>
#include <string.h>

#define BUFFER_OVERFLOW_ERROR -1

LOUDLL_API
int vsprintf_s(char* Buffer, size_t BufferCount, const char* Format, va_list args) {
    if (!Buffer || BufferCount == 0) return BUFFER_OVERFLOW_ERROR;

    size_t Index = 0;
    size_t Addition = 0;
    size_t remainingBuffer = BufferCount - 1; // Reserve space for null terminator
    char* BufferStart = Buffer;

    while (Format[Index] && remainingBuffer > 0) {
        if (Format[Index] == '%') {
            Index++; // Skip '%'

            if (Format[Index] == 's') { // String
                const char* strArg = va_arg(args, const char*);
                Addition = strlen(strArg);
                if (Addition > remainingBuffer) return BUFFER_OVERFLOW_ERROR;
                strncpy(Buffer, strArg, Addition);
                Buffer += Addition;
                remainingBuffer -= Addition;
                Index++;
            } 
            else if (Format[Index] == 'd' || Format[Index] == 'u') { // Integer
                int num = va_arg(args, int);
                char intString[21];
                intToString(num, intString);
                Addition = strlen(intString);
                if (Addition > remainingBuffer) return BUFFER_OVERFLOW_ERROR;
                strncpy(Buffer, intString, Addition);
                Buffer += Addition;
                remainingBuffer -= Addition;
                Index++;
            }
            else if (Format[Index] == 'x' || Format[Index] == 'X') { // Hexadecimal
                uint64_t num = va_arg(args, uint64_t);
                char hexString[21];
                uintToHexString(num, hexString);
                Addition = strlen(hexString);
                if (Addition > remainingBuffer) return BUFFER_OVERFLOW_ERROR;
                strncpy(Buffer, hexString, Addition);
                Buffer += Addition;
                remainingBuffer -= Addition;
                Index++;
            }
            else {
                *Buffer++ = Format[Index++];
                remainingBuffer--;
            }
        } else {
            *Buffer++ = Format[Index++];
            remainingBuffer--;
        }
    }

    *Buffer = '\0'; // Null-terminate the buffer
    return (int)(Buffer - BufferStart); // Return number of characters written
}

LOUDLL_API
int _vsprintf(char* Buffer, size_t BufferCount, const char* Format, ...) {
    va_list Args;
    va_start(Args, Format);
    int result = vsprintf_s(Buffer, BufferCount, Format, Args);
    va_end(Args);
    return result;
}

LOUDLL_API
void GetRtcTimeData(TIME_T* PTIME){
    uint64_t Data[2];
    Data[0] = 0;
    Data[1] = (uint64_t)PTIME;
    LouCALL(LOUGETRTCDATA,(uint64_t)&Data[0],0);
}


static mutex_t LouCallLock;

static inline void TailLouCall(
    uint64_t Call,
    uint64_t Data,
    uint64_t SystemEmulation
){
    asm("INT $0x80");
}

 
LOUDLL_API
void LouCALL(
    uint64_t Call,
    uint64_t Data,
    uint64_t SystemEmulation
){
    TailLouCall(Call, Data, SystemEmulation);
}

static int i = 0;

LOUDLL_API
void AnnyaUserThreadStub(DWORD(*Work)(PVOID), PVOID Param, PVOID Thread){
    LouPrint("User Thread:%h Has Started\n", Thread);
    DWORD Result = Work(Param);    
    LouPrint("User Thread:%h :: Exited With Value:%h\n", Thread, Result);
    AnnyaDestroyThread((void*)Thread);
    while(1){
        LouYeildExecution();
    }
}

typedef struct _ATTACH_THREAD_DATA{
    bool   (*DllEntry)(uint64_t, uint64_t, uint64_t);
    uint64_t DllHandle;
    uint64_t DllCallReason;
    uint64_t DllReserved;
    void   (*LockRelease)(mutex_t* Lock);
    mutex_t  Lock;
}ATTACH_THREAD_DATA, * PATTACH_THREAD_DATA;

LOUDLL_API
DWORD AnnyaAttachDllToProcess(PVOID ThreadData){
    PATTACH_THREAD_DATA DllAttachData = (PATTACH_THREAD_DATA)ThreadData;
    DllAttachData->DllEntry(DllAttachData->DllHandle, DllAttachData->DllCallReason, DllAttachData->DllReserved);
    DllAttachData->LockRelease(&DllAttachData->Lock);
    return 0;
}

LOUDLL_API
void LouTrashAndDumpProcess(){
    LouPrint("LouTrashAndDumpProcess()\n");
    while(1);
}

LOUDLL_API
void* LouGenericAllocateHeapEx(
    void* Heap, 
    size_t AllocationSize,
    size_t Alginment
){

    uint64_t KulaPacket[5] = {0};
    KulaPacket[1] = (uint64_t)Heap;
    KulaPacket[2] = (uint64_t)AllocationSize;
    KulaPacket[3] = (uint64_t)Alginment;
    LouCALL(LOUALLOCHEAPGENERICEX, (uint64_t)&KulaPacket[0], 0);
    return (void*)KulaPacket[4];
}

LOUDLL_API
void LouGenericFreeHeap(void* Heap, void* Address){
    uint64_t KulaPacket[3] = {0};
    KulaPacket[1] = (uint64_t)Heap;
    KulaPacket[2] = (uint64_t)Address;
    LouCALL(LOUFREEGENERICHEAP, (uint64_t)&KulaPacket[0], 0);
}



LOUDLL_API
void* LouVirtualAllocUser(
    size_t      CommitSize,     //allocated PhysicalMemory
    size_t      ReservedSize,   //AllocatedVirtual
    uint64_t    PageFlags
){
    uint64_t KulaPacket[5] = {0};
    KulaPacket[1] = CommitSize;
    KulaPacket[2] = ReservedSize;
    KulaPacket[3] = PageFlags;
    LouCALL(LOUVIRTUALALLOCUSER, (uint64_t)&KulaPacket[0], 0);
    return (void*)KulaPacket[4];
}

LOUDLL_API
void* 
AnnyaGetLibraryFunctionN(
    string ModuleName,
    string FunctionName
){
    uint64_t KulaPacket[4] = {0};
    KulaPacket[1] = (uint64_t)ModuleName;
    KulaPacket[2] = (uint64_t)FunctionName;
    LouCALL(LOUAGLFN, (uint64_t)&KulaPacket[0], 0);
    return (void*)KulaPacket[3]; 
}

LOUDLL_API
void* 
AnnyaGetLibraryFunctionH(
    HANDLE ModuleHandle, 
    string FunctionName
){
    LouPrint("AnnyaGetLibraryFunctionH()\n");
    while(1);
    return 0;
}

LOUDLL_API
void
LouCloseFileA(
    FILE* File
){
    UINT64 KulaPacket[2] = {0, (UINT64)File};
    LouCALL(LOUCLOSEFILE, (uint64_t)&KulaPacket[0], 0);
}

LOUDLL_API
FILE*
LouOpenFileExA(
    string          FileName,
    ACCESS_MASK     AccessMask
){
    uint64_t KulaPacket[4] = {0};
    KulaPacket[1] = (uint64_t)FileName;
    KulaPacket[3] = (uint64_t)AccessMask;
    LouCALL(LOULOADFILE, (uint64_t)&KulaPacket[0], 0);
    return (void*)KulaPacket[1]; 
}

LOUDLL_API
FILE*
LouOpenFileA(
    string FileName
){
    return LouOpenFileExA(
        FileName,
        ACCESS_MASK_GENERIC_ALL
    );
}

LOUDLL_API
void 
LouExitDosMode(){
    uint64_t KulaPacket = 0;
    LouCALL(LOUEXITDOSMODE, (uint64_t)&KulaPacket, 0);
}

LOUDLL_API
void* LouMemSet(void* dest, int value, size_t count) {
    unsigned char* ptr = (unsigned char*)dest;
    unsigned char val = (unsigned char)value;

    for (size_t i = 0; i < count; i++) {
        ptr[i] = val;
    }

    return dest;
}

LOUDLL_API
void LouYeildExecution(){
    uint64_t KulaPacket;
    LouCALL(LOUYEILDEXE, (uint64_t)&KulaPacket, 0);
}

LOUDLL_API
void ReleaseLoadLibraryALock(mutex_t* Mutex){
    MutexUnlock(Mutex);
}

struct ProcessLoaderParameters{
    mutex_t                 Lock;
    UINT64*                 ModEntrys;
    SIZE                    StackReserve;
    SIZE                    StackCommit;
    SIZE                    HeapReserved;
    SIZE                    HeapCommit;
    UINT16                  Subsystem;
    PVOID                   TlsData;
    PVOID*                  TlsCallbacks;
};

UINT64 LouGetPeb();
UINT64 LouGetTeb();

LOUDLL_API
DWORD LouProcessInitThread(
    PVOID   Data
){
    struct ProcessLoaderParameters* LoaderData = (struct ProcessLoaderParameters*)Data;
    UINT64* Tmp = LoaderData->ModEntrys; 
    UINT64 CurrentEntry = Tmp[Tmp[0]];
    bool   (*DllEntry)(uint64_t, uint64_t, uint64_t);

    
    UINT64 Peb = LouGetPeb();
    PTEB Teb = (PTEB)LouGetTeb();


    Teb->ThreadLocalStoragePointer = LoaderData->TlsData;



    if(LoaderData->TlsCallbacks){
        LouPrint("Tls Trees:%d\n", (SIZE)LoaderData->TlsCallbacks[0]);
        SIZE Trees = (SIZE)LoaderData->TlsCallbacks[0];
        for(SIZE i = 0 ; i < Trees; i++){
            PVOID* TmpBranch = (PVOID*)LoaderData->TlsCallbacks[i + 1];
            if(TmpBranch){
                LouPrint("Tls Branches:%d\n", TmpBranch[0]);
                SIZE Branches = (SIZE)TmpBranch[0];
                for(SIZE j = 0 ; j < i; j++){
                    DllEntry = TmpBranch[j + 1];
                    if(DllEntry){
                        DllEntry((uint64_t)DllEntry, DLL_PROCESS_ATTACH, 0);
                    }
                }
            }
        }
    }

    for(size_t i = 0 ; Tmp[i + 1] != CurrentEntry; i++){
        DllEntry = (PVOID)Tmp[i + 1];
        DllEntry((uint64_t)DllEntry, DLL_PROCESS_ATTACH, 0);
    }

    MutexUnlock(&LoaderData->Lock);

    if(Teb->ThreadLocalStoragePointer){
        LouPrint("HERE\n");
        while(1);
    }

    int (*ProcessEntry)(UINT64);
    ProcessEntry = (PVOID)CurrentEntry;

    return ProcessEntry(Peb);
}

LOUDLL_API
void 
LouSystemShutdown(SHUTDOWN_ACTION ShutDown){
    uint64_t Data[2] = {0};
    Data[1] = (uint64_t)ShutDown;
    LouCALL(LOUSHUTDOWN, (uint64_t)&Data[0], 0);
}

LOUDLL_API 
LOUSTATUS 
LouInitializeIoCtlTable(
    PVOID Table
){
    UINT64 KulaPacket[3] = {0, (UINT64)Table, 0};
    LouCALL(LOUINITIOCTLTABLE, (UINT64)&KulaPacket[0], 0);
    return (LOUSTATUS)KulaPacket[2];
}

LOUDLL_API 
LOUSTATUS 
LouCallIoCtlFunction(
    PLOU_IOCTL_TABLE_ENTRY  Entry, 
    UINT64*                 IoKulaPacket
){
    UINT64 KulaPacket[4] = {0, (UINT64)Entry, (UINT64)IoKulaPacket, 0};
    LouCALL(LOUIOCTLCALLFUNC, (UINT64)&KulaPacket[0], 0);
    return (LOUSTATUS)KulaPacket[3];
}

LOUDLL_API
LOUSTATUS
LouGetBootFrameBuffer(
    PBOOTVID_FRAMEBUFFER* OutFb
){
    if(!OutFb){
        return STATUS_INVALID_PARAMETER;
    }
    UINT64 FbOut = 0x00;
    LOUSTATUS Status = LouCallIoCtlFunction(&LouDllIoCalls[BOOTVID_GETBOOTVIDFB], &FbOut);
    if(Status != STATUS_SUCCESS){
        LouPrint("LouGetBootFrameBuffer():IOCTL Call Failed\n");
        return Status;
    }
    *OutFb = (PBOOTVID_FRAMEBUFFER)FbOut;
    return STATUS_SUCCESS;
}

LOUDLL_API
LOUSTATUS 
LouGetProcessName(
    HANDLE  ProcessHandle,
    PSTRING OutString
){
    UINT64 KulaPacket[4] = {0, 0, (UINT64)ProcessHandle, (UINT64)OutString};
    LouCALL(LOUGETPROCNAME, (UINT64)&KulaPacket[0], 0);
    return (LOUSTATUS)KulaPacket[1];
}

LOUDLL_API
LOUSTATUS
LouGetCurrentProccessHandle(
    PHANDLE     OutHandle,
    ACCESS_MASK RequestedAccess
){
    UINT64 KulaPacket[4] = {0, 0 , (UINT64)OutHandle, (UINT64)RequestedAccess};
    LouCALL(LOUGETCURRENTPROCHANDLE, (UINT64)&KulaPacket[0], 0);
    return (LOUSTATUS)KulaPacket[1];
}

LOUDLL_API
void
LouPutCurrentProcessHandle(
    HANDLE ProcessHandle
){
    UINT64 KulaPacket[2] = {0, (UINT64)ProcessHandle};
    LouCALL(LOUPUTCURRENTPROCHANDLE, (UINT64)&KulaPacket, 0);
}

LOUDLL_API
LOUSTATUS
LouGetCurrentProccessName(
    PSTRING NameOut
){
    LOUSTATUS Status;
    ACCESS_MASK RequestedAccess = PROCESS_QUERY_INFORMATION;
    HANDLE CurrentProcessHandle = 0x00;
    Status = LouGetCurrentProccessHandle(
        &CurrentProcessHandle,
        RequestedAccess
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    Status = LouGetProcessName(
        CurrentProcessHandle,
        NameOut
    );
    LouPutCurrentProcessHandle(CurrentProcessHandle);
    return Status;
}

LOUDLL_API 
PVOID 
LouKeAllocateVmmIsolatedBuffer64(
    SIZE    Size,
    SIZE    Alignment,
    BOOLEAN Zero,
    BOOLEAN Shared,
    UINT64  Flags
){
    UINT64 KulaPacket[7] = {0, 0, (UINT64)Size, (UINT64)Alignment, (UINT64)Zero, (UINT64)Shared, (UINT64)Flags};
    LouCALL(LOUALLOCVMMBUFF64, (UINT64)&KulaPacket[0], 0);
    return (PVOID)KulaPacket[1];
}

LOUDLL_API
PVOID 
LouAllocateVirtualMemoryEx2(
    SIZE        Size,
    SIZE        Alignment,
    BOOLEAN     Shared,
    UINT64      Flags
){
    return LouKeAllocateVmmIsolatedBuffer64(
        Size,
        Alignment,
        false,
        Shared,
        Flags
    );
}

LOUDLL_API
PVOID 
LouAllocateVirtualMemoryEx(
    SIZE        Size,
    SIZE        Alignment,
    UINT64      Flags
){
    return LouAllocateVirtualMemoryEx2(
        Size,
        Alignment,
        false,
        Flags
    );
}

LOUDLL_API
PVOID 
LouAllocateVirtualMemory(
    SIZE        Size,
    UINT64      Flags
){
    return LouAllocateVirtualMemoryEx(
        Size,
        GetAlignmentBySize(Size),
        Flags  
    );
}

void LouCaptureNtContext(UINT64);

LOUSTATUS 
LouUnwindTillException(
    PNT_CONTEXT         NtContext,
    PEXCEPTION_RECORD   ExRecord
){
    LouPrint("LOUDLL.DLL:LouUnwindTillException()\n");

    return STATUS_UNSUCCESSFUL;
}

ANNA_EXPORT
void 
LouRtlRaiseNtException(
    PEXCEPTION_RECORD   ExRecord
){
    LouPrint("LOUDLL.DLL:LouRtlRaiseException()\n");
    //PNT_CONTEXT Context = LouGlobalUserMallocEx(sizeof(NT_CONTEXT), GET_ALIGNMENT(NT_CONTEXT));
    //LouCaptureNtContext((UINT64)&Context->Amd64);
    //LouUnwindTillException(Context, ExRecord);
    
    while(1);
}

ANNA_EXPORT
void
LouRaiseNtException(
    DWORD           ExceptionCode,
    DWORD           ExceptionFlags,
    ULONG_PTR*      Args
){
    LouPrint("LOUDLL.DLL:LouRaiseException()\n");
    while(1);
}