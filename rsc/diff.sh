#!/bin/bash

# Color definition
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
CYAN="\e[36m"
RESET="\e[0m"

BIN=$1

elf_file_diff() {
    nm ${1} | cut -d ' ' -f 1,3 > nm_out;
    ./ft_nm ${1} | cut -d ' ' -f 1,3 > out
    diff out nm_out && echo -e "${GREEN}Diff ${1} ok${RESET}"
    rm nm_out out
}

elf32_basic_test() {
    NAME32=${1}.out
    gcc -m32 ${1} -o ${NAME32}
    elf_file_diff ${NAME32}
    rm ${NAME32}
}

test_exit_code() {
    nm ${1} > nm_out 2> /dev/null; echo -e "${YELLOW}${1}\tExit code:${RESET} ${GREEN}${?}${RESET}"
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
    test_exit_code " "
    test_exit_code dsa
    test_perm_file 000 000
    test_perm_file 666 000
    test_perm_file 444 666
    test_perm_file 111 444
    rm perm_111
}

elf_file_diff ${BIN}
elf32_basic_test rsc/main_32.c
exit_code_tester