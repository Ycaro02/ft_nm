#include "../include/nm.h"
#include "../include/elf_getter.h"

/**
 *	@brief Update t_list node to accordate sort
 *	@param lst list node
 *	@param min min node
 *	@param reverse_opt reverse option
 *	@return min node
*/
static t_list *update_min(t_list *lst, t_list *min, uint8_t reverse_opt)
{
	t_sym_tab	*min_sym, *current = ((t_list *) lst)->content;
	int 		cmp;

	if (!min)
		min = lst;
	
	min_sym = ((t_list *) min)->content;
	cmp = ft_strcmp(current->sym_name, min_sym->sym_name);
	
	if (reverse_opt) {
		if (cmp > 0)
			min = lst;
		
	} else {
		if (cmp < 0)
			min = lst;
	} 
	if (cmp == 0) {
		if (current->value < min_sym->value)
			min = lst;
	}
	return (min);
}

/** 
 *	@brief Get symbol name
 * 	@param symbole struct list
*/
static void lst_name_sort(t_list *lst, uint8_t reverse_opt)
{
    t_list *head = lst;
    t_list *min = NULL, *tmp;
    
	if (!lst)
        return ;
    while (lst)  {
		min = update_min(lst, min, reverse_opt);
		lst = lst->next;
    }
    tmp = head->content;
    head->content = min->content;
    min->content = tmp;
    lst_name_sort(head->next, reverse_opt);
}

