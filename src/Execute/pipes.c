/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:18:16 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/22 17:53:40 by rauferna         ###   ########.fr       */
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
			write(2, "A\n", 2);
		if (temp->infile_flag == 0)
		{			
			write(2, "B\n", 2);
			if (temp->previous)
				temp->fds->infile = temp->previous->fds->pipe[0];
		}
			write(1, "C\n", 2);
		if (temp->outfile_flag == 0)
			temp->fds->outfile = temp->fds->pipe[1];
		temp = temp->next;
			write(2, "D\n", 2);
	}
}
