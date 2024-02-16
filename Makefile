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

PATH_SRC=src/
SRC =		main.c 		\
			manage.c	\
			errors.c	

PATH_BUILT_INS=src/built-ins/

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

PATH_PARSER=src/parser/
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

PATH_SIGNALS=src/signals/
SIGNALS =	signals.c

PATH_EXECUTOR=src/executor/
EXECUTOR =	executor.c		\
			exe_one_cmd.c	\
			manage_io_files.c	\
			here_doc.c \
			path.c

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
	$(CC) $(OBJ) $(LIB) -o $(NAME) -lreadline
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

$(OBJ_DIR)%.o: $(PATH_SRC)%.c
	@echo "$(PINK)Compiling Object.$(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PATH_BUILT_INS)%.c
	@echo "$(PINK)Compiling Object.$(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PATH_SIGNALS)%.c
	@echo "$(PINK)Compiling Object.$(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PATH_PARSER)%.c
	@echo "$(PINK)Compiling Object.$(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PATH_EXECUTOR)%.c
	@echo "$(PINK)Compiling Object.$(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

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