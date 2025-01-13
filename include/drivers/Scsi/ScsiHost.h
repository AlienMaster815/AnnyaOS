#ifndef _SCSI_HOST_H
#define _SCSI_HOST_H

#ifndef _CSTDINT_H
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#endif

#include "../ScatterList.h"

#include "FibreChannel/FibreChannelFrame.h"
#include "CxlFlashIoCtl.h"
#include "ScsiBsgFibreChannel.h"
#include "ScsiBsgUfs.h"
#include "ScsiFibreChannelNetlink.h"
#include "ScsiProtocol.h"
#include "ScsiCommon.h"
#include "IscsiIf.h"

#endif //_SCSI_HOST_H