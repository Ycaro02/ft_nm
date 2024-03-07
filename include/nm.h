# ifndef FT_NM_HEADER
# define FT_NM_HEADER 1

# include <elf.h>						/* elf structure */
# include <sys/mman.h>					/* mmap */
# include <fcntl.h>						/* open */
# include <sys/stat.h>					/* fstat */
# include <stdlib.h>					/* exit NULL */
# include <stdio.h>						/* Perror */
# include "../libft/basic_define.h" 	/* Color */
# include "endian.h"					/* endian */
# include "../libft/libft.h" 			/* libft */
# include "../libft/list/linked_list.h" /* list */

/* Symbole char enum */
enum e_symb_char {
  UNDIFINED_SYM='U',				/* undefined symbole */
  OBJECT_SYM='R',					/* data object sym like variable */
  FUNCTION_SYM='T', 				/* function symbole */
  SECTIONB_SYM='B', 				/* specific section data */
  COMMON_SYM='C',   				/* common/shared symbole or file name */
  DATA_SYM='D',     				/* data object */
  IFUNC_SYM='I',    				/* indirect function, real adress know at run time */
  NUM_SYM='N',      				/* defined number symbole*/
  LOOS_SYM='O',     				/* specific os */
  LOPROC_SYM='P',   				/* specific procesor */
  NO_BITS_SYM='B',					/* No bits symbole */
  ALLOC_WRITE_SYM='D',				/* if symbole section header flag alloc or write */
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
    Elf64_Xword		symtab_size;	/* symtab size in bytes */
    int8_t			class;  		/* bool class 1 for elf64 0 for 32 */
    int8_t			endian; 		/* bool endian 0 for same endian otherwise reverse */
} t_elf_file;

/* struct stat typedef */
typedef struct stat t_stat;

/* parse elf_header */
void			*parse_elf_header(char *str);
void			display_elf_header(void *elf_struct, int8_t endian);
uint16_t 		detect_struct_size(void *elf_ptr, uint16_t size64, uint16_t size32);

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

/* symbole getter */
Elf64_Word		get_Sym_name(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Addr		get_Sym_value(void *ptr, int8_t endian, int8_t is_elf64);
uint8_t			get_Sym_info(void *ptr, int8_t is_elf64);
Elf64_Section	get_Sym_shndx(void *ptr, int8_t endian, int8_t is_elf64);

/* handle str table */
char			*get_strtab(void *ptr, uint16_t sizeof_Sshdr, int8_t endian, int8_t is_elf64);
void			*get_shstrtab(void *ptr, int8_t endian, int8_t is_elf64);

/* handle endian */
void    		reverse_bytes(uint8_t *ptr, size_t max);
int     		detect_local_endian();

/* test utils */
void    		test_reverse_byte(void rev_function());

/* Display data function */
void			display_all_section_header(t_elf_file *file);
void			display_all_program_header(t_elf_file *file);
void			display_symbol_info(void *sym_ptr, int8_t endian, int8_t is_elf64);
void			display_section_header_info(void *sh_ptr, int8_t endian, int8_t class);
void			display_program_header_info(void *elf_struct, int8_t endian);

# endif /* FT_NM_HEADER */