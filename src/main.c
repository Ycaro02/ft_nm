#include <elf.h>			/* elf structure */
#include <sys/mman.h>		/* mmap */
#include <fcntl.h>			/* open */
#include <sys/stat.h>		/* fstat */
#include <stdlib.h>			/* exit NULL */
#include <stdio.h>			/* PERROR */
# include "../libft/basic_define.h"
#include "../libft/libft.h" 	/* libft */

typedef struct stat t_stat;

int call_open(char *str)
{
	int fd = open(str, O_RDONLY);
	if (fd < 0) { /* maybe reject 0 ? */
		perror("Error cannot open:\'"); 
		ft_printf_fd(2, "Incorect fd for %s fd %d\n", str, fd);
		exit(1);
	}
	return (fd);
}


int check_identification_byte(void *elf_struct, int byte, int value)
{
	int ret = ((Elf64_Ehdr *) elf_struct)->e_ident[byte] == value;
	if (!ret) {
		ft_printf_fd(2, "Index %d, not a valid value %d, expected %d\n", byte, (((Elf64_Ehdr *) elf_struct)->e_ident[byte]), value);
	}	
	return (ret);
}

int header_identification_correct(void *elf_struct)
{
	if (!check_identification_byte(elf_struct, EI_MAG0, ELFMAG0)\
		|| !check_identification_byte(elf_struct, EI_MAG1, ELFMAG1)\
		|| !check_identification_byte(elf_struct, EI_MAG2, ELFMAG2)\
		|| !check_identification_byte(elf_struct, EI_MAG3, ELFMAG3)) {
		return (FALSE);
	}
	// ft_strncmp(((Elf64_Ehdr *) elf_struct)->e_ident, ELFMAG, SELFMAG);
	return (TRUE);
}

int main(int argc, char **argv)
{
	char *str = "a.out";
	if (argc > 1) {
		str = argv[1];
	}
	int fd = call_open(str);
	if (fd < 0) {
		return (1);
	}
	t_stat sb;
	int ret = fstat(fd, &sb);
	if (ret != -1 ) {
		size_t len = sb.st_size;
		void *elf_struct = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
		if (elf_struct != MAP_FAILED) {
			ft_printf_fd(1, "Mmap success\n");
			for (int i = 0; i < 16; ++i) {
				ft_printf_fd(1, "[%d]: |%d|\n", i, ((Elf64_Ehdr *)elf_struct)->e_ident[i]);
			}
			header_identification_correct(elf_struct);
			munmap(elf_struct, len);
		} else {
			perror("Error fstat:\'"); 
		}
	} else {
		perror("Error fstat:\'"); 
	}




	close(fd);
	return (0);
}
