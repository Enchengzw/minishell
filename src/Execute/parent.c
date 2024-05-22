/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:02:51 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/08 15:15:56 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_parent_process(t_cmd *cmd, t_data *data, pid_t pid)
{
	if (cmd->previous && ft_close(&(cmd->previous->fds->pipe[0])))
			return (ft_putstr_fd("Error closing pipe[0]\n", STDERR), ERROR);
	if (ft_close(&(cmd->fds->pipe[1])))
		return (ft_putstr_fd("Error closing pipe[1]\n", STDERR), ERROR);
	waitpid(pid, &(data->exit_code), 0);
	/* if (ft_restore_io(cmd))
			return (ft_putstr_fd("Out of resources\n", STDERR), ERROR); */
	return (SUCCESS);
}