/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:31:12 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/27 12:46:51 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_close(int *fd)
{
	int	result;

	if (*fd > 0)
	{
		result = close(*fd);
		if (result == 0)
		{
			*fd = -1;
			return (SUCCESS);
		}
		else
		{
			write(2, "Close failure\n", 15);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ft_close_unused_fds(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	if (cmd->next)
	{
		temp = cmd->next;
		while (temp)
		{
			if (ft_close(&(temp->fds->infile)))
			{
				return (ERROR);
			}
			if (ft_close(&(temp->fds->outfile)))
			{
				return (ERROR);
			}
			temp = temp->next;
		}
	}
	return (SUCCESS);
}
