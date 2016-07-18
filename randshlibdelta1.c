/* randshlibdelta1.c - Tests the randomisation of delta between ET_EXEC main
 *     executable and shared libraries (should match randshlib)
 *
 * Copyright (c)2014 by Kees Cook <keescook@chromium.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Offset to library randomisation (ET_EXEC)";
const char testprog[] = RUNDIR"/getshlibdelta1";
