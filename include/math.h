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


#define LN2 0.69314718055994530942
#define E   2.71828182845904523536

static inline double klog(double x) {
    if (x <= 0.0) {
        return 0.0/0.0; 
    }

    int exp = 0;

    while (x >= 2.0) { x *= 0.5; exp++; }
    while (x < 0.5) { x *= 2.0; exp--; }

    double z  = (x - 1.0) / (x + 1.0);
    double z2 = z * z;

    double term = z;
    double sum  = 0.0;

    for (int n = 1; n <= 19; n += 2) {
        sum += term / n;
        term *= z2;
    }

    return 2.0 * sum + exp * LN2;
}

#define log(x) klog(x)

static inline double kfloor(double x) {
    long long i = (long long)x;

    if (x < 0.0 && x != (double)i) {
        return (double)(i - 1);
    }
    return (double)i;
}

#define floor(x) kfloor(x)

#ifdef __cplusplus
}
#endif

#endif