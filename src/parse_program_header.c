#include "../include/nm.h"

// typedef struct
// {
//   Elf64_Word	p_type;			
//   Elf64_Word	p_flags;		
//   Elf64_Off	p_offset;		
//   Elf64_Addr	p_vaddr;		
//   Elf64_Addr	p_paddr;		
//   Elf64_Xword	p_filesz;		/* Segment size in file */
//   Elf64_Xword	p_memsz;		/* Segment size in memory */
//   Elf64_Xword	p_align;		/* Segment alignment */
// } Elf64_Phdr;

/* Segment type */
Elf64_Word get_program_header_type(void *ptr, int8_t endian) {
    if (IS_ELF64(ptr)) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_type, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_type, endian));
}

/* Segment flags */
Elf64_Word get_program_header_flags(void *ptr, int8_t endian) {
    if (IS_ELF64(ptr)) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_flags, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_flags, endian));
}

/* Segment file offset */
Elf64_Off get_program_header_offset(void *ptr, int8_t endian) {
    if (IS_ELF64(ptr)) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_offset, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_offset, endian));
}
/* Segment virtual address */
Elf64_Addr get_program_header_vaddr(void *ptr, int8_t endian) {
    if (IS_ELF64(ptr)) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_vaddr, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_vaddr, endian));
}
/* Segment physical address */
Elf64_Addr get_program_header_paddr(void *ptr, int8_t endian) {
    if (IS_ELF64(ptr)) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_paddr, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_paddr, endian));
}

Elf64_Xword get_program_header_filesz(void *ptr, int8_t endian) {
    if (IS_ELF64(ptr)) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_filesz, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_filesz, endian));
}


Elf64_Xword get_program_header_memsz(void *ptr, int8_t endian) {
    if (IS_ELF64(ptr)) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_memsz, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_memsz, endian));
}


Elf64_Xword get_program_header_align(void *ptr, int8_t endian) {
    if (IS_ELF64(ptr)) {
        return (READ_DATA(((Elf64_Phdr *) ptr)->p_align, endian));
    }
    return (READ_DATA(((Elf32_Phdr *) ptr)->p_align, endian));
}






void display_program_header_info(void *ph_ptr, int8_t endian)
{
	ft_printf_fd(1, YELLOW"Ptype:%s%s|%p| "RESET,RESET, GREEN, get_program_header_type(ph_ptr, endian));
	ft_printf_fd(1, YELLOW"P flags:%s%s|%p| "RESET,RESET, GREEN, get_program_header_flags(ph_ptr, endian));
	ft_printf_fd(1, YELLOW"P offset:%s%s|%p| "RESET,RESET, GREEN, get_program_header_offset(ph_ptr, endian));
	ft_printf_fd(1, YELLOW"P vaddr:%s%s|%p| "RESET,RESET, GREEN, get_program_header_vaddr(ph_ptr, endian));
	ft_printf_fd(1, YELLOW"P paddr:%s%s|%p| "RESET,RESET, GREEN, get_program_header_paddr(ph_ptr, endian));
    ft_printf_fd(1, YELLOW"P fileS:%s%s|%p| "RESET,RESET, GREEN, get_program_header_filesz(ph_ptr, endian));
	ft_printf_fd(1, YELLOW"P memS:%s%s|%p| "RESET,RESET, GREEN, get_program_header_memsz(ph_ptr, endian));
	ft_printf_fd(1, YELLOW"P align:%s%s|%p| "RESET,RESET, GREEN, get_program_header_align(ph_ptr, endian));
}
