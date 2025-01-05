/* SPDX-License-Identifier: GPL-2.0 OR MIT */
/*
 * Copyright 2012-2021 VMware, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/*
 * svga3d_dx.h --
 *
 *    SVGA 3d hardware definitions for DX10 support.
 */



#ifndef _SVGA3D_DX_H_
#define _SVGA3D_DX_H_

#include "SVGARegisters.h"
#include "SVGA3DLimits.h"
#include "SVGA3DTypes.h"

#define SVGA3D_INPUT_MIN 0
#define SVGA3D_INPUT_PER_VERTEX_DATA 0
#define SVGA3D_INPUT_PER_INSTANCE_DATA 1
#define SVGA3D_INPUT_MAX 2
typedef uint32_t SVGA3dInputClassification;

#define SVGA3D_COLOR_WRITE_ENABLE_RED (1 << 0)
#define SVGA3D_COLOR_WRITE_ENABLE_GREEN (1 << 1)
#define SVGA3D_COLOR_WRITE_ENABLE_BLUE (1 << 2)
#define SVGA3D_COLOR_WRITE_ENABLE_ALPHA (1 << 3)
#define SVGA3D_COLOR_WRITE_ENABLE_ALL                                          \
	(SVGA3D_COLOR_WRITE_ENABLE_RED | SVGA3D_COLOR_WRITE_ENABLE_GREEN |     \
	 SVGA3D_COLOR_WRITE_ENABLE_BLUE | SVGA3D_COLOR_WRITE_ENABLE_ALPHA)
typedef uint8_t SVGA3dColorWriteEnable;

#define SVGA3D_DEPTH_WRITE_MASK_ZERO 0
#define SVGA3D_DEPTH_WRITE_MASK_ALL 1
typedef uint8_t SVGA3dDepthWriteMask;

#define SVGA3D_FILTER_MIP_LINEAR (1 << 0)
#define SVGA3D_FILTER_MAG_LINEAR (1 << 2)
#define SVGA3D_FILTER_MIN_LINEAR (1 << 4)
#define SVGA3D_FILTER_ANISOTROPIC (1 << 6)
#define SVGA3D_FILTER_COMPARE (1 << 7)
typedef uint32_t SVGA3dFilter;

#define SVGA3D_CULL_INVALID 0
#define SVGA3D_CULL_MIN 1
#define SVGA3D_CULL_NONE 1
#define SVGA3D_CULL_FRONT 2
#define SVGA3D_CULL_BACK 3
#define SVGA3D_CULL_MAX 4
typedef uint8_t SVGA3dCullMode;

#define SVGA3D_COMPARISON_INVALID 0
#define SVGA3D_COMPARISON_MIN 1
#define SVGA3D_COMPARISON_NEVER 1
#define SVGA3D_COMPARISON_LESS 2
#define SVGA3D_COMPARISON_EQUAL 3
#define SVGA3D_COMPARISON_LESS_EQUAL 4
#define SVGA3D_COMPARISON_GREATER 5
#define SVGA3D_COMPARISON_NOT_EQUAL 6
#define SVGA3D_COMPARISON_GREATER_EQUAL 7
#define SVGA3D_COMPARISON_ALWAYS 8
#define SVGA3D_COMPARISON_MAX 9
typedef uint8_t SVGA3dComparisonFunc;

#define SVGA3D_MULTISAMPLE_RAST_DISABLE 0
#define SVGA3D_MULTISAMPLE_RAST_ENABLE 1
#define SVGA3D_MULTISAMPLE_RAST_DX_MAX 1
#define SVGA3D_MULTISAMPLE_RAST_DISABLE_LINE 2
#define SVGA3D_MULTISAMPLE_RAST_MAX 2
typedef uint8_t SVGA3dMultisampleRastEnable;

#define SVGA3D_DX_MAX_VERTEXBUFFERS 32
#define SVGA3D_DX_MAX_VERTEXINPUTREGISTERS 16
#define SVGA3D_DX_SM41_MAX_VERTEXINPUTREGISTERS 32
#define SVGA3D_DX_MAX_SOTARGETS 4
#define SVGA3D_DX_MAX_SRVIEWS 128
#define SVGA3D_DX_MAX_CONSTBUFFERS 16
#define SVGA3D_DX_MAX_SAMPLERS 16
#define SVGA3D_DX_MAX_CLASS_INSTANCES 253

#define SVGA3D_DX_MAX_CONSTBUF_BINDING_SIZE (4096 * 4 * (uint32)sizeof(uint32))

typedef uint32_t SVGA3dShaderResourceViewId;
typedef uint32_t SVGA3dRenderTargetViewId;
typedef uint32_t SVGA3dDepthStencilViewId;
typedef uint32_t SVGA3dUAViewId;

typedef uint32_t SVGA3dShaderId;
typedef uint32_t SVGA3dElementLayoutId;
typedef uint32_t SVGA3dSamplerId;
typedef uint32_t SVGA3dBlendStateId;
typedef uint32_t SVGA3dDepthStencilStateId;
typedef uint32_t SVGA3dRasterizerStateId;
typedef uint32_t SVGA3dQueryId;
typedef uint32_t SVGA3dStreamOutputId;

typedef union {
	struct {
		uint32_t r;
		uint32_t g;
		uint32_t b;
		uint32_t a;
	};

	uint32_t value[4];
} SVGA3dRGBAUint32;

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGAMobId mobid;
} SVGAOTableDXContextEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineContext {
	uint32_t cid;
} SVGA3dCmdDXDefineContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyContext {
	uint32_t cid;
} SVGA3dCmdDXDestroyContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBindContext {
	uint32_t cid;
	SVGAMobId mobid;
	uint32_t validContents;
} SVGA3dCmdDXBindContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXReadbackContext {
	uint32_t cid;
} SVGA3dCmdDXReadbackContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXInvalidateContext {
	uint32_t cid;
} SVGA3dCmdDXInvalidateContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetSingleConstantBuffer {
	uint32_t slot;
	SVGA3dShaderType type;
	SVGA3dSurfaceId sid;
	uint32_t offsetInBytes;
	uint32_t sizeInBytes;
} SVGA3dCmdDXSetSingleConstantBuffer;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetShaderResources {
	uint32_t startView;
	SVGA3dShaderType type;

} SVGA3dCmdDXSetShaderResources;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetShader {
	SVGA3dShaderId shaderId;
	SVGA3dShaderType type;
} SVGA3dCmdDXSetShader;
#pragma pack(pop)

