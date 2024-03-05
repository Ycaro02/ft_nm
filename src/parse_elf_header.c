# include "../include/nm.h"

/*Get all Elf64_Ehdr */

/* Get header type  */ 
static inline Elf64_Half get_header_type(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_type, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_type, endian));
}

/* Get machine */
static inline Elf64_Half get_header_machine(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_machine, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_machine, endian));
}

/* Get version */
static inline Elf64_Word get_header_version(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_version, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_version, endian));
}

/* Get addr entry point */
static inline Elf64_Addr get_header_entry(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_entry, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_entry, endian));
}

/* Get Program header table file offset */
static inline Elf64_Off get_header_phoff(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phoff, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phoff, endian));
}

/* Get Section header table file offset */
static inline Elf64_Off get_header_shoff(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shoff, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shoff, endian));
}

/* Get Processor-specific flags */
static inline Elf64_Word get_header_flags(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_flags, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_flags, endian));
}

/* ELF header size in bytes */
static inline Elf64_Half get_header_ehsize(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_ehsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_ehsize, endian));
}

/* Program header table entry size */
static inline Elf64_Half get_header_phentsize(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phentsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phentsize, endian));
}

/* Program header table entry count */
static inline Elf64_Half get_header_phnum(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phnum, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phnum, endian));
}

/* Section header table entry size */
static inline Elf64_Half get_header_shentsize(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shentsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shentsize, endian));
}

/* Section header table entry count */
static inline Elf64_Half get_header_shnum(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shnum, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shnum, endian));
}

/* Section header string table index */
static inline Elf64_Half get_header_shstrndx(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shstrndx, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shstrndx, endian));
}

void display_elf_header(void *elf_struct, int8_t endian)
{
	ft_printf_fd(1, YELLOW"type:%s%s|%d| "RESET,RESET, GREEN, get_header_type(elf_struct, endian));
	ft_printf_fd(1, YELLOW"machine:%s%s|%d| "RESET,RESET, GREEN, get_header_machine(elf_struct, endian));
	ft_printf_fd(1, YELLOW"version:%s%s|%d| "RESET,RESET, GREEN, get_header_version(elf_struct, endian));
	ft_printf_fd(1, YELLOW"entry:%s%s|%p| "RESET,RESET, GREEN, get_header_entry(elf_struct, endian));
	ft_printf_fd(1, YELLOW"phoff:%s%s|%d| "RESET,RESET, GREEN, get_header_phoff(elf_struct, endian));
	ft_printf_fd(1, YELLOW"shoff:%s%s|%d| "RESET,RESET, GREEN, get_header_shoff(elf_struct, endian));
	ft_printf_fd(1, YELLOW"flags:%s%s|%d| "RESET,RESET, GREEN, get_header_flags(elf_struct, endian));
	ft_printf_fd(1, YELLOW"ehsize:%s%s|%d| "RESET,RESET, GREEN, get_header_ehsize(elf_struct, endian));
	ft_printf_fd(1, YELLOW"phentsize%s%s|%d| "RESET,RESET,GREEN, get_header_phentsize(elf_struct, endian));
	ft_printf_fd(1, YELLOW"phnum:%s%s|%d| "RESET,RESET, GREEN, get_header_phnum(elf_struct, endian));
	ft_printf_fd(1, YELLOW"shentsize%s%s|%d| "RESET,RESET,GREEN, get_header_shentsize(elf_struct, endian));
	ft_printf_fd(1, YELLOW"shnum:%s%s|%d| "RESET,RESET, GREEN, get_header_shnum(elf_struct, endian));
	ft_printf_fd(1, YELLOW"shstrndx:%s%s|%d|\n"RESET,RESET, GREEN, get_header_shstrndx(elf_struct, endian));
}

static int call_open(char *str)
{
	int fd = open(str, O_RDONLY);
	if (fd < 0) { /* maybe reject 0 ? */
		ft_printf_fd(2, "ft_nm: Can't open %s fd %d\n", str, fd);
		return (-1);
	}
	return (fd);
}

