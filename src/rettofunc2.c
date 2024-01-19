/* rettofunc2.c - Tests whether return to function exploits using memcpy() work
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <string.h>
#include "body.h"
#include "paxtest.h"

const char testname[] = "Return to function (memcpy)              ";

static const fptr overflow[32] = {
	itworked, itworked, itworked, itworked, itworked, itworked, itworked, itworked,
	itworked, itworked, itworked, itworked, itworked, itworked, itworked, itworked,
	itworked, itworked, itworked, itworked, itworked, itworked, itworked, itworked,
	itworked, itworked, itworked, itworked, itworked, itworked, itworked, itworked
};

void doit( void )
{
	char buf[sizeof(unsigned long)];

	forced_memcpy( buf, overflow, sizeof( overflow ) );
}
