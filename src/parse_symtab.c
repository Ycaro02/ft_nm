#include "../include/nm.h"

/* Symbol name (string tbl index) */
Elf64_Word get_symbol_name(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_name, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_name, endian));
}

/* Symbol type and binding */
static inline unsigned char get_symbol_info(void *ptr, int8_t is_elf64) {
    if (is_elf64) {
        return ((unsigned char)(((Elf64_Sym *) ptr)->st_info));
    }
    return ((unsigned char)(((Elf32_Sym *) ptr)->st_info));
}

/* Symbol visibility */
static inline unsigned char get_symbol_other(void *ptr, int8_t is_elf64) {
    if (is_elf64) {
        return ((unsigned char)(((Elf64_Sym *) ptr)->st_other));
    }
    return ((unsigned char)(((Elf32_Sym *) ptr)->st_other));
}

/* Section index */
static inline Elf64_Section get_symbol_shndx(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_shndx, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_shndx, endian));
}

/* Symbol value */
static inline Elf64_Addr get_symbol_value(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_value, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_value, endian));
}

/* Symbol size */
static inline Elf64_Xword get_symbol_size(void *ptr, int8_t endian, int8_t is_elf64) {
    if (is_elf64) {
        return (READ_DATA(((Elf64_Sym *) ptr)->st_size, endian));
    }
    return (READ_DATA(((Elf32_Sym *) ptr)->st_size, endian));
}

void display_symbol_info(void *sym_ptr, int8_t endian, int8_t is_elf64) {
    ft_printf_fd(1, YELLOW"S name:%s%s|%d| "RESET, RESET, GREEN, get_symbol_name(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S info:%s%s|%d| "RESET, RESET, GREEN, get_symbol_info(sym_ptr, is_elf64));
    ft_printf_fd(1, YELLOW"S other:%s%s|%d| "RESET, RESET, GREEN, get_symbol_other(sym_ptr, is_elf64));
    ft_printf_fd(1, YELLOW"S shndx:%s%s|%d| "RESET, RESET, GREEN, get_symbol_shndx(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S value:%s%s|%p| "RESET, RESET, GREEN, get_symbol_value(sym_ptr, endian, is_elf64));
    ft_printf_fd(1, YELLOW"S size:%s%s|%d|\n"RESET, RESET, GREEN, get_symbol_size(sym_ptr, endian, is_elf64));
}