#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "body.h"

char *testname = "Executable heap (large)    ";

void doit( void )
{
	char *buf;
	void (*func)(void);

	buf = malloc( 256*1024 );
	if( buf == NULL ) {
		fprintf( stderr, "Out of memory\n" );
		exit( 1 );
	}

	/* Put a RETN instruction in the buffer */
	*buf = '\xc3';

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))buf;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

