/* getheap.c - Get the address of the first element allocated on the heap and
 *             print it.
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
	char *p;

	p = malloc( 100 );
	if( p == NULL ) {
		perror( "getheap" );
		exit( 1 );
	}

	printf( "%0p\n", p );

	exit( 0 );
}
