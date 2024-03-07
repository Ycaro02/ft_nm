#!/bin/bash

# Colors
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
CYAN="\e[36m"
RESET="\e[0m"

BIN=$1

display_color_msg() {
	COLOR=$1
	MSG=$2
	echo -e "${COLOR}${MSG}${RESET}"
}


elf_file_diff() {
    nm ${1} > nm_out;
    ./ft_nm ${1} > out
    diff out nm_out 
	if [ $? -ne 0 ]; then
		display_color_msg ${RED} "Diff ${1} failed"
	else
		display_color_msg ${GREEN} "Diff ${1} ok"
	fi
	rm nm_out out
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
	elf32_basic_test rsc/main_32.c
}

basic_diff_test



#### EXIT CODE TESTER ####

test_exit_code() {
    nm ${1} > nm_out 2> /dev/null; 
	display_color_msg ${YELLOW} "${1}\nExit code:${GREEN}${?}${RESET}"
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