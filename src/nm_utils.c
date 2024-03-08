# include "../include/nm.h"

/** 
 *  @brief Simple detect endian function: https://www.embeddedsoft.net/simple-code-to-find-endianness-in-c
 *	@return (Elf define for LSB, MSB)
*/
int detect_local_endian()
{
	int i = 1;
	/* just check value of lower byte */
	return ((*((char *)&i) == 1) ? ELFDATA2LSB : ELFDATA2MSB);
}
// ft_printf_fd(2, YELLOW"Local arch: little endian, LSB\n"RESET);
// 	ft_printf_fd(2, YELLOW"Local arch: big endian, MSB\n"RESET);

/** @brief Get section header offset
 *  @param elf_ptr pointer on elf struct
 *  @param size64 size of 64 bits struct
 *  @param size32 size of 32 bits struct
 *  @return accordate size
*/
uint16_t detect_struct_size(int8_t is_elf64, uint16_t size64, uint16_t size32)
{
	return (is_elf64 ? size64 : size32);
}

/** 
 *	@brief Call open
 *	@param str file name
*/
int call_open(char *str)
{
	int fd = open(str, O_RDONLY);
	
	if (fd < 0) { /* maybe reject 0 ? */
		ft_printf_fd(2, "ft_nm: '%s", str);
		perror("'");
		return (-1);
	}
	return (fd);
}

/** 
 *	@brief Display symbole value
 *	@param nbr number to display
 *	@param fd file descriptor
*/
void	display_sym_value(unsigned long nbr, int fd)
{
	char	*base_16 = "0123456789abcdef";
	
	if (nbr > 15)
		display_sym_value(nbr / 16, fd);
	ft_putchar_fd(base_16[nbr % 16], fd);
}

/** 
 *	@brief Get hex len
 *	@param nbr number to compute
 *	@return hex len
*/
uint8_t compute_hex_len(unsigned long nbr)
{
	uint8_t count = 0;
	while (nbr > 15) {
		nbr /= 16;
		count++;
	}
	return (count);
}

