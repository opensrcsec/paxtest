/* mprotshbss.c - Tests whether code in the .bss segment of a shared library can
 *                be executed after trying to use mprotect() to make it
 *                executable.
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include "body.h"
#include "shellcode.h"

const char testname[] = "Executable shared library bss (mprotect) ";

void doit( void )
{
	char *shbss;
	char *shbss2;
	fptr func;
	void *handle1, *handle2;

	handle1 = dlopen( "shlibtest.so", RTLD_LAZY );
	if( handle1 == NULL ) {
		fprintf( stderr, "dlopen() returned NULL\n" );
		exit( 1 );
	}
	dlerror(); /* clear any errors */
	shbss = dlsym( handle1, "shbss" );
	if( dlerror() != NULL ) {
		fprintf( stderr, "symbol %s not found in %s\n", "shbss", "shlibtest.so" );
		exit( 1 );
	}

	handle2 = dlopen( "shlibtest2.so", RTLD_LAZY );
	if( handle2 == NULL ) {
		fprintf( stderr, "dlopen() returned NULL\n" );
		exit( 1 );
	}
	dlerror(); /* clear any errors */
	shbss2 = dlsym( handle2, "shbss2" );
	if( dlerror() != NULL ) {
		fprintf( stderr, "symbol %s not found in %s\n", "shbss2", "shlibtest2.so" );
		exit( 1 );
	}

	copy_shellcode(shbss, SHELLCODE_RETURN);
	copy_shellcode(shbss2, SHELLCODE_RETURN);

	/* Convert the pointer to a function pointer */
	func = shbss < shbss2 ? (fptr)shbss : (fptr)shbss2;

	/* Try to make the memory region executable by using mprotect() */
	/* Due to an OpenBSD bug PROT_READ is required */
	do_mprotect(func, MAX_SHELLCODE_LEN, PROT_READ|PROT_EXEC );

	/* Call the code in the buffer */
	func();

	do_mprotect(func, MAX_SHELLCODE_LEN, PROT_READ|PROT_WRITE );

	/* It worked when the function returns */
	itworked();

	dlclose( handle1 );
	dlclose( handle2 );
}
