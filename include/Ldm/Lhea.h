#ifndef _LHEA_H
#define _LHEA_H

typedef enum _LHEA_ERROR_SOURCE_TYPE{
    LheaErrSrcTypeMCE = 0,
    LheaErrSrcTypeCMC,
    LheaErrSrcTypeCPE,
    LheaErrSrcTypeNMI,
    LheaErrSrcTypePCIe,
    LheaErrSrcTypeGeneric,
    LheaErrSrcTypeINIT,
    LheaErrSrcTypeBOOT,
    LheaErrSrcTypeSCIGeneric,
    LheaErrSrcTypeIPFMCA,
    LheaErrSrcTypeIPFCMC,
    LheaErrSrcTypeIPFCPE,
    LheaErrSrcTypeGenericV2,
    LheaErrSrcTypeSCIGenericV2,
    LheaErrSrcTypeBMC,
    LheaErrSrcTypePMEM,
    LheaErrSrcTypeDeviceDriver,
    LheaErrSrcTypeSea,
    LheaErrSrcTypeSei,
    LheaErrSrcTypeMax,
}LHEA_ERROR_SOURCE_TYPE, * PLHEA_ERROR_SOURCE_TYPE;

typedef enum _LHEA_EVENT_LOG_ENTRY_ID{
    LheaEventLogEntryIdCmcPollingTimeout = 0,
    LheaEventLogEntryIdLheaInit,
    LheaEventLogEntryIdCmcSwitchToPolling,
    LheaEventLogEntryIdDroppedCorrectedError,
    LheaEventLogEntryIdStartedReportHwError,
    LheaEventLogEntryIdPFAMemoryOfflined,
    LheaEventLogEntryIdPFAMemoryRemoveMonitor,
    LheaEventLogEntryIdPFAMemoryPolicy,
    LheaEventLogEntryIdPshedInjectError,
    LheaEventLogEntryIdOscCapabilities,
    LheaEventLogEntryIdPshedPluginRegister,
    LheaEventLogEntryIdAddRemoveErrorSource,
    LheaEventLogEntryIdWorkQueueItem,
    LheaEventLogEntryIdAttemptErrorRecovery,
    LheaEventLogEntryIdMcaFoundErrorInBank,
    LheaEventLogEntryIdMcaStuckErrorCheck,
    LheaEventLogEntryIdMcaErrorCleared,
    LheaEventLogEntryIdClearedPoison,
    LheaEventLogEntryIdProcessEINJ,
    LheaEventLogEntryIdProcessHEST,
    LheaEventLogEntryIdCreateGenericRecord,
    LheaEventLogEntryIdErrorRecord,
    LheaEventLogEntryIdErrorRecordLimit,
    LheaEventLogEntryIdAerNotGrantedToOs,
    LheaEventLogEntryIdErrSrcArrayInvalid,
    LheaEventLogEntryIdAcpiTimeOut,
    LheaEventLogCmciRestart,
    LheaEventLogCmciFinalRestart,
    LheaEventLogEntryEtwOverFlow,
    LheaEventLogAzccRootBusSearchErr,
    LheaEventLogAzccRootBusList,
    LheaEventLogEntryIdErrSrcInvalid,
    LheaEventLogEntryIdGenericErrMemMap,
    LheaEventLogEntryIdPshedCallbackCollision,
    LheaEventLogEntryIdSELBugCheckProgress,
    LheaEventLogEntryIdPshedPluginLoad,
    LheaEventLogEntryIdPshedPluginUnload,
    LheaEventLogEntryIdPshedPluginSupported,
    LheaEventLogEntryIdDeviceDriver,
    LheaEventLogEntryIdCmciImplPresent,
    LheaEventLogEntryIdCmciInitError,
    LheaEventLogEntryIdSELBugCheckRecovery,
    LheaEventLogEntryIdDrvErrSrcInvalid,
    LheaEventLogEntryIdDrvHandleBusy,
    LheaEventLogEntryIdWheaHeartbeat,
    LheaEventLogAzccRootBusPoisonSet,
    LheaEventLogEntryIdSELBugCheckInfo,
    LheaEventLogEntryIdErrDimmInfoMismatch,
    LheaEventLogEntryIdeDpcEnabled,
    LheaEventLogEntryPageOfflineDone,
    LheaEventLogEntryPageOfflinePendMax,
    LheaEventLogEntryIdBadPageLimitReached,
    LheaEventLogEntrySrarDetail,
    LheaEventLogEntryEarlyError,
    LheaEventLogEntryIdPcieOverrideInfo,
    LheaEventLogEntryIdReadPcieOverridesErr,
    LheaEventLogEntryIdPcieConfigInfo,
    LheaEventLogEntryIdPcieSummaryFailed,
    LheaEventLogEntryIdThrottleRegCorrupt,
    LheaEventLogEntryIdThrottleAddErrSrcFailed,
    LheaEventLogEntryIdThrottleRegDataIgnored,
    LheaEventLogEntryIdEnableKeyNotifFailed,
    LheaEventLogEntryIdKeyNotificationFailed,
    LheaEventLogEntryIdPcieRemoveDevice,
    LheaEventLogEntryIdPcieAddDevice,
    LheaEventLogEntryIdPcieSpuriousErrSource,
    LheaEventLogEntryIdMemoryAddDevice,
    LheaEventLogEntryIdMemoryRemoveDevice,
    LheaEventLogEntryIdMemorySummaryFailed,
    LheaEventLogEntryIdPcieDpcError,
    LheaEventLogEntryIdCpuBusesInitFailed,
    LheaEventLogEntryIdPshedPluginInitFailed,
    LheaEventLogEntryIdFailedAddToDefectList,
    LheaEventLogEntryIdDefectListFull,
    LheaEventLogEntryIdDefectListUEFIVarFailed,
    LheaEventLogEntryIdDefectListCorrupt,
    LheaEventLogEntryIdBadHestNotifyData,
    LheaEventLogEntryIdRowFailure,
    LheaEventLogEntryIdSrasTableNotFound,
    LheaEventLogEntryIdSrasTableError,
    LheaEventLogEntryIdSrasTableEntries,
    LheaEventLogEntryIdPFANotifyCallbackAction,
    LheaEventLogEntryIdSELBugCheckCpusQuiesced,
    LheaEventLogEntryIdPshedPiCpuid,
    LheaEventLogEntryIdSrasTableBadData,
    LheaEventLogEntryIdDriFsStatus,
    LheaEventLogEntryIdCpusFrozen,
    LheaEventLogEntryIdCpusFrozenNoCrashDump,
    LheaEventLogEntryIdRegNotifyPolicyChange,
    LheaEventLogEntryIdRegError,
    LheaEventLogEntryIdRowOfflineEvent,
    LheaEventLogEntryIdBitOfflineEvent,
    LheaEventLogEntryIdBadGasFields,
    LheaEventLogEntryIdCrashDumpError,
    LheaEventLogEntryIdCrashDumpCheckpoint,
    LheaEventLogEntryIdCrashDumpProgressPercent,
    LheaEventLogEntryIdPreviousCrashBugCheckProgress,
    LheaEventLogEntryIdSELBugCheckStackDump,
    LheaEventLogEntryIdPciePromotedAerErr,
    LheaEventLogEntryIdPshedPiTraceLog,
}LHEA_EVENT_LOG_ENTRY_ID, * PLHEA_EVENT_LOG_ENTRY_ID;

