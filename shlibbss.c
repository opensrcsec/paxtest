/* shlibbss.c - Tests wether code in the .bss segment of a shared library can
 *              be executed
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "body.h"

char *testname = "Executable shared library bss            ";

extern char bufbss, bufbss2;

void doit( void )
{
	fptr func;

	/* Put a RETN instruction in the buffer */
	bufbss = '\xc3';
	bufbss2 = '\xc3';

	/* Convert the pointer to a function pointer */
	func = &bufbss < &bufbss2 ? (fptr)&bufbss : (fptr)&bufbss2;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

