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
 * svga3d_cmd.h --
 *
 *    SVGA 3d hardware cmd definitions
 */

#ifndef _SVGA3D_CMD_H_
#define _SVGA3D_CMD_H_

#include "SVGA3DTypes.h"
#include "SVGA3DLimits.h"
#include "SVGA3DRegisters.h"

typedef enum SVGAFifo3dCmdId {
	SVGA_3D_CMD_LEGACY_BASE = 1000,
	SVGA_3D_CMD_BASE = 1040,

	SVGA_3D_CMD_SURFACE_DEFINE = 1040,
	SVGA_3D_CMD_SURFACE_DESTROY = 1041,
	SVGA_3D_CMD_SURFACE_COPY = 1042,
	SVGA_3D_CMD_SURFACE_STRETCHBLT = 1043,
	SVGA_3D_CMD_SURFACE_DMA = 1044,
	SVGA_3D_CMD_CONTEXT_DEFINE = 1045,
	SVGA_3D_CMD_CONTEXT_DESTROY = 1046,
	SVGA_3D_CMD_SETTRANSFORM = 1047,
	SVGA_3D_CMD_SETZRANGE = 1048,
	SVGA_3D_CMD_SETRENDERSTATE = 1049,
	SVGA_3D_CMD_SETRENDERTARGET = 1050,
	SVGA_3D_CMD_SETTEXTURESTATE = 1051,
	SVGA_3D_CMD_SETMATERIAL = 1052,
	SVGA_3D_CMD_SETLIGHTDATA = 1053,
	SVGA_3D_CMD_SETLIGHTENABLED = 1054,
	SVGA_3D_CMD_SETVIEWPORT = 1055,
	SVGA_3D_CMD_SETCLIPPLANE = 1056,
	SVGA_3D_CMD_CLEAR = 1057,
	SVGA_3D_CMD_PRESENT = 1058,
	SVGA_3D_CMD_SHADER_DEFINE = 1059,
	SVGA_3D_CMD_SHADER_DESTROY = 1060,
	SVGA_3D_CMD_SET_SHADER = 1061,
	SVGA_3D_CMD_SET_SHADER_CONST = 1062,
	SVGA_3D_CMD_DRAW_PRIMITIVES = 1063,
	SVGA_3D_CMD_SETSCISSORRECT = 1064,
	SVGA_3D_CMD_BEGIN_QUERY = 1065,
	SVGA_3D_CMD_END_QUERY = 1066,
	SVGA_3D_CMD_WAIT_FOR_QUERY = 1067,
	SVGA_3D_CMD_PRESENT_READBACK = 1068,
	SVGA_3D_CMD_BLIT_SURFACE_TO_SCREEN = 1069,
	SVGA_3D_CMD_SURFACE_DEFINE_V2 = 1070,
	SVGA_3D_CMD_GENERATE_MIPMAPS = 1071,
	SVGA_3D_CMD_DEAD4 = 1072,
	SVGA_3D_CMD_DEAD5 = 1073,
	SVGA_3D_CMD_DEAD6 = 1074,
	SVGA_3D_CMD_DEAD7 = 1075,
	SVGA_3D_CMD_DEAD8 = 1076,
	SVGA_3D_CMD_DEAD9 = 1077,
	SVGA_3D_CMD_DEAD10 = 1078,
	SVGA_3D_CMD_DEAD11 = 1079,
	SVGA_3D_CMD_ACTIVATE_SURFACE = 1080,
	SVGA_3D_CMD_DEACTIVATE_SURFACE = 1081,
	SVGA_3D_CMD_SCREEN_DMA = 1082,
	SVGA_3D_CMD_DEAD1 = 1083,
	SVGA_3D_CMD_DEAD2 = 1084,

	SVGA_3D_CMD_DEAD12 = 1085,
	SVGA_3D_CMD_DEAD13 = 1086,
	SVGA_3D_CMD_DEAD14 = 1087,
	SVGA_3D_CMD_DEAD15 = 1088,
	SVGA_3D_CMD_DEAD16 = 1089,
	SVGA_3D_CMD_DEAD17 = 1090,

	SVGA_3D_CMD_SET_OTABLE_BASE = 1091,
	SVGA_3D_CMD_READBACK_OTABLE = 1092,

	SVGA_3D_CMD_DEFINE_GB_MOB = 1093,
	SVGA_3D_CMD_DESTROY_GB_MOB = 1094,
	SVGA_3D_CMD_DEAD3 = 1095,
	SVGA_3D_CMD_UPDATE_GB_MOB_MAPPING = 1096,

	SVGA_3D_CMD_DEFINE_GB_SURFACE = 1097,
	SVGA_3D_CMD_DESTROY_GB_SURFACE = 1098,
	SVGA_3D_CMD_BIND_GB_SURFACE = 1099,
	SVGA_3D_CMD_COND_BIND_GB_SURFACE = 1100,
	SVGA_3D_CMD_UPDATE_GB_IMAGE = 1101,
	SVGA_3D_CMD_UPDATE_GB_SURFACE = 1102,
	SVGA_3D_CMD_READBACK_GB_IMAGE = 1103,
	SVGA_3D_CMD_READBACK_GB_SURFACE = 1104,
	SVGA_3D_CMD_INVALIDATE_GB_IMAGE = 1105,
	SVGA_3D_CMD_INVALIDATE_GB_SURFACE = 1106,

	SVGA_3D_CMD_DEFINE_GB_CONTEXT = 1107,
	SVGA_3D_CMD_DESTROY_GB_CONTEXT = 1108,
	SVGA_3D_CMD_BIND_GB_CONTEXT = 1109,
	SVGA_3D_CMD_READBACK_GB_CONTEXT = 1110,
	SVGA_3D_CMD_INVALIDATE_GB_CONTEXT = 1111,

	SVGA_3D_CMD_DEFINE_GB_SHADER = 1112,
	SVGA_3D_CMD_DESTROY_GB_SHADER = 1113,
	SVGA_3D_CMD_BIND_GB_SHADER = 1114,

	SVGA_3D_CMD_SET_OTABLE_BASE64 = 1115,

	SVGA_3D_CMD_BEGIN_GB_QUERY = 1116,
	SVGA_3D_CMD_END_GB_QUERY = 1117,
	SVGA_3D_CMD_WAIT_FOR_GB_QUERY = 1118,

	SVGA_3D_CMD_NOP = 1119,

	SVGA_3D_CMD_ENABLE_GART = 1120,
	SVGA_3D_CMD_DISABLE_GART = 1121,
	SVGA_3D_CMD_MAP_MOB_INTO_GART = 1122,
	SVGA_3D_CMD_UNMAP_GART_RANGE = 1123,

	SVGA_3D_CMD_DEFINE_GB_SCREENTARGET = 1124,
	SVGA_3D_CMD_DESTROY_GB_SCREENTARGET = 1125,
	SVGA_3D_CMD_BIND_GB_SCREENTARGET = 1126,
	SVGA_3D_CMD_UPDATE_GB_SCREENTARGET = 1127,

	SVGA_3D_CMD_READBACK_GB_IMAGE_PARTIAL = 1128,
	SVGA_3D_CMD_INVALIDATE_GB_IMAGE_PARTIAL = 1129,

	SVGA_3D_CMD_SET_GB_SHADERCONSTS_INLINE = 1130,

	SVGA_3D_CMD_GB_SCREEN_DMA = 1131,
	SVGA_3D_CMD_BIND_GB_SURFACE_WITH_PITCH = 1132,
	SVGA_3D_CMD_GB_MOB_FENCE = 1133,
	SVGA_3D_CMD_DEFINE_GB_SURFACE_V2 = 1134,
	SVGA_3D_CMD_DEFINE_GB_MOB64 = 1135,
	SVGA_3D_CMD_REDEFINE_GB_MOB64 = 1136,
	SVGA_3D_CMD_NOP_ERROR = 1137,

	SVGA_3D_CMD_SET_VERTEX_STREAMS = 1138,
	SVGA_3D_CMD_SET_VERTEX_DECLS = 1139,
	SVGA_3D_CMD_SET_VERTEX_DIVISORS = 1140,
	SVGA_3D_CMD_DRAW = 1141,
	SVGA_3D_CMD_DRAW_INDEXED = 1142,

	SVGA_3D_CMD_DX_MIN = 1143,
	SVGA_3D_CMD_DX_DEFINE_CONTEXT = 1143,
	SVGA_3D_CMD_DX_DESTROY_CONTEXT = 1144,
	SVGA_3D_CMD_DX_BIND_CONTEXT = 1145,
	SVGA_3D_CMD_DX_READBACK_CONTEXT = 1146,
	SVGA_3D_CMD_DX_INVALIDATE_CONTEXT = 1147,
	SVGA_3D_CMD_DX_SET_SINGLE_CONSTANT_BUFFER = 1148,
	SVGA_3D_CMD_DX_SET_SHADER_RESOURCES = 1149,
	SVGA_3D_CMD_DX_SET_SHADER = 1150,
	SVGA_3D_CMD_DX_SET_SAMPLERS = 1151,
	SVGA_3D_CMD_DX_DRAW = 1152,
	SVGA_3D_CMD_DX_DRAW_INDEXED = 1153,
	SVGA_3D_CMD_DX_DRAW_INSTANCED = 1154,
	SVGA_3D_CMD_DX_DRAW_INDEXED_INSTANCED = 1155,
	SVGA_3D_CMD_DX_DRAW_AUTO = 1156,
	SVGA_3D_CMD_DX_SET_INPUT_LAYOUT = 1157,
	SVGA_3D_CMD_DX_SET_VERTEX_BUFFERS = 1158,
	SVGA_3D_CMD_DX_SET_INDEX_BUFFER = 1159,
	SVGA_3D_CMD_DX_SET_TOPOLOGY = 1160,
	SVGA_3D_CMD_DX_SET_RENDERTARGETS = 1161,
	SVGA_3D_CMD_DX_SET_BLEND_STATE = 1162,
	SVGA_3D_CMD_DX_SET_DEPTHSTENCIL_STATE = 1163,
	SVGA_3D_CMD_DX_SET_RASTERIZER_STATE = 1164,
	SVGA_3D_CMD_DX_DEFINE_QUERY = 1165,
	SVGA_3D_CMD_DX_DESTROY_QUERY = 1166,
	SVGA_3D_CMD_DX_BIND_QUERY = 1167,
	SVGA_3D_CMD_DX_SET_QUERY_OFFSET = 1168,
	SVGA_3D_CMD_DX_BEGIN_QUERY = 1169,
	SVGA_3D_CMD_DX_END_QUERY = 1170,
	SVGA_3D_CMD_DX_READBACK_QUERY = 1171,
	SVGA_3D_CMD_DX_SET_PREDICATION = 1172,
	SVGA_3D_CMD_DX_SET_SOTARGETS = 1173,
	SVGA_3D_CMD_DX_SET_VIEWPORTS = 1174,
	SVGA_3D_CMD_DX_SET_SCISSORRECTS = 1175,
	SVGA_3D_CMD_DX_CLEAR_RENDERTARGET_VIEW = 1176,
	SVGA_3D_CMD_DX_CLEAR_DEPTHSTENCIL_VIEW = 1177,
	SVGA_3D_CMD_DX_PRED_COPY_REGION = 1178,
	SVGA_3D_CMD_DX_PRED_COPY = 1179,
	SVGA_3D_CMD_DX_PRESENTBLT = 1180,
	SVGA_3D_CMD_DX_GENMIPS = 1181,
	SVGA_3D_CMD_DX_UPDATE_SUBRESOURCE = 1182,
	SVGA_3D_CMD_DX_READBACK_SUBRESOURCE = 1183,
	SVGA_3D_CMD_DX_INVALIDATE_SUBRESOURCE = 1184,
	SVGA_3D_CMD_DX_DEFINE_SHADERRESOURCE_VIEW = 1185,
	SVGA_3D_CMD_DX_DESTROY_SHADERRESOURCE_VIEW = 1186,
	SVGA_3D_CMD_DX_DEFINE_RENDERTARGET_VIEW = 1187,
	SVGA_3D_CMD_DX_DESTROY_RENDERTARGET_VIEW = 1188,
	SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW = 1189,
	SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_VIEW = 1190,
	SVGA_3D_CMD_DX_DEFINE_ELEMENTLAYOUT = 1191,
	SVGA_3D_CMD_DX_DESTROY_ELEMENTLAYOUT = 1192,
	SVGA_3D_CMD_DX_DEFINE_BLEND_STATE = 1193,
	SVGA_3D_CMD_DX_DESTROY_BLEND_STATE = 1194,
	SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_STATE = 1195,
	SVGA_3D_CMD_DX_DESTROY_DEPTHSTENCIL_STATE = 1196,
	SVGA_3D_CMD_DX_DEFINE_RASTERIZER_STATE = 1197,
	SVGA_3D_CMD_DX_DESTROY_RASTERIZER_STATE = 1198,
	SVGA_3D_CMD_DX_DEFINE_SAMPLER_STATE = 1199,
	SVGA_3D_CMD_DX_DESTROY_SAMPLER_STATE = 1200,
	SVGA_3D_CMD_DX_DEFINE_SHADER = 1201,
	SVGA_3D_CMD_DX_DESTROY_SHADER = 1202,
	SVGA_3D_CMD_DX_BIND_SHADER = 1203,
	SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT = 1204,
	SVGA_3D_CMD_DX_DESTROY_STREAMOUTPUT = 1205,
	SVGA_3D_CMD_DX_SET_STREAMOUTPUT = 1206,
	SVGA_3D_CMD_DX_SET_COTABLE = 1207,
	SVGA_3D_CMD_DX_READBACK_COTABLE = 1208,
	SVGA_3D_CMD_DX_BUFFER_COPY = 1209,
	SVGA_3D_CMD_DX_TRANSFER_FROM_BUFFER = 1210,
	SVGA_3D_CMD_DX_SURFACE_COPY_AND_READBACK = 1211,
	SVGA_3D_CMD_DX_MOVE_QUERY = 1212,
	SVGA_3D_CMD_DX_BIND_ALL_QUERY = 1213,
	SVGA_3D_CMD_DX_READBACK_ALL_QUERY = 1214,
	SVGA_3D_CMD_DX_PRED_TRANSFER_FROM_BUFFER = 1215,
	SVGA_3D_CMD_DX_MOB_FENCE_64 = 1216,
	SVGA_3D_CMD_DX_BIND_ALL_SHADER = 1217,
	SVGA_3D_CMD_DX_HINT = 1218,
	SVGA_3D_CMD_DX_BUFFER_UPDATE = 1219,
	SVGA_3D_CMD_DX_SET_VS_CONSTANT_BUFFER_OFFSET = 1220,
	SVGA_3D_CMD_DX_SET_PS_CONSTANT_BUFFER_OFFSET = 1221,
	SVGA_3D_CMD_DX_SET_GS_CONSTANT_BUFFER_OFFSET = 1222,
	SVGA_3D_CMD_DX_SET_HS_CONSTANT_BUFFER_OFFSET = 1223,
	SVGA_3D_CMD_DX_SET_DS_CONSTANT_BUFFER_OFFSET = 1224,
	SVGA_3D_CMD_DX_SET_CS_CONSTANT_BUFFER_OFFSET = 1225,

	SVGA_3D_CMD_DX_COND_BIND_ALL_SHADER = 1226,
	SVGA_3D_CMD_DX_MAX = 1227,

	SVGA_3D_CMD_SCREEN_COPY = 1227,

	SVGA_3D_CMD_RESERVED1 = 1228,
	SVGA_3D_CMD_RESERVED2 = 1229,
	SVGA_3D_CMD_RESERVED3 = 1230,
	SVGA_3D_CMD_RESERVED4 = 1231,
	SVGA_3D_CMD_RESERVED5 = 1232,
	SVGA_3D_CMD_RESERVED6 = 1233,
	SVGA_3D_CMD_RESERVED7 = 1234,
	SVGA_3D_CMD_RESERVED8 = 1235,

	SVGA_3D_CMD_GROW_OTABLE = 1236,
	SVGA_3D_CMD_DX_GROW_COTABLE = 1237,
	SVGA_3D_CMD_INTRA_SURFACE_COPY = 1238,

	SVGA_3D_CMD_DEFINE_GB_SURFACE_V3 = 1239,

	SVGA_3D_CMD_DX_RESOLVE_COPY = 1240,
	SVGA_3D_CMD_DX_PRED_RESOLVE_COPY = 1241,
	SVGA_3D_CMD_DX_PRED_CONVERT_REGION = 1242,
	SVGA_3D_CMD_DX_PRED_CONVERT = 1243,
	SVGA_3D_CMD_WHOLE_SURFACE_COPY = 1244,

	SVGA_3D_CMD_DX_DEFINE_UA_VIEW = 1245,
	SVGA_3D_CMD_DX_DESTROY_UA_VIEW = 1246,
	SVGA_3D_CMD_DX_CLEAR_UA_VIEW_UINT = 1247,
	SVGA_3D_CMD_DX_CLEAR_UA_VIEW_FLOAT = 1248,
	SVGA_3D_CMD_DX_COPY_STRUCTURE_COUNT = 1249,
	SVGA_3D_CMD_DX_SET_UA_VIEWS = 1250,

	SVGA_3D_CMD_DX_DRAW_INDEXED_INSTANCED_INDIRECT = 1251,
	SVGA_3D_CMD_DX_DRAW_INSTANCED_INDIRECT = 1252,
	SVGA_3D_CMD_DX_DISPATCH = 1253,
	SVGA_3D_CMD_DX_DISPATCH_INDIRECT = 1254,

	SVGA_3D_CMD_WRITE_ZERO_SURFACE = 1255,
	SVGA_3D_CMD_UPDATE_ZERO_SURFACE = 1256,
	SVGA_3D_CMD_DX_TRANSFER_TO_BUFFER = 1257,
	SVGA_3D_CMD_DX_SET_STRUCTURE_COUNT = 1258,

	SVGA_3D_CMD_LOGICOPS_BITBLT = 1259,
	SVGA_3D_CMD_LOGICOPS_TRANSBLT = 1260,
	SVGA_3D_CMD_LOGICOPS_STRETCHBLT = 1261,
	SVGA_3D_CMD_LOGICOPS_COLORFILL = 1262,
	SVGA_3D_CMD_LOGICOPS_ALPHABLEND = 1263,
	SVGA_3D_CMD_LOGICOPS_CLEARTYPEBLEND = 1264,

	SVGA_3D_CMD_DX_COPY_COTABLE_INTO_MOB = 1265,

	SVGA_3D_CMD_UPDATE_GB_SCREENTARGET_V2 = 1266,

	SVGA_3D_CMD_DEFINE_GB_SURFACE_V4 = 1267,
	SVGA_3D_CMD_DX_SET_CS_UA_VIEWS = 1268,
	SVGA_3D_CMD_DX_SET_MIN_LOD = 1269,

	SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIL_VIEW_V2 = 1272,
	SVGA_3D_CMD_DX_DEFINE_STREAMOUTPUT_WITH_MOB = 1273,
	SVGA_3D_CMD_DX_SET_SHADER_IFACE = 1274,
	SVGA_3D_CMD_DX_BIND_STREAMOUTPUT = 1275,
	SVGA_3D_CMD_SURFACE_STRETCHBLT_NON_MS_TO_MS = 1276,
	SVGA_3D_CMD_DX_BIND_SHADER_IFACE = 1277,

	SVGA_3D_CMD_UPDATE_GB_SCREENTARGET_MOVE = 1278,

	SVGA_3D_CMD_DX_PRED_STAGING_COPY = 1281,
	SVGA_3D_CMD_DX_STAGING_COPY = 1282,
	SVGA_3D_CMD_DX_PRED_STAGING_COPY_REGION = 1283,
	SVGA_3D_CMD_DX_SET_VERTEX_BUFFERS_V2 = 1284,
	SVGA_3D_CMD_DX_SET_INDEX_BUFFER_V2 = 1285,
	SVGA_3D_CMD_DX_SET_VERTEX_BUFFERS_OFFSET_AND_SIZE = 1286,
	SVGA_3D_CMD_DX_SET_INDEX_BUFFER_OFFSET_AND_SIZE = 1287,
	SVGA_3D_CMD_DX_DEFINE_RASTERIZER_STATE_V2 = 1288,
	SVGA_3D_CMD_DX_PRED_STAGING_CONVERT_REGION = 1289,
	SVGA_3D_CMD_DX_PRED_STAGING_CONVERT = 1290,
	SVGA_3D_CMD_DX_STAGING_BUFFER_COPY = 1291,

	SVGA_3D_CMD_MAX = 1303,
	SVGA_3D_CMD_FUTURE_MAX = 3000
} SVGAFifo3dCmdId;

