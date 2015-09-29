#ifndef _BODY_H_
#define _BODY_H_

#include <stddef.h>

/* provided by body.c */
void itworked( void );
void itfailed( void );
int do_mprotect( const void *addr, size_t len, int prot );

/* provided by individual tests */
typedef void (*fptr)(void);
extern const char testname[];
void doit( void );

#endif
