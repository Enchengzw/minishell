/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:18:16 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/07 13:17:00 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_create_pipes(t_data *data)
{
	t_cmd *temp;
	
	temp = data->cmd;
	while(temp)
	{
		if (pipe(temp->fds->pipe) == -1)
			return (ERROR);
		temp = temp->next;
	}
	return (SUCCESS);
}

void	ft_link_io(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd;
	while (temp)
	{
		if (temp->infile_flag == 0)
		{			
			if (temp->previous)
			{
				temp->fds->infile = temp->previous->fds->pipe[0];
			}
		}
		if (temp->outfile_flag == 0 && temp->next)
			temp->fds->outfile = temp->fds->pipe[1];
		temp = temp->next;
	}
}

int ft_close(int fd)
{
	if (fd > 0)
	{
		if (close(fd) == 0)
			return (SUCCESS);
	}
	return (ERROR);
}

int	ft_close_everything(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd;
	if (ft_close(data->std_in))
		return (ERROR);
	if (ft_close(data->std_out))
		return (ERROR);
	while (temp)
	{
		if (ft_close(temp->fds->pipe[0]))
			return (ERROR);
		if (ft_close(temp->fds->pipe[1]))
			return (ERROR);
		if (ft_close(temp->fds->infile))
			return (ERROR);
		if (ft_close(temp->fds->outfile))
			return (ERROR);
		temp = temp->next;
	}
}
