CC=gcc
CFLAGS=-ggdb -O2
LDFLAGS=

TESTS=	anonmap \
	execbss \
	execdata \
	execheap \
	execstack \
	mprotanon \
	mprotbss \
	mprotdata \
	mprotheap \
	mprotshbss \
	mprotshdata \
	mprotstack \
	rettofunc1 \
	rettofunc2 \
	shlibbss \
	shlibdata

SHLIBS=	shlibtest.so

all: $(SHLIBS) $(TESTS) runtests

runtests: $(TESTS) genruntests
	sh genruntests $(TESTS)

clean:
	-rm -f *.o *.s *~ core $(SHLIBS) $(TESTS) runtests mptest.log

anonmap: body.o anonmap.o

execbss: body.o execbss.o

execdata: body.o execdata.o

execheap: body.o execheap.o

execstack: body.o execstack.o

mprotanon: body.o mprotanon.o

mprotbss: body.o mprotbss.o

mprotheap: body.o mprotheap.o

mprotdata: body.o mprotdata.o

mprotshbss: body.o mprotshbss.o shlibtest.so

mprotshdata: body.o mprotshdata.o shlibtest.so

mprotstack: body.o mprotstack.o

rettofunc1: body.o rettofunc1.o

rettofunc2: body.o rettofunc2.o

shlibtest.o: shlibtest.c
	$(CC) $(CFLAGS) -fPIC -DPIC -c $< -o $@

shlibtest.so: shlibtest.o
	$(CC) $(SHLDFLAGS) -shared -o $@ $+

shlibbss: body.o shlibbss.o shlibtest.so

shlibdata: body.o shlibdata.o shlibtest.so
