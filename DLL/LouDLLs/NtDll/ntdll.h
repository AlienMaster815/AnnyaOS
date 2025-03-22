#ifndef NTDLL_H
#define NTDLL_H

#define NTDLL_API __declspec(dllexport)

#include <Annya.h>
#include <WinTEB.h>
#include <stdalign.h>
#define GET_ALIGNMENT(x) (alignof(x))

typedef long long unsigned int U64;

static inline void* __builtin_memcpy(void* Destination,void* Source, U64 ByteCount){
    // Cast pointers to char* for byte-wise copying
    char* dest = (char*)Destination;
    const char* src = (const char*)Source;

    // Check if the source and destination overlap
    if (dest > src && dest < src + ByteCount) {
        // Copy backwards if there's overlap to prevent data corruption
        for (size_t i = ByteCount; i > 0; i--) {
            dest[i - 1] = src[i - 1];
        }
    } else {
        // Standard forward copy
        for (size_t i = 0; i < ByteCount; i++) {
            dest[i] = src[i];
        }
    }

    return Destination;
}


#endif