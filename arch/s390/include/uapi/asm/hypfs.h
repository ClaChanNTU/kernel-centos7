/*
 * Structures for hypfs interface
 *
 * Copyright IBM Corp. 2013
 *
 * Author: Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef _ASM_HYPFS_H
#define _ASM_HYPFS_H

#include <linux/types.h>

/*
 * Structures for binary interface /sys/kernel/debug/diag_0c
 */
struct hypfs_diag0c_hdr {
	__u64	len;		/* Length of diag0c buffer without header */
	__u16	version;	/* Version of header */
	char	reserved1[6];	/* Reserved */
	char	tod_ext[16];	/* TOD clock for diag0c */
	__u64	count;		/* Number of entries (CPUs) in diag0c array */
	char	reserved2[24];	/* Reserved */
};

struct hypfs_diag0c_entry {
	char	date[8];	/* MM/DD/YY in EBCDIC */
	char	time[8];	/* HH:MM:SS in EBCDIC */
	__u64	virtcpu;	/* Virtual time consumed by the virt CPU (us) */
	__u64	totalproc;	/* Total of virtual and simulation time (us) */
	__u32	cpu;		/* Linux logical CPU number */
	__u32	reserved;	/* Align to 8 byte */
};

struct hypfs_diag0c_data {
	struct hypfs_diag0c_hdr		hdr;		/* 64 byte header */
	struct hypfs_diag0c_entry	entry[];	/* diag0c entry array */
};

#endif