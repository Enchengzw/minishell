# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 16:38:50 by ezhou             #+#    #+#              #
#    Updated: 2024/06/26 21:10:50 by rauferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

NAME = minishell

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

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
		./src/Builtins/ft_export_utils.c \
		./src/Builtins/ft_print_sorted_env.c \
		./src/Builtins/ft_pwd.c \
		./src/Builtins/ft_unset.c \
		./src/Signals/signals.c \
		./src/Execute/check.c \
		./src/Execute/execute.c \
		./src/Execute/children.c \
		./src/Execute/utils.c \
		./src/Execute/fd_handler.c \
		./src/Execute/parent.c \
		./src/Cleaning/ft_free.c \
		./src/Parse/check_args.c \
		./src/Parse/check_cmd.c \
		./src/Parse/ft_split_mod_pipe.c \
		./src/Parse/ft_split_mod.c \
		./src/Parse/parse.c \
		./src/Parse/redirections.c \
		./src/Parse/ft_here_doc.c \
		./src/Parse/ft_here_doc_utils.c \
		./src/Parse/parse_utils.c \
		./src/Parse/pre_check_quotes.c \
		./src/Parse/expand_env.c \
		./src/debug.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) -I./$(INCLUDE) -o $(NAME) $(OBJ) -L$(LIBFT) -lft -lreadline
	@echo "$(COLOUR_GREEN)(•̀ᴗ•́)و $(NAME) generado!$(COLOUR_END)"

%.o : %.c
	@$(CC) $(CFLAGS) -I./$(INCLUDE) -c -o $@ $<
	@echo "$(COLOUR_BLUE)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compilando archivos .c$(COLOUR_END)"

norm:
	@norminette $(SRC) $(INCLUDE)*.h

clean:
	@$(RM) $(OBJ)
	@echo "$(COLOUR_RED)¯\_(ツ)_/¯ Objectos removidos!$(COLOUR_END)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED)(╯°□°）╯︵ ┻━┻ $(NAME) removido!$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re norm
