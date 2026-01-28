
//x86_64-w64-mingw32-gcc -shared -o LouDll.dll LouDll.c -nostdlib -nodefaultlibs -I../../../Include
#include "LouDll.h"
#include <LouCoff.h>

#define NTDLL_RVA_ENTRIES 68
#define KERNELBASE_RVA_ENTRIES 1
#define LOUDLL_EMULATED_BINARIES 2

void LouYeildExecution();

static KULA_RVA_NAME KernelBaseNames[KERNELBASE_RVA_ENTRIES] = {
    "InitializeCriticalSectionEx",
};

static KULA_RVA_ADDRESS KernelBaseAddresses[KERNELBASE_RVA_ENTRIES] = {
    (PVOID)RtlInitializeCriticalSectionEx,
};


static KULA_RVA_NAME NtDllNames[NTDLL_RVA_ENTRIES] = {
    "RtlInitializeCriticalSectionEx",
    "AnnyaNtGetProcessHeap",
    "RtlAllocateHeap",
    "RtlEnterCriticalSection",
    "RtlLeaveCriticalSection",
    "GetProcessHeap",
    "_wcsicmp",
    "_wcslwr",
    "wcslen",
    "_wcslwr_s",
    "wcsnlen",
    "_wcsnicmp",
    "_wcsupr",
    "_wcsupr_s",
    "wcscpy",
    "wcscpy_s",
    "wcscat",
    "wcscat_s",
    "wcschr",
    "wcscmp",
    "wcscspn",
    "wcsncat",
    "wcsncat_s",
    "wcsncmp",
    "wcsncpy",
    "wcsncpy_s",
    "wcsrchr",
    "wcspbrk",
    "RtlUnicodeToMultiByteSize",
    "RtlUnicodeToMultiByteN",
    "RtlMultiByteToUnicodeSize",
    "RtlMultiByteToUnicodeN",
    "strlen",
    "wcsspn",
    "wcsstr",
    "wcstok",
    "wcstok_s",
    "wcstombs",
    "mbstowcs",
    "iswctype",
    "iswalnum",
    "iswalpha",
    "iswascii",
    "iswdigit",
    "iswgraph",    
    "iswlower",
    "iswprint",
    "iswspace",
    "iswxdigit",
    "wcstol",
    "wcstoul",
    "wcstoi64",
    "wcstoui64",
    "_ultow",
    "_ltow",
    "_itow",
    "_ui64tow",
    "_i64tow",
    "_ui64tow_s",
    "_ultow_s",
    "_i64tow_s",
    "_ltow_s",
    "_itow_s",
    "_wtol",
    "_wtoi",
    "_wtoi64",
    "_wsplitpath_s",
    "_wmakepath_s",
};

static KULA_RVA_ADDRESS NtDllAddresses[NTDLL_RVA_ENTRIES] = {
    (PVOID)RtlInitializeCriticalSectionEx,
    (PVOID)AnnyaNtGetProcessHeap,
    (PVOID)RtlAllocateHeap,
    (PVOID)RtlEnterCriticalSection,
    (PVOID)RtlLeaveCriticalSection,
    (PVOID)AnnyaNtGetProcessHeap,
    (PVOID)_wcsicmp,
    (PVOID)_wcslwr,
    (PVOID)wcslen,
    (PVOID)_wcslwr_s,
    (PVOID)wcsnlen,
    (PVOID)_wcsnicmp,
    (PVOID)_wcsupr,
    (PVOID)_wcsupr_s,
    (PVOID)wcscpy,
    (PVOID)wcscpy_s,
    (PVOID)wcscat,
    (PVOID)wcscat_s,
    (PVOID)wcschr,
    (PVOID)wcscmp,
    (PVOID)wcscspn,
    (PVOID)wcsncat,
    (PVOID)wcsncat_s,
    (PVOID)wcsncmp,
    (PVOID)wcsncpy,
    (PVOID)wcsncpy_s,
    (PVOID)wcsrchr,
    (PVOID)wcspbrk,
    (PVOID)RtlUnicodeToMultiByteSize,
    (PVOID)RtlUnicodeToMultiByteN,
    (PVOID)RtlMultiByteToUnicodeSize,
    (PVOID)RtlMultiByteToUnicodeN,
    (PVOID)strlen,
    (PVOID)wcsspn,
    (PVOID)wcsstr,
    (PVOID)wcstok,
    (PVOID)wcstok_s,
    (PVOID)wcstombs,
    (PVOID)mbstowcs,
    (PVOID)iswctype,
    (PVOID)iswalnum,
    (PVOID)iswalpha,
    (PVOID)iswascii,
    (PVOID)iswdigit,
    (PVOID)iswgraph,
    (PVOID)iswlower,
    (PVOID)iswprint,
    (PVOID)iswspace,
    (PVOID)iswxdigit,
    (PVOID)wcstol,
    (PVOID)wcstoul,
    (PVOID)wcstoi64,
    (PVOID)wcstoui64,
    (PVOID)_ultow,
    (PVOID)_ltow,
    (PVOID)_itow,
    (PVOID)_ui64tow,
    (PVOID)_i64tow,
    (PVOID)_ui64tow_s,
    (PVOID)_ultow_s,
    (PVOID)_i64tow_s,
    (PVOID)_ltow_s,
    (PVOID)_itow_s,
    (PVOID)_wtol,
    (PVOID)_wtoi,
    (PVOID)_wtoi64,
    (PVOID)_wsplitpath_s,
    (PVOID)_wmakepath_s,
};