typedef union {
	struct {
		uint32_t cbOffset : 12;
		uint32_t cbId : 4;
		uint32_t baseSamp : 4;
		uint32_t baseTex : 7;
		uint32_t reserved : 5;
	};
	uint32_t value;
} SVGA3dIfaceData;

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetShaderIface {
	SVGA3dShaderType type;
	uint32_t numClassInstances;
	uint32_t index;
	uint32_t iface;
	SVGA3dIfaceData data;
} SVGA3dCmdDXSetShaderIface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBindShaderIface {
	uint32_t cid;
	SVGAMobId mobid;
	uint32_t offsetInBytes;
} SVGA3dCmdDXBindShaderIface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetSamplers {
	uint32_t startSampler;
	SVGA3dShaderType type;

} SVGA3dCmdDXSetSamplers;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDraw {
	uint32_t vertexCount;
	uint32_t startVertexLocation;
} SVGA3dCmdDXDraw;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDrawIndexed {
	uint32_t indexCount;
	uint32_t startIndexLocation;
	int32_t baseVertexLocation;
} SVGA3dCmdDXDrawIndexed;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDrawInstanced {
	uint32_t vertexCountPerInstance;
	uint32_t instanceCount;
	uint32_t startVertexLocation;
	uint32_t startInstanceLocation;
} SVGA3dCmdDXDrawInstanced;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDrawIndexedInstanced {
	uint32_t indexCountPerInstance;
	uint32_t instanceCount;
	uint32_t startIndexLocation;
	int32_t baseVertexLocation;
	uint32_t startInstanceLocation;
} SVGA3dCmdDXDrawIndexedInstanced;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDrawIndexedInstancedIndirect {
	SVGA3dSurfaceId argsBufferSid;
	uint32_t byteOffsetForArgs;
} SVGA3dCmdDXDrawIndexedInstancedIndirect;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDrawInstancedIndirect {
	SVGA3dSurfaceId argsBufferSid;
	uint32_t byteOffsetForArgs;
} SVGA3dCmdDXDrawInstancedIndirect;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDrawAuto {
	uint32_t pad0;
} SVGA3dCmdDXDrawAuto;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDispatch {
	uint32_t threadGroupCountX;
	uint32_t threadGroupCountY;
	uint32_t threadGroupCountZ;
} SVGA3dCmdDXDispatch;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDispatchIndirect {
	SVGA3dSurfaceId argsBufferSid;
	uint32_t byteOffsetForArgs;
} SVGA3dCmdDXDispatchIndirect;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetInputLayout {
	SVGA3dElementLayoutId elementLayoutId;
} SVGA3dCmdDXSetInputLayout;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dVertexBuffer {
	SVGA3dSurfaceId sid;
	uint32_t stride;
	uint32_t offset;
} SVGA3dVertexBuffer;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetVertexBuffers {
	uint32_t startBuffer;

} SVGA3dCmdDXSetVertexBuffers;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dVertexBuffer_v2 {
	SVGA3dSurfaceId sid;
	uint32_t stride;
	uint32_t offset;
	uint32_t sizeInBytes;
} SVGA3dVertexBuffer_v2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetVertexBuffers_v2 {
	uint32_t startBuffer;

} SVGA3dCmdDXSetVertexBuffers_v2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dVertexBufferOffsetAndSize {
	uint32_t stride;
	uint32_t offset;
	uint32_t sizeInBytes;
} SVGA3dVertexBufferOffsetAndSize;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetVertexBuffersOffsetAndSize {
	uint32_t startBuffer;

} SVGA3dCmdDXSetVertexBuffersOffsetAndSize;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetIndexBuffer {
	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	uint32_t offset;
} SVGA3dCmdDXSetIndexBuffer;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetIndexBuffer_v2 {
	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	uint32_t offset;
	uint32_t sizeInBytes;
} SVGA3dCmdDXSetIndexBuffer_v2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetIndexBufferOffsetAndSize {
	SVGA3dSurfaceFormat format;
	uint32_t offset;
	uint32_t sizeInBytes;
} SVGA3dCmdDXSetIndexBufferOffsetAndSize;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetTopology {
	SVGA3dPrimitiveType topology;
} SVGA3dCmdDXSetTopology;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetRenderTargets {
	SVGA3dDepthStencilViewId depthStencilViewId;

} SVGA3dCmdDXSetRenderTargets;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetBlendState {
	SVGA3dBlendStateId blendId;
	float blendFactor[4];
	uint32_t sampleMask;
} SVGA3dCmdDXSetBlendState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetDepthStencilState {
	SVGA3dDepthStencilStateId depthStencilId;
	uint32_t stencilRef;
} SVGA3dCmdDXSetDepthStencilState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetRasterizerState {
	SVGA3dRasterizerStateId rasterizerId;
} SVGA3dCmdDXSetRasterizerState;
#pragma pack(pop)

#define SVGA3D_DXQUERY_FLAG_PREDICATEHINT (1 << 0)
typedef uint32_t SVGA3dDXQueryFlags;

#define SVGADX_QDSTATE_INVALID ((uint8)-1)
#define SVGADX_QDSTATE_MIN 0
#define SVGADX_QDSTATE_IDLE 0
#define SVGADX_QDSTATE_ACTIVE 1
#define SVGADX_QDSTATE_PENDING 2
#define SVGADX_QDSTATE_FINISHED 3
#define SVGADX_QDSTATE_MAX 4
typedef uint8_t SVGADXQueryDeviceState;

