

#define PNG_SIGNATURE 0x89504E470D0A1A0A

typedef struct __attribute__((packed)) _PNG_CHUNK_HEADER{
    uint32_t    Length;     //BE
    uint8_t     Type[4];    //LE
}PNG_CHUNK_HEADER, * PPNG_CHUNK_HEADER;

typedef struct _PNG_CHUNK_HEADER_HANDLE{
    uint32_t    Length;
    char        Type[5];
    uint8_t*    Data;
    bool        CompressedData;
}PNG_CHUNK_HEADER_HANDLE, * PPNG_CHUNK_HEADER_HANDLE;

#define PNG_IMAGE_HEADER_TYPE                                               "IHDR"
#define PNG_PALETTE_HEADER_TYPE                                             "PLTE"
#define PNG_IMAGE_DATA_HEADER_TYPE                                          "IDAT"
#define PNG_IMAGE_TRAILER_HEADER_TYPE                                       "IEND"
#define PNG_TRANSPARENCY_HEADER_TYPE                                        "tRNS"
#define PNG_PRIMARY_CHROMATITIES_AND_WHITE_POINT_HEADER_TYPE                "cHRM"
#define PNG_GAMMA_HEADER_TYPE                                               "gAMA"
#define PNG_EMBEDDED_ICC_PROFILE_HEADER_TYPE                                "iCCP"
#define PNG_SIGNIFICANT_BIT_HEADER_TYPE                                     "sBIT"
#define PNG_STANDARD_RGB_HEADER_TYPE                                        "sRGB"
#define PNG_CODING_INDEPENDENT_CODE_POINTS_FOR_SIGNAL_ID_HEADER_TYPE        "cICP"
#define PNG_MASTER_DISPLAY_COLOR_VOLUME                                     "mDCV"
#define PNG_CONTENT_LIGHT_LEVEL_HEADER_TYPE                                 "cLLI"
#define PNG_TEXTUAL_DATA_HEADER_TYPE                                        "tEXt"
#define PNG_COMPRESSED_TEXTUAL_DATA_HEADER_TYPE                             "zTXt"
#define PNG_INTERNATIONAL_TEXTUAL_DATA                                      "iTXt"
#define PNG_BACKGROUND_COLOR_HEADER_TYPE                                    "bKGD"
#define PNG_IMAGE_HISTOGRAM_HEADER_TYPE                                     "hIST"
#define PNG_PHYSICAL_PIXEL_DIMENSIONS_HEADER_TYPE                           "pPHY"
#define PNG_SUGGESTED_PALETTE_HEADER_TYPE                                   "sPLT"
#define PNG_EXCHANGEABLE_IMGAGE_FILE_HEADER_TYPE                            "eXIF"
#define PNG_TIME_STAMP_INFORMATION_HEADER_TPYE                              "tIME"
#define PNG_ANIMATION_CONTROL_HEADER_TYPE                                   "acTL"
#define PNG_FRAME_CONTROL_HEADER_TYPE                                       "fcTL"
#define PNG_FRAME_DATA_HEADER_TYPE                                          "fdAT"

#define PPCAWPH PPNG_PRIMARY_CHROMATIC_AND_WHITE_POINT_CHUNK
#define PPCAWPH_T PNG_PRIMARY_CHROMATITIES_AND_WHITE_POINT_HEADER_TYPE


typedef struct __attribute__((packed)) _PNG_IMAGE_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint32_t            Width; //BE
    uint32_t            Height; //BE
    uint8_t             BitDepth;
    uint8_t             ColorType;
    uint8_t             CompressionMethod;
    uint8_t             FilterMethod;
    uint8_t             InterlaceMethod;
}PNG_IMAGE_CHUNK, * PPNG_IMAGE_CHUNK;

typedef struct __attribute__((packed)) _PNG_PALETTE_DATA{
    uint8_t     Red;
    uint8_t     Green;
    uint8_t     Blue;
}PNG_PALETTE_DATA, * PPNG_PALETTE_DATA; 

typedef struct __attribute__((packed)) _PNG_PALETTE_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    PNG_PALETTE_DATA    PaletteData[];
}PNG_PALETTE_CHUNK, * PPNG_PALETTE_CHUNK;