static KULA_TBALE_ENTRIES KulaEntries[LOUDLL_EMULATED_BINARIES] = {
    {
        .BinaryName = "ntdll.dll",
        .Members = NTDLL_RVA_ENTRIES,
        .Names = NtDllNames,
        .Rvas = NtDllAddresses,
    },
    {
        .BinaryName = "kernelbase.dll",
        .Members = KERNELBASE_RVA_ENTRIES,
        .Names = KernelBaseNames,
        .Rvas = KernelBaseAddresses,
    },
};

DECLARE_KULA_TABLE = {
    .KulaSignature = "KULA;",
    .TableMembers = LOUDLL_EMULATED_BINARIES,
    .Entries = KulaEntries,
};

static inline size_t GetAlignmentBySize(size_t Size){
    if(Size <= 2)    return 2;
    if(Size <= 4)    return 4;
    if(Size <= 8)    return 8;
    if(Size <= 16)   return 16;
    if(Size <= 32)   return 32;
    if(Size <= 64)   return 64;
    if(Size <= 128)  return 128;
    if(Size <= 256)  return 256;
    if(Size <= 512)  return 512;
    if(Size <= 1024) return 1024;
    if(Size <= 2048) return 2048;
    return 4096;
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

    if((!InStream) || (!OutStream) || ((uintptr_t)InStream == (uintptr_t)OutStream)){
        return STATUS_INVALID_PARAMETER;
    }

    for(size_t i = 0 ; i < StreamSize; i++){
        OutStream[(StreamSize - 1) - i] = InStream[i]; 
    }
    return STATUS_SUCCESS;
}


BOOL NtDllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);

LOUDLL_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    BOOL Tmp = true;
    //Tmp = NtDllMainCRTStartup(hModule, ul_reason_for_call, lpReserved);
    if(!Tmp){
        return Tmp;
    }
    return TRUE;    
}

static mutex_t PrintLock;
LOUDLL_API
int LouPrint(char* Str, ...){
    va_list Arg;
    va_start(Arg, Str);
    uint64_t Data[4] = {0};
    Data[0] = 0;
    Data[1] = (uint64_t)Str;
    Data[2] = (uint64_t)&Arg;
    while(Data[0] != 1){
        LouCALL(LOUPRINTCALL, (uint64_t)&Data[0], 0);
    }
    va_end(Arg);
    return Data[3];
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
    while(Data[0] != 1){
        LouCALL(LOUCREATETHREAD, (uint64_t)&Data[0] ,0);
    }
    return (PTHREAD)Data[1];
}


LOUDLL_API
void AnnyaDestroyThread(PTHREAD Thread){
    uint64_t Data[2] = {0};
    Data[1] = (uint64_t)Thread;
    while(Data[0] != 1){
        LouCALL(LOUDESTROYTHREAD, (uint64_t)&Data[0], 0);
    }
}