typedef enum _LHEA_ERROR_SEVERITY{
    LheaErrSevRecoverable = 0,
    LheaErrSevFatal,
    LheaErrSevCorrected,
    LheaErrSevInformational
}LHEA_ERROR_SEVERITY, * PLHEA_ERROR_SEVERITY;

typedef union _LHEA_EVENT_LOG_ENTRY_FLAGS{
  struct{
    ULONG   Reserved1         : 1;
    ULONG   LogInternalEtw    : 1;
    ULONG   LogBlackbox       : 1;
    ULONG   LogSel            : 1;
    ULONG   RawSel            : 1;
    ULONG   NoFormat          : 1;
    ULONG   Driver            : 1;
    ULONG   Reserved2         : 25;
  };
  ULONG     AsULONG;
}LHEA_EVENT_LOG_ENTRY_FLAGS, * PLHEA_EVENT_LOG_ENTRY_FLAGS;


typedef struct _LHEA_EVENT_LOG_ENTRY_HEADER{
  ULONG                         Signature;
  ULONG                         Version;
  ULONG                         Length;
  LHEA_EVENT_LOG_ENTRY_ID       LogEntryId;
  LHEA_ERROR_SEVERITY           Severity;
  ULONG                         SequenceNumber;
  LHEA_EVENT_LOG_ENTRY_FLAGS    Flags;
  ULONG                         Reserved;
}LHEA_EVENT_LOG_ENTRY_HEADER, * PLHEA_EVENT_LOG_ENTRY_HEADER;

