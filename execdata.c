/* execdata.c - Tests whether code in the .data segment can be executed
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "body.h"
#include "shellcode.h"

const char testname[] = "Executable data                          ";

char buf[MAX_SHELLCODE_LEN] = SHELLCODE_RETURN_ARRAY;

void doit( void )
{
	fptr func;

	copy_shellcode(buf, SHELLCODE_RETURN);

	/* Convert the pointer to a function pointer */
	func = (fptr)&buf;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}
