/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:27:08 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/02 11:43:16 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_restore_io(t_cmd *cmd)
{
	if (dup2(STDIN_FILENO, *(cmd->fds->std_in)) == -1)
		return (ERROR);
	if (dup2(STDOUT_FILENO, *(cmd->fds->std_out)) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_redirect(t_cmd *cmd)
{
	if (cmd->fds->infile)
	{
		if (dup2(STDIN_FILENO, cmd->fds->infile) == -1)
			return (ERROR);
	}
	if (cmd->fds->outfile)
	{
		if (dup2(STDOUT_FILENO, cmd->fds->outfile) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_actions(pid_t pid, t_cmd *cmd)
{
	if (pid == 0)
	{
		//close(cmd->fds->pipe[0]);
		if (execve(cmd->cmd_path, cmd->arg, cmd->env->env) == -1)
			return (ft_putstr_fd("Error executing execve\n", STDERR), ERROR);
	}
	else
	{
		//close(cmd->fds->pipe[1])
		if (ft_restore_io(cmd))
			return (ft_putstr_fd("Out of resources", STDERR), ERROR);
	}
	return (SUCCESS);
}

int	ft_create_processes(t_data *data)
{
	int		size;
	pid_t	*childrens;
	int		i;
	t_cmd	*temp;

	temp = data->cmd;
	i = -1;
	size = ft_list_size(data->cmd);
	childrens = (pid_t *)ft_calloc(size + 1, sizeof(pid_t));
	while (++i < size)
	{	
		ft_child_signals();
		if (ft_redirect(temp))
			return (free(childrens), ft_putstr_fd("Out of resources", STDERR), 12);
		childrens[i] = fork();
		if (childrens[i] == -1)
			return (free(childrens), ft_putstr_fd("Out of resources", STDERR), 12);
		if (ft_actions(childrens[i], temp))
			return (free(childrens), 12);
		temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_execute(t_data *data)
{
	int code;

	code = ft_check_data(data);
	if (code != INT_MIN)
		return (code);
	if (ft_create_pipes(data))
		return (ft_putstr_fd("Not enough resources to create pipe", STDERR), 12);
	ft_link_io(data);
	return (ft_create_processes(data));
}