#include <elf.h>			/* elf structure */
#include <sys/mman.h>		/* mmap */
#include <fcntl.h>			/* open */
#include <sys/stat.h>		/* fstat */
#include <stdlib.h>			/* exit NULL */
#include <stdio.h>			/* PERROR */
# include "../libft/basic_define.h"
#include "../libft/libft.h" 	/* libft */

/* struct stat typedef */
typedef struct stat t_stat;

/* Elf structure typedef */
typedef Elf64_Ehdr t_elf64;
typedef Elf32_Ehdr t_elf32;

/* Get ELF header field */
# define ELF_HFIELD(ptr, field)		(((t_elf64 *) ptr)->e_ident[field])
/* Alias to easy call ELF Hfield ptr, class*/
# define ELF_CLASS(ptr)				ELF_HFIELD(ptr, EI_CLASS)
/* is 64 bits format */
# define IS_ELF64(ptr)				ELF_CLASS(ptr) == ELFCLASS64
/* get type by class */
# define ELF_TYPE(ptr)				IS_ELF64(ptr) ? ((t_elf64 *) ptr)->e_type : ((t_elf32 *) ptr)->e_type  


/* parse elf_header */
void *parse_elf_header(char *str);