#define SVGA_NUM_3D_CMD (SVGA_3D_CMD_MAX - SVGA_3D_CMD_BASE)

#pragma pack(push, 1)
typedef struct {
	uint32_t id;
	uint32_t size;
} SVGA3dCmdHeader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t numMipLevels;
} SVGA3dSurfaceFace;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
	SVGA3dSurface1Flags surfaceFlags;
	SVGA3dSurfaceFormat format;

	SVGA3dSurfaceFace face[SVGA3D_MAX_SURFACE_FACES];

} SVGA3dCmdDefineSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
	SVGA3dSurface1Flags surfaceFlags;
	SVGA3dSurfaceFormat format;

	SVGA3dSurfaceFace face[SVGA3D_MAX_SURFACE_FACES];
	uint32_t multisampleCount;
	SVGA3dTextureFilter autogenFilter;

} SVGA3dCmdDefineSurface_v2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
} SVGA3dCmdDestroySurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
} SVGA3dCmdDefineContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
} SVGA3dCmdDestroyContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dClearFlag clearFlag;
	uint32_t color;
	float depth;
	uint32_t stencil;

} SVGA3dCmdClear;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dLightType type;
	SVGA3dBool inWorldSpace;
	float diffuse[4];
	float specular[4];
	float ambient[4];
	float position[4];
	float direction[4];
	float range;
	float falloff;
	float attenuation0;
	float attenuation1;
	float attenuation2;
	float theta;
	float phi;
} SVGA3dLightData;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;

} SVGA3dCmdPresent;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dRenderStateName state;
	union {
		uint32_t uintValue;
		float floatValue;
	};
} SVGA3dRenderState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;

} SVGA3dCmdSetRenderState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dRenderTargetType type;
	SVGA3dSurfaceImageId target;
} SVGA3dCmdSetRenderTarget;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceImageId src;
	SVGA3dSurfaceImageId dest;

} SVGA3dCmdSurfaceCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceImageId surface;
	SVGA3dCopyBox box;
} SVGA3dCmdIntraSurfaceCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t srcSid;
	uint32_t destSid;
} SVGA3dCmdWholeSurfaceCopy;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceImageId src;
	SVGA3dSurfaceImageId dest;
	SVGA3dBox boxSrc;
	SVGA3dBox boxDest;
} SVGA3dCmdSurfaceStretchBltNonMSToMS;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceImageId src;
	SVGA3dSurfaceImageId dest;
	SVGA3dBox boxSrc;
	SVGA3dBox boxDest;
	SVGA3dStretchBltMode mode;
} SVGA3dCmdSurfaceStretchBlt;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t discard : 1;

	uint32_t unsynchronized : 1;

	uint32_t reserved : 30;
} SVGA3dSurfaceDMAFlags;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGAGuestImage guest;
	SVGA3dSurfaceImageId host;
	SVGA3dTransferType transfer;

} SVGA3dCmdSurfaceDMA;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t suffixSize;

	uint32_t maximumOffset;

	SVGA3dSurfaceDMAFlags flags;
} SVGA3dCmdSurfaceDMASuffix;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t first;
	uint32_t last;
} SVGA3dArrayRangeHint;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t surfaceId;
	uint32_t offset;
	uint32_t stride;
} SVGA3dArray;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dDeclType type;
	SVGA3dDeclMethod method;
	SVGA3dDeclUsage usage;
	uint32_t usageIndex;
} SVGA3dVertexArrayIdentity;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dVertexDecl {
	SVGA3dVertexArrayIdentity identity;
	SVGA3dArray array;
	SVGA3dArrayRangeHint rangeHint;
} SVGA3dVertexDecl;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dPrimitiveRange {
	SVGA3dPrimitiveType primType;
	uint32_t primitiveCount;

	SVGA3dArray indexArray;
	uint32_t indexWidth;

	uint32_t indexBias;
} SVGA3dPrimitiveRange;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t numVertexDecls;
	uint32_t numRanges;

} SVGA3dCmdDrawPrimitives;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;

	uint32_t primitiveCount;
	uint32_t startVertexLocation;

	uint8_t primitiveType;
	uint8_t padding[3];
} SVGA3dCmdDraw;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;

	uint8_t primitiveType;

	uint32_t indexBufferSid;
	uint32_t indexBufferOffset;

	uint8_t indexBufferStride;

	uint32_t baseVertexLocation;

	uint32_t primitiveCount;
	uint32_t pad0;
	uint16_t pad1;
} SVGA3dCmdDrawIndexed;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint16_t streamOffset;
	uint8_t stream;
	uint8_t type;
	uint8_t method;
	uint8_t usage;
	uint8_t usageIndex;
	uint8_t padding;

} SVGA3dVertexElement;
#pragma pack(pop)