static void *load_elf_info(int fd, size_t len)
{
	void *elf_struct = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
	if (elf_struct == MAP_FAILED) {
		perror("Error mmap:\'"); 
		close(fd);
		return (NULL);
	}
	return (elf_struct);
}

/** @brief check if c value is val1 or val 2
 * 	@return bool 1 for true otherwise 0 
*/

static inline int check_identification_byte(char c, int val1, int val2) {
	return ((c == val1 || c == val2));
}

/** @brief check if c value is between val1 and val2
 * 	@return bool 1 for true otherwise 0 
*/
static inline int check_range_int8_val(char c, int val1, int val2) {
	return ((c >= val1 && c <= val2));
}

static inline int detect_os_abi(uint8_t os_abi)
{
	/* 0 >= os_abi <= 3 || 0 >= os_abi <= 12 || special os case */
	if (check_range_int8_val(os_abi, ELFOSABI_NONE, ELFOSABI_GNU)\
		|| check_range_int8_val(os_abi, ELFOSABI_SOLARIS, ELFOSABI_OPENBSD)\
		|| check_identification_byte(os_abi, ELFOSABI_ARM_AEABI, ELFOSABI_ARM)\
		|| os_abi == ELFOSABI_STANDALONE) {
		return (os_abi);	
	}
	ft_printf_fd(2, "Unknow os ABI %d\n", os_abi);
	return (-1);
}

/**@brief Parse header identification field
 * @param	char *str, file name to check
 * 			void *elf_struct pointer on elf header struct
*/
int header_identification_correct(char *str, void *elf_struct)
{
	/* check magic number ELFMAG */
	if (ft_strncmp(((char *) ((Elf64_Ehdr *) elf_struct)->e_ident), ELFMAG, SELFMAG) != 0) {
        ft_printf_fd(2, "field 0 %d\n", ELF_HFIELD(elf_struct, 0));
		ft_printf_fd(2, "ft_nm: %s: file format not recognized: %s\n", str, ((char *) ((Elf64_Ehdr *) elf_struct)->e_ident));
		return (FALSE);
	}
	/* get class 32 or 64 bits */
	char c = ELF_HFIELD(elf_struct, EI_CLASS);
	int ret = check_identification_byte(c, ELFCLASS32, ELFCLASS64);
	if (ret == FALSE) {
		ft_printf_fd(2, "Invalid class found: %d\n", c);
		return (ret);
	}
	/* get endian little or big */
	c = ELF_HFIELD(elf_struct, EI_DATA);
    ret = check_identification_byte(c, ELFDATA2LSB, ELFDATA2MSB);
	if (ret == FALSE) {
		ft_printf_fd(2, "Invalid endian found: %d\n", c);
		return (ret);
	}
	/* check version must be current version */
	if (((Elf64_Ehdr *) elf_struct)->e_ident[EI_VERSION] != EV_CURRENT) {
		ft_printf_fd(2, "Invalid version found: %d\n", ((Elf64_Ehdr *) elf_struct)->e_ident[EI_DATA]);
		return (FALSE);
	}
	/* detect os ABI */
	int os_abi = detect_os_abi(ELF_HFIELD(elf_struct, EI_OSABI));
	if (os_abi == -1) {
		return (FALSE);
	}
	int abi_version = ELF_HFIELD(elf_struct, EI_ABIVERSION); /* check this ? */
	(void)abi_version;
	ft_printf_fd(2, GREEN"Valid elf header: %s\n"RESET, ((char *) ((Elf64_Ehdr *) elf_struct)->e_ident));
	// int byte_pad = ((Elf64_Ehdr *) elf_struct)->e_ident[EI_PAD]; /* check this ? */
	
	return (TRUE);
}

