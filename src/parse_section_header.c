#include "../include/nm.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Shdr/Elf32_Shdr                           //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/**
 * Getter value for section header table (Elf64/32_Shdr) structure array
*/
/* Section name (string tbl index) */
Elf64_Word get_section_header_name(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_name, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_name, endian));
}

/* Section type */
Elf64_Word get_section_header_type(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_type, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_type, endian));
}

/* Section flags */
Elf64_Xword get_section_header_flags(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_flags, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_flags, endian));
}

/* Section virtual address at execution */
Elf64_Addr get_section_header_addr(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_addr, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_addr, endian));
}

/* Section file offset */
Elf64_Off get_section_header_offset(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_offset, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_offset, endian));
}

/* Section size in bytes */
Elf64_Xword get_section_header_size(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_size, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_size, endian));
}

/* Link to another section */
Elf64_Word get_section_header_link(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_link, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_link, endian));
}

/* Additional section information */
Elf64_Word get_section_header_info(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_info, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_info, endian));
}

/* Section alignment */
Elf64_Xword get_section_header_addralign(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_addralign, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_addralign, endian));
}

/* Entry size if section holds table */
Elf64_Xword get_section_header_entsize(void *ptr, int8_t endian, int8_t is_elf64)
{
    if (is_elf64) {
        return (READ_DATA(((Elf64_Shdr *) ptr)->sh_entsize, endian));
    }
    return (READ_DATA(((Elf32_Shdr *) ptr)->sh_entsize, endian));
}

void display_section_header_info(void *sh_ptr, int8_t endian, int8_t class)
{
    ft_printf_fd(1, YELLOW"S name:%s%s|%d| "RESET,RESET, GREEN, get_section_header_name(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S type:%s%s|%d| "RESET,RESET, GREEN, get_section_header_type(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S flags:%s%s|%p| "RESET,RESET, GREEN, get_section_header_flags(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S addr:%s%s|%p| "RESET,RESET, GREEN, get_section_header_addr(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S offset:%s%s|%p| "RESET,RESET, GREEN, get_section_header_offset(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S size:%s%s|%d| "RESET,RESET, GREEN, get_section_header_size(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S link:%s%s|%d| "RESET,RESET, GREEN, get_section_header_link(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S info:%s%s|%d| "RESET,RESET, GREEN, get_section_header_info(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S align:%s%s|%d| "RESET,RESET, GREEN, get_section_header_addralign(sh_ptr, endian, class));
    ft_printf_fd(1, YELLOW"S entsize:%s%s|%d| "RESET,RESET, GREEN, get_section_header_entsize(sh_ptr, endian, class));
}