#define SVGA3D_VERTEX_ELEMENT_RESPECT_STREAM (1 << 7)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;

	uint32_t numElements;

} SVGA3dCmdSetVertexDecls;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
	uint32_t stride;
	uint32_t offset;
} SVGA3dVertexStream;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;

	uint32_t numStreams;

} SVGA3dCmdSetVertexStreams;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t numDivisors;
} SVGA3dCmdSetVertexDivisors;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t stage;
	SVGA3dTextureStateName name;
	union {
		uint32_t value;
		float floatValue;
	};
} SVGA3dTextureState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;

} SVGA3dCmdSetTextureState;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dTransformType type;
	float matrix[16];
} SVGA3dCmdSetTransform;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	float min;
	float max;
} SVGA3dZRange;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dZRange zRange;
} SVGA3dCmdSetZRange;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
} SVGA3dMaterial;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dFace face;
	SVGA3dMaterial material;
} SVGA3dCmdSetMaterial;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t index;
	SVGA3dLightData data;
} SVGA3dCmdSetLightData;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t index;
	uint32_t enabled;
} SVGA3dCmdSetLightEnabled;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dRect rect;
} SVGA3dCmdSetViewport;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dRect rect;
} SVGA3dCmdSetScissorRect;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t index;
	float plane[4];
} SVGA3dCmdSetClipPlane;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t shid;
	SVGA3dShaderType type;

} SVGA3dCmdDefineShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t shid;
	SVGA3dShaderType type;
} SVGA3dCmdDestroyShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t reg;
	SVGA3dShaderType type;
	SVGA3dShaderConstType ctype;
	uint32_t values[4];

} SVGA3dCmdSetShaderConst;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dShaderType type;
	uint32_t shid;
} SVGA3dCmdSetShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dQueryType type;
} SVGA3dCmdBeginQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dQueryType type;
	SVGAGuestPtr guestResult;
} SVGA3dCmdEndQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dQueryType type;
	SVGAGuestPtr guestResult;
} SVGA3dCmdWaitForQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t totalSize;
	SVGA3dQueryState state;
	union {
		uint32_t result32;
		uint32_t queryCookie;
	};
} SVGA3dQueryResult;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceImageId srcImage;
	SVGASignedRect srcRect;
	uint32_t destScreenId;
	SVGASignedRect destRect;

} SVGA3dCmdBlitSurfaceToScreen;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
	SVGA3dTextureFilter filter;
} SVGA3dCmdGenerateMipmaps;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
} SVGA3dCmdActivateSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
} SVGA3dCmdDeactivateSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdScreenDMA {
	uint32_t screenId;
	SVGAGuestImage refBuffer;
	SVGAGuestImage destBuffer;
	SVGAGuestImage changeMap;
} SVGA3dCmdScreenDMA;
#pragma pack(pop)

