/* shlibdata.c - Tests wether code in the .data segment of a shared library can
 *               be executed
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "body.h"

char *testname = "Executable shared library data           ";

extern char bufdata, bufdata2;

void doit( void )
{
	fptr func;

	/* Convert the pointer to a function pointer */
	func = &bufdata < &bufdata2 ? (fptr)&bufdata : (fptr)&bufdata2;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

