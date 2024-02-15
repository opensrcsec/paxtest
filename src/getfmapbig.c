/* getfmapbig.c - Get the address of a big file mapping
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * Copyright (c)2024 by Mathias Krause <minipli@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "paxtest.h"

#ifndef RUNDIR
#error RUNDIR not defined
#endif

int main(int argc, char *argv[])
{
	static const char bigfile[] = RUNDIR"/shlibtestbig.so";
	char *buf;
	int fd;

	fd = open(bigfile, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "open('%s') failed\n", bigfile);
		exit(1);
	}

	buf = mmap(NULL, HUGE_PAGE_SIZE, PROT_READ, MAP_PRIVATE, fd, 0);
	if (buf == MAP_FAILED ) {
		fprintf(stderr, "mmap() returned NULL\n");
		exit(1);
	}

	printf("%p\n", buf);

	exit(0);
}