#pragma pack(push, 1)
typedef struct {
	SVGA3dQueryTypeUint8 type;
	uint16_t pad0;
	SVGADXQueryDeviceState state;
	SVGA3dDXQueryFlags flags;
	SVGAMobId mobid;
	uint32_t offset;
} SVGACOTableDXQueryEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineQuery {
	SVGA3dQueryId queryId;
	SVGA3dQueryType type;
	SVGA3dDXQueryFlags flags;
} SVGA3dCmdDXDefineQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyQuery {
	SVGA3dQueryId queryId;
} SVGA3dCmdDXDestroyQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBindQuery {
	SVGA3dQueryId queryId;
	SVGAMobId mobid;
} SVGA3dCmdDXBindQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetQueryOffset {
	SVGA3dQueryId queryId;
	uint32_t mobOffset;
} SVGA3dCmdDXSetQueryOffset;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBeginQuery {
	SVGA3dQueryId queryId;
} SVGA3dCmdDXBeginQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXEndQuery {
	SVGA3dQueryId queryId;
} SVGA3dCmdDXEndQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXReadbackQuery {
	SVGA3dQueryId queryId;
} SVGA3dCmdDXReadbackQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXMoveQuery {
	SVGA3dQueryId queryId;
	SVGAMobId mobid;
	uint32_t mobOffset;
} SVGA3dCmdDXMoveQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBindAllQuery {
	uint32_t cid;
	SVGAMobId mobid;
} SVGA3dCmdDXBindAllQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXReadbackAllQuery {
	uint32_t cid;
} SVGA3dCmdDXReadbackAllQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetPredication {
	SVGA3dQueryId queryId;
	uint32_t predicateValue;
} SVGA3dCmdDXSetPredication;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dDXSOState {
	uint32_t offset;
	uint32_t intOffset;
	uint32_t dead1;
	uint32_t dead2;
} SVGA3dDXSOState;
#pragma pack(pop)

#define SVGA3D_DX_SO_OFFSET_APPEND ((uint32)~0u)

#pragma pack(push, 1)
typedef struct SVGA3dSoTarget {
	SVGA3dSurfaceId sid;
	uint32_t offset;
	uint32_t sizeInBytes;
} SVGA3dSoTarget;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetSOTargets {
	uint32_t pad0;

} SVGA3dCmdDXSetSOTargets;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dViewport {
	float x;
	float y;
	float width;
	float height;
	float minDepth;
	float maxDepth;
} SVGA3dViewport;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetViewports {
	uint32_t pad0;

} SVGA3dCmdDXSetViewports;
#pragma pack(pop)

#define SVGA3D_DX_MAX_VIEWPORTS 16

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetScissorRects {
	uint32_t pad0;

} SVGA3dCmdDXSetScissorRects;
#pragma pack(pop)

#define SVGA3D_DX_MAX_SCISSORRECTS 16

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXClearRenderTargetView {
	SVGA3dRenderTargetViewId renderTargetViewId;
	SVGA3dRGBAFloat rgba;
} SVGA3dCmdDXClearRenderTargetView;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXClearDepthStencilView {
	uint16_t flags;
	uint16_t stencil;
	SVGA3dDepthStencilViewId depthStencilViewId;
	float depth;
} SVGA3dCmdDXClearDepthStencilView;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredCopyRegion {
	SVGA3dSurfaceId dstSid;
	uint32_t dstSubResource;
	SVGA3dSurfaceId srcSid;
	uint32_t srcSubResource;
	SVGA3dCopyBox box;
} SVGA3dCmdDXPredCopyRegion;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredStagingCopyRegion {
	SVGA3dSurfaceId dstSid;
	uint32_t dstSubResource;
	SVGA3dSurfaceId srcSid;
	uint32_t srcSubResource;
	SVGA3dCopyBox box;
	uint8_t readback;
	uint8_t unsynchronized;
	uint8_t mustBeZero[2];
} SVGA3dCmdDXPredStagingCopyRegion;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredCopy {
	SVGA3dSurfaceId dstSid;
	SVGA3dSurfaceId srcSid;
} SVGA3dCmdDXPredCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredConvertRegion {
	SVGA3dSurfaceId dstSid;
	uint32_t dstSubResource;
	SVGA3dBox destBox;
	SVGA3dSurfaceId srcSid;
	uint32_t srcSubResource;
	SVGA3dBox srcBox;
} SVGA3dCmdDXPredConvertRegion;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredStagingConvertRegion {
	SVGA3dSurfaceId dstSid;
	uint32_t dstSubResource;
	SVGA3dBox destBox;
	SVGA3dSurfaceId srcSid;
	uint32_t srcSubResource;
	SVGA3dBox srcBox;
	uint8_t readback;
	uint8_t unsynchronized;
	uint8_t mustBeZero[2];
} SVGA3dCmdDXPredStagingConvertRegion;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredConvert {
	SVGA3dSurfaceId dstSid;
	SVGA3dSurfaceId srcSid;
} SVGA3dCmdDXPredConvert;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredStagingConvert {
	SVGA3dSurfaceId dstSid;
	SVGA3dSurfaceId srcSid;
	uint8_t readback;
	uint8_t unsynchronized;
	uint8_t mustBeZero[2];
} SVGA3dCmdDXPredStagingConvert;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBufferCopy {
	SVGA3dSurfaceId dest;
	SVGA3dSurfaceId src;
	uint32_t destX;
	uint32_t srcX;
	uint32_t width;
} SVGA3dCmdDXBufferCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXStagingBufferCopy {
	SVGA3dSurfaceId dest;
	SVGA3dSurfaceId src;
	uint32_t destX;
	uint32_t srcX;
	uint32_t width;
	uint8_t readback;
	uint8_t unsynchronized;
	uint8_t mustBeZero[2];
} SVGA3dCmdDXStagingBufferCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceId dstSid;
	uint32_t dstSubResource;
	SVGA3dSurfaceId srcSid;
	uint32_t srcSubResource;
	SVGA3dSurfaceFormat copyFormat;
} SVGA3dCmdDXResolveCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceId dstSid;
	uint32_t dstSubResource;
	SVGA3dSurfaceId srcSid;
	uint32_t srcSubResource;
	SVGA3dSurfaceFormat copyFormat;
} SVGA3dCmdDXPredResolveCopy;
#pragma pack(pop)

