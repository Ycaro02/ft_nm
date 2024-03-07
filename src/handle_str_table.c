# include "../include/nm.h"

/** @brief Get section header strtab
 *  @param ptr pointer on elf struct
 *	@param endian endian value
 *  @param is_elf64 1 for 64 bits 0 for 32 bits
 *  @return shstrtab pointer
*/
void *get_shstrtab(void *ptr, int8_t endian, int8_t is_elf64)
{
	uint16_t	sizeof_Sshdr = detect_struct_size(is_elf64, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	/* section header ptr, base pointer + section header offset */
	void		*section_header = (ptr + get_Ehdr_shoff(ptr, endian));
	/* section_header_strtab, sectionheader[idx], section header str index */
	void *section_shstrtab = section_header + (sizeof_Sshdr * get_Ehdr_shstrndx(ptr, endian));
	void *shstrtab = ptr + get_Shdr_offset(section_shstrtab, endian, is_elf64); /* TOCHECK */
	return (shstrtab);
}

/** @brief Get strtab
 * 	@param ptr pointer on elf struct
 * 	@param sizeof_Sshdr size of section header
 * 	@param endian endian value
 * 	@param is_elf64 1 for 64 bits 0 for 32 bits
 * 	@return strtab pointer
*/
char *get_strtab(void *ptr, uint16_t sizeof_Sshdr, int8_t endian, int8_t is_elf64)
{
	char		*strtab = NULL;
	char		*shstrtab = get_shstrtab(ptr, endian, is_elf64);
	void		*section_header = (ptr + get_Ehdr_shoff(ptr, endian));
	uint16_t	max = get_Ehdr_shnum(ptr, endian);

	for (uint16_t i = 0; i < max; ++i) {
		/* structure header pointer */
		void *s_hptr = (section_header + (sizeof_Sshdr * i));
		// display_section_header_info(s_hptr, endian, is_elf64);
		if (get_Shdr_type(s_hptr, endian, is_elf64) == SHT_STRTAB) { /* 3 hardcode strtab value */
			// strtab_off = get_Shdr_offset(s_hptr, endian, is_elf64);
			uint16_t name_idx = get_Shdr_name(s_hptr, endian, is_elf64);
			if (ft_strcmp(((char *) shstrtab + name_idx), ".strtab") == 0) {
				// ft_printf_fd(1, RED"Found strtab addr: [%p], |%s|\n"RESET, (shstrtab + name_idx), ((char *) shstrtab + name_idx));
				strtab = ptr + get_Shdr_offset(s_hptr, endian, is_elf64);
				break;
			}
		}
	}
	return (strtab);
}
