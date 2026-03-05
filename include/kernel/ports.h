#ifndef _PORTS_H
#define _PORTS_H

#include <cstdint.h>

#ifndef _USER_MODE_CODE_
uint64_t read_msr(uint32_t msr_id);
#endif
#endif
