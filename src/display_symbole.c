#include "../include/nm.h"

/** 
 *	@brief Get symbol name
 * 	@param symbole struct list
*/
static void lst_name_sort(t_list *lst)
{
    if (!lst)
        return ;
    t_list *head = lst;
    t_list *min = NULL;
    while (lst)  {
        if (!min)
            min = lst;
        if (ft_strcmp(((t_sym_tab *) ((t_list *) lst)->content)->sym_name, ((t_sym_tab *) ((t_list *) min)->content)->sym_name) <= 0)
            min = lst;
        lst = lst->next;
    }
    t_list *tmp = head->content;
    head->content = min->content;
    min->content = tmp;
    lst_name_sort(head->next);
}

/* @brief is source file */
static int is_source_file(uint8_t type)
{
	return ((type == STT_FILE || type == STT_SECTION));
}

/** 
 *	@brief Display symbole value
 *	@param nbr number to display
 *	@param fd file descriptor
*/
static void	display_sym_value(unsigned long nbr, int fd)
{
	char	*base_16;

	base_16 = "0123456789abcdef";
	if (nbr > 15)
		display_sym_value(nbr / 16, fd);
	ft_putchar_fd(base_16[nbr % 16], fd);
}


/** 
 *	@brief Get hex len
 *	@param nbr number to compute
 *	@return hex len
*/
static uint8_t compute_hex_len(unsigned long nbr)
{
	uint8_t count = 0;
	while (nbr > 15) {
		nbr /= 16;
		count++;
	}
	return (count);
}

/** 
 *	@brief Get zero padding: if elf 64, 16 digit else 8 - number len, all multiply by len != 0 to avoid protect if
 * 	@param class 1 for 64 bits 0 for 32 bits
 * 	@param len number len
 * 	@param is_undef 1 for undef 0 otherwise
 * 	@return number of padding
*/
static uint8_t get_zero_padding(int8_t class, uint8_t len, int8_t is_undef)
{
	return (((class == 1 ? 16 : 8) - (len + 1)) * (is_undef));
}

/** 
 *	@brief Insert pad
 * 	@param pad number of pad to insert
 * 	@param c char to insert
*/
static void insert_pad(uint8_t pad, char *c)
{
	while (pad > 0) {
		ft_printf_fd(1, c);
		--pad;
	}
}

/** 
 *	@brief Get symbole char
 * 	@param file pointer on file struct
 * 	@param symbole pointer on symbole struct
 * 	@param sizeof_Sshdr size of section header
 * 	@return symbole char
*/
static uint8_t get_symbole_char(t_elf_file *file, t_sym_tab *symbole, int16_t sizeof_Sshdr)
{
	uint8_t c = UNDIFINED_SYM;
	Elf64_Section shndx = symbole->shndx;

	if (symbole->bind == STB_WEAK) {
		if (symbole->type == STT_OBJECT) {
			c = 'V';
		} else {
			c = 'W';
		}
		c += (shndx == SHN_UNDEF) * 32;
	} else if (symbole->bind == STB_GNU_UNIQUE) {
		c = UNDIFINED_SYM + 32;
	} else if (shndx != SHN_UNDEF) {
		Elf64_Half shnum = get_Ehdr_shnum(file->ptr, file->endian);
		
		if (shndx == SHN_ABS) {
			c = ABS_SYM;
		} else if (shndx == SHN_COMMON) {
			c = COMMON_SYM;
		}  else if (shndx < shnum) {
			void *section_header_ptr = file->ptr + get_Ehdr_shoff(file->ptr, file->endian) + (sizeof_Sshdr * shndx);
			Elf64_Word sh_type = get_Shdr_type(section_header_ptr, file->endian, file->class);
			Elf64_Xword sh_flag = get_Shdr_flags(section_header_ptr, file->endian, file->class);

			if (sh_type == SHT_NOBITS) {
				c = NO_BITS_SYM; /* b */
			} else if (sh_flag == (SHF_ALLOC | SHF_WRITE)) {
				c = ALLOC_WRITE_SYM; /* d */
			} else if (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_EXECINSTR)) {
				c = FUNCTION_SYM; /* T */
			} else if (sh_flag & SHF_ALLOC && !(sh_flag & SHF_WRITE)) { /* obh sym R r*/
				c = OBJECT_SYM;
			}
			else if (sh_type & SHT_GROUP) {
				c = DEBUG_SYM;
			}
			if ((c >= 'A' && c <= 'Z') && (c != UNDIFINED_SYM && symbole->bind != STB_GLOBAL)) {
				c += 32;
			}
		}
	}
	return (c);
}

