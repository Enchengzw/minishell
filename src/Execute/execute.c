/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:27:08 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/19 11:09:12 by rauferna         ###   ########.fr       */
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

int	ft_redirect(t_cmd *cmd)
{
	if (cmd->fds->infile)
	{
		if (dup2(cmd->fds->infile, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Dup2 ErroIr\n", 2);
			return (ERROR);
		}
		close(cmd->fds->infile);
	}
	if (cmd->fds->outfile)
	{
		if (dup2(cmd->fds->outfile, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Dup2 Error\n", 2);
			return (ERROR);
		}
		close(cmd->fds->outfile);
	}
	return (SUCCESS);
}

int	ft_actions(pid_t pid, t_cmd *cmd, t_data *data)
{
	if (pid == 0)
	{
		/*ft_printf("adsa%s\n %s\n", cmd->cmd_path, cmd->arg[0]);*/
		//close(cmd->fds->pipe[0]);
		if (execve(cmd->cmd_path, cmd->arg, data->env) == -1)
			return (ft_putstr_fd("Error executing execve\n", STDERR), ERROR);
	}
	else
	{
		waitpid(pid, &g_exit_code, 0);
		if (ft_restore_io(cmd))
			return (ft_putstr_fd("Out of resources\n", STDERR), ERROR);
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
			return (free(childrens), ft_putstr_fd("Out of resources\n", STDERR), 12);
		childrens[i] = fork();
		if (childrens[i] == -1)
			return (free(childrens), ft_putstr_fd("Out of resources\n", STDERR), 12);
		if (ft_actions(childrens[i], temp, data))
			return (free(childrens), 12);
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
	/*if (ft_create_pipes(data) == SUCCESS)
		return (ft_putstr_fd("Not enough resources to create pipe", STDERR), 12);*/
	ft_link_io(data);
	return (ft_create_processes(data));
}
