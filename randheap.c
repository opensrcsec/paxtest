/* randstack.c - Tests the randomisation of the stack pointer.
 * 
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

char *testname = "Heap randomisation test                  ";
char *testprog = RUNDIR"/getheap";

