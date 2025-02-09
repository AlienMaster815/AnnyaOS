#include <LouAPI.h>



PBITMAP_HANDLE UnpackBitmap(FILE* FileToUnpack){
    PBITMAP_HANDLE MapHandle = 0x00;
    PBITMAP_FILE_HEADER BitmapFile = (PBITMAP_FILE_HEADER)FileToUnpack;
    PBITMAP_INFORMATION_HEADER BIH = (PBITMAP_INFORMATION_HEADER)((uint64_t)FileToUnpack + sizeof(BITMAP_FILE_HEADER));
    
    if(BitmapFile->BFType != 0x4D42){
        LouPrint("Error: File Is Not Bitmap Type\n");
        LouFree((RAMADD)FileToUnpack);
        return MapHandle;
    }

    FILE* NewUserAddress = LouMalloc(BitmapFile->BFSize);//, USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);

    memcpy((void*)NewUserAddress, (void*)FileToUnpack, BitmapFile->BFSize);
    LouFree((RAMADD)FileToUnpack);

    FileToUnpack = NewUserAddress;    
    BitmapFile = (PBITMAP_FILE_HEADER)FileToUnpack;
    BIH = (PBITMAP_INFORMATION_HEADER)((uint64_t)FileToUnpack + sizeof(BITMAP_FILE_HEADER));
    

    LouPrint("File Size:%h\n", BitmapFile->BFSize);
    LouPrint("Pixel Data Offset:%h\n", BitmapFile->BFOffBits);

    LouPrint("BMP Width:%d\n",  BIH->BIWidth);
    LouPrint("BMP Height:%d\n", BIH->BIHeight);
    LouPrint("BMP BPP:%d\n",    BIH->BIBpp);
    
    uint8_t* PixelData = (uint8_t*)((uint64_t)FileToUnpack + (uint64_t)BitmapFile->BFOffBits);

    LouPrint("FileToUnp:%h\n", FileToUnpack);
    LouPrint("PixelData:%h\n", PixelData);

    MapHandle = (PBITMAP_HANDLE)LouMalloc(sizeof(BITMAP_HANDLE));//, WRITEABLE_PAGE | USER_PAGE | PRESENT_PAGE);

    MapHandle->Width = BIH->BIWidth;
    MapHandle->Height = BIH->BIHeight;
    MapHandle->Bpp = BIH->BIBpp;
    MapHandle->UnpackedData = (void*)PixelData;
    MapHandle->FileHandle = FileToUnpack;
    MapHandle->FileEnd = (uint64_t)FileToUnpack + (uint64_t)BitmapFile->BFSize;
    return MapHandle;
}

PBITMAP_HANDLE LouKeOpenBitmapImage(string FilePath){
    FILE* File = fopen(FilePath);
    return UnpackBitmap(File);
}

void LouKeCloseBitmapImage(PBITMAP_HANDLE BitHandle){
    if(BitHandle->FileHandle){
        LouFree((RAMADD)BitHandle->FileHandle);
    }
    LouFree((RAMADD)BitHandle);
}
