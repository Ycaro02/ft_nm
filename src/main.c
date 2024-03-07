# include "../include/nm.h"

t_elf_file *get_elf_file_context(t_nm_context c, char *path)
{
	t_elf_file *file = ft_calloc(sizeof(t_elf_file), 1);

	if (!file) {
		ft_printf_fd(2, "Alloc error get nm file\n");
		return (NULL);
	}

	file->ptr = parse_elf_header(path); 
	if (!file->ptr) {
		free(file);
		return (NULL);
	}
	/* maybe just store this in flag ?? */
	/* get bool endian 0 is same endian */
	file->endian = ELF_HFIELD(file->ptr, EI_DATA) - c.l_endian; 
	/* get bool class */
	file->class = IS_ELF64(file->ptr);
	return (file);
}

int main(int argc, char **argv)
{
	t_nm_context		context;
	char 			    *path = "a.out";
	int					exit_code = 0;
	
	context.flag = 0;
	context.l_endian = detect_local_endian();
	ft_printf_fd(2, YELLOW"Local endian = %u\n"RESET, context.l_endian);
	if (argc > 1) {
		path = argv[1];
	}
	t_elf_file *file = get_elf_file_context(context, path);
	if (file) {
		// display_elf_header(file->ptr, file->endian);
		// display_all_program_header(file);
		exit_code = display_file_symbole(file);
		free(file);
	}
	// test_macro(elf_struct, endian);
	return (exit_code);
}
