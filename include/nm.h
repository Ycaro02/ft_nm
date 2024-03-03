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
/* get type */
# define ELF_TYPE(ptr, endian)		IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_type, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_type, endian)
/* Get machine */
# define ELF_MACHINE(ptr, endian)	IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_machine, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_machine, endian) 
/* Get version */
# define ELF_VERSION(ptr, endian)	IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_version, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_version, endian) 
/* get addr entry point */
# define ELF_ENTRY(ptr, endian)		IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_entry, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_entry, endian) 
/* get Program header table file offset */
# define ELF_PHOFF(ptr, endian)		IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_phoff, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_phoff, endian) 
/* get Section header table file offset */
# define ELF_SHOFF(ptr, endian)		IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_shoff, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_shoff, endian) 
/* get Processor-specific flags */
# define ELF_FLAGS(ptr, endian)		IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_flags, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_flags, endian) 
/* ELF header size in bytes */
# define ELF_EHSIZE(ptr, endian)	IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_ehsize, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_ehsize, endian) 
/* Program header table entry size */
# define ELF_PHENTSIZE(ptr, endian)	IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_phentsize, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_phentsize, endian) 
/* Program header table entry count */
# define ELF_PHNUM(ptr, endian)		IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_phnum, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_phnum, endian) 
/* Section header table entry size */
# define ELF_SHENTSIZE(ptr, endian)	IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_shentsize, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_shentsize, endian) 
/* Section header table entry count */
# define ELF_SHNUM(ptr, endian)		IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_shnum, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_shnum, endian) 
/* Section header string table index */
# define ELF_SHSTRNDX(ptr, endian)	IS_ELF64(ptr) ? READ_DATA(((Elf64_Ehdr *) ptr)->e_shstrndx, endian) : READ_DATA(((Elf32_Ehdr *) ptr)->e_shstrndx, endian) 


typedef struct s_nm_context {
    uint8_t flag;
    int8_t  l_endian;
} t_nm_context;

typedef struct s_elf {
    char    *name;
    uint8_t class;
    uint8_t endian;
} t_elf;

/* parse elf_header */
void    *parse_elf_header(char *str);

/* handle endian */
void    reverse_bytes(uint8_t *ptr, size_t max);
int     detect_local_endian();
/* test utils */
void    test_reverse_byte(void rev_function());

# endif /* FT_NM_HEADER */