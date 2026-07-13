#ifndef _PORTS_H
#define _PORTS_H

#include <cstdint.h>

#ifndef _USER_MODE_CODE_
uint64_t LouKeReadMsr(uint32_t msr_id);
void     LouKeWriteMsr(uint32_t msr_id, uint64_t Value);
#endif
#endif
