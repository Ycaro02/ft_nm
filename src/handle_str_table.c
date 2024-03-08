# include "../include/nm.h"

/** 
 *	@brief Get section header strtab
 *	@param ptr pointer on elf struct
 *	@param endian endian value
 *	@param is_elf64 1 for 64 bits 0 for 32 bits
 *	@return shstrtab pointer
*/
void *get_shstrtab(void *ptr, int8_t endian, int8_t is_elf64)
{
	uint16_t	sizeof_Sshdr = detect_struct_size(is_elf64, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	/* section header ptr, base pointer + section header offset */
	void		*section_header = (ptr + get_Ehdr_shoff(ptr, endian));
	/* section_header_strtab, sectionheader[idx], section header str index */
	Elf64_Half shstrtab_idx = get_Ehdr_shstrndx(ptr, endian);
	if (shstrtab_idx > get_Ehdr_shnum(ptr, endian)) {
		ft_printf_fd(2, "No shstrtab found, bad index %d, max: %d\n", shstrtab_idx, get_Ehdr_shnum(ptr, endian));
		return (NULL);
	}
	void *section_shstrtab = section_header + (sizeof_Sshdr * shstrtab_idx);
	void *shstrtab = ptr + get_Shdr_offset(section_shstrtab, endian, is_elf64);
	return (shstrtab);
}

/** 
 *	@brief Get strtab
 * 	@param ptr pointer on elf struct
 * 	@param sizeof_Sshdr size of section header
 * 	@param endian endian value
 * 	@param is_elf64 1 for 64 bits 0 for 32 bits
 * 	@return strtab pointer
*/
char *get_strtab(void *ptr, uint16_t sizeof_Sshdr, int8_t endian, int8_t is_elf64)
{
	char		*strtab = NULL,	*shstrtab = get_shstrtab(ptr, endian, is_elf64);
	void		*section_header = (ptr + get_Ehdr_shoff(ptr, endian));
	uint16_t	max = get_Ehdr_shnum(ptr, endian);

	if (!shstrtab) {
		return (NULL);
	}
	/* safe loop here shnum already verify */
	for (uint16_t i = 0; i < max; ++i) {
		void *sh_ptr = (section_header + (sizeof_Sshdr * i));

		if (get_Shdr_type(sh_ptr, endian, is_elf64) == SHT_STRTAB) {
			uint16_t name_idx = get_Shdr_name(sh_ptr, endian, is_elf64); /* need to check idx here, get shstrtab len todo that */
			if (ft_strcmp(((char *) shstrtab + name_idx), ".strtab") == 0) {
				// ft_printf_fd(1, RED"Found strtab addr: [%p], |%s|\n"RESET, (shstrtab + name_idx), ((char *) shstrtab + name_idx));
				strtab = ptr + get_Shdr_offset(sh_ptr, endian, is_elf64);
				break;
			}
		}
	}
	return (strtab);
}
