/* randshlib.c - Tests the randomisation of shared library loading
 * 
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

char *testname = "Shared library randomisation test        ";
char *testprog = RUNDIR"/getshlib";

