#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "body.h"

char *testname = "Executable data            ";

char buf = '\xc3';	/* RETN instruction */

void doit( void )
{
	void (*func)(void);

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))&buf;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

