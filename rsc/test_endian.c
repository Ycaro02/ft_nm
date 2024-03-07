/* 	@brief reverse byte function need to be checked/optimize */
void    reverse_bytes(uint8_t *ptr, size_t max)
{
    uint8_t    tmp;

    for (size_t i = 0; i < max / 2; ++i) {
        tmp = ptr[i];
        ptr[i] = ptr[max - i - 1];
        ptr[max - i - 1] = tmp;
    }
}

void test_reverse_byte(void rev_function())
{
    int16_t nb16 = 5;
	rev_function(&nb16, 2);
    int16_t rev16 = 5;
    int16_t new16 = SWAP_BYTE_16(rev16);

    if (new16 != nb16) {
        ft_printf_fd(1, RED"Int 16 bad reverse\n"RESET);
    } else {
        ft_printf_fd(1, GREEN"Int  16 reverse OK\n"RESET);
    }

	int32_t nb32 = 5;
	rev_function(&nb32, 4);
    int32_t rev32 = 5;
    int32_t new32 = SWAP_BYTE_32(rev32);

    if (new32 != nb32) {
        ft_printf_fd(1, RED"Int 32 bad reverse\n"RESET);
    } else {
        ft_printf_fd(1, GREEN"Int  32 reverse OK\n"RESET);
    }

    int64_t nb64 = 5l;
	rev_function(&nb64, 8);
    int64_t rev64 = 5;
    int64_t new64 = SWAP_BYTE_64(rev64);

    if (new64 != nb64) {
        ft_printf_fd(1, RED"Int 64 bad reverse\n"RESET);
    } else {
        ft_printf_fd(1, GREEN"Int  64 reverse OK\n"RESET);
    }

    uint64_t unb64 = 5ul;
	rev_function(&unb64, 8);
    uint64_t urev64 = 5;

    uint64_t unew64 = SWAP_BYTE_64(urev64);
    if (unew64 != unb64) {
        ft_printf_fd(1, RED"UInt 64 bad reverse\n"RESET);
    } else {
        ft_printf_fd(1, GREEN"UInt 64 reverse OK\n"RESET);
    }

}
