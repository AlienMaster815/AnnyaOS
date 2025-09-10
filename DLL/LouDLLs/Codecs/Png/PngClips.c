#include "../codecs.h"
#include "png.h"

static int abs(int x) {
    return (x < 0) ? -x : x;
}

CODECS_API
HANDLE 
AnnyaCreateClipFromPng(
    HANDLE  Handle
){
    PCODECS_TYPE_QUERY Type = (PCODECS_TYPE_QUERY)Handle;
    PPNG_HANDLE PngHandle = (PPNG_HANDLE)Type->HandleInformation.ImageHandleData.PrivateDataHandle;
    PPNG_CHUNK_HEADER_HANDLE Headers = PngHandle->HeaderData; 
    PPNG_CHUNK_HEADER HeaderRaw = (PPNG_CHUNK_HEADER)Headers[0].Data;
    PPNG_CHUNK_HEADER_HANDLE UnpackedDataHandle = (PPNG_CHUNK_HEADER_HANDLE)&Headers[PngHandle->HeaderCount - 1];
    PPNG_IMAGE_CHUNK ImageHeader = (PPNG_IMAGE_CHUNK)HeaderRaw;

    if(!IS_HANDLE_SIGNATURE(HeaderRaw, PNG_IMAGE_HEADER_TYPE)){
        LouPrint("ERROR: Header is not Image Header:%s\n", &HeaderRaw->Type[0]);
        return 0x00;
    }
    if(!IS_HANDLE_SIGNATURE(UnpackedDataHandle, PNG_IMAGE_DATA_HEADER_TYPE)){
        LouPrint("ERROR: Header is not Image Header:%s\n", &UnpackedDataHandle->Type[0]);
    }
    
    PDRSD_CLIP PngClip = LouDrsdCreateClip(0, 0, ImageHeader->Width, ImageHeader->Height, 0, 0, 0 ,0);

    if ((ImageHeader->ColorType == 6) && (ImageHeader->BitDepth == 8)) {
        const size_t Width = ImageHeader->Width;
        const size_t Height = ImageHeader->Height;
        uint8_t* Decompressed = (uint8_t*)UnpackedDataHandle->Data;
        size_t RowSize = Width * 4;  // 4 bytes per pixel (RGBA)
        size_t Stride = RowSize + 1; // 1 extra byte for filter type
        size_t FullStride = Height * Stride;

        uint8_t* DecompressedCopy = LouGlobalUserMallocEx(FullStride, 8);
        if (!DecompressedCopy) {
            LouPrint("ERROR: Failed to allocate temp PNG buffer\n");
            return 0x00;
        }
        LouMemCpy(DecompressedCopy, Decompressed, FullStride);

        uint8_t* PrevRow = LouGlobalUserMallocEx(RowSize, 8); 
        if (!PrevRow) {
            LouGlobalUserFree(DecompressedCopy);
            return 0x00;
        }

        for (size_t y = 0; y < Height; y++) {
            uint8_t* Row = DecompressedCopy + y * Stride;
            uint8_t FilterType = Row[0];
            uint8_t* PixelData = Row + 1;

            switch (FilterType) {
                case 0:  // None
                    // No filtering
                    break;

                case 1:  // Sub
                    for (size_t i = 4; i < RowSize; i++) {
                        PixelData[i] = (PixelData[i] + PixelData[i - 4]) & 0xFF;
                    }
                    break;

                case 2:  // Up
                    for (size_t i = 0; i < RowSize; i++) {
                        PixelData[i] = (PixelData[i] + PrevRow[i]) & 0xFF;
                    }
                    break;

                case 3:  // Average
                    for (size_t i = 0; i < RowSize; i++) {
                        uint8_t left = (i >= 4) ? PixelData[i - 4] : 0;
                        uint8_t up = PrevRow[i];
                        PixelData[i] = (PixelData[i] + ((left + up) / 2)) & 0xFF;
                    }
                    break;

                case 4:  // Paeth
                    for (size_t i = 0; i < RowSize; i++) {
                        uint8_t left = (i >= 4) ? PixelData[i - 4] : 0;
                        uint8_t up = PrevRow[i];
                        uint8_t upLeft = (i >= 4) ? PrevRow[i - 4] : 0;

                        int p = (int)left + (int)up - (int)upLeft;
                        int pa = abs(p - (int)left);
                        int pb = abs(p - (int)up);
                        int pc = abs(p - (int)upLeft);

                        uint8_t paeth;
                        if (pa <= pb && pa <= pc)
                            paeth = left;
                        else if (pb <= pc)
                            paeth = up;
                        else
                            paeth = upLeft;

                        PixelData[i] = (PixelData[i] + paeth) & 0xFF;
                    }
                    break;

                default:
                    LouPrint("WARNING: Unknown FilterType %d, skipping row\n", FilterType);
                    continue;
            }

            // Copy pixel data to clip
            for (size_t x = 0; x < Width; x++) {
                uint8_t R = PixelData[x * 4 + 0];
                uint8_t G = PixelData[x * 4 + 1];
                uint8_t B = PixelData[x * 4 + 2];
                uint8_t A = PixelData[x * 4 + 3];

                PngClip->WindowBuffer[x + (y * Width)] = (A << 24) | (R << 16) | (G << 8) | B;
            }

            // Save current row for next iteration
            LouMemCpy(PrevRow, PixelData, RowSize);
        }

        LouGlobalUserFree(PrevRow);
        LouGlobalUserFree(DecompressedCopy);
    }
    
    LouPrint("Filter Type   :%d\n", ImageHeader->FilterMethod);
    LouPrint("Bit Depth     :%d\n", ImageHeader->BitDepth);
    LouPrint("Color Type    :%d\n", ImageHeader->ColorType);
    LouPrint("Interlace     :%d\n", ImageHeader->InterlaceMethod);

    LouPrint("AnnyaCreateClipFromPng()\n");

    return (HANDLE)PngClip;
}
