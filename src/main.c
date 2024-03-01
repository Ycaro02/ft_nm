# include "../include/nm.h"

void    reverse_bytes(uint8_t *ptr, size_t max)
{
    uint8_t    tmp;

    for (size_t i = 0; i < max / 2; ++i) {
        tmp = ptr[i];
        ptr[i] = ptr[max - i - 1];
        ptr[max - i - 1] = tmp;
    }
}

void test_reverse_byte()
{
	int nb = 9;
	unsigned char *str = ft_calloc(sizeof(unsigned char*), nb);
	for (int i = 0; i < nb; ++i) {
		str[i] = i;
	}
	ft_printf_fd(1, YELLOW"Before:\n"RESET);
	for (int i = 0; i < nb; ++i) {
		ft_printf_fd(1, GREEN"%d:\n"RESET, str[i]);
	}

	reverse_bytes(str, nb);

	ft_printf_fd(1, YELLOW"After:\n"RESET);
	for (int i = 0; i < nb; ++i) {
		ft_printf_fd(1, BLUE"%d:\n"RESET, str[i]);
	}
}

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
	ft_printf_fd(1, "type: %d == %d\n", ELF_TYPE(elf_struct), ((Elf64_Ehdr *) elf_struct)->e_type);
	ft_printf_fd(1, "machine: %d == %d\n", ELF_MACHINE(elf_struct), ((Elf64_Ehdr *) elf_struct)->e_machine);
	ft_printf_fd(1, "version: %d == %d\n", ELF_VERSION(elf_struct), ((Elf64_Ehdr *) elf_struct)->e_version);
	test_reverse_byte();
	return (0);
}
