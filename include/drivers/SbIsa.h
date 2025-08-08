// Header: HeaderName.h

#ifndef _SB_ISA_H
#define _SB_ISA_H

#ifdef __cplusplus
extern "C" {
#endif

// ------------------- UNIVERSAL DATA ------------------- //
// Define shared types or macros here
// Example:
// typedef struct HeaderCommon { int CommonID; } HeaderCommon;

#if defined(_USER_MODE_CODE_)

// ------------------- USER MODE ------------------------ //
#include <Annya.h>    // User mode system includes

// --- Global user-mode data (visible across all DLLs) ---

#ifdef _MODULE_NAME
// --- Private user-mode data (specific to MODULE_NAME.DLL) ---
#else
// --- Shared user-mode data ---
#endif

#else // Kernel mode section

// ------------------- KERNEL MODE ---------------------- //
#ifdef __cplusplus
#include <LouDDK.h>
#else
#include <LouAPI.h>
#endif

#define SBISA_DSP_MIXER_COMMAND             0x0224
#define SBISA_DSP_MIXER_DATA                0x0225
#define SBISA_DSP_MIXER_RESET               0x0226
#define SBISA_DSP_READ                      0x022A
#define SBISA_DSP_WRITE                     0x022C
#define SBISA_DSP_READ_STATUS               0x022E
#define SBISA_DSP_IRQ_ACK                   0x022F

#define SBISA_COMMAND_SET_TIME_CONSTANT     0x40
#define SBISA_COMMAND_SET_OUTPUT_SAMPLE     0x41
#define SBISA_COMMAND_TURN_SPEAKER_ON       0xD1
#define SBISA_COMMAND_TURN_SPEAKER_OFF      0xD3
#define SBISA_COMMAND_STOP_PLAYING_8_BIT    0xD0
#define SBISA_COMMAND_RESUME_PLAYING_8_BIT  0xD4
#define SBISA_COMMAND_STOP_PLAYING_16_BIT   0xD5
#define SBISA_COMMAND_RESUME_PLAYING_16_BIT 0xD6
#define SBISA_COMMAND_GET_DSP_VERSION       0xE1
#define SBISA_COMMAND_SET_IRQ               0x80
#define SBISA_COMMAND_SET_VOLUME            0x22
#define SET_SB_VOLUME(L, R)     (((L & 0xF) << 4) | (R & 0xF))

#define SBISA_FOUND_DEVICE 0xAA

static inline void LouKeSbIsaWriteReset(UINT8 Data){
    outb(SBISA_DSP_MIXER_RESET, Data);
}

static inline UINT8 LouKeSbIsaReadDsp(){
    return inb(SBISA_DSP_READ);
}

#ifdef _KERNEL_MODULE_
// --- Module-specific data (MODULE_NAME.SYS) ---

#else
// --- LOUOSKRNL.EXE-specific data ---


#endif

#endif // end user vs kernel

#ifdef __cplusplus
}
#endif

#endif // HEADERNAME_H
