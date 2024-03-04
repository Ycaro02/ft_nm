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

static inline int check_identification_byte(char c, int val1, int val2)
{
	return ((c == val1 || c == val2));
}

/** @brief check if c value is between val1 and val2
 * 	@return bool 1 for true otherwise 0 
*/
static inline int check_range_int8_val(char c, int val1, int val2)
{
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
	ft_printf_fd(1, GREEN"Valid elf header: %s\n"RESET, ((char *) ((Elf64_Ehdr *) elf_struct)->e_ident));
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

uint16_t get_structure_size(void *elf_ptr, uint16_t size64, uint16_t size32)
{
	if (IS_ELF64(elf_ptr)) {
		return (size64);
	}
	return (size32);
}

void display_all_program_header(void *ptr, int8_t endian)
{
	uint16_t	struct_size = get_structure_size(ptr, sizeof(Elf64_Phdr), sizeof(Elf32_Phdr)); 
	void		*p_header = ptr + get_header_phoff(ptr, endian);
	uint16_t	max = get_header_phnum(ptr, endian);

	ft_printf_fd(1, RED"Program header table\n"RESET);

	for (uint16_t i = 0; i < max; ++i) {
		ft_printf_fd(1, BLUE"Idx [%d]\n"RESET, i);
		display_program_header_info(p_header + (struct_size * i), endian);
		ft_printf_fd(1, "\n");
	}
}

// Elf64_Off get_strtab_offset(void *ptr, int8_t endian, uint16_t max, uint16_t struct_size)
// {
// 	for (uint16_t i = 0; i < max; ++i) {
// 		ft_printf_fd(1, "Number [%d] type [%d]\n", i, get_section_header_type(ptr + (struct_size * i), endian));
// 		if (get_section_header_type(ptr + (struct_size * i), endian) == 3) { /* 3 hardcode strtab value */
// 			return (get_section_header_offset(ptr + (struct_size * i), endian));
// 		}
// 	}
// 	return (0);
// }

void *get_shstrtab(void *ptr, int8_t endian, int8_t is_elf64)
{
	uint16_t	struct_size = get_structure_size(ptr, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	void		*section_header = (ptr + get_header_shoff(ptr, endian));
	// uint16_t	max = get_header_shnum(ptr, endian);

	void *section_shstrtab = section_header + (struct_size * get_header_shstrndx(ptr, endian));
	void *shstrtab = ptr + get_section_header_offset(section_shstrtab, endian, is_elf64);
	return (shstrtab);
}

void display_all_section_header(void *ptr, int8_t endian, int8_t is_elf64)
 {
	uint16_t	struct_size = get_structure_size(ptr, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	void		*section_header = (ptr + get_header_shoff(ptr, endian));
	uint16_t	max = get_header_shnum(ptr, endian);
	ft_printf_fd(1, RED"Section header table\n"RESET);

	char *shstrtab = get_shstrtab(ptr, endian, is_elf64);
	for (uint16_t i = 0; i < max; ++i) {
		void *header_ptr = section_header + (struct_size * i);
		uint16_t name_idx = get_section_header_name(header_ptr, endian, is_elf64);
		ft_printf_fd(1, YELLOW"|%s|\n"RESET, ((char * )(shstrtab + name_idx)));
	}

	char *strtab = NULL;

	for (uint16_t i = 0; i < max; ++i) {
		ft_printf_fd(1, PURPLE"Idx [%d]\n"RESET, i);
		/* structure header pointer */
		void *s_hptr = (section_header + (struct_size * i));
		display_section_header_info(s_hptr, endian, is_elf64);
		ft_printf_fd(1, "\n");
		ft_printf_fd(1, "type [%d] %d\n", i, get_section_header_type(s_hptr, endian, is_elf64));
		if (get_section_header_type(s_hptr, endian, is_elf64) == 3u) { /* 3 hardcode strtab value */
			// strtab_off = get_section_header_offset(s_hptr, endian, is_elf64);
			uint16_t name_idx = get_section_header_name(s_hptr, endian, is_elf64);
			if (ft_strcmp(((char *) shstrtab + name_idx), ".strtab") == 0) {
				ft_printf_fd(1, RED"Found strtab addr: [%p], |%s|\n"RESET, (shstrtab + name_idx), ((char *) shstrtab + name_idx));
				strtab = shstrtab + name_idx;
				break;
			}
		}
	}

	void *symtab = NULL;
	Elf64_Xword section_size = 0;

	for (uint16_t i = 0; i < max; ++i) {
		void *s_hptr = (section_header + (struct_size * i));
		if (get_section_header_type(s_hptr, endian, is_elf64) == 2u) { /* 2 hardcode symtab value */
			// strtab_off = get_section_header_offset(s_hptr, endian, is_elf64);
			uint16_t name_idx = get_section_header_name(s_hptr, endian, is_elf64);
			if (ft_strcmp(((char *) shstrtab + name_idx), ".symtab") == 0) {
				ft_printf_fd(1, RED"Found symtab addr: [%p], |%s|\n"RESET, (shstrtab + name_idx), ((char *) shstrtab + name_idx));
				section_size = get_section_header_size(s_hptr, endian, is_elf64);
				symtab = shstrtab + name_idx;
				break;
			}
		}
	}

	Elf64_Xword s_sym_size = get_structure_size(ptr, sizeof(Elf64_Sym), sizeof(Elf32_Sym));

	for (Elf64_Xword i = 0; i < section_size; i += s_sym_size) {
		void *s_symptr = symtab + i;
		display_symbol_info(s_symptr, endian, is_elf64);
		(void)strtab;
		// uint32_t name_idx = get_symbol_name(s_symptr, endian, is_elf64);
		// ft_printf_fd(1, RED"Symtab i: [%d], name idx [%d] |%s|\n"RESET, (i % s_sym_size), name_idx, ((char *) strtab + name_idx));
		// break;
	}

 }