CC=gcc
CFLAGS=-ggdb -O2
LDFLAGS=

OBJS=rettofunc1 \
	rettofunc2

all: $(OBJS)

clean:
	-rm -f *.o *.s *~ core $(OBJS)

rettofunc1: body.o rettofunc1.o

rettofunc2: body.o rettofunc2.o

