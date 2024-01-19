#!/usr/bin/make
#
# PaXtest master makefile
# Copyright(c) 2003 by Peter Busser <peter@adamantix.org>
# This file has been released under the GNU Public Licence version 2 or later

all:
	@cat targets

linux:
	$(MAKE) -f Makefile.psm

linux32:
	$(MAKE) -f Makefile.psm THEARCH=-m32

linux64:
	$(MAKE) -f Makefile.psm THEARCH=-m64

openbsd:
	gmake -f Makefile.OpenBSD

freebsd:
	$(MAKE) -f Makefile.FreeBSD

clean:
	$(MAKE) -f Makefile.psm clean

