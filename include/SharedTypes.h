/*
-- Tyler Radomski-Grennier 9/6/20 11:17
-- NOTICE: This File Is Only mFor Types 
-- And The Types Are For ALL Subsystems 
*/
#ifndef _STYPES_H
#define _STYPES_H

#ifndef __INT_MAX__
#define INT_MAX 2147483647
#endif

typedef uint8_t LouKIRQL;

typedef struct _Fixed20_12{
    int32_t FULL;
}Fixed20_12;

// Extract the integer part
#define FIXED20_12_INTEGER(value) ((value) >> 12)

// Extract the fractional part
#define FIXED20_12_FRACTIONAL(value) ((value) & 0xFFF)

// Create a fixed20_12 number from integer and fractional parts
#define MAKE_FIXED20_12(integer, fractional) (((integer) << 12) | (fractional & 0xFFF))


#define DFixedConst8(x)  ((x) << 3) // multiply by 8 and convert to fixed-point representation

#define DFixedConst(x) ((x) << 12)

#define DFixedMul(a,b) (((int64_t)(a.FULL) * (int64_t)(b.FULL)) >> 12)
#define DFixedDiv(a, b) (((int64_t)(a.FULL) << 12) / (b.FULL))
// DFixedConst_666 multiplies an integer by 666 and converts it to fixed-point format
#define DFixedConst666(x)  ((x) * 666 << 12)
// DFixed_const_half adds 0.5 to the integer and converts it to fixed-point format
#define DFixedConstHalf(x)  (((x) << 12) + (1 << 11))
#define DFixedTrunc(value) ((value).FULL >> 12)
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define MinimumOfTwo(type, x, y) \
    ({ type __min1 = (x); type __min2 = (y); __min1 < __min2 ? __min1 : __min2; })


#ifndef _KERNEL_MODULE_
static inline int
RoundUpPowerOf2(int x)
{
    if (x < 0)
        return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}

static inline Fixed20_12 DFixedInit(int32_t value) {
    Fixed20_12 result;

    // Assume the input is a whole integer and shift it into the fixed-point format.
    result.FULL = value << 12;  // Shift by 12 to fill the integer part.

    return result;
}

static inline Fixed20_12 DFixedInitHalf(int32_t integer_part){
    Fixed20_12 result;

    // Shift the integer part into the upper 20 bits
    result.FULL = integer_part << 12;

    // Add 0.5 to the fractional part
    result.FULL += 1 << 11; // 0.5 in fixed20_12 format
    return result;
}

typedef struct _INT_512{
    __int128 low;  // Lower 128 bits
    __int128 high; // Higher 128 bits
} int512_t;




#endif
typedef struct  _ListHeader{
    struct _ListHeader* LastHeader;
    struct _ListHeader* NextHeader;
}ListHeader, * PListHeader;


#define HighQuad(v) ((__int128)v >> 64)
#define LowQuad(v) ((__int128)v & 0xFFFFFFFFFFFFFFFF)

#define GetStackVariable(offset) (*(uintptr_t*)((uintptr_t)__builtin_frame_address(0) - (offset)))
#define SetStackVariable(offset, value) (*(uintptr_t*)((uintptr_t)__builtin_frame_address(0) - (offset)) = (uintptr_t)(value))

typedef struct _DELAYED_FUNCTION{
    void    (*DelayedFunction)(void* WorkData);
    void*   WorkData;
}DELAYED_FUNCTION, * PDELAYED_FUNCTION;

typedef int         LOU_TOKEN;
typedef uint64_t    COUNTER;

static inline
uint16_t ConvertBeToLeU16(uint16_t Foo){
    uint16_t Tmp1, Tmp2;
    Tmp1 = Foo & 0xFF;
    Tmp2 = Foo >> 8;
    return (Tmp1 << 8) | Tmp2;
}

static inline
uint32_t ConvertBeToLeU32(uint32_t Foo) {
    uint32_t Tmp1, Tmp2, Tmp3, Tmp4;
    Tmp1 = Foo & 0xFF;
    Tmp2 = (Foo >> 8) & 0xFF;
    Tmp3 = (Foo >> 16) & 0xFF;
    Tmp4 = (Foo >> 24) & 0xFF;    
    return (Tmp1 << 24) | (Tmp2 << 16) | (Tmp3 << 8) | Tmp4;
}

static inline
uint64_t ConvertBeToLeU64(uint64_t Foo) {
    uint64_t Tmp1, Tmp2, Tmp3, Tmp4, Tmp5, Tmp6, Tmp7, Tmp8;
    Tmp1 = Foo & 0xFF;
    Tmp2 = (Foo >> 8) & 0xFF;
    Tmp3 = (Foo >> 16) & 0xFF;
    Tmp4 = (Foo >> 24) & 0xFF;
    Tmp5 = (Foo >> 32) & 0xFF;
    Tmp6 = (Foo >> 40) & 0xFF;
    Tmp7 = (Foo >> 48) & 0xFF;
    Tmp8 = (Foo >> 56) & 0xFF;
    return (Tmp1 << 56) | (Tmp2 << 48) | (Tmp3 << 40) | (Tmp4 << 32) | (Tmp5 << 24) | (Tmp6 << 16) | (Tmp7 << 8)  | Tmp8;
}


typedef struct _PCIE_SYSTEM_MANAGER{
    ListHeader  Neighbors;
    uint64_t    BaseAddress;
    uint16_t    PCISegmentGroupNumber;
    uint8_t     StartBusNumber;
    uint8_t     EndBusNumber;
}PCIE_SYSTEM_MANAGER, * PPCIE_SYSTEM_MANAGER;

#endif
