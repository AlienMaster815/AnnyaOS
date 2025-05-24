

#define PNG_SIGNATURE 0x89504E470D0A1A0A

typedef struct __attribute__((packed)) _PNG_CHUNK_HEADER{
    uint32_t    Length;
    uint32_t    Type;
}PNG_CHUNK_HEADER, * PPNG_CHUNK_HEADER;

typedef struct _PNG_CHUNK_HEADER_HANDLE{
    uint32_t    Length;
    char        Type[5];
    uint8_t*    Data;
}PNG_CHUNK_HEADER_HANDLE, * PPNG_CHUNK_HEADER_HANDLE;

#define PNG_IMAGE_HEADER_TYPE                                               "IHDR"
#define PNG_PALETTE_HEADER_TYPE                                             "PLTE"
#define PNG_IMAGE_DATA_HEADER_TYPE                                          "IDAT"
#define PNG_IMAGE_TRAILER_HEADER_TYPE                                       "IEND"
#define PNG_TRANSPARENCY_HEADER_TYPE                                        "tRNS"
#define PNG_PRIMARY_CHROMATITIES_AND_WHITE_POINT_HEADER_TYPE                "cHRM"
#define PNG_GAMMA_HEADER_TYPE                                               "gAMA"
#define PNG_EMBEDDED_ICC_PROFILE_HEADER_TYPE                                "ICCP"
#define PNG_SIGNIFICANT_BIT_HEADER_TYPE                                     "sBIT"
#define PNG_STANDARD_RGB_HEADER_TYPE                                        "sRGB"
#define PNG_CODING_INDEPENDENT_CODE_POINTE_FOR_SIGNAL_ID_HEADER_TYPE        "cICP"
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

typedef struct __attribute__((packed)) _PNG_IMAGE_CHUNK{
    PNG_CHUNK_HEADER    ChunkHeader;
    uint32_t            Width;
    uint32_t            Height;
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
    uint16_t    GraySampleValue;
    uint16_t    RedSampleValue;
    uint16_t    GreenSampleValue;
    uint16_t    BlueSampleValue;
    uint8_t     AlphaPaletteData[];
}PNG_TRANSPARENCY_CHUNK, * PPNG_TRANSPARENCY_CHUNK;