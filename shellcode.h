#ifndef _SHELLCODE_H_
#define _SHELLCODE_H_

#include "paxtest.h"

#define MAX_SHELLCODE_LEN 12

#if defined(__powerpc__)
#define SHELLCODE_RETURN "\x4e\x80\x00\x20"
#elif defined(__sparc__) && !defined(__arch64__)
#define SHELLCODE_RETURN "\x81\xc7\xe0\x08\x81\xe8\x00\x00"
#elif defined(__sparc__) && defined(__arch64__)
#define SHELLCODE_RETURN "\x9d\xe3\xbf\x40\x81\xcf\xe0\x08\x01\x00\x00\x00"
#elif defined(__arm__) && !defined(__arch64__)
#define SHELLCODE_RETURN "\x1e\xff\x2f\xe1"
#else
#define SHELLCODE_RETURN "\xc3"
#endif
#define SIZE_OF_SHELLCODE_RETURN (sizeof(SHELLCODE_RETURN) - 1)

#if defined(__powerpc64__)
static inline void copy_shellcode(void *dst)
{
	/* 12 bytes total */
	unsigned long dstaddr = (unsigned long)dst + sizeof(dstaddr);
	forced_memcpy(dst, &dstaddr, sizeof(dstaddr));
	forced_memcpy(dst + sizeof(dstaddr), SHELLCODE_RETURN, SIZE_OF_SHELLCODE_RETURN);
}
#else
static inline void copy_shellcode(void *dst)
{
	forced_memcpy(dst, SHELLCODE_RETURN, SIZE_OF_SHELLCODE_RETURN);
}
#endif

#endif
