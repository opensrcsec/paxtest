#include <stdio.h>

extern int doit( void );
extern char *testname;

int main( int argc, char *argv[] )
{
	doit();

	/* Probably never reached */
	printf( "%s: Failed\n", testname );
	exit( 0 );
}

void itworked( void )
{
	printf( "%s: Vulnerable\n", testname );
	exit( 1 );
}

void itfailed( void )
{
	printf( "%s: Ok\n", testname );
	exit( 2 );
}

unsigned long get_sp( void )
{
	__asm__( "movl %esp, %eax" );
}

