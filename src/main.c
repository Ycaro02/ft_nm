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
	ft_printf_fd(1, "class: %d\n", ELF_CLASS(elf_struct));
	ft_printf_fd(1, "type: %d == %d\n", ELF_TYPE(elf_struct), ((t_elf64 *) elf_struct)->e_type);
	return (0);
}
