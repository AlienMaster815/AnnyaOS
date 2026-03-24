#ifndef _ATOMIC_H
#define _ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdatomic.h>

typedef struct {
	int counter;
}atomic_t;

typedef struct {
    INT64 counter;
}ATOMIC64, atomic_int64_t;

typedef atomic_t* p_atomic_t;

#define ATOMIC_TRUE  1
#define ATOMIC_FALSE 0

typedef atomic_t ATOMIC, * PATOMIC, ATOMIC_BOOLEAN, * PATOMIC_BOOLEAN;


static inline int atomic_read(atomic_t* v) {
    return __atomic_load_n(&v->counter, __ATOMIC_SEQ_CST);
}

static inline void atomic_set(atomic_t* v, int i) {
    __atomic_store_n(&v->counter, i, __ATOMIC_SEQ_CST);
}

static inline void atomic_write(atomic_t* v, int i) {
    __atomic_store_n(&v->counter, i, __ATOMIC_SEQ_CST);
}

static inline bool atomic_cmpxchg(atomic_t* v, int old, int newv) {
    return __atomic_compare_exchange_n(&v->counter, &old, newv, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

static inline int64_t atomic64_read(atomic_int64_t* v) {
    return __atomic_load_n(&v->counter, __ATOMIC_SEQ_CST);
}

static inline void atomic64_set(atomic_int64_t* v, int i) {
    __atomic_store_n(&v->counter, i, __ATOMIC_SEQ_CST);
}

static inline void atomic64_write(atomic_int64_t* v, int i) {
    __atomic_store_n(&v->counter, i, __ATOMIC_SEQ_CST);
}

static inline bool atomic64_cmpxchg(atomic_int64_t* v, int old, int newv) {
    return __atomic_compare_exchange_n(&v->counter, &old, newv, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}


#ifdef __cplusplus
}
#endif
#endif