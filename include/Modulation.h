#ifndef _MODULATION_H
#define _MODULATION_H

#ifndef _USER_MODE_CODE_
#ifdef __cplusplus
#define DRIVER_IMPORT extern "C" __declspec(dllimport)
#define LOUAPI extern "C"
#else
#define DRIVER_IMPORT __declspec(dllimport)
#define LOUAPI 
#endif
#endif

#ifndef _KERNEL_MODULE_
#ifdef __cplusplus
#define KERNEL_EXPORT extern "C" __declspec(dllexport)
#define DRIVER_EXPORT extern "C" __declspec(dllimport)
#else
#define KERNEL_EXPORT __declspec(dllexport)
#define DRIVER_EXPORT __declspec(dllimport)
#endif
#else
#ifdef __cplusplus
#define KERNEL_EXPORT extern "C" __declspec(dllimport)
#define DRIVER_EXPORT extern "C" __declspec(dllexport)
#else
#define KERNEL_EXPORT __declspec(dllimport)
#define DRIVER_EXPORT __declspec(dllexport)
#endif
#endif



#endif