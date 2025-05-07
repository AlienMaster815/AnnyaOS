#ifndef _ACPI_THERMAL_H
#define _ACPI_THERMAL_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

typedef enum{
    Active = 0,
    Passive = 1,
}LOUACPI_PREFERED_COOLING_METHOD;



#ifdef __cplusplus
}
#endif
#endif