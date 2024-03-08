# ifndef FT_NM_HEADER
# define FT_NM_HEADER 1

# include <elf.h>						/* elf structure */
# include <sys/mman.h>					/* mmap */
# include <fcntl.h>						/* open */
# include <sys/stat.h>					/* fstat */
# include <stdlib.h>					/* exit NULL */
# include <stdio.h>						/* Perror */
# include "../libft/basic_define.h" 	/* Color */
# include "macro.h"						/* macro */
# include "../libft/libft.h" 			/* libft */
# include "../libft/list/linked_list.h" /* list */

/* Symbole char enum */
enum e_symb_char {
  UNDIFINED_SYM='U',				/* undefined symbole */
  ABS_SYM='A',      				/* absolute symbole */
  COMMON_SYM='C',   				/* common/shared symbole or file name */
  NO_BITS_SYM='B',					/* No bits symbole */
  ALLOC_WRITE_SYM='D',				/* if symbole section header flag alloc or write */
  FUNCTION_SYM='T', 				/* function symbole */
  OBJECT_SYM='R',					/* data object sym like variable */
  DEBUG_SYM='n',					/* debug symbole */
//   DATA_SYM='D',     				/* data object */
//   IFUNC_SYM='I',    				/* indirect function, real adress know at run time */
//   LOOS_SYM='O',     				/* specific os */
//   LOPROC_SYM='P',   				/* specific procesor */
//   NUM_SYM='N',      				/* defined number symbole*/
//   SECTIONB_SYM='B', 				/* specific section data */
};

/**
 * nm execution context
*/
typedef struct s_nm_context {
    uint8_t			flag;			/* nm flag for bonus */
    int8_t			l_endian;		/* local env endian */
} t_nm_context;

/**
 * symbole data
*/
typedef struct s_sym_tab {
	char			*sym_name;  	/* symbole name */
	Elf64_Addr		value;      	/* symbole value */
    uint8_t			type;       	/* symbole type, info subfield */
    uint8_t			bind;       	/* symbole bind, second info subfield */
    Elf64_Section	shndx;      	/* symbole section header index */
} t_sym_tab;

/**
 * nm file data
*/
typedef struct s_elf_file {
    char		    *name;			/* file name */
	void		    *ptr;			/* base file ptr, mmap return */
	void		    *symtab;		/* symtab ptr*/
	Elf64_Off		file_size;		/* file len */
    Elf64_Xword		symtab_size;	/* symtab size in bytes */
    int8_t			class;  		/* bool class 1 for elf64 0 for 32 */
    int8_t			endian; 		/* bool endian 0 for same endian otherwise reverse */
} t_elf_file;

/*
    shoff in elf header, section header offset DONE
    shnum in elf header, section header number DONE
        maybe store this value and compare all section index when we need to user it
    shstrtabdx in elf header, section header str tab index DONE
    shstrtab checked return NULL if no found, return must to ce check DONE
*/

/* struct stat typedef */
typedef struct stat t_stat;

/* parse elf_header */
void			*parse_elf_header(char *str, Elf64_Off *len);
void			display_elf_header(void *elf_struct, int8_t endian);

/* program header */
int8_t			display_file_symbole(t_elf_file *file);

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

/* program header getter */
Elf64_Word		get_program_header_type(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Off		get_program_header_offset(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Addr		get_program_header_vaddr(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Addr		get_program_header_paddr(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword		get_program_header_filesz(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword		get_program_header_memsz(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Word		get_program_header_flags(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword		get_program_header_align(void *ptr, int8_t endian, int8_t is_elf64);

/* symbole getter */
Elf64_Word		get_Sym_name(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Addr		get_Sym_value(void *ptr, int8_t endian, int8_t is_elf64);
uint8_t			get_Sym_info(void *ptr, int8_t is_elf64);
Elf64_Section	get_Sym_shndx(void *ptr, int8_t endian, int8_t is_elf64);

/* handle str table */
char			*get_strtab(void *ptr, uint16_t sizeof_Sshdr, int8_t endian, int8_t is_elf64);
void			*get_shstrtab(void *ptr, int8_t endian, int8_t is_elf64);

/* nm utils */
int     		detect_local_endian();
int				call_open(char *str);
uint16_t 		detect_struct_size(int8_t is_elf64, uint16_t size64, uint16_t size32);
void			display_sym_value(unsigned long nbr, int fd);
uint8_t			compute_hex_len(unsigned long nbr);
/* test utils */
void    		test_reverse_byte(void rev_function());

/* parse cmd line */
t_list 			*extract_file_from_cmd(int argc, char **argv);

/* Display data function */
void			display_all_section_header(t_elf_file *file);
void			display_all_program_header(t_elf_file *file);
void			display_symbol_info(void *sym_ptr, int8_t endian, int8_t is_elf64);
void			display_section_header_info(void *sh_ptr, int8_t endian, int8_t class);

# endif /* FT_NM_HEADER */