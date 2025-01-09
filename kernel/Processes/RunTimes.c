#include <LouAPI.h>

void* PsGetCurrentServerSiloGlobals();


// Function to check if the process is UTF-8
void* RtlpIsUtf8Process(char arg1) {

    return (void*)0x00; 
}

uint64_t CountUnicodeToUTF8(const wchar_t* utf16Src, int32_t utf16Length, uint32_t* utf8Size) {

    return 0; 
}

uint64_t RtlUnicodeToUTF8N(char* utf8Dest, int32_t utf8MaxBytes, uint32_t* utf8BytesWritten, const wchar_t* utf16Src, char strictCheck) {
    return STATUS_SUCCESS;
}



int64_t RtlUnicodeToMultiByteN(void* dest, uint32_t destSize, uint32_t* bytesCopied, wchar_t* src, int32_t srcSize) {

    return 0;
}

int64_t RtlUnicodeToMultiByteSize(uint32_t* size, wchar_t* src, int32_t length) {

    return 0;
}
