/* randheap2.c - Tests the randomisation of the heap of PIE main executable.
 * 
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Heap randomisation test (PIE)            ";
const char testprog[] = RUNDIR"/getheap2";
