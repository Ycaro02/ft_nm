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

elf_file_diff ${BIN}
elf32_basic_test rsc/main_32.c