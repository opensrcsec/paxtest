#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "body.h"

char *testname = "Executable stack           ";

void doit( void )
{
	char buf;
	void (*func)(void);

	/* Put a RETN instruction in the buffer */
	buf = '\xc3';

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))&buf;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

