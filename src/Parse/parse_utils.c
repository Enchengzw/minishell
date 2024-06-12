/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:31:05 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/04 20:16:23 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_check_exceptions(char **args, int *j, t_cmd *cmd)
{
	if (args[*j] && (args[*j][0] == '|' || args[*j][0] == ';')
		&& (!args[*j + 1] || !args[*j + 1][0]))
	{
		ft_error_syntax(args[*j]);
		cmd->cmd_flag = -1;
	}
}

int	ft_is_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (0);
	else if (ft_strcmp(command, "echo") == 0)
		return (0);
	else if (ft_strcmp(command, "env") == 0)
		return (0);
	else if (ft_strcmp(command, "exit") == 0)
		return (0);
	else if (ft_strcmp(command, "export") == 0)
		return (0);
	else if (ft_strcmp(command, "pwd") == 0)
		return (0);
	else if (ft_strcmp(command, "unset") == 0)
		return (0);
	else
		return (1);
}

int	ft_openfile(char *file, int type)
{
	int	fd[2];

	if (type == 1)
	{
		fd[0] = open(file, O_RDONLY, 0644);
		if (fd[0] == -1)
			ft_error_fnf(file);
		return (fd[0]);
	}
	else if (type == 2)
	{
		fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] == -1)
			ft_error_fnf(file);
		return (fd[1]);
	}
	else if (type == 3)
	{
		fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[1] == -1)
			ft_error_fnf(file);
		return (fd[1]);
	}
	return (-1);
}
