CC=gcc
CFLAGS=-ggdb -O2
LDFLAGS=

TESTS=	execbss \
	execdata \
	execheap1 \
	execheap2 \
	execstack \
	mprotbss \
	mprotdata \
	mprotheap \
	mprotstack \
	rettofunc1 \
	rettofunc2

all: $(TESTS) runtests

runtests: $(TESTS)
	sh genruntests $(TESTS)

clean:
	-rm -f *.o *.s *~ core $(TESTS) runtests

execbss: body.o execbss.o

execdata: body.o execdata.o

execheap1: body.o execheap1.o

execheap2: body.o execheap2.o

execstack: body.o execstack.o

mprotbss: body.o mprotbss.o

mprotheap: body.o mprotheap.o

mprotdata: body.o mprotdata.o

mprotstack: body.o mprotstack.o

rettofunc1: body.o rettofunc1.o

rettofunc2: body.o rettofunc2.o

