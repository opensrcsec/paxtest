#include <stdio.h>
#include <string.h>
#include "body.h"

char *testname = "Return to function (memcpy)";

char overflow[] = "xxxxxxxxxxxx";

void doit( void )
{
	char buf[4];

	/* Copy the address of sploitworked() function in the overflow array */
	*((unsigned long *)(overflow + 8)) = (unsigned long)itworked;

	memcpy( buf, overflow, 13 );
}

