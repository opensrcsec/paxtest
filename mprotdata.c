#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable data (mprotect) ";

char buf = '\xc3';	/* RETN instruction */

void doit( void )
{
	void (*func)(void);

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))&buf;

	/* Try to make the data executable first by using mprotect */
	mprotect( &buf, 1, PROT_EXEC );

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

