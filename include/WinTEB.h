#ifndef _WINTEB_H
#define _WINTEB_H

#ifndef _USER_MODE_CODE_
#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif
#else
#include <Annya.h>
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
    uint8_t  TebActivationContextStack[40];
    uint8_t  TebSpareBytes1[24];
    uint64_t TebSystemReserved2[26];
    uint64_t TebTlsExpansionSlots;      
    uint64_t TebDeallocationStack;
    uint64_t TebTlsSlots[64];           
    uint8_t  TebReservedForOle[8];       
    uint64_t TebReservedForNtRpc[4];    
    uint64_t TebTlsExpansionSlotsExtra;
} WIN_TEB, *PWIN_TEB;

typedef struct __attribute__((packed, aligned(8))) _WIN_PEB {
    uint8_t  InheritedAddressSpace;       
    uint8_t  ReadImageFileExecOptions;    
    uint8_t  BeingDebugged;               
    uint8_t  BitField;                    
    uint64_t Mutant;                       
    uint64_t ImageBaseAddress;             
    uint64_t Ldr;                          
    uint64_t ProcessParameters;            
    uint64_t SubSystemData;                
    uint64_t ProcessHeap;                  
    uint64_t FastPebLock;                  
    uint64_t AtlThunkSListPtr;             
    uint64_t IFEOKey;                      
    uint32_t CrossProcessFlags;            
    uint8_t  Padding1[4];                  
    uint64_t KernelCallbackTable;          
    uint32_t SystemReserved;               
    uint32_t AtlThunkSListPtr32;           
    uint64_t ApiSetMap;                    
    uint64_t TlsExpansionCounter;          
    uint64_t TlsBitmap;                    
    uint32_t TlsBitmapBits[2];             
    uint64_t ReadOnlySharedMemoryBase;     
    uint64_t HotpatchInformation;          
    uint64_t ReadOnlyStaticServerData;     
    uint64_t AnsiCodePageData;             
    uint64_t OemCodePageData;              
    uint64_t UnicodeCaseTableData;         
    uint32_t NumberOfProcessors;           
    uint32_t NtGlobalFlag;                 
    uint64_t CriticalSectionTimeout;       
    uint64_t HeapSegmentReserve;           
    uint64_t HeapSegmentCommit;            
    uint64_t HeapDeCommitTotalFreeThreshold; 
    uint64_t HeapDeCommitFreeBlockThreshold; 
    uint32_t NumberOfHeaps;                
    uint32_t MaximumNumberOfHeaps;         
    uint64_t ProcessHeaps;                 
    uint64_t GdiSharedHandleTable;         
    uint64_t ProcessStarterHelper;         
    uint32_t GdiDCAttributeList;           
    uint8_t  Padding2[4];                  
    uint64_t LoaderLock;                   
    uint32_t OSMajorVersion;               
    uint32_t OSMinorVersion;               
    uint16_t OSBuildNumber;                
    uint16_t OSCSDVersion;                 
    uint32_t OSPlatformId;                 
    uint32_t ImageSubsystem;               
    uint32_t ImageSubsystemMajorVersion;   
    uint32_t ImageSubsystemMinorVersion;   
    uint64_t ActiveProcessAffinityMask;    
    uint64_t GdiHandleBuffer[60];          
    uint64_t PostProcessInitRoutine;       
    uint64_t TlsExpansionBitmap;           
    uint32_t TlsExpansionBitmapBits[32];   
    uint64_t SessionId;                    
    uint64_t AppCompatFlags;               
    uint64_t AppCompatFlagsUser;           
    uint64_t ShimData;                     
    uint64_t AppCompatInfo;                
    uint64_t CSDVersion;                   
    uint64_t ActivationContextData;        
    uint64_t ProcessAssemblyStorageMap;    
    uint64_t SystemDefaultActivationContextData; 
    uint64_t SystemAssemblyStorageMap;     
    uint64_t MinimumStackCommit;           
    uint64_t SparePointers[4];             
    uint32_t SpareUlongs[5];               
    uint64_t WerRegistrationData;          
    uint64_t WerShipAssertPtr;             
    uint64_t pUnused;                      
    uint64_t pImageHeaderHash;             
    uint64_t TracingFlags;                 
    uint8_t  Padding3[8];                  
} WIN_PEB, *PWIN_PEB;


#ifdef __cplusplus
}
#endif
#endif