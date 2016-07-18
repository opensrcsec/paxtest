/* randshlibdelta2.c - Tests the randomisation of delta between ET_DYN main
 *     executable and shared libraries
 *
 * Copyright (c)2014 by Kees Cook <keescook@chromium.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Offset to library randomisation (ET_DYN) ";
const char testprog[] = RUNDIR"/getshlibdelta2";
