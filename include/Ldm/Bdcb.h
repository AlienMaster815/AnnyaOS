#ifndef _BDCB_H
#define _BDCB_H

#include <cstdint.h>

typedef enum _BDCB_CALLBACK_TYPE{
	BdCbStatusUpdate = 0,
	BdCbInitializeImage
}BDCB_CALLBACK_TYPE, * PBDCB_CALLBACK_TYPE;

typedef enum _BDCB_CLASSIFICATION{
	BdCbClassificationUnknownImage = 0,
	BdCbClassificationKnownGoodImage,
	BdCbClassificationKnownBadImage,
	BdCbClassificationKnownBadImageBootCritical,
	BdCbClassificationEnd
}BDCB_CLASSIFICATION, * PBDCB_CLASSIFICATION;

typedef enum _BDCB_STATUS_UPDATE_TYPE{
	BdCbStatusPrepareForDependencyLoad = 0,
	BdCbStatusPrepareForDriverLoad,
	BdCbStatusPrepareForUnload
}BDCB_STATUS_UPDATE_TYPE, * PBDCB_STATUS_UPDATE_TYPE;

typedef struct _BDCB_IMAGE_INFORMATION{
	BDCB_CLASSIFICATION Classification;
	ULONG               ImageFlags;
	UNICODE_STRING      ImageName;
	UNICODE_STRING      RegistryPath;
	UNICODE_STRING      CertificatePublisher;
	UNICODE_STRING      CertificateIssuer;
	PVOID               ImageHash;
	PVOID               CertificateThumbprint;
	ULONG               ImageHashAlgorithm;
	ULONG               ThumbprintHashAlgorithm;
	ULONG               ImageHashLength;
	ULONG               CertificateThumbprintLength;
}BDCB_IMAGE_INFORMATION, * PBDCB_IMAGE_INFORMATION;

typedef struct _BDCB_STATUS_UPDATE_CONTEXT{
	BDCB_STATUS_UPDATE_TYPE StatusType;
}BDCB_STATUS_UPDATE_CONTEXT, * PBDCB_STATUS_UPDATE_CONTEXT;

#endif