typedef struct _LHEA_EVENT_LOG_ENTRY{
    LHEA_EVENT_LOG_ENTRY_HEADER     LheaHeader;
}LHEA_EVENT_LOG_ENTRY, * PLHEA_EVENT_LOG_ENTRY;;

typedef union _LHEA_REVISION{
    struct {
        USHORT      MinorRevision : 8;
        USHORT      MajorRevision : 8;
    };
    USHORT          AsUSHORT;
}LHEA_REVISION, * PLHEA_REVISION;

typedef struct _LHEA_ERROR_RECORD_HEADER_VALID_BITS{
    struct{
        ULONG   PlatforId   : 1;
        ULONG   TimeStamp   : 1;
        ULONG   PartitionId : 1;
        ULONG   Reserved    : 29;
    };
    ULONG       AsULONG;
}LHEA_ERROR_RECORD_HEADER_VALID_BITS, * PLHEA_ERROR_RECORD_HEADER_VALID_BITS;

typedef ULONGLONG LHEA_TIMESTAMP, * PLHEA_TIMESTAMP;
typedef ULONG LHEA_ERROR_RECORD_HEADER_FLAGS, * PLHEA_ERROR_RECORD_HEADER_FLAGS;

typedef union _LHEA_PERSISTENCE_INFO{
    struct{
        ULONGLONG   Identifier  : 16;
        ULONGLONG   Length      : 24;
        ULONGLONG   Persistence : 1;
        ULONGLONG   Reserved    : 23;
    };
    ULONGLONG       AsULONGLONG;
}LHEA_PERSISTENCE_INFO, * PLHEA_PERSISTENCE_INFO;

typedef struct _LHEA_ERROR_RECORD_HEADER{
    ULONG                                   Signature;
    LHEA_REVISION                           Revision;
    ULONG                                   SignatureEnd;
    USHORT                                  SectionCount;
    LHEA_ERROR_SEVERITY                     Severity;
    LHEA_ERROR_RECORD_HEADER_VALID_BITS     ValidBits;
    ULONG                                   Length;
    LHEA_TIMESTAMP                          TimeStamp;
    GUID                                    PlatforId;
    GUID                                    PartitionId;
    GUID                                    CreatorId;
    GUID                                    NotifyType;
    ULONGLONG                               RecordId;
    LHEA_ERROR_RECORD_HEADER_FLAGS          Flags;
    union{
        struct{
            ULONG                           OsBuildNumber;
            UCHAR                           Reserved2[8];
        };
        UCHAR                               Reserved[12];
    };
}LHEA_ERROR_RECORD_HEADER, * PLHEA_ERROR_RECORD_HEADER;

typedef union _LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS{
    struct{
        ULONG   SectionOffset   : 1;
        ULONG   SectionLength   : 1;
        ULONG   Revision        : 1;
        ULONG   ValidBits       : 1;
        ULONG   Reserved        : 28;
    };
    ULONG       AsULONG;
}LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS, * PLHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS;

typedef struct _LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS{
    struct{
        ULONG   PlatformErrorDeviceSupported    : 1;
        ULONG   DataValid                       : 1;
        ULONG   ResourceNotAvailable            : 1;
        ULONG   LatentError                     : 1;
        ULONG   Reserved                        : 28;
    };  
    ULONG       AsULONG;
}LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS, * PLHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS;

typedef struct _LHEA_ERROR_RECORD_SECTION_DESCRIPTOR{
    ULONG                                           SectionOffset;
    ULONG                                           SectionLength;
    LHEA_REVISION                                   Revision;
    LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS  ValidBits;
    UCHAR                                           Reserved;
    LHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS      Flags;
    GUID                                            SectionType;
    GUID                                            FRUId;
    LHEA_ERROR_SEVERITY                             SectionSeverity;
    CCHAR                                           FRUText[20];
}LHEA_ERROR_RECORD_SECTION_DESCRIPTOR, * PLHEA_ERROR_RECORD_SECTION_DESCRIPTOR;

typedef struct _LHEA_ERROR_RECORD{
    LHEA_ERROR_RECORD_HEADER                LheaHeader;
    LHEA_ERROR_RECORD_SECTION_DESCRIPTOR    SectionDescriptor[1];
}LHEA_ERROR_RECORD, * PLHEA_ERROR_RECORD;

typedef enum _LHEA_ERROR_TYPE{
    LheaErrTypeProcessor = 0,
    LheaErrTypeMemory,
    LheaErrTypePCIExpress,
    LheaErrTypeNMI,
    LheaErrTypePCIXBus,
    LheaErrTypePCIXDevice,
    LheaErrTypeGeneric,
    LheaErrTypePmem
}LHEA_ERROR_TYPE, * LWHEA_ERROR_TYPE;

