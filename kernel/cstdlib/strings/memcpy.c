
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

static uint64_t SavedState = 0;

uint8_t* LouMallocEx(size_t x, size_t y);

//Fuck It Well do it live
void SaveEverything(uint64_t* ContextHandle);
void RestoreEverything(uint64_t* ContextHandle);

typedef struct _PROCESSOR_FEATURES{
    bool    Sse1Supported;
    bool    Sse2Supported;
    bool    Sse3Supported;
    bool    Ssse3Supported;
    bool    Sse41Supported;
    bool    Sse42Supported;
    bool    Avx1Supported;
    bool    Avx2Supported;
    bool    Avx512Supported;
}PROCESSOR_FEATURES, * PPROCESSOR_FEATURES;

static void* (*MemcopyHandler)(void*, const void*, size_t);

void simd_copy(uint64_t Destination, uint64_t Source);

static void* memcpy_basic(void* destination, const void* source, size_t num) {
    volatile char* dest = (char*)destination;
    volatile const char* src = (const char*)source;

    // Handle overlapping memory regions (copy backward)
    if (dest > src && dest < src + num) {
        dest += num;
        src += num;
        while (num >= 8) {
            dest -= 8;
            src -= 8;
            *(uint64_t*)dest = *(const uint64_t*)src;
            num -= 8;
        }
        if (num >= 4) {
            dest -= 4;
            src -= 4;
            *(uint32_t*)dest = *(const uint32_t*)src;
            num -= 4;
        }
        if (num >= 2) {
            dest -= 2;
            src -= 2;
            *(uint16_t*)dest = *(const uint16_t*)src;
            num -= 2;
        }
        if (num >= 1) {
            dest -= 1;
            src -= 1;
            *dest = *src;
        }
    } else {
        // Normal forward copy (non-overlapping memory)
        while (num >= 8) {
            *(uint64_t*)dest = *(const uint64_t*)src;
            dest += 8;
            src += 8;
            num -= 8;
        }
        if (num >= 4) {
            *(uint32_t*)dest = *(const uint32_t*)src;
            dest += 4;
            src += 4;
            num -= 4;
        }
        if (num >= 2) {
            *(uint16_t*)dest = *(const uint16_t*)src;
            dest += 2;
            src += 2;
            num -= 2;
        }
        if (num >= 1) {
            *dest = *src;
        }
    }
    return destination;
}
 
static void* memcpy_sse(void* destination, const void* source, size_t num) {
    // Check for overlapping regions (Backward Copy Case)
    SaveEverything(&SavedState);
    if (destination > source && destination < (void*)((uintptr_t)source + num)) {
        uintptr_t CurrentIndex = num;

        // SSE needs 16-byte alignment
        while (CurrentIndex > 16) { // While we can use SSE1
            if ((((uintptr_t)destination + CurrentIndex - 16) & 0x0F) == 0 &&
                (((uintptr_t)source + CurrentIndex - 16) & 0x0F) == 0) {
                // Use SIMD instructions
                while (CurrentIndex > 16) {
                    CurrentIndex -= 16;
                    simd_copy((uint64_t)((uintptr_t)destination + CurrentIndex), 
                              (uint64_t)((uintptr_t)source + CurrentIndex));
                }
            } else {
                register uint64_t Ts = ((uintptr_t)(destination + CurrentIndex - 16) & 0x0F) ? 
                                       ((uintptr_t)(destination + CurrentIndex - 16) & 0x0F) : 16;
                CurrentIndex -= Ts;
                memcpy_basic((void*)((uintptr_t)destination + CurrentIndex), 
                             (void*)((uintptr_t)source + CurrentIndex), Ts);
            }
        }

        // Copy remaining bytes
        if (CurrentIndex > 0) {
            memcpy_basic((void*)((uintptr_t)destination + CurrentIndex - 1), 
                         (void*)((uintptr_t)source + CurrentIndex - 1), CurrentIndex);
        }
    } else {
        // Forward Copy Case
        uintptr_t CurrentIndex = 0;

        // SSE needs 16-byte alignment
        while ((CurrentIndex + 16) <= num) { // While we can use SSE1
            if ((((uintptr_t)destination & 0x0F) == 0) && (((uintptr_t)source & 0x0F) == 0)) {
                // Use SIMD instructions
                while ((CurrentIndex + 16) <= num) {
                    simd_copy((uint64_t)((uintptr_t)destination + CurrentIndex), 
                              (uint64_t)((uintptr_t)source + CurrentIndex));
                    CurrentIndex += 16;
                }
            } else {
                register uint64_t Ts = ((uintptr_t)destination & 0x0F) ? 
                                       (16 - ((uintptr_t)destination & 0x0F)) : 0;
                memcpy_basic((void*)((uintptr_t)destination + CurrentIndex), 
                             (void*)((uintptr_t)source + CurrentIndex), Ts);
                CurrentIndex += Ts;
            }
        }

        // Copy remaining bytes
        if (CurrentIndex != num) {
            memcpy_basic((void*)((uintptr_t)destination + CurrentIndex), 
                         (void*)((uintptr_t)source + CurrentIndex), num - CurrentIndex);
        }
    }
    RestoreEverything(&SavedState);
    return destination;
}

//static void* memcpy_avx256(void* destination, const void* source, size_t num){

//    while(1);
//    return 0;
//}

void SendProcessorFeaturesToMemCpy(PPROCESSOR_FEATURES ProcessorFeatures){
    if(ProcessorFeatures->Avx512Supported){
        MemcopyHandler = memcpy_sse;
        //MemcopyHandler = memcpy_avx256;
        return;
    }
    if(ProcessorFeatures->Avx2Supported){
        MemcopyHandler = memcpy_sse;
        //MemcopyHandler = memcpy_avx256;
        return;
    }
    else if(ProcessorFeatures->Avx1Supported){
        MemcopyHandler = memcpy_sse;
        //MemcopyHandler = memcpy_avx256;
        return;
    }
    if(ProcessorFeatures->Sse42Supported){
        MemcopyHandler = memcpy_sse;
        return;
    }
    else if(ProcessorFeatures->Sse41Supported){
        MemcopyHandler = memcpy_sse;
        return;
    }
    else if(ProcessorFeatures->Sse3Supported){
        MemcopyHandler = memcpy_sse;
        return;
    }
    else if(ProcessorFeatures->Sse2Supported){
        MemcopyHandler = memcpy_sse;
        return;
    }
    else if(ProcessorFeatures->Sse1Supported){
        MemcopyHandler = memcpy_sse;
        return;
    }
    MemcopyHandler = memcpy_basic;
}

void InitializeBasicMemcpy(){
    SavedState = (uintptr_t)LouMallocEx(2688, 64);
    MemcopyHandler = memcpy_basic;
}

void* memcpy(void* destination, const void* source, size_t num) {
    return MemcopyHandler(destination, source, num);
}


