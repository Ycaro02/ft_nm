#!/bin/bash

# Colors
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
CYAN="\e[36m"
LIGHT_GRAY="\e[37m"
GRAY="\e[90m"
LIGHT_RED="\e[91m"
LIGHT_GREEN="\e[92m"
LIGHT_YELLOW="\e[93m"
LIGHT_BLUE="\e[94m"
LIGHT_MAGENTA="\e[95m"
LIGHT_CYAN="\e[96m"
WHITE="\e[97m"
RESET="\e[0m"

BIN=$1
GOOD_FILE="rsc/test_file/good_files/"
BAD_FILE="rsc/test_file/bad_files/"
MANDATORY_FILE="rsc/test_file/mandatory/"

TEST_BAD_FILE="rsc/test_file/test_bad_file/"
PE_FILE="rsc/test_file/pe_file/"


EXIT_CODE=0

FT_NM="./ft_nm"
V_OUT="valgrind_out"
VALGRIND_NM="valgrind --log-file=${V_OUT} --track-fds=yes ${FT_NM}"
CHECK_LEAK="All heap blocks were freed -- no leaks are possible"
FD_LEAK="FILE DESCRIPTORS: 4 open (3 std) at exit."
VERIFY_FD="$(pwd)/${V_OUT}"

VALGRIND_CHECK=0

if [ $2 -eq 1 ]; then
	FT_NM=${VALGRIND_NM}
fi

check_valgrind_test_passed() {
	if [ ${VALGRIND_CHECK} -eq 0 ]; then
		display_color_msg ${LIGHT_MAGENTA} "Valgrind test ${RESET}${GREEN}OK${RESET}"
	else
		display_color_msg ${RED} "Valgrind test failed"
		exit 1
	fi
}

check_fd_leak() {
	FD=0
	cat ${V_OUT} | grep ${FD_LEAK} > /dev/null 2> /dev/null
	SAVE_EXIT=$?
	
	if [ ${SAVE_EXIT} -ne 0 ]; then
		FD=1
	fi

	if [ ${FD} -eq 1 ]; then
		cat ${V_OUT} | grep ${VERIFY_FD} > /dev/null 2> /dev/null
		SAVE_EXIT=$?
		if [ ${SAVE_EXIT} -ne 0 ]; then
			echo -e "${RED}Fd leak ${1} $RESET"
			VALGRIND_CHECK=1
		fi
	fi
}

check_error_code() {
	if [ ${3} -eq 1 ]; then
		if [ ${SAVE_EXIT} -ne 0 ]; then
				echo -e "${RED}${1} ${2} $RESET"
				VALGRIND_CHECK=1
		fi	
	else
		if [ ${SAVE_EXIT} -eq 0 ]; then
				echo -e "${RED}${1} ${2} $RESET"
				VALGRIND_CHECK=1
		fi
	fi
}

check_valgrind_output() {
	cat ${V_OUT} | grep "${3}" > /dev/null 2> /dev/null
	SAVE_EXIT=$?
	check_error_code "${1}" "${2}" "${4}"
}


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

valgrind_check() {
	check_valgrind_output "Invalid read/write found in" "${1}" "Invalid" 0
	check_valgrind_output "Conditional jump found in" "${1}" "Conditional" 0
	check_fd_leak ${1}	
	check_valgrind_output "Leaks found in" "${1}" "${CHECK_LEAK}" 1
}


empty_string_protect() {
	if [ -z $1 ]; then
		BIN="a.out (replace empty string)"
	else
		BIN="$@"
	fi
}

do_diff() {
	diff $1 $2
	if [ $? -ne 0 ]; then
		display_double_color_msg ${YELLOW} "Diff ${BIN}: " ${RED} "KO"
		EXIT_CODE=1
	else
		display_double_color_msg ${YELLOW} "Diff ${BIN}: " ${GREEN} "OK"
	fi
}

elf_file_diff() {
	empty_string_protect "$@"
    nm ${BIN} > nm_out 2> /dev/null;
	# remove bfd plugin error, nm display it on fd 1 idk why
	cut_bfd_plugin_error
    ${FT_NM} ${BIN} > out 2> /dev/null
	do_diff out nm_out
	if [ -f $V_OUT ]; then
		valgrind_check ${BIN}
		check_valgrind_test_passed
		rm ${V_OUT}
	fi
	rm nm_out out
}

exec_file_onebyone() {
	display_color_msg ${CYAN} "Exec file one by one in dir"
	for file in $@; do
		elf_file_diff ${file}
	done
}

multiple_file_diff() {
	display_color_msg ${CYAN} "Call multiple diff"
	# for file in $@; do
	# 	echo -e " ${YELLOW}${file}${RESET}"
	# done
	elf_file_diff "$@"
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
	elf_file_diff rsc/test_file/debug_sym.o
	elf_file_diff rsc/test_file/mandatory/test_facile
	elf_file_diff rsc/test_file/mandatory/not_so_easy_test
	elf_file_diff rsc/test_file/mandatory/not_so_easy_test_32-bit
	elf_file_diff
	elf32_basic_test rsc/test_file/main_32.c
}

check_test_passed() {
	if [ ${EXIT_CODE} -eq 0 ]; then
		display_color_msg ${GREEN} "All test passed"
	else
		display_color_msg ${RED} "Some test failed"
		exit 1
	fi
}

do_test() {
	basic_diff_test
	exec_file_onebyone ${MANDATORY_FILE}*
	exec_file_onebyone ${PE_FILE}*
	exec_file_onebyone ${TEST_BAD_FILE}*
	multiple_file_diff ft_nm rsc/libft_malloc.so libft/ft_atoi.o rsc/test_file/debug_sym.o
	multiple_file_diff ft_nm sda
	multiple_file_diff ft_nm libft/*.o
	multiple_file_diff ${GOOD_FILE}*
	multiple_file_diff ${BAD_FILE}*
	check_test_passed

	if [ -f $V_OUT ]; then
		rm ${V_OUT}
	fi
}

do_test


#### EXIT CODE TESTER ####
test_exit_code() {
    nm ${1} > nm_out 2> /dev/null;
	display_color_msg ${YELLOW} "${1}\nReal Exit code:${CYAN}${?}${RESET}"
    ${FT_NM} ${1} > nm_out 2> /dev/null;
	display_color_msg ${YELLOW} "${1}\nMynm Exit code:${GREEN}${?}${RESET}"
	if [ -f $V_OUT ]; then
		valgrind_check ${1}
		rm ${V_OUT}
	fi
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

# exit_code_tester