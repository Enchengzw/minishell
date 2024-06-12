/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:44:53 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/04 20:16:07 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*find_path_loop(char *path_line, char *path, char *command)
{
	int		i;
	char	**paths;

	i = 0;
	while (path_line[i])
	{
		paths = ft_split(path_line, ':');
		if (!paths || !paths[i])
			break ;
		path = paths[i];
		if (ft_strchr(command, '/') == NULL)
		{
			path = ft_strjoin(path, "/");
			path = ft_strjoin(path, command);
		}
		else
			path = ft_strjoin(path, ft_strrchr(command, '/'));
		if (access(path, F_OK | R_OK | X_OK) == 0)
			return (free(paths), path);
		i++;
	}
	ft_error_cnf(command);
	return (free(path), NULL);
}

char	*ft_find_pathcmd(char **envp, char *command)
{
	int		i;
	char	*path;
	char	*path_line;

	i = 0;
	path = 0;
	if (access(command, F_OK | R_OK | X_OK) == 0)
		return (command);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		ft_error_fnf(command);
		return (NULL);
	}
	path_line = envp[i] + 5;
	return (find_path_loop(path_line, path, command));
}

static int	pre_check(char **args, int *k)
{
	if (*k > 0 && (((strcmp(args[*k - 1], "<") == 0
					|| strcmp(args[*k - 1], "<<") == 0))
			|| (strcmp(args[*k - 1], "<") == 0
				|| strcmp(args[*k - 1], "<<") == 0)))
		return (1);
	return (0);
}

void	ft_check_cmd(char **args, int *i, int *k, t_cmd *cmd)
{
	if (pre_check(args, k) == 1)
		return ;
	if (ft_is_builtin(args[*k]) == 0)
		cmd->is_builtin = 1;
	else
	{
		cmd->cmd_path = ft_find_pathcmd(*(cmd->env->env), args[*k]);
		if (cmd->cmd_path == NULL)
			cmd->cmd_flag = -1;
	}
	if (cmd->is_builtin == 1)
	{
		cmd->arg[(*i)++] = ft_strdup(args[*k]);
		cmd->cmd_flag = 1;
	}
	else if (cmd->cmd_path)
	{
		cmd->arg[(*i)++] = ft_strdup(args[*k]);
		cmd->cmd_flag = 1;
	}
}
