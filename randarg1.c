/* randarg.c - Tests the randomization of arguments/environment
 * 
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Arg/env randomization test (SEGMEXEC)    ";
const char testprog[] = RUNDIR"/getarg1";
