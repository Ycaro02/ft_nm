#include "../include/nm.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                                                            //
//                            Elf64_Sym/Elf32_Sym							  //
//                                                                            //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/**
 * Getter value for symbole table (Elf64/32_sym) structure array
*/

/* @brief get Symbol name (string tbl index) */
Elf64_Word get_Sym_name(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_name, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_name, endian));
}

/* @brief get Symbol type and binding */
uint8_t get_Sym_info(void *ptr, int8_t is_elf64) {
    if (is_elf64) {
        return ((uint8_t)(((Elf64_Sym *) ptr)->st_info));
    }
    return ((uint8_t)(((Elf32_Sym *) ptr)->st_info));
}

/* @brief get Symbol visibility */
uint8_t get_Sym_other(void *ptr, int8_t is_elf64) {
    if (is_elf64) {
        return ((uint8_t)(((Elf64_Sym *) ptr)->st_other));
    }
    return ((uint8_t)(((Elf32_Sym *) ptr)->st_other));
}

/* @brief get Section index */
Elf64_Section get_Sym_shndx(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_shndx, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_shndx, endian));
}

/* @brief get Symbol value */
Elf64_Addr get_Sym_value(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_value, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_value, endian));
}

/* @brief get Symbol size */
Elf64_Xword get_Sym_size(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_size, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_size, endian));
}

/** 
 * @brief disaplay symbole information with getter call
*/
void display_symbol_info(void *sym_ptr, int8_t endian, int8_t is_elf64) {
    ft_printf_fd(1, YELLOW"S name:%s%s|%d| "RESET, RESET, GREEN, get_Sym_name(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S info:%s%s|%d| "RESET, RESET, GREEN, get_Sym_info(sym_ptr, is_elf64));
    ft_printf_fd(1, YELLOW"S other:%s%s|%d| "RESET, RESET, GREEN, get_Sym_other(sym_ptr, is_elf64));
    ft_printf_fd(1, YELLOW"S shndx:%s%s|%d| "RESET, RESET, GREEN, get_Sym_shndx(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S value:%s%s|%p| "RESET, RESET, GREEN, get_Sym_value(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S size:%s%s|%d|\n"RESET, RESET, GREEN, get_Sym_size(sym_ptr, endian, is_elf64));
}