void *parse_elf_header(char *str)
{
	void	*elf_struct = NULL;
	t_stat 	sb;

	int 	fd = call_open(str);
	if (fd < 0) {
		return (NULL);
	}
	if (fstat(fd, &sb) == -1) {
		perror("Error fstat:\'"); 
		close(fd);
		return (NULL);
	}
	elf_struct = load_elf_info(fd, sb.st_size);
	if (!elf_struct) { /* fd close in load_elf_info in error case */
		return (NULL);
	}
	close(fd); /* now we had data in void * we can close fd */
	if (header_identification_correct(str, elf_struct) == FALSE) {
		munmap(elf_struct, sb.st_size);
		elf_struct = NULL;
	}
	return (elf_struct);
}

uint16_t detect_struct_size(void *elf_ptr, uint16_t size64, uint16_t size32)
{
	return (IS_ELF64(elf_ptr) ? size64 : size32);
	// return ((IS_ELF64(elf_ptr) * size64) + (IS_ELF64(elf_ptr) * size32)); /* branchless version */
}

void display_all_program_header(t_nm_file *file)
{
	uint16_t	sizeof_Sshdr = detect_struct_size(file->ptr, sizeof(Elf64_Phdr), sizeof(Elf32_Phdr)); 
	void		*p_header = file->ptr + get_header_phoff(file->ptr, file->endian);
	uint16_t	max = get_header_phnum(file->ptr, file->endian);

	ft_printf_fd(1, RED"Program header table\n"RESET);

	for (uint16_t i = 0; i < max; ++i) {
		ft_printf_fd(1, BLUE"Idx [%d]\n"RESET, i);
		display_program_header_info(p_header + (sizeof_Sshdr * i), file->endian);
		ft_printf_fd(1, "\n");
	}
}

