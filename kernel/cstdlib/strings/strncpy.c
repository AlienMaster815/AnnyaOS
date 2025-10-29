#include <LouAPI.h>

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

char* LouKeCombineStr_s(char* String1, size_t Str1Size, char* String2, size_t Str2Size){
    char* Result = LouKeMallocArray(char, Str1Size + Str2Size + 1, KERNEL_GENERIC_MEMORY);
    strncpy(Result, String1, Str1Size);
    strncat(Result, String2, Str2Size);
    return Result;
}

char* LouKeCombineStr(char* String1, char* String2){
    return LouKeCombineStr_s(String1, strlen(String1), String2, strlen(String2));
}

char* LouKeAddFileToPath_s(char* Path, size_t PathLength, char* FileName, size_t FileNameLength){
    char* Result = LouKeMallocArray(char, PathLength + FileNameLength + 2, KERNEL_GENERIC_MEMORY);
    strncpy(Result, Path, PathLength);
    strncat(Result, "/", strlen("/"));
    strncat(Result, FileName, FileNameLength);
    return Result;
}

char* LouKeAddFileToPath(char* Path, char* FileName){
    return LouKeAddFileToPath_s(Path, strlen(Path), FileName, strlen(FileName));
}