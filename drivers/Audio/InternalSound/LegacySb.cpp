#include <LouDDK.h>

#define SB16_DSP_MIXER_PORT         0x224
#define SB16_DSP_MIVER_DATA_PORT    0x225
#define SB16_DSP_RESET_PORT         0x226
#define SB16_DSP_READ_PORT          0x22A
#define SB16_DSP_WRITE_PORT         0x22C
#define SB16_DSP_READ_STATUS        0x22E   //interrupt 8 bit Acknoledged on read 
#define SB16_DSP_16B_INTERRUPT_ACK  0x22F


LOUDDK_API_ENTRY
void CheckForSoundblaster16(){

}