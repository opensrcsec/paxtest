/* writetext.c - Test wether a .text sections can be written
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Writable text segments                   ";

extern int shlibtest( void );

static void sigsegv( int sig )
{
	printf( "Killed\n" );
	exit( 1 );
}

void doit( void )
{
	char *buf;
	char c;

	buf = (char*)shlibtest;

	signal( SIGSEGV, sigsegv );

	/* Try to make the text writable first by using mprotect */
	do_mprotect( buf, 4096, PROT_READ|PROT_WRITE|PROT_EXEC );

	/* Try to write something */
	*buf = 'X';

	/* It worked when the function returns */
	itworked();
}

