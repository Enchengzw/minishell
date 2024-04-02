/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:42:47 by rguerrer          #+#    #+#             */
/*   Updated: 2024/04/02 11:28:16 by ezhou            ###   ########.fr       */
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
	int	*std_in;
	int	*std_out;
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
	int				std_in;
	int				std_out;
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

// EXECUTOR
int					ft_execute(t_data *data);
int					ft_create_processes(t_data *data);
int					ft_actions(pid_t pid, t_cmd *cmd);
int					ft_redirect(t_cmd *cmd);
int					ft_restore_io(t_cmd *cmd);
int					ft_create_pipes(t_data *data);
void				ft_link_io(t_data *data);
int					ft_check_data(t_data *data);
int					ft_check_fds(t_fds *io);

// ERROR
void				ft_exit_error(char *str, int n);

// UTILS
int					ft_list_size(t_cmd *cmd);

// CLEANING
void				ft_free_content(t_data *data);

#endif