#!/bin/bash

GOOD_FILE="rsc/test_file/good_files/"
BAD_FILE="rsc/test_file/bad_files/"
MANDATORY_FILE="rsc/test_file/mandatory/"
TEST_BAD_FILE="rsc/test_file/test_bad_file/"
PE_FILE="rsc/test_file/pe_file/"

EXIT_CODE=0




if [ -z $4 ]; then
	NM_FLAGS=""
	FT_NM_FLAGS=""
else
	make bonus > /dev/null
	NM_FLAGS=" $3"
	FT_NM_FLAGS=" $4"
fi

NM="nm${NM_FLAGS}"
FT_NM="./ft_nm${FT_NM_FLAGS}"


source rsc/sh/color.sh
source rsc/sh/valgrind_test.sh
source rsc/sh/exit_code.sh

BIN=$1

if [ $2 -eq 1 ]; then
	FT_NM=${VALGRIND_NM}
fi

display_args_array() {
	for file in $@; do
		echo -e " ${YELLOW}${file}${RESET}"
	done
}

cut_bfd_plugin_error() {
	cat nm_out | grep -v "bfd plugin" > tmp_out
	diff tmp_out nm_out > /dev/null
	if [ $? -ne 0 ]; then
		cat tmp_out > nm_out
	fi
	rm tmp_out
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
		display_double_color_msg ${YELLOW} "Diff ${NM} ${BIN}: " ${RED} "KO"
		EXIT_CODE=1
	else
		display_double_color_msg ${YELLOW} "Diff ${NM} ${BIN}: " ${GREEN} "OK"
	fi
}

elf_file_diff() {
	empty_string_protect "$@"
    ${NM} ${BIN} > nm_out 2> /dev/null;
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
	elf_file_diff rsc/test_file/libft_malloc.so
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
	multiple_file_diff ft_nm rsc/test_file/libft_malloc.so libft/ft_atoi.o rsc/test_file/debug_sym.o
	multiple_file_diff ft_nm rsc/test_file/libft_malloc.so libft/ft_atoi.o dasdas ft_nm
	multiple_file_diff ft_nm sda
	multiple_file_diff ft_nm libft/*.o
	multiple_file_diff ${GOOD_FILE}*
	multiple_file_diff ${BAD_FILE}*
	check_test_passed


	# exit_code_tester

	if [ -f $V_OUT ]; then
		rm ${V_OUT}
	fi
}

do_test