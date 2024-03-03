# include "../include/nm.h"


int main(int argc, char **argv)
{
	t_nm_context	context;
	char 			*path = "a.out";
	
	context.flag = 0;
	context.l_endian = detect_local_endian();
	printf("Local endian = %d\n", context.l_endian);
	if (argc > 1) {
		path = argv[1];
	}
	void *elf_struct = parse_elf_header(path); 
	if (!elf_struct) {
		return (1);
	}
	ft_printf_fd(1, "class: %d\n", ELF_CLASS(elf_struct));
	/* endian bool, 0 if same endian */
	int8_t endian =  ELF_HFIELD(elf_struct, EI_DATA) - context.l_endian; 
	ft_printf_fd(1, "type:      %d == %d\n", ELF_TYPE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_type);
	ft_printf_fd(1, "machine:   %d == %d\n", ELF_MACHINE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_machine);
	ft_printf_fd(1, "version:   %d == %d\n", ELF_VERSION(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_version);
	ft_printf_fd(1, "entry:     %p == %p\n", ELF_ENTRY(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_entry);
	ft_printf_fd(1, "phoff:     %d == %d\n", ELF_PHOFF(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phoff);
	ft_printf_fd(1, "shoff:     %d == %d\n", ELF_SHOFF(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shoff);
	ft_printf_fd(1, "flags:     %d == %d\n", ELF_FLAGS(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_flags);
	ft_printf_fd(1, "ehsize:    %d == %d\n", ELF_EHSIZE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_ehsize);
	ft_printf_fd(1, "phentsize: %d == %d\n", ELF_PHENTSIZE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phentsize);
	ft_printf_fd(1, "phnum:     %d == %d\n", ELF_PHNUM(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phnum);
	ft_printf_fd(1, "shentsize: %d == %d\n", ELF_SHENTSIZE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shentsize);
	ft_printf_fd(1, "shnum:     %d == %d\n", ELF_SHNUM(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shnum);
	ft_printf_fd(1, "shstrndx:  %d == %d\n", ELF_SHSTRNDX(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shstrndx);
	
	
	// test_reverse_byte(reverse_bytes);

	return (0);
}
