CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -O3 -g

NAME	=	ft_nm

SRCS	=	src/main.c\
			src/parse_elf_header.c\
			src/nm_utils.c\
			src/parse_program_header.c\
			src/parse_section_header.c\
			src/parse_symtab.c\
			src/display_symbole.c\
			src/handle_str_table.c\
			src/parse_cmd_line.c\
			src/handle_flag.c\
			

SRCS_BONUS	=	src/bonus.c\
				src/handle_flag.c\


LIBFT	= 	libft/libft.a

LIST	= 	libft/list/linked_list.a

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT	=	libft/libft.a

RM		= 	rm -f

MAKE_LIBFT	=	make -s -C libft

MAKE_LIST	=	make -s -C libft/list

TESTER		=	./rsc/diff.sh 


ifeq ($(findstring bonus, ${MAKECMDGOALS}), bonus)
SRCS += ${SRCS_BONUS}
endif

all:		${NAME}

%.o : %.c
	@$(CC) ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			@echo "\033[6;36m ----- Compiling lib\t\t----- \033[0m"
			@${MAKE_LIBFT}
			@${MAKE_LIST}
			@echo "\033[6;32m ----- Compiling lib done\t----- \033[0m"
			@ echo "\033[6;36m ----- Compiling ${NAME} project  ----- \033[0m"
			@${CC} ${CFLAGS} -o ${NAME} $(OBJS) ${LIBFT} ${LIST}
			@echo "\033[6;32m ----- Compiling ${NAME} done     ----- \033[0m"

test :	${NAME}
			@./${NAME} ${NAME}

dtest:	${NAME}
			@${TESTER} ${NAME} 0

vtest:	${NAME}
			@${TESTER} ${NAME} 1

bonus:	${NAME}

clean:
			@echo "\033[6;31m ----- Cleaning  ${NAME} obj\t----- \033[0m"
			@${RM} ${OBJS} ${OBJS_BONUS}
			@${MAKE_LIBFT} clean
			@${MAKE_LIST} clean
			@echo "\033[6;33m ----- Cleaning  ${NAME} done\t----- \033[0m"

fclean:		clean
			@${MAKE_LIBFT} fclean
			@${MAKE_LIST} fclean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus test dtest vtest