void uintToHexString(uint64_t number, char* hexString) {
    int i = 0;
    hexString[0] = '0';
    hexString[1] = 'x';
    i = 2;  // Start filling the string after '0x'

    char tempString[16];  // Temporary array to store reversed hex string (16 hex digits for 64 bits)
    int tempIndex = 0;

    // Handle the case when number is 0
    if (number == 0) {
        hexString[i++] = '0';
        hexString[i] = '\0';
        return;
    }

    // Convert number to hex string in reverse order
    while (number != 0) {
        int digit = number % 16;
        tempString[tempIndex++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        number /= 16;
    }

    // Copy the reversed hex string to the final string
    while (tempIndex > 0) {
        hexString[i++] = tempString[--tempIndex];
    }

    hexString[i] = '\0'; // Null-terminate the string
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

LOUDLL_API
int strcmp(const char* str1, const char* str2) {

    // Compare characters until we reach the specified number of characters (n)
    while (1) {
        // Compare the current characters in both strings
        char c1 = *str1++;
        char c2 = *str2++;

        // If the characters are equal or both are null terminators, continue
        if (c1 == c2 || c1 == '\0' || c2 == '\0') {
            // If we've compared n characters or reached the end of either string, return 0
            if (c1 == '\0' && c2 == '\0') {
                return 0;
            }
        }
        else {
            // The characters are not equal, return the difference
            return c1 - c2;
        }

    }

    // If we've reached here, the first n characters are equal

    return 0;
}



static mutex_t VsSprintFLock;

#include <stdarg.h>
#include <stdint.h>
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
    while(Data[0] != 1){
        LouCALL(LOUGETRTCDATA,(uint64_t)&Data[0],0);
    }
}

LOUDLL_API
void AnnyaUpdateButton(
    int64_t x, int64_t y,
    uint32_t Width, uint32_t Height,
    PBUTTONHANDLE HBUTTON
){
    LouPrint("AnnyaUpdateButton()\n");
    while(1);
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
    while(!KulaPacket[0]){
        LouCALL(LOUALLOCHEAPGENERICEX, (uint64_t)&KulaPacket[0], 0);
    }
    return (void*)KulaPacket[4];
}

LOUDLL_API
void LouGenericFreeHeap(void* Heap, void* Address){
    uint64_t KulaPacket[3] = {0};
    KulaPacket[1] = (uint64_t)Heap;
    KulaPacket[2] = (uint64_t)Address;
    while(!KulaPacket){
        LouCALL(LOUFREEGENERICHEAP, (uint64_t)&KulaPacket[0], 0);
    }
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
    while(!KulaPacket[0]){
        LouCALL(LOUVIRTUALALLOCUSER, (uint64_t)&KulaPacket[0], 0);
    }
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
    while(!KulaPacket[0]){
        LouCALL(LOUAGLFN, (uint64_t)&KulaPacket[0], 0);
    }
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
FILE*
LouOpenFileA(
    string FileName
){
    uint64_t KulaPacket[2] = {0};
    KulaPacket[1] = (uint64_t)FileName;
    while(!KulaPacket[0]){
        LouCALL(LOULOADFILE, (uint64_t)&KulaPacket[0], 0);
    }
    return (void*)KulaPacket[1]; 
}

LOUDLL_API
void
LouCloseFile(
    FILE* ClosingFile
){
    uint64_t KulaPacket[2] = {0};
    KulaPacket[1] = (uint64_t)ClosingFile;
    while(!KulaPacket[0]){
        LouCALL(LOULOADFILE, (uint64_t)&KulaPacket[0], 0);
    } 
}

LOUDLL_API
void 
LouExitDosMode(){
    uint64_t KulaPacket = 0;
    while(!KulaPacket){
        LouCALL(LOUEXITDOSMODE, (uint64_t)&KulaPacket, 0);
    } 
}

LOUDLL_API
void LouGlobalUserFree(void* Addr){
    uint64_t KulaPacket[2] = {0};
    KulaPacket[1] = (uint64_t)Addr;
    while(!KulaPacket[0]){
        LouCALL(LOUGLOBALFREE, (uint64_t)&KulaPacket[0], 0);
    }
}

LOUDLL_API 
void*
LouGlobalUserMallocEx(size_t Size, uint64_t Alignment){
    uint64_t KulaPacket[4] = {0};
    KulaPacket[2] = Size;
    KulaPacket[3] = Alignment;
    while(!KulaPacket[0]){
        LouCALL(LOUGLOBALMALLOC, (uint64_t)&KulaPacket[0], 0);
    }
    return (void*)KulaPacket[1];
}

LOUDLL_API
void*
LouGlobalUserMalloc(size_t Size){
    LouGlobalUserMallocEx(Size, GetAlignmentBySize(Size));
}

LOUDLL_API
void* memset(void* dest, int value, size_t count) {
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
    while(KulaPacket != 1){
        LouCALL(LOUYEILDEXE, (uint64_t)&KulaPacket, 0);
    }
}

LOUDLL_API
void ReleaseLoadLibraryALock(mutex_t* Mutex){
    MutexUnlock(Mutex);
}

struct ModuleEntryList{
    ListHeader  Peers;
    PVOID       Entry;
    PVOID       ModuleHandle;
};

struct ProcessLoaderParameters{
    mutex_t                 Lock;
    struct ModuleEntryList  ModEntrys;
};

LOUDLL_API
DWORD LouProcessInitThread(
    PVOID   Data
){
    struct ProcessLoaderParameters* LoaderData = (struct ProcessLoaderParameters*)Data;



    MutexUnlock(&LoaderData->Lock);
    return 0;
}

LOUDLL_API
void 
LouSystemShutdown(SHUTDOWN_ACTION ShutDown){
    uint64_t Data[2] = {0};
    Data[1] = (uint64_t)ShutDown;
    while(Data[0] != 1){
        LouCALL(LOUSHUTDOWN, (uint64_t)&Data[0], 0);
    }
}