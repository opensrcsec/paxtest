/* getstack.c - Get the location of the stack and print it
 *              (Idea by Peter Roozemaal)
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>

int main( int argc, char *argv[] ){
	char a;

	printf( "%p\n", &a );

	exit( 0 );
}

