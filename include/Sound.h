#ifndef _LOUSINE_SOUND_H
#define _LOUSINE_SOUND_H
#ifdef __cplusplus
extern "C" {
#endif

#define AES_IEC958_STATUS_SIZE  24

typedef struct _SOUND_AES_IEC958{
    UINT8   Status[AES_IEC958_STATUS_SIZE];
    UINT8   SubCode[147];
    UINT8   Padding;
    UINT8   DigSubFrame;
}SOUND_AES_IEC958, * PSOUND_AES_IEC958;

#ifdef __cplusplus
}
#endif
#endif