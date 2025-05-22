#ifndef _ACPI_BATTERY_H
#define _ACPI_BATTERY_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

//Remaining battery Percentage = (BateryRemaining / LastFullCharge) * 100
//Remaining Battery Life Hors = (Battery / BatteryPresentDrainRate)
//Low Events:go into hibernate
//Cirtical Event: emergency shutdown : no saving things
//calibration can be done with hardware or _BMD method


#ifdef __cplusplus
}
#endif
#endif