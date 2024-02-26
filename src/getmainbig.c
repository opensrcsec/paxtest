/* getmainbig.c - Get the address of the main function with big alignment and print it
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * Copyright (c)2024 by Mathias Krause <minipli@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include <stdio.h>
#include <stdlib.h>
#include "paxtest.h"

void __attribute__ ((noinline)) foo(void)
{
	printf("%p\n", __builtin_return_address(0));
}

int main(int argc, char *argv[]) __aligned(HUGE_PAGE_SIZE);
int main(int argc, char *argv[])
{
	foo();
	exit(0);
}
