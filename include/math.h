#ifndef _MATH_H
#define _MATH_H

#ifdef __cplusplus
extern "C"{
#endif

#define IsPowerOf2(x) ((x) > 0 && ((x) & ((x) - 1)) == 0)

static inline int ILog2(unsigned int x) {
    int result = 0;
    while (x >>= 1) { // Right shift until x becomes 0
        result++;
    }
    return result;
}


#ifdef __cplusplus
}
#endif

#endif