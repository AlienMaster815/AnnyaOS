
#ifndef _SECURITY_H
#define _SECURITY_H

#define ACCESS bool

#define GRANTED true
#define DENIED false

//different access levels
typedef enum{
    Kernel,
    System,
    Signed,
    Trusted,
    Admin,
    User,
    LousineInternalAntivirus,
}OperatingMode;

#ifndef _KERNEL_MODULE_
OperatingMode LouKeCheckOperatingMode();
#endif

#endif
