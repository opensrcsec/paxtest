/* mprotshbss.c - Tests wether code in the .bss segment of a shared library can
 *                be executed after trying to use mprotect() to make it
 *                executable.
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable shared library bss (mprotect) ";

extern char bufbss;

void doit( void )
{
	fptr func;

	/* Put a RETN instruction in the buffer */
	bufbss = '\xc3';

	/* Try to make the memory region executable by using mprotect() */
	do_mprotect( &bufbss, 1, PROT_EXEC );

	/* Convert the pointer to a function pointer */
	func = (fptr)&bufbss;

	/* Call the code in the buffer */
	func();

	do_mprotect( &bufbss, 1, PROT_READ|PROT_WRITE );

	/* It worked when the function returns */
	itworked();
}

