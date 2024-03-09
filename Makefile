include rsc/mk/color.mk
include rsc/mk/source.mk

NAME	=	ft_nm
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O3 -g
RM		=	rm -rf
TESTER	=	./rsc/nm_tester.sh 
CALL_TESTER = ./rsc/call_tester.sh
DISPLAY_ASCII_ART = ./rsc/mk/ascii.sh

ifeq ($(findstring bonus, $(MAKECMDGOALS)), bonus)
SRCS += $(SRCS_BONUS)
else
SRCS += $(MAIN_MANDATORY)
endif

all:		$(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIST)
	@printf "$(GREEN)Compiling $(NAME) done$(RESET)\n"

$(LIBFT):
	@${DISPLAY_ASCII_ART}
	@printf "$(CYAN)Compiling lib$(RESET)\n"
	@$(MAKE_LIBFT)
	@$(MAKE_LIST)
	@printf "$(GREEN)Compiling lib done$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(YELLOW)Compile $<$(RESET)\n"
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(CFLAGS)

test :	$(NAME)
	@./$(NAME) $(NAME)

dtest:	$(NAME)
	@$(TESTER) $(NAME) 0

all_test:	bonus
	@$(CALL_TESTER)

bonus:	$(NAME)

clean:
ifeq ($(shell [ -d $(OBJ_DIR) ] && echo 0 || echo 1), 0)
	@$(RM) $(OBJ_DIR)
	@printf "$(RED)Clean $(OBJ_DIR)/test output$(RESET)\n"
endif
	@$(RM) nm_out out valgrind_out

fclean:		clean
	@printf "$(RED)Clean $(NAME)/lib$(RESET)\n"
	@$(RM) $(NAME)
	@$(MAKE_LIBFT) fclean
	@$(MAKE_LIST) fclean

re:			fclean all

.PHONY:		all clean fclean re
