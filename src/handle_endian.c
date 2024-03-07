# include "../include/nm.h"

/** 
 *  @brief Simple detect endian function: https://www.embeddedsoft.net/simple-code-to-find-endianness-in-c
 *	@return (Elf define for LSB, MSB)
*/
int detect_local_endian()
{
	int i = 1;
	return ((*((char *)&i) == 1) ? ELFDATA2LSB : ELFDATA2MSB);
	
	// if (*((char *)&i) == 1) { /* jsut check value of lower byte */
		// ft_printf_fd(2, YELLOW"Local arch: little endian, LSB\n"RESET);
		// endian = ELFDATA2LSB;	
	// } 
	// else {
	// 	ft_printf_fd(2, YELLOW"Local arch: big endian, MSB\n"RESET);
    // }
	// return (endian);
}