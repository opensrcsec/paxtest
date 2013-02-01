#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void)
{
	char *addr;
	int can_map_above_stack = 0;
	char **maps;
	unsigned int num_maps = 0;

	/* return normal mmap randomization on 64bit systems */
	if (sizeof(unsigned long) == 8) {
		addr = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		goto out;
	}

	maps = (char **)calloc(1024 * 1024, sizeof(char *));

	while (1) {
		addr = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (addr == 0xffffffff)
			break;
		if (addr > (char *)&addr)
			can_map_above_stack = 1;
		maps[num_maps++] = addr;
	}

	if (!can_map_above_stack) {
		/* upper end is randomized due to the stack base and PROT_NONE gap
		   inserted above stack */
		unsigned int map_size = 0x1000;
		while (1) {
			munmap(maps[--num_maps], 0x1000);
			addr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
			if (addr == 0xffffffff)
				break;
			munmap(addr, map_size);
			map_size += 0x1000;
		}
		/* can't insert any bigger mapping, filled mmap -> stack gap, next deallocation is
		   lowest mappable address
		*/
	}

	munmap(maps[num_maps - 1], 0x1000);
	addr = mmap(NULL, 0x1000, PROT_READ | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

out:
	printf("%p\n", addr);
	return 0;
}
