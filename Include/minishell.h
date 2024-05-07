/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:42:47 by rguerrer          #+#    #+#             */
/*   Updated: 2024/05/07 13:24:14 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <termios.h>

# define GREEN_TEXT "\x1b[32m"
# define YELLOW_TEXT "\x1b[33m"
# define RESET_TEXT "\x1b[0m"

# define ERROR 1
# define SUCCESS 0
# define STDERR 2

int					g_exit_code;

typedef struct s_fds
{
	int	infile;
	int	outfile;
	int	pipe[2];
	int	std_in;
	int	std_out;
}	t_fds;

typedef struct s_env
{
	char			***env;
	int				env_size;
}					t_env;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*previous;
	t_fds			*fds;
	char			*cmd_path;
	char			**arg;
	t_env			*env;
	int				num_arg;
	int				infile_flag;
	int				outfile_flag;
	int				cmd_flag;
	int				file_flag;
	int				semicolon_flag;
	int				is_builtin;
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
int					ft_exit(t_cmd *cmd, t_data *start);
int					ft_unset(t_cmd **cmd);

// BUILTINS UTILS
char				*ft_getenv(char *variable, char **env);
int					ft_valid_name(char *string);
int					ft_is_in_env_index(char **env, char *variable, int *index, int *flag);
int					ft_print_export_error(char *variable);

// SIGNALS
static void			ft_shell_handler(int signal);
static void			ft_shell_handler(int signal);
void				ft_child_signals(void);
void				ft_main_signals(void);

//PARSE
int					ft_parse(char *input, t_data *data);
void				ft_check_exceptions(char **args, int *j, t_cmd *cmd);
int					ft_is_builtin(char *command);
char				*ft_pre_check_quotes(char *input);
int					ft_here_doc(char **args, int i, t_cmd *cmd);
int					ft_check_redirections(char **args, int i, t_cmd *cmd,
						t_data *data);
int					ft_openfile(char *file, int type);
void				ft_create_struct(char **args, t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_find_pathcmd(char **envp, char *command);
char				**ft_split_mod(char const *s, char c);
char				**ft_process_args(char **args, int *j, t_cmd *cmd,
						t_data *data);

// EXECUTOR
int					ft_execute(t_data *data);
int					ft_create_processes(t_data *data);
int					ft_actions(pid_t pid, t_cmd *cmd, t_data *data);
int					ft_redirect(t_cmd *cmd);
int					ft_restore_io(t_cmd *cmd);
int					ft_create_pipes(t_data *data);
void				ft_link_io(t_data *data);
int					ft_check_data(t_data *data);
int					ft_check_fds(t_fds *io);

// ERROR
void				ft_exit_error(char *str, int n);
int					error_cnf(char *command);
int					error_fnf(char *file);
int					error_syntax(char *file);

// UTILS
int					ft_list_size(t_cmd *cmd);

// CLEANING
void				ft_free_content(t_data *data);
void				ft_free_list(t_cmd *cmd);
int					ft_close_all_fds(t_data *data);

#endif