/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:27:08 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/24 12:36:48 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_restore_io(t_cmd *cmd)
{
	if (dup2((cmd->fds->std_in), STDIN_FILENO) == -1)
		return (ERROR);
	if (dup2((cmd->fds->std_out), STDOUT_FILENO) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_execute_commands(t_cmd *temp, t_data *data)
{
	pid_t	children;

	children = fork();
	if (children == -1)
		return (ft_putstr_fd("Error forking\n", STDERR), ERROR);
	if (children == 0)
		ft_child_process(temp, data);
	else
	{
		if (ft_parent_process(temp, data, children))
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_create_processes(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd;
	while (temp)
	{
		if (temp->next)
		{
			if(pipe(temp->fds->pipe) == ERROR)
				return (ft_putstr_fd("Error creating pipe\n", STDERR), ERROR);
		}
		if (temp->is_builtin == 1)
		{
			if (execute_builtins(temp, data))
				return (12);
		}
		else
		{
			if (ft_execute_commands(temp, data))
				return (ERROR);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_execute(t_data *data)
{
	int	code;

	code = ft_check_data(data);
	if (code != INT_MIN)
		return (code);
	code = ft_create_processes(data);
	if (!code)
		return (ERROR);
	return (code);
}