typedef uint32_t SVGA3dDXPresentBltMode;
#define SVGADX_PRESENTBLT_LINEAR (1 << 0)
#define SVGADX_PRESENTBLT_FORCE_SRC_SRGB (1 << 1)
#define SVGADX_PRESENTBLT_FORCE_SRC_XRBIAS (1 << 2)
#define SVGADX_PRESENTBLT_MODE_MAX (1 << 3)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPresentBlt {
	SVGA3dSurfaceId srcSid;
	uint32_t srcSubResource;
	SVGA3dSurfaceId dstSid;
	uint32_t destSubResource;
	SVGA3dBox boxSrc;
	SVGA3dBox boxDest;
	SVGA3dDXPresentBltMode mode;
} SVGA3dCmdDXPresentBlt;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXGenMips {
	SVGA3dShaderResourceViewId shaderResourceViewId;
} SVGA3dCmdDXGenMips;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXUpdateSubResource {
	SVGA3dSurfaceId sid;
	uint32_t subResource;
	SVGA3dBox box;
} SVGA3dCmdDXUpdateSubResource;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXReadbackSubResource {
	SVGA3dSurfaceId sid;
	uint32_t subResource;
} SVGA3dCmdDXReadbackSubResource;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXInvalidateSubResource {
	SVGA3dSurfaceId sid;
	uint32_t subResource;
} SVGA3dCmdDXInvalidateSubResource;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXTransferFromBuffer {
	SVGA3dSurfaceId srcSid;
	uint32_t srcOffset;
	uint32_t srcPitch;
	uint32_t srcSlicePitch;
	SVGA3dSurfaceId destSid;
	uint32_t destSubResource;
	SVGA3dBox destBox;
} SVGA3dCmdDXTransferFromBuffer;
#pragma pack(pop)

#define SVGA3D_TRANSFER_TO_BUFFER_READBACK (1 << 0)
#define SVGA3D_TRANSFER_TO_BUFFER_FLAGS_MASK (1 << 0)
typedef uint32_t SVGA3dTransferToBufferFlags;

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXTransferToBuffer {
	SVGA3dSurfaceId srcSid;
	uint32_t srcSubResource;
	SVGA3dBox srcBox;
	SVGA3dSurfaceId destSid;
	uint32_t destOffset;
	uint32_t destPitch;
	uint32_t destSlicePitch;
	SVGA3dTransferToBufferFlags flags;
} SVGA3dCmdDXTransferToBuffer;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredTransferFromBuffer {
	SVGA3dSurfaceId srcSid;
	uint32_t srcOffset;
	uint32_t srcPitch;
	uint32_t srcSlicePitch;
	SVGA3dSurfaceId destSid;
	uint32_t destSubResource;
	SVGA3dBox destBox;
} SVGA3dCmdDXPredTransferFromBuffer;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSurfaceCopyAndReadback {
	SVGA3dSurfaceId srcSid;
	SVGA3dSurfaceId destSid;
	SVGA3dCopyBox box;
} SVGA3dCmdDXSurfaceCopyAndReadback;
#pragma pack(pop)

typedef uint32_t SVGADXHintId;
#define SVGA_DX_HINT_NONE 0
#define SVGA_DX_HINT_PREFETCH_OBJECT 1
#define SVGA_DX_HINT_PREEVICT_OBJECT 2
#define SVGA_DX_HINT_PREFETCH_COBJECT 3
#define SVGA_DX_HINT_PREEVICT_COBJECT 4
#define SVGA_DX_HINT_MAX 5

#pragma pack(push, 1)
typedef struct SVGAObjectRef {
	SVGAOTableType type;
	uint32_t id;
} SVGAObjectRef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGACObjectRef {
	SVGACOTableType type;
	uint32_t cid;
	uint32_t id;
} SVGACObjectRef;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXHint {
	SVGADXHintId hintId;

} SVGA3dCmdDXHint;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBufferUpdate {
	SVGA3dSurfaceId sid;
	uint32_t x;
	uint32_t width;
} SVGA3dCmdDXBufferUpdate;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetConstantBufferOffset {
	uint32_t slot;
	uint32_t offsetInBytes;
} SVGA3dCmdDXSetConstantBufferOffset;
#pragma pack(pop)

typedef SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetVSConstantBufferOffset;

typedef SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetPSConstantBufferOffset;

typedef SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetGSConstantBufferOffset;

typedef SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetHSConstantBufferOffset;

typedef SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetDSConstantBufferOffset;

typedef SVGA3dCmdDXSetConstantBufferOffset SVGA3dCmdDXSetCSConstantBufferOffset;

#define SVGA3D_BUFFEREX_SRV_RAW (1 << 0)
#define SVGA3D_BUFFEREX_SRV_FLAGS_MAX (1 << 1)
#define SVGA3D_BUFFEREX_SRV_FLAGS_MASK (SVGA3D_BUFFEREX_SRV_FLAGS_MAX - 1)
typedef uint32_t SVGA3dBufferExFlags;

#pragma pack(push, 1)
typedef struct {
	union {
		struct {
			uint32_t firstElement;
			uint32_t numElements;
			uint32_t pad0;
			uint32_t pad1;
		} buffer;
		struct {
			uint32_t mostDetailedMip;
			uint32_t firstArraySlice;
			uint32_t mipLevels;
			uint32_t arraySize;
		} tex;
		struct {
			uint32_t firstElement;
			uint32_t numElements;
			SVGA3dBufferExFlags flags;
			uint32_t pad0;
		} bufferex;
	};
} SVGA3dShaderResourceViewDesc;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;
	SVGA3dShaderResourceViewDesc desc;
	uint32_t pad;
} SVGACOTableDXSRViewEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineShaderResourceView {
	SVGA3dShaderResourceViewId shaderResourceViewId;

	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;

	SVGA3dShaderResourceViewDesc desc;
} SVGA3dCmdDXDefineShaderResourceView;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyShaderResourceView {
	SVGA3dShaderResourceViewId shaderResourceViewId;
} SVGA3dCmdDXDestroyShaderResourceView;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dRenderTargetViewDesc {
	union {
		struct {
			uint32_t firstElement;
			uint32_t numElements;
			uint32_t padding0;
		} buffer;
		struct {
			uint32_t mipSlice;
			uint32_t firstArraySlice;
			uint32_t arraySize;
		} tex;
		struct {
			uint32_t mipSlice;
			uint32_t firstW;
			uint32_t wSize;
		} tex3D;
	};
} SVGA3dRenderTargetViewDesc;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;
	SVGA3dRenderTargetViewDesc desc;
	uint32_t pad[2];
} SVGACOTableDXRTViewEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineRenderTargetView {
	SVGA3dRenderTargetViewId renderTargetViewId;

	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;

	SVGA3dRenderTargetViewDesc desc;
} SVGA3dCmdDXDefineRenderTargetView;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyRenderTargetView {
	SVGA3dRenderTargetViewId renderTargetViewId;
} SVGA3dCmdDXDestroyRenderTargetView;
#pragma pack(pop)

