#!/bin/bash

# Colors
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
CYAN="\e[36m"
RESET="\e[0m"

BIN=$1
GOOD_FILE="rsc/test_file/good_files/"
BAD_FILE="rsc/test_file/good_files/"
EXIT_CODE=0

display_color_msg() {
	COLOR=$1
	MSG=$2
	echo -e "${COLOR}${MSG}${RESET}"
}

display_double_color_msg () {
	COLOR1=$1
	MSG1=$2
	COLOR2=$3
	MSG2=$4
	echo -e "${COLOR1}${MSG1}${RESET}${COLOR2}${MSG2}${RESET}"
}

cut_bfd_plugin_error() {
	cat nm_out | grep -v "bfd plugin" > tmp_out
	diff tmp_out nm_out > /dev/null
	if [ $? -ne 0 ]; then
		cat tmp_out > nm_out
	fi
	rm tmp_out
}

elf_file_diff() {
    nm ${1} > nm_out 2> /dev/null;

	cut_bfd_plugin_error

    ./ft_nm ${1} > out 2> /dev/null
	
	if [ -z "$1" ]; then
		BIN="a.out (replace empty string)"
	else
		BIN="$1"
	fi

    diff out nm_out 
	if [ $? -ne 0 ]; then
		display_double_color_msg ${YELLOW} "Diff ${BIN}: " ${RED} "KO"
		EXIT_CODE=1
	else
		display_double_color_msg ${YELLOW} "Diff ${BIN}: " ${GREEN} "OK"
	fi
	rm nm_out out
}

multiple_file_diff() {
	display_color_msg ${CYAN} "Call multiple diff: "
	for file in $@; do
		echo -e " ${YELLOW}${file}${RESET}"
	done
	elf_file_diff $@
}

elf32_basic_test() {
    NAME32=${1}.out
    gcc -m32 ${1} -o ${NAME32}
    elf_file_diff ${NAME32}
    rm ${NAME32}
}

basic_diff_test() {
	elf_file_diff ${BIN}
	elf_file_diff rsc/libft_malloc.so
	elf_file_diff libft/ft_atoi.o
	elf_file_diff rsc/debug_sym.o
	elf_file_diff rsc/test_file/mandatory/test_facile
	elf_file_diff rsc/test_file/mandatory/not_so_easy_test
	elf_file_diff rsc/test_file/mandatory/not_so_easy_test_32-bit
	elf_file_diff
	elf32_basic_test rsc/main_32.c
}

correct_error_test() {
	display_color_msg ${CYAN} "Correct error test: "
	elf_file_diff rsc/test_file/mandatory/error_header
	elf_file_diff rsc/test_file/mandatory/header_offset_error
}

incorrect_error_test() {
	display_color_msg ${CYAN} "Incorrect error test: "
	elf_file_diff rsc/test_file/mandatory/header
	elf_file_diff rsc/test_file/mandatory/header_and_prog
	elf_file_diff rsc/test_file/mandatory/header_and_prog_copy
	elf_file_diff rsc/test_file/mandatory/header_copy
	elf_file_diff rsc/test_file/mandatory/unterminated_string
	elf_file_diff rsc/test_file/mandatory/wrong_arch
}

check_test_passed() {
	if [ ${EXIT_CODE} -eq 0 ]; then
		display_color_msg ${GREEN} "All test passed"
	else
		display_color_msg ${RED} "Some test failed"
		exit 1
	fi
}

export "LC_COLLATE=en_US.utf8"
basic_diff_test
correct_error_test
incorrect_error_test
multiple_file_diff ft_nm rsc/libft_malloc.so libft/ft_atoi.o rsc/debug_sym.o
multiple_file_diff ft_nm sda
multiple_file_diff ft_nm libft/*.o
multiple_file_diff ${GOOD_FILE}*
multiple_file_diff ${BAD_FILE}*
check_test_passed


#### EXIT CODE TESTER ####
test_exit_code() {
    nm ${1} > nm_out 2> /dev/null;
	display_color_msg ${YELLOW} "${1}\nReal Exit code:${CYAN}${?}${RESET}"
    ./ft_nm ${1} > nm_out 2> /dev/null;
	display_color_msg ${YELLOW} "${1}\nMynm Exit code:${GREEN}${?}${RESET}"
    rm nm_out
}

test_perm_file() {
    PERM=$1
    OLD=$2
    if [ ! ${PERM} -eq ${OLD} ];
    then
        mv perm_${OLD} perm_${1}
    else
        touch perm_${1}
    fi
    chmod ${1} perm_${1}
    test_exit_code perm_${1}
    chmod 777 perm_${1}
}

exit_code_tester() {
    test_exit_code ${BIN}
    test_exit_code ' '
    test_exit_code dsa
    test_perm_file 000 000
    test_perm_file 111 000
    test_perm_file 444 111
	test_perm_file 777 444
    rm perm_777
}
#### END ####