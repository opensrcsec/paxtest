/* randmain1.c - Tests the randomisation of ET_EXEC main executable
 * 
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

char *testname = "Main executable randomisation (ET_EXEC)  ";
char *testprog = RUNDIR"/getmain1";

