/* mprotheap.c - Tests wether code on the heap can be executed after trying to
 *               use mprotect() to make it executable.
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable heap (mprotect)               ";

void doit( void )
{
	char *buf;
	void (*func)(void);

	buf = malloc( 1 );
	if( buf == NULL ) {
		fprintf( stderr, "Out of memory\n" );
		exit( 1 );
	}

	/* Put a RETN instruction in the buffer */
	*buf = '\xc3';

	/* Try to make the buffer executable by using mprotect() */
	do_mprotect( buf, 1, PROT_EXEC );

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))buf;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

