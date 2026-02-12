#ifndef _KERNEL_SECURITY_H
#define _KERNEL_SECURITY_H

#ifdef _USER_MODE_CODE_
#include <Annya.h>
#else
#ifndef __cplusplus
#include <LouAPI.h>
#else 
#include <LouDDK.h>
extern "C" {
#endif
#endif

typedef DWORD ACCESS_MASK, * PACCESS_MASK;


#define ACCESS_MASK_OBJSPEC_MASK        0xFFFF
#define ACCESS_MASK_OBJSPEC_SHIFT       0x00
#define ACCESS_MASK_OBJSPEC             (ACCESS_MASK_OBJSPEC_MASK << ACCESS_MASK_OBJSPEC_SHIFT)

#define ACCESS_MASK_STD_RIGHTS_MASK     0xFF
#define ACCESS_MASK_STD_RIGHTS_SHIFT    16
#define ACCESS_MASK_STD_RIGHTS          (ACCESS_MASK_STD_RIGHTS_MASK << ACCESS_MASK_STD_RIGHTS_SHIFT)
#define     STD_ACCESS_DELETE           (1UL << 16)
#define     STD_ACCESS_READ_CONTROL     (1UL << 17)
#define     STD_ACCESS_WRITE_DAC        (1UL << 18)
#define     STD_ACCESS_WRITE_OWNER      (1UL << 19)
#define     STD_ACCESS_SYNCHRONIZE      (1UL << 20)
#define     STD_RIGHTS_REQUIRED         (0xFUL << 16)
#define     STD_RIGHTS_ALL              (0x1FUL << 16)
#define     STD_RIGHTS_READ             (STD_ACCESS_READ_CONTROL)
#define     STD_RIGHTS_WRITE            (STD_ACCESS_READ_CONTROL)
#define     STD_RIGHTS_EXECUTE          (STD_ACCESS_READ_CONTROL)
#define ACCESS_MASK_GENERIC_ALL         (1UL << 28)
#define ACCESS_MASK_GENERIC_EXECUTE     (1UL << 29)
#define ACCESS_MASK_GENERIC_WRITE       (1UL << 30)
#define ACCESS_MASK_GENERIC_READ        (1UL << 31)



#ifdef __cplusplus
}
#endif
#endif