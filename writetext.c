/* writetext.c - Test wether a .text sections can be written
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Writable text segments                   ";

extern int shlibtest( void );

void doit( void )
{
	char *buf;
	char c;

	/* Try to make the data executable first by using mprotect */
	do_mprotect( shlibtest, 1, PROT_WRITE );

	buf = (char *)shlibtest;

	/* Try to write something */
	*buf = 'X';

	/* It worked when the function returns */
	itworked();
}

