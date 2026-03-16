#ifndef _RANDOM_H
#define _RANDOM_H

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _USER_MODE_CODE_

KERNEL_EXPORT uint64_t Random(uint64_t Seed);

#endif
#ifdef __cplusplus
}
#endif

#endif