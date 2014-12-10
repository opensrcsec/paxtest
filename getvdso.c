/* getshlib.c - Get the address of the maped VDSO  and print it
 *
 * Copyright (c) 2014 by Brad Spengler <spender@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	FILE *f = fopen("/proc/self/maps", "r");
	char buf[1024] = { };
	if (f == NULL)
		return 0;

	while (fgets(buf, sizeof(buf)-1, f)) {
		if (strstr(buf, "[vdso]")) {
			char *p = strchr(buf, '-');
			unsigned long val;
			*p = '\0';
			val = strtoul(buf, NULL, 16);
			printf("%p\n", val);
			fclose(f);
			return 0;
		}
	}
	fclose(f);
	return 0;
}
