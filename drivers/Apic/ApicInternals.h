#ifndef _APIC_INTERNALS_H
#define _APIC_INTERNALS_H

#include <LouAPI.h>

typedef enum{
    APIC_TIMER_MODE_ONE_SHOT = 0,
    APIC_TIMER_MODE_PERIODIC,
    APIC_TIMER_MODE_TSC_DEADLINE,
}APIC_TIMER_MODE;

typedef enum{
    APIC_LVT_DELIVERY_MODE_FIXED    = 0b0000,
    APIC_LVT_DELIVERY_MODE_SMI      = 0b0010,
    APIC_LVT_DELIVERY_MODE_NMI      = 0b0100,
    APIC_LVT_DELIVERY_MODE_EXT_INT  = 0b0111,
    APIC_LVT_DELIVERY_MODE_INIT     = 0b1000,
}APIC_LVT_DELIVERY_MODE;

typedef enum {
    APIC_TRIGGER_MODE_EDGE = 0,
    APIC_TRIGGER_MODE_LEVEL,
}APIC_TRIGGER_MODE;

typedef enum{
    APIC_IN_PIN_POLARITY_ACTIVE_HIGH = 0,
    APIC_IN_PIN_POLARITY_ACTIVE_LOW,
}APIC_IN_PIN_POLARITY;

typedef enum{
    APIC_ERROR_STATUS_SEND_CHECKSUM_ERROR =     (1),
    APIC_ERROR_STATUS_RECEIVE_CHECKSUM_ERROR =  (1 << 1),
    APIC_ERROR_STATUS_SEND_ACCEPT_ERROR =       (1 << 2),
    APIC_ERROR_STATUS_RECEIVE_ACCEPT_ERROR =    (1 << 3),
    APIC_ERROR_STATUS_REDIRECT_IPI =            (1 << 4),
    APIC_ERROR_STATUS_SEND_ILLEGAL_VECTOR =     (1 << 5),
    APIC_ERROR_STATUS_RECEIVE_ILLEGAL_VECTOR =  (1 << 6),
    APIC_ERROR_STATUS_ILLEGAL_VECTOR_ADDRESS =  (1 << 7),
}APIC_ERROR_STATUS;

typedef enum{
    APIC_TIMER_DIVIDE_BY2   = 0b0000,
    APIC_TIMER_DIVIDE_BY4   = 0b0001,
    APIC_TIMER_DIVIDE_BY8   = 0b0010,
    APIC_TIMER_DIVIDE_BY16  = 0b0011,
    APIC_TIMER_DIVIDE_BY32  = 0b1000,
    APIC_TIMER_DIVIDE_BY64  = 0b1001,
    APIC_TIMER_DIVIDE_BY128 = 0b1010,
    APIC_TIMER_DIVIDE_BY1   = 0b1011, 
}APIC_TIMER_DIVIDE_CONFIG;

typedef enum {
    APIC_ICR_DELIVERY_MODE_FIXED = 0,
    APIC_ICR_DELIVERY_MODE_LOWEST_PRIORITY,
    APIC_ICR_DELIVERY_MODE_SMI,
    APIC_ICR_DELIVERY_MODE_RSVD0,
    APIC_ICR_DELIVERY_MODE_NMI,
    APIC_ICR_DELIVERY_MODE_INIT,
    APIC_ICR_DELIVERY_MODE_STARTUP,
}APIC_ICR_DELIVERY_MODE;

typedef enum{
    APIC_DESTINATION_MODE_PHYSICAL = 0,
    APIC_DESTINATION_MODE_LOGICAL,
}APIC_DESTINATION_MODE;

typedef enum{
    APIC_LEVEL_DE_ASSERT = 0,
    APIC_LEVEL_ASSERT,
}APIC_LEVEL;

typedef enum{
    APIC_DESTINATION_SHORTHAND_NONE,
    APIC_DESTINATION_SHORTHAND_SELF,
    APIC_DESTINATION_SHORTHAND_ALL,
    APIC_DESTINATION_SHORTHAND_ALL_ES, //excluding self
}APIC_DESTINATION_SHORTHAND;

typedef struct _APIC_DEVICE_OBJECT{
    mutex_t     WriteLock;
    PVOID       ApicBase;
}APIC_DEVICE_OBJECT, * PAPIC_DEVICE_OBJECT;

//TODO: 

//if ESR bit 4 is set then a redirectable IPI with lowest prioirty 
//is not supported so an IPI sender must check this in an error to 
//verify if this caused and error

//if ESR bit 5 is set the handler must scan through all local 
//tables and if the vector is 0 through 15 and print

//if ESR bit 6 is set the handler must scan through all local 
//tables and if the vector is 0 through 15 and print

//if ESR bit 7 is set the handler must attatch to the GPF Handler
//and disable whatever kernel thread or user process accessed 
//created the GPF


#endif