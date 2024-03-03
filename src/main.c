# include "../include/nm.h"

int main(int argc, char **argv)
{
	t_nm_context	context;
	char 			    *path = "a.out";
	
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
	// test_macro(elf_struct, endian);
	display_elf_header(elf_struct, endian);
  display_all_program_header(elf_struct, endian);
  display_all_section_header(elf_struct, endian);
	return (0);
}
