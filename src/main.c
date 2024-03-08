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

static int nm(t_nm_context c, int argc, char **argv)
{
	t_list 				*file_lst = extract_file_from_cmd(argc, argv);
	t_list 				*lst = file_lst;
	int					exit_code = 0;

	if (lst) {
		while (lst) {
			t_elf_file *file = get_elf_file_context(c, lst->content);
			if (file) {
				exit_code = display_file_symbole(file);
				free(file);
			}
			lst = lst->next;
		}
	}
	lst_clear(&file_lst, free);
	return (exit_code);
}

int main(int argc, char **argv)
{
	t_nm_context		context;
	int					exit_code = 0;
	
	context.flag = 0;
	context.l_endian = detect_local_endian();
	exit_code = nm(context, argc, argv);
	return (exit_code);
}
