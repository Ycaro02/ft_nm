#include "../include/nm.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Phdr/Elf32_Phdr                           //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/**
 * Getter value for program header structure
*/

/* @brief get Segment type */
Elf64_Word get_program_header_type(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_type, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_type, endian));
}

/* @brief get Segment file offset */
Elf64_Off get_program_header_offset(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_offset, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_offset, endian));
}
/* @brief get Segment virtual address */
Elf64_Addr get_program_header_vaddr(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_vaddr, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_vaddr, endian));
}
/* @brief get Segment physical address */
Elf64_Addr get_program_header_paddr(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_paddr, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_paddr, endian));
}
/* @brief get Segment size in file */
Elf64_Xword get_program_header_filesz(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_filesz, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_filesz, endian));
}

/* @brief get Segment size in memory */
Elf64_Xword get_program_header_memsz(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_memsz, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_memsz, endian));
}

/* @brief get Segment flags */
Elf64_Word get_program_header_flags(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_flags, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_flags, endian));
}

/* @brief get Segment alignment */
Elf64_Xword get_program_header_align(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_align, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_align, endian));
}

/** 
 *  @brief Get section header offset
 *  @param Program header ptr
 *  @param endian
*/
void display_program_header_info(void *ph_ptr, int8_t endian, int8_t is_elf64)
{
	ft_printf_fd(1, YELLOW"Ptype:%s%s|%p| "RESET,RESET, GREEN, get_program_header_type(ph_ptr, endian, is_elf64));
	ft_printf_fd(1, YELLOW"P flags:%s%s|%p| "RESET,RESET, GREEN, get_program_header_flags(ph_ptr, endian, is_elf64));
	ft_printf_fd(1, YELLOW"P offset:%s%s|%p| "RESET,RESET, GREEN, get_program_header_offset(ph_ptr, endian, is_elf64));
	ft_printf_fd(1, YELLOW"P vaddr:%s%s|%p| "RESET,RESET, GREEN, get_program_header_vaddr(ph_ptr, endian, is_elf64));
	ft_printf_fd(1, YELLOW"P paddr:%s%s|%p| "RESET,RESET, GREEN, get_program_header_paddr(ph_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"P fileS:%s%s|%p| "RESET,RESET, GREEN, get_program_header_filesz(ph_ptr, endian, is_elf64));
	ft_printf_fd(1, YELLOW"P memS:%s%s|%p| "RESET,RESET, GREEN, get_program_header_memsz(ph_ptr, endian, is_elf64));
	ft_printf_fd(1, YELLOW"P align:%s%s|%p| "RESET,RESET, GREEN, get_program_header_align(ph_ptr, endian, is_elf64));
}

/** 
 *	@brief Get section header offset
 *	@param file pointer nm_file context
*/
void display_all_program_header(t_elf_file *file)
{
	uint16_t	sizeof_Sshdr = detect_struct_size(file->ptr, sizeof(Elf64_Phdr), sizeof(Elf32_Phdr)); 
	void		*p_header = file->ptr + get_Ehdr_phoff(file->ptr, file->endian);
	uint16_t	max = get_Ehdr_phnum(file->ptr, file->endian);

	ft_printf_fd(1, RED"Program header table\n"RESET);

	for (uint16_t i = 0; i < max; ++i) {
		ft_printf_fd(1, BLUE"Idx [%d]\n"RESET, i);
		display_program_header_info(p_header + (sizeof_Sshdr * i), file->endian, file->class);
		ft_printf_fd(1, "\n");
	}
}