#define SVGA3D_DXDSVIEW_CREATE_READ_ONLY_DEPTH 0x01
#define SVGA3D_DXDSVIEW_CREATE_READ_ONLY_STENCIL 0x02
#define SVGA3D_DXDSVIEW_CREATE_FLAG_MASK 0x03
typedef uint8_t SVGA3DCreateDSViewFlags;

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;
	uint32_t mipSlice;
	uint32_t firstArraySlice;
	uint32_t arraySize;
	SVGA3DCreateDSViewFlags flags;
	uint8_t pad0;
	uint16_t pad1;
	uint32_t pad2;
} SVGACOTableDXDSViewEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineDepthStencilView {
	SVGA3dDepthStencilViewId depthStencilViewId;

	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;
	uint32_t mipSlice;
	uint32_t firstArraySlice;
	uint32_t arraySize;
	SVGA3DCreateDSViewFlags flags;
	uint8_t pad0;
	uint16_t pad1;
} SVGA3dCmdDXDefineDepthStencilView;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineDepthStencilView_v2 {
	SVGA3dDepthStencilViewId depthStencilViewId;

	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;
	uint32_t mipSlice;
	uint32_t firstArraySlice;
	uint32_t arraySize;
	SVGA3DCreateDSViewFlags flags;
	uint8_t pad0;
	uint16_t pad1;
} SVGA3dCmdDXDefineDepthStencilView_v2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyDepthStencilView {
	SVGA3dDepthStencilViewId depthStencilViewId;
} SVGA3dCmdDXDestroyDepthStencilView;
#pragma pack(pop)

#define SVGA3D_UABUFFER_RAW (1 << 0)
#define SVGA3D_UABUFFER_APPEND (1 << 1)
#define SVGA3D_UABUFFER_COUNTER (1 << 2)
typedef uint32_t SVGA3dUABufferFlags;

#pragma pack(push, 1)
typedef struct {
	union {
		struct {
			uint32_t firstElement;
			uint32_t numElements;
			SVGA3dUABufferFlags flags;
			uint32_t padding0;
			uint32_t padding1;
		} buffer;
		struct {
			uint32_t mipSlice;
			uint32_t firstArraySlice;
			uint32_t arraySize;
			uint32_t padding0;
			uint32_t padding1;
		} tex;
		struct {
			uint32_t mipSlice;
			uint32_t firstW;
			uint32_t wSize;
			uint32_t padding0;
			uint32_t padding1;
		} tex3D;
	};
} SVGA3dUAViewDesc;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;
	SVGA3dUAViewDesc desc;
	uint32_t structureCount;
	uint32_t pad[7];
} SVGACOTableDXUAViewEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineUAView {
	SVGA3dUAViewId uaViewId;

	SVGA3dSurfaceId sid;
	SVGA3dSurfaceFormat format;
	SVGA3dResourceType resourceDimension;

	SVGA3dUAViewDesc desc;
} SVGA3dCmdDXDefineUAView;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyUAView {
	SVGA3dUAViewId uaViewId;
} SVGA3dCmdDXDestroyUAView;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXClearUAViewUint {
	SVGA3dUAViewId uaViewId;
	SVGA3dRGBAUint32 value;
} SVGA3dCmdDXClearUAViewUint;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXClearUAViewFloat {
	SVGA3dUAViewId uaViewId;
	SVGA3dRGBAFloat value;
} SVGA3dCmdDXClearUAViewFloat;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXCopyStructureCount {
	SVGA3dUAViewId srcUAViewId;
	SVGA3dSurfaceId destSid;
	uint32_t destByteOffset;
} SVGA3dCmdDXCopyStructureCount;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetStructureCount {
	SVGA3dUAViewId uaViewId;
	uint32_t structureCount;
} SVGA3dCmdDXSetStructureCount;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetUAViews {
	uint32_t uavSpliceIndex;

} SVGA3dCmdDXSetUAViews;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetCSUAViews {
	uint32_t startIndex;

} SVGA3dCmdDXSetCSUAViews;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dInputElementDesc {
	uint32_t inputSlot;
	uint32_t alignedByteOffset;
	SVGA3dSurfaceFormat format;
	SVGA3dInputClassification inputSlotClass;
	uint32_t instanceDataStepRate;
	uint32_t inputRegister;
} SVGA3dInputElementDesc;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t elid;
	uint32_t numDescs;
	SVGA3dInputElementDesc descs[32];
	uint32_t pad[62];
} SVGACOTableDXElementLayoutEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineElementLayout {
	SVGA3dElementLayoutId elementLayoutId;

} SVGA3dCmdDXDefineElementLayout;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyElementLayout {
	SVGA3dElementLayoutId elementLayoutId;
} SVGA3dCmdDXDestroyElementLayout;
#pragma pack(pop)

#define SVGA3D_DX_MAX_RENDER_TARGETS 8

