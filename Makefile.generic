#!/usr/bin/make

ifndef CC
CC=gcc
endif
ifndef CFLAGS
CFLAGS=-O2
endif
ifndef LDFLAGS
LDFLAGS=
endif
ifndef RUNDIR
RUNDIR=.
endif

CFLAGS+=-DRUNDIR=\"${RUNDIR}\"


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
	randamap \
	randheap1 \
	randheap2 \
	randmain1 \
	randmain2 \
	randshlib \
	randstack1 \
	randstack2 \
	rettofunc1 \
	rettofunc2 \
	shlibbss \
	shlibdata \
	writetext

UTILS=	getamap \
	getheap1 \
	getheap2 \
	getmain1 \
	getmain2 \
	getshlib \
	getstack1 \
	getstack2

CHPAX:=chpax-0.5

CHPAXSRC:=$(CHPAX)/aout.c \
	$(CHPAX)/chpax.c \
	$(CHPAX)/elf32.c \
	$(CHPAX)/elf64.c \
	$(CHPAX)/flags.c \
	$(CHPAX)/io.c

SHLIBS=	shlibtest.so

all: chpax $(SHLIBS) $(TESTS) $(UTILS) paxtest

clean:
	-rm -f *.o $(CHPAX)/*.o *.s *~ core
	-rm -f $(SHLIBS) $(TESTS) $(UTILS)
	-rm -f paxtest chpax paxtest.log a.out

ifdef DESTDIR
ifdef BINDIR
ifdef RUNDIR
install: all
	mkdir -p $(DESTDIR)/$(RUNDIR)
	cp $(SHLIBS) $(TESTS) $(UTILS) $(DESTDIR)/$(RUNDIR)
	mkdir -p $(DESTDIR)/$(BINDIR)
	cp paxtest $(DESTDIR)/$(BINDIR)
	chmod 755 $(DESTDIR)/$(BINDIR)/paxtest
endif
endif
endif

paxtest: $(TESTS) genpaxtest
	sh genpaxtest $(TESTS)

anonmap: body.o anonmap.o

chpax: $(CHPAXSRC:.c=.o)
	$(CC) $(LDFLAGS) -o $@ $+

crt1S.o: crt1S.S

execbss: body.o execbss.o

execdata: body.o execdata.o

execheap: body.o execheap.o

execstack: body.o execstack.o

getheap1: getheap.o
	$(CC) $(LDFLAGS) -o $@ $+

getheap2: crt1S.o interp.o getheap.o
	$(CC) -shared -o $@ $+

getheap.o: getheap.c
	$(CC) $(CFLAGS) -fPIC -DPIC -o $@ -c $<

getamap.o: getamap.c

getmain1: getmain.o
	$(CC) $(LDFLAGS) -o $@ $+
	./chpax -X $@

getmain2: crt1S.o interp.o getmain2.o
	$(CC) -shared -o $@ $+

getmain2.o: getmain.c
	$(CC) $(CFLAGS) -fPIC -DPIC -o $@ -c $<

getshlib: getshlib.o -ldl

getstack1: getstack.o
	$(CC) $(LDFLAGS) -o $@ $+
	./chpax -S $@

getstack2: getstack1 chpax
	rm -f $@
	cp getstack1 $@
	chmod +x $@
	./chpax -P $@

mprotanon: body.o mprotanon.o

mprotbss: body.o mprotbss.o

mprotheap: body.o mprotheap.o

mprotdata: body.o mprotdata.o

mprotshbss: body.o mprotshbss.o shlibtest.so

mprotshdata: body.o mprotshdata.o shlibtest.so

mprotstack: body.o mprotstack.o

randamap: randbody.o randamap.o

randheap1: randbody.o randheap1.o

randheap2: randbody.o randheap2.o

randmain1: randbody.o randmain1.o

randmain2: randbody.o randmain2.o

randshlib: randbody.o randshlib.o

randstack1: randbody.o randstack1.o

randstack2: randbody.o randstack2.o

rettofunc1: body.o rettofunc1.o

rettofunc2: body.o rettofunc2.o

shlibtest.o: shlibtest.c
	$(CC) $(CFLAGS) -fPIC -DPIC -c $< -o $@

shlibtest.so: shlibtest.o
	$(CC) $(SHLDFLAGS) -shared -o $@ $+

shlibbss: body.o shlibbss.o shlibtest.so

shlibdata: body.o shlibdata.o shlibtest.so

writetext: body.o writetext.o shlibtest.so