typedef enum _LHEA_RAW_DATA_FORMAT {
    LheaRawDataFormatInvalid,
    LheaRawDataFormatGeneric,
    LheaRawDataFormatIPFSalRecord,
    LheaRawDataFormatIntel64MCA,
    LheaRawDataFormatAMD64MCA,
    LheaRawDataFormatMemory,
    LheaRawDataFormatPCIExpress,
    LheaRawDataFormatNMIPort,
    LheaRawDataFormatPCIXBus,
    LheaRawDataFormatPCIXDevice,
    LheaRawDataFormatMax
}LHEA_RAW_DATA_FORMAT, * LWHEA_RAW_DATA_FORMAT;


typedef struct _LHEA_ERROR_PACKET_V2{
    GUID                    Signature;
    ULONG                   Flags;
    LHEA_ERROR_TYPE         ErrorType;
    LHEA_ERROR_SEVERITY     ErrorSeverity;
    ULONG                   ErrorSourceId;
    LHEA_ERROR_SOURCE_TYPE  ErrorSourceType;
    GUID                    NotifyType;
    ULONG                   Context;
    LHEA_RAW_DATA_FORMAT    DataFormat;
    ULONG                   DataOffset;
    ULONG                   DataLength;
    ULONG                   PshedDataOffset;
    ULONG                   PshedDataLength;
}LHEA_ERROR_PACKET_V2, * PLHEA_ERROR_PACKET_V2;

typedef union _LHEA_NOTIFICATION_FLAGS{
    struct{
        USHORT  PollIntervalRW              :   1;
        USHORT  SwitchToPollingThresholdRW  :   1;
        USHORT  SwitchToPollingWindowRW     :   1;
        USHORT  ErrorThresholdRW            :   1;
        USHORT  ErrorThresholdWindowRW      :   1;
        USHORT  Reserved                    :   11;
    };
    USHORT      AsUSHORT;
}LHEA_NOTIFICATION_FLAGS, * PLHEA_NOTIFICATION_FLAGS;

typedef struct _LHEA_NOTIFICATION_DESCRIPTOR{
    UCHAR                       Type;
    UCHAR                       Length;
    LHEA_NOTIFICATION_FLAGS     Flags;
    union{
        struct{
            ULONG               PollInterval;
        }Polled;
        struct{
            ULONG               PollInterval;
            ULONG               Vector;
            ULONG               SwitchToPollingThreshold;
            ULONG               SwitchToPollingWindow;
            ULONG               ErrorThreshold;
            ULONG               ErrorThresholdWindow;
        }Interrupt;
        struct{
            ULONG               PollInterval;
            ULONG               Vector;
            ULONG               SwitchToPollingThreshold;
            ULONG               SwitchToPollingWindow;
            ULONG               ErrorThreshold;
            ULONG               ErrorThresholdWindow;
        }LocalInterrupt;
        struct{
            ULONG               PollInterval;
            ULONG               Vector;
            ULONG               SwitchToPollingThreshold;
            ULONG               SwitchToPollingWindow;
            ULONG               ErrorThreshold;
            ULONG               ErrorThresholdWindow;
        }Sci;
        struct{
            ULONG               PollInterval;
            ULONG               Vector;
            ULONG               SwitchToPollingThreshold;
            ULONG               SwitchToPollingWindow;
            ULONG               ErrorThreshold;
            ULONG               ErrorThresholdWindow;
        }Nmi;
        struct{
            ULONG               PollInterval;
            ULONG               Vector;
            ULONG               SwitchToPollingThreshold;
            ULONG               SwitchToPollingWindow;
            ULONG               ErrorThreshold;
            ULONG               ErrorThresholdWindow;
        }Sea;
        struct{
            ULONG               PollInterval;
            ULONG               Vector;
            ULONG               SwitchToPollingThreshold;
            ULONG               SwitchToPollingWindow;
            ULONG               ErrorThreshold;
            ULONG               ErrorThresholdWindow;
        }Sei;
        struct{
            ULONG               PollInterval;
            ULONG               Vector;
            ULONG               SwitchToPollingThreshold;
            ULONG               SwitchToPollingWindow;
            ULONG               ErrorThreshold;
            ULONG               ErrorThresholdWindow;
        }Gsiv;
    };
}LHEA_NOTIFICATION_DESCRIPTOR, * PLHEA_NOTIFICATION_DESCRIPTOR;

