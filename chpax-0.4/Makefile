##
## Makefile for chpax.c
##
## The PaX project : http://pageexec.virtualave.net/
##

SRC	= chpax.c io.c elf32.c elf64.c aout.c flags.c
OBJ	= $(SRC:.c=.o)
RM	= rm -f 
TARGET	= chpax
CC	= gcc
CFLAGS	= -Wall -W -g3

all	: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean	:
	$(RM) *.o *~ \#* *\#

fclean	: clean
	$(RM) $(TARGET)
