# include "../include/nm.h"

/* Get machine */
static inline Elf64_Half get_header_machine(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_machine, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_machine, endian));
}

/* Get version */
static inline Elf64_Word get_header_version(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_version, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_version, endian));
}

/* Get addr entry point */
static inline Elf64_Addr get_header_entry(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_entry, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_entry, endian));
}

/* Get Program header table file offset */
static inline Elf64_Off get_header_phoff(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phoff, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phoff, endian));
}

/* Get Section header table file offset */
static inline Elf64_Off get_header_shoff(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shoff, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shoff, endian));
}

/* Get Processor-specific flags */
static inline Elf64_Word get_header_flags(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_flags, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_flags, endian));
}

/* ELF header size in bytes */
static inline Elf64_Half get_header_ehsize(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_ehsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_ehsize, endian));
}

/* Program header table entry size */
static inline Elf64_Half get_header_phentsize(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phentsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phentsize, endian));
}

/* Program header table entry count */
static inline Elf64_Half get_header_phnum(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_phnum, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_phnum, endian));
}

/* Section header table entry size */
static inline Elf64_Half get_header_shentsize(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shentsize, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shentsize, endian));
}

/* Section header table entry count */
static inline Elf64_Half get_header_shnum(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shnum, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shnum, endian));
}

/* Section header string table index */
static inline Elf64_Half get_header_shstrndx(void *ptr, uint8_t endian) {
  if (IS_ELF64(ptr)) {
    return (READ_DATA(((Elf64_Ehdr *) ptr)->e_shstrndx, endian));
  }
  return (READ_DATA(((Elf32_Ehdr *) ptr)->e_shstrndx, endian));
}

static void test_macro(void *elf_struct, int8_t endian)
{
	ft_printf_fd(1, YELLOW"type:      %d == %d\n"RESET, ELF_TYPE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_type);
	ft_printf_fd(1, YELLOW"machine:   %d == %d\n"RESET, ELF_MACHINE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_machine);
	ft_printf_fd(1, YELLOW"version:   %d == %d\n"RESET, ELF_VERSION(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_version);
	ft_printf_fd(1, YELLOW"entry:     %p == %p\n"RESET, ELF_ENTRY(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_entry);
	ft_printf_fd(1, YELLOW"phoff:     %d == %d\n"RESET, ELF_PHOFF(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phoff);
	ft_printf_fd(1, YELLOW"shoff:     %d == %d\n"RESET, ELF_SHOFF(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shoff);
	ft_printf_fd(1, YELLOW"flags:     %d == %d\n"RESET, ELF_FLAGS(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_flags);
	ft_printf_fd(1, YELLOW"ehsize:    %d == %d\n"RESET, ELF_EHSIZE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_ehsize);
	ft_printf_fd(1, YELLOW"phentsize: %d == %d\n"RESET, ELF_PHENTSIZE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phentsize);
	ft_printf_fd(1, YELLOW"phnum:     %d == %d\n"RESET, ELF_PHNUM(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phnum);
	ft_printf_fd(1, YELLOW"shentsize: %d == %d\n"RESET, ELF_SHENTSIZE(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shentsize);
	ft_printf_fd(1, YELLOW"shnum:     %d == %d\n"RESET, ELF_SHNUM(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shnum);
	ft_printf_fd(1, YELLOW"shstrndx:  %d == %d\n"RESET, ELF_SHSTRNDX(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shstrndx);
}

static void test_fun(void *elf_struct, int8_t endian)
{
	ft_printf_fd(1, GREEN"type:      %d == %d\n"RESET, get_header_type(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_type);
	ft_printf_fd(1, GREEN"machine:   %d == %d\n"RESET, get_header_machine(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_machine);
	ft_printf_fd(1, GREEN"version:   %d == %d\n"RESET, get_header_version(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_version);
	ft_printf_fd(1, GREEN"entry:     %p == %p\n"RESET, get_header_entry(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_entry);
	ft_printf_fd(1, GREEN"phoff:     %d == %d\n"RESET, get_header_phoff(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phoff);
	ft_printf_fd(1, GREEN"shoff:     %d == %d\n"RESET, get_header_shoff(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shoff);
	ft_printf_fd(1, GREEN"flags:     %d == %d\n"RESET, get_header_flags(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_flags);
	ft_printf_fd(1, GREEN"ehsize:    %d == %d\n"RESET, get_header_ehsize(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_ehsize);
	ft_printf_fd(1, GREEN"phentsize: %d == %d\n"RESET, get_header_phentsize(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phentsize);
	ft_printf_fd(1, GREEN"phnum:     %d == %d\n"RESET, get_header_phnum(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_phnum);
	ft_printf_fd(1, GREEN"shentsize: %d == %d\n"RESET, get_header_shentsize(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shentsize);
	ft_printf_fd(1, GREEN"shnum:     %d == %d\n"RESET, get_header_shnum(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shnum);
	ft_printf_fd(1, GREEN"shstrndx:  %d == %d\n"RESET, get_header_shstrndx(elf_struct, endian), ((Elf64_Ehdr *) elf_struct)->e_shstrndx);
}

int main(int argc, char **argv)
{
	t_nm_context	context;
	char 			*path = "a.out";
	
	context.flag = 0;
	context.l_endian = detect_local_endian();
	printf("Local endian = %d\n", context.l_endian);
	if (argc > 1) {
		path = argv[1];
	}
	void *elf_struct = parse_elf_header(path); 
	if (!elf_struct) {
		return (1);
	}
	ft_printf_fd(1, "class: %d\n", ELF_CLASS(elf_struct));
	/* endian bool, 0 if same endian */
	int8_t endian =  ELF_HFIELD(elf_struct, EI_DATA) - context.l_endian; 
	
	
	test_macro(elf_struct, endian);
	test_fun(elf_struct, endian);
	
	
	// test_reverse_byte(reverse_bytes);

	return (0);
}
