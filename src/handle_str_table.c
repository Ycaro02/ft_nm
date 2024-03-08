# include "../include/nm.h"

static uint8_t invalid_strtab(char *strtab, void* end_of_file)
{
	while (strtab != end_of_file) {
		if (*strtab == '\0') {
			break;
		}
		++strtab;
	}
	return ((void *)strtab == end_of_file);
}

/** 
 *	@brief Get section header strtab
 *	@param ptr pointer on elf struct
 *	@param endian endian value
 *	@param is_elf64 1 for 64 bits 0 for 32 bits
 *	@return shstrtab pointer
*/
void *get_shstrtab(t_elf_file *file, int8_t endian, int8_t is_elf64)
{
	void		*ptr = file->ptr;
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

	if (invalid_strtab(shstrtab, file->ptr + file->file_size)) {
		ft_printf_fd(2, "Invalid format no valid shstrtab\n");
		return (NULL);
	}

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
char *get_strtab(t_elf_file *file, uint16_t sizeof_Sshdr, int8_t endian, int8_t is_elf64)
{
	void		*ptr = file->ptr;
	char		*strtab = NULL,	*shstrtab = get_shstrtab(file, endian, is_elf64);
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
				strtab = ptr + get_Shdr_offset(sh_ptr, endian, is_elf64);
				if (invalid_strtab(strtab, file->ptr + file->file_size)) {
					ft_printf_fd(2, "Invalid format no valid strtab\n");
					return (NULL);
				}
				// ft_printf_fd(2, RED"Found strtab addr: [%p], name |%s|, size %u\n"RESET, (shstrtab + name_idx), ((char *) shstrtab + name_idx));
				break;
			}
		}
	}
	return (strtab);
}