#pragma pack(push, 1)
typedef struct SVGA3dDXBlendStatePerRT {
	uint8_t blendEnable;
	uint8_t srcBlend;
	uint8_t destBlend;
	uint8_t blendOp;
	uint8_t srcBlendAlpha;
	uint8_t destBlendAlpha;
	uint8_t blendOpAlpha;
	SVGA3dColorWriteEnable renderTargetWriteMask;
	uint8_t logicOpEnable;
	uint8_t logicOp;
	uint16_t pad0;
} SVGA3dDXBlendStatePerRT;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint8_t alphaToCoverageEnable;
	uint8_t independentBlendEnable;
	uint16_t pad0;
	SVGA3dDXBlendStatePerRT perRT[SVGA3D_DX_MAX_RENDER_TARGETS];
	uint32_t pad1[7];
} SVGACOTableDXBlendStateEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineBlendState {
	SVGA3dBlendStateId blendId;
	uint8_t alphaToCoverageEnable;
	uint8_t independentBlendEnable;
	uint16_t pad0;
	SVGA3dDXBlendStatePerRT perRT[SVGA3D_DX_MAX_RENDER_TARGETS];
} SVGA3dCmdDXDefineBlendState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyBlendState {
	SVGA3dBlendStateId blendId;
} SVGA3dCmdDXDestroyBlendState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint8_t depthEnable;
	SVGA3dDepthWriteMask depthWriteMask;
	SVGA3dComparisonFunc depthFunc;
	uint8_t stencilEnable;
	uint8_t frontEnable;
	uint8_t backEnable;
	uint8_t stencilReadMask;
	uint8_t stencilWriteMask;

	uint8_t frontStencilFailOp;
	uint8_t frontStencilDepthFailOp;
	uint8_t frontStencilPassOp;
	SVGA3dComparisonFunc frontStencilFunc;

	uint8_t backStencilFailOp;
	uint8_t backStencilDepthFailOp;
	uint8_t backStencilPassOp;
	SVGA3dComparisonFunc backStencilFunc;
} SVGACOTableDXDepthStencilEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineDepthStencilState {
	SVGA3dDepthStencilStateId depthStencilId;

	uint8_t depthEnable;
	SVGA3dDepthWriteMask depthWriteMask;
	SVGA3dComparisonFunc depthFunc;
	uint8_t stencilEnable;
	uint8_t frontEnable;
	uint8_t backEnable;
	uint8_t stencilReadMask;
	uint8_t stencilWriteMask;

	uint8_t frontStencilFailOp;
	uint8_t frontStencilDepthFailOp;
	uint8_t frontStencilPassOp;
	SVGA3dComparisonFunc frontStencilFunc;

	uint8_t backStencilFailOp;
	uint8_t backStencilDepthFailOp;
	uint8_t backStencilPassOp;
	SVGA3dComparisonFunc backStencilFunc;
} SVGA3dCmdDXDefineDepthStencilState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyDepthStencilState {
	SVGA3dDepthStencilStateId depthStencilId;
} SVGA3dCmdDXDestroyDepthStencilState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint8_t fillMode;
	SVGA3dCullMode cullMode;
	uint8_t frontCounterClockwise;
	uint8_t provokingVertexLast;
	int32_t depthBias;
	float depthBiasClamp;
	float slopeScaledDepthBias;
	uint8_t depthClipEnable;
	uint8_t scissorEnable;
	SVGA3dMultisampleRastEnable multisampleEnable;
	uint8_t antialiasedLineEnable;
	float lineWidth;
	uint8_t lineStippleEnable;
	uint8_t lineStippleFactor;
	uint16_t lineStipplePattern;
	uint8_t forcedSampleCount;
	uint8_t mustBeZero[3];
} SVGACOTableDXRasterizerStateEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineRasterizerState {
	SVGA3dRasterizerStateId rasterizerId;

	uint8_t fillMode;
	SVGA3dCullMode cullMode;
	uint8_t frontCounterClockwise;
	uint8_t provokingVertexLast;
	int32_t depthBias;
	float depthBiasClamp;
	float slopeScaledDepthBias;
	uint8_t depthClipEnable;
	uint8_t scissorEnable;
	SVGA3dMultisampleRastEnable multisampleEnable;
	uint8_t antialiasedLineEnable;
	float lineWidth;
	uint8_t lineStippleEnable;
	uint8_t lineStippleFactor;
	uint16_t lineStipplePattern;
} SVGA3dCmdDXDefineRasterizerState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineRasterizerState_v2 {
	SVGA3dRasterizerStateId rasterizerId;

	uint8_t fillMode;
	SVGA3dCullMode cullMode;
	uint8_t frontCounterClockwise;
	uint8_t provokingVertexLast;
	int32_t depthBias;
	float depthBiasClamp;
	float slopeScaledDepthBias;
	uint8_t depthClipEnable;
	uint8_t scissorEnable;
	SVGA3dMultisampleRastEnable multisampleEnable;
	uint8_t antialiasedLineEnable;
	float lineWidth;
	uint8_t lineStippleEnable;
	uint8_t lineStippleFactor;
	uint16_t lineStipplePattern;
	uint32_t forcedSampleCount;
} SVGA3dCmdDXDefineRasterizerState_v2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyRasterizerState {
	SVGA3dRasterizerStateId rasterizerId;
} SVGA3dCmdDXDestroyRasterizerState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dFilter filter;
	uint8_t addressU;
	uint8_t addressV;
	uint8_t addressW;
	uint8_t pad0;
	float mipLODBias;
	uint8_t maxAnisotropy;
	SVGA3dComparisonFunc comparisonFunc;
	uint16_t pad1;
	SVGA3dRGBAFloat borderColor;
	float minLOD;
	float maxLOD;
	uint32_t pad2[6];
} SVGACOTableDXSamplerEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineSamplerState {
	SVGA3dSamplerId samplerId;
	SVGA3dFilter filter;
	uint8_t addressU;
	uint8_t addressV;
	uint8_t addressW;
	uint8_t pad0;
	float mipLODBias;
	uint8_t maxAnisotropy;
	SVGA3dComparisonFunc comparisonFunc;
	uint16_t pad1;
	SVGA3dRGBAFloat borderColor;
	float minLOD;
	float maxLOD;
} SVGA3dCmdDXDefineSamplerState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroySamplerState {
	SVGA3dSamplerId samplerId;
} SVGA3dCmdDXDestroySamplerState;
#pragma pack(pop)

