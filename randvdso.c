/* randvdso.c - Tests the randomisation of VDSO
 * 
 * Copyright (c) 2014 by Brad Spengler <spender@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "VDSO randomisation test                  ";
const char testprog[] = RUNDIR"/getvdso";
