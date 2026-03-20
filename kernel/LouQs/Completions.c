#include <LouAPI.h>

KERNEL_EXPORT 
LOUSTATUS 
LouKeWaitForCompletionTimeout(
    PLOUQ_COMPLETION    Completion,
    SIZE                Hz
){
    return LouKeWaitForAtomicBooleanRegisterConditionHz(
        &Completion->Completed,
        Hz,
        true
    );
}
