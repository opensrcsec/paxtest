/* getshlib.c - Get the address of a function in a shared library and print it
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU
#include <dlfcn.h>

int main( int argc, char *argv[] )
{
	void *handle;

	handle = dlopen( RTLD_DEFAULT, RTLD_LAZY );
	if( handle != NULL ) {
		void *sprintf;
	       
		sprintf = dlsym( handle, "sprintf" );

		if( dlerror() == NULL ) {
			printf( "%0p\n", sprintf );
		}

		dlclose( handle );
	}
}
