/* randheap2.c - Tests the randomisation of the heap of ET_DYN main executable.
 * 
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

char *testname = "Heap randomisation test (ET_DYN)         ";
char *testprog = RUNDIR"/getheap2";

