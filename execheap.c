/* execheap.c - Tests wether code in the heap can be executed
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "body.h"

char *testname = "Executable heap                          ";

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

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))buf;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

