#include "X2ApicInternals.h"

//reusing x1 code for sanity

UINT32 ApicHalGetX2ApicId(){
    return ApicHalGetX2ApicIdRegister();
}

UINT32 ApicHalGetX2ApicVersion(){
    UINT32 Register = ApicHalGetX2ApicVersionRegister();
    return GET_X1APIC_VERSION_VALUE(Register);
}

UINT32 ApicHalGetX2ApicMaxLvtEntry(){
    UINT32 Register = ApicHalGetX2ApicVersionRegister();
    return GET_X1APIC_MAX_LVT_ENTRY_VALUE(Register);
}

BOOLEAN ApicHalX2ApicSupportsEoiSuppression(){
    UINT32 Register = ApicHalGetX2ApicVersionRegister();
    return GET_X1APIC_SUPPORT_EOI_SUPRESS_VALUE(Register) ? true : false;
}

APIC_TIMER_MODE ApicHalGetX2ApicLvtTimerMode(){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    return (APIC_TIMER_MODE)GET_X1APIC_LVT_TIMER_MODE(Register);
}

BOOLEAN ApicHalIsX2ApicLvtTimerMasked(){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    return GET_X1APIC_LVT_TIMER_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX2ApicLvtTimerInterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    return GET_X1APIC_LVT_TIMER_DELIVERY_STATUS(Register) ? true : false;
}

UINT8 ApicHalGetX2ApicLvtTimerVector(){
    UINT32 Register = ApicHalGetX2ApicLvtTimerRegister();
    return (UINT8)GET_X1APIC_LVT_TIMER_VECTOR(Register); 
}

BOOLEAN ApicHalIsX2ApicLvtCmciMasked(){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    return GET_X1APIC_LVT_CMCI_MASK(Register) ? true : false;
}

BOOLEAN ApicHalIsX2ApicLvtCmciInterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    return GET_X1APIC_LVT_CMCI_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtCmciDeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LVT_CMCI_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtCmciVector(){
    UINT32 Register = ApicHalGetX2ApicLvtCmciRegister();
    return (UINT8)GET_X1APIC_LVT_CMCI_VECTOR(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint0Masked(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return GET_X1APIC_LINT0_MASK(Register) ? true : false;
}

APIC_TRIGGER_MODE ApicHalGetX2ApicLvtLint0TriggerMode(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return (APIC_TRIGGER_MODE)GET_X1APIC_LINT0_TRIGGER_MODE(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint0IrrSet(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return GET_X1APIC_LINT0_REMOTE_IRR(Register) ? true : false;
}

APIC_IN_PIN_POLARITY ApicHalGetX2ApicLvtLint0InPinPolarity(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT0_INT_PIN_POLARITY(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint0InterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return GET_X1APIC_LINT0_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtLint0DeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LINT0_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtLint0Vector(){
    UINT32 Register = ApicHalGetX2ApicLvtLint0Register();
    return (UINT8)GET_X1APIC_LINT0_VECTOR(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint1Masked(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return GET_X1APIC_LINT1_MASK(Register) ? true : false;
}

APIC_TRIGGER_MODE ApicHalGetX2ApicLvtLint1TriggerMode(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return (APIC_TRIGGER_MODE)GET_X1APIC_LINT1_TRIGGER_MODE(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint1IrrSet(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return GET_X1APIC_LINT1_REMOTE_IRR(Register) ? true : false;
}

APIC_IN_PIN_POLARITY ApicHalGetX2ApicLvtLint1InPinPolarity(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return (APIC_IN_PIN_POLARITY)GET_X1APIC_LINT1_INT_PIN_POLARITY(Register);
}

BOOLEAN ApicHalIsX2ApicLvtLint1InterruptPending(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return GET_X1APIC_LINT1_DELIVERY_STATUS(Register) ? true : false;
}

APIC_LVT_DELIVERY_MODE ApicHalGetX2ApicLvtLint1DeliveryMode(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return (APIC_LVT_DELIVERY_MODE)GET_X1APIC_LINT1_DELIVERY_MODE(Register);
}

UINT8 ApicHalGetX2ApicLvtLint1Vector(){
    UINT32 Register = ApicHalGetX2ApicLvtLint1Register();
    return (UINT8)GET_X1APIC_LINT1_VECTOR(Register);
}

//134