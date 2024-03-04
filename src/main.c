# include "../include/nm.h"

t_nm_file *get_nm_file_context(t_nm_context c, void *elf_struct)
{
	t_nm_file *file = ft_calloc(sizeof(t_nm_file), 1);
	if (!file) {
		ft_printf_fd(2, "Alloc error get nm file\n");
		return (NULL);
	}
	file->endian = ELF_HFIELD(elf_struct, EI_DATA) - c.l_endian; 
	file->class = IS_ELF64(elf_struct);
	return (file);
}

int main(int argc, char **argv)
{
	t_nm_context		context;
	char 			    *path = "a.out";
	
	context.flag = 0;
	context.l_endian = detect_local_endian();
	printf(YELLOW"Local endian = %d\n"RESET, context.l_endian);
	if (argc > 1) {
		path = argv[1];
	}
	void *elf_struct = parse_elf_header(path); 
	if (!elf_struct) {
		return (1);
	}
	ft_printf_fd(1, "class: %d\n", ELF_CLASS(elf_struct));
	/* endian bool, 0 if same endian */
	t_nm_file *file = get_nm_file_context(context, elf_struct);
	if (file) {
		display_elf_header(elf_struct, file->endian);
		display_all_program_header(elf_struct, file->endian);
		display_all_section_header(elf_struct, file->endian, file->class);
		free(file);
	}
	// test_macro(elf_struct, endian);
	return (0);
}
