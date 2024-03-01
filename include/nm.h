#include <elf.h>			/* elf structure */
#include <sys/mman.h>		/* mmap */
#include <fcntl.h>			/* open */
#include <sys/stat.h>		/* fstat */
#include <stdlib.h>			/* exit NULL */
#include <stdio.h>			/* Perror */
# include "../libft/basic_define.h" /* Color */
#include "../libft/libft.h" 	/* libft */

/* struct stat typedef */
typedef struct stat t_stat;

/* Start macro parse header ident */
/* Get ELF header field */
# define ELF_HFIELD(ptr, field)		(((Elf64_Ehdr *) ptr)->e_ident[field])
/* Alias to easy call ELF Hfield ptr, class*/
# define ELF_CLASS(ptr)				ELF_HFIELD(ptr, EI_CLASS)
/* is 64 bits format */
# define IS_ELF64(ptr)				ELF_CLASS(ptr) == ELFCLASS64
/* Get type */
/* get type by class */
# define ELF_TYPE(ptr)				IS_ELF64(ptr) ? ((Elf64_Ehdr *) ptr)->e_type : ((Elf32_Ehdr *) ptr)->e_type  
/* Get machine */
# define ELF_MACHINE(ptr)           IS_ELF64(ptr) ? ((Elf64_Ehdr *) ptr)->e_machine : ((Elf32_Ehdr *) ptr)->e_machine 
/* Get version */
# define ELF_VERSION(ptr)           IS_ELF64(ptr) ? ((Elf64_Ehdr *) ptr)->e_version : ((Elf32_Ehdr *) ptr)->e_version 

typedef struct s_elf {
    char    *name;
    uint8_t class;
    uint8_t endian;
} t_elf;


/* parse elf_header */
void *parse_elf_header(char *str);