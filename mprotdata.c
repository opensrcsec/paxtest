/* mprotdata.c - Tests wether code in the .data segment can be executed after
 *               trying to use mprotect() to make it executable.
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable data (mprotect)               ";

char buf = '\xc3';	/* RETN instruction */

void doit( void )
{
	void (*func)(void);

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))&buf;

	/* Try to make the data executable first by using mprotect */
	do_mprotect( &buf, 1, PROT_EXEC );

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

