#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void)
{
	char *addr;
	char *last_addr;

	/* return normal mmap randomization on 64bit systems */
	if (sizeof(unsigned long) == 8) {
		addr = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		goto out;
	}

	while (1) {
		addr = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (addr == MAP_FAILED)
			break;
		last_addr = addr;
	}

	munmap(last_addr, 0x1000);
	addr = mmap(NULL, 0x1000, PROT_READ | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

out:
	printf("%p\n", addr);
	return 0;
}
