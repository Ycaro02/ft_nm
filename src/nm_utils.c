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



// ft_printf_fd(2, YELLOW"Local arch: little endian, LSB\n"RESET);
// 	ft_printf_fd(2, YELLOW"Local arch: big endian, MSB\n"RESET);