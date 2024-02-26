# include "../include/nm.h"


int main(int argc, char **argv)
{
	char *path = "a.out";
	if (argc > 1) {
		path = argv[1];
	}
	void *elf_struct = parse_elf_header(path); 
	if (!elf_struct) {
		return (1);
	}
	return (0);
}