typedef enum _LHEAP_DPC_ERROR_EVENT_TYPE{
    LheapDpcErrNoErr = 0,
    LheapDpcErrBusNotFound,
    LheapDpcErrDpcedSubtree,
    LheapDpcErrDeviceIdBad,
    LheapDpcErrResetFailed,
    LheapDpcErrNoChildren
}LHEAP_DPC_ERROR_EVENT_TYPE, * PLHEAP_DPC_ERROR_EVENT_TYPE;

typedef enum _LHEA_ERROR_SOURCE_STATE{
    LheaErrSrcStateStarted = 0,
    LheaErrSrcStateStopped
}LHEA_ERROR_SOURCE_STATE, * PLHEA_ERROR_SOURCE_STATE;

typedef union _XPF_MCE_FLAGS{
  struct {
    ULONG  MCG_CapabilityRW     :   1;
    ULONG  MCG_GlobalControlRW  :   1;
    ULONG  Reserved             :   30;
  };
  ULONG    AsULONG;
}XPF_MCE_FLAGS, * PXPF_MCE_FLAGS;

typedef union _XPF_MC_BANK_FLAGS{
    struct{
        UCHAR   ClearOnInitializationRW :   1;
        UCHAR   ControlDataRW           :   1;
        UCHAR   Reserved                :   6;
    };
    UCHAR       AsUCHAR;
}XPF_MC_BANK_FLAGS, * PXPF_MC_BANK_FLAGS;

typedef union _XPF_CMC_FLAGS{
    struct{
        ULONG   Reserved  : 31;
        ULONG   Condition : 1;
    };
    ULONG       AsULONG;
}XPF_CMC_FLAGS, * PXPF_CMC_FLAGS;

typedef struct _LHEA_XPF_MC_BANK_DESCRIPTOR{
    UCHAR               BankNumber;
    BOOLEAN             ClearOnInitialization;
    UCHAR               StatusDataFormat;
    XPF_MC_BANK_FLAGS   Flags;
    ULONG               ControlMsr;
    ULONG               StatusMsr;
    ULONG               MiscMsr;
    ULONGLONG           ControlData;
}LHEA_XPF_MC_BANK_DESCRIPTOR, * PLHEA_XPF_MC_BANK_DESCRIPTOR;

typedef struct _LHEA_XPF_MCE_DESCRIPTOR{
    USHORT                          Type;
    UCHAR                           Enabled;
    UCHAR                           NumberOfBanks;
    XPF_MCE_FLAGS                   Flags;
    ULONGLONG                       MCG_Capability;
    ULONGLONG                       MCG_GlobalControl;
    LHEA_XPF_MC_BANK_DESCRIPTOR     Banks[1];
}LHEA_XPF_MCE_DESCRIPTOR, * PLHEA_XPF_MCE_DESCRIPTOR;

typedef struct _LHEA_XPF_CMC_DESCRIPTOR{
    USHORT                          Type;
    UCHAR                           Enabled;
    UCHAR                           Reserved;
    UCHAR                           NumberOfBanks;
    XPF_CMC_FLAGS                   Flags;
    ULONG                           ErrorThreshold;
    ULONG                           ErrorThresholdWindow;
    LHEA_XPF_MC_BANK_DESCRIPTOR     Banks[1];
}LHEA_XPF_CMC_DESCRIPTOR, * PLHEA_XPF_CMC_DESCRIPTOR;

typedef struct _LHEA_XPF_NMI_DESCRIPTOR{
    USHORT      Reserved;
    UCHAR       ProcessorId;
    UCHAR       Mask;
}LHEA_XPF_NMI_DESCRIPTOR, * PLHEA_XPF_NMI_DESCRIPTOR;

typedef struct _LHEA_IPF_MCA_DESCRIPTOR{
    USHORT      Type;
    UCHAR       Enabled;
    UCHAR       Reserved;
}LHEA_IPF_MCA_DESCRIPTOR, * PLHEA_IPF_MCA_DESCRIPTOR;

typedef struct _LHEA_IPF_CMC_DESCRIPTOR{
    USHORT      Type;
    UCHAR       Enabled;
    UCHAR       Reserved;
}LHEA_IPF_CMC_DESCRIPTOR, * PLHEA_IPF_CMC_DESCRIPTOR;

typedef struct _LHEA_IPF_CPE_DESCRIPTOR{
    USHORT      Type;
    UCHAR       Enabled;
    UCHAR       Reserved;
}LHEA_IPF_CPE_DESCRIPTOR, * PLHEA_IPF_CPE_DESCRIPTOR;