#define SVGADX_SIGNATURE_SEMANTIC_NAME_UNDEFINED 0
#define SVGADX_SIGNATURE_SEMANTIC_NAME_POSITION 1
#define SVGADX_SIGNATURE_SEMANTIC_NAME_CLIP_DISTANCE 2
#define SVGADX_SIGNATURE_SEMANTIC_NAME_CULL_DISTANCE 3
#define SVGADX_SIGNATURE_SEMANTIC_NAME_RENDER_TARGET_ARRAY_INDEX 4
#define SVGADX_SIGNATURE_SEMANTIC_NAME_VIEWPORT_ARRAY_INDEX 5
#define SVGADX_SIGNATURE_SEMANTIC_NAME_VERTEX_ID 6
#define SVGADX_SIGNATURE_SEMANTIC_NAME_PRIMITIVE_ID 7
#define SVGADX_SIGNATURE_SEMANTIC_NAME_INSTANCE_ID 8
#define SVGADX_SIGNATURE_SEMANTIC_NAME_IS_FRONT_FACE 9
#define SVGADX_SIGNATURE_SEMANTIC_NAME_SAMPLE_INDEX 10
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_U_EQ_0_EDGE_TESSFACTOR 11
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_V_EQ_0_EDGE_TESSFACTOR 12
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_U_EQ_1_EDGE_TESSFACTOR 13
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_V_EQ_1_EDGE_TESSFACTOR 14
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_U_INSIDE_TESSFACTOR 15
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_QUAD_V_INSIDE_TESSFACTOR 16
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_TRI_U_EQ_0_EDGE_TESSFACTOR 17
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_TRI_V_EQ_0_EDGE_TESSFACTOR 18
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_TRI_W_EQ_0_EDGE_TESSFACTOR 19
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_TRI_INSIDE_TESSFACTOR 20
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_LINE_DETAIL_TESSFACTOR 21
#define SVGADX_SIGNATURE_SEMANTIC_NAME_FINAL_LINE_DENSITY_TESSFACTOR 22
#define SVGADX_SIGNATURE_SEMANTIC_NAME_MAX 23
typedef uint32_t SVGA3dDXSignatureSemanticName;

#define SVGADX_SIGNATURE_REGISTER_COMPONENT_UNKNOWN 0
typedef uint32_t SVGA3dDXSignatureRegisterComponentType;

#define SVGADX_SIGNATURE_MIN_PRECISION_DEFAULT 0
typedef uint32_t SVGA3dDXSignatureMinPrecision;

#pragma pack(push, 1)
typedef struct SVGA3dDXSignatureEntry {
	uint32_t registerIndex;
	SVGA3dDXSignatureSemanticName semanticName;
	uint32_t mask;
	SVGA3dDXSignatureRegisterComponentType componentType;
	SVGA3dDXSignatureMinPrecision minPrecision;
} SVGA3dDXShaderSignatureEntry;
#pragma pack(pop)

#define SVGADX_SIGNATURE_HEADER_VERSION_0 0x08a92d12

#pragma pack(push, 1)
typedef struct SVGA3dDXSignatureHeader {
	uint32_t headerVersion;
	uint32_t numInputSignatures;
	uint32_t numOutputSignatures;
	uint32_t numPatchConstantSignatures;
} SVGA3dDXShaderSignatureHeader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineShader {
	SVGA3dShaderId shaderId;
	SVGA3dShaderType type;
	uint32_t sizeInBytes;
} SVGA3dCmdDXDefineShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGACOTableDXShaderEntry {
	SVGA3dShaderType type;
	uint32_t sizeInBytes;
	uint32_t offsetInBytes;
	SVGAMobId mobid;
	uint32_t pad[4];
} SVGACOTableDXShaderEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyShader {
	SVGA3dShaderId shaderId;
} SVGA3dCmdDXDestroyShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBindShader {
	uint32_t cid;
	uint32_t shid;
	SVGAMobId mobid;
	uint32_t offsetInBytes;
} SVGA3dCmdDXBindShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBindAllShader {
	uint32_t cid;
	SVGAMobId mobid;
} SVGA3dCmdDXBindAllShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXCondBindAllShader {
	uint32_t cid;
	SVGAMobId testMobid;
	SVGAMobId mobid;
} SVGA3dCmdDXCondBindAllShader;
#pragma pack(pop)

#define SVGA3D_MAX_DX10_STREAMOUT_DECLS 64
#define SVGA3D_MAX_STREAMOUT_DECLS 512

#pragma pack(push, 1)
typedef struct SVGA3dStreamOutputDeclarationEntry {
	uint32_t outputSlot;
	uint32_t registerIndex;
	uint8_t registerMask;
	uint8_t pad0;
	uint16_t pad1;
	uint32_t stream;
} SVGA3dStreamOutputDeclarationEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGAOTableStreamOutputEntry {
	uint32_t numOutputStreamEntries;
	SVGA3dStreamOutputDeclarationEntry decl[SVGA3D_MAX_DX10_STREAMOUT_DECLS];
	uint32_t streamOutputStrideInBytes[SVGA3D_DX_MAX_SOTARGETS];
	uint32_t rasterizedStream;
	uint32_t numOutputStreamStrides;
	uint32_t mobid;
	uint32_t offsetInBytes;
	uint8_t usesMob;
	uint8_t pad0;
	uint16_t pad1;
	uint32_t pad2[246];
} SVGACOTableDXStreamOutputEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineStreamOutput {
	SVGA3dStreamOutputId soid;
	uint32_t numOutputStreamEntries;
	SVGA3dStreamOutputDeclarationEntry decl[SVGA3D_MAX_DX10_STREAMOUT_DECLS];
	uint32_t streamOutputStrideInBytes[SVGA3D_DX_MAX_SOTARGETS];
	uint32_t rasterizedStream;
} SVGA3dCmdDXDefineStreamOutput;
#pragma pack(pop)

