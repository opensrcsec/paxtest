/* randarg.c - Tests the randomization of arguments/environment
 * 
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Arg/env randomization test (SEGMEXEC)    ";
const char testprog[] = RUNDIR"/getarg1";

#ifndef __i386__
int skip_test(void)
{
	return 1;
}
#endif
