#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable bss (mprotect)  ";

char buf;

void doit( void )
{
	void (*func)(void);

	/* Put a RETN instruction in the buffer */
	char buf = '\xc3';

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))&buf;

	/* Try to make the bss executable first by using mprotect */
	mprotect( &buf, 1, PROT_EXEC );

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

