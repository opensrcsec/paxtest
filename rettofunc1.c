/* rettofunc1.c - Tests wether return to function exploits work or not.
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include "body.h"

char *testname = "Return to function (strcpy)              ";

char overflow[] = "xxxxxxxxxxxxxxxxxxxx";

void doit( void )
{
	char buf[4];

	/* Copy the address of sploitworked() function in the overflow array */
	*((unsigned long *)(overflow + 8)) = (unsigned long)itworked;
	*((unsigned long *)(overflow + 12)) = (unsigned long)itworked;
	*((unsigned long *)(overflow + 16)) = (unsigned long)itworked;

	strcpy( buf, overflow );
}