/* @brief is source file */
static int is_source_file(uint8_t type) {
	return ((type == STT_FILE || type == STT_SECTION));
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
	} else {
		Elf64_Half shnum = get_Ehdr_shnum(file->ptr, file->endian);
		
		if (shndx == SHN_ABS) {
			c = ABS_SYM;
			c += (symbole->bind != STB_GLOBAL) * 32;
		} else if (shndx == SHN_COMMON) {
			c = COMMON_SYM;
		}  else if (shndx < shnum) { /* section header index protect here */
			void *section_header_ptr = get_section_header(file) + (sizeof_Sshdr * shndx);
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
			} else if (sh_type == SHT_GROUP || sh_type == SHT_PROGBITS \
				|| ft_strncmp(symbole->sym_name, ".SUNW_signature", ft_strlen(".SUNW_signature")) == 0) {
				c = 'n';
			} 
			if (symbole->type == STT_SECTION \
				&& ft_strncmp(symbole->sym_name, ".debug", ft_strlen(".debug")) == 0) {
				return ('N');
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
static t_sym_tab fill_sym_node(t_elf_file *file, const char *name, Elf64_Xword i, uint8_t type)
{
	t_sym_tab symbole;
	symbole.sym_name = (char *)name;
	symbole.value = get_Sym_value((file->symtab + i), file->endian, file->class);
	symbole.type =  type;
	symbole.bind = ELF32_ST_BIND(get_Sym_info((file->symtab + i), file->class));
	symbole.shndx = get_Sym_shndx((file->symtab + i), file->endian, file->class);
	// ft_printf_fd(2, "\nFor %s value: %p\n", symbole.sym_name, symbole.value);
	return (symbole);
}

/** 
 *	@brief Build symbole list
 * 	@param file pointer on file struct
 * 	@param strtab pointer on string table
 * 	@return list of symbole
*/
static t_list *build_symbole_list(t_elf_file *file, char *strtab, uint8_t flag, int16_t sizeof_Sshdr)
{
	t_list			*name_lst = NULL;
	Elf64_Xword		struct_sym_size = detect_struct_size(file->class, sizeof(Elf64_Sym), sizeof(Elf32_Sym));

	/* 	symtabsize range checked in display_file_symbole
		same for name_idx, same logic that shstrtab get strtab len and check idx
	*/
	for (Elf64_Xword i = 0; i < file->symtab_size; i += struct_sym_size) {
		Elf64_Word 	name_idx = get_Sym_name((file->symtab + i), file->endian, file->class);
		const char	*name = strtab + name_idx;
		uint8_t		type = ELF32_ST_TYPE(get_Sym_info((file->symtab + i), file->class));
		/* Protect name idx here */
		if (check_end_of_file(file, strtab + name_idx)) {
			ft_printf_fd(2, "Invalid symbole name addr\n");
			return (NULL);
		}

		uint8_t bind = ELF32_ST_BIND(get_Sym_info((file->symtab + i), file->class));
		
		Elf64_Section sym_shndx = get_Sym_shndx((file->symtab + i), file->endian, file->class);

		if (has_flag(flag, G_OPTION) && bind != STB_GLOBAL) {
			if (bind != STB_WEAK)
				continue;
		}
		if (has_flag(flag, U_OPTION) && sym_shndx != SHN_UNDEF) {
			continue ;
		}
		// ft_printf_fd(2, "name: %s\n", name);
		if (!has_flag(flag, A_OPTION) && is_source_file(type)) {
			continue;
		}

		if (is_source_file(type)) {
			char *shstrtab = get_shstrtab(file, file->endian, file->class);
			if (type == STT_SECTION){
				// ft_printf_fd(2, RED"name: %s\n"RESET, "yo is section");
				void *sh_ptr = get_section_header(file);
				sh_ptr += (sizeof_Sshdr * sym_shndx);
				name_idx = get_Shdr_name(sh_ptr, file->endian, file->class);
				name = shstrtab + name_idx;
				// ft_printf_fd(2, YELLOW"name: %s\n"RESET, name);
				if (check_end_of_file(file, shstrtab + name_idx)) {
					ft_printf_fd(2, "Invalid symbole name addr (section header name)\n");
					continue ;
				}
			}
		}
		// ft_printf_fd(2, RED"before name: %s, %d\n"RESET, name, name[0]);
		
	
		// ft_printf_fd(2, CYAN"name: %p: %s, char[0] %d, char[1] %d\nCond %d\n"RESET, name, name, name[0], name[1], (has_flag(flag, A_OPTION) || name[0] != 0));

		if ((has_flag(flag, A_OPTION) && sym_shndx != SHN_UNDEF) || name[0] != 0) {
			t_sym_tab *sym_node = ft_calloc(sizeof(t_sym_tab), 1);
			if (!sym_node) {
				ft_printf_fd(1, RED"ft_nm: Alloc error display symb\n"RESET);
				lst_clear(&name_lst, free);
				return (NULL); /* need to return return NULL or error here */
			}
			*sym_node = fill_sym_node(file, name, i, type);
			ft_lstadd_back(&name_lst, ft_lstnew(sym_node));
		}
	}
	return (name_lst);
}

/** 
 *	@brief Get padding from class
 * 	@param class 1 for 64 bits 0 for 32 bits
 * 	@return number of padding char to insert
*/
static uint8_t padding_from_class(int8_t class) {
	return (class ? 16 : 8);
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
	return ((padding_from_class(class) - (len + 1)) * (is_undef));
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
 *	@brief Display symbole loop
 *	@param name_lst list of symbole
 *	@param file pointer on file struct
 *	@param sizeof_Sshdr size of section header
*/
static void display_sym_loop(t_list *name_lst, t_elf_file *file, int16_t sizeof_Sshdr, uint8_t flag)
{
	for (t_list *current = name_lst; current; current = current->next) {
		t_sym_tab	*symbole = (t_sym_tab *) ((t_list *) current)->content;
		uint8_t		pad = get_zero_padding(file->class, compute_hex_len(symbole->value), symbole->shndx != SHN_UNDEF);
		uint8_t 	symbole_char = get_symbole_char(file, symbole, sizeof_Sshdr);

		// if (has_flag(flag, A_OPTION) && symbole_char == DEBUG_SYM) {
		// 	if (symbole->bind == STB_GLOBAL)
		// 		symbole_char -= 32; /* go uppercase */
		// }
		(void)flag;

		if (pad > 0) {
			insert_pad(pad, "0");
			display_sym_value(symbole->value, 1);
		} else {
			insert_pad(padding_from_class(file->class), " ");
		}
		ft_printf_fd(1, " %c %s\n", symbole_char, (char *) symbole->sym_name);
	}
}

/** 
 *	@brief Display symbole
 * 	@param file pointer on file struct
 * 	@param sizeof_Sshdr size of section header
 * 	@return 0 if success otherwise -1
*/
static int8_t real_display_symbol(t_elf_file *file, int16_t sizeof_Sshdr, uint8_t nm_flag)
{
	t_list 		*name_lst;
	char 		*strtab = get_strtab(file, sizeof_Sshdr, file->endian, file->class);

	if (!strtab) {
		// ft_printf_fd(1, "bfd plugin: %s: file too short\n", file->name);
		ft_printf_fd(2, "ft_nm: %s: file format not recognized\n", file->name);
		return (1);
	}
	name_lst = build_symbole_list(file, strtab, nm_flag, sizeof_Sshdr);
	if (!name_lst) {
		ft_printf_fd(2, "No symbole found or malloc error\n");
		return (1); /* need to return value here*/
	}

	uint8_t reverse = has_flag(nm_flag, R_OPTION);

	if (!has_flag(nm_flag, P_OPTION)) {
		lst_name_sort(name_lst, reverse);
	}
	// if (reverse) {
	// 	reverse_lst(&name_lst);
	// }

	display_sym_loop(name_lst, file, sizeof_Sshdr, nm_flag);
	lst_clear(&name_lst, free);
	return (0);

}

/** 
 *	@brief Display file symbole
 *	@param file pointer on file struct
*/
int8_t display_file_symbole(t_elf_file *file, uint8_t nm_flag)
 {
	uint16_t	sizeof_Sshdr = detect_struct_size(file->class, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	void		*section_header = get_section_header(file);
	uint16_t	max = get_Ehdr_shnum(file->ptr, file->endian);
	
	if (!section_header) {
		return (1);
	}
	/* safe loop here shnum already checked */
	for (uint16_t i = 0; i < max; ++i) {
		void *sh_ptr = section_header + (sizeof_Sshdr * i);
		/* Get symtab here */
		if (get_Shdr_type(sh_ptr, file->endian, file->class) == SHT_SYMTAB) {
			Elf64_Off	symoffset = get_Shdr_offset(sh_ptr, file->endian, file->class); 
			void		*end_file = file->ptr + file->file_size; 
			
			file->symtab_size = get_Shdr_size(sh_ptr, file->endian, file->class);
			file->symtab = file->ptr + symoffset;
			/* check symbole table range start (offset) end (offset + size) */
			if (file->symtab >= end_file || file->symtab + file->symtab_size >= end_file) {
				ft_printf_fd(2, "Error file symtab\n");
				return (1);
			}
			break;
		}
	}
	return (real_display_symbol(file, sizeof_Sshdr, nm_flag));
 }