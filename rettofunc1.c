#include <stdio.h>
#include "body.h"

char *testname = "Return to function (strcpy)";

char overflow[] = "xxxxxxxxxxxx";

void doit( void )
{
	char buf[4];

	/* Copy the address of sploitworked() function in the overflow array */
	*((unsigned long *)(overflow + 8)) = (unsigned long)itworked;

	strcpy( buf, overflow );
}

