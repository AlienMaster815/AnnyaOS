/* SPDX-License-Identifier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright (c) 2009-2024 Broadcom. All Rights Reserved. The term
 * “Broadcom” refers to Broadcom Inc. and/or its subsidiaries.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#ifndef _VMWSVGA_H
#define _VMWSVGA_H

#include <LouDDK.h>
#include "TtmObj.h"
#include "VmFence.h"
#include "VMWareRegisters.h"

#define VMWSVGA_DRIVER_NAME "Lousine Kernel Internal VMWSVGA.SYS Module"
#define VMWSVGA_DRIVER_MAJOR 0
#define VMWSVGA_DRIVER_MINOR 1
#define VMWSVGA_FIFO_STATIC_SIZE (1024 * 1024)
#define VMWSVGA_NUM_DISP_UNITS  8
#define VMWSVGA_CMD_BOUNCE_INIT_SIZE 32768

#define VMWSVGA_INITIAL_WIDTH  1280
#define VMWSVGA_INITIAL_HEIGHT 800

#define VMWSVGA_SVGA_II_ID  0x0405
#define VMWSVGA_SVGA_III_ID 0x0406

#define VMWSVGA_MAX_IRQS 6

#define VMWSVGA_NUM_GB_CONTEXT          256
#define VMWSVGA_NUM_GB_SHADER           20000
#define VMWSVGA_NUM_GB_SURFACE          32768
#define VMWSVGA_NUM_GB_SCREEN_TARGET    VMWSVGA_NUM_DISP_UNITS
#define VMWSVGA_NUM_DXCONTEXT           256
#define VMWSVGA_NUM_DXQUERY             512
#define VMWSVGA_NUM_MOB                 (VMWSVGA_NUM_GB_CONTEXT+\
                                         VMWSVGA_NUM_GB_SHADER +\
                                         VMWSVGA_NUM_GB_SURFACE+\
                                         VMWSVGA_NUM_GB_SCREEN_TARGET)

#define VMW_RES_HT_ORDER 12


#endif //_VMWSVGA_H

enum vmw_res_type {
	vmw_res_context,
	vmw_res_surface,
	vmw_res_stream,
	vmw_res_shader,
	vmw_res_dx_context,
	vmw_res_cotable,
	vmw_res_view,
	vmw_res_streamoutput,
	vmw_res_max
};

struct vmw_sw_context{
	//DECLARE_HASHTABLE(res_ht, VMW_RES_HT_ORDER);
	bool kernel;
	void* fp;
    void* filp;
	uint32_t *cmd_bounce;
	uint32_t cmd_bounce_size;
	void* cur_query_bo;
	ListHeader bo_relocations;
	ListHeader res_relocations;
	uint32_t *buf_start;
	void* res_cache[vmw_res_max];
	void* last_query_ctx;
	bool needs_post_query_barrier;
	void* staged_bindings;
	bool staged_bindings_inuse;
	ListHeader staged_cmd_res;
	ListHeader ctx_list;
	void* dx_ctx_node;
	void* dx_query_mob;
	void* dx_query_ctx;
	void* man;
	void* ctx;
};

LOUSTATUS VmwHostGetGustInformation(
    string guest_info_param,
    string buffer, 
    size_t *length
);