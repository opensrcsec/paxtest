/* getmain.c - Get the address of the main function and print it
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
	printf( "0x%08x\n", main );
}
