/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:02:51 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/24 13:14:57 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_parent_process(t_cmd *cmd, t_data *data, pid_t pid)
{ 
	pid_t	pid_check;
	int		code;
	
	code = 0;
	if (cmd->previous && ft_close(&(cmd->previous->fds->pipe[0])))
			return (ft_putstr_fd("Error closing pipe[0]\n", STDERR), ERROR);
	if (ft_close(&(cmd->fds->pipe[1])))
		return (ft_putstr_fd("Error closing pipe[1]\n", STDERR), ERROR);
	while(1)
	{
		pid_check = waitpid(pid, &code, 0);
		if (pid_check > 0)
			break;
	}
	data->exit_code = code;
	return (SUCCESS);
}