#define SVGA3D_LOTRANSBLT_HONORALPHA (0x01)
#define SVGA3D_LOSTRETCHBLT_MIRRORX (0x01)
#define SVGA3D_LOSTRETCHBLT_MIRRORY (0x02)
#define SVGA3D_LOALPHABLEND_SRCHASALPHA (0x01)

#pragma pack(push, 1)
typedef struct SVGA3dCmdLogicOpsBitBlt {
	SVGA3dSurfaceImageId src;
	SVGA3dSurfaceImageId dst;
	SVGA3dLogicOp logicOp;
	SVGA3dLogicOpRop3 logicOpRop3;

} SVGA3dCmdLogicOpsBitBlt;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdLogicOpsTransBlt {
	SVGA3dSurfaceImageId src;
	SVGA3dSurfaceImageId dst;
	uint32_t color;
	uint32_t flags;
	SVGA3dBox srcBox;
	SVGA3dSignedBox dstBox;
	SVGA3dBox clipBox;
} SVGA3dCmdLogicOpsTransBlt;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdLogicOpsStretchBlt {
	SVGA3dSurfaceImageId src;
	SVGA3dSurfaceImageId dst;
	uint16_t mode;
	uint16_t flags;
	SVGA3dBox srcBox;
	SVGA3dSignedBox dstBox;
	SVGA3dBox clipBox;
} SVGA3dCmdLogicOpsStretchBlt;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdLogicOpsColorFill {
	SVGA3dSurfaceImageId dst;
	uint32_t color;
	SVGA3dLogicOp logicOp;
	SVGA3dLogicOpRop3 logicOpRop3;

} SVGA3dCmdLogicOpsColorFill;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdLogicOpsAlphaBlend {
	SVGA3dSurfaceImageId src;
	SVGA3dSurfaceImageId dst;
	uint32_t alphaVal;
	uint32_t flags;
	SVGA3dBox srcBox;
	SVGA3dSignedBox dstBox;
	SVGA3dBox clipBox;
} SVGA3dCmdLogicOpsAlphaBlend;
#pragma pack(pop)