typedef struct __attribute__((packed)) _PNG_TRANSPARENCY_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    union {
        struct __attribute__((packed)){ 
            uint16_t            GraySampleValue;
        }Type1;
        struct __attribute__((packed)){
            uint16_t            RedSampleValue;
            uint16_t            GreenSampleValue;
            uint16_t            BlueSampleValue;
        }Type2;
        struct __attribute__((packed)){
            uint8_t             AlphaPaletteData1;
            uint8_t             AlphaPaletteData[];
        }Type3;
    }ColorType;
}PNG_TRANSPARENCY_CHUNK, * PPNG_TRANSPARENCY_CHUNK;

typedef struct __attribute__((packed)) _PNG_PRIMARY_CHROMATIC_AND_WHITE_POINT_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint32_t            WhitePointX;
    uint32_t            WhitePointY;
    uint32_t            RedX;
    uint32_t            RedY;
    uint32_t            GreenX;
    uint32_t            GreenY;
    uint32_t            BlueX;
    uint32_t            BlueY;
}PNG_PRIMARY_CHROMATIC_AND_WHITE_POINT_CHUNK, * PPNG_PRIMARY_CHROMATIC_AND_WHITE_POINT_CHUNK;

typedef struct __attribute__((packed)) _PNG_GAMMA_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint32_t            ImageGamma;
}PNG_GAMMA_CHUNK, * PPNG_GAMMA_CHUNK;

typedef struct __attribute__((packed)) _PNG_EMBEDDED_ICCP_PROFILE_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint8_t             ChunkData[];
}PNG_EMBEDDED_ICCP_PROFILE_CHUNK, * PPNG_EMBEDDED_ICCP_PROFILE_CHUNK;

typedef struct __attribute__((packed)) _PNG_STANDARD_RGB_COLOR_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint8_t             RenderIntent;
}PNG_STANDARD_RGB_COLOR_CHUNK, * PPNG_STANDARD_RGB_COLOR_CHUNK;

#define PNG_SRGB_RENDER_INTENT_PERCEPTUAL               0
#define PNG_SRGB_RENDER_INTENT_RELATIVE_COLORMETRIC     1
#define PNG_SRGB_RENDER_INTENT_SATURATION               2
#define PNG_SRGB_RENDER_INTENT_ABSOLUTE_COLORMETRIC     3

typedef struct __attribute__((packed)) _PNG_CODING_INDEPENDENT_CODE_POINTS_FOR_SIGNAL_ID_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint8_t             ColorPrimatives;
    uint8_t             TransferFunction;
    uint8_t             MatrixCoefficents;
    uint8_t             VideFullRangeFlag;
}PNG_CODING_INDEPENDENT_CODE_POINTS_FOR_SIGNAL_ID_CHUNK, * PPNG_CODING_INDEPENDENT_CODE_POINTS_FOR_SIGNAL_ID_CHUNK;

typedef struct __attribute__((packed)) _PNG_TEXTUAL_DATA_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint8_t             TextData[];
}PNG_TEXTUAL_DATA_CHUNK, * PPNG_TEXTUAL_DATA_CHUNK;

typedef struct __attribute__((packed)) _PNG_COMPRESSED_TEXTUAL_DATA_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint8_t             Data[];
}PNG_COMPRESSED_TEXTUAL_DATA_CHUNK, * PPNG_COMPRESSED_TEXTUAL_DATA_CHUNK;

typedef struct __attribute__((packed)) _PNG_INTERNATIONAL_TEXTUAL_DATA_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint8_t             Data[];
}PNG_INTERNATIONAL_TEXTUAL_DATA_CHUNK, * PPNG_INTERNATIONAL_TEXTUAL_DATA_CHUNK;

typedef struct __attribute__((packed)) _PNG_BACKGROUND_COLOR_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint16_t            GreyScale;
    uint16_t            Red;
    uint16_t            Green;
    uint16_t            Blue;
    uint8_t             PaletteIndex;
}PNG_BACKGROUND_COLOR_CHUNK, * PPNG_BACKGROUND_COLOR_CHUNK;

typedef struct __attribute__((packed)) _PNG_IMAGE_HISTOGRAM{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint16_t            FrequencyBytes[];
}PNG_IMAGE_HISTOGRAM, * PPNG_IMAGE_HISTOGRAM;

