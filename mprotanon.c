/* mprotanon.c - Tests wether code can be executed in anonymous mappings
 *               after trying to use mprotect() to make it executable.
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable anonymous mapping (mprotect)  ";

void doit( void )
{
	char *buf;
	void (*func)(void);

	buf = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if( buf == NULL ) {
		fprintf( stderr, "mmap() returned NULL\n" );
		exit( 1 );
	}

	/* Put a RETN instruction in the buffer */
	*buf = '\xc3';

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))buf;

	/* Try to make the anonymous mapping executable first by using mprotect */
	do_mprotect( &buf, 1, PROT_EXEC );

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

