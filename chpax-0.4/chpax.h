/*
 * Include file for chpax.c
 * 
 * The PaX project : http://pageexec.virtualave.net/
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/elf.h>
#include <linux/a.out.h>

#define	CHPAX_VERSION		"0.4"

#define HF_PAX_PAGEEXEC         1    /* 0: Paging based non-exec pages */
#define HF_PAX_EMUTRAMP         2    /* 0: Emulate trampolines */
#define HF_PAX_MPROTECT         4    /* 0: Restrict mprotect() */
#define HF_PAX_RANDMMAP         8    /* 0: Randomize mmap() base */
#define HF_PAX_RANDEXEC         16   /* 1: Randomize ET_EXEC base */
#define HF_PAX_SEGMEXEC         32   /* 0: Segmentation based non-exec pages */

#define EI_PAX                  14   /* Index to read the PaX flags into ELF header e_ident[] array */

#define	XCLOSE(fd)		\
do				\
{				\
 if (close(fd))			\
   perror("close");		\
}				\
while (0)

#define	FILE_IS_ELF64(h)	(h.e_ident[EI_CLASS] == 2)
#define	FILE_IS_ELF32(h)	(h.e_ident[EI_CLASS] == 1)

/* Extern variables */
extern struct elf32_hdr		header_elf;
extern struct elf64_hdr		header_elf64;
extern struct exec		header_aout;
extern int			header_size;
extern void			*header;
extern int			fd;
extern unsigned long		(*get_flags)();
extern void			(*put_flags)(unsigned long);

/* Function prototypes */
int                     read_header(char *name, int mode);
int			write_header();
unsigned long		get_flags_elf();
void			put_flags_elf(unsigned long flags);
unsigned long		get_flags_aout();
void			put_flags_aout(unsigned long flags);
unsigned long		get_flags_elf64();
void			put_flags_elf64(unsigned long flags);
void			usage(char *name);
unsigned long		scan_flags(unsigned long flags, char **argv, int *view);
void			print_flags(unsigned long flags);
