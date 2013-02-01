/* randexhaust2.c - Tests the randomisation under memory exhaustion
 * when trying to get a fixed address at the bottom of the address space
 */

#ifndef RUNDIR
#error RUNDIR not defined
#endif

const char testname[] = "Randomization under memory exhaustion @0 ";
const char testprog[] = RUNDIR"/getexhaust2";
