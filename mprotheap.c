#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable heap (mprotect) ";

void doit( void )
{
	char *buf;
	void (*func)(void);

	buf = malloc( 1 );
	if( buf == NULL ) {
		fprintf( stderr, "Out of memory\n" );
		exit( 1 );
	}

	/* Put a RETN instruction in the buffer */
	*buf = '\xc3';

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))buf;

	/* Try to make the heap executable by using mprotect */
	mprotect( buf, 1, PROT_EXEC );

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

