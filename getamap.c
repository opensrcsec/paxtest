/* getamap.c - Get the address of the first anonymous mapping
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>


int main( int argc, char *argv[] )
{
	char *buf;

	buf = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if( buf == NULL ) {
		fprintf( stderr, "mmap() returned NULL\n" );
		exit( 1 );
	}

	printf( "%0p\n", buf );

	exit( 0 );
}