typedef union _LHEA_PCI_SLOT_NUMBER{
    struct{
        ULONG   DeviceNumber    :   5;
        ULONG   FunctionNumber  :   3;
        ULONG   Reserved        :   24;
    };  
    ULONG       AsULONG;
}LHEA_PCI_SLOT_NUMBER, * PLHEA_PCI_SLOT_NUMBER;

typedef struct _LHEA_AER_ROOTPORT_DESCRIPTOR{
    USHORT                  Type;
    UCHAR                   Enabled;
    UCHAR                   Reserved;
    ULONG                   BusNumber;
    LHEA_PCI_SLOT_NUMBER    BridgeSlotNumber;
    USHORT                  DeviceControl;
    USHORT                  RootControl;
    ULONG                   RootPortControl;
    ULONG                   MaxRawDataLength;
}LHEA_AER_ROOTPORT_DESCRIPTOR, * PLHEA_AER_ROOTPORT_DESCRIPTOR;

typedef union _AER_ENDPOINT_DESCRIPTOR_FLAGS{
    struct {
        USHORT  UncorrectableErrorMasked        :   1;
        USHORT  UncorrectableErrorSeverity      :   1;
        USHORT  CorrectableErrorMasked          :   1;
        USHORT  AdvancedErrorReportingSupported :   1;
        USHORT  Reserved                        :   12;
    };
    USHORT      AsUSHORT;
}AER_ENDPOINT_DESCRIPTOR_FLAGS, * PAER_ENDPOINT_DESCRIPTOR_FLAGS;

typedef struct _LHEA_AER_ENDPOINT_DESCRIPTOR{
    USHORT                          Type;
    UCHAR                           Enabled;
    UCHAR                           Reserved;
    ULONG                           MaxErrSvc;
    LHEA_PCI_SLOT_NUMBER            DescriptorSlotNumber;
    AER_ENDPOINT_DESCRIPTOR_FLAGS   Flags;
    ULONG                           UncorrectableErrorMaskedRW;
    ULONG                           UncorrectableErrorSeverityRW;
    ULONG                           CorrectableErrorMaskedRW;
    ULONG                           AdvancedCapsAndCtrlRW;
    ULONG                           PcieSvcMask;
}LHEA_AER_ENDPOINT_DESCRIPTOR, * PLHEA_AER_ENDPOINT_DESCRIPTOR;


typedef union _AER_BRIDGE_DESCRIPTOR_FLAGS{
    struct{
        USHORT  UncorrectableErrorMaskedRW              :   1;
        USHORT  UncorrectableErrorSeverityRW            :   1;
        USHORT  CorrectableErrorMaskedRW                :   1;
        USHORT  CorrectableErrorSeverityRW              :   1;
        USHORT  AdvancedCapsAndCtrlRW                   :   1;
        USHORT  SecondaryUncorrectableErrorMaskedRW     :   1;
        USHORT  SecondaryUncorrectableErrorSeverityRW   :   1;
        USHORT  SecondaryAdvancedCapsAndCtrlRW          :   1;
        USHORT  Reserved                                :   8;
    };
    USHORT      AsUSHORT;
}AER_BRIDGE_DESCRIPTOR_FLAGS, * PAER_BRIDGE_DESCRIPTOR_FLAGS;

typedef struct _LHEA_AER_BRIDGE_DESCRIPTOR{
    USHORT                          Type;
    BOOLEAN                         Enabled;
    UCHAR                           Reserved;
    ULONG                           BusNumber;
    LHEA_PCI_SLOT_NUMBER            Slot;
    USHORT                          DeviceControl;
    AER_BRIDGE_DESCRIPTOR_FLAGS     Flags;
    ULONG                           UncorrectableErrorMask;
    ULONG                           UncorrectableErrorSeverity;
    ULONG                           CorrectableErrorMask;
    ULONG                           AdvancedCapsAndControl;
    ULONG                           SecondaryUncorrectableErrorMask;
    ULONG                           SecondaryUncorrectableErrorSev;
    ULONG                           SecondaryCapsAndControl;
}LHEA_AER_BRIDGE_DESCRIPTOR, * PLHEA_AER_BRIDGE_DESCRIPTOR;

typedef PHYSICAL_ADDRESS LHEA_PHYSICAL_ADDRESS;

