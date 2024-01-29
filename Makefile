# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

NAME =minishell

CC = gcc
CFLAGS =-Wall -Werror -Wextra -g3

# librarys
LIB = libft/libft.a

SRC =	main.c 		\
		init.c		\
		manage.c	\
    expand.c  \
		quots.c		\
		divide_args.c	\
		matrix_utils.c	\
		quot_utils.c	\
		utils.c			\
		parse.c			\
		init_cmds.c		\
		add_io_files.c	\
		errors.c

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(PINK)Compiling the librarys.$(CLEAR)"
	$(MAKE) -sC ./libft
	@echo "$(GREEN)librarys compiled correctly\n$(CLEAR)"
	@echo "$(PINK)Compiling the minishell.$(CLEAR)"
	$(CC) $(OBJ) $(LIB) -o $(NAME) -lreadline
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

$(OBJ_DIR)%.o: src/%.c
	@echo "$(PINK)Compiling Object.$(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\n"

clean:
	@echo "$(PINK)Removing compiled files.$(CLEAR)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -sC ./libft
	@echo "$(GREEN)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -sC ./libft
	@echo "$(GREEN)Exec. files removed correctly\nSuccess!\n$(CLEAR)"

###############################################################################

clear:
	@clear

run: clear all
	@./$(NAME)

ruin: env
env: all
	@env -i ./$(NAME)

re: fclean all
.PHONY: clean fclean re all run