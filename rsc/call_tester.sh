#!/bin/bash

TESTER="rsc/nm_tester.sh" 
NAME="ft_nm"

VALGRIND_OPT=0

if [ ! -z $1 ]; then
VALGRIND_OPT=$1
fi

./rsc/mk/ascii.sh "tester"


# ${TESTER} ${NAME} 1

${TESTER} ${NAME} 0 "-p" "-p"

# ${TESTER} ${NAME} ${VALGRIND_OPT} "-r" "-r"

# ${TESTER} ${NAME} ${VALGRIND_OPT} "-u" "-u"

# ${TESTER} ${NAME} ${VALGRIND_OPT} "-g" "-g"

# ${TESTER} ${NAME} ${VALGRIND_OPT} "-a" "-a"


# ${TESTER} ${NAME} ${VALGRIND_OPT} "-rp" "-rp"
# ${TESTER} ${NAME} ${VALGRIND_OPT} "-ru" "-ru"
# ${TESTER} ${NAME} ${VALGRIND_OPT} "-pu" "-pu"

# ${TESTER} ${NAME} ${VALGRIND_OPT} "-rpu" "-rpu"

# ${TESTER} ${NAME} ${VALGRIND_OPT} "-gu" "-gu"
# ${TESTER} ${NAME} ${VALGRIND_OPT} "-gp" "-gp"
# ${TESTER} ${NAME} ${VALGRIND_OPT} "-gr" "-gr"

# ${TESTER} ${NAME} ${VALGRIND_OPT} "-grpu" "-grpu"
