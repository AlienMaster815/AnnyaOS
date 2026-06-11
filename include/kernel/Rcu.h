#ifndef _RCU_H
#define _RCU_H

typedef struct _SRCU_PER_CPU_OBJECT{
    LouKIRQL                Irql;
    int                     NonRcuSleepableProcessorIndex;
    KERNEL_REFERENCE        Readers;
    PVOID                   CurrentReader;
}SRCU_PER_CPU_OBJECT, * PSRCU_PER_CPU_OBJECT,
  RCU_PER_CPU_OBJECT, *  PRCU_PER_CPU_OBJECT;

typedef struct _SRCU_OBJECT{
    BOOLEAN                 Sleepable;
    BOOLEAN                 MbAfterReadUnlock;
    PVOID                   Writer;
    PSRCU_PER_CPU_OBJECT    PerCpuData;
}SRCU_OBJECT, * PSRCU_OBJECT,
  RCU_OBJECT, *  PRCU_OBJECT;

#define DEFINE_SRCU(Name) \
    SRCU_OBJECT Name = { \
        .Sleepable = true, \
    }

#define DEFINE_RCU(Name) \
    SRCU_OBJECT Name = { \
        .Sleepable = false, \
    }

#define DEFINE_STATIC_SRCU(Name) \
    static SRCU_OBJECT Name = { \
        .Sleepable = true, \
    }

#define DEFINE_STATIC_RCU(Name) \
    static SRCU_OBJECT Name = { \
        .Sleepable = false, \
    }

//TODO: Fast
KERNEL_EXPORT LOUSTATUS LouKeInitializeSrcuObject(PSRCU_OBJECT SrcuObject);
KERNEL_EXPORT LOUSTATUS LouKeInitializeRcuObject(PRCU_OBJECT RcuObject);

KERNEL_EXPORT void LouKeDeInitializeSrcuObject(PSRCU_OBJECT SrcuObject);
KERNEL_EXPORT void LouKeDeInitializeRcuObject(PRCU_OBJECT RcuObject);

KERNEL_EXPORT void LouKeForceSrcuMbAfterReadUnlock(PSRCU_OBJECT SrcuObject);
KERNEL_EXPORT void LouKeForceRcuMbAfterReadUnlock(PRCU_OBJECT RcuObject);

KERNEL_EXPORT int LouKeSrcuAcquireReadLock(PRCU_OBJECT RcuObject);
KERNEL_EXPORT void LouKeRcuAcquireReadLock();

KERNEL_EXPORT void LouKeSrcuReleaseReadLock(PSRCU_OBJECT SrcuObject, int Processor);
KERNEL_EXPORT void LouKeRcuReleaseReadLock(PSRCU_OBJECT SrcuObject);


#endif