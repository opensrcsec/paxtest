/* getmain.c - Get the address of the main function and print it
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <stdlib.h>

void foo( int unused )
{
	printf( "0x%08x\n", ((unsigned long*)&unused)[-1] );
}

int main( int argc, char *argv[] )
{
	foo(0);
}
