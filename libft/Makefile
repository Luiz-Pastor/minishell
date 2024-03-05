# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 11:55:51 by abarrio-          #+#    #+#              #
#    Updated: 2024/03/05 09:44:41 by lpastor-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

NAME = libft.a

# COMPILER OPTIONS
AR = ar -crs
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
#CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

###########################################################################

PATH_BASICS_FUNC=ft_lib_basics
BASICS_FUNC =	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_bzero.c \
				ft_toupper.c \
				ft_tolower.c

PATH_STR_FUNC=ft_lib_str
STR_FUNC =		ft_strlen.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_strcmp.c

PATH_MEM_FUNC=ft_lib_mem
MEM_FUNC =		ft_memset.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_memcmp.c

PATH_REST_FUNC=ft_lib_rest
REST_FUNC =		ft_atoi.c \
				ft_calloc.c \
				ft_substr.c \
				ft_split.c \
				ft_itoa.c \
				ft_atof.c	\
				ft_mfree.c

PATH_PUT_FUNC=ft_lib_put
PUT_FUNC =		ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr.c \
				ft_putchar.c

PATH_GNL_FUNC=ft_gnl
GNL_FUNC = 		ft_get_next_line.c \
				ft_get_next_line_utils.c

PATH_PRINTF_FUNC=ft_printf
PRINTF_FUNC =	ft_printf.c \
				ft_type_char.c \
				ft_type_string.c \
				ft_type_ptr.c \
				ft_type_nbr.c \
				ft_type_nbr2.c \
				ft_type_un_nbr.c \
				ft_type_hex.c \
				ft_type_percent.c \
				ft_width.c \
				ft_type_un_nbr2.c \
				ft_type_hex2.c \
				ft_type_nbr3.c \
				ft_type_hex3.c 

PATH_LIB_STRUCT=ft_lib_struct
STRUCT_FUNC =	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstadd_back.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c

OBJ_DIR = obj
OBJ=	$(BASICS_FUNC:%.c=$(OBJ_DIR)/%.o) \
		$(STR_FUNC:%.c=$(OBJ_DIR)/%.o) \
		$(MEM_FUNC:%.c=$(OBJ_DIR)/%.o) \
		$(REST_FUNC:%.c=$(OBJ_DIR)/%.o) \
		$(PUT_FUNC:%.c=$(OBJ_DIR)/%.o) \
		$(GNL_FUNC:%.c=$(OBJ_DIR)/%.o) \
		$(PRINTF_FUNC:%.c=$(OBJ_DIR)/%.o) \
		$(STRUCT_FUNC:%.c=$(OBJ_DIR)/%.o)

###########################################################################

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(PINK)Compiling the library.$(CLEAR)"
	$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)libft compiled correctly\n$(CLEAR)"

$(OBJ_DIR)/%.o: $(PATH_BASICS_FUNC)/%.c
	@echo "$(PINK)Compiling Object $< $(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PATH_STR_FUNC)/%.c
	@echo "$(PINK)Compiling Object $< $(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PATH_MEM_FUNC)/%.c
	@echo "$(PINK)Compiling Object $< $(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PATH_REST_FUNC)/%.c
	@echo "$(PINK)Compiling Object $< $(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PATH_PUT_FUNC)/%.c
	@echo "$(PINK)Compiling Object $< $(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PATH_GNL_FUNC)/%.c
	@echo "$(PINK)Compiling Object $< $(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PATH_PRINTF_FUNC)/%.c
	@echo "$(PINK)Compiling Object $< $(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PATH_LIB_STRUCT)/%.c
	@echo "$(PINK)Compiling Object $< $(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

###########################################################################

clean:
	@echo "$(PINK)Removing compiled files.$(CLEAR)"
	$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Object files removed correctly\n$(CLEAR)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(GREEN)Exec. files removed correctly\nSuccess!\n$(CLEAR)"

re: fclean all

.PHONY: clean fclean re all