/* mprotbss.c - Tests wether code in the .bss segment can be executed after
 *              trying to use mprotect() to make it executable
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable bss (mprotect)                ";

char buf;

void doit( void )
{
	void (*func)(void);

	/* Put a RETN instruction in the buffer */
	buf = '\xc3';

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))&buf;

	/* Try to make the bss executable first by using mprotect */
	do_mprotect( &buf, 1, PROT_EXEC );

	/* Call the code in the buffer */
	func();

	do_mprotect( &buf, 1, PROT_READ|PROT_WRITE );

	/* It worked when the function returns */
	itworked();
}

