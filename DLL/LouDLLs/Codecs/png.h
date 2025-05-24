

#define PNG_SIGNATURE 0x89504E470D0A1A0A

typedef struct _PNG_CHUNK_HEADER{
    uint32_t    Lenth;
    uint32_t    Type;
    uint8_t     Data[];
}PNG_CHUNK_HEADER, * PPNG_CHUNK_HEADER;

