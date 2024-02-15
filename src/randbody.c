/* randbody.c - This part is shared by the randomization tests
 *
 * Copyright (c)2003-2014 by Peter Busser <peter@adamantix.org>, Brad Spengler <spender@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <stdlib.h>

#define COUNT	(1500)

extern const char testname[];
extern const char testprog[];

int skip_test(void) __attribute__((weak));
int skip_test(void)
{
	return 0;
}

int main( int argc, char *argv[] )
{
	FILE *fp;
	int i, x;
	unsigned long results[COUNT];
	unsigned int quality[8 * sizeof(unsigned long)] = { 0 };
	unsigned int weak_bits = 0;
	unsigned int dupes = 0;
	unsigned long tmp;
	unsigned long and;
	unsigned long or;
	int bits;
	int ret;

	printf( "%s: ", testname );
	fflush(NULL);

	if( skip_test() ) {
		printf( "Skipped, not applicable\n" );
		exit( 0 );
	}

	and = ~0L;
	or = 0L;
	for( i = 0; i < COUNT; i++ ) {
		fp = popen( testprog, "r" );
		if( fp == NULL ) {
			perror( testprog );
			exit( 1 );
		}

		ret = fscanf( fp, "%lx", &tmp );
		if (ret != 1) {
			perror ( testprog );
			exit( 1 );
		}
		results[i] = tmp;
		and &= tmp;
		or |= tmp;

		pclose( fp );
	}

	if( and == or ) {
		printf( "No randomization\n" );
	} else {
		tmp = and ^ ~or;
		tmp = or & ~tmp;
		bits = 0;
		for (i = 0; i < sizeof(quality)/sizeof(quality[0]); i++) {
			if (!(tmp & (1UL << i)))
				continue;
			for (x = 0; x < COUNT; x++) {
				if (results[x] & (1UL << i))
					quality[i] += 1;
			}
			if (quality[i] <= ((COUNT * 35) / 100) || quality[i] >= ((COUNT * 65) / 100))
				weak_bits++;
		}
		while( tmp != 0 ) {
			bits += (tmp%2);
			tmp >>= 1;
		}

		printf( "%d quality bits (guessed)\n", bits - weak_bits);
	}

	exit( 0 );
}

