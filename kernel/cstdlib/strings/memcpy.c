
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <emmintrin.h> 
#include <immintrin.h> 

static uint64_t SavedState = 0;

void* LouMallocEx(size_t BytesToAllocate, size_t Aligned);

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

__attribute__((target("avx2")))
static void* memcpy_avx2(void* destination, const void* source, size_t num) {
    SaveEverything(&SavedState);
    uintptr_t dest_ptr = (uintptr_t)destination;
    uintptr_t src_ptr = (uintptr_t)source;

    size_t count = num / 32;
    for(size_t i = 0; i < count; ++i){
        __m256i tmp = _mm256_loadu_si256((const __m256i*)(src_ptr + i * 32));
        _mm256_storeu_si256((__m256i*)(dest_ptr + i * 32), tmp);
    }

    // Copy remaining bytes
    size_t remaining = num % 32;
    uint8_t* c_dest = (uint8_t*)(dest_ptr + count * 32);
    const uint8_t* c_src = (const uint8_t*)(src_ptr + count * 32);
    for(size_t i = 0; i < remaining; ++i){
        c_dest[i] = c_src[i];
    }
    RestoreEverything(&SavedState);
    return destination;
}

static void* memcpy_basic(void* destination, const void* source, size_t num) {
    volatile char* dest = (char*)destination;
    volatile const char* src = (const char*)source;

    // Handle overlapping memory regions (copy backward)
    if (dest > src && dest < src + num) {
        for(size_t i = num; i > 0;){
            dest[i] = src[i];
            i -= 1;
        }
    } else {
        // Normal forward copy (non-overlapping memory)
        for(size_t i = 0; i < num;){
            dest[i] = src[i];
            i += 1;
        }
    }
    return destination;
}
 
__attribute__((target("sse2")))
UNUSED static void* memcpy_sse2(void* destination, const void* source, size_t num) {
    SaveEverything(&SavedState);
    __m128i* dest = (__m128i*)destination;
    const __m128i* src = (const __m128i*)source;

    size_t count = num / 16;
    for(size_t i = 0; i < count; ++i){
        __m128i tmp = _mm_loadu_si128(&src[i]);
        _mm_storeu_si128(&dest[i], tmp);
    }
    size_t remaining = num % 16;
    char* c_dest = (char*)dest + count * 16;
    const char* c_src = (const char*)src + count * 16;
    for(size_t i = 0; i < remaining; ++i){
        c_dest[i] = c_src[i];
    }
    RestoreEverything(&SavedState);
    return destination;
}

__attribute__((target("avx512f")))
UNUSED static void* memcpy_avx512(void* destination, const void* source, size_t num) {
    uintptr_t dest_ptr = (uintptr_t)destination;
    uintptr_t src_ptr = (uintptr_t)source;

    size_t count = num / 64;
    for(size_t i = 0; i < count; ++i){
        __m512i tmp = _mm512_loadu_si512((const void*)(src_ptr + i * 64));
        _mm512_storeu_si512((void*)(dest_ptr + i * 64), tmp);
    }

    // Copy remaining bytes
    size_t remaining = num % 64;
    uint8_t* c_dest = (uint8_t*)(dest_ptr + count * 64);
    const uint8_t* c_src = (const uint8_t*)(src_ptr + count * 64);
    for(size_t i = 0; i < remaining; ++i){
        c_dest[i] = c_src[i];
    }

    return destination;
}


void SendProcessorFeaturesToMemCpy(PPROCESSOR_FEATURES ProcessorFeatures){
    
    if(!SavedState){
        SavedState = (uintptr_t)LouMallocEx(2688, 64);
    }

    if(ProcessorFeatures->Avx512Supported){
        //MemcopyHandler = memcpy_sse;
        MemcopyHandler = memcpy_avx512;
        return;
    }
    else if(ProcessorFeatures->Avx2Supported){
        MemcopyHandler = memcpy_avx2;
        return;
    }
    else if(ProcessorFeatures->Sse2Supported){
        MemcopyHandler = memcpy_sse2;
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