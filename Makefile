#!/usr/bin/make
#
# PaXtest master makefile
# Copyright(c) 2003 by Peter Busser <peter@adamantix.org>
# This file has been released under the GNU Public Licence version 2 or later

all:
	@cat targets

linux:
	cd src && $(MAKE) -f Makefile.psm

linux32:
	cd src && $(MAKE) -f Makefile.psm THEARCH=-m32

linux64:
	cd src && $(MAKE) -f Makefile.psm THEARCH=-m64

openbsd:
	cd src && gmake -f Makefile.OpenBSD

freebsd:
	cd src && $(MAKE) -f Makefile.FreeBSD

clean:
	cd src && $(MAKE) -f Makefile.psm clean
