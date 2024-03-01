# include "../include/nm.h"

int call_open(char *str)
{
	int fd = open(str, O_RDONLY);
	if (fd < 0) { /* maybe reject 0 ? */
		ft_printf_fd(2, "ft_nm: Can't open %s fd %d\n", str, fd);
		return (-1);
	}
	return (fd);
}

void *load_elf_info(int fd, size_t len)
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

__always_inline int check_identification_byte(char c, int val1, int val2)
{
	return ((c == val1 || c == val2));
}

/** @brief check if c value is between val1 and val2
 * 	@return bool 1 for true otherwise 0 
*/
__always_inline int check_range_int8_val(char c, int val1, int val2)
{
	return ((c >= val1 && c <= val2));
}

__always_inline int detect_os_abi(uint8_t os_abi)
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
