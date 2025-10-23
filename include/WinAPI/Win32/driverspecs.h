/* 
 * Clean-room reimplementation of functionality from Wine project file: <drvicespecs.h>
 *
 * This file contains original source code written from scratch based on
 * publicly available behavior of the Windows API and documented interfaces.
 *
 * No Wine source code was copied or reused. Behavior is matched only for
 * compatibility.
 *
 * This implementation is NOT a derivative of Wine source code and is not
 * subject to Wine licensing terms.
 */

#ifndef DRIVERSPECS_H
#define DRIVERSPECS_H

#include "specstrings.h"
#include "concurrencysal.h"

#define _IRQL_raises_(x)
#define _IRQL_requires_(x)
#define _IRQL_requires_max_(x)
#define _IRQL_requires_min_(x)
#define _IRQL_restores_
#define _IRQL_saves_

#define __drv_aliasesMem
#define __drv_allocatesMem(kind)
#define __drv_arg(x,y)
#define __drv_at(x,y)
#define __drv_deref(x)
#define __drv_dispatchType(x)
#define __drv_dispatchType_other
#define __drv_formatString(x)
#define __drv_freesMem(kind)
#define __drv_in(x)
#define __drv_in_deref(x)
#define __drv_maxIRQL(x)
#define __drv_nonConstant
#define __drv_out(x)
#define __drv_out_deref(x)
#define __drv_raisesIRQL(x)
#define __drv_requiresIRQL(x)
#define __drv_restoresIRQL
#define __drv_restoresIRQLGlobal(x,y)
#define __drv_savesIRQL
#define __drv_savesIRQLGlobal(x,y)
#define __drv_setsIRQL(x)
#define __drv_useCancelIRQL
#define __drv_valueIs(x)
#define __drv_when(x,y)

#define __internal_kernel_driver
#define __kernel_code
#define __kernel_driver
#define __user_code
#define __user_driver

#endif