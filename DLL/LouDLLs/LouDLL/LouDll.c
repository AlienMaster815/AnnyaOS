
//x86_64-w64-mingw32-gcc -shared -o LouDll.dll LouDll.c -nostdlib -nodefaultlibs -I../../../Include
#define _LOUDLL_
#include <Annya.h>
#include <stdarg.h>


#define LOUDLL_API __declspec(dllexport)


LOUDLL_API
void*
LouMemCpy(
    void* OutStream,
    void* InStream,
    size_t ByteCount
){
    volatile char* dest = (char*)OutStream;
    volatile const char* src = (const char*)InStream;

    // Handle overlapping memory regions (copy backward)
    if (dest > src && dest < src + ByteCount) {
        for(size_t i = ByteCount; i > 0;){
            dest[i] = src[i];
            i -= 1;
        }
    } else {
        // Normal forward copy (non-overlapping memory)
        for(size_t i = 0; i < ByteCount;){
            dest[i] = src[i];
            i += 1;
        }
    }
    return OutStream;
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

LOUDLL_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

static mutex_t PrintLock;
LOUDLL_API
int LouPrint(char* Str, ...){
    va_list Arg;
    va_start(Arg, Str);
    uint64_t Data[3];
    Data[0] = 0;
    Data[1] = (uint64_t)Str;
    Data[2] = (uint64_t)&Arg;
    while(Data[0] != 1){
        LouCALL(LOUPRINTCALL, (uint64_t)&Data, 0);
    }
    va_end(Arg);
    return Data[1];
}

LOUDLL_API
uint16_t AnnyaGetScreenBufferHeight(){
    uint64_t Data[2];
    Data[0] = 0;
    while(Data[0] != 1){
        LouCALL(GETSCREENHEIGHT, (uint64_t)&Data, 0);
    }
    return (uint16_t)Data[1];
}

LOUDLL_API
int64_t AnnyaGetScreenBufferWidth(){
    uint64_t Data[2];
    Data[0] = 0;
    while(Data[0] != 1){
        LouCALL(GETSCREENWIDTH, (uint64_t)&Data, 0);
    }
    return (int64_t)Data[1];
}

LOUDLL_API
PTHREAD AnnyaCreateThread(DWORD (*Function)(PVOID), PVOID FunctionParameters){
    if(!Function){
        return 0x00;
    }
    //uint64_t Result;
    uint64_t Data[3];
    Data[0] = 0;
    Data[1] = (uint64_t)Function;
    Data[2] = (uint64_t)FunctionParameters;
    while(Data[0] != 1){
        LouCALL(LOUCREATETHREAD, (uint64_t)&Data ,0);
    }
    return (PTHREAD)Data[1];
}


LOUDLL_API
void AnnyaDestroyThread(PTHREAD Thread){
    uint64_t Data = (uint64_t) Thread;
    LouCALL(LOUDESTROYTHREAD, (uint64_t)&Data, 0);
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
size_t strlen(const char* str) {
    const char* ptr = str;
    while (*ptr != '\0') {
        ++ptr;
    }
    return ptr - str;
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
        LouCALL(LOUGETRTCDATA,(uint64_t)&Data,0);
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

static void LouSpin(){
    uint16_t i = 0;
    while(i != (uint16_t)-1){
        i++;
    }
}

LOUDLL_API
void LouCALL(
    uint64_t Call,
    uint64_t Data,
    uint64_t SystemEmulation
){
    MutexLock(&LouCallLock);
    TailLouCall(Call, Data, SystemEmulation);
    MutexUnlock(&LouCallLock);
    LouSpin();
}


LOUDLL_API
void AnnyaUserThreadStub(void* PTHREAD, void* THREAD_DATA, uintptr_t ThreadHandle){
    DWORD (*NewThread)(void* THREAD_DATA) = PTHREAD;
    DWORD Result = NewThread(THREAD_DATA);    
    LouPrint("Thread:%h :: Exited With Value:%h\n", PTHREAD, Result);
    AnnyaDestroyThread((void*)ThreadHandle);
    while(1);
}

typedef struct _ATTACH_THREAD_DATA{
    bool   (*DllEntry)(uint64_t, uint64_t, uint64_t);
    uint64_t DllHandle;
    uint64_t DllCallReason;
    uint64_t DllReserved;
    void   (*LockRelease)();
}ATTACH_THREAD_DATA, * PATTACH_THREAD_DATA;

LOUDLL_API
DWORD AnnyaAttachDllToProcess(PVOID ThreadData){
    PATTACH_THREAD_DATA DllAttachData = (PATTACH_THREAD_DATA)ThreadData;
    DllAttachData->DllEntry(DllAttachData->DllHandle, DllAttachData->DllCallReason, DllAttachData->DllReserved);
    DllAttachData->LockRelease();
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
    uint64_t KulaPacket[4] = {0};
    KulaPacket[1] = (uint64_t)Heap;
    KulaPacket[2] = (uint64_t)AllocationSize;
    KulaPacket[3] = (uint64_t)Alginment;
    while(!KulaPacket[0]){
        LouCALL(LOUALLOCHEAPGENERICEX, (uint64_t)&KulaPacket[0], 0);
    }
    return (void*)KulaPacket[4];
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