# include "../include/nm.h"

/** 
 *  @brief Simple detect endian function: https://www.embeddedsoft.net/simple-code-to-find-endianness-in-c
 *	@return (Elf define for LSB, MSB)
*/
int detect_local_endian()
{
	int8_t endian = ELFDATA2MSB;
	int i = 1;
	if (*((char *)&i) == 1) { /* jsut check value of lower byte */
		ft_printf_fd(2, YELLOW"Local arch: little endian, LSB\n"RESET);
		endian = ELFDATA2LSB;	
	} else {
		ft_printf_fd(2, YELLOW"Local arch: big endian, MSB\n"RESET);
    }
	return (endian);
}