/** 
 *	@brief Fill symbole node
 * 	@param file pointer on file struct
 * 	@param strtab pointer on string table
 * 	@param i symbole index in symtable
 * 	@param name_idx symbole name index in strtab
 * 	@param type symbole type
 * 	@return symbole node struct
*/
static t_sym_tab fill_sym_node(t_elf_file *file, char *strtab, Elf64_Xword i, Elf64_Word name_idx, uint8_t type)
{
	t_sym_tab symbole;
	symbole.sym_name = strtab + name_idx;
	symbole.value = get_Sym_value((file->symtab + i), file->endian, file->class);
	symbole.type =  type;
	symbole.bind = ELF32_ST_BIND(get_Sym_info((file->symtab + i), file->class));
	symbole.shndx = get_Sym_shndx((file->symtab + i), file->endian, file->class);
	return (symbole);
}

/** 
 *	@brief Build symbole list
 * 	@param file pointer on file struct
 * 	@param strtab pointer on string table
 * 	@return list of symbole
*/
static t_list *build_symbole_list(t_elf_file *file, char *strtab)
{
	t_list			*name_lst = NULL;
	Elf64_Xword		struct_sym_size = detect_struct_size(file->class, sizeof(Elf64_Sym), sizeof(Elf32_Sym));

	for (Elf64_Xword i = 0; i < file->symtab_size; i += struct_sym_size) {
		Elf64_Word 	name_idx = get_Sym_name((file->symtab + i), file->endian, file->class);
		const char	*name = strtab + name_idx;
		uint8_t		type = ELF32_ST_TYPE(get_Sym_info((file->symtab + i), file->class));
		
		if (name && *name && !is_source_file(type)) {
			t_sym_tab *sym_node = ft_calloc(sizeof(t_sym_tab), 1);
		
			if (!sym_node) {
				ft_printf_fd(1, RED"ft_nm: Alloc error display symb\n"RESET);
				if (name_lst) {
					lst_clear(&name_lst, free);
				}
				return (NULL); /* need to return return NULL or error here */
			}
			*sym_node = fill_sym_node(file, strtab, i, name_idx, type);
			ft_lstadd_back(&name_lst, ft_lstnew(sym_node));
		}
	}
	return (name_lst);
}

/** 
 *	@brief Display symbole
 * 	@param file pointer on file struct
 * 	@param sizeof_Sshdr size of section header
 * 	@return 0 if success otherwise -1
*/
static int8_t real_display_symbol(t_elf_file *file, int16_t sizeof_Sshdr)
{
	char 		*strtab = get_strtab(file->ptr, sizeof_Sshdr, file->endian, file->class);
	if (!strtab) {
		ft_printf_fd(1, RED"ft_nm: Error no .strtab found\n"RESET);
		return (1);
	}
	t_list *name_lst = build_symbole_list(file, strtab);
	if (!name_lst) {
		ft_printf_fd(2, "No symbole found or malloc error\n");
		return (1); /* need to return value here*/
	}
	lst_name_sort(name_lst);
	for (t_list *current = name_lst; current; current = current->next) {
		t_sym_tab *symbole = (t_sym_tab *) ((t_list *) current)->content;
		uint8_t pad = get_zero_padding(file->class, compute_hex_len(symbole->value), symbole->shndx != SHN_UNDEF);
		if (pad > 0) {
			insert_pad(pad, "0");
			display_sym_value(symbole->value, 1);
		} else {
			insert_pad(file->class == 1 ? 16 : 8, " "); /* replace this hardcode shit */
		}
		uint8_t symbole_char = get_symbole_char(file, symbole, sizeof_Sshdr);
		ft_printf_fd(1, " %c %s\n",symbole_char, (char *) symbole->sym_name);
	}
	lst_clear(&name_lst, free);
	return (0);

}

/** 
 *	@brief Display file symbole
 *	@param file pointer on file struct
*/
int8_t display_file_symbole(t_elf_file *file)
 {
	uint16_t	sizeof_Sshdr = detect_struct_size(file->class, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	void		*section_header = (file->ptr + get_Ehdr_shoff(file->ptr, file->endian));
	uint16_t	max = get_Ehdr_shnum(file->ptr, file->endian);
	char 		*shstrtab = get_shstrtab(file->ptr, file->endian, file->class);
	
	for (uint16_t i = 0; i < max; ++i) {
		void *s_hptr = (section_header + (sizeof_Sshdr * i));
		if (get_Shdr_type(s_hptr, file->endian, file->class) == SHT_SYMTAB) { /* 2 hardcode symtab value */
			// strtab_off = get_Shdr_offset(s_hptr, file->endian, file->class);
			uint16_t name_idx = get_Shdr_name(s_hptr, file->endian, file->class);
			if (ft_strcmp(((char *) shstrtab + name_idx), ".symtab") == 0) {
				file->symtab_size = get_Shdr_size(s_hptr, file->endian, file->class);
				Elf64_Off symoffset = get_Shdr_offset(s_hptr, file->endian, file->class);
				file->symtab = file->ptr + symoffset;
				break;
			}
		}
	}
	// if (real_display_symbol(file, sizeof_Sshdr) == -1) {
	// 	return (-1);
	// }
	// return (0);
	return (real_display_symbol(file, sizeof_Sshdr));
 }