# include "../include/nm.h"

/**
 * @brief Extracts the file context for an ELF file.
 * It allocates memory for the structure and sets its fields based on the parsed ELF header.
 * @param c The t_nm_context structure containing the context information.
 * @param path The path of the ELF file.
 * @return A pointer to the t_elf_file structure if successful, NULL otherwise.
 */
static t_elf_file *get_elf_file_context(t_nm_context c, char *path)
{
	t_elf_file *file = ft_calloc(sizeof(t_elf_file), 1);

	if (!file) {
		ft_printf_fd(2, "Alloc error get nm file\n");
		return (NULL);
	}

	file->ptr = parse_elf_header(path, &file->file_size); 
	if (!file->ptr) {
		free(file);
		return (NULL);
	}
	/* maybe just store this in flag ?? */
	/* get bool endian 0 is same endian */
	file->name = path;
	file->endian = ELF_HFIELD(file->ptr, EI_DATA) - c.l_endian; 
	/* get bool class */
	file->class = IS_ELF64(file->ptr);
	return (file);
}

/**
 * @brief Performs the nm operation on the given files.
 * It extracts the file paths from the command line arguments,
 * creates the file context for each file, and displays the symbols for each file.
 * @param c The t_nm_context structure containing the context information.
 * @param argc The number of command line arguments.
 * @param argv An array of command line arguments.
 * @return The exit code of the nm operation.
 */
static int nm(t_nm_context c, int argc, char **argv)
{
	t_list	*file_lst = extract_file_from_cmd(argc, argv);
	t_list	*lst = file_lst;
	int 	exit_code = 0;
	int8_t	file_header = ft_lstsize(file_lst) > 1;

	if (lst) {
		while (lst) {
			t_elf_file *elf_file = get_elf_file_context(c, lst->content);
			if (elf_file) {
				if (file_header) {
					ft_printf_fd(1, "\n%s:\n", elf_file->name);
				}
				exit_code = display_file_symbole(elf_file);
				free(elf_file);
			} else {
				exit_code = 1;
			}
			lst = lst->next;
		}
	}
	lst_clear(&file_lst, free);
	return (exit_code);
}

/**
 * @brief The entry point of the program.
 * This function initializes the t_nm_context structure, detects the local endianess,
 * and calls the nm function to perform the nm operation on the command line arguments.
 * @param argc The number of command line arguments.
 * @param argv An array of command line arguments.
 * @return The exit code of the program.
 */
int main(int argc, char **argv)
{
	t_nm_context	context;
	int 			exit_code = 0;

	context.flag = parse_flag(argc, argv);
	context.l_endian = detect_local_endian();
	exit_code = nm(context, argc, argv);
	return exit_code;
}