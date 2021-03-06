/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2018 Farhan Khan. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef INDEX_H
#define INDEX_H 

#include <stdint.h>

/*
Header source Documentation/technical/index-format.txt
*/

struct cache_tree {
	int			entry_count;
	int			subtree_count;
	uint8_t			objectname[20];
	struct cache_tree	**subtree;
};

struct indexhdr {
	char			sig[4];		/* Always "DIRC" */
	uint32_t		version;	/* Version Number */
	uint32_t		entries;	/* Number of extensions */
};

struct indexentry {
	uint32_t		ctime_sec;
	uint32_t		ctime_nsec;
	uint32_t		mtime_sec;
	uint32_t		mtime_nsec;
	uint32_t		dev;
	uint32_t		ino;
	uint32_t		mode;
	uint32_t		uid;
	uint32_t		gid;
	uint32_t		size;
	uint8_t			sha[20];
	uint16_t		flags;
	char			name[1];
} __packed;

#define CE_EXTENDED	0x4000

struct indexextentry {
	uint32_t		ctime_sec;
	uint32_t		ctime_nsec;
	uint32_t		mtime_sec;
	uint32_t		mtime_nsec;
	uint32_t		dev;
	uint32_t		ino;
	uint32_t		mode;
	uint32_t		uid;
	uint32_t		gid;
	uint32_t		size;
	uint8_t			sha[20];
	uint16_t		flags;
	uint16_t		flags2;
	char			name[1];
};

struct indexcache {
	struct indexhdr		*indexhdrs;
	struct indexextentry	*indexextentry;
	struct cache_tree	*cache_tree;
};

struct cache_tree	*parse_index(unsigned char *indexmap, off_t indexsize);

#endif
