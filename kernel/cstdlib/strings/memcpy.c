
#include <stddef.h>
#include <stdbool.h>
#include <cstdint.h>
#include <emmintrin.h> 
#include <immintrin.h> 

/*static uint64_t* SavedState = 0;

void* LouGeneralAllocateMemoryEx(size_t BytesToAllocate, size_t Aligned);

//Fuck It Well do it live
void SaveEverything(uint64_t ContextHandle);
void RestoreEverything(uint64_t ContextHandle);

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

void simd_copy(uint64_t Destination, uint64_t Source);

void* memcpy_basic(void* destination, const void* source, size_t num) {
    uint8_t* d = (uint8_t*)destination;
    const uint8_t* s = (const uint8_t*)source;

    if (d == s || num == 0) return destination;

    if (d > s && d < s + num) {
        for (size_t i = num; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    } else {
        for (size_t i = 0; i < num; i++) {
            d[i] = s[i];
        }
    }
    return destination;
}

__attribute__((target("avx2")))
static void* memcpy_avx2(void* destination, const void* source, size_t num) {
    if(num < 256){
        return memcpy_basic(destination, source, num);
    }
    if(SavedState)SaveEverything(SavedState[LouKeGetCurrentProcessorNumber()]);
    uintptr_t d = (uintptr_t)destination;
    uintptr_t s = (uintptr_t)source;

    if (d == s || num == 0) return destination;

    if (d < s || d >= (s + num)) {
        size_t count = num / 32;
        for (size_t i = 0; i < count; ++i) {
            __m256i tmp = _mm256_loadu_si256((const __m256i*)(s + i * 32));
            _mm256_storeu_si256((__m256i*)(d + i * 32), tmp);
        }
        for (size_t i = count * 32; i < num; ++i) {
            ((uint8_t*)d)[i] = ((const uint8_t*)s)[i];
        }
    } 
    else {
        size_t remaining = num % 32;
        for (size_t i = 1; i <= remaining; ++i) {
            ((uint8_t*)d)[num - i] = ((const uint8_t*)s)[num - i];
        }
        size_t count = num / 32;
        for (size_t i = count; i > 0; --i) {
            size_t offset = (i - 1) * 32;
            __m256i tmp = _mm256_loadu_si256((const __m256i*)(s + offset));
            _mm256_storeu_si256((__m256i*)(d + offset), tmp);
        }

    }
    if(SavedState)RestoreEverything(SavedState[LouKeGetCurrentProcessorNumber()]);
    return destination;
}

 
__attribute__((target("sse2")))
UNUSED static void* memcpy_sse2(void* destination, const void* source, size_t num) {
    if(num < 128){
        return memcpy_basic(destination, source, num);
    }
    if(SavedState)SaveEverything(SavedState[LouKeGetCurrentProcessorNumber()]);
    unsigned char* d = (unsigned char*)destination;
    const unsigned char* s = (const unsigned char*)source;

    if (d == s || num == 0) return destination;

    if (d < s || d >= (s + num)) {
        size_t count = num / 16;
        for (size_t i = 0; i < count; ++i) {
            __m128i tmp = _mm_loadu_si128((const __m128i*)(s + i * 16));
            _mm_storeu_si128((__m128i*)(d + i * 16), tmp);
        }
        for (size_t i = count * 16; i < num; ++i) {
            d[i] = s[i];
        }
    } 
    else {
        size_t remaining = num % 16;
        for (size_t i = 1; i <= remaining; ++i) {
            d[num - i] = s[num - i];
        }
        size_t count = num / 16;
        for (size_t i = count; i > 0; --i) {
            size_t offset = (i - 1) * 16;
            __m128i tmp = _mm_loadu_si128((const __m128i*)(s + offset));
            _mm_storeu_si128((__m128i*)(d + offset), tmp);
        }
    }
    if(SavedState)RestoreEverything(SavedState[LouKeGetCurrentProcessorNumber()]);
    return destination;
}

__attribute__((target("avx512f")))
UNUSED static void* memcpy_avx512(void* destination, const void* source, size_t num) {
    if(num < 512){
        return memcpy_basic(destination, source, num);
    }

    if(SavedState)SaveEverything(SavedState[LouKeGetCurrentProcessorNumber()]);
    uint8_t* d = (uint8_t*)destination;
    const uint8_t* s = (const uint8_t*)source;

    if (d == s || num == 0) return destination;

    if (d < s || d >= (s + num)) {
        size_t count = num / 64;
        for (size_t i = 0; i < count; ++i) {
            __m512i tmp = _mm512_loadu_si512((const void*)(s + i * 64));
            _mm512_storeu_si512((void*)(d + i * 64), tmp);
        }
        for (size_t i = count * 64; i < num; ++i) {
            d[i] = s[i];
        }
    } 
    else {
        size_t remaining = num % 64;
        for (size_t i = 1; i <= remaining; ++i) {
            d[num - i] = s[num - i];
        }

        size_t count = num / 64;
        for (size_t i = count; i > 0; --i) {
            size_t offset = (i - 1) * 64;
            __m512i tmp = _mm512_loadu_si512((const void*)(s + offset));
            _mm512_storeu_si512((void*)(d + offset), tmp);
        }
    }
    if(SavedState)RestoreEverything(SavedState[LouKeGetCurrentProcessorNumber()]);
    return destination;
}
*/

LOUAPI uint16_t GetNPROC();


KERNEL_EXPORT void* memcpy(void* destination, const void* source, size_t num) {
    if (destination == source || num == 0) return destination;
    if (destination > source && (uintptr_t)destination < (uintptr_t)source + num) {
        uint8_t* d_end = (uint8_t*)destination + num - 1;
        const uint8_t* s_end = (const uint8_t*)source + num - 1;
        __asm__ volatile (
            "std\n\t"
            "rep movsb\n\t"
            "cld"
            : "+D"(d_end), "+S"(s_end), "+c"(num)
            :
            : "memory"
        );
    } 
    else {
        __asm__ volatile (
            "cld\n\t"
            "rep movsb"
            : "+D"(destination), "+S"(source), "+c"(num)
            :
            : "memory"
        );
    }
    return destination;
}
