#!/bin/bash

TESTER="rsc/nm_tester.sh" 
NAME="ft_nm"

${TESTER} ${NAME} 1

${TESTER} ${NAME} 0 "-p" "-p"

${TESTER} ${NAME} 1 "--no-sort" "-p"

${TESTER} ${NAME} 0 "-r" "-r"

${TESTER} ${NAME} 1 "-r" "-r"

${TESTER} ${NAME} 0 "-u" "-u"

${TESTER} ${NAME} 1 "-u" "-u"

${TESTER} ${NAME} 1 "-rp" "-rp"

${TESTER} ${NAME} 1 "-ru" "-ru"

${TESTER} ${NAME} 1 "-pu" "-pu"

${TESTER} ${NAME} 1 "-rpu" "-rpu"
