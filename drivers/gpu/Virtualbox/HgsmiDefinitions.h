#ifndef _HGSMI_DEFINITIONS_H
#define _HGSMI_DEFINITIONS_H

/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */
/* Copyright (C) 2025 Tyler Grenier */
/* Rewritten keystroke-by-keystroke by Tyler Grenier for AnnyaOS */

#define HGSMI_BUFFER_HEADER_F_SEQUENCE_BITS         0x03
#define HGSMI_BUFFER_HEADER_F_SEQUENCE_SINGLE       0
#define HGSMI_BUFFER_HEADER_F_SEQUENCE_START        1
#define HGSMI_BUFFER_HEADER_F_SEQUENCE_CONTINUE     2
#define HGSMI_BUFFER_HEADER_F_SEQUENCE_END          3

typedef struct __attribute__((packed)) _HGSMI_BUFFER_HEADER{
    uint32_t        DataSize;
    uint8_t         Flags;
    uint8_t         Channel;
    uint16_t        ChannelInformation;
    union{
        uint8_t HeaderData[8];
        struct {
            uint32_t Reserved1;
            uint32_t Reserved2;
        }Buffer;
        struct {
            uint32_t SequenceIndex;
            uint32_t SequenceSize;
        }SequenceStart;
        struct {
            uint32_t SequenceIndex;
            uint32_t SequenceOffset;
        }SequenceContinue;
    }u;
}HGSMI_BUFFER_HEADER, * PHGSMI_BUFFER_HEADER;

typedef struct __attribute__((packed)) _HGSMI_BUFFER_TAIL{
    uint32_t Reserved;
    uint32_t Checksum;
}HGSMI_BUFFER_TAIL, * PHGSMI_BUFFER_TAIL;

#define VIRTUALBOX_HGSMI_NUMBER_OF_CHANNELS 0x100

#endif//_HGSMI_DEFINITIONS_H