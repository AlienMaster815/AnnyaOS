#include <Lkrs.h>

//read and writes follow LE based encoding

void LkrsWriteUint8(char* Base, uint8_t Data){
    Base[0] = (char)Data;
}

void LkrsWriteUint16(char* Base, uint16_t Data){
    Base[0] = (char)Data & 0xFF;
    Base[1] = (char)(Data >> 8) & 0xFF;
}

void LkrsWriteUint32(char* Base, uint32_t Data){
    Base[0] = (char)(Data)          & 0xFF;
    Base[1] = (char)(Data >> 8)     & 0xFF;
    Base[2] = (char)(Data >> 16)    & 0xFF;
    Base[3] = (char)(Data >> 24)    & 0xFF;
}

void LkrsWriteUint64(char* Base, uint64_t Data){
    Base[0] = (char)(Data)          & 0xFF;
    Base[1] = (char)(Data >> 8)     & 0xFF;
    Base[2] = (char)(Data >> 16)    & 0xFF;
    Base[3] = (char)(Data >> 24)    & 0xFF;
    Base[4] = (char)(Data >> 32)    & 0xFF;
    Base[5] = (char)(Data >> 40)    & 0xFF;
    Base[6] = (char)(Data >> 48)    & 0xFF;
    Base[7] = (char)(Data >> 56)    & 0xFF;
}

void LkrsReadUint8(char* Base, uint8_t* Data){
    Data[0] = (uint8_t)Base[0];
}

void LkrsReadUint16(char* Base, uint16_t* Data){
    *Data   = (uint8_t)Base[0];
    *Data  |= (uint8_t)Base[1] << 8;
}

void LkrsReadUint32(char* Base, uint16_t* Data){
    *Data   = (uint8_t)Base[0];
    *Data  |= (uint8_t)Base[1] << 8;
    *Data  |= (uint8_t)Base[2] << 16;
    *Data  |= (uint8_t)Base[3] << 24;
}


void LkrsReadUint64(char* Base, uint64_t* Data){
    *Data   = (uint64_t)Base[0];
    *Data  |= (uint64_t)Base[1] << 8;
    *Data  |= (uint64_t)Base[2] << 16;
    *Data  |= (uint64_t)Base[3] << 24;
    *Data  |= (uint64_t)Base[4] << 32;
    *Data  |= (uint64_t)Base[5] << 40;
    *Data  |= (uint64_t)Base[6] << 48;
    *Data  |= (uint64_t)Base[7] << 56;
}