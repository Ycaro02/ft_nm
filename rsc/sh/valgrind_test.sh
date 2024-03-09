#!/bin/bash

V_OUT="valgrind_out"
VALGRIND_NM="valgrind --log-file=${V_OUT} --track-fds=yes ${FT_NM}"
CHECK_LEAK="All heap blocks were freed -- no leaks are possible"
FD_LEAK="FILE DESCRIPTORS: 4 open (3 std) at exit."
VERIFY_FD="$(pwd)/${V_OUT}"
VALGRIND_CHECK=0

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


valgrind_check() {
	check_valgrind_output "Invalid read/write found in" "${1}" "Invalid" 0
	check_valgrind_output "Conditional jump found in" "${1}" "Conditional" 0
	check_fd_leak ${1}	
	check_valgrind_output "Leaks found in" "${1}" "${CHECK_LEAK}" 1
}

