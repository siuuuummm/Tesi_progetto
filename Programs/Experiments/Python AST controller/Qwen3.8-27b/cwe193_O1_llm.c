#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *process_name(char *name)
{
	size_t len;
	char *result;

	len = strlen(name);
	result = (char *)0;
	if (len < 0x11) {
		result = (char *)malloc(0x10);
		strcpy(result, name);
	}
	return result;
}

int main(int argc, char **argv)
{
	char *name;
	char *reg;
	size_t len;
	char **p;

	setvbuf(stdout, (char *)0, 2, 0);
	if (1 < argc) {
		p = argv + 1;
		do {
			name = *p;
			reg = process_name(name);
			if (reg == (char *)0) {
				len = strlen(name);
				printf("Nome troppo lungo: %zu caratteri\n", len);
			}
			else {
				len = strlen(reg);
				printf("Registrato: %s (%zu caratteri)\n", reg, len);
				free(reg);
			}
			p = p + 1;
		} while (p != argv + argc);
	}
	return 0;
}
