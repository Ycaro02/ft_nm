include rsc/mk/color.mk
include rsc/mk/source.mk

NAME	=	ft_nm
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O3 -g
RM		=	rm -rf
TESTER	=	./rsc/nm_tester.sh 

ifeq ($(findstring bonus, $(MAKECMDGOALS)), bonus)
SRCS += $(SRCS_BONUS)
SRCS += $(MAIN_BONUS)
else
SRCS += $(MAIN_MANDATORY)
endif

all:		$(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	lib $(OBJS) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIST)
	@printf "$(GREEN)Compiling $(NAME) done$(RESET)\n"

lib:
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

vtest:	$(NAME)
	@$(TESTER) $(NAME) 1

bonus:	$(NAME)

clean:
ifeq ($(shell [ -d $(OBJ_DIR) ] && echo 0 || echo 1), 0)
	@printf "$(RED)Clean $(OBJ_DIR)$(RESET)\n"
	@$(RM) $(OBJ_DIR)
	@printf "$(RED)Clean $(NAME)$(RESET)\n"
endif
	@$(MAKE_LIBFT) clean
	@$(MAKE_LIST) clean

fclean:		clean
	@$(MAKE_LIBFT) fclean
	@$(MAKE_LIST) fclean
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus test dtest vtest lib