//always allocate this as Version 2
typedef struct _LHEA_GENERIC_ERROR_DESCRIPTOR{
    USHORT                          Type;
    UCHAR                           Reserved;
    UCHAR                           Enabled;
    ULONG                           ErrStatusBlockLength;
    ULONG                           RelatedErrorSourceId;
    UCHAR                           ErrStatusAddressSpaceId;
    UCHAR                           ErrStatusAddressBitWidth;
    UCHAR                           ErrStatusAddressBitOffset;
    UCHAR                           ErrStatusAddressAccessSize;
    LHEA_PHYSICAL_ADDRESS           ErrorStatusAddress;
    LHEA_NOTIFICATION_DESCRIPTOR    Notify;
}LHEA_GENERIC_ERROR_DESCRIPTOR, * PLHEA_GENERIC_ERROR_DESCRIPTOR;

typedef struct _LHEA_GENERIC_ERROR_DESCRIPTOR_V2{
    USHORT                          Type;
    UCHAR                           Reserved;
    UCHAR                           Enabled;
    ULONG                           ErrStatusBlockLength;
    ULONG                           RelatedErrorSourceId;
    UCHAR                           ErrStatusAddressSpaceId;
    UCHAR                           ErrStatusAddressBitWidth;
    UCHAR                           ErrStatusAddressBitOffset;
    UCHAR                           ErrStatusAddressAccessSize;
    LHEA_PHYSICAL_ADDRESS           ErrorStatusAddress;
    LHEA_NOTIFICATION_DESCRIPTOR    Notify;
    UCHAR                           ReadAckAddressSpaceId;
    UCHAR                           ReadAckAddressBitWidth;
    UCHAR                           ReadAckAddressBitOffset;
    UCHAR                           ReadAckAddressAccessSize;
    LHEA_PHYSICAL_ADDRESS           ReadAckAddress;
    ULONGLONG                       ReadAckPreservedMask;
    ULONGLONG                       ReadAckWriteMask;
}LHEA_GENERIC_ERROR_DESCRIPTOR_V2, * PLHEA_GENERIC_ERROR_DESCRIPTOR_V2;

typedef 
LOUSTATUS
LHEA_ERROR_SOURCE_INITIALIZE_DEVICE_DRIVER(
    PVOID Context,
    ULONG ErrorSourceId
);
typedef LHEA_ERROR_SOURCE_INITIALIZE_DEVICE_DRIVER* PLHEA_ERROR_SOURCE_INITIALIZE_DEVICE_DRIVER;

typedef 
void 
LHEA_ERROR_SOURCE_UNINITIALIZE_DEVICE_DRIVER(
    PVOID Context
);
typedef LHEA_ERROR_SOURCE_UNINITIALIZE_DEVICE_DRIVER* PLHEA_ERROR_SOURCE_UNINITIALIZE_DEVICE_DRIVER;

typedef 
LOUSTATUS
LHEA_ERROR_SOURCE_CORRECT_DEVICE_DRIVER(
    PVOID       ErrorSourceDescriptor,
    PULONG      MaxSectionLength
);
typedef LHEA_ERROR_SOURCE_CORRECT_DEVICE_DRIVER* PLHEA_ERROR_SOURCE_CORRECT_DEVICE_DRIVER;

typedef struct _LHEA_ERROR_SOURCE_CONFIGURATION_DD{
    PLHEA_ERROR_SOURCE_INITIALIZE_DEVICE_DRIVER     Initialize;
    PLHEA_ERROR_SOURCE_UNINITIALIZE_DEVICE_DRIVER   Uninitialize;
    PLHEA_ERROR_SOURCE_CORRECT_DEVICE_DRIVER        Correct;
}LHEA_ERROR_SOURCE_CONFIGURATION_DD, * PLHEA_ERROR_SOURCE_CONFIGURATION_DD;

typedef struct _LHEA_DEVICE_DRIVER_DESCRIPTOR{
    USHORT                              Type;
    BOOLEAN                             Enabled;
    UCHAR                               Reserved;
    GUID                                SourceGuid;
    USHORT                              LogTag;
    USHORT                              Reserved2;
    ULONG                               PacketLength;
    ULONG                               PacketCount;
    PUCHAR                              PacketBuffer;
    LHEA_ERROR_SOURCE_CONFIGURATION_DD  Config;
    GUID                                CreatorId;
    GUID                                PartitionId;
    ULONG                               MaxSectionDataLength;
    ULONG                               MaxSectionsPerRecord;
    PUCHAR                              PacketStateBuffer;
    LONG                                OpenHandles;
}LHEA_DEVICE_DRIVER_DESCRIPTOR, * PLHEA_DEVICE_DRIVER_DESCRIPTOR;

