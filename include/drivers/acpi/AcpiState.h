#ifndef _ACPI_STATE_H
#define _ACPI_STATE_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

typedef enum{
    Run         = 0,
    Sleeping    = 1,
    Hibernation = 2,
    Shutdown    = 3, 
}LOUACPI_GLOBAL_STATE;

typedef enum {
    D0      = 0,
    D1      = 1,
    D2      = 2,
    D3_Hot  = 3,
    D3_Off  = 4,
}LOUACPI_DEVICE_STATE;

typedef enum {
    S1 = 0, 
    S2 = 1, 
    S3 = 2, 
    S4 = 3, 
    S5 = 4, 
}LOUACPI_HIBERNATION_STATE;

typedef enum {
    C0 = 0,
    C1 = 1,
    C2 = 2, 
    C3 = 3,
}LOUACPI_CPU_POWER_STATE;

typedef enum{
    P0 = 0,
    P1 = 0,
    PN = 0,
}LOUACPI_CPU_PERFORMANCE_STATE;

#ifdef __cplusplus
}
#endif
#endif