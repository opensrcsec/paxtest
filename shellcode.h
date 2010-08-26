#include <unistd.h>
#include <string.h>

#define MAX_SHELLCODE_LEN 12

#if defined(__powerpc__)
#define SHELLCODE_RETURN_ARRAY { '\x4e', '\x80', '\x00', '\x20' }
#define SHELLCODE_RETURN "\x4e\x80\x00\x20"
#define SIZE_OF_SHELLCODE_RETURN 4
#elif defined(__sparc__) && !defined(__arch64__)
#define SHELLCODE_RETURN_ARRAY { '\x81', '\xc7', '\xe0', '\x08', '\x81', '\xe8' ,'\x00', '\x00' }
#define SHELLCODE_RETURN "\x81\xc7\xe0\x08\x81\xe8\x00\x00"
#define SIZE_OF_SHELLCODE_RETURN 8
#elif defined(__sparc__) && defined(__arch64__)
#define SHELLCODE_RETURN_ARRAY { '\x9d', '\xe3', '\xbf', '\x40', '\x81', '\xcf', '\xe0', '\x08', '\x01', '\x00', '\x00', '\x00' }
#define SHELLCODE_RETURN "\x9d\xe3\xbf\x40\x81\xcf\xe0\x08\x01\x00\x00\x00"
#define SIZE_OF_SHELLCODE_RETURN 12
#else
#define SHELLCODE_RETURN_ARRAY { '\xc3' }
#define SHELLCODE_RETURN "\xc3"
#define SIZE_OF_SHELLCODE_RETURN 1
#endif

#if defined(__powerpc64__)
static inline void copy_shellcode(char *dest, char *src)
{
	/* 12 bytes total */
	unsigned long dstaddr = (unsigned long)dest + sizeof(dstaddr);
	memcpy(dest, &dstaddr, sizeof(dstaddr));
	memcpy(dest + sizeof(dstaddr), src, SIZE_OF_SHELLCODE_RETURN);
}
#else
static inline void copy_shellcode(char *dest, char *src)
{
	memcpy(dest, src, SIZE_OF_SHELLCODE_RETURN);
}
#endif
