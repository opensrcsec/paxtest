/* getshlibbig.c - Get the address of a function in a big shared library and
 * print it
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * Copyright (c)2024 by Mathias Krause <minipli@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
	static const char libname[] = "shlibtestbig.so";
	static const char symname[] = "big_nop";
	void *handle, *sym;

	handle = dlopen(libname, RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "failed to load shared library '%s': %s\n", libname,
		        dlerror() ?: "unknown error");
		exit(1);
	}

	dlerror(); /* clear any errors */
	sym = dlsym(handle, symname);
	if (sym == NULL) {
		fprintf(stderr, "symbol %s not found in %s: %s\n", symname, libname,
		        dlerror() ?: "unknown error");
		exit(1);
	}

	printf("%p\n", sym);
	dlclose(handle);

	return 0;
}
