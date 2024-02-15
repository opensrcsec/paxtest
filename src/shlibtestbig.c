/* shlibtestbig.c - Big shared library used by the shared library tests.
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * Copyright (c)2024 by Mathias Krause <minipli@grsecurity.net>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#include "paxtest.h"

int dummy_pad1(void) __aligned(HUGE_PAGE_SIZE);
int dummy_pad1(void)
{
	return 0;
}

/* A function which does nothing, it only exists so it can be referenced */
void big_nop(void)
{
	return;
}

int dummy_pad2(void) __aligned(HUGE_PAGE_SIZE);
int dummy_pad2(void)
{
	return 0;
}
