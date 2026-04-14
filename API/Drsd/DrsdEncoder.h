#ifndef _DRSD_ENCODER_INTERNAL_H
#define _DRSD_ENCODER_INTERNAL_H

static inline UINT DrsdEncoderIndex(PDRSD_ENCODER Encoder){
    return Encoder->Index;
}

static inline UINT32 DrsdEncoderMask(
    PDRSD_ENCODER   Encoder
){
    return 1 << DrsdEncoderIndex(Encoder);
}

#define DrsdForEachEncoderMask(Encoder, Device, EncoderMask) \
    ForEachListEntry((Encoder), &(Device)->ModeConfig.EncoderList, Head) \
        ForEachIf((EncoderMask) & DrsdEncoderMask(Encoder))

#endif