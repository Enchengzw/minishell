# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 16:38:50 by ezhou             #+#    #+#              #
#    Updated: 2024/04/03 18:10:21 by ezhou            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

NAME = minishell

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -lreadline

LIBFT = Libft/
INCLUDE = Include/

LIBS = $(LIBFT)/libft.a

SRC	=	./src/main.c \
		./src/error.c \
		./src/Builtins/ft_cd.c \
		./src/Builtins/ft_echo.c \
		./src/Builtins/ft_env_utils.c \
		./src/Builtins/ft_env.c \
		./src/Builtins/ft_exit.c \
		./src/Builtins/ft_export.c \
		./src/Builtins/ft_print_sorted_env.c \
		./src/Builtins/ft_pwd.c \
		./src/Builtins/ft_unset.c \
		./src/Signals/signals.c \
		./src/Execute/check.c \
		./src/Execute/execute.c \
		./src/Execute/pipes.c \
		./src/Execute/utils.c \
		./src/Cleaning/ft_free.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) -I./$(INCLUDE) -L$(LIBFT) -lft -o $(NAME) $(OBJ)
	@echo "$(COLOUR_GREEN)(•̀ᴗ•́)و $(NAME) generado!$(COLOUR_END)"

%.o : %.c
	@$(CC) -I./$(INCLUDE) -c -o $@ $<
	@echo "$(COLOUR_BLUE)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compilando archivos .c$(COLOUR_END)"

clean:
	@$(RM) $(OBJ)
	@echo "$(COLOUR_RED)¯\_(ツ)_/¯ Objectos removidos!$(COLOUR_RED)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED)(╯°□°）╯︵ ┻━┻ $(NAME) removido!$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re