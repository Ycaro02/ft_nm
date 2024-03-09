#!/bin/bash

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
