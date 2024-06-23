/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:42:47 by rguerrer          #+#    #+#             */
/*   Updated: 2024/06/12 19:43:16 by rauferna         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

# define GREEN_TEXT "\x1b[32m"
# define YELLOW_TEXT "\x1b[33m"
# define RESET_TEXT "\x1b[0m"

# define ERROR 1
# define SUCCESS 0
# define STDERR 2

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
	char			*type;
	t_env			*env;
	int				*exit_code;
	int				num_arg;
	int				infile_flag;
	int				outfile_flag;
	int				cmd_flag;
	int				file_flag;
	int				is_builtin;
	int				two_points;
	int				redirect_then;
}					t_cmd;

typedef struct s_data
{
	char			*user_input;
	char			**env;
	t_cmd			*cmd;
	int				exit_code;
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
int					ft_is_in_env_index(char **env, char *variable,
						int *index, int *flag);
int					ft_print_export_error(char *variable);
char				*ft_get_label(char *variable);
char				*ft_get_value(char *variable);
char				*ft_make_export_line(char *label, char *value);
int					ft_has_args(char **arg);

// SIGNALS
void				ft_shell_handler(int signal);
void				ft_child_signals(void);
void				ft_main_signals(void);

//PARSE
int					ft_parse(char *input, t_data *data);
void				ft_check_exceptions(char **args, int *j, t_cmd *cmd);
int					ft_is_builtin(char *command);
char				*ft_pre_check_quotes(char *input, int *quote);
int					ft_here_doc(char **args, char *res, int i, t_cmd *cmd);
int					ft_check_redirections(char **args, int i, t_cmd *cmd,
						t_data *data);
int					ft_openfile(char *file, int type);
void				ft_create_struct(char **args, t_data *data);
char				*ft_find_pathcmd(char **envp, char *command, int *absolute);
char				**ft_split_mod(char const *s, t_cmd *cmd);
char				**ft_split_mod_pipe(char const *s);
void				ft_process_args(t_cmd *cmd, t_data *data, char **args);
char				*ft_copy_char(char *str, int *k, t_cmd *cmd);
int					ft_special_character(char c);
char				*ft_strjoin_allocs1(char *s1, char *s2);
void				ft_check_cmd(char **args, int *i, int *k, t_cmd *cmd);
void				ft_check_type(const char *s, t_cmd *cmd, int *i, int *k);
int					ft_len_type(char *str);
void				ft_check_double_greather(char **args,
						char *res, int i, t_cmd *cmd);

// EXECUTOR
int					ft_execute(t_data *data);
int					ft_create_processes(t_data *data);
int					ft_redirect(t_cmd *cmd);
int					ft_restore_io(t_cmd *cmd);
int					ft_check_data(t_data *data);
void				ft_child_process(t_cmd *cmd, t_data *data);
int					ft_parent_process(t_cmd *cmd, t_data *data, pid_t pid);
int					execute_builtins(t_cmd *cmd, t_data *data);
void				ft_set_redirections(t_cmd *cmd);

// ERROR
void				ft_exit_error(char *str, int n, t_data *data);
int					ft_error_cnf(char *command);
int					ft_error_fnf(char *file);
int					ft_error_syntax(char *file);
void				ft_print_node(t_cmd *cmd);
void				ft_format_exit_code(int *exit_code);

// UTILS
int					ft_list_size(t_cmd *cmd);

// CLEANING
void				ft_free_content(t_data *data);
void				ft_free_list(t_cmd *cmd);
int					ft_close(int *fd);
int					ft_close_unused_fds(t_cmd *cmd);
int					ft_free_all(t_data *data);

#endif