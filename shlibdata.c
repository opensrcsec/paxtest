/* shlibdata.c - Tests wether code in the .data segment of a shared library can
 *               be executed
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "body.h"

char *testname = "Executable shared library data           ";

extern char bufdata;

void doit( void )
{
	void (*func)(void);

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))&bufdata;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

