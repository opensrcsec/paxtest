#!/bin/sh
#
# Script to search for ELF binaries and shared libraries that contain segments
# with an alignment bigger than 4096, reducing runtime ASLR entropy bits.
#
# The bigger alignment is likely not needed and more likely only an artifact of
# using an old toolchain to build these binaries/libraries that defaulted to a
# needlessly big alignment.
#
# Requires GNU awk (for strtonum(), patches welcome ;)), readelf (either
# binutil's, which is faster, or elfutils') and, optionally, scanelf -- again,
# much faster that the find-based fall-back.
#
# (C) 2024 Open Source Security
#
# This file has been released under the GNU Public Licence version 2 or later.
#
# - minipli

find_tools() {
	local err

	err=0
	READELF=$(command -v readelf 2>/dev/null || command -v eu-readelf 2>/dev/null)
	if [ -z "$READELF" ]; then
		echo >&2 "error: 'readelf' not found!"
		echo >&2 "error: Please install either binutils or elfutils."
		err=1
	fi

	if $READELF --help | grep -F -q -e '--wide'; then
		READELF="$READELF -W"
	fi

	AWK=$(command -v gawk 2>/dev/null)
	if [ -z "$AWK" ]; then
		echo >&2 "error: 'gawk' not found!"
		echo >&2 "error: Please install gawk."
		err=1
	fi

	SCANELF=$(command -v scanelf 2>/dev/null)

	if [ $err -ne 0 ]; then
		exit $err
	fi
}

# generate a list of ELF files below a given directory
elf_list() {
	if [ -n "$SCANELF" ]; then
		$SCANELF -B -F "%F" -R "$1"
	else
		find "$1" -type f -exec head -c 4 "{}" \; -print | sed -n 's|^.ELF||p'
	fi
}

filter_type() {
	local has_needed
	local has_interp
	local elf_type

	has_interp=$($READELF -l "$1" 2>/dev/null | grep -qw INTERP && echo 1 || echo 0)
	has_needed=$($READELF -d "$1" 2>/dev/null | grep -qw NEEDED && echo 1 || echo 0)
	elf_type=$($READELF -h "$1" 2>/dev/null | sed -n 's/.*Type:.*\(NONE\|REL\|EXEC\|DYN\|CORE\).*$/\1/p')

	# static EXEC: !NEEDED, !INTERP
	# static DYN (aka static PIE): !NEEDED, INTERP
	# EXEC: ?NEEDED, INTERP
	# DYN (shlib): ?NEEDED, !INTERP
	# DYN (PIE): ?NEEDED, INTERP
	if [ $has_needed -eq 0 ] && [ $has_interp -eq 0 ] && [ "$elf_type" = "EXEC" ] ; then
		sed 's/)$/, statically linked)/'
	else
		cat
	fi
}

check_file() {
	$READELF -l "$1" 2>/dev/null | $AWK '
		BEGIN  { align=0x1000; p=0 }
		/LOAD/ { if (strtonum($NF) > align) { align=strtonum($NF); p=1 } }
		END    { if (p) printf "%s (max align=%#x)\n", "'"$1"'", align }
		' | filter_type "$1"
}

check_dir() {
	elf_list "$1" | while read file; do
		check_file "$file"
	done
}

check() {
	if [ -d "$1" ]; then
		check_dir "$1"
	elif [ -r "$1" ]; then
		check_file "$1"
	else
		echo "ignoring '$1': neither a directory nor a file"
	fi
}

find_tools

if [ $# -lt 1 ]; then
	echo >&2 "error: Missing directory/file argument(s)!"
	echo >&2
	echo >&2 "usage: $0 /path/to/check..."
	exit 1
fi

for arg in "$@"; do
	check "$arg"
done
