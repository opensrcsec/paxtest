/* rettofunc2.c - Tests wether return to function exploits using memcpy() work
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <string.h>
#include "body.h"

char *testname = "Return to function (memcpy)              ";

char overflow[] = "xxxxxxxxxxxxxxxxxxxx";

void doit( void )
{
	char buf[4];

	/* Copy the address of sploitworked() function in the overflow array */
	*((unsigned long *)(overflow + 8)) = (unsigned long)itworked;
	*((unsigned long *)(overflow + 12)) = (unsigned long)itworked;
	*((unsigned long *)(overflow + 16)) = (unsigned long)itworked;

	memcpy( buf, overflow, sizeof( overflow ) );
}

