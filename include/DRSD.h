#ifndef _DRSD_H
#define _DRSD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdlib.h>
#include <Modulation.h>

typedef struct _DRSD_DEVICE_INFO_FLAGS{
    union{
        struct{
            UINT    GuarenteedDmaBufferContract     :   1;
            UINT    Reserved                        :   31;
        };
        UINT        Value;
    };  
}DRSD_DEVICE_INFO_FLAGS, * PDRSD_DEVICE_INFO_FLAGS;

typedef struct _DRSD_DEVICE_INFO{
    UINT                    DmaBufferSize;
    UINT                    DmaBufferSegmentSet;
    UINT                    DmaBufferPRivateDataSize;
    UINT                    AllocationListSize;
    UINT                    PatchLocationListSize;
    DRSD_DEVICE_INFO_FLAGS  Flags;
}DRSD_DEVICE_INFO, * PDRSD_DEVICE_INFO;

typedef struct _DRSD_CREATE_DEVICE_FLAGS{
    union{
        struct{
            UINT    SystemDevice    :   1;
            UINT    GdiDevice       :   1;
            UINT    Reserved        :   29;
            UINT    DevReserve      :   1;
        };
        UINT        Value;
    };
}DRSD_CREATE_DEVICE_FLAGS, * PDRSD_CREATE_DEVICE_FLAGS;

typedef struct _DRSD_ARG_CREATE_DEVICE{
    HANDLE                          Device;
    union{
        DRSD_CREATE_DEVICE_FLAGS    Flags;
        PDRSD_DEVICE_INFO           DeviceInfo;
    };
    ULONG                           Pasid;
    HANDLE                          KmdProcess;
}DRSD_ARG_CREATE_DEVICE, * PDRSD_ARG_CREATE_DEVICE;

#ifndef _USER_MODE_CODE_
#ifndef _DRSD_MAIN_INTERNALS
DRIVER_IMPORT LOUSTATUS DrsdCreateDevice(const HANDLE Adapter, PDRSD_ARG_CREATE_DEVICE CreateDevice);
#else
DRIVER_EXPORT LOUSTATUS DrsdCreateDevice(const HANDLE Adapter, PDRSD_ARG_CREATE_DEVICE CreateDevice);
#endif
#else //USER MODE CODE

#endif

#ifdef __cplusplus
}
#endif
#endif