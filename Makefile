#!/usr/bin/make
#
# PaXtest master makefile
# Copyright(c) 2003 by Peter Busser <peter@adamantix.org>
# This file has been released under the GNU Public Licence version 2 or later

all:
	cat targets

adamantix:
	make -f Makefile.Adamantix

redhat-taroon:
	make -f Makefile.RedHat-taroon

gentoo: generic

gentoo-hardened:
	make -f Makefile.Gentoo-hardened

generic:
	make -f Makefile.generic

clean:
	make -f Makefile.Adamantix clean