void *get_shstrtab(void *ptr, int8_t endian, int8_t is_elf64)
{
	uint16_t	sizeof_Sshdr = detect_struct_size(ptr, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	/* section header ptr, base pointer + section header offset */
	void		*section_header = (ptr + get_header_shoff(ptr, endian));
	/* section_header_strtab, sectionheader[idx], section header str index */
	void *section_shstrtab = section_header + (sizeof_Sshdr * get_header_shstrndx(ptr, endian));
	void *shstrtab = ptr + get_section_header_offset(section_shstrtab, endian, is_elf64);
	return (shstrtab);
}

char *get_strtab(void *ptr, uint16_t sizeof_Sshdr, int8_t endian, int8_t is_elf64)
{
	char		*strtab = NULL;
	char		*shstrtab = get_shstrtab(ptr, endian, is_elf64);
	void		*section_header = (ptr + get_header_shoff(ptr, endian));
	uint16_t	max = get_header_shnum(ptr, endian);

	for (uint16_t i = 0; i < max; ++i) {
		/* structure header pointer */
		void *s_hptr = (section_header + (sizeof_Sshdr * i));
		// display_section_header_info(s_hptr, endian, is_elf64);
		if (get_section_header_type(s_hptr, endian, is_elf64) == 3u) { /* 3 hardcode strtab value */
			// strtab_off = get_section_header_offset(s_hptr, endian, is_elf64);
			uint16_t name_idx = get_section_header_name(s_hptr, endian, is_elf64);
			if (ft_strcmp(((char *) shstrtab + name_idx), ".strtab") == 0) {
				// ft_printf_fd(1, RED"Found strtab addr: [%p], |%s|\n"RESET, (shstrtab + name_idx), ((char *) shstrtab + name_idx));
				strtab = ptr + get_section_header_offset(s_hptr, endian, is_elf64);
				break;
			}
		}
	}
	return (strtab);
}


void lst_name_sort(t_list *lst)
{
    if (!lst)
        return ;
    t_list *head = lst;
    t_list *min = NULL;
    while (lst)  {
        if (!min)
            min = lst;
        char *current = ((t_sym_tab *) ((t_list *) lst)->content)->sym_name;
        char *min_file = ((t_sym_tab *) ((t_list *) min)->content)->sym_name;
        if (ft_strcmp(current, min_file) <= 0)
            min = lst;
        lst = lst->next;
    }
    t_list *tmp = head->content;
    head->content = min->content;
    min->content = tmp;
    lst_name_sort(head->next);
}

int is_source_file(char *name)
{
	int len = ft_strlen(name);
	if (len > 2 && name[len - 2] == '.') {
		if (!ft_isdigit(name[len -1]))
			return (1);
	}
	return (0);
}

void	display_sym_value(unsigned long nbr, int fd)
{
	char	*base_16;

	base_16 = "0123456789abcdef";
	if (nbr > 15)
		display_sym_value(nbr / 16, fd);
	ft_putchar_fd(base_16[nbr % 16], fd);
}

uint8_t compute_hex_len(unsigned long nbr)
{
	uint8_t count = 0;
	while (nbr > 15) {
		nbr /= 16;
		count++;
	}
	return (count);
}

/* if elf 64, 16 digit else 8 - number len, all multiply by len != 0 to avoid protect if*/
uint8_t get_zero_padding(int8_t class, uint8_t len, int8_t is_undef)
{
	return (((class == 1 ? 16 : 8) - (len + 1)) * (is_undef));
}

void insert_pad(uint8_t pad, char *c)
{
	while (pad > 0) {
		ft_printf_fd(1, c);
		--pad;
	}
}

uint8_t get_symbole_char(t_nm_file *file, t_sym_tab *symbole, int16_t sizeof_Sshdr)
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
		Elf64_Half shnum = get_header_shnum(file->ptr, file->endian);
		if (shndx == SHN_ABS) {
			c = 'a';
		} else if (shndx == SHN_COMMON) {
			c = COMMON_SYM;
		}  else if (shndx < shnum) {
			void *section_header_ptr = file->ptr + get_header_shoff(file->ptr, file->endian) + (sizeof_Sshdr * shndx);
			Elf64_Word sh_type = get_section_header_type(section_header_ptr, file->endian, file->class);
			Elf64_Xword sh_flag = get_section_header_flags(section_header_ptr, file->endian, file->class);

			if (sh_type == SHT_NOBITS) {
				c = NO_BITS_SYM; /* b */
			} else if (sh_flag == (SHF_ALLOC | SHF_WRITE)) {
				c = ALLOC_WRITE_SYM; /* d */
			} else if (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_EXECINSTR)) {
				c = FUNCTION_SYM; /* T */
			} else if (sh_flag & SHF_ALLOC && !(sh_flag & SHF_WRITE) ) { /* obh sym R r*/
				c = OBJECT_SYM;
			}
			if ((c >= 'A' && c <= 'Z') && (c != UNDIFINED_SYM && symbole->bind != STB_GLOBAL)) {
				c += 32;
			}
		}
	}
	return (c);

	/* file->ptr + secion header offset, take shndx, get_symvole_shndx
		search in sh table if shndx < shnub s*/
	
}