typedef struct __attribute__((packed)) _PNG_PHYSICAL_PIXEL_DIMENSION{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint32_t            XPixels;
    uint32_t            YPixels;
    uint8_t             UnitSpecifier;
}PNG_PHYSICAL_PIXEL_DIMENSION, * PPNG_PHYSICAL_PIXEL_DIMENSION;

#define PNG_PHYS_UNIT_SPECIFIER_UNKOWN  0
#define PNG_PHYS_UNIT_SPECIFIER_METRIC  1

typedef struct __attribute__((packed)) _PNG_SUGGESTED_PALETTE_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint8_t             Data[];
}PNG_SUGGESTED_PALETTE_CHUNK, * PPNG_SUGGESTED_PALETTE_CHUNK;

typedef struct __attribute__((packed)) _PNG_EXCHANGEABLE_IMAGE_FILE_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint8_t             Data[];
}PNG_EXCHANGEABLE_IMAGE_FILE_CHUNK, * PPNG_EXCHANGEABLE_IMAGE_FILE_CHUNK;

typedef struct __attribute__((packed)) _PNG_TIME_STAMP_INFORMATION_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint16_t            YearStamp;
    uint8_t             MonthStamp;
    uint8_t             DayStamp;
    uint8_t             HourStamp;
    uint8_t             MinuteStamp;
    uint8_t             SecondStamp;
}PNG_TIME_STAMP_INFORMATION_CHUNK, * PPNG_TIME_STAMP_INFORMATION_CHUNK;

typedef struct __attribute__((packed)) _PNG_ANIMATION_CONTROL_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint32_t            FrameCount;
    uint32_t            Plays;
}PNG_ANIMATION_CONTROL_CHUNK, * PPNG_ANIMATION_CONTROL_CHUNK;

//TODO:fcTL + fdAT

typedef union _PNG_CHUNK{
    PNG_IMAGE_CHUNK                                             ImageChunk;
    PNG_PALETTE_CHUNK                                           PaletteChunk;
    PNG_TRANSPARENCY_CHUNK                                      TransparencyChunk;
    PNG_PRIMARY_CHROMATIC_AND_WHITE_POINT_CHUNK                 ChromaticAndWhitePointChunk;
    PNG_GAMMA_CHUNK                                             GammaChunk;
    PNG_EMBEDDED_ICCP_PROFILE_CHUNK                             EmbeddedICCChunk;
    PNG_STANDARD_RGB_COLOR_CHUNK                                StandardRGBColorChunk;
    PNG_CODING_INDEPENDENT_CODE_POINTS_FOR_SIGNAL_ID_CHUNK      CodinngIndependentCodePointsForSignalChunk;
    PNG_TEXTUAL_DATA_CHUNK                                      TextualDataChunk;
    PNG_COMPRESSED_TEXTUAL_DATA_CHUNK                           CompressedTextualDataChunk;
    PNG_INTERNATIONAL_TEXTUAL_DATA_CHUNK                        InternationalTextualDataChunk;
    PNG_BACKGROUND_COLOR_CHUNK                                  BackgroundColorChunk;
    PNG_IMAGE_HISTOGRAM                                         ImageHistogramChunk;
    PNG_PHYSICAL_PIXEL_DIMENSION                                PhysicalPixelDimensionChunk;
    PNG_SUGGESTED_PALETTE_CHUNK                                 SuggestedPaletteChunk;
    PNG_EXCHANGEABLE_IMAGE_FILE_CHUNK                           ExchangeableImageFileChunk;
    PNG_TIME_STAMP_INFORMATION_CHUNK                            TimeStampInformationChunk;
    PNG_ANIMATION_CONTROL_CHUNK                                 AnimationControlChunk;
}PNG_CHUNK, * PPNG_CHUNK;

typedef struct  _IDAT_CODECS_STREAM_UNPACKER{
    void*   CurrentIndex;
    size_t  StreamSize;
    void*   UnpackedStream;
}IDAT_CODECS_STREAM_UNPACKER, * PIDAT_CODECS_STREAM_UNPACKER;


typedef struct _PNG_HANDLE{
    string PngName;
    size_t HeaderCount;
    void*  HeaderData;
    size_t Width;
    size_t Height;
}PNG_HANDLE, * PPNG_HANDLE;


#define IS_HANDLE_SIGNATURE(Header, Signature) (strncmp((string)&((Header)->Type[0]), Signature, 4) == 0)