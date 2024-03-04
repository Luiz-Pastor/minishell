# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

NAME =minishell

CC = gcc
CFLAGS =-Wall -Werror -Wextra 

# librarys
LIB = libft/libft.a

VPATH = src:src/built-ins:src/parser:src/signals:src/executor

SRC =		main.c 		\
			manage.c	\
			errors.c	\
			errors_2.c	\
			envp_utils.c

BUILT_INS =	built_ins.c \
			export.c \
			cd.c \
			unset.c \
			pwd.c \
			env.c \
			exit.c \
			echo.c \
			variables_utils.c \
			export_alone.c \
			export_2.c

PARSER =	expand.c  \
			quots.c		\
			divide_args.c	\
			matrix_utils.c	\
			quot_utils.c	\
			utils.c			\
			parse.c			\
			init_cmds.c		\
			init.c		\
			add_io_files.c	\
			expand_2.c \
			check_cmd_arg.c	\
			add_elements.c

SIGNALS =	signals.c \
			signals_heredoc.c

EXECUTOR =	executor.c		\
			exe_one_cmd.c	\
			aux_manage_files.c	\
			manage_io_files.c	\
			here_doc.c \
			path.c \
			childs.c

OBJ_DIR = obj/
OBJ =	$(SRC:%.c=$(OBJ_DIR)%.o) \
		$(BUILT_INS:%.c=$(OBJ_DIR)%.o) \
		$(PARSER:%.c=$(OBJ_DIR)%.o) \
		$(SIGNALS:%.c=$(OBJ_DIR)%.o) \
		$(EXECUTOR:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(PINK)Compiling the librarys.$(CLEAR)"
	$(MAKE) -sC ./libft
	@echo "$(GREEN)librarys compiled correctly\n$(CLEAR)"
	@echo "$(PINK)Compiling the minishell.$(CLEAR)"
	$(CC) $(OBJ) $(LIB) -o $(NAME) -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

$(OBJ_DIR)%.o: %.c
	@echo "$(PINK)Compiling Object.$(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -I/Users/$(USER)/.brew/opt/readline/include -o $@

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

r: run
run: clear all
	@./$(NAME)

ruin: env
env: all
	@env -i ./$(NAME)

re: fclean all
.PHONY: clean fclean re all run

del: 
	@echo $(OBJ)