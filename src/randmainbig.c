/* randmainbig.c - Tests randomization of a hugepage aligned ET_DYN main executable
 * 
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * Copyright (c)2024 by Mathias Krause <minipli@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Big main executable randomization (PIE)  ";
const char testprog[] = RUNDIR"/getmainbig";
