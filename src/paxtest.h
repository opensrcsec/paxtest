#ifndef _PAXTEST_H_
#define _PAXTEST_H_

#include <string.h>
#include <unistd.h>

/*
 * ARMv6 and ARMv7 do not like 64k alignment, 32k is ok
 */
#if defined(__arm__) && __ARM_ARCH >= 6 && __ARM_ARCH <= 7
#define PAGE_SIZE_MAX  (32768)
#else
#define PAGE_SIZE_MAX	0x10000	/* 64k should cover most arches */
#endif
#ifndef __aligned
#define __aligned(x)	__attribute__((aligned(x)))
#endif
#define __pagealigned	__aligned(PAGE_SIZE_MAX)
#define __use(x)	asm volatile ( "" : : "m" (x) );

static inline char *forced_strcpy(char *dst, const char *src)
{
	strcpy(dst, src);
	/* ensure the compiler won't optimize the strcpy() away */
	__use(dst);
	return dst;
}

static inline void *forced_memcpy(void *dst, const void *src, size_t n)
{
	memcpy(dst, src, n);
	/* ensure the compiler won't optimize the memcpy() away */
	__use(dst);
	return dst;
}

#endif
