#ifndef _APIC_INTERNALS_H
#define _APIC_INTERNALS_H

#include "X1ApicInternals.h"

typedef struct _APIC_DEVICE_OBJECT{

    PVOID       ApicBase;
}APIC_DEVICE_OBJECT, * PAPIC_DEVICE_OBJECT;

#endif