#define SVGA3D_DX_SO_NO_RASTERIZED_STREAM 0xFFFFFFFF

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDefineStreamOutputWithMob {
	SVGA3dStreamOutputId soid;
	uint32_t numOutputStreamEntries;
	uint32_t numOutputStreamStrides;
	uint32_t streamOutputStrideInBytes[SVGA3D_DX_MAX_SOTARGETS];
	uint32_t rasterizedStream;
} SVGA3dCmdDXDefineStreamOutputWithMob;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXBindStreamOutput {
	SVGA3dStreamOutputId soid;
	uint32_t mobid;
	uint32_t offsetInBytes;
	uint32_t sizeInBytes;
} SVGA3dCmdDXBindStreamOutput;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXDestroyStreamOutput {
	SVGA3dStreamOutputId soid;
} SVGA3dCmdDXDestroyStreamOutput;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetStreamOutput {
	SVGA3dStreamOutputId soid;
} SVGA3dCmdDXSetStreamOutput;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetMinLOD {
	SVGA3dSurfaceId sid;
	float minLOD;
} SVGA3dCmdDXSetMinLOD;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint64_t value;
	uint32_t mobId;
	uint32_t mobOffset;
} SVGA3dCmdDXMobFence64;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXSetCOTable {
	uint32_t cid;
	uint32_t mobid;
	SVGACOTableType type;
	uint32_t validSizeInBytes;
} SVGA3dCmdDXSetCOTable;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXGrowCOTable {
	uint32_t cid;
	uint32_t mobid;
	SVGACOTableType type;
	uint32_t validSizeInBytes;
} SVGA3dCmdDXGrowCOTable;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXReadbackCOTable {
	uint32_t cid;
	SVGACOTableType type;
} SVGA3dCmdDXReadbackCOTable;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXCopyCOTableIntoMob {
	uint32_t cid;
	SVGACOTableType type;
	uint32_t mobid;
} SVGA3dCmdDXCopyCOTableIntoMob;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXPredStagingCopy {
	SVGA3dSurfaceId dstSid;
	SVGA3dSurfaceId srcSid;
	uint8_t readback;
	uint8_t unsynchronized;
	uint8_t mustBeZero[2];

} SVGA3dCmdDXPredStagingCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDXStagingCopy {
	SVGA3dSurfaceId dstSid;
	SVGA3dSurfaceId srcSid;
	uint8_t readback;
	uint8_t unsynchronized;
	uint8_t mustBeZero[2];

} SVGA3dCmdDXStagingCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCOTableData {
	uint32_t mobid;
} SVGA3dCOTableData;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dBufferBinding {
	uint32_t bufferId;
	uint32_t stride;
	uint32_t offset;
} SVGA3dBufferBinding;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dConstantBufferBinding {
	uint32_t sid;
	uint32_t offsetInBytes;
	uint32_t sizeInBytes;
} SVGA3dConstantBufferBinding;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGADXInputAssemblyMobFormat {
	uint32_t layoutId;
	SVGA3dBufferBinding vertexBuffers[SVGA3D_DX_MAX_VERTEXBUFFERS];
	uint32_t indexBufferSid;
	uint32_t pad;
	uint32_t indexBufferOffset;
	uint32_t indexBufferFormat;
	uint32_t topology;
} SVGADXInputAssemblyMobFormat;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGADXContextMobFormat {
	SVGADXInputAssemblyMobFormat inputAssembly;

	struct {
		uint32_t blendStateId;
		uint32_t blendFactor[4];
		uint32_t sampleMask;
		uint32_t depthStencilStateId;
		uint32_t stencilRef;
		uint32_t rasterizerStateId;
		uint32_t depthStencilViewId;
		uint32_t renderTargetViewIds[SVGA3D_DX_MAX_RENDER_TARGETS];
	} renderState;

	uint32_t pad0[8];

	struct {
		uint32_t targets[SVGA3D_DX_MAX_SOTARGETS];
		uint32_t soid;
	} streamOut;

	uint32_t pad1[10];

	uint32_t uavSpliceIndex;

	uint8_t numViewports;
	uint8_t numScissorRects;
	uint16_t pad2[1];

	uint32_t pad3[3];

	SVGA3dViewport viewports[SVGA3D_DX_MAX_VIEWPORTS];
	uint32_t pad4[32];

	SVGASignedRect scissorRects[SVGA3D_DX_MAX_SCISSORRECTS];
	uint32_t pad5[64];

	struct {
		uint32_t queryID;
		uint32_t value;
	} predication;

	SVGAMobId shaderIfaceMobid;
	uint32_t shaderIfaceOffset;
	struct {
		uint32_t shaderId;
		SVGA3dConstantBufferBinding
			constantBuffers[SVGA3D_DX_MAX_CONSTBUFFERS];
		uint32_t shaderResources[SVGA3D_DX_MAX_SRVIEWS];
		uint32_t samplers[SVGA3D_DX_MAX_SAMPLERS];
	} shaderState[SVGA3D_NUM_SHADERTYPE];
	uint32_t pad6[26];

	SVGA3dQueryId queryID[SVGA3D_MAX_QUERY];

	SVGA3dCOTableData cotables[SVGA_COTABLE_MAX];

	uint32_t pad7[64];

	uint32_t uaViewIds[SVGA3D_DX11_1_MAX_UAVIEWS];
	uint32_t csuaViewIds[SVGA3D_DX11_1_MAX_UAVIEWS];

	uint32_t pad8[188];
} SVGADXContextMobFormat;
#pragma pack(pop)

#define SVGA3D_DX_MAX_CLASS_INSTANCES_PADDED 256

#pragma pack(push, 1)
typedef struct SVGADXShaderIfaceMobFormat {
	struct {
		uint32_t numClassInstances;
		uint32_t iface[SVGA3D_DX_MAX_CLASS_INSTANCES_PADDED];
		SVGA3dIfaceData data[SVGA3D_DX_MAX_CLASS_INSTANCES_PADDED];
	} shaderIfaceState[SVGA3D_NUM_SHADERTYPE];

	uint32_t pad0[1018];
} SVGADXShaderIfaceMobFormat;
#pragma pack(pop)

#endif