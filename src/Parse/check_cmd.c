/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:44:53 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/27 20:08:43 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*find_path_loop(char *path_line, char *command)
{
	int		i;
	char	**paths;
	char	*path;
	char	*tmp;

	i = 0;
	paths = ft_split(path_line, ':');
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(path, F_OK | R_OK | X_OK) == 0)
		{
			ft_free_char(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_char(paths);
	ft_error_cnf(command);
	return (NULL);
}

char	*ft_find_pathcmd(char **envp, char *command, int *absolute)
{
	int		i;
	char	*path_line;

	i = 0;
	if (command[0] == '\0')
	{
		ft_error_cnf(command);
		return (NULL);
	}
	if (access(command, F_OK | R_OK | X_OK) == 0)
	{
		*absolute = 1;
		return (command);
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		ft_error_fnf(command);
		return (NULL);
	}
	path_line = envp[i] + 5;
	return (find_path_loop(path_line, command));
}

void	ft_check_cmd(char **args, int *i, int *k, t_cmd *cmd)
{
	char	*tmp;
	int		absolute;

	absolute = 0;
	tmp = NULL;
	if (ft_is_builtin(args[*k]) == 0)
		cmd->is_builtin = 1;
	else
	{
		cmd->cmd_path = ft_find_pathcmd(*(cmd->env->env), args[*k], &absolute);
		if (cmd->cmd_path == NULL)
			cmd->cmd_flag = -1;
	}
	if (cmd->cmd_path != NULL || cmd->is_builtin == 1)
		cmd->cmd_flag = 1;
	if (cmd->file_flag != 0)
		tmp = cmd->arg[*k];
	else
		tmp = cmd->arg[*i];
	cmd->arg[(*i)++] = ft_strdup(args[*k]);
	if (!cmd->arg[*i - 1])
		ft_putstr_fd("Malloc Error\n", STDERR);
	if (absolute == 0 && tmp)
		free(tmp);
	tmp = NULL;
}
