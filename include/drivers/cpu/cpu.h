#ifndef _PROCESSOR_CPU_H
#define _PROCESSOR_CPU_H
#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

#include "IntelFamily.h"
#include "Processor.h"


typedef struct _PROCESSOR_PPIN_INFORMATION{
    int32_t     Feature;
    int32_t     MsrPPINControl;
    int32_t     MsrPPIN;
}PROCESSOR_PPIN_INFORMATION, * PPROCESSOR_PPIN_INFORMATION;

typedef struct _PPIN_CPU_ID{
    uint16_t    Vendor;
    uint16_t    Family;
    uint16_t    Model;
    uint16_t    Stepping;
    uint16_t    Feature;
    uint16_t    Flags;
    uint8_t     Type;
    uintptr_t   DrvDat;
}PPIN_CPU_ID, PPPIN_CPU_ID;

#define X86_64_VENDOR_ANY           0xFFFF
#define X86_64_FAMILY_ANY           0
#define X86_64_MODEL_ANY            0 
#define X86_64_STEPPING_ANY         0
#define X86_64_STEPPING_MINIMUM     0
#define X86_64_STEPPING_MAXIMUM     0x0F
#define X86_64_FEATURE_ANY          0
#define X86_64_CPU_TYPE_ANY         0

#define X86_64_VENDOR_INTEL         0
#define X86_64_VENDOR_CYRIX         1
#define X86_64_VENDOR_AMD           2
#define X86_64_VENDOR_UMC           3
#define X86_64_VENDOR_CENTUAR       5
#define X86_64_VENDOR_TRANSMETA     7   
#define X86_64_VENDOR_NSC           8
#define X86_64_VENDOR_HYGON         9
#define X86_64_VENDOR_ZHAOXIN       10
#define X86_64_VENDOR_VORTEX        11
#define X86_64_VENDOR_NUM           12

#define X86_64_CPU_ID_FLAG_ENTRY_VALID   1

#define X86_64_DEFINE_CPU_ID(_Vendor, _Family, _Model, _Stepping, \
                                _Feature, _Type, _DrvDat) \
    .Vendor = (uint16_t)_Vendor, \
    .Family = (uint16_t)_Family, \
    .Model = (uint16_t)_Model, \
    .Stepping = (uint16_t)_Stepping, \
    .Feature = (uint16_t)_Feature, \
    .Flags = X86_64_CPU_ID_FLAG_ENTRY_VALID,\
    .Type = (uint16_t)_Type, \
    .DrvDat = (uintptr_t)_DrvDat,

#define X86_64_DEFINE_FEATURE(Feature, Data) \
    X86_64_DEFINE_CPU_ID(X86_64_VENDOR_ANY, X86_64_FAMILY_ANY, \
        X86_64_MODEL_ANY, X86_64_STEPPING_ANY, Feature, X86_64_CPU_TYPE_ANY, Data)

typedef union _CPU_VFM{
    uint32_t VFM;
    struct {
        uint8_t X86_64Model;
        uint8_t X86_64;
        uint8_t X86_64Vendor;
        uint8_t X86_64Reserved;
    };
}CPU_VFM, * PCPU_VFM;

#define CPU_VFM_WRITE_VENDOR(Vfm, Vendor)   SHIFT_SET_UINT8(Vfm, UINT8_WIDTH * 2 , Vendor)
#define CPU_VFM_READ_VENDOR(Vfm)            SHIFT_RIGHT_GET_UINT8(Vfm, UINT8_WIDTH * 2)

#define CPU_VFM_WRITE_FAMILY(Vfm, Family)   SHIFT_SET_UINT8(Vfm, UINT8_WIDTH * 1 , Family)
#define CPU_VFM_READ_FAMILY(Vfm)            SHIFT_RIGHT_GET_UINT8(Vfm, UINT8_WIDTH * 1)

#define CPU_VFM_WRITE_MODEL(Vfm, Model)     SHIFT_SET_UINT8(Vfm, UINT8_WIDTH * 0, Model)
#define CPU_VFM_READ_MODEL(Vfm)             SHIFT_RIGHT_GET_UINT8(Vfm, UINT8_WIDTH * 0)

#define DEFINE_VFM(V, F, M) ((V << 16) | (F << 8) | (M)) 

#define X86_64_DEFINE_VFM(Vfm, Data) \
    X86_64_DEFINE_CPU_ID(CPU_VFM_READ_VENDOR(Vfm) , CPU_VFM_READ_FAMILY(Vfm), \
        CPU_VFM_READ_MODEL(Vfm), X86_64_STEPPING_ANY, X86_64_FEATURE_ANY, X86_64_CPU_TYPE_ANY, Data)   
    

#define X86_64_VENDOR_UNKNOWN       0xFF

#define X86_64_FEATURE_INTEL_PPIN   (0 << 0)
#define X86_64_FEATURE_AMD_PPIN     (1 << 0)

#define MSR_GENERIC_PPIN_CONTROL    (0 << 0)
#define MSR_AMD_PPIN_CONTROL        (1 << 0)

#define MSR_GENERIC_PPIN            (0 << 0)
#define MSR_AMD_PPIN                (1 << 0)


#ifdef __cplusplus
}
#endif
#endif