void display_symbol(t_nm_file *file, int16_t sizeof_Sshdr)
{
	Elf64_Xword 	struct_sym_size = detect_struct_size(file->ptr, sizeof(Elf64_Sym), sizeof(Elf32_Sym));
	char 			*strtab = get_strtab(file->ptr, sizeof_Sshdr, file->endian, file->class);
	if (!strtab) {
		ft_printf_fd(1, RED"ft_nm: Error no .strtab found\n"RESET);
		return ;
	}

	t_list *name_lst = NULL;

	for (Elf64_Xword i = 0; i < file->symtab_size; i += struct_sym_size) {
		Elf64_Word 	name_idx = get_symbol_name((file->symtab + i), file->endian, file->class);
		// ft_printf_fd(1, "%s\n", ((char *) strtab + name_idx));
		char 		*name = strtab + name_idx;
		/* if (name && *name && name is not source/obj file) */
		if (name && *name && !is_source_file(name)) {
			t_sym_tab *sym_node = ft_calloc(sizeof(t_sym_tab), 1);
			if (!sym_node) {
				ft_printf_fd(1, RED"ft_nm: Alloc error display symb\n"RESET);
				return ; /* need to return return NULL or error here */
			}
			sym_node->sym_name = strtab + name_idx;
			sym_node->value = get_symbol_value((file->symtab + i), file->endian, file->class);
 			sym_node->type =  ELF32_ST_TYPE(get_symbol_info((file->symtab + i), file->class));
 			sym_node->bind = ELF32_ST_BIND(get_symbol_info((file->symtab + i), file->class));
			sym_node->shndx = get_symbol_shndx((file->symtab + i), file->endian, file->class);
			ft_lstadd_back(&name_lst, ft_lstnew(sym_node));

		}
	}

	lst_name_sort(name_lst);

	for (t_list *current = name_lst; current; current = current->next) {
		// ft_printf_fd(1, "%p A ", ((t_sym_tab *) ((t_list *) current)->content)->value);
		t_sym_tab *symbole = (t_sym_tab *) ((t_list *) current)->content;
		uint8_t pad = get_zero_padding(file->class, compute_hex_len(symbole->value), symbole->shndx != SHN_UNDEF);
		if (pad > 0) {
			insert_pad(pad, "0");
			display_sym_value(symbole->value, 1);
		} else {
			insert_pad(file->class == 1 ? 16 : 8, " "); /* replace this hardcode shit */
		}
		// uint8_t symbole_char = get_symbole_char(symbole->type, symbole->bind, symbole->shndx);
		uint8_t symbole_char = get_symbole_char(file, symbole, sizeof_Sshdr);
		ft_printf_fd(1, " %c %s\n",symbole_char, (char *) symbole->sym_name);
		// ft_printf_fd(2, YELLOW"char %c, |%u|\n"RESET, get_symbole_char(symbole->type, symbole->bind, sh_flag), sh_flag);

	}
	lst_clear(&name_lst, NULL);
}

void display_all_section_header(t_nm_file *file)
 {
	uint16_t	sizeof_Sshdr = detect_struct_size(file->ptr, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	void		*section_header = (file->ptr + get_header_shoff(file->ptr, file->endian));
	uint16_t	max = get_header_shnum(file->ptr, file->endian);
	char 		*shstrtab = get_shstrtab(file->ptr, file->endian, file->class);
	
	// ft_printf_fd(1, RED"Section header table\nSection header strtab:\n"RESET);

	// for (uint16_t i = 0; i < max; ++i) {
	// 	void *header_ptr = section_header + (sizeof_Sshdr * i);
	// 	uint16_t name_idx = get_section_header_name(header_ptr, file->endian, file->class);
	// 	ft_printf_fd(1, YELLOW"|%s|\n"RESET, ((char * )(shstrtab + name_idx)));
	// }


	for (uint16_t i = 0; i < max; ++i) {
		void *s_hptr = (section_header + (sizeof_Sshdr * i));
		if (get_section_header_type(s_hptr, file->endian, file->class) == 2u) { /* 2 hardcode symtab value */
			// strtab_off = get_section_header_offset(s_hptr, file->endian, file->class);
			uint16_t name_idx = get_section_header_name(s_hptr, file->endian, file->class);
			if (ft_strcmp(((char *) shstrtab + name_idx), ".symtab") == 0) {
				file->symtab_size = get_section_header_size(s_hptr, file->endian, file->class);
				Elf64_Off symoffset = get_section_header_offset(s_hptr, file->endian, file->class);
				file->symtab = file->ptr + symoffset;
				// sh_flag = get_section_header_flags(s_hptr, file->endian, file->class);
				// ft_printf_fd(1, RED"Found symtab offset: [%p], |%s| symtab = |%p| \n"RESET, symoffset, ((char *) shstrtab + name_idx), file->symtab);
			
				break;
			}
		}
	}

	display_symbol(file, sizeof_Sshdr);
 }