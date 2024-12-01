#ifndef ELF_GETTER_H
# define ELF_GETTER_H 1

# include "../libft/basic_define.h" 	/* Color */

typedef struct s_elf_file t_elf_file;

/* elf header getter */
Elf64_Half		get_Ehdr_type(void *ptr, int8_t endian);
Elf64_Half		get_Ehdr_machine(void *ptr, int8_t endian);
Elf64_Word		get_Ehdr_version(void *ptr, int8_t endian);
Elf64_Addr		get_Ehdr_entry(void *ptr, int8_t endian);
Elf64_Off		get_Ehdr_phoff(void *ptr, int8_t endian);
Elf64_Off		get_Ehdr_shoff(void *ptr, int8_t endian);
Elf64_Word		get_Ehdr_flags(void *ptr, int8_t endian);
Elf64_Half		get_Ehdr_ehsize(void *ptr, int8_t endian);
Elf64_Half		get_Ehdr_phentsize(void *ptr, int8_t endian);
Elf64_Half		get_Ehdr_phnum(void *ptr, int8_t endian);
Elf64_Half		get_Ehdr_shentsize(void *ptr, int8_t endian);
Elf64_Half		get_Ehdr_shnum(void *ptr, int8_t endian);
Elf64_Half		get_Ehdr_shstrndx(void *ptr, int8_t endian);

/* section header getter */
Elf64_Word		get_Shdr_name(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Word		get_Shdr_type(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword		get_Shdr_flags(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Addr		get_Shdr_addr(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Off		get_Shdr_offset(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword		get_Shdr_size(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Word		get_Shdr_link(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword		get_Shdr_addralign(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword		get_Shdr_entsize(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Word		get_Shdr_info(void *ptr, int8_t endian, int8_t is_elf64);
void 			*get_section_header(t_elf_file *file);

/* symbole getter */
Elf64_Word		get_Sym_name(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Addr		get_Sym_value(void *ptr, int8_t endian, int8_t is_elf64);
uint8_t			get_Sym_info(void *ptr, int8_t is_elf64);
Elf64_Section	get_Sym_shndx(void *ptr, int8_t endian, int8_t is_elf64);

#endif /* ELF_GETTER_H */