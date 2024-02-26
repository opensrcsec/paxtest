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
# (C) 2024 Open Source Security, Inc. All Rights Reserved.
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

check_dir() {
	if [ ! -d "$1" ]; then
		echo "ignoring '$1': not a directory"
		return
	fi

	elf_list "$1" | while read file; do
		$READELF -Wl "$file" 2>/dev/null | $AWK '
			BEGIN  { align=0x1000; p=0 }
			/LOAD/ { if (strtonum($NF) > align) { align=strtonum($NF); p=1 } }
			END    { if (p) printf "%s (max align=%#x)\n", "'"$file"'", align }
			'
	done
}

find_tools

if [ $# -lt 1 ]; then
	echo >&2 "error: Missing directory argument(s)!"
	echo >&2
	echo >&2 "usage: $0 /path/to/check..."
	exit 1
fi

for dir in "$@"; do
	check_dir "$dir"
done
