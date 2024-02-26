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
		ft_printf_fd(2, "ft_nm: Can't open %s fd %d\n", str, fd);
		return (-1);
	}
	return (fd);
}

void *load_elf_info(int fd, size_t len)
{
	void *elf_struct = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
	if (elf_struct == MAP_FAILED) {
		perror("Error mmap:\'"); 
		close(fd);
		return (NULL);
	}
	return (elf_struct);
}


int check_identification_byte(char c, int val1, int val2)
{
	int ret = (c == val1 || c == val2);
	// if (!ret) {
		// ft_printf_fd(2, "Index %d, not a valid value %d, expected %d\n", byte, (((Elf64_Ehdr *) elf_struct)->e_ident[byte]), value);
	// }	
	return (ret);
}

int header_identification_correct(char *str, void *elf_struct)
{
	/* check magic number ELFMAG */
	if (ft_strncmp(((char *) ((Elf64_Ehdr *) elf_struct)->e_ident), ELFMAG, SELFMAG) != 0) {
		ft_printf_fd(2, "ft_nm: %s: file format not recognized\n", str);
		return (FALSE);
	} else {
		ft_printf_fd(1, "Good format: %s\n", ((char *) ((Elf64_Ehdr *) elf_struct)->e_ident));
	}
	/* get class 32 or 64 bits */
	char c = ((Elf64_Ehdr *) elf_struct)->e_ident[EI_CLASS];
	int ret = check_identification_byte(c, ELFCLASS32, ELFCLASS64);
	c = ((Elf64_Ehdr *) elf_struct)->e_ident[EI_DATA];
	ret = check_identification_byte(c, ELFDATA2LSB, ELFDATA2MSB);
	if (ret == 0) {
		ft_printf_fd(2, "Invalid class fount class %d\n", c);
		return (FALSE);

	}
	// int class = ((Elf64_Ehdr *) elf_struct)->e_ident[EI_CLASS];
	// if (class == ELFCLASSNONE || (class != ELFCLASS32 && class != ELFCLASS64)) {
	// } else {
	// 	ft_printf_fd(1, "Good class\n");
	// }

	// int endian = ((Elf64_Ehdr *) elf_struct)->e_ident[EI_DATA];
	// if (endian == ELFDATANONE || (endian != ELFDATA2LSB && endian != ELFDATA2MSB)) {
	// 	ft_printf_fd(2, "Invalid endian fount endian %d\n", endian);
	// 	return (FALSE);
	// } else {
	// 	ft_printf_fd(1, "Good endian\n");
	// }
	return (TRUE);
}


void *file_to_elf(char *str)
{
	void	*elf_struct = NULL;
	t_stat 	sb;
	int 	fd = call_open(str);
	
	if (fd < 0) {
		return (NULL);
	}
	
	if (fstat(fd, &sb) == -1) {
		perror("Error fstat:\'"); 
		close(fd);
		return (NULL);
	}
	
	elf_struct = load_elf_info(fd, sb.st_size);
	if (!elf_struct) { /* fd close in load_elf_info in error case */
		return (NULL);
	}
	close(fd); /* now we had data in void * we can close fd */
	if (header_identification_correct(str, elf_struct) == FALSE) {
		munmap(elf_struct, sb.st_size);
		elf_struct = NULL;
	}
	return (elf_struct);
}

int main(int argc, char **argv)
{
	char *path = "a.out";
	if (argc > 1) {
		path = argv[1];
	}
	void *elf_struct = file_to_elf(path); 
	if (!elf_struct) {
		return (1);
	}
	return (0);
}
