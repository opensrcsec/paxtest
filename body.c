/* body.c - This part shared by the test programs (except for the randomisation
 *          tests)
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#ifndef PAGESIZE
#define PAGESIZE	(4096)
#endif /* PAGESIZE */

extern int doit( void );
extern char *testname;

int main( int argc, char *argv[] )
{
	printf( "%s: ", testname );
	fflush( stdout );

	doit();

	/* Probably never reached */
	printf( "Failed\n" );
	exit( 0 );
}

void itworked( void )
{
	printf( "Vulnerable\n" );
	exit( 1 );
}

void itfailed( void )
{
	printf( "Ok\n" );
	exit( 2 );
}


int do_mprotect( const void *addr, size_t len, int prot )
{
	void *ptr;
	int retval;

	/* Allign to a multiple of PAGESIZE, assumed to be a power of two */
	ptr = (char *)(((int) addr + PAGESIZE-1) & ~(PAGESIZE-1));

	retval = mprotect( ptr, len, prot );
	if( retval != 0 && errno == EINVAL ) {
		perror( "could not mprotect():" );
		exit( 1 );
	}

	return retval;
}

