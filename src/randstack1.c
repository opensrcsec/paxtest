/* randstack.c - Tests the randomization of the stack pointer.
 * 
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Stack randomization test (SEGMEXEC)      ";
const char testprog[] = RUNDIR"/getstack1";

#ifndef __i386__
int skip_test(void)
{
	return 1;
}
#endif
