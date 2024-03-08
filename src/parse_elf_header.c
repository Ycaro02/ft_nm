# include "../include/nm.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Ehdr/Elf32_Ehdr                           //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/**
 * Getter value for elf header structure
*/

/* @brief Get header type  */ 
Elf64_Half get_Ehdr_type(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_type, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_type, endian));
}

/* @brief Get machine */
Elf64_Half get_Ehdr_machine(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_machine, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_machine, endian));
}

/* @brief Get version */
Elf64_Word get_Ehdr_version(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_version, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_version, endian));
}

/* @brief Get addr entry point */
Elf64_Addr get_Ehdr_entry(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_entry, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_entry, endian));
}

/* @brief Get Program header table file offset */
Elf64_Off get_Ehdr_phoff(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phoff, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phoff, endian));
}

/* @brief Get Section header table file offset */
Elf64_Off get_Ehdr_shoff(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shoff, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shoff, endian));
}

/* @brief Get Processor-specific flags */
Elf64_Word get_Ehdr_flags(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_flags, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_flags, endian));
}

/* @brief ELF header size in bytes */
Elf64_Half get_Ehdr_ehsize(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_ehsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_ehsize, endian));
}

/* @brief Program header table entry size */
Elf64_Half get_Ehdr_phentsize(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phentsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phentsize, endian));
}

/* @brief Program header table entry count */
Elf64_Half get_Ehdr_phnum(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phnum, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phnum, endian));
}

/* @brief Section header table entry size */
Elf64_Half get_Ehdr_shentsize(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shentsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shentsize, endian));
}

/* @brief Section header table entry count */
Elf64_Half get_Ehdr_shnum(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shnum, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shnum, endian));
}

/* @brief Section header string table index */
Elf64_Half get_Ehdr_shstrndx(void *ptr, int8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shstrndx, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shstrndx, endian));
}

/* GETTER END */

/** 
 *	@brief Display program header info
 *	@param Shdr pointer on section header struct table
*/
void display_elf_header(void *elf_struct, int8_t endian)
{
	ft_printf_fd(1, YELLOW"type:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_type(elf_struct, endian));
	ft_printf_fd(1, YELLOW"machine:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_machine(elf_struct, endian));
	ft_printf_fd(1, YELLOW"version:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_version(elf_struct, endian));
	ft_printf_fd(1, YELLOW"entry:%s%s|%p| "RESET,RESET, GREEN, get_Ehdr_entry(elf_struct, endian));
	ft_printf_fd(1, YELLOW"phoff:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_phoff(elf_struct, endian));
	ft_printf_fd(1, YELLOW"shoff:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_shoff(elf_struct, endian));
	ft_printf_fd(1, YELLOW"flags:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_flags(elf_struct, endian));
	ft_printf_fd(1, YELLOW"ehsize:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_ehsize(elf_struct, endian));
	ft_printf_fd(1, YELLOW"phentsize%s%s|%d| "RESET,RESET,GREEN, get_Ehdr_phentsize(elf_struct, endian));
	ft_printf_fd(1, YELLOW"phnum:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_phnum(elf_struct, endian));
	ft_printf_fd(1, YELLOW"shentsize%s%s|%d| "RESET,RESET,GREEN, get_Ehdr_shentsize(elf_struct, endian));
	ft_printf_fd(1, YELLOW"shnum:%s%s|%d| "RESET,RESET, GREEN, get_Ehdr_shnum(elf_struct, endian));
	ft_printf_fd(1, YELLOW"shstrndx:%s%s|%d|\n"RESET,RESET, GREEN, get_Ehdr_shstrndx(elf_struct, endian));
}

/** 
 *	@brief Load elf info in memory
 *	@param fd file descriptor
 *	@param len file size
 *	@return pointer on elf struct or NULL in case of error
*/
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

/** 
 *	@brief check if c value is val1 or val 2
 *	@return bool 1 for true otherwise 0 
*/
static int check_identification_byte(char c, int val1, int val2) {
	return ((c == val1 || c == val2));
}

/** 
 *	@brief check if c value is between val1 and val2
 *	@return bool 1 for true otherwise 0 
*/
static int check_range_int8_val(char c, int val1, int val2) {
	return ((c >= val1 && c <= val2));
}

static int detect_os_abi(uint8_t os_abi)
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

/**
 *	@brief Parse header identification field
 *	@param str file name to check
 *	@param elf_struct pointer on elf header struct
*/
static int header_identification_correct(char *str, void *elf_struct)
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
	// ft_printf_fd(2, GREEN"Valid elf header: %s\n"RESET, ((char *) ((Elf64_Ehdr *) elf_struct)->e_ident));
	// int byte_pad = ((Elf64_Ehdr *) elf_struct)->e_ident[EI_PAD]; /* check this ? */
	
	return (TRUE);
}

/** 
 *	@brief Parse elf header
 *	@param str file name
 *	@return pointer on elf struct or NULL in case of error
*/
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