/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:18:16 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/23 13:02:09 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_redirect(t_cmd *cmd)
{
	if (cmd->fds->infile >= 0)
	{
		if (dup2(cmd->fds->infile, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Dup2 Error Infile\n", 2);
			return (ERROR);
		}
		if (ft_close(&(cmd->fds->infile)))
			return (ERROR);
	}
	if (cmd->fds->outfile >= 0)
	{
		if (dup2(cmd->fds->outfile, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Dup2 Error Outfile\n", 2);
			return (ERROR);
		}
		if (ft_close(&(cmd->fds->outfile)))
			return (ERROR);
	}
	return (SUCCESS);
}

void	ft_set_redirections(t_cmd *cmd)
{
	if (cmd->infile_flag == 0)
	{
		if (cmd->previous)
		{
			cmd->fds->infile = cmd->previous->fds->pipe[0];
			cmd->previous->fds->pipe[0] = -1;
		}
	}
	if (cmd->outfile_flag == 0 && cmd->next)
	{
		cmd->fds->outfile = cmd->fds->pipe[1];
		cmd->fds->pipe[1] = -1;
	} 
}

void	ft_child_process(t_cmd *cmd, t_data *data)
{
	if (ft_close(&(cmd->fds->pipe[0])))
		ft_exit_error("Error closing pipe[0]\n", 1, data);
	ft_set_redirections(cmd);
	if (ft_redirect(cmd))
		ft_exit_error("Error redirecting\n", 1, data);
	ft_child_signals();
	if (execve(cmd->cmd_path, cmd->arg, *(cmd->env->env)) == -1)
		ft_exit_error("Error executing command\n", 1, data);
}
