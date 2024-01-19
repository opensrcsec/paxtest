/* getshlib.c - Get the address of the maped VDSO  and print it
 *
 * Copyright (c) 2014 by Brad Spengler <spender@grsecurity.net>
 * Copyright (c) 2015 by Oliver Pinter <op+paxtest@hardenedbsd.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __FreeBSD__
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/elf.h>
#include <errno.h>
#include <unistd.h>

#define	PROC_AUXV_MAX	256
#define	AT_TIMEKEEP	22
#endif

int main( int argc, char *argv[] )
{
#ifdef __linux__
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
			printf("%p\n", (void *)val);
			fclose(f);
			return 0;
		}
	}
	fclose(f);
	return 0;
#elif defined(__FreeBSD__)
	Elf_Auxinfo	*aux, *auxv;
	int		name[4];
	size_t		len;
	int		ret = 0;

	name[0] = CTL_KERN;
	name[1] = KERN_PROC;
	name[2] = KERN_PROC_AUXV;
	name[3] = getpid();

	len = PROC_AUXV_MAX * sizeof(Elf_Auxinfo);
	auxv = malloc(len);
	if (auxv == NULL) {
		ret = 1;
		goto out;
	}

	if (sysctl(name, 4, auxv, &len, NULL, 0) == -1) {
		ret = 2;
		goto out;
	}

	for (aux = auxv; aux->a_type != AT_NULL; aux++) {
		if (aux->a_type == AT_TIMEKEEP) {
			printf("%p\n", aux->a_un.a_ptr);
			return 0;
		}
	}

out:
	if (auxv != NULL)
		free(auxv);
	printf("%p\n", NULL);
	return ret;
#else
#error	unsupported OS
#endif
}
