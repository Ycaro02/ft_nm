# ifndef FT_NM_HEADER
# define FT_NM_HEADER 1

# include <elf.h>			/* elf structure */
# include <sys/mman.h>		/* mmap */
# include <fcntl.h>			/* open */
# include <sys/stat.h>		/* fstat */
# include <stdlib.h>			/* exit NULL */
# include <stdio.h>			/* Perror */
# include "../libft/basic_define.h" /* Color */
# include "../libft/libft.h" 	/* libft */
# include "../libft/list/linked_list.h" /* list */

/* struct stat typedef */
typedef struct stat t_stat;

/* From <byteswap.h> */
/* Swap bytes in 16-bit value.  */
#define SWAP_BYTE_16(x)					\
  ((__uint16_t) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))

/* Swap bytes in 32-bit value.  */
#define SWAP_BYTE_32(x)					\
  ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8)	\
   | (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24))

/* Swap bytes in 64-bit value.  */
#define SWAP_BYTE_64(x)			\
  ((((x) & 0xff00000000000000ull) >> 56)	\
   | (((x) & 0x00ff000000000000ull) >> 40)	\
   | (((x) & 0x0000ff0000000000ull) >> 24)	\
   | (((x) & 0x000000ff00000000ull) >> 8)	\
   | (((x) & 0x00000000ff000000ull) << 8)	\
   | (((x) & 0x0000000000ff0000ull) << 24)	\
   | (((x) & 0x000000000000ff00ull) << 40)	\
   | (((x) & 0x00000000000000ffull) << 56))

/* Start macro parse header ident */
/* Get ELF header field */
# define ELF_HFIELD(ptr, field)		(((Elf64_Ehdr *) ptr)->e_ident[field])
/* Alias to easy call ELF Hfield ptr, class*/
# define ELF_CLASS(ptr)				ELF_HFIELD(ptr, EI_CLASS)
/* is 64 bits format */
# define IS_ELF64(ptr)				ELF_CLASS(ptr) == ELFCLASS64
/* if size == 2 swap 16 bits, else: if size == 4 swap 32 bit, else swap 64*/
# define REVERSE_ENDIAN(x, size)	size == 2 ? SWAP_BYTE_16(x) : ((size == 4 ? SWAP_BYTE_32(x) : SWAP_BYTE_64(x)))
/* if endian = 0 || size data == 1, don't revese, else call reverse endian */
# define READ_DATA(data, endian)	(endian == 0 || sizeof(data) == 1) ? data : REVERSE_ENDIAN(endian, sizeof(data)) 

typedef struct s_nm_context {
    uint8_t			flag;				/* nm flag for bonus */
    int8_t			l_endian;			/* local env endian */
} t_nm_context;

typedef struct s_sym_tab {
	char			*sym_name;  /* symbole name */
	Elf64_Addr		value;      /* symbole value */
    uint8_t			type;       /* symbole type, info subfield */
    uint8_t			bind;       /* symbole bind, second info subfield */
    Elf64_Section	shndx;      /* symbole section header index */
} t_sym_tab;

typedef struct s_nm_file {
    char		    *name;			/* file name */
	void		    *ptr;			/* base file ptr, mmap return */
	void		    *symtab;		/* symtab ptr*/
    Elf64_Xword		symtab_size;	/* symtab size in bytes */
    int8_t			class;  		/* bool class 1 for elf64 0 for 32 */
    int8_t			endian; 		/* bool endian 0 for same endian otherwise reverse */
} t_nm_file;


enum e_symb_char {
  UNDIFINED_SYM='U', /* undefined symbole */
  OBJECT_SYM='R',   /* data object sym like variable */
  FUNCTION_SYM='T', /* function symbole */
  SECTIONB_SYM='B', /* specific section data */
  COMMON_SYM='C',   /* common/shared symbole or file name */
  DATA_SYM='D',     /* data object */
  IFUNC_SYM='I',    /* indirect function, real adress know at run time */
  NUM_SYM='N',      /* defined number symbole*/
  LOOS_SYM='O',     /* specific os */
  LOPROC_SYM='P',   /* specific procesor */
  NO_BITS_SYM='B',
  ALLOC_WRITE_SYM='D', /* if symbole section header flag alloc or write */
};


/* parse elf_header */
void    *parse_elf_header(char *str);
void    display_elf_header(void *elf_struct, int8_t endian);


void display_all_section_header(t_nm_file *file);
void display_all_program_header(t_nm_file *file);
void display_symbol_info(void *sym_ptr, int8_t endian, int8_t is_elf64);
void display_section_header_info(void *sh_ptr, int8_t endian, int8_t class);
/* program header */
void display_program_header_info(void *elf_struct, int8_t endian);
/* section header getter */
Elf64_Word get_section_header_name(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Word get_section_header_type(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword get_section_header_flags(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Addr get_section_header_addr(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Off get_section_header_offset(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword get_section_header_size(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Word get_section_header_link(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword get_section_header_addralign(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Xword get_section_header_entsize(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Word get_section_header_info(void *ptr, int8_t endian, int8_t is_elf64);
/* symbole getter */
Elf64_Word get_symbol_name(void *ptr, int8_t endian, int8_t is_elf64);
Elf64_Addr get_symbol_value(void *ptr, int8_t endian, int8_t is_elf64);
unsigned char get_symbol_info(void *ptr, int8_t is_elf64);
Elf64_Section get_symbol_shndx(void *ptr, int8_t endian, int8_t is_elf64);
/* handle endian */
void    reverse_bytes(uint8_t *ptr, size_t max);
int     detect_local_endian();
/* test utils */
void    test_reverse_byte(void rev_function());

# endif /* FT_NM_HEADER */