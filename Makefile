CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -O3 -g

SRCS	=	src/main.c\
			src/parse_elf_header.c\
			src/handle_endian.c\
			src/parse_program_header.c\
			src/parse_section_header.c\
			src/parse_symtab.c\
			

LIBFT	= 	libft/libft.a

LIST = libft/list/linked_list.a

OBJS = $(SRCS:.c=.o)

RM	= rm -f

NAME	= ft_nm

LIBFT	= libft/libft.a

# CALL_TESTER="make -s -C tester"

MAKE_LIBFT	=	make -s -C libft

MAKE_LIST	=	make -s -C libft/list

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

test : ${NAME}
		@./${NAME} ${NAME}

clean:
			@echo "\033[6;31m ----- Cleaning  ${NAME} obj\t----- \033[0m"
			@${RM} ${OBJS}
			@${MAKE_LIBFT} clean
			@${MAKE_LIST} clean
			@echo "\033[6;33m ----- Cleaning  ${NAME} done\t----- \033[0m"

fclean:		clean
			@${MAKE_LIBFT} fclean
			@${MAKE_LIST} fclean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