#define SVGA3D_CLEARTYPE_INVALID_GAMMA_INDEX 0xFFFFFFFF

#define SVGA3D_CLEARTYPE_GAMMA_WIDTH 512
#define SVGA3D_CLEARTYPE_GAMMA_HEIGHT 16

#pragma pack(push, 1)
typedef struct SVGA3dCmdLogicOpsClearTypeBlend {
	SVGA3dSurfaceImageId tmp;
	SVGA3dSurfaceImageId dst;
	SVGA3dSurfaceImageId gammaSurf;
	SVGA3dSurfaceImageId alphaSurf;
	uint32_t gamma;
	uint32_t color;
	uint32_t color2;
	uint32_t alphaOffsetX;
	uint32_t alphaOffsetY;

} SVGA3dCmdLogicOpsClearTypeBlend;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGAMobFormat ptDepth;
	uint32_t sizeInBytes;
	uint64_t base;
} SVGAOTableMobEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceFormat format;
	SVGA3dSurface1Flags surface1Flags;
	uint32_t numMipLevels;
	uint32_t multisampleCount;
	SVGA3dTextureFilter autogenFilter;
	SVGA3dSize size;
	SVGAMobId mobid;
	uint32_t arraySize;
	uint32_t mobPitch;
	SVGA3dSurface2Flags surface2Flags;
	uint8_t multisamplePattern;
	uint8_t qualityLevel;
	uint16_t bufferByteStride;
	float minLOD;
	uint32_t pad0[2];
} SVGAOTableSurfaceEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGAMobId mobid;
} SVGAOTableContextEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGA3dShaderType type;
	uint32_t sizeInBytes;
	uint32_t offsetInBytes;
	SVGAMobId mobid;
} SVGAOTableShaderEntry;
#pragma pack(pop)

