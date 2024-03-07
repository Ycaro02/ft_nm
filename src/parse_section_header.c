#include "../include/nm.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Shdr/Elf32_Shdr                           //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/**
 * Getter value for section header table (Elf64/32_Shdr) structure array
*/
/* @brief Section name (string tbl index) */
Elf64_Word get_Shdr_name(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_name, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_name, endian));
}

/* @brief Section type */
Elf64_Word get_Shdr_type(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_type, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_type, endian));
}

/* @brief Section flags */
Elf64_Xword get_Shdr_flags(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_flags, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_flags, endian));
}

/* @brief Section virtual address at execution */
Elf64_Addr get_Shdr_addr(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_addr, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_addr, endian));
}

/* @brief Section file offset */
Elf64_Off get_Shdr_offset(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_offset, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_offset, endian));
}

/* @brief Section size in bytes */
Elf64_Xword get_Shdr_size(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_size, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_size, endian));
}

/* @brief Link to another section */
Elf64_Word get_Shdr_link(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_link, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_link, endian));
}

/* @brief Additional section information */
Elf64_Word get_Shdr_info(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_info, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_info, endian));
}

/* @brief Section alignment */
Elf64_Xword get_Shdr_addralign(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_addralign, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_addralign, endian));
}

/* @brief Entry size if section holds table */
Elf64_Xword get_Shdr_entsize(void *ptr, int8_t endian, int8_t is_elf64)
{
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_entsize, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_entsize, endian));
}


/** @brief display section header information
 * 	@param sh_ptr pointer on section header struct
 * 	@param endian endian value
 * 	@param class 1 for 64 bits 0 for 32 bits
*/
void display_section_header_info(void *sh_ptr, int8_t endian, int8_t class)
{
    ft_printf_fd(1, YELLOW"S name:%s%s|%d| "RESET,RESET, GREEN, get_Shdr_name(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S type:%s%s|%d| "RESET,RESET, GREEN, get_Shdr_type(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S flags:%s%s|%p| "RESET,RESET, GREEN, get_Shdr_flags(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S addr:%s%s|%p| "RESET,RESET, GREEN, get_Shdr_addr(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S offset:%s%s|%p| "RESET,RESET, GREEN, get_Shdr_offset(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S size:%s%s|%d| "RESET,RESET, GREEN, get_Shdr_size(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S link:%s%s|%d| "RESET,RESET, GREEN, get_Shdr_link(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S info:%s%s|%d| "RESET,RESET, GREEN, get_Shdr_info(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S align:%s%s|%d| "RESET,RESET, GREEN, get_Shdr_addralign(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S entsize:%s%s|%d| "RESET,RESET, GREEN, get_Shdr_entsize(sh_ptr, endian, class));
}

/** @brief display all section header
 *	@param file pointer on file struct
*/	
 void display_all_section_header(t_elf_file *file) {
	uint16_t	sizeof_Sshdr = detect_struct_size(file->ptr, sizeof(Elf64_Shdr), sizeof(Elf32_Shdr)); 
	uint16_t	max = get_Ehdr_shnum(file->ptr, file->endian);
	void		*section_header = (file->ptr + get_Ehdr_shoff(file->ptr, file->endian));
	char 		*shstrtab = get_shstrtab(file->ptr, file->endian, file->class);
	ft_printf_fd(1, RED"Section header table\nSection header strtab:\n"RESET);
	for (uint16_t i = 0; i < max; ++i) {
		void *header_ptr = section_header + (sizeof_Sshdr * i);
		uint16_t name_idx = get_Shdr_name(header_ptr, file->endian, file->class);
		ft_printf_fd(1, YELLOW"|%s|\n"RESET, ((char * )(shstrtab + name_idx)));
	}
}