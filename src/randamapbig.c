/* randamapbig.c - Tests the randomization of big anonymous mappings.
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * Copyright (c)2024 by Mathias Krause <minipli@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Anonymous huge mapping randomization test";
const char testprog[] = RUNDIR"/getamapbig";