#define SVGA_STFLAG_PRIMARY (1 << 0)
#define SVGA_STFLAG_RESERVED (1 << 1)
typedef uint32_t SVGAScreenTargetFlags;

#pragma pack(push, 1)
typedef struct {
	SVGA3dSurfaceImageId image;
	uint32_t width;
	uint32_t height;
	uint32_t xRoot;
	uint32_t yRoot;
	SVGAScreenTargetFlags flags;
	uint32_t dpi;
	uint32_t pad[7];
} SVGAOTableScreenTargetEntry;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	float value[4];
} SVGA3dShaderConstFloat;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t value[4];
} SVGA3dShaderConstInt;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t value;
} SVGA3dShaderConstBool;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint16_t streamOffset;
	uint8_t stream;
	uint8_t type;
	uint8_t methodUsage;
	uint8_t usageIndex;
} SVGAGBVertexElement;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
	uint16_t stride;
	uint32_t offset;
} SVGAGBVertexStream;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct {
	SVGA3dRect viewport;
	SVGA3dRect scissorRect;
	SVGA3dZRange zRange;

	SVGA3dSurfaceImageId renderTargets[SVGA3D_RT_MAX];
	SVGAGBVertexElement decl1[4];

	uint32_t renderStates[SVGA3D_RS_MAX];
	SVGAGBVertexElement decl2[18];
	uint32_t pad0[2];

	struct {
		SVGA3dFace face;
		SVGA3dMaterial material;
	} material;

	float clipPlanes[SVGA3D_MAX_CLIP_PLANES][4];
	float matrices[SVGA3D_TRANSFORM_MAX][16];

	SVGA3dBool lightEnabled[SVGA3D_NUM_LIGHTS];
	SVGA3dLightData lightData[SVGA3D_NUM_LIGHTS];

	uint32_t shaders[SVGA3D_NUM_SHADERTYPE_PREDX];
	SVGAGBVertexElement decl3[10];
	uint32_t pad1[3];

	uint32_t occQueryActive;
	uint32_t occQueryValue;

	SVGA3dShaderConstInt pShaderIValues[SVGA3D_CONSTINTREG_MAX];
	SVGA3dShaderConstInt vShaderIValues[SVGA3D_CONSTINTREG_MAX];
	uint16_t pShaderBValues;
	uint16_t vShaderBValues;

	SVGAGBVertexStream streams[SVGA3D_MAX_VERTEX_ARRAYS];
	SVGA3dVertexDivisor divisors[SVGA3D_MAX_VERTEX_ARRAYS];
	uint32_t numVertexDecls;
	uint32_t numVertexStreams;
	uint32_t numVertexDivisors;
	uint32_t pad2[30];

	uint32_t tsColorKey[SVGA3D_NUM_TEXTURE_UNITS];
	uint32_t textureStages[SVGA3D_NUM_TEXTURE_UNITS][SVGA3D_TS_CONSTANT + 1];
	uint32_t tsColorKeyEnable[SVGA3D_NUM_TEXTURE_UNITS];

	SVGA3dShaderConstFloat pShaderFValues[SVGA3D_CONSTREG_MAX];
	SVGA3dShaderConstFloat vShaderFValues[SVGA3D_CONSTREG_MAX];
} SVGAGBContextData;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGAOTableType type;
	uint64_t baseAddress;
	uint32_t sizeInBytes;
	uint32_t validSizeInBytes;
	SVGAMobFormat ptDepth;
} SVGA3dCmdSetOTableBase;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGAOTableType type;
	uint64_t baseAddress;
	uint32_t sizeInBytes;
	uint32_t validSizeInBytes;
	SVGAMobFormat ptDepth;
} SVGA3dCmdSetOTableBase64;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGAOTableType type;
	uint64_t baseAddress;
	uint32_t sizeInBytes;
	uint32_t validSizeInBytes;
	SVGAMobFormat ptDepth;
} SVGA3dCmdGrowOTable;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGAOTableType type;
} SVGA3dCmdReadbackOTable;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDefineGBMob {
	SVGAMobId mobid;
	SVGAMobFormat ptDepth;
	uint64_t base;
	uint32_t sizeInBytes;
} SVGA3dCmdDefineGBMob;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDestroyGBMob {
	SVGAMobId mobid;
} SVGA3dCmdDestroyGBMob;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDefineGBMob64 {
	SVGAMobId mobid;
	SVGAMobFormat ptDepth;
	uint64_t base;
	uint32_t sizeInBytes;
} SVGA3dCmdDefineGBMob64;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdRedefineGBMob64 {
	SVGAMobId mobid;
	SVGAMobFormat ptDepth;
	uint64_t base;
	uint32_t sizeInBytes;
} SVGA3dCmdRedefineGBMob64;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdUpdateGBMobMapping {
	SVGAMobId mobid;
} SVGA3dCmdUpdateGBMobMapping;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDefineGBSurface {
	uint32_t sid;
	SVGA3dSurface1Flags surfaceFlags;
	SVGA3dSurfaceFormat format;
	uint32_t numMipLevels;
	uint32_t multisampleCount;
	SVGA3dTextureFilter autogenFilter;
	SVGA3dSize size;
} SVGA3dCmdDefineGBSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDefineGBSurface_v2 {
	uint32_t sid;
	SVGA3dSurface1Flags surfaceFlags;
	SVGA3dSurfaceFormat format;
	uint32_t numMipLevels;
	uint32_t multisampleCount;
	SVGA3dTextureFilter autogenFilter;
	SVGA3dSize size;
	uint32_t arraySize;
	uint32_t pad;
} SVGA3dCmdDefineGBSurface_v2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDefineGBSurface_v3 {
	uint32_t sid;
	SVGA3dSurfaceAllFlags surfaceFlags;
	SVGA3dSurfaceFormat format;
	uint32_t numMipLevels;
	uint32_t multisampleCount;
	SVGA3dMSPattern multisamplePattern;
	SVGA3dMSQualityLevel qualityLevel;
	SVGA3dTextureFilter autogenFilter;
	SVGA3dSize size;
	uint32_t arraySize;
} SVGA3dCmdDefineGBSurface_v3;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDefineGBSurface_v4 {
	uint32_t sid;
	SVGA3dSurfaceAllFlags surfaceFlags;
	SVGA3dSurfaceFormat format;
	uint32_t numMipLevels;
	uint32_t multisampleCount;
	SVGA3dMSPattern multisamplePattern;
	SVGA3dMSQualityLevel qualityLevel;
	SVGA3dTextureFilter autogenFilter;
	SVGA3dSize size;
	uint32_t arraySize;
	uint32_t bufferByteStride;
} SVGA3dCmdDefineGBSurface_v4;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDestroyGBSurface {
	uint32_t sid;
} SVGA3dCmdDestroyGBSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdBindGBSurface {
	uint32_t sid;
	SVGAMobId mobid;
} SVGA3dCmdBindGBSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdBindGBSurfaceWithPitch {
	uint32_t sid;
	SVGAMobId mobid;
	uint32_t baseLevelPitch;
} SVGA3dCmdBindGBSurfaceWithPitch;
#pragma pack(pop)

