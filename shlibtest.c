/* shlibtest.c - Shared library used by the shared library tests.
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

char bufbss;

char bufdata = '\xc3';

/* A function which does nothing, it only exists so it can be referenced */
int shlibtest( void )
{
	return 1;
}
