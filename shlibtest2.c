/* shlibtest2.c - Shared library used by the shared library tests.
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include "shellcode.h"

char shbss2[4096];

char shdata2[4096] = SHELLCODE_RETURN_ARRAY;

/* A function which does nothing, it only exists so it can be referenced */
int shlibtest2( void )
{
	return 1;
}
