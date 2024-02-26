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

/* Get ELF header field */
# define ELF_HFIELD(ptr, field)		(((Elf64_Ehdr *) ptr)->e_ident[field])
/* Alias to easy call ELF Hfield ptr, class*/
# define ELF_CLASS(ptr)				ELF_HFIELD(ptr, EI_CLASS)

/* parse elf_header */
void *parse_elf_header(char *str);