typedef struct _LHEA_ERROR_SOURCE_DESCRIPTOR{
    ULONG                                   Length;
    ULONG                                   Version;
    LHEA_ERROR_SOURCE_TYPE                  Type;
    LHEA_ERROR_SOURCE_STATE                 State;
    ULONG                                   MaxRawDataLength;
    ULONG                                   NumRecordToPreallocate;
    ULONG                                   MaxSectionsPerRecord;
    ULONG                                   ErrorSourceId;
    ULONG                                   PlatformErrorSourceId;
    ULONG                                   Flags;
    union{          
        LHEA_XPF_MCE_DESCRIPTOR             XpfMceDescriptor;
        LHEA_XPF_CMC_DESCRIPTOR             XpfCmcDescriptor;
        LHEA_XPF_NMI_DESCRIPTOR             XpfNmiDescriptor;
        LHEA_IPF_MCA_DESCRIPTOR             IpfMcaDescriptor;
        LHEA_IPF_CMC_DESCRIPTOR             IpfCmcDescriptor;
        LHEA_IPF_CPE_DESCRIPTOR             IpfCpeDescriptor;
        LHEA_AER_ROOTPORT_DESCRIPTOR        AerRootportDescriptor;
        LHEA_AER_ENDPOINT_DESCRIPTOR        AerEndpointDescriptor;
        LHEA_AER_BRIDGE_DESCRIPTOR          AerBrigeDescriptor;
        LHEA_GENERIC_ERROR_DESCRIPTOR       GenErrDescriptor;
        LHEA_GENERIC_ERROR_DESCRIPTOR_V2    GenErrDescriptorV2;
        LHEA_DEVICE_DRIVER_DESCRIPTOR       DeviceDriverDescriptor;
    }Info;
}LHEA_ERROR_SOURCE_DESCRIPTOR, * PLHEA_ERROR_SOURCE_DESCRIPTOR;

typedef 
LOUSTATUS
LHEA_ERROR_SOURCE_CORRECT(
    PVOID                   PluginContext,
    ULONG                   ErrorSourceId,
    LHEA_ERROR_SOURCE_STATE State
);
typedef LHEA_ERROR_SOURCE_CORRECT* PLHEA_ERROR_SOURCE_CORRECT;

typedef 
LOUSTATUS 
LHEA_ERROR_SOURCE_INITIALIZE(
    ULONG                           Phase,
    PLHEA_ERROR_SOURCE_DESCRIPTOR   Descriptor,
    PVOID                           Context
);
typedef LHEA_ERROR_SOURCE_INITIALIZE* PLHEA_ERROR_SOURCE_INITIALIZE;

typedef 
LOUSTATUS 
LHEA_ERROR_SOURCE_CREATE_RECORD(
    ...
);
typedef LHEA_ERROR_SOURCE_CREATE_RECORD* PLHEA_ERROR_SOURCE_CREATE_RECORD;

typedef 
LOUSTATUS 
LHEA_ERROR_SOURCE_RECOVER(
    ...
);
typedef LHEA_ERROR_SOURCE_RECOVER* PLHEA_ERROR_SOURCE_RECOVER;

typedef 
LOUSTATUS 
LHEA_ERROR_SOURCE_UNINITIALIZE(
    PVOID Context,
    ULONG SectionIndex
);
typedef LHEA_ERROR_SOURCE_UNINITIALIZE* PLHEA_ERROR_SOURCE_UNINITIALIZE;

typedef struct _LHEA_ERROR_SOURCE_CONFIGURATION{
    ULONG                               Flags;
    PLHEA_ERROR_SOURCE_CORRECT          Correct;
    PLHEA_ERROR_SOURCE_INITIALIZE       Initialize;
    PLHEA_ERROR_SOURCE_CREATE_RECORD    CreateRecord;
    PLHEA_ERROR_SOURCE_RECOVER          Recover;
    PLHEA_ERROR_SOURCE_UNINITIALIZE     Uninitialize;
    PVOID                               Reserved;
}LHEA_ERROR_SOURCE_CONFIGURATION, * PLHEA_ERROR_SOURCE_CONFIGURATION;

typedef 
BOOLEAN
LHEA_SIGNAL_HANDLER_OVERRIDE_CALLBACK(
    PVOID   Context
);
typedef LHEA_SIGNAL_HANDLER_OVERRIDE_CALLBACK *PLHEA_SIGNAL_HANDLER_OVERRIDE_CALLBACK;





#endif
