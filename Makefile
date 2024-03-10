include rsc/mk/color.mk
include rsc/mk/source.mk

NAME		=	ft_nm
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -O3 -g
RM			=	rm -rf
TESTER		=	./rsc/nm_tester.sh 
CALL_TESTER =	./rsc/call_tester.sh
ASCII_ART	=	./rsc/mk/ascii.sh

ASCII_NAME		=	${NAME}

ifeq ($(findstring bonus, $(MAKECMDGOALS)), bonus)
ASCII_NAME	= "bonus"
SRCS += $(SRCS_BONUS)
else
SRCS += $(MAIN_MANDATORY)
endif

all:		$(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(OBJ_DIR)
	@printf "$(CYAN)Compiling lib...$(RESET)\n"
	@$(MAKE_LIBFT)
	@$(MAKE_LIST)
	@printf "$(GREEN)Compiling lib done$(RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIST)
	@printf "$(GREEN)Compiling $(NAME) done$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@([ ! -d ${OBJ_DIR} ] && ${ASCII_ART} ${ASCII_NAME} && mkdir ${OBJ_DIR}) || printf ""
	@printf "$(YELLOW)Compile $<$(RESET)\n"
	@$(CC) -o $@ -c $< $(CFLAGS)

test :	$(NAME)
	@./$(NAME) $(NAME)

dtest:	$(NAME)
	@$(TESTER) $(NAME) 0

all_test:	bonus
	@$(CALL_TESTER)

bonus: clear_mandatory ${NAME}

clear_mandatory:
ifeq ($(shell [ -f ${OBJ_DIR}/main.o ] && echo 0 || echo 1), 0)
	@printf "$(RED)Clean mandatory obj $(RESET)\n"
	@rm -rf ${OBJ_DIR}
endif

clean:
ifeq ($(shell [ -d ${OBJ_DIR} ] && echo 0 || echo 1), 0)
	@$(RM) $(OBJ_DIR)
	@printf "$(RED)Clean $(OBJ_DIR)/test output$(RESET)\n"
	@$(RM) nm_out out valgrind_out
endif

fclean:		clean
	@printf "$(RED)Clean $(NAME)/lib$(RESET)\n"
	@$(RM) $(NAME) nm_out out valgrind_out
	@$(MAKE_LIBFT) fclean
	@$(MAKE_LIST) fclean

re:			fclean all

.PHONY:		all clean fclean re bonus
