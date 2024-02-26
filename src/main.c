#include <elf.h>			/* elf structure */
#include <sys/mman.h>		/* mmap */
#include <fcntl.h>			/* open */
#include <sys/stat.h>		/* fstat */
#include <stdlib.h>			/* exit NULL */
#include <stdio.h>			/* PERROR */

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
