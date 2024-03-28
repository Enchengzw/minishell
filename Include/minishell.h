/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:42:47 by rguerrer          #+#    #+#             */
/*   Updated: 2024/03/28 12:27:27 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

# define GREEN_TEXT "\x1b[32m"
# define RESET_TEXT "\x1b[0m"

# define ERROR 1
# define SUCCESS 0
# define STDERR 2

int					g_exit_code;

typedef struct s_fds
{
	int	infile;
	int	outfile;
	int	here_document;
	int	pipe[2];
	int	*stdin;
	int	*stdout;
}	t_fds;

typedef struct s_env
{
	char			**env;
	int				env_size;
}					t_env;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*previous;
	t_fds           *fds;
	char			*cmd_path;
	char			**arg;
	t_env			*env;
	int				num_arg;
}					t_cmd;

typedef struct s_data
{
	// t_token		*token;
	char			*user_input;
	char			**env;
	t_cmd			*cmd;
	int				stdin;
	int				stdout;
}					t_data;

// BUILTINS
int					ft_pwd(void);
int					ft_env(t_cmd **cmd);
int					ft_cd(t_cmd **cmd);
int					ft_echo(char **args);
int					ft_env(t_cmd **cmd);
int					ft_export(t_cmd **cmd);
int					ft_print_sorted_env(char **env);

// BUILTINS UTILS
int					ft_valid_name(char *string);
int					ft_is_in_env_index(char **env, char *variable, int *index);
int					ft_print_export_error(char *variable);

// SIGNALS
static void			ft_shell_handler(int signal);
static void			ft_shell_handler(int signal);
void				ft_child_signals(void);
void				ft_main_signals(void);

// ERROR
void				ft_exit_error(char *str, int n);

#endif