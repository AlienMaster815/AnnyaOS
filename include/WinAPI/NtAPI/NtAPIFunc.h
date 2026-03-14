#ifndef _NTAPI_FUNC_H
#define _NTAPI_FUNC_H
#include <NtAPI.h>
#pragma once

#ifdef __cplusplus
#define NTHALAPI extern "C"
#define NTSYSCALLAPI extern "C"
#define CLFSUSER_API extern "C"
#define NTAPI_INLINE inline
#define NTKERNELAPI extern "C"
#define _DECL_HAL_KE_IMPORT extern "C"
#else

#define NTHALAPI extern
#define NTSYSCALLAPI extern
#define CLFSUSER_API extern
#define NTAPI_INLINE inline
#define NTKERNELAPI extern
#define _DECL_HAL_KE_IMPORT extern
#endif



#include "Misc/undocumentedTypes.h"
#include "ioaccess.h"
#include "ntddk.h"
#include "ntddsfio.h"
#include "ntddsysenv.h"
#include "ntifs.h"
#include "wmistr.h"
#include "ntddsfio.h"
#include "wmilib.h"
#include "irp.h"
#include "ntddsysenv.h"
#include "Ntintsafe.h"
#include "ntoapi.h"
#include "ntifs.h"
#include "wmidata.h"
#include "wdmsec.h"
#include "procgrp.h"
#include "ntstrsafe.h"
#include "wdm.h"
#include "../../kernel/loustatus.h"
#include "iointx.h"

#endif