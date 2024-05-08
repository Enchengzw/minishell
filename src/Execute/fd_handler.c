/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:31:12 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/08 15:36:39 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_close(int *fd)
{
	if (*fd > 0)
	{
		//printf("closing fd: %d\n", *fd);
		if (close(*fd) == 0)
		{
			*fd = -1;
			return (SUCCESS);
		}
		else
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_close_unused_fds(t_cmd *cmd)
{
	t_cmd	*temp;
	
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