#define SVGA3D_COND_BIND_GB_SURFACE_FLAG_READBACK (1 << 0)
#define SVGA3D_COND_BIND_GB_SURFACE_FLAG_UPDATE (1 << 1)

#pragma pack(push, 1)
typedef struct SVGA3dCmdCondBindGBSurface {
	uint32_t sid;
	SVGAMobId testMobid;
	SVGAMobId mobid;
	uint32_t flags;
} SVGA3dCmdCondBindGBSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdUpdateGBImage {
	SVGA3dSurfaceImageId image;
	SVGA3dBox box;
} SVGA3dCmdUpdateGBImage;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdUpdateGBSurface {
	uint32_t sid;
} SVGA3dCmdUpdateGBSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdReadbackGBImage {
	SVGA3dSurfaceImageId image;
} SVGA3dCmdReadbackGBImage;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdReadbackGBSurface {
	uint32_t sid;
} SVGA3dCmdReadbackGBSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdReadbackGBImagePartial {
	SVGA3dSurfaceImageId image;
	SVGA3dBox box;
	uint32_t invertBox;
} SVGA3dCmdReadbackGBImagePartial;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdInvalidateGBImage {
	SVGA3dSurfaceImageId image;
} SVGA3dCmdInvalidateGBImage;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdInvalidateGBSurface {
	uint32_t sid;
} SVGA3dCmdInvalidateGBSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdInvalidateGBImagePartial {
	SVGA3dSurfaceImageId image;
	SVGA3dBox box;
	uint32_t invertBox;
} SVGA3dCmdInvalidateGBImagePartial;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDefineGBContext {
	uint32_t cid;
} SVGA3dCmdDefineGBContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDestroyGBContext {
	uint32_t cid;
} SVGA3dCmdDestroyGBContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdBindGBContext {
	uint32_t cid;
	SVGAMobId mobid;
	uint32_t validContents;
} SVGA3dCmdBindGBContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdReadbackGBContext {
	uint32_t cid;
} SVGA3dCmdReadbackGBContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdInvalidateGBContext {
	uint32_t cid;
} SVGA3dCmdInvalidateGBContext;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDefineGBShader {
	uint32_t shid;
	SVGA3dShaderType type;
	uint32_t sizeInBytes;
} SVGA3dCmdDefineGBShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdBindGBShader {
	uint32_t shid;
	SVGAMobId mobid;
	uint32_t offsetInBytes;
} SVGA3dCmdBindGBShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdDestroyGBShader {
	uint32_t shid;
} SVGA3dCmdDestroyGBShader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	uint32_t regStart;
	SVGA3dShaderType shaderType;
	SVGA3dShaderConstType constType;

} SVGA3dCmdSetGBShaderConstInline;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dQueryType type;
} SVGA3dCmdBeginGBQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dQueryType type;
	SVGAMobId mobid;
	uint32_t offset;
} SVGA3dCmdEndGBQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t cid;
	SVGA3dQueryType type;
	SVGAMobId mobid;
	uint32_t offset;
} SVGA3dCmdWaitForGBQuery;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGAMobId mobid;
	uint32_t mustBeZero;
	uint32_t initialized;
} SVGA3dCmdEnableGart;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	SVGAMobId mobid;
	uint32_t gartOffset;
} SVGA3dCmdMapMobIntoGart;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t gartOffset;
	uint32_t numPages;
} SVGA3dCmdUnmapGartRange;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t stid;
	uint32_t width;
	uint32_t height;
	uint32_t xRoot;
	uint32_t yRoot;
	SVGAScreenTargetFlags flags;

	uint32_t dpi;
} SVGA3dCmdDefineGBScreenTarget;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t stid;
} SVGA3dCmdDestroyGBScreenTarget;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t stid;
	SVGA3dSurfaceImageId image;
} SVGA3dCmdBindGBScreenTarget;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t stid;
	SVGA3dRect rect;
} SVGA3dCmdUpdateGBScreenTarget;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t stid;
	SVGA3dRect rect;
	SVGA3dFrameUpdateType type;
} SVGA3dCmdUpdateGBScreenTarget_v2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t stid;
	SVGA3dRect rect;
	SVGA3dFrameUpdateType type;
	SVGAUnsignedPoint srcPoint;
} SVGA3dCmdUpdateGBScreenTargetMove;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SVGA3dCmdGBScreenDMA {
	uint32_t screenId;
	uint32_t dead;
	SVGAMobId destMobID;
	uint32_t destPitch;
	SVGAMobId changeMapMobID;
} SVGA3dCmdGBScreenDMA;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t value;
	uint32_t mobId;
	uint32_t mobOffset;
} SVGA3dCmdGBMobFence;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t stid;
	SVGA3dSurfaceImageId dest;

	uint32_t statusMobId;
	uint32_t statusMobOffset;

	uint32_t mustBeInvalidId;
	uint32_t mustBeZero;
} SVGA3dCmdScreenCopy;
#pragma pack(pop)

#define SVGA_SCREEN_COPY_STATUS_FAILURE 0x00
#define SVGA_SCREEN_COPY_STATUS_SUCCESS 0x01
#define SVGA_SCREEN_COPY_STATUS_INVALID 0xFFFFFFFF

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
} SVGA3dCmdWriteZeroSurface;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t sid;
} SVGA3dCmdUpdateZeroSurface;
#pragma pack(pop)

#endif