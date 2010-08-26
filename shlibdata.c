/* shlibdata.c - Tests whether code in the .data segment of a shared library can
 *               be executed
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "body.h"
#include "shellcode.h"

const char testname[] = "Executable shared library data           ";


void doit( void )
{
	fptr func;
	char *shdata, *shdata2;
	void *handle1, *handle2;

	handle1 = dlopen( "shlibtest.so", RTLD_LAZY );
	if( handle1 == NULL ) {
		fprintf( stderr, "dlopen() returned NULL\n" );
		exit( 1 );
	}
	dlerror(); /* clear any errors */
	shdata = dlsym( handle1, "shdata" );
	if( dlerror() != NULL ) {
		fprintf( stderr, "symbol %s not found in %s\n", "shdata", "shlibtest.so" );
		exit( 1 );
	}

	handle2 = dlopen( "shlibtest2.so", RTLD_LAZY );
	if( handle2 == NULL ) {
		fprintf( stderr, "dlopen() returned NULL\n" );
		exit( 1 );
	}
	dlerror(); /* clear any errors */
	shdata2 = dlsym( handle2, "shdata2" );
	if( dlerror() != NULL ) {
		fprintf( stderr, "symbol %s not found in %s\n", "shdata2", "shlibtest2.so" );
		exit( 1 );
	}

	copy_shellcode(shdata, SHELLCODE_RETURN);
	copy_shellcode(shdata2, SHELLCODE_RETURN);

	/* Convert the pointer to a function pointer */
	func = shdata < shdata2 ? (fptr)shdata : (fptr)shdata2;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();

	dlclose( handle1 );
	dlclose( handle2 );
}
