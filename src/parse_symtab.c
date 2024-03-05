#include "../include/nm.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Sym/Elf32_Sym							  //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/**
 * Getter value for symbole table (Elf64/32_sym) structure array
*/
/* Symbol name (string tbl index) */
Elf64_Word get_symbol_name(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_name, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_name, endian));
}

/* Symbol type and binding */
uint8_t get_symbol_info(void *ptr, int8_t is_elf64) {
    if (is_elf64) {
        return ((uint8_t)(((Elf64_Sym *) ptr)->st_info));
    }
    return ((uint8_t)(((Elf32_Sym *) ptr)->st_info));
}

/* Symbol visibility */
uint8_t get_symbol_other(void *ptr, int8_t is_elf64) {
    if (is_elf64) {
        return ((uint8_t)(((Elf64_Sym *) ptr)->st_other));
    }
    return ((uint8_t)(((Elf32_Sym *) ptr)->st_other));
}

/* Section index */
Elf64_Section get_symbol_shndx(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_shndx, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_shndx, endian));
}

/* Symbol value */
Elf64_Addr get_symbol_value(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_value, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_value, endian));
}

/* Symbol size */
Elf64_Xword get_symbol_size(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_size, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_size, endian));
}

/** 
 * @brief disaplay symbole information with getter call
*/
void display_symbol_info(void *sym_ptr, int8_t endian, int8_t is_elf64) {
    ft_printf_fd(1, YELLOW"S name:%s%s|%d| "RESET, RESET, GREEN, get_symbol_name(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S info:%s%s|%d| "RESET, RESET, GREEN, get_symbol_info(sym_ptr, is_elf64));
    ft_printf_fd(1, YELLOW"S other:%s%s|%d| "RESET, RESET, GREEN, get_symbol_other(sym_ptr, is_elf64));
    ft_printf_fd(1, YELLOW"S shndx:%s%s|%d| "RESET, RESET, GREEN, get_symbol_shndx(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S value:%s%s|%p| "RESET, RESET, GREEN, get_symbol_value(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S size:%s%s|%d|\n"RESET, RESET, GREEN, get_symbol_size(sym_ptr, endian, is_elf64));
}