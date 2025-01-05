/* SPDX-License-Identifier: GPL-2.0 OR MIT */
/**********************************************************
 * Copyright 2015-2021 VMware, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************/
#ifndef VM_BASIC_TYPES_H
#define VM_BASIC_TYPES_H

#include <LouDDK.h>

typedef uint64_t uint64_t_t;

typedef bool Bool;

#define MAX_UINT64 0xFFFFFFFFFFFFFFFF
#define MAX_UINT32 0xFFFFFFFF
#define MAX_UINT16 0xFFFF

#define CONST64U(x) x##ULL

#ifndef MBYTES_SHIFT
#define MBYTES_SHIFT 20
#endif
#ifndef MBYTES_2_BYTES
#define MBYTES_2_BYTES(_nbytes) ((uint64_t)(_nbytes) << MBYTES_SHIFT)
#endif

/*
 * MKS Guest Stats types
 */

typedef struct MKSGuestStatCounter {
	atomic_t count;
} MKSGuestStatCounter;

typedef struct MKSGuestStatCounterTime {
	MKSGuestStatCounter counter;
	atomic_t selfCycles;
	atomic_t totalCycles;
} MKSGuestStatCounterTime;

/*
 * Flags for MKSGuestStatInfoEntry::flags below
 */

#define MKS_GUEST_STAT_FLAG_NONE    0
#define MKS_GUEST_STAT_FLAG_TIME    (1U << 0)

typedef __attribute__((aligned(32))) struct MKSGuestStatInfoEntry {
	union {
		const char *s;
		uint64_t u;
	} name;
	union {
		const char *s;
		uint64_t u;
	} description;
	uint64_t flags;
	union {
		MKSGuestStatCounter *counter;
		MKSGuestStatCounterTime *counterTime;
		uint64_t u;
	} stat;
} MKSGuestStatInfoEntry;

#define INVALID_PPN64       ((PPN64)0x000fffffffffffffULL)

#define MKS_GUEST_STAT_INSTANCE_DESC_LENGTH 1024
#define MKS_GUEST_STAT_INSTANCE_MAX_STATS   4096
#define MKS_GUEST_STAT_INSTANCE_MAX_STAT_PPNS        \
	(ROUND_UP64(MKS_GUEST_STAT_INSTANCE_MAX_STATS *  \
		sizeof(MKSGuestStatCounterTime), 4096))

#define MKS_GUEST_STAT_INSTANCE_MAX_INFO_PPNS        \
	(ROUND_UP64(MKS_GUEST_STAT_INSTANCE_MAX_STATS *  \
		sizeof(MKSGuestStatInfoEntry), 4096))

#define MKS_GUEST_STAT_AVERAGE_NAME_LENGTH  40

#define MKS_GUEST_STAT_INSTANCE_MAX_STRS_PPNS        \
	(ROUND_UP64(MKS_GUEST_STAT_INSTANCE_MAX_STATS *  \
		MKS_GUEST_STAT_AVERAGE_NAME_LENGTH, 4096))


/*
 * The MKSGuestStatInstanceDescriptor is used as main interface to
 * communicate guest stats back to the host code.  The guest must
 * allocate an instance of this structure at the start of a page and
 * provide the physical address to the host.  From there the host code
 * can walk this structure to find other (pinned) pages containing the
 * stats data.
 *
 * Since the MKSGuestStatInfoEntry structures contain userlevel
 * pointers, the InstanceDescriptor also contains pointers to the
 * beginning of these sections allowing the host side code to correctly
 * interpret the pointers.
 *
 * Because the host side code never acknowledges anything back to the
 * guest there is no strict requirement to maintain compatability
 * across releases.  If the interface changes the host might not be
 * able to log stats, but the guest will continue to run normally.
 */

typedef struct MKSGuestStatInstanceDescriptor {
	uint64_t reservedMBZ; /* must be zero for now. */
	uint64_t statStartVA; /* VA of the start of the stats section. */
	uint64_t strsStartVA; /* VA of the start of the strings section. */
	uint64_t statLength;  /* length of the stats section in bytes. */
	uint64_t infoLength;  /* length of the info entry section in bytes. */
	uint64_t strsLength;  /* length of the strings section in bytes. */
	uint64_t  statPPNs[MKS_GUEST_STAT_INSTANCE_MAX_STAT_PPNS]; /* stat counters */
	uint64_t  infoPPNs[MKS_GUEST_STAT_INSTANCE_MAX_INFO_PPNS]; /* stat info */
	uint64_t  strsPPNs[MKS_GUEST_STAT_INSTANCE_MAX_STRS_PPNS]; /* strings */
	char   description[MKS_GUEST_STAT_INSTANCE_DESC_LENGTH];
} MKSGuestStatInstanceDescriptor;

#endif