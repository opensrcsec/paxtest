/* getarg.c - Get the location of an argument and print it
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ){
	printf( "%p\n", argv[0] );

	exit( 0 );
}

