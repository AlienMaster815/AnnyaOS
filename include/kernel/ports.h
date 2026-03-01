#ifndef _PORTS_H
#define _PORTS_H

#include <cstdint.h>
#include <stddef.h>



#ifdef __x86_64__
uint64_t read_msr(uint32_t msr_id);
#endif

#endif
