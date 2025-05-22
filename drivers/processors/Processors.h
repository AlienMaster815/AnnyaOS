#ifndef _PROCESRS_H
#define _PROCESRS_H

#include <LouDDK.h>
#include <NtAPI.h>

KERNEL_IMPORT uint16_t GetNPROC();
KERNEL_IMPORT void UpgradeNPROC();
KERNEL_IMPORT void DowngradeNPROC();

KERNEL_IMPORT void cpuid(unsigned int code, unsigned int* eax, unsigned int* ebx, unsigned int* ecx, unsigned int* edx);

#define IS_PENTIUM4 family == 0xF && model >= 0x3 && model <= 0xF
#define IS_XENON51xx family == 0xF && model == 0xF
#define IS_CORE2 family == 0x6 && (model == 0xE || model == 0xF)
#define IS_XENON54xx family == 0xF && model == 0x5
#define IS_INTEL_CORE (family == 0x6 && model >= 0xE) || (family == 0xF && model >= 0x6)
#define IS_ATOM_200_300 family == 0x6 && model == 0x2C
#define IS_ATOM_N family == 0x6 && model == 0x27

typedef struct {
    uint8_t* Base;
    uint8_t* Top;
} Stack;

namespace CPU{

    typedef 
    enum{
        UNKNOWNVen,
        INTEL,
        AMD,
        VIA,
    }VENDOR_ID;

    typedef enum{
        FPU,
        SMP,
        MMX,
        SSE1,
        SSE2,
        SSE3,
        SSE4A,
        SSE42,
        HYPERTHREAD,
        APIC,
        XAPIC,
        X2APIC,
        //New NEM Features
        LAHFSAHF,
        XOP,
        POPCNT,
        CMPXCHG16B,
        ALTMOVCR8,
        LZCNT,
        MISALIGNSSE,
        MMXEXT,
        AMD3DNOW,
        EXTENDEDAMD3DNOW,
        PAGE1GB,
        AES,
        PCLMULQDQ,
        PCID,
        FMA4,
        F16,
        RDRAND,
        RDWRFSGS,
        SMEP,
        ENHANCEDFASTSTRING,
        BMI1,
        BMI2,
        MOVBE,
        NPIEP1,
        DEPX87FPUSACE,
        RDSEED,
        ADX,
        INTELPREFETCH,
        SMAP,
        HLE,
        RTM,
        RDTSPC,
        CLFUSHOPT,
        CLWB,
        SHA,
        X87POINTERSAVE,
        //NEW CPUID Featuers
        VME,
        DE,
        PSE,
        TSC,
        MSR,
        MCE,
        CX8,
        //APIC,
        SEP,
        MTRR,
        PGE,
        MCA,
        CMOV,
        PAT,
        //PSE,
        PSN,
        CLFLUSH,
        DS,
        ACPITHERM,
        FXSR,
        SS,
        TM,
        PBE,
        PCLMUL,
        DTES64,
        MONITOR,
        CPLDS,
        VMX,
        SMX,
        EST,
        TM2,
        CNTXID,
        SDBG,
        FMA,
        CX16,
        TPRUPDATE,
        PDCM,
        //PCID,
        DCA,
        ///MOVBE,
        //POPCNT,
        XSAVE,
        OSXSAVE,
        AVX,
        F16C,
        HVP,
        //Leaf 7
        MNEMONIC,
        FSGBASE,
        TSCADJUST,
        SGX,
        AVX2,
        FDPONLY,
//        SMEP,
        ERMS,
        INVPCID,
        //RTM,
        PQM,
        DEP_FPU_CS_DS,
        MPE,
        PQE,
        AVX512F,
        SEVENTEEN,
        //RDSEED,
        TWENTYONE,
        INTELPT,
        AVX512PF,
        AVX512ER,
        AVX512CD,
        THIRTY,
        THIRTYONE,
        PREFETCHCHWT1,
        ONE,
        UMIP,
        PKU,
        OSPKE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        ELEVEN,
        TWELVE,
        FOURTEEN,
        MAWAU,
        RDPID,
        SGXLC,
        FOUR,
        MDCLEAR,
        IBRS_IBPB,
        STI8P,
        FLUSH_CMD,
        ARCHCAP,
        CORECAP,
        SSBD,
        //Leaf 0xD
        XSAVE_SIZE,
        XSAVE_FERATURES,
    }FEATURE;

    typedef enum{
        UNKNOWNProc,
        PENTIUM_4_PROCESSOR,
        XENON51xx,
        CORE2,
        XENON54xx,
        INTEL_CORE,
        ATOM_Family,
        ATHLONX1,
        ATHLONX2,
        PHENOM,
        RYZEN,
    }PROCCESSOR_ID;

    typedef struct {
        VENDOR_ID CpuVenId;
        PROCCESSOR_ID ProccessorId;
        uint64_t ProccessorVersion;
        uint16_t NumberOfProcessors;
    }CPUID_PACKET, * PCPUID_PACKET;

    class CPUID {
        public:
            CPUID();
            ~CPUID();
            bool IsProcessorBrand(VENDOR_ID Ven);
            bool IsProcessorId(PROCCESSOR_ID ProcID);
            uint64_t GetProcessorVersion();
            uint16_t GetNumberOfProcessors();
            bool IsFeatureSupported(FEATURE Feature);
        private:
            bool ParseCpuFeature(FEATURE Feature);
            PCPUID_PACKET CpuIdPacket;

        #define FPU_MASK 0x01 //bit 1
        #define SMP_MASK 0x01 << 1 //bit 2
        #define MMX_MASK 0x01 << 2 //bit 3
        #define SSE_MASK 0x0F << 3
        #define HYPERTHREAD_MASK 0x01 << 7
    };
};
#endif