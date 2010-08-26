/* mprotheap.c - Tests whether code on the heap can be executed after trying to
 *               use mprotect() to make it executable.
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"
#include "shellcode.h"

const char testname[] = "Executable heap (mprotect)               ";

void doit( void )
{
	char *buf;
	fptr func;

	buf = malloc( MAX_SHELLCODE_LEN );
	if( buf == NULL ) {
		fprintf( stderr, "Out of memory\n" );
		exit( 1 );
	}

	copy_shellcode(buf, SHELLCODE_RETURN);

	/* Try to make the buffer executable by using mprotect() */
	/* Due to a FreeBSD bug PROT_READ is required */
	do_mprotect( buf, SIZE_OF_SHELLCODE_RETURN, PROT_READ|PROT_EXEC );

	/* Convert the pointer to a function pointer */
	func = (fptr)buf;

	/* Call the code in the buffer */
	func();

	do_mprotect( buf, MAX_SHELLCODE_LEN, PROT_READ|PROT_WRITE );

	/* It worked when the function returns */
	itworked();
}
