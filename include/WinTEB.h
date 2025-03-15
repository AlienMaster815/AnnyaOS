#ifndef _WINTEB_H
#define _WINTEB_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

typedef struct __attribute__((packed, aligned(8))) _WIN_TEB {
    uint64_t TebNtTibExceptList;
    uint64_t TebNtTibStackBase;        
    uint64_t TebNtTibStackLimit;       
    uint64_t TebNtTibSubSystemTib;     
    uint64_t TebNtTibFiberData;        
    uint64_t TebNtTibArbitraryUserPtr; 
    uint64_t TebNtTibSelf;             
    uint64_t TebEnvironmentPointer;     
    uint64_t TebClientIdUniqueProcess; 
    uint64_t TebClientIdUniqueThread;  
    uint64_t TebActiveRpcHandle;        
    uint64_t TebThreadLocalStoragePtr;  
    uint64_t TebProcessEnvironmentBlock;
    uint32_t TebLastErrorValue;         
    uint32_t TebCountOfCriticalSections;
    uint64_t TebCsrClientThread;
    uint64_t TebWin32ThreadInfo;
    uint32_t TebUser32Reserved[26];
    uint64_t TebWOW32Reserved;
    uint32_t TebCurrentLocale;
    uint32_t TebFpSoftwareStatusRegister;
    uint64_t TebSystemReserved1[54];
    uint64_t TebExceptionCode;
    uint8_t TebActivationContextStack[40];
    uint8_t TebSpareBytes1[24];
    uint64_t TebSystemReserved2[26];
    uint64_t TebTlsExpansionSlots;      
    uint64_t TebDeallocationStack;
    uint64_t TebTlsSlots[64];           
    uint8_t TebReservedForOle[8];       
    uint64_t TebReservedForNtRpc[4];    
    uint64_t TebTlsExpansionSlotsExtra;
} WIN_TEB, *PWIN_TEB;


#ifdef __cplusplus
}
#endif
#endif