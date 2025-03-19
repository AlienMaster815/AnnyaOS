#ifndef _USER_THREAD_H
#define _USER_THREAD_H

#ifdef __cplusplus
extern "C"{
#endif


typedef struct {
    bool locked;
} mutex_t;

static inline void MutexLock(mutex_t* m){
    while(m->locked == true){
        //spinlock
    }
    m->locked = true;
}

static inline void MutexUnlock(mutex_t* m){
    m->locked = false;
}

static inline void MutexSyncronize(mutex_t* m){
    while(m->locked){
        //spinlock
    }
}

static inline bool MutexIsLocked(mutex_t* m){
    if(m->locked)return true;
    return false;
}




#ifdef __cplusplus
}
#endif
#endif