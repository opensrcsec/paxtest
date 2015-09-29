/* randmain2.c - Tests the randomization of the ET_DYN main executable
 * 
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Main executable randomization (PIE)      ";
const char testprog[] = RUNDIR"/getmain2";
