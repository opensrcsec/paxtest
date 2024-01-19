/* shlibtest.c - Shared library used by the shared library tests.
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include "paxtest.h"

char shbss[PAGE_SIZE_MAX] __pagealigned;

char shdata[PAGE_SIZE_MAX] __pagealigned = { 'A' };

/* A function which does nothing, it only exists so it can be referenced */
int shlibtest( void )
{
	return 1;
}
