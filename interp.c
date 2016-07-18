#ifdef __FreeBSD__
const char __invoke_dynamic_linker__[] __attribute__ ((section (".interp"))) = "/libexec/ld-elf.so.1";
#elif defined(__linux__) && defined(__UCLIBC__)
const char __invoke_dynamic_linker__[] __attribute__ ((section (".interp"))) = "/lib/ld-uClibc.so.0";
#elif defined(__linux__)
const char __invoke_dynamic_linker__[] __attribute__ ((section (".interp"))) = "/lib/ld-linux.so.2";
#else
#error unsupported OS
#endif
