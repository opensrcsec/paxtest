CC=gcc
CFLAGS=-ggdb -O2
LDFLAGS=

OBJS=	execbss \
	execdata \
	execheap \
	execstack \
	rettofunc1 \
	rettofunc2

all: $(OBJS) runtests

runtests: $(OBJS)
	sh genruntests $(OBJS)

clean:
	-rm -f *.o *.s *~ core $(OBJS) runtests

execbss: body.o execbss.o

execdata: body.o execdata.o

execheap: body.o execheap.o

execstack: body.o execstack.o

rettofunc1: body.o rettofunc1.o

rettofunc2: body.o